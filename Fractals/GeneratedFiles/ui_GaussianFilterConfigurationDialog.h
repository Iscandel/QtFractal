/********************************************************************************
** Form generated from reading UI file 'GaussianFilterConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAUSSIANFILTERCONFIGURATIONDIALOG_H
#define UI_GAUSSIANFILTERCONFIGURATIONDIALOG_H

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

class Ui_GaussianFilterConfigurationDialog
{
public:
    QDoubleSpinBox *mySpinW;
    QDoubleSpinBox *mySpinRadiusY;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QDoubleSpinBox *mySpinRadiusX;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *mySpinA;

    void setupUi(QDialog *GaussianFilterConfigurationDialog)
    {
        if (GaussianFilterConfigurationDialog->objectName().isEmpty())
            GaussianFilterConfigurationDialog->setObjectName(QStringLiteral("GaussianFilterConfigurationDialog"));
        GaussianFilterConfigurationDialog->resize(223, 171);
        mySpinW = new QDoubleSpinBox(GaussianFilterConfigurationDialog);
        mySpinW->setObjectName(QStringLiteral("mySpinW"));
        mySpinW->setGeometry(QRect(130, 90, 81, 22));
        mySpinW->setValue(5);
        mySpinRadiusY = new QDoubleSpinBox(GaussianFilterConfigurationDialog);
        mySpinRadiusY->setObjectName(QStringLiteral("mySpinRadiusY"));
        mySpinRadiusY->setGeometry(QRect(130, 30, 81, 22));
        mySpinRadiusY->setValue(2);
        label_3 = new QLabel(GaussianFilterConfigurationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 70, 55, 16));
        label_4 = new QLabel(GaussianFilterConfigurationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 70, 55, 16));
        horizontalLayoutWidget = new QWidget(GaussianFilterConfigurationDialog);
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

        mySpinRadiusX = new QDoubleSpinBox(GaussianFilterConfigurationDialog);
        mySpinRadiusX->setObjectName(QStringLiteral("mySpinRadiusX"));
        mySpinRadiusX->setGeometry(QRect(30, 30, 81, 22));
        mySpinRadiusX->setValue(2);
        label = new QLabel(GaussianFilterConfigurationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 55, 16));
        label_2 = new QLabel(GaussianFilterConfigurationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 10, 55, 16));
        mySpinA = new QDoubleSpinBox(GaussianFilterConfigurationDialog);
        mySpinA->setObjectName(QStringLiteral("mySpinA"));
        mySpinA->setGeometry(QRect(30, 90, 81, 22));
        mySpinA->setValue(2);

        retranslateUi(GaussianFilterConfigurationDialog);

        QMetaObject::connectSlotsByName(GaussianFilterConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *GaussianFilterConfigurationDialog)
    {
        GaussianFilterConfigurationDialog->setWindowTitle(QApplication::translate("GaussianFilterConfigurationDialog", "GaussianFilterConfigurationDialog", Q_NULLPTR));
        label_3->setText(QApplication::translate("GaussianFilterConfigurationDialog", "Param a", Q_NULLPTR));
        label_4->setText(QApplication::translate("GaussianFilterConfigurationDialog", "Param w", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("GaussianFilterConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("GaussianFilterConfigurationDialog", "Cancel", Q_NULLPTR));
        label->setText(QApplication::translate("GaussianFilterConfigurationDialog", "Radius X", Q_NULLPTR));
        label_2->setText(QApplication::translate("GaussianFilterConfigurationDialog", "Radius Y", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GaussianFilterConfigurationDialog: public Ui_GaussianFilterConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAUSSIANFILTERCONFIGURATIONDIALOG_H
