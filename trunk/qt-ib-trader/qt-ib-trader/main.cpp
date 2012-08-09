#include "ibmainwindow.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IbMainWindow w;
	w.show();
	return a.exec();
}
