#include <QApplication>

#include "mainwindow.hpp"

#include "logger.hpp"
#include "mainlogger.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	qRegisterMetaType<QString>("QString");

    QString name1{"main.log"};
    QString name2{"mainD.log"};
    MainLogger::start(name1, name2);
    qDebug("[log] main");

	MainWindow window{};
	window.show();
	return app.exec();
}