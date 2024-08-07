#include "view.hpp"

#include "painter.hpp"


View::View(QFrame* parent)
	: QFrame(parent)
	, mGraphicsScene(new GraphicsScene())
	, mGraphicsView(new GraphicsView())
	, mPainter(new Painter(mGraphicsScene, mGraphicsView))
{
	setStyle(QStyleFactory::create("Fusion"));
	mLogger = std::make_unique<Logger>(LogType::VIEW, LogLevel::LOW, LogFunction::YES);
	mPainter->onChangePenSize(3);
}


void View::configure()
{
	mLogger->printStartFunction(__FUNCTION__);
	View::setupCentralWidget();
	connect(mGraphicsScene, &GraphicsScene::addRectToScene, mPainter, &Painter::onAddRectToScene);
	mLogger->printEndFunction(__FUNCTION__);
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

	mVLayout = new QGridLayout;
	mVLayout->addWidget(mLeftToolBar, 0, 0);
	mVLayout->addWidget(m_zoomSlider, 0, 1);
	mVLayout->addWidget(mGraphicsView, 0, 2);
	mVLayout->addWidget(m_opacitySlider, 0, 3);
	mVLayout->addWidget(m_opacitySliderImage, 0, 4);
	mVLayout->addWidget(m_dataWidget, 0, 5);

	mVLayout->addWidget(mBottomToolBar, 1, 2);
	mVLayout->addWidget(m_statusBar, 1, 0);
	m_progressBar->setMaximumWidth(600);
	mVLayout->addWidget(m_progressBar, 1, 5);


	mHLayout = new QGridLayout;
	mHLayout->addLayout(mVLayout, 0, 0);
	mHLayout->addLayout(m_vLayoutBars, 1, 0);
	setLayout(mHLayout);
	*/
	mVLayout = new QGridLayout;
	mVLayout->addWidget(mLeftToolBar, 0, 0);
	mVLayout->addWidget(mGraphicsView, 0, 2);
	mHLayout = new QGridLayout;
	mHLayout->addLayout(mVLayout, 0, 0);
	setLayout(mHLayout);
}

void View::setupGraphicsView()
{
	mLogger->printStartFunction(__FUNCTION__);

	mGraphicsView->setRenderHint(QPainter::Antialiasing, false);
	mGraphicsView->setDragMode(QGraphicsView::NoDrag);
	mGraphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	mGraphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	mGraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	mGraphicsView->setScene(mGraphicsScene);

	connect(mGraphicsScene, &GraphicsScene::paintWhiteBoard, mPainter, &Painter::onPaintOnBoard);
	connect(mGraphicsScene, &GraphicsScene::paintWhiteBoardBackground, mPainter, &Painter::onPaintBackground);
	//connect(mGraphicsView, &GraphicsView::zoomIn, this, &View::onZoomIn);
	//connect(mGraphicsView, &GraphicsView::zoomOut, this, &View::onZoomOut);
}

void View::createMenus()
{
	//mMenuBar = new QMenuBar(this);
	//mFileMenu = mMenuBar->addMenu(tr("&File"));
	//mFileMenu->addSeparator();
	//mFileMenu = mMenuBar->addMenu(tr("&Tool"));
}

void View::setupLeftToolBar() 
{
	
	View::creteAction();
	mLeftToolBar = new ToolBar();
	mLeftToolBar->setWindowFlag(Qt::FramelessWindowHint);
	mLeftToolBar->setOrientation(Qt::Vertical);
	//mLeftToolBar->addWidget(mMenuBar);
	//mLeftToolBar->addAction(action_loadDirectory);

	mColorPicker = new ColorPicker();
	connect(mColorPicker, &ColorPicker::changeColor, mPainter, &Painter::onChangeColor);
	mLeftToolBar->addWidget(mColorPicker);
	mLeftToolBar->addSeparator();

	mPenSizePicker = new PenSizePicker();
	mLeftToolBar->addWidget(mPenSizePicker);
	connect(mPenSizePicker, &PenSizePicker::changePenSize, mPainter, &Painter::onChangePenSize);

	mLeftToolBar->addSeparator();

	mLeftToolBar->addAction(action_paint);
	mLeftToolBar->addAction(action_move);
	mLeftToolBar->addAction(action_ROI);
	mLeftToolBar->addSeparator();
	mLeftToolBar->addAction(action_create_roi);
	mLeftToolBar->addAction(action_saveWhitePixmap);

	mLogger->printEndFunction(__FUNCTION__);
}

void View::creteAction()
{
	
	action_paint = new QAction(tr("&Paint"), this);
	action_paint->setToolTip("Painting");
	action_paint->setCheckable(true);
	action_paint->setEnabled(true);

	action_move = new QAction(tr("&Move"), this);
	action_move->setToolTip("Moving");
	action_move->setCheckable(true);
	action_move->setEnabled(true);

	action_ROI = new QAction(tr("&ROI"), this);
	action_ROI->setToolTip("select ROI");
	action_ROI->setCheckable(true);
	action_ROI->setEnabled(true);	

	connect(action_paint, &QAction::triggered, this, &View::onSetPaint);
	connect(action_move, &QAction::triggered, this, &View::onSetMove);
	connect(action_ROI, &QAction::triggered, this, &View::onSetROI);

	action_loadDirectory = new QAction(tr("&Load Directory"), this);
	action_loadDirectory->setStatusTip(tr("Load Directory"));
	action_loadDirectory->setToolTip("Load Directory");
	//connect(action_loadDirectory, &QAction::triggered, this, &View::onLoadDirectory);
	//connect(action_loadDirectory, &QAction::triggered, this, &View::onLoadDirectory);
	
	action_create_roi = new QAction(tr("&Create ROI"), this);
	action_create_roi->setToolTip("Create all roi on current images");
	//connect(action_create_roi, &QAction::triggered, mPainter, &Painter::onCreateRois);

	action_saveWhitePixmap = new QAction(tr("&Save objects"), this);
	action_saveWhitePixmap->setToolTip("Save all roi on current images");

	connect(action_saveWhitePixmap, &QAction::triggered, mPainter, &Painter::onSavePaint);

	/*
	connect(action_saveWhitePixmap, &QAction::triggered, mPainter, &Painter::onSaveRois);
	connect(action_saveWhitePixmap, &QAction::triggered, m_dataWidget, &DataWidget::open);
	connect(mPainter, &Painter::updateFileFromId, m_dataWidget, &DataWidget::onUpdateFileFromId );
	connect(mPainter, &Painter::updatStatus, m_dataWidget, &DataWidget::onUpdateStatus );
	connect(mPainter, &Painter::addRoi, m_dataWidget, &DataWidget::onAddRoi );
	connect(mPainter, &Painter::clearRoiWidget, m_dataWidget, &DataWidget::clearRoiWidget );
*/
	//connect(m_dataWidget->roiWidget, &RoiWidget::itemChanged, mPainter, &Painter::onRoiItemChanged);
	//connect(m_dataWidget->roiWidget, &RoiWidget::itemSelectionChanged, mPainter, &Painter::onRoiItemSelectionChanged);
	

	//action_train_network = new QAction(tr("&Train Network"), this);
	//action_train_network->setToolTip("Train Network");
	//connect(action_train_network, &QAction::triggered, this, &View::onTrainNetwork);

	//action_useNetwork = new QAction(tr("&Use Network"), this);
	//action_useNetwork->setToolTip("Use Network");
	//connect(action_useNetwork, &QAction::triggered, mPainter, &Painter::onUseNetwork);
	//connect(mPainter, &Painter::useNetwork, this, &View::onUseNetwork);
	
	
	//View::onSetPaint();
}

void View::onSetPaint()
{
	mLogger->printStartFunction(__FUNCTION__);

	action_paint->setChecked(true);
	action_move->setChecked(false);
	action_ROI->setChecked(false);
	mGraphicsView->setDragMode(QGraphicsView::NoDrag);
	mGraphicsScene->setMode(uiMode::Paint);
}

void View::onSetMove()
{
	mLogger->printStartFunction(__FUNCTION__);

	action_paint->setChecked(false);
	action_move->setChecked(true);
	action_ROI->setChecked(false);
	mGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
	mGraphicsScene->setMode(uiMode::MoveSelect);
}

void View::onSetROI()
{
	mLogger->printStartFunction(__FUNCTION__);

	action_move->setChecked(false);
	action_paint->setChecked(false);
	action_ROI->setChecked(true);
	mGraphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	mGraphicsScene->setMode(uiMode::SelectROI);
}