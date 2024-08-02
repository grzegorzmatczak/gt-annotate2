#pragma once

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
		void setupView(QJsonObject const& a_config);
		void setupLayout();

	private:
		QMenu* m_fileMenu;
		QMenuBar* m_menuBar;
		//DataMemory* m_dataMemory;

	private:
		//View* m_view;

		//QThread* m_dlibThread;
		//DlibNetwork* m_dlib;
};
