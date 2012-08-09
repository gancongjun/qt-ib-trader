#ifndef IBMAINWINDOW_H
#define IBMAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_ibmainwindow.h"

class IbMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	IbMainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~IbMainWindow();

private:
	Ui::IbMainWindowClass ui;
};

#endif // IBMAINWINDOW_H
