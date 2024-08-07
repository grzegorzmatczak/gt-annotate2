#include "painter.hpp"

#include "logger.hpp"
#include "labeldialog.hpp"
#include "configreader.hpp"

Painter::Painter(GraphicsScene *graphicsScene, GraphicsView* graphicsView)
	: mGraphicsScene(graphicsScene)
	, mGraphicsView(graphicsView)
{
	mLogger = std::make_unique<Logger>(LogType::PAINTER, LogLevel::LOW, LogFunction::YES);
	QPixmap test;

	ConfigReader cf = ConfigReader();
	QJsonObject config;
	cf.readConfig("config.json", config);
	mSettings.configureColors(config);
	mGraphicsView->setPainterSettings(&mSettings);

	test.load("test.png");
	addImageToScene(test);


}

void Painter::addImageToScene(QPixmap image)
{
	mLogger->printStartFunction(__FUNCTION__);
	mPixmap = static_cast<GraphicsPixmapItem*>(mGraphicsScene->addPixmap(image));

	mPixmap->setEnabled(true);
	mPixmap->setVisible(true);
	mPixmap->setOpacity(1.0);
	mPixmap->setAcceptHoverEvents(true);
	mPixmap->setAcceptTouchEvents(true);
	mPixmap->setZValue(-2);
	mPixmap->update();

	mImage = image.toImage();
	mPaintImage = image.toImage();

	for (int y = 0; y < mPaintImage.height(); y++)
	{
		for (int x = 0; x < mPaintImage.width(); x++)
		{
			mPaintImage.setPixelColor(x, y, QColor{ 255, 255, 255, 127 });
		}
	}
	
	QPixmap whiteBoardPixmap = QPixmap::fromImage(mPaintImage);
	mPaintPixmap = static_cast<GraphicsPixmapItem*>(mGraphicsScene->addPixmap(whiteBoardPixmap));
	mPaintPixmap->setEnabled(true);
	mPaintPixmap->setVisible(true);
	mPaintPixmap->setOpacity(0.5);
	mPaintPixmap->setAcceptHoverEvents(true);
	mPaintPixmap->setAcceptTouchEvents(true);
	mPaintPixmap->setZValue(-1);
	mPaintPixmap->update();
}

void Painter::onPaintOnBoard(qint32 x, qint32 y)
{
	onPaintOnBoardInColor(x, y, mSettings.m_color);
}

void Painter::onPaintBackground(qint32 x, qint32 y)
{
	onPaintOnBoardInColor(x, y, mSettings.m_colorBackground);
}


