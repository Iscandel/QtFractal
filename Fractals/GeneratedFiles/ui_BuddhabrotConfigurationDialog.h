/********************************************************************************
** Form generated from reading UI file 'BuddhabrotConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUDDHABROTCONFIGURATIONDIALOG_H
#define UI_BUDDHABROTCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuddhabrotConfigurationDialog
{
public:
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QDoubleSpinBox *mySpinXMin;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QDoubleSpinBox *mySpinXMax;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QDoubleSpinBox *mySpinYMin;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_8;
    QDoubleSpinBox *mySpinYMax;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QSpinBox *mySpinSizeX;
    QWidget *verticalLayoutWidget_7;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QSpinBox *mySpinSizeY;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_2;
    QSpinBox *mySpinIterationsRed;
    QWidget *verticalLayoutWidget_10;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_9;
    QSpinBox *mySpinIterationsGreen;
    QWidget *verticalLayoutWidget_11;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_10;
    QSpinBox *mySpinIterationsBlue;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QDoubleSpinBox *mySpinLightIntensity;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;

    void setupUi(QWidget *BuddhabrotConfigurationDialog)
    {
        if (BuddhabrotConfigurationDialog->objectName().isEmpty())
            BuddhabrotConfigurationDialog->setObjectName(QStringLiteral("BuddhabrotConfigurationDialog"));
        BuddhabrotConfigurationDialog->resize(319, 552);
        groupBox = new QGroupBox(BuddhabrotConfigurationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 291, 171));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 271, 103));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        mySpinXMin = new QDoubleSpinBox(gridLayoutWidget);
        mySpinXMin->setObjectName(QStringLiteral("mySpinXMin"));
        mySpinXMin->setMinimum(-1000);
        mySpinXMin->setMaximum(1000);
        mySpinXMin->setValue(-2);

        verticalLayout_3->addWidget(mySpinXMin);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        mySpinXMax = new QDoubleSpinBox(gridLayoutWidget);
        mySpinXMax->setObjectName(QStringLiteral("mySpinXMax"));
        mySpinXMax->setMinimum(-1000);
        mySpinXMax->setMaximum(1000);

        verticalLayout->addWidget(mySpinXMax);


        verticalLayout_3->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_4->addWidget(label_6);

        mySpinYMin = new QDoubleSpinBox(gridLayoutWidget);
        mySpinYMin->setObjectName(QStringLiteral("mySpinYMin"));
        mySpinYMin->setMinimum(-1000);
        mySpinYMin->setMaximum(1000);
        mySpinYMin->setValue(-2);

        verticalLayout_4->addWidget(mySpinYMin);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_2->addWidget(label_8);

        mySpinYMax = new QDoubleSpinBox(gridLayoutWidget);
        mySpinYMax->setObjectName(QStringLiteral("mySpinYMax"));
        mySpinYMax->setMinimum(-1000);
        mySpinYMax->setMaximum(1000);
        mySpinYMax->setValue(2);

        verticalLayout_2->addWidget(mySpinYMax);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(BuddhabrotConfigurationDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 190, 291, 80));
        verticalLayoutWidget_6 = new QWidget(groupBox_2);
        verticalLayoutWidget_6->setObjectName(QStringLiteral("verticalLayoutWidget_6"));
        verticalLayoutWidget_6->setGeometry(QRect(10, 20, 81, 51));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_6->addWidget(label_3);

        mySpinSizeX = new QSpinBox(verticalLayoutWidget_6);
        mySpinSizeX->setObjectName(QStringLiteral("mySpinSizeX"));
        mySpinSizeX->setMaximum(20000);
        mySpinSizeX->setValue(800);

        verticalLayout_6->addWidget(mySpinSizeX);

        verticalLayoutWidget_7 = new QWidget(groupBox_2);
        verticalLayoutWidget_7->setObjectName(QStringLiteral("verticalLayoutWidget_7"));
        verticalLayoutWidget_7->setGeometry(QRect(140, 20, 81, 51));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_7);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(verticalLayoutWidget_7);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_7->addWidget(label_4);

        mySpinSizeY = new QSpinBox(verticalLayoutWidget_7);
        mySpinSizeY->setObjectName(QStringLiteral("mySpinSizeY"));
        mySpinSizeY->setMaximum(20000);
        mySpinSizeY->setValue(800);

        verticalLayout_7->addWidget(mySpinSizeY);

        groupBox_3 = new QGroupBox(BuddhabrotConfigurationDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 280, 291, 211));
        verticalLayoutWidget_9 = new QWidget(groupBox_3);
        verticalLayoutWidget_9->setObjectName(QStringLiteral("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(10, 20, 111, 51));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_9);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_9->addWidget(label_2);

        mySpinIterationsRed = new QSpinBox(verticalLayoutWidget_9);
        mySpinIterationsRed->setObjectName(QStringLiteral("mySpinIterationsRed"));
        mySpinIterationsRed->setMaximum(1000000);
        mySpinIterationsRed->setValue(50);

        verticalLayout_9->addWidget(mySpinIterationsRed);

        verticalLayoutWidget_10 = new QWidget(groupBox_3);
        verticalLayoutWidget_10->setObjectName(QStringLiteral("verticalLayoutWidget_10"));
        verticalLayoutWidget_10->setGeometry(QRect(160, 20, 111, 51));
        verticalLayout_10 = new QVBoxLayout(verticalLayoutWidget_10);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(verticalLayoutWidget_10);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_10->addWidget(label_9);

        mySpinIterationsGreen = new QSpinBox(verticalLayoutWidget_10);
        mySpinIterationsGreen->setObjectName(QStringLiteral("mySpinIterationsGreen"));
        mySpinIterationsGreen->setMaximum(1000000);
        mySpinIterationsGreen->setValue(50);

        verticalLayout_10->addWidget(mySpinIterationsGreen);

        verticalLayoutWidget_11 = new QWidget(groupBox_3);
        verticalLayoutWidget_11->setObjectName(QStringLiteral("verticalLayoutWidget_11"));
        verticalLayoutWidget_11->setGeometry(QRect(90, 90, 111, 51));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_11);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(verticalLayoutWidget_11);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_11->addWidget(label_10);

        mySpinIterationsBlue = new QSpinBox(verticalLayoutWidget_11);
        mySpinIterationsBlue->setObjectName(QStringLiteral("mySpinIterationsBlue"));
        mySpinIterationsBlue->setMaximum(1000000);
        mySpinIterationsBlue->setValue(50);

        verticalLayout_11->addWidget(mySpinIterationsBlue);

        verticalLayoutWidget = new QWidget(groupBox_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(90, 150, 111, 51));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_5->addWidget(label);

        mySpinLightIntensity = new QDoubleSpinBox(verticalLayoutWidget);
        mySpinLightIntensity->setObjectName(QStringLiteral("mySpinLightIntensity"));

        verticalLayout_5->addWidget(mySpinLightIntensity);

        horizontalLayoutWidget = new QWidget(BuddhabrotConfigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 500, 195, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        myButtonOk = new QPushButton(horizontalLayoutWidget);
        myButtonOk->setObjectName(QStringLiteral("myButtonOk"));

        horizontalLayout->addWidget(myButtonOk);

        myButtonCancel = new QPushButton(horizontalLayoutWidget);
        myButtonCancel->setObjectName(QStringLiteral("myButtonCancel"));

        horizontalLayout->addWidget(myButtonCancel);


        retranslateUi(BuddhabrotConfigurationDialog);

        QMetaObject::connectSlotsByName(BuddhabrotConfigurationDialog);
    } // setupUi

    void retranslateUi(QWidget *BuddhabrotConfigurationDialog)
    {
        BuddhabrotConfigurationDialog->setWindowTitle(QApplication::translate("BuddhabrotConfigurationDialog", "BuddhabrotConfigurationDialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("BuddhabrotConfigurationDialog", "Domain", Q_NULLPTR));
        label_5->setText(QApplication::translate("BuddhabrotConfigurationDialog", "X min", Q_NULLPTR));
        label_7->setText(QApplication::translate("BuddhabrotConfigurationDialog", "X max", Q_NULLPTR));
        label_6->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Y min", Q_NULLPTR));
        label_8->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Y max", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("BuddhabrotConfigurationDialog", "Image size", Q_NULLPTR));
        label_3->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Size X", Q_NULLPTR));
        label_4->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Size Y", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("BuddhabrotConfigurationDialog", "General", Q_NULLPTR));
        label_2->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Iterations red", Q_NULLPTR));
        label_9->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Iterations green", Q_NULLPTR));
        label_10->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Iterations blue", Q_NULLPTR));
        label->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Light intensity", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("BuddhabrotConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("BuddhabrotConfigurationDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuddhabrotConfigurationDialog: public Ui_BuddhabrotConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUDDHABROTCONFIGURATIONDIALOG_H
