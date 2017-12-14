/********************************************************************************
** Form generated from reading UI file 'Fractals.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTALS_H
#define UI_FRACTALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgetfractal.h"

QT_BEGIN_NAMESPACE

class Ui_FractalsClass
{
public:
    QAction *actionSave_image;
    QAction *actionExit;
    QAction *actionChoose_fractal;
    QAction *actionConfigure_fractal;
    QAction *actionZoomPlus;
    QAction *actionZoomMinus;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    WidgetFractal *myLabelImage;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FractalsClass)
    {
        if (FractalsClass->objectName().isEmpty())
            FractalsClass->setObjectName(QStringLiteral("FractalsClass"));
        FractalsClass->resize(600, 400);
        actionSave_image = new QAction(FractalsClass);
        actionSave_image->setObjectName(QStringLiteral("actionSave_image"));
        actionExit = new QAction(FractalsClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionChoose_fractal = new QAction(FractalsClass);
        actionChoose_fractal->setObjectName(QStringLiteral("actionChoose_fractal"));
        actionConfigure_fractal = new QAction(FractalsClass);
        actionConfigure_fractal->setObjectName(QStringLiteral("actionConfigure_fractal"));
        actionZoomPlus = new QAction(FractalsClass);
        actionZoomPlus->setObjectName(QStringLiteral("actionZoomPlus"));
        actionZoomMinus = new QAction(FractalsClass);
        actionZoomMinus->setObjectName(QStringLiteral("actionZoomMinus"));
        centralWidget = new QWidget(FractalsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 555, 278));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        myLabelImage = new WidgetFractal(scrollAreaWidgetContents);
        myLabelImage->setObjectName(QStringLiteral("myLabelImage"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myLabelImage->sizePolicy().hasHeightForWidth());
        myLabelImage->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(myLabelImage);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        FractalsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FractalsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        FractalsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FractalsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FractalsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FractalsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FractalsClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave_image);
        menuFile->addAction(actionExit);
        mainToolBar->addAction(actionChoose_fractal);
        mainToolBar->addAction(actionConfigure_fractal);
        mainToolBar->addAction(actionZoomPlus);
        mainToolBar->addAction(actionZoomMinus);

        retranslateUi(FractalsClass);

        QMetaObject::connectSlotsByName(FractalsClass);
    } // setupUi

    void retranslateUi(QMainWindow *FractalsClass)
    {
        FractalsClass->setWindowTitle(QApplication::translate("FractalsClass", "Fractals", Q_NULLPTR));
        actionSave_image->setText(QApplication::translate("FractalsClass", "Save image", Q_NULLPTR));
        actionExit->setText(QApplication::translate("FractalsClass", "Exit", Q_NULLPTR));
        actionChoose_fractal->setText(QApplication::translate("FractalsClass", "Choose fractal", Q_NULLPTR));
        actionConfigure_fractal->setText(QApplication::translate("FractalsClass", "Configure fractal", Q_NULLPTR));
        actionZoomPlus->setText(QApplication::translate("FractalsClass", "Zoom +", Q_NULLPTR));
        actionZoomMinus->setText(QApplication::translate("FractalsClass", "Zoom -", Q_NULLPTR));
        myLabelImage->setText(QApplication::translate("FractalsClass", "TextLabel", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("FractalsClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FractalsClass: public Ui_FractalsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTALS_H
