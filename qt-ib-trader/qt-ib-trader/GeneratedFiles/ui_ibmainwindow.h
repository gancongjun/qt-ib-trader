/********************************************************************************
** Form generated from reading UI file 'ibmainwindow.ui'
**
** Created: Thu Aug 9 06:10:39 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IBMAINWINDOW_H
#define UI_IBMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IbMainWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IbMainWindowClass)
    {
        if (IbMainWindowClass->objectName().isEmpty())
            IbMainWindowClass->setObjectName(QString::fromUtf8("IbMainWindowClass"));
        IbMainWindowClass->resize(600, 400);
        menuBar = new QMenuBar(IbMainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        IbMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IbMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        IbMainWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(IbMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        IbMainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(IbMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        IbMainWindowClass->setStatusBar(statusBar);

        retranslateUi(IbMainWindowClass);

        QMetaObject::connectSlotsByName(IbMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *IbMainWindowClass)
    {
        IbMainWindowClass->setWindowTitle(QApplication::translate("IbMainWindowClass", "IbMainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IbMainWindowClass: public Ui_IbMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IBMAINWINDOW_H
