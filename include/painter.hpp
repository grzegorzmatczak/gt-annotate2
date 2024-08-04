#pragma once

#include <QtWidgets>
#include <QHash>
#include <QObject>

#include "graphicsscene.hpp"
#include "graphicsview.hpp"

#include "graphicspixmapitem.hpp"
#include "graphicsrectitem.hpp"

//#include "labeldialog.hpp"
//#include "imageprocessing/contour.hpp"



class Painter : public QObject
{	
	Q_OBJECT
	public:
		Painter(GraphicsScene *graphicsScene, GraphicsView* graphicsView);

		QImage m_paintImage;
		QImage m_gridImage;
		QImage m_image;

		GraphicsPixmapItem *m_paintPixmap;
		GraphicsPixmapItem *m_pixmap;
		GraphicsPixmapItem *m_gridPixmap;

	private:
		void addImageToScene(QPixmap image);

};
