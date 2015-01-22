/********************************************************************************
** Form generated from reading UI file 'rebeditp10504.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef REBEDITP10504_H
#define REBEDITP10504_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RebEditClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RebEditClass)
    {
        if (RebEditClass->objectName().isEmpty())
            RebEditClass->setObjectName(QStringLiteral("RebEditClass"));
        RebEditClass->resize(600, 400);
        centralWidget = new QWidget(RebEditClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        RebEditClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RebEditClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        RebEditClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RebEditClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RebEditClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RebEditClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RebEditClass->setStatusBar(statusBar);

        retranslateUi(RebEditClass);

        QMetaObject::connectSlotsByName(RebEditClass);
    } // setupUi

    void retranslateUi(QMainWindow *RebEditClass)
    {
        RebEditClass->setWindowTitle(QApplication::translate("RebEditClass", "RebEdit", 0));
    } // retranslateUi

};

namespace Ui {
    class RebEditClass: public Ui_RebEditClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // REBEDITP10504_H
