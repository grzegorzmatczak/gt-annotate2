#include "graphicsview.hpp"

#include "paintersettings.hpp"

#include <QMouseEvent>

 void GraphicsView::setPainterSettings(PainterSettings * painterSettings)
 {
	mSettings = painterSettings;
 }

 void GraphicsView::paintEvent(QPaintEvent *event) 
{
	QGraphicsView::paintEvent(event);

	int pen_size = mSettings->m_penSize;
	qreal scale = mScale;
	QPen pen(mSettings->m_color, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

	QPainter painter_id(viewport());
	painter_id.setRenderHint(QPainter::Antialiasing, false);
	painter_id.setPen(pen);

	if (pen_size == 2)
	{
		QRectF rectangle(
						(mPoint.x()) - pen_size/2 * scale, 
						(mPoint.y()) - pen_size/2 * scale, 
						pen_size * scale, pen_size * scale);
		painter_id.drawRect(rectangle);
	}
	if (pen_size == 3)
	{
		QRectF rectangle(
						(mPoint.x()) - (pen_size+2)/2 * scale, 
						(mPoint.y()) - (pen_size+2)/2 * scale, 
						(pen_size+1) * scale, (pen_size+1) * scale);
		painter_id.drawRect(rectangle);
	}
	if (pen_size == 4)
	{
		QRectF rectangle(
						(mPoint.x()) - (pen_size+3)/2 * scale, 
						(mPoint.y()) - (pen_size+3)/2 * scale, 
						(pen_size+2) * scale, (pen_size+2) * scale);
		painter_id.drawRect(rectangle);
	}
	if (pen_size == 5)
	{
		QRectF rectangle(
						(mPoint.x()) - (pen_size+4)/2 * scale, 
						(mPoint.y()) - (pen_size+4)/2 * scale, 
						(pen_size+3) * scale, (pen_size+3) * scale);
		painter_id.drawRect(rectangle);
	}
	
	painter_id.end();
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	mPoint = event->pos();
	viewport()->repaint();
	QGraphicsView::mouseMoveEvent(event);
}