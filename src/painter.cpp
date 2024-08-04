#include "painter.hpp"
#include "rect.hpp"



Painter::Painter(GraphicsScene *graphicsScene, GraphicsView* graphicsView)
	: m_graphicsScene(graphicsScene)
	, m_graphicsView(graphicsView)
{
	QPixmap test;

	test.load("test.png");

	addImageToScene(test);
}

void Painter::addImageToScene(QPixmap image)
{
	m_pixmap = static_cast<GraphicsPixmapItem*>(m_graphicsScene->addPixmap(image));

	m_pixmap->setEnabled(true);
	m_pixmap->setVisible(true);
	m_pixmap->setOpacity(1.0);
	m_pixmap->setAcceptHoverEvents(true);
	m_pixmap->setAcceptTouchEvents(true);
	m_pixmap->setZValue(-2);
	m_pixmap->update();

	m_image = image.toImage();
	m_paintImage = image.toImage();

	for (int y = 0; y < m_paintImage.height(); y++)
	{
		for (int x = 0; x < m_paintImage.width(); x++)
		{
			m_paintImage.setPixelColor(x, y, QColor{ 255, 255, 255, 127 });
		}
	}
	
	QPixmap whiteBoardPixmap = QPixmap::fromImage(m_paintImage);
	m_paintPixmap = static_cast<GraphicsPixmapItem*>(m_graphicsScene->addPixmap(whiteBoardPixmap));
	m_paintPixmap->setEnabled(true);
	m_paintPixmap->setVisible(true);
	m_paintPixmap->setOpacity(0.5);
	m_paintPixmap->setAcceptHoverEvents(true);
	m_paintPixmap->setAcceptTouchEvents(true);
	m_paintPixmap->setZValue(-1);
	m_paintPixmap->update();

	emit(updateView());
}