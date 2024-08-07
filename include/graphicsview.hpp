#pragma once

#include <QGraphicsView>
#include <QObject>

class PainterSettings;

class GraphicsView : public QGraphicsView
{
	Q_OBJECT
	public:
		void setPainterSettings(PainterSettings * painterSettings);

	protected:
		void mouseMoveEvent(QMouseEvent *event) override;
		void paintEvent(QPaintEvent *event) override;
	private:
		PainterSettings * mSettings;
		qint32 mMode{0};
		qreal mScale{1.0};
		QPointF mPoint;
};