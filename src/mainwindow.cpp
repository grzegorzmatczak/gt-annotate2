#include "mainwindow.hpp"

#include <QtWidgets>


MainWindow::MainWindow()
{
	configure();
}


void MainWindow::configure() 
{
	setupView();
	createMenus();
	setupLayout();
	setupMainWidget();
}

void MainWindow::setupMainWidget() 
{
	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(m_view, 0, 0);
	setLayout(mainLayout);
	resize(1600, 600);
}

void MainWindow::createMenus()
{}

void MainWindow::setupView()
{
	m_view = new View();
	m_view->setMinimumWidth(1000);
	m_view->configure();
}

void MainWindow::setupLayout() 
{}
