/********************************************************************************
** Form generated from reading UI file 'MitchellNetravaliFilterConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MITCHELLNETRAVALIFILTERCONFIGURATIONDIALOG_H
#define UI_MITCHELLNETRAVALIFILTERCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MitchellNetravaliFilterConfigurationDialog
{
public:
    QDoubleSpinBox *mySpinRadiusX;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QDoubleSpinBox *mySpinRadiusY;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *mySpinB;
    QDoubleSpinBox *mySpinC;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *MitchellNetravaliFilterConfigurationDialog)
    {
        if (MitchellNetravaliFilterConfigurationDialog->objectName().isEmpty())
            MitchellNetravaliFilterConfigurationDialog->setObjectName(QStringLiteral("MitchellNetravaliFilterConfigurationDialog"));
        MitchellNetravaliFilterConfigurationDialog->resize(229, 171);
        mySpinRadiusX = new QDoubleSpinBox(MitchellNetravaliFilterConfigurationDialog);
        mySpinRadiusX->setObjectName(QStringLiteral("mySpinRadiusX"));
        mySpinRadiusX->setGeometry(QRect(30, 30, 81, 22));
        mySpinRadiusX->setValue(2);
        horizontalLayoutWidget = new QWidget(MitchellNetravaliFilterConfigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 130, 195, 31));
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

        mySpinRadiusY = new QDoubleSpinBox(MitchellNetravaliFilterConfigurationDialog);
        mySpinRadiusY->setObjectName(QStringLiteral("mySpinRadiusY"));
        mySpinRadiusY->setGeometry(QRect(130, 30, 81, 22));
        mySpinRadiusY->setValue(2);
        label = new QLabel(MitchellNetravaliFilterConfigurationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 55, 16));
        label_2 = new QLabel(MitchellNetravaliFilterConfigurationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 10, 55, 16));
        mySpinB = new QDoubleSpinBox(MitchellNetravaliFilterConfigurationDialog);
        mySpinB->setObjectName(QStringLiteral("mySpinB"));
        mySpinB->setGeometry(QRect(30, 90, 81, 22));
        mySpinB->setValue(0.33);
        mySpinC = new QDoubleSpinBox(MitchellNetravaliFilterConfigurationDialog);
        mySpinC->setObjectName(QStringLiteral("mySpinC"));
        mySpinC->setGeometry(QRect(130, 90, 81, 22));
        mySpinC->setValue(0.33);
        label_3 = new QLabel(MitchellNetravaliFilterConfigurationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 70, 55, 16));
        label_4 = new QLabel(MitchellNetravaliFilterConfigurationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 70, 55, 16));

        retranslateUi(MitchellNetravaliFilterConfigurationDialog);

        QMetaObject::connectSlotsByName(MitchellNetravaliFilterConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *MitchellNetravaliFilterConfigurationDialog)
    {
        MitchellNetravaliFilterConfigurationDialog->setWindowTitle(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "MitchellNetravaliFilterConfigurationDialog", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "Radius X", Q_NULLPTR));
        label_2->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "Radius Y", Q_NULLPTR));
        label_3->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "Param B", Q_NULLPTR));
        label_4->setText(QApplication::translate("MitchellNetravaliFilterConfigurationDialog", "Param C", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MitchellNetravaliFilterConfigurationDialog: public Ui_MitchellNetravaliFilterConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MITCHELLNETRAVALIFILTERCONFIGURATIONDIALOG_H
