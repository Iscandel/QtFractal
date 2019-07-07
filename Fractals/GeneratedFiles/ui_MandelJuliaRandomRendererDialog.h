/********************************************************************************
** Form generated from reading UI file 'MandelJuliaRandomRendererDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANDELJULIARANDOMRENDERERDIALOG_H
#define UI_MANDELJULIARANDOMRENDERERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MandelJuliaRandomRendererDialog
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *myRadioColor1;
    QRadioButton *myRadioColor2;
    QRadioButton *myRadioColor3;
    QRadioButton *myRadioColor4;
    QRadioButton *myRadioColor5;
    QRadioButton *myRadioFractalColor6;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *myButtonOk;
    QPushButton *myButtonCancel;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QScrollBar *myScrollBarRed;
    QLabel *label_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QScrollBar *myScrollBarGreen;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QScrollBar *myScrollBarBlue;
    QLabel *label_5;
    QLabel *myLabelColorPreview;
    QPushButton *myButtonPredefined;
    QPushButton *myButtonRandom;

    void setupUi(QDialog *MandelJuliaRandomRendererDialog)
    {
        if (MandelJuliaRandomRendererDialog->objectName().isEmpty())
            MandelJuliaRandomRendererDialog->setObjectName(QStringLiteral("MandelJuliaRandomRendererDialog"));
        MandelJuliaRandomRendererDialog->resize(400, 313);
        label = new QLabel(MandelJuliaRandomRendererDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 211, 16));
        horizontalLayoutWidget = new QWidget(MandelJuliaRandomRendererDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 40, 261, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        myRadioColor1 = new QRadioButton(horizontalLayoutWidget);
        myRadioColor1->setObjectName(QStringLiteral("myRadioColor1"));

        horizontalLayout->addWidget(myRadioColor1);

        myRadioColor2 = new QRadioButton(horizontalLayoutWidget);
        myRadioColor2->setObjectName(QStringLiteral("myRadioColor2"));

        horizontalLayout->addWidget(myRadioColor2);

        myRadioColor3 = new QRadioButton(horizontalLayoutWidget);
        myRadioColor3->setObjectName(QStringLiteral("myRadioColor3"));

        horizontalLayout->addWidget(myRadioColor3);

        myRadioColor4 = new QRadioButton(horizontalLayoutWidget);
        myRadioColor4->setObjectName(QStringLiteral("myRadioColor4"));

        horizontalLayout->addWidget(myRadioColor4);

        myRadioColor5 = new QRadioButton(horizontalLayoutWidget);
        myRadioColor5->setObjectName(QStringLiteral("myRadioColor5"));

        horizontalLayout->addWidget(myRadioColor5);

        myRadioFractalColor6 = new QRadioButton(horizontalLayoutWidget);
        myRadioFractalColor6->setObjectName(QStringLiteral("myRadioFractalColor6"));

        horizontalLayout->addWidget(myRadioFractalColor6);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 5);
        horizontalLayout->setStretch(2, 5);
        horizontalLayout->setStretch(3, 5);
        horizontalLayout->setStretch(4, 10);
        horizontalLayout->setStretch(5, 1);
        label_2 = new QLabel(MandelJuliaRandomRendererDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(250, 20, 101, 16));
        horizontalLayoutWidget_2 = new QWidget(MandelJuliaRandomRendererDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(100, 270, 195, 31));
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

        horizontalLayoutWidget_3 = new QWidget(MandelJuliaRandomRendererDialog);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 90, 191, 31));
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
        horizontalLayoutWidget_4 = new QWidget(MandelJuliaRandomRendererDialog);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 130, 201, 31));
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
        horizontalLayoutWidget_5 = new QWidget(MandelJuliaRandomRendererDialog);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 170, 191, 31));
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
        myLabelColorPreview = new QLabel(MandelJuliaRandomRendererDialog);
        myLabelColorPreview->setObjectName(QStringLiteral("myLabelColorPreview"));
        myLabelColorPreview->setGeometry(QRect(250, 90, 111, 111));
        myButtonPredefined = new QPushButton(MandelJuliaRandomRendererDialog);
        myButtonPredefined->setObjectName(QStringLiteral("myButtonPredefined"));
        myButtonPredefined->setGeometry(QRect(80, 220, 93, 28));
        myButtonRandom = new QPushButton(MandelJuliaRandomRendererDialog);
        myButtonRandom->setObjectName(QStringLiteral("myButtonRandom"));
        myButtonRandom->setGeometry(QRect(220, 220, 93, 28));

        retranslateUi(MandelJuliaRandomRendererDialog);

        QMetaObject::connectSlotsByName(MandelJuliaRandomRendererDialog);
    } // setupUi

    void retranslateUi(QDialog *MandelJuliaRandomRendererDialog)
    {
        MandelJuliaRandomRendererDialog->setWindowTitle(QApplication::translate("MandelJuliaRandomRendererDialog", "MandelJuliaRandomColorRenderer", Q_NULLPTR));
        label->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Low iterations --> High iterations", Q_NULLPTR));
        myRadioColor1->setText(QString());
        myRadioColor2->setText(QString());
        myRadioColor3->setText(QString());
        myRadioColor4->setText(QString());
        myRadioColor5->setText(QString());
        myRadioFractalColor6->setText(QString());
        label_2->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Fractal set color", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Cancel", Q_NULLPTR));
        label_3->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Red", Q_NULLPTR));
        label_4->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Green", Q_NULLPTR));
        label_5->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Blue", Q_NULLPTR));
        myLabelColorPreview->setText(QString());
        myButtonPredefined->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Predefined", Q_NULLPTR));
        myButtonRandom->setText(QApplication::translate("MandelJuliaRandomRendererDialog", "Random", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MandelJuliaRandomRendererDialog: public Ui_MandelJuliaRandomRendererDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANDELJULIARANDOMRENDERERDIALOG_H
