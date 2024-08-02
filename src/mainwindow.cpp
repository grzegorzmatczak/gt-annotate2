#include "mainwindow.hpp"

#include <QtWidgets>


MainWindow::MainWindow()
{
	configure();
}


void MainWindow::configure() 
{
	createMenus();
	setupLayout();
	setupMainWidget();
}

void MainWindow::setupMainWidget() 
{
	#ifdef DEBUG
	Logger->debug("MainWindow::setupMainWidget()");
	#endif
	
	QGridLayout* mainLayout = new QGridLayout;
	//m_view->setMinimumWidth(1000);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	//mainLayout->addWidget(m_view, 0, 0);
	setLayout(mainLayout);

	resize(1600, 600);
}

void MainWindow::createMenus()
{}

void MainWindow::setupView(QJsonObject const& a_config)
{
	//m_view = new View(a_config, m_dataMemory);
	//m_view->setMinimumWidth(1000);
}

void MainWindow::setupLayout() 
{}
