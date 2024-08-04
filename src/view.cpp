#include "view.hpp"


View::View(QFrame* parent)
	: QFrame(parent)
	, m_graphicsScene(new GraphicsScene())
	, m_graphicsView(new GraphicsView())
{}


void View::configure()
{
	View::setupCentralWidget();
}


void View::setupCentralWidget()
{
	View::setupGraphicsView();
	View::createMenus();
	View::setupLeftToolBar();
	/*
	View::setupDataWidget();
	
	
	
	View::setupBottomToolBar();
	View::setupSliders();
	View::setupProgressBar();

	m_vLayout = new QGridLayout;
	m_vLayout->addWidget(m_leftToolBar, 0, 0);
	m_vLayout->addWidget(m_zoomSlider, 0, 1);
	m_vLayout->addWidget(m_graphicsView, 0, 2);
	m_vLayout->addWidget(m_opacitySlider, 0, 3);
	m_vLayout->addWidget(m_opacitySliderImage, 0, 4);
	m_vLayout->addWidget(m_dataWidget, 0, 5);

	m_vLayout->addWidget(m_bottomToolBar, 1, 2);
	m_vLayout->addWidget(m_statusBar, 1, 0);
	m_progressBar->setMaximumWidth(600);
	m_vLayout->addWidget(m_progressBar, 1, 5);


	m_hLayout = new QGridLayout;
	m_hLayout->addLayout(m_vLayout, 0, 0);
	m_hLayout->addLayout(m_vLayoutBars, 1, 0);
	setLayout(m_hLayout);
	*/
	m_vLayout = new QGridLayout;
	m_vLayout->addWidget(m_leftToolBar, 0, 0);
	m_vLayout->addWidget(m_graphicsView, 0, 2);
	m_hLayout = new QGridLayout;
	m_hLayout->addLayout(m_vLayout, 0, 0);
	setLayout(m_hLayout);
}

void View::setupGraphicsView()
{
	#ifdef DEBUG
	Logger->debug("View::setupGraphicsView()");
	#endif
	m_graphicsView->setRenderHint(QPainter::Antialiasing, false);
	m_graphicsView->setDragMode(QGraphicsView::NoDrag);
	m_graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	m_graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	m_graphicsView->setScene(m_graphicsScene);

	//connect(m_graphicsScene, &GraphicsScene::paintWhiteBoard, m_painter, &Painter::onPaintOnBoard);
	//connect(m_graphicsScene, &GraphicsScene::paintWhiteBoardBackground, m_painter, &Painter::onPaintBackground);
	//connect(m_graphicsView, &GraphicsView::zoomIn, this, &View::onZoomIn);
	//connect(m_graphicsView, &GraphicsView::zoomOut, this, &View::onZoomOut);
}

void View::createMenus()
{
	m_menuBar = new QMenuBar(this);
	m_fileMenu = m_menuBar->addMenu(tr("&File"));
	m_fileMenu->addSeparator();
	m_fileMenu = m_menuBar->addMenu(tr("&Tool"));
}

void View::setupLeftToolBar() 
{
	
	View::creteAction();
	m_leftToolBar = new ToolBar();
	m_leftToolBar->setWindowFlag(Qt::FramelessWindowHint);
	m_leftToolBar->setOrientation(Qt::Vertical);
	m_leftToolBar->addWidget(m_menuBar);
	//m_leftToolBar->addAction(action_loadDirectory);
	
}

void View::creteAction()
{
	/*
	action_paint = new QAction(tr("&Paint"), this);
	action_paint->setToolTip("Painting");
	action_paint->setCheckable(true);
	action_paint->setEnabled(true);

	action_move = new QAction(tr("&Move"), this);
	action_move->setToolTip("Moving");
	action_paint->setCheckable(true);

	action_ROI = new QAction(tr("&ROI"), this);
	action_ROI->setToolTip("select ROI");	

	connect(action_paint, &QAction::triggered, this, &View::onSetPaint);
	connect(action_move, &QAction::triggered, this, &View::onSetMove);
	connect(action_ROI, &QAction::triggered, this, &View::onSetROI);

	action_loadDirectory = new QAction(tr("&Load Directory"), this);
	action_loadDirectory->setStatusTip(tr("Load Directory"));
	action_loadDirectory->setToolTip("Load Directory");
	connect(action_loadDirectory, &QAction::triggered, this, &View::onLoadDirectory);
	connect(action_loadDirectory, &QAction::triggered, this, &View::onLoadDirectory);
	
	action_create_roi = new QAction(tr("&Create ROI"), this);
	action_create_roi->setToolTip("create all roi on current images");
	connect(action_create_roi, &QAction::triggered, m_painter, &Painter::onCreateRois);

	action_saveWhitePixmap = new QAction(tr("&Save objects"), this);
	action_saveWhitePixmap->setToolTip("Save all roi on current images");
	connect(action_saveWhitePixmap, &QAction::triggered, m_painter, &Painter::onSavePaint);
	connect(action_saveWhitePixmap, &QAction::triggered, m_painter, &Painter::onSaveRois);
	connect(action_saveWhitePixmap, &QAction::triggered, m_dataWidget, &DataWidget::open);
	connect(m_painter, &Painter::updateFileFromId, m_dataWidget, &DataWidget::onUpdateFileFromId );
	connect(m_painter, &Painter::updatStatus, m_dataWidget, &DataWidget::onUpdateStatus );
	connect(m_painter, &Painter::addRoi, m_dataWidget, &DataWidget::onAddRoi );
	connect(m_painter, &Painter::clearRoiWidget, m_dataWidget, &DataWidget::clearRoiWidget );

	connect(m_dataWidget->roiWidget, &RoiWidget::itemChanged, m_painter, &Painter::onRoiItemChanged);
	connect(m_dataWidget->roiWidget, &RoiWidget::itemSelectionChanged, m_painter, &Painter::onRoiItemSelectionChanged);
	

	action_train_network = new QAction(tr("&Train Network"), this);
	action_train_network->setToolTip("Train Network");
	connect(action_train_network, &QAction::triggered, this, &View::onTrainNetwork);

	action_useNetwork = new QAction(tr("&Use Network"), this);
	action_useNetwork->setToolTip("Use Network");
	connect(action_useNetwork, &QAction::triggered, m_painter, &Painter::onUseNetwork);
	connect(m_painter, &Painter::useNetwork, this, &View::onUseNetwork);
	
	
	View::onSetPaint();*/
}