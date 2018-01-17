/********************************************************************************
** Form generated from reading UI file 'MandelbrotConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANDELBROTCONFIGURATIONDIALOG_H
#define UI_MANDELBROTCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
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

class Ui_MandelbrotConfigurationDialog
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
    QSpinBox *mySpinIterations;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *myCheckBoxLogLog;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_9;
    QComboBox *myComboRenderer;
    QVBoxLayout *verticalLayout_10;
    QLabel *label;
    QPushButton *myButtonConfigureRenderer;

    void setupUi(QDialog *MandelbrotConfigurationDialog)
    {
        if (MandelbrotConfigurationDialog->objectName().isEmpty())
            MandelbrotConfigurationDialog->setObjectName(QStringLiteral("MandelbrotConfigurationDialog"));
        MandelbrotConfigurationDialog->resize(346, 546);
        groupBox = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 291, 171));
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

        groupBox_2 = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 190, 291, 80));
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

        groupBox_3 = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 280, 291, 80));
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

        mySpinIterations = new QSpinBox(verticalLayoutWidget_9);
        mySpinIterations->setObjectName(QStringLiteral("mySpinIterations"));
        mySpinIterations->setMaximum(10000);
        mySpinIterations->setValue(50);

        verticalLayout_9->addWidget(mySpinIterations);

        verticalLayoutWidget_5 = new QWidget(groupBox_3);
        verticalLayoutWidget_5->setObjectName(QStringLiteral("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(150, 20, 133, 51));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        myCheckBoxLogLog = new QCheckBox(verticalLayoutWidget_5);
        myCheckBoxLogLog->setObjectName(QStringLiteral("myCheckBoxLogLog"));

        verticalLayout_5->addWidget(myCheckBoxLogLog);

        horizontalLayoutWidget = new QWidget(MandelbrotConfigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(70, 470, 195, 41));
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

        groupBox_4 = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 370, 291, 80));
        horizontalLayoutWidget_2 = new QWidget(groupBox_4);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 271, 55));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_9 = new QLabel(horizontalLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_8->addWidget(label_9);

        myComboRenderer = new QComboBox(horizontalLayoutWidget_2);
        myComboRenderer->setObjectName(QStringLiteral("myComboRenderer"));

        verticalLayout_8->addWidget(myComboRenderer);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_10->addWidget(label);

        myButtonConfigureRenderer = new QPushButton(horizontalLayoutWidget_2);
        myButtonConfigureRenderer->setObjectName(QStringLiteral("myButtonConfigureRenderer"));

        verticalLayout_10->addWidget(myButtonConfigureRenderer);


        horizontalLayout_2->addLayout(verticalLayout_10);


        retranslateUi(MandelbrotConfigurationDialog);

        QMetaObject::connectSlotsByName(MandelbrotConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *MandelbrotConfigurationDialog)
    {
        MandelbrotConfigurationDialog->setWindowTitle(QApplication::translate("MandelbrotConfigurationDialog", "MandelJuliaConfigurationDialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MandelbrotConfigurationDialog", "Domain", Q_NULLPTR));
        label_5->setText(QApplication::translate("MandelbrotConfigurationDialog", "X min", Q_NULLPTR));
        label_7->setText(QApplication::translate("MandelbrotConfigurationDialog", "X max", Q_NULLPTR));
        label_6->setText(QApplication::translate("MandelbrotConfigurationDialog", "Y min", Q_NULLPTR));
        label_8->setText(QApplication::translate("MandelbrotConfigurationDialog", "Y max", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MandelbrotConfigurationDialog", "Image size", Q_NULLPTR));
        label_3->setText(QApplication::translate("MandelbrotConfigurationDialog", "Size X", Q_NULLPTR));
        label_4->setText(QApplication::translate("MandelbrotConfigurationDialog", "Size Y", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MandelbrotConfigurationDialog", "General", Q_NULLPTR));
        label_2->setText(QApplication::translate("MandelbrotConfigurationDialog", "Iterations", Q_NULLPTR));
        myCheckBoxLogLog->setText(QApplication::translate("MandelbrotConfigurationDialog", "Log log smoothing", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MandelbrotConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MandelbrotConfigurationDialog", "Cancel", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MandelbrotConfigurationDialog", "Renderer", Q_NULLPTR));
        label_9->setText(QApplication::translate("MandelbrotConfigurationDialog", "Renderer", Q_NULLPTR));
        myComboRenderer->clear();
        myComboRenderer->insertItems(0, QStringList()
         << QApplication::translate("MandelbrotConfigurationDialog", "Black & white", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Predefined", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Random", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Sine", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "3D", Q_NULLPTR)
        );
        label->setText(QString());
        myButtonConfigureRenderer->setText(QApplication::translate("MandelbrotConfigurationDialog", "Configure", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MandelbrotConfigurationDialog: public Ui_MandelbrotConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELBROTCONFIGURATIONDIALOG_H
