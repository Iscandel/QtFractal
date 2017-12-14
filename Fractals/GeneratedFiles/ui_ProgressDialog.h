/********************************************************************************
** Form generated from reading UI file 'ProgressDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSDIALOG_H
#define UI_PROGRESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QProgressBar *myProgressBar;
    QFormLayout *formLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *ProgressDialog)
    {
        if (ProgressDialog->objectName().isEmpty())
            ProgressDialog->setObjectName(QStringLiteral("ProgressDialog"));
        ProgressDialog->resize(400, 95);
        verticalLayoutWidget = new QWidget(ProgressDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 10, 351, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        myProgressBar = new QProgressBar(verticalLayoutWidget);
        myProgressBar->setObjectName(QStringLiteral("myProgressBar"));
        myProgressBar->setValue(24);

        verticalLayout->addWidget(myProgressBar);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetMinimumSize);
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton);


        verticalLayout->addLayout(formLayout);


        retranslateUi(ProgressDialog);

        QMetaObject::connectSlotsByName(ProgressDialog);
    } // setupUi

    void retranslateUi(QWidget *ProgressDialog)
    {
        ProgressDialog->setWindowTitle(QApplication::translate("ProgressDialog", "ProgressDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ProgressDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProgressDialog: public Ui_ProgressDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSDIALOG_H
