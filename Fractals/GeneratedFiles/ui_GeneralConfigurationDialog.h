/********************************************************************************
** Form generated from reading UI file 'GeneralConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERALCONFIGURATIONDIALOG_H
#define UI_GENERALCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneralConfigurationDialog
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *myCheckboxUseFilter;
    QComboBox *myComboFilterType;
    QPushButton *myButtonConfigFilter;
    QGroupBox *groupBox_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *mySpinNbThreads;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QSpinBox *mySpinOversampling;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QSpinBox *mySpinBlockSize;

    void setupUi(QWidget *GeneralConfigurationDialog)
    {
        if (GeneralConfigurationDialog->objectName().isEmpty())
            GeneralConfigurationDialog->setObjectName(QStringLiteral("GeneralConfigurationDialog"));
        GeneralConfigurationDialog->resize(551, 282);
        horizontalLayoutWidget_2 = new QWidget(GeneralConfigurationDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(170, 240, 195, 31));
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

        groupBox = new QGroupBox(GeneralConfigurationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 130, 531, 91));
        groupBox->setAutoFillBackground(false);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayoutWidget_3 = new QWidget(groupBox);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 10, 511, 80));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        myCheckboxUseFilter = new QCheckBox(horizontalLayoutWidget_3);
        myCheckboxUseFilter->setObjectName(QStringLiteral("myCheckboxUseFilter"));

        horizontalLayout_3->addWidget(myCheckboxUseFilter);

        myComboFilterType = new QComboBox(horizontalLayoutWidget_3);
        myComboFilterType->setObjectName(QStringLiteral("myComboFilterType"));

        horizontalLayout_3->addWidget(myComboFilterType);

        myButtonConfigFilter = new QPushButton(horizontalLayoutWidget_3);
        myButtonConfigFilter->setObjectName(QStringLiteral("myButtonConfigFilter"));

        horizontalLayout_3->addWidget(myButtonConfigFilter);

        groupBox_2 = new QGroupBox(GeneralConfigurationDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 531, 101));
        horizontalLayoutWidget = new QWidget(groupBox_2);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(140, 30, 227, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        mySpinNbThreads = new QSpinBox(horizontalLayoutWidget);
        mySpinNbThreads->setObjectName(QStringLiteral("mySpinNbThreads"));
        mySpinNbThreads->setMinimum(1);
        mySpinNbThreads->setValue(1);

        verticalLayout->addWidget(mySpinNbThreads);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        mySpinOversampling = new QSpinBox(horizontalLayoutWidget);
        mySpinOversampling->setObjectName(QStringLiteral("mySpinOversampling"));
        mySpinOversampling->setMinimum(1);
        mySpinOversampling->setValue(1);

        verticalLayout_2->addWidget(mySpinOversampling);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        mySpinBlockSize = new QSpinBox(horizontalLayoutWidget);
        mySpinBlockSize->setObjectName(QStringLiteral("mySpinBlockSize"));
        mySpinBlockSize->setMinimum(2);
        mySpinBlockSize->setMaximum(10000);
        mySpinBlockSize->setValue(32);

        verticalLayout_3->addWidget(mySpinBlockSize);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(GeneralConfigurationDialog);

        QMetaObject::connectSlotsByName(GeneralConfigurationDialog);
    } // setupUi

    void retranslateUi(QWidget *GeneralConfigurationDialog)
    {
        GeneralConfigurationDialog->setWindowTitle(QApplication::translate("GeneralConfigurationDialog", "GeneralConfigurationDialog", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("GeneralConfigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("GeneralConfigurationDialog", "Cancel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("GeneralConfigurationDialog", "Filter", Q_NULLPTR));
        myCheckboxUseFilter->setText(QApplication::translate("GeneralConfigurationDialog", "Use reconstruction filter", Q_NULLPTR));
        myComboFilterType->clear();
        myComboFilterType->insertItems(0, QStringList()
         << QApplication::translate("GeneralConfigurationDialog", "Box", Q_NULLPTR)
         << QApplication::translate("GeneralConfigurationDialog", "Gaussian", Q_NULLPTR)
         << QApplication::translate("GeneralConfigurationDialog", "MitchellNetravali", Q_NULLPTR)
        );
        myButtonConfigFilter->setText(QApplication::translate("GeneralConfigurationDialog", "Configure", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("GeneralConfigurationDialog", "Computation", Q_NULLPTR));
        label->setText(QApplication::translate("GeneralConfigurationDialog", "Nb. threads", Q_NULLPTR));
        label_2->setText(QApplication::translate("GeneralConfigurationDialog", "Oversampling", Q_NULLPTR));
        label_3->setText(QApplication::translate("GeneralConfigurationDialog", "Block size", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GeneralConfigurationDialog: public Ui_GeneralConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERALCONFIGURATIONDIALOG_H
