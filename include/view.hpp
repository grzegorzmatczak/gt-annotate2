#pragma once

#include <QtWidgets>
#include <QHash>
#include <QJsonObject>

#include "graphicsscene.hpp"
#include "graphicsview.hpp"
#include "toolbar.hpp"
#include "painter.hpp"

#include "logger.hpp"
#include "mainlogger.hpp"
#include "colorpicker.hpp"
#include "pensizepicker.hpp"

class Painter;

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
	
	private slots:
		void onSetPaint();
		void onSetMove();
		void onSetROI();

	private:
		GraphicsView *mGraphicsView;
		GraphicsScene *mGraphicsScene;
		ToolBar* mLeftToolBar;
		ToolBar* mBottomToolBar;

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
		QMenu* mFileMenu;
		QMenuBar* mMenuBar;
	
	private: //Layout
		QGridLayout *mVLayout;
		QGridLayout *mHLayout;

	private:
		qreal m_scaleOpacity;
		qreal m_scaleOpacityROI;
		qreal m_scaleOpacityImage;
		qreal m_scale;

	private:
		Painter* mPainter;
		ColorPicker* mColorPicker;
		PenSizePicker* mPenSizePicker;
	
	private:
		std::unique_ptr<Logger> mLogger;

};