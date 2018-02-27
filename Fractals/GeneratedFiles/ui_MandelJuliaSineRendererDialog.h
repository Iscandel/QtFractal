/********************************************************************************
** Form generated from reading UI file 'MandelJuliaSineRendererDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANDELJULIASINERENDERERDIALOG_H
#define UI_MANDELJULIASINERENDERERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MandelJuliaSineRendererDialog
{
public:
    QGroupBox *groupBox;
    QRadioButton *myRadioPotential;
    QRadioButton *myRadioMode3D;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *mySpinAmplitudeR;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QDoubleSpinBox *mySpinAmplitudeG;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QDoubleSpinBox *mySpinAmplitudeB;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QDoubleSpinBox *mySpinPhaseR;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QDoubleSpinBox *mySpinPhaseG;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QDoubleSpinBox *mySpinPhaseB;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QDoubleSpinBox *mySpinPulsationR;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QDoubleSpinBox *mySpinPulsationG;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QDoubleSpinBox *mySpinPulsationB;
    QGroupBox *groupBox_5;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QScrollBar *myScrollBarBlue;
    QLabel *label_5;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QScrollBar *myScrollBarRed;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QScrollBar *myScrollBarGreen;
    QLabel *label_4;
    QLabel *myFractalPreview;

    void setupUi(QDialog *MandelJuliaSineRendererDialog)
    {
        if (MandelJuliaSineRendererDialog->objectName().isEmpty())
            MandelJuliaSineRendererDialog->setObjectName(QStringLiteral("MandelJuliaSineRendererDialog"));
        MandelJuliaSineRendererDialog->resize(604, 443);
        groupBox = new QGroupBox(MandelJuliaSineRendererDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 10, 501, 80));
        myRadioPotential = new QRadioButton(groupBox);
        myRadioPotential->setObjectName(QStringLiteral("myRadioPotential"));
        myRadioPotential->setGeometry(QRect(80, 30, 95, 20));
        myRadioPotential->setChecked(true);
        myRadioMode3D = new QRadioButton(groupBox);
        myRadioMode3D->setObjectName(QStringLiteral("myRadioMode3D"));
        myRadioMode3D->setGeometry(QRect(290, 30, 95, 20));
        horizontalLayoutWidget_2 = new QWidget(MandelJuliaSineRendererDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(200, 400, 195, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        myButtonOk = new QPushButton(horizontalLayoutWidget_2);
        myButtonOk->setObjectName(QStringLiteral("myButtonOk"));

        horizontalLayout_2->addWidget(myButtonOk);

        myButtonCancel = new QPushButton(horizontalLayoutWidget_2);
        myButtonCancel->setObjectName(QStringLiteral("myButtonCancel"));

        horizontalLayout_2->addWidget(myButtonCancel);

        groupBox_2 = new QGroupBox(MandelJuliaSineRendererDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 181, 121));
        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 160, 88));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        mySpinAmplitudeR = new QDoubleSpinBox(verticalLayoutWidget);
        mySpinAmplitudeR->setObjectName(QStringLiteral("mySpinAmplitudeR"));
        mySpinAmplitudeR->setDecimals(8);
        mySpinAmplitudeR->setMinimum(-1000);
        mySpinAmplitudeR->setMaximum(1000);
        mySpinAmplitudeR->setSingleStep(0.5);

        horizontalLayout->addWidget(mySpinAmplitudeR);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        mySpinAmplitudeG = new QDoubleSpinBox(verticalLayoutWidget);
        mySpinAmplitudeG->setObjectName(QStringLiteral("mySpinAmplitudeG"));
        mySpinAmplitudeG->setDecimals(8);
        mySpinAmplitudeG->setMinimum(-1000);
        mySpinAmplitudeG->setMaximum(1000);
        mySpinAmplitudeG->setSingleStep(0.5);

        horizontalLayout_6->addWidget(mySpinAmplitudeG);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 8);

        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        mySpinAmplitudeB = new QDoubleSpinBox(verticalLayoutWidget);
        mySpinAmplitudeB->setObjectName(QStringLiteral("mySpinAmplitudeB"));
        mySpinAmplitudeB->setDecimals(8);
        mySpinAmplitudeB->setMinimum(-1000);
        mySpinAmplitudeB->setMaximum(1000);
        mySpinAmplitudeB->setSingleStep(0.5);

        horizontalLayout_7->addWidget(mySpinAmplitudeB);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 8);

        verticalLayout->addLayout(horizontalLayout_7);

        groupBox_3 = new QGroupBox(MandelJuliaSineRendererDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(390, 100, 201, 121));
        verticalLayoutWidget_3 = new QWidget(groupBox_3);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 160, 88));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_10 = new QLabel(verticalLayoutWidget_3);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_11->addWidget(label_10);

        mySpinPhaseR = new QDoubleSpinBox(verticalLayoutWidget_3);
        mySpinPhaseR->setObjectName(QStringLiteral("mySpinPhaseR"));
        mySpinPhaseR->setDecimals(8);
        mySpinPhaseR->setMinimum(-1000);
        mySpinPhaseR->setMaximum(1000);
        mySpinPhaseR->setSingleStep(0.5);

        horizontalLayout_11->addWidget(mySpinPhaseR);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 8);

        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_11 = new QLabel(verticalLayoutWidget_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_12->addWidget(label_11);

        mySpinPhaseG = new QDoubleSpinBox(verticalLayoutWidget_3);
        mySpinPhaseG->setObjectName(QStringLiteral("mySpinPhaseG"));
        mySpinPhaseG->setDecimals(8);
        mySpinPhaseG->setMinimum(-1000);
        mySpinPhaseG->setMaximum(10000);
        mySpinPhaseG->setSingleStep(0.5);

        horizontalLayout_12->addWidget(mySpinPhaseG);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 8);

        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_12 = new QLabel(verticalLayoutWidget_3);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_13->addWidget(label_12);

        mySpinPhaseB = new QDoubleSpinBox(verticalLayoutWidget_3);
        mySpinPhaseB->setObjectName(QStringLiteral("mySpinPhaseB"));
        mySpinPhaseB->setDecimals(8);
        mySpinPhaseB->setMinimum(-1000);
        mySpinPhaseB->setMaximum(1000);
        mySpinPhaseB->setSingleStep(0.5);

        horizontalLayout_13->addWidget(mySpinPhaseB);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 8);

        verticalLayout_3->addLayout(horizontalLayout_13);

        groupBox_4 = new QGroupBox(MandelJuliaSineRendererDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(200, 100, 181, 121));
        verticalLayoutWidget_2 = new QWidget(groupBox_4);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 160, 88));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_8->addWidget(label_7);

        mySpinPulsationR = new QDoubleSpinBox(verticalLayoutWidget_2);
        mySpinPulsationR->setObjectName(QStringLiteral("mySpinPulsationR"));
        mySpinPulsationR->setDecimals(8);
        mySpinPulsationR->setMinimum(-1000);
        mySpinPulsationR->setMaximum(1000);
        mySpinPulsationR->setSingleStep(0.5);

        horizontalLayout_8->addWidget(mySpinPulsationR);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 8);

        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        mySpinPulsationG = new QDoubleSpinBox(verticalLayoutWidget_2);
        mySpinPulsationG->setObjectName(QStringLiteral("mySpinPulsationG"));
        mySpinPulsationG->setDecimals(8);
        mySpinPulsationG->setSingleStep(0.5);

        horizontalLayout_9->addWidget(mySpinPulsationG);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 8);

        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_9 = new QLabel(verticalLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_10->addWidget(label_9);

        mySpinPulsationB = new QDoubleSpinBox(verticalLayoutWidget_2);
        mySpinPulsationB->setObjectName(QStringLiteral("mySpinPulsationB"));
        mySpinPulsationB->setDecimals(8);
        mySpinPulsationB->setMinimum(-1000);
        mySpinPulsationB->setMaximum(1000);
        mySpinPulsationB->setSingleStep(0.5);

        horizontalLayout_10->addWidget(mySpinPulsationB);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 8);

        verticalLayout_2->addLayout(horizontalLayout_10);

        groupBox_5 = new QGroupBox(MandelJuliaSineRendererDialog);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(110, 240, 381, 141));
        horizontalLayoutWidget_5 = new QWidget(groupBox_5);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 100, 191, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        myScrollBarBlue = new QScrollBar(horizontalLayoutWidget_5);
        myScrollBarBlue->setObjectName(QStringLiteral("myScrollBarBlue"));
        myScrollBarBlue->setMaximum(255);
        myScrollBarBlue->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(myScrollBarBlue);

        label_5 = new QLabel(horizontalLayoutWidget_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalLayout_5->setStretch(0, 8);
        horizontalLayout_5->setStretch(1, 1);
        horizontalLayoutWidget_3 = new QWidget(groupBox_5);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 20, 191, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        myScrollBarRed = new QScrollBar(horizontalLayoutWidget_3);
        myScrollBarRed->setObjectName(QStringLiteral("myScrollBarRed"));
        myScrollBarRed->setMaximum(255);
        myScrollBarRed->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(myScrollBarRed);

        label_3 = new QLabel(horizontalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        horizontalLayout_3->setStretch(0, 8);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayoutWidget_4 = new QWidget(groupBox_5);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 60, 201, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        myScrollBarGreen = new QScrollBar(horizontalLayoutWidget_4);
        myScrollBarGreen->setObjectName(QStringLiteral("myScrollBarGreen"));
        myScrollBarGreen->setMaximum(255);
        myScrollBarGreen->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(myScrollBarGreen);

        label_4 = new QLabel(horizontalLayoutWidget_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        horizontalLayout_4->setStretch(0, 8);
        horizontalLayout_4->setStretch(1, 1);
        myFractalPreview = new QLabel(groupBox_5);
        myFractalPreview->setObjectName(QStringLiteral("myFractalPreview"));
        myFractalPreview->setGeometry(QRect(260, 20, 101, 101));

        retranslateUi(MandelJuliaSineRendererDialog);

        QMetaObject::connectSlotsByName(MandelJuliaSineRendererDialog);
    } // setupUi

    void retranslateUi(QDialog *MandelJuliaSineRendererDialog)
    {
        MandelJuliaSineRendererDialog->setWindowTitle(QApplication::translate("MandelJuliaSineRendererDialog", "MandelJuliaSineRendererDialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MandelJuliaSineRendererDialog", "Type", Q_NULLPTR));
        myRadioPotential->setText(QApplication::translate("MandelJuliaSineRendererDialog", "Potential", Q_NULLPTR));
        myRadioMode3D->setText(QApplication::translate("MandelJuliaSineRendererDialog", "3D", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MandelJuliaSineRendererDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MandelJuliaSineRendererDialog", "Cancel", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MandelJuliaSineRendererDialog", "Amplitudes", Q_NULLPTR));
        label->setText(QApplication::translate("MandelJuliaSineRendererDialog", "R", Q_NULLPTR));
        label_2->setText(QApplication::translate("MandelJuliaSineRendererDialog", "G", Q_NULLPTR));
        label_6->setText(QApplication::translate("MandelJuliaSineRendererDialog", "B", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MandelJuliaSineRendererDialog", "Phase", Q_NULLPTR));
        label_10->setText(QApplication::translate("MandelJuliaSineRendererDialog", "R", Q_NULLPTR));
        label_11->setText(QApplication::translate("MandelJuliaSineRendererDialog", "G", Q_NULLPTR));
        label_12->setText(QApplication::translate("MandelJuliaSineRendererDialog", "B", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MandelJuliaSineRendererDialog", "Pulsations", Q_NULLPTR));
        label_7->setText(QApplication::translate("MandelJuliaSineRendererDialog", "R", Q_NULLPTR));
        label_8->setText(QApplication::translate("MandelJuliaSineRendererDialog", "G", Q_NULLPTR));
        label_9->setText(QApplication::translate("MandelJuliaSineRendererDialog", "B", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MandelJuliaSineRendererDialog", "Fractal color", Q_NULLPTR));
        label_5->setText(QApplication::translate("MandelJuliaSineRendererDialog", "Blue", Q_NULLPTR));
        label_3->setText(QApplication::translate("MandelJuliaSineRendererDialog", "Red", Q_NULLPTR));
        label_4->setText(QApplication::translate("MandelJuliaSineRendererDialog", "Green", Q_NULLPTR));
        myFractalPreview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MandelJuliaSineRendererDialog: public Ui_MandelJuliaSineRendererDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELJULIASINERENDERERDIALOG_H
