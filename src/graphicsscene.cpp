#include "graphicsscene.hpp"


#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

void GraphicsScene::setMode(uiMode mode)
{
	mMode = mode;
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
	if (mMode == uiMode::Paint && e->buttons() == Qt::LeftButton)
	{
		qreal xreal = e->scenePos().rx();
		qreal yreal = e->scenePos().ry();
		onPaintWhiteBoard(xreal, yreal);
	}
	if (mMode == uiMode::Paint && e->buttons() == Qt::RightButton)
	{
		qreal xreal = e->scenePos().rx();
		qreal yreal = e->scenePos().ry();
		onPaintWhiteBoardBackground(xreal, yreal);
	}
	else if (mMode == uiMode::SelectROI)
	{
		QGraphicsScene::mouseMoveEvent(e);
	}
	else if (mMode == uiMode::MoveSelect)
	{
		QGraphicsScene::mouseMoveEvent(e);
	}
}

void GraphicsScene::onPaintWhiteBoard(qreal x, qreal y)
{
	int rx = static_cast<int>(x);
	int ry = static_cast<int>(y);
	emit(paintWhiteBoard(rx, ry));
}

void GraphicsScene::onPaintWhiteBoardBackground(qreal x, qreal y)
{
	int rx = static_cast<int>(x);
	int ry = static_cast<int>(y);
	emit(paintWhiteBoardBackground(rx, ry));
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
	QGraphicsScene::mousePressEvent(e);
	if (mMode == uiMode::Paint && e->buttons() == Qt::LeftButton)
	{
        qreal xreal = e->scenePos().x();
		qreal yreal = e->scenePos().y();
		onPaintWhiteBoard(xreal, yreal);
		emit(updateView());
	}
	if (mMode == uiMode::Paint && e->buttons() == Qt::RightButton)
	{
        qreal xreal = e->scenePos().x();
		qreal yreal = e->scenePos().y();
		onPaintWhiteBoardBackground(xreal, yreal);
		emit(updateView());
	}
	else if (mMode == uiMode::SelectROI && e->buttons() == Qt::LeftButton)
	{
        qreal xreal = e->scenePos().rx()/10 * 10;
        qreal yreal = e->scenePos().ry()/10 * 10;

		mStartPoint = e->scenePos(); // Save start pos to save ROI on scene.
		isSelected = false;

		int x = static_cast<int>(xreal);
		int y = static_cast<int>(yreal);
		QPointF point = QPointF(x, y);
		e->setScenePos(point);
		QGraphicsScene::mousePressEvent(e);

	}
	if (mMode == uiMode::SelectROI && e->buttons() == Qt::MiddleButton)
	{
		isSelected = true;
	}
	else if (mMode == uiMode::MoveSelect && e->buttons() == Qt::LeftButton)
	{
		QGraphicsScene::mousePressEvent(e);
	}
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
	if (mMode == uiMode::Paint)
	{
	}
	else if (mMode == uiMode::SelectROI && !isSelected)
	{
		QPainterPath tmpPath = selectionArea();
		//setSelectionArea(QPainterPath());
		if (tmpPath.isEmpty())
		{
		}
		else
		{
			emit(addRectToScene(mStartPoint, e->scenePos(), true, ""));
			emit(updateView());
		}

		QGraphicsScene::mouseReleaseEvent(e);
	}
	else if (mMode == uiMode::MoveSelect)
	{
		QGraphicsScene::mouseReleaseEvent(e);
	}
}