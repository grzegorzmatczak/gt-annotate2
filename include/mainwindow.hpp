#pragma once

#include "view.hpp"

#include <QtWidgets>



class MainWindow : public QWidget
{
	Q_OBJECT

	public:
		MainWindow();

	private:
		void configure();
		void setupMainWidget();
		void createMenus();
		void setupView();
		void setupLayout();

	private:
		QMenu* m_fileMenu;
		QMenuBar* m_menuBar;
		View* m_view;

};