void Painter::onPaintOnBoardInColor(qint32 x, qint32 y, QColor color)
{
	mLogger->print(QString("x:%1, y:%2").arg(x).arg(y)
		, LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	if (mSettings.m_penSize == 1)
	{
		mPaintImage.setPixelColor(x, y, color);
	}
	else if (mSettings.m_penSize > 1 && mSettings.m_penSize < 20)
	{
		qint32 it = mSettings.m_penSize - 1;
		for (int zx = -it; zx <= it; zx++)
		{
			for (int zy = -it; zy <= it; zy++)
			{
				mPaintImage.setPixelColor(x + zx, y + zy, color);
			}
		}
	}
	else
	{
		mLogger->print("painter not select", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	}
	mPaintPixmap->setPixmap(QPixmap::fromImage(mPaintImage));
}

void Painter::onChangeColor(QColor color)
{
	mSettings.m_color = color;
}

void Painter::onChangePenSize(qint32 size)
{
	mSettings.m_penSize = size;
}

void Painter::onSavePaint()
{
	mLogger->printStartFunction(__FUNCTION__);
	//cv::Mat cleanData = cv::Mat(mPaintImage.height(), mPaintImage.width(), CV_8UC1, cv::Scalar(0));
	QImage imageToSave = QImage(mPaintImage.width(), mPaintImage.height(), QImage::Format_Indexed8);
	int counter{0};


	QVector<QRgb> my_table;
	for(int i = 0; i < 256; i++) my_table.push_back(qRgb(i,i,i));
	imageToSave.setColorTable(my_table);
	for (int i = 0; i < mPaintImage.width(); i++)
	{
		for (int j = 0; j < mPaintImage.height(); j++)
		{
			imageToSave.setPixel(i,j,0);
		}
	}

	QList<QGraphicsItem*> items = mGraphicsScene->items(Qt::DescendingOrder);
	for(auto& item: items)
	{
		if (item->type() == RoiType::ROI && item->isEnabled())
		{
			QRectF rect = item->boundingRect();
			qreal x;
			qreal y;
			qreal width;
			qreal height;
			rect.getRect(&x, &y, &width, &height);
			mLogger->print(QString("x:%1,y:%2,w:%3,h:%4")
				.arg(x)
				.arg(y)
				.arg(width)
				.arg(height)
				, LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
			
			for (int i = 0; i < mSettings.m_colors.size(); i++)
			{
				QString color = mSettings.m_colors[i];
				for (int i = x; i < x+width; i++)
				{
					for (int j = y; j < y+height; j++)
					{
						
						if (mSettings.m_colorHash[color].rgb() == mPaintImage.pixel(i, j))
						{
							counter++;
							imageToSave.setPixel(i,j,mSettings.m_colorIntHash[color]);
						}

					}
				}
			}
		}
	}

	mLogger->printEndFunction(__FUNCTION__);

	
	
	imageToSave.save("test_1.png");
	//m_dataMemory->m_gt[m_id] = cleanData;
	//const QString m_fileNameWithPath = m_dataMemory->gtPaths(m_id) + m_dataMemory->filenames(m_id);
	//cv::imwrite(m_fileNameWithPath.toStdString(), cleanData);
	mLogger->printEndFunction(__FUNCTION__);

}


void Painter::onAddRectToScene(QPointF startPoint, QPointF stopPoint, bool dialog, QString name)
{
	mLogger->printStartFunction(__FUNCTION__);
	qreal x = 0;
	qreal y = 0;
	qreal width = 1;
	qreal heigt = 1;

	if (startPoint.x() < stopPoint.x() && startPoint.y() < stopPoint.y())
	{
		x = startPoint.x();
		width = qAbs(x - stopPoint.x());
		y = startPoint.y();
		heigt = qAbs(y - stopPoint.y());
		mLogger->print("Bottom Right", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	}
	else if (startPoint.x() < stopPoint.x() && startPoint.y() > stopPoint.y())
	{
		x = startPoint.x();
		width = qAbs(x - stopPoint.x());
		y = stopPoint.y();
		heigt = qAbs(y - startPoint.y());
		mLogger->print("Up Right", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	}
	else if (startPoint.x() > stopPoint.x() && startPoint.y() < stopPoint.y())
	{
		x = stopPoint.x();
		width = qAbs(x - startPoint.x());
		y = startPoint.y();
		heigt = qAbs(y - stopPoint.y());
		mLogger->print("Bottom Left", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	}
	else if (startPoint.x() > stopPoint.x() && startPoint.y() > stopPoint.y())
	{
		x = stopPoint.x();
		width = qAbs(x - startPoint.x());
		y = stopPoint.y();
		heigt = qAbs(y - startPoint.y());
		mLogger->print("Up Left", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
	}

	if (dialog)
	{
		LabelDialog* dialog = new LabelDialog("");
		int dialogCode = dialog->exec();

		if (dialogCode == QDialog::Accepted)
		{
			QString tempStr = dialog->getLabelName();
			QRectF tempRectToText = QRectF(x, y, width, heigt);
			QColor color = QColor::fromRgb(0, 0, 0, 0);
			GraphicsRectItem* rectItem = new GraphicsRectItem(color, tempStr, tempRectToText, RoiType::ROI, 0);
			mGraphicsScene->addItem(rectItem);
			mLogger->print("addItem", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
		}
		if (dialogCode == QDialog::Rejected)
		{
			mLogger->print("QDialog::Rejected", LogType::PAINTER, LogLevel::LOW, __FUNCTION__);
		}
	}
	else
	{}
	mLogger->printEndFunction(__FUNCTION__);
}