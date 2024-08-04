#pragma once

#include <QtWidgets>
#include <QHash>

#include "graphicsscene.hpp"
#include "graphicsview.hpp"
#include "toolbar.hpp"
#include "painter.hpp"


class View : public QFrame
{
	Q_OBJECT
	
	public:
		View(QFrame *parent = nullptr);
		QGraphicsView *view() const;
		void configure();

	private:
		void setupGraphicsView();
		void setupCentralWidget();
		void createMenus();
		void creteAction();
		void setupLeftToolBar();
		
	private:
		GraphicsView *m_graphicsView;
		GraphicsScene *m_graphicsScene;
		ToolBar* m_leftToolBar;
		ToolBar* m_bottomToolBar;

	private:
		QAction* action_paint;
		QAction* action_move;
		QAction* action_ROI;
		QAction* action_loadDirectory;
		QAction* action_saveWhitePixmap;
		QAction* action_create_roi;
		QAction* action_nextImage;
		QAction* action_prevImage;
		QAction* action_copyNextImage;
		QAction* action_copyPrevImage;
		QAction* action_train_network;
		QAction* action_useNetwork;

	private:
		QMenu* m_fileMenu;
		QMenuBar* m_menuBar;
	
	private: //Layout
		QGridLayout *m_vLayout;
		QGridLayout *m_hLayout;

	private:
		qreal m_scaleOpacity;
		qreal m_scaleOpacityROI;
		qreal m_scaleOpacityImage;
		qreal m_scale;

	private:
		Painter* m_painter;

};