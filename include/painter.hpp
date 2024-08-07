#pragma once

#include <QtWidgets>
#include <QHash>
#include <QObject>

#include "graphicsscene.hpp"
#include "graphicsview.hpp"

#include "graphicspixmapitem.hpp"
#include "graphicsrectitem.hpp"
#include "paintersettings.hpp"

class Logger;

enum RoiType
{
	ROI = 4,
	PAINT = 5,
	IMAGE = 6,
	DLIB = 10
};

class Painter : public QObject
{	
	Q_OBJECT
	public:
		Painter(GraphicsScene *graphicsScene, GraphicsView* graphicsView);
	private:
		void addImageToScene(QPixmap image);
		void onPaintOnBoardInColor(qint32 x, qint32 y, QColor color);
	public slots:
		void onPaintOnBoard(qint32 x, qint32 y);
		void onPaintBackground(qint32 x, qint32 y);
		void onChangeColor(QColor color);
		void onChangePenSize(qint32 size);
		void onSavePaint();
		void onAddRectToScene(QPointF startPoint, QPointF stopPoint, bool dialog, QString name);
	private:
		std::unique_ptr<Logger> mLogger;
	private:
		QImage mPaintImage;
		QImage mGridImage;
		QImage mImage;

		GraphicsPixmapItem *mPaintPixmap;
		GraphicsPixmapItem *mPixmap;
		GraphicsPixmapItem *mGridPixmap;

		GraphicsView *mGraphicsView;
		GraphicsScene *mGraphicsScene;
		PainterSettings mSettings;
};
