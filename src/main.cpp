#include <QApplication>

#include "mainwindow.hpp"

#include "logger.hpp"
#include "mainlogger.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	qRegisterMetaType<QString>("QString");

    QString log{"log.log"};
	QString logd{"logd.log"};
	MainLogger::start(log, logd);

	MainWindow window{};
	window.show();
	return app.exec();
}