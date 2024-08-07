#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QPen>

enum uiMode
{
	None = 0,
	SelectROI = 1,
	Paint = 2,
	MoveSelect = 3
};

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT
	public:
		void setMode(uiMode mode);
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	private:
		void onPaintWhiteBoard(qreal x, qreal y);
		void onPaintWhiteBoardBackground(qreal x, qreal y);
	signals:
		void paintWhiteBoard(qint32 x, qint32 y);
		void paintWhiteBoardBackground(qint32 x, qint32 y);
		void updateView();
		void addRectToScene(QPointF startPoint, QPointF stopPoint, bool dialog, QString name);
	private:
		uiMode mMode;
		bool isSelected{false};
		QPointF mStartPoint;
		QPointF mStopPoint;
	

};