/********************************************************************************
** Form generated from reading UI file 'LyapunovConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LYAPUNOVCONFIGURATIONDIALOG_H
#define UI_LYAPUNOVCONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_LyapunovConigurationDialog
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
    QLabel *label_2;
    QPushButton *myButtonConfigureRenderer;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_9;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_10;
    QSpinBox *mySpinIterations;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_11;
    QDoubleSpinBox *mySpinInitialValue;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_11;
    QLabel *label;
    QLineEdit *myEditSequence;

    void setupUi(QDialog *LyapunovConigurationDialog)
    {
        if (LyapunovConigurationDialog->objectName().isEmpty())
            LyapunovConigurationDialog->setObjectName(QStringLiteral("LyapunovConigurationDialog"));
        LyapunovConigurationDialog->resize(357, 598);
        groupBox = new QGroupBox(LyapunovConigurationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 341, 171));
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
        mySpinXMin->setValue(0);

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
        mySpinXMax->setValue(4);

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
        mySpinYMin->setValue(0);

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
        mySpinYMax->setValue(4);

        verticalLayout_2->addWidget(mySpinYMax);


        verticalLayout_4->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_4, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(LyapunovConigurationDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 190, 341, 80));
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

        horizontalLayoutWidget = new QWidget(LyapunovConigurationDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(80, 530, 195, 41));
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

        groupBox_4 = new QGroupBox(LyapunovConigurationDialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 430, 341, 80));
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
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_10->addWidget(label_2);

        myButtonConfigureRenderer = new QPushButton(horizontalLayoutWidget_2);
        myButtonConfigureRenderer->setObjectName(QStringLiteral("myButtonConfigureRenderer"));

        verticalLayout_10->addWidget(myButtonConfigureRenderer);


        horizontalLayout_2->addLayout(verticalLayout_10);

        groupBox_3 = new QGroupBox(LyapunovConigurationDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 280, 341, 141));
        verticalLayoutWidget_9 = new QWidget(groupBox_3);
        verticalLayoutWidget_9->setObjectName(QStringLiteral("verticalLayoutWidget_9"));
        verticalLayoutWidget_9->setGeometry(QRect(10, 20, 111, 51));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(verticalLayoutWidget_9);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_9->addWidget(label_10);

        mySpinIterations = new QSpinBox(verticalLayoutWidget_9);
        mySpinIterations->setObjectName(QStringLiteral("mySpinIterations"));
        mySpinIterations->setMaximum(10000000);
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
        label_11 = new QLabel(verticalLayoutWidget_5);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_5->addWidget(label_11);

        mySpinInitialValue = new QDoubleSpinBox(verticalLayoutWidget_5);
        mySpinInitialValue->setObjectName(QStringLiteral("mySpinInitialValue"));
        mySpinInitialValue->setMinimum(-1e+6);
        mySpinInitialValue->setMaximum(1e+7);
        mySpinInitialValue->setValue(0.5);

        verticalLayout_5->addWidget(mySpinInitialValue);

        verticalLayoutWidget = new QWidget(groupBox_3);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 80, 201, 51));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_11->addWidget(label);

        myEditSequence = new QLineEdit(verticalLayoutWidget);
        myEditSequence->setObjectName(QStringLiteral("myEditSequence"));

        verticalLayout_11->addWidget(myEditSequence);


        retranslateUi(LyapunovConigurationDialog);

        QMetaObject::connectSlotsByName(LyapunovConigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *LyapunovConigurationDialog)
    {
        LyapunovConigurationDialog->setWindowTitle(QApplication::translate("LyapunovConigurationDialog", "LyapunovConigurationDialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LyapunovConigurationDialog", "Domain", Q_NULLPTR));
        label_5->setText(QApplication::translate("LyapunovConigurationDialog", "X min", Q_NULLPTR));
        label_7->setText(QApplication::translate("LyapunovConigurationDialog", "X max", Q_NULLPTR));
        label_6->setText(QApplication::translate("LyapunovConigurationDialog", "Y min", Q_NULLPTR));
        label_8->setText(QApplication::translate("LyapunovConigurationDialog", "Y max", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("LyapunovConigurationDialog", "Image size", Q_NULLPTR));
        label_3->setText(QApplication::translate("LyapunovConigurationDialog", "Size X", Q_NULLPTR));
        label_4->setText(QApplication::translate("LyapunovConigurationDialog", "Size Y", Q_NULLPTR));
        myButtonOk->setText(QApplication::translate("LyapunovConigurationDialog", "OK", Q_NULLPTR));
        myButtonCancel->setText(QApplication::translate("LyapunovConigurationDialog", "Cancel", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("LyapunovConigurationDialog", "Renderer", Q_NULLPTR));
        label_9->setText(QApplication::translate("LyapunovConigurationDialog", "Renderer", Q_NULLPTR));
        myComboRenderer->clear();
        myComboRenderer->insertItems(0, QStringList()
         << QApplication::translate("LyapunovConigurationDialog", "Predefined 1", Q_NULLPTR)
         << QApplication::translate("LyapunovConigurationDialog", "Random", Q_NULLPTR)
        );
        label_2->setText(QString());
        myButtonConfigureRenderer->setText(QApplication::translate("LyapunovConigurationDialog", "Configure", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("LyapunovConigurationDialog", "General", Q_NULLPTR));
        label_10->setText(QApplication::translate("LyapunovConigurationDialog", "Iterations", Q_NULLPTR));
        label_11->setText(QApplication::translate("LyapunovConigurationDialog", "Initial value", Q_NULLPTR));
        label->setText(QApplication::translate("LyapunovConigurationDialog", "Sequence", Q_NULLPTR));
        myEditSequence->setText(QApplication::translate("LyapunovConigurationDialog", "ab", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LyapunovConigurationDialog: public Ui_LyapunovConigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LYAPUNOVCONFIGURATIONDIALOG_H
