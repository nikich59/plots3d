/********************************************************************************
** Form generated from reading UI file 'legendwidgetxyz.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEGENDWIDGETXYZ_H
#define UI_LEGENDWIDGETXYZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LegendWidgetXYZ
{
public:
    QLabel *label;
    QLabel *label_axisX;
    QLabel *label_axisY;
    QLabel *label_5;
    QLabel *label_levels;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_3;
    QLabel *label_centerX;
    QLabel *label_centerY;
    QLabel *label_rangeZ;
    QLabel *label_rangeX;
    QLabel *label_rangeY;
    QLabel *label_centerZ;

    void setupUi(QWidget *LegendWidgetXYZ)
    {
        if (LegendWidgetXYZ->objectName().isEmpty())
            LegendWidgetXYZ->setObjectName(QStringLiteral("LegendWidgetXYZ"));
        LegendWidgetXYZ->resize(360, 330);
        LegendWidgetXYZ->setWindowOpacity(0.5);
        label = new QLabel(LegendWidgetXYZ);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 261, 21));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_axisX = new QLabel(LegendWidgetXYZ);
        label_axisX->setObjectName(QStringLiteral("label_axisX"));
        label_axisX->setGeometry(QRect(10, 30, 261, 41));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_axisX->setPalette(palette);
        label_axisX->setAutoFillBackground(true);
        label_axisY = new QLabel(LegendWidgetXYZ);
        label_axisY->setObjectName(QStringLiteral("label_axisY"));
        label_axisY->setGeometry(QRect(10, 100, 261, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_axisY->setPalette(palette1);
        label_axisY->setAutoFillBackground(true);
        label_5 = new QLabel(LegendWidgetXYZ);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 80, 261, 21));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        label_levels = new QLabel(LegendWidgetXYZ);
        label_levels->setObjectName(QStringLiteral("label_levels"));
        label_levels->setGeometry(QRect(280, 30, 71, 291));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        label_levels->setPalette(palette2);
        label_levels->setAutoFillBackground(true);
        label_6 = new QLabel(LegendWidgetXYZ);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 180, 51, 21));
        label_6->setFont(font);
        label_7 = new QLabel(LegendWidgetXYZ);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 210, 51, 21));
        label_7->setFont(font);
        label_8 = new QLabel(LegendWidgetXYZ);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 240, 51, 21));
        label_8->setFont(font);
        label_9 = new QLabel(LegendWidgetXYZ);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 270, 51, 21));
        label_9->setFont(font);
        label_10 = new QLabel(LegendWidgetXYZ);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 150, 51, 21));
        label_10->setFont(font);
        label_11 = new QLabel(LegendWidgetXYZ);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 300, 51, 21));
        label_11->setFont(font);
        label_3 = new QLabel(LegendWidgetXYZ);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(280, 10, 71, 16));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        label_centerX = new QLabel(LegendWidgetXYZ);
        label_centerX->setObjectName(QStringLiteral("label_centerX"));
        label_centerX->setGeometry(QRect(70, 150, 71, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(235, 235, 235, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_centerX->setPalette(palette3);
        label_centerX->setFont(font);
        label_centerX->setAutoFillBackground(true);
        label_centerY = new QLabel(LegendWidgetXYZ);
        label_centerY->setObjectName(QStringLiteral("label_centerY"));
        label_centerY->setGeometry(QRect(70, 180, 71, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_centerY->setPalette(palette4);
        label_centerY->setFont(font);
        label_centerY->setAutoFillBackground(true);
        label_rangeZ = new QLabel(LegendWidgetXYZ);
        label_rangeZ->setObjectName(QStringLiteral("label_rangeZ"));
        label_rangeZ->setGeometry(QRect(70, 300, 71, 21));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_rangeZ->setPalette(palette5);
        label_rangeZ->setFont(font);
        label_rangeZ->setAutoFillBackground(true);
        label_rangeX = new QLabel(LegendWidgetXYZ);
        label_rangeX->setObjectName(QStringLiteral("label_rangeX"));
        label_rangeX->setGeometry(QRect(70, 240, 71, 21));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_rangeX->setPalette(palette6);
        label_rangeX->setFont(font);
        label_rangeX->setAutoFillBackground(true);
        label_rangeY = new QLabel(LegendWidgetXYZ);
        label_rangeY->setObjectName(QStringLiteral("label_rangeY"));
        label_rangeY->setGeometry(QRect(70, 270, 71, 21));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_rangeY->setPalette(palette7);
        label_rangeY->setFont(font);
        label_rangeY->setAutoFillBackground(true);
        label_centerZ = new QLabel(LegendWidgetXYZ);
        label_centerZ->setObjectName(QStringLiteral("label_centerZ"));
        label_centerZ->setGeometry(QRect(70, 210, 71, 21));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_centerZ->setPalette(palette8);
        label_centerZ->setFont(font);
        label_centerZ->setAutoFillBackground(true);

        retranslateUi(LegendWidgetXYZ);

        QMetaObject::connectSlotsByName(LegendWidgetXYZ);
    } // setupUi

    void retranslateUi(QWidget *LegendWidgetXYZ)
    {
        LegendWidgetXYZ->setWindowTitle(QApplication::translate("LegendWidgetXYZ", "Form", 0));
        label->setText(QApplication::translate("LegendWidgetXYZ", "X", 0));
        label_axisX->setText(QString());
        label_axisY->setText(QString());
        label_5->setText(QApplication::translate("LegendWidgetXYZ", "Y", 0));
        label_levels->setText(QString());
        label_6->setText(QApplication::translate("LegendWidgetXYZ", "CenterY:", 0));
        label_7->setText(QApplication::translate("LegendWidgetXYZ", "CenterZ:", 0));
        label_8->setText(QApplication::translate("LegendWidgetXYZ", "RangeX:", 0));
        label_9->setText(QApplication::translate("LegendWidgetXYZ", "RangeY:", 0));
        label_10->setText(QApplication::translate("LegendWidgetXYZ", "CenterX:", 0));
        label_11->setText(QApplication::translate("LegendWidgetXYZ", "RangeZ:", 0));
        label_3->setText(QApplication::translate("LegendWidgetXYZ", "Levels:", 0));
        label_centerX->setText(QString());
        label_centerY->setText(QString());
        label_rangeZ->setText(QString());
        label_rangeX->setText(QString());
        label_rangeY->setText(QString());
        label_centerZ->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LegendWidgetXYZ: public Ui_LegendWidgetXYZ {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEGENDWIDGETXYZ_H
