/********************************************************************************
** Form generated from reading UI file 'MandelJuliaLayerConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANDELJULIALAYERCONFIGURATIONDIALOG_H
#define UI_MANDELJULIALAYERCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MandelJuliaLayerConfigurationDialog
{
public:
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QDialog *MandelJuliaLayerConfigurationDialog)
    {
        if (MandelJuliaLayerConfigurationDialog->objectName().isEmpty())
            MandelJuliaLayerConfigurationDialog->setObjectName(QStringLiteral("MandelJuliaLayerConfigurationDialog"));
        MandelJuliaLayerConfigurationDialog->resize(400, 732);
        comboBox = new QComboBox(MandelJuliaLayerConfigurationDialog);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(40, 50, 151, 22));
        label = new QLabel(MandelJuliaLayerConfigurationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 55, 16));

        retranslateUi(MandelJuliaLayerConfigurationDialog);

        QMetaObject::connectSlotsByName(MandelJuliaLayerConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *MandelJuliaLayerConfigurationDialog)
    {
        MandelJuliaLayerConfigurationDialog->setWindowTitle(QApplication::translate("MandelJuliaLayerConfigurationDialog", "MandelJuliaLayerConfigurationDialog", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Normal", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Triangle inequality", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Average curvature 1", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Average curvature 2", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Average curvature 3", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Stripe average", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Fold line", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Fold square", Q_NULLPTR)
         << QApplication::translate("MandelJuliaLayerConfigurationDialog", "Fold circle", Q_NULLPTR)
        );
        label->setText(QApplication::translate("MandelJuliaLayerConfigurationDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MandelJuliaLayerConfigurationDialog: public Ui_MandelJuliaLayerConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELJULIALAYERCONFIGURATIONDIALOG_H
