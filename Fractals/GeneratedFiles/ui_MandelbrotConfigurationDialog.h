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
#include <QtWidgets/QLineEdit>
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
    QDoubleSpinBox *mySpinBailout;
    QLabel *label_10;
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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *myCheckBoxUseFunction;
    QLineEdit *myEditFunction;
    QComboBox *myComboComputationType;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *myCheckBoxUseAddEnd;
    QLineEdit *myEditAddEndFunction;
    QCheckBox *myCheckBoxLambertCorrection;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *myCheckBoxUseRerange;
    QLineEdit *myEditRerangeFunction;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_14;
    QCheckBox *myCheckBoxUseRerangeHeight;
    QLineEdit *myEditRerangeHeight;

    void setupUi(QDialog *MandelbrotConfigurationDialog)
    {
        if (MandelbrotConfigurationDialog->objectName().isEmpty())
            MandelbrotConfigurationDialog->setObjectName(QStringLiteral("MandelbrotConfigurationDialog"));
        MandelbrotConfigurationDialog->resize(378, 862);
        groupBox = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 341, 171));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 315, 103));
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
        mySpinXMin->setDecimals(15);
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
        mySpinXMax->setDecimals(15);
        mySpinXMax->setMinimum(-1000);
        mySpinXMax->setMaximum(1000);
        mySpinXMax->setValue(2);

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
        mySpinYMin->setDecimals(15);
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
        mySpinYMax->setDecimals(15);
        mySpinYMax->setMinimum(-1000);
        mySpinYMax->setMaximum(1000);
        mySpinYMax->setValue(2);

        verticalLayout_2->addWidget(mySpinYMax);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(MandelbrotConfigurationDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 190, 341, 80));
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
        groupBox_3->setGeometry(QRect(20, 280, 341, 131));
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

        mySpinBailout = new QDoubleSpinBox(groupBox_3);
        mySpinBailout->setObjectName(QStringLiteral("mySpinBailout"));
        mySpinBailout->setGeometry(QRect(60, 100, 211, 22));
        mySpinBailout->setMaximum(1e+20);
        mySpinBailout->setValue(128);
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(110, 80, 55, 16));
        horizontalLayoutWidget = new QWidget(MandelbrotConfigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(70, 510, 195, 41));
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
        groupBox_4->setGeometry(QRect(20, 410, 341, 80));
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

        verticalLayoutWidget = new QWidget(MandelbrotConfigurationDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 600, 160, 51));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        myCheckBoxUseFunction = new QCheckBox(verticalLayoutWidget);
        myCheckBoxUseFunction->setObjectName(QStringLiteral("myCheckBoxUseFunction"));

        verticalLayout_11->addWidget(myCheckBoxUseFunction);

        myEditFunction = new QLineEdit(verticalLayoutWidget);
        myEditFunction->setObjectName(QStringLiteral("myEditFunction"));

        verticalLayout_11->addWidget(myEditFunction);

        myComboComputationType = new QComboBox(MandelbrotConfigurationDialog);
        myComboComputationType->setObjectName(QStringLiteral("myComboComputationType"));
        myComboComputationType->setGeometry(QRect(200, 610, 151, 22));
        verticalLayoutWidget_2 = new QWidget(MandelbrotConfigurationDialog);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(110, 670, 197, 51));
        verticalLayout_12 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        myCheckBoxUseAddEnd = new QCheckBox(verticalLayoutWidget_2);
        myCheckBoxUseAddEnd->setObjectName(QStringLiteral("myCheckBoxUseAddEnd"));

        verticalLayout_12->addWidget(myCheckBoxUseAddEnd);

        myEditAddEndFunction = new QLineEdit(verticalLayoutWidget_2);
        myEditAddEndFunction->setObjectName(QStringLiteral("myEditAddEndFunction"));

        verticalLayout_12->addWidget(myEditAddEndFunction);

        myCheckBoxLambertCorrection = new QCheckBox(MandelbrotConfigurationDialog);
        myCheckBoxLambertCorrection->setObjectName(QStringLiteral("myCheckBoxLambertCorrection"));
        myCheckBoxLambertCorrection->setGeometry(QRect(180, 560, 141, 20));
        verticalLayoutWidget_3 = new QWidget(MandelbrotConfigurationDialog);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(80, 740, 221, 51));
        verticalLayout_13 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        myCheckBoxUseRerange = new QCheckBox(verticalLayoutWidget_3);
        myCheckBoxUseRerange->setObjectName(QStringLiteral("myCheckBoxUseRerange"));

        verticalLayout_13->addWidget(myCheckBoxUseRerange);

        myEditRerangeFunction = new QLineEdit(verticalLayoutWidget_3);
        myEditRerangeFunction->setObjectName(QStringLiteral("myEditRerangeFunction"));

        verticalLayout_13->addWidget(myEditRerangeFunction);

        verticalLayoutWidget_4 = new QWidget(MandelbrotConfigurationDialog);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(80, 800, 221, 51));
        verticalLayout_14 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        myCheckBoxUseRerangeHeight = new QCheckBox(verticalLayoutWidget_4);
        myCheckBoxUseRerangeHeight->setObjectName(QStringLiteral("myCheckBoxUseRerangeHeight"));

        verticalLayout_14->addWidget(myCheckBoxUseRerangeHeight);

        myEditRerangeHeight = new QLineEdit(verticalLayoutWidget_4);
        myEditRerangeHeight->setObjectName(QStringLiteral("myEditRerangeHeight"));

        verticalLayout_14->addWidget(myEditRerangeHeight);


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
        label_10->setText(QApplication::translate("MandelbrotConfigurationDialog", "Bailout", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MandelbrotConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MandelbrotConfigurationDialog", "Cancel", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MandelbrotConfigurationDialog", "Renderer", Q_NULLPTR));
        label_9->setText(QApplication::translate("MandelbrotConfigurationDialog", "Renderer", Q_NULLPTR));
        myComboRenderer->clear();
        myComboRenderer->insertItems(0, QStringList()
         << QApplication::translate("MandelbrotConfigurationDialog", "Black & white", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Random", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Random 2", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Sine", Q_NULLPTR)
        );
        label->setText(QString());
        myButtonConfigureRenderer->setText(QApplication::translate("MandelbrotConfigurationDialog", "Configure", Q_NULLPTR));
        myCheckBoxUseFunction->setText(QApplication::translate("MandelbrotConfigurationDialog", "Function", Q_NULLPTR));
        myComboComputationType->clear();
        myComboComputationType->insertItems(0, QStringList()
         << QApplication::translate("MandelbrotConfigurationDialog", "Normal", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Triangle inequality", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Average curvature 1", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Average curvature 2", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Average curvature 3", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Stripe average", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Fold line", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Fold square", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Fold circle", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Exp smoothing", Q_NULLPTR)
         << QApplication::translate("MandelbrotConfigurationDialog", "Z smoothing", Q_NULLPTR)
        );
        myCheckBoxUseAddEnd->setText(QApplication::translate("MandelbrotConfigurationDialog", "Function (addEnd, branching)", Q_NULLPTR));
        myCheckBoxLambertCorrection->setText(QApplication::translate("MandelbrotConfigurationDialog", "Lambert correction", Q_NULLPTR));
        myCheckBoxUseRerange->setText(QApplication::translate("MandelbrotConfigurationDialog", "Re-range value function ", Q_NULLPTR));
        myCheckBoxUseRerangeHeight->setText(QApplication::translate("MandelbrotConfigurationDialog", "Re-range 3D height", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MandelbrotConfigurationDialog: public Ui_MandelbrotConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELBROTCONFIGURATIONDIALOG_H
