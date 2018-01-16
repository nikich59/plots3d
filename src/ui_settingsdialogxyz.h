/********************************************************************************
** Form generated from reading UI file 'settingsdialogxyz.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOGXYZ_H
#define UI_SETTINGSDIALOGXYZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialogXYZ
{
public:
    QPushButton *pushButton;
    QFrame *frame;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *spinBox_centerX;
    QLabel *label_3;
    QDoubleSpinBox *spinBox_centerY;
    QLabel *label_4;
    QDoubleSpinBox *spinBox_centerZ;
    QFrame *frame_2;
    QFrame *line_6;
    QFrame *line_7;
    QFrame *line_8;
    QFrame *line_9;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *spinBox_rangeX;
    QLabel *label_7;
    QDoubleSpinBox *spinBox_rangeY;
    QLabel *label_8;
    QDoubleSpinBox *spinBox_rangeZ;
    QFrame *frame_axis;
    QLabel *label_axis;
    QLabel *label_surfaceTopColor;
    QPushButton *pushButton_surfaceTopColor;
    QLabel *label_surfaceMiddleColor;
    QPushButton *pushButton_surfaceMiddleColor;
    QLabel *label_surfaceBottomColor;
    QPushButton *pushButton_surfaceBottomColor;
    QFrame *line_axisBottom;
    QFrame *line_axisTop;
    QFrame *line_axisLeft;
    QFrame *line_10;
    QCheckBox *checkBox_surfaceEnabled;
    QPushButton *pushButton_surfaceMiddleColorAuto;
    QFrame *frame_3;
    QFrame *line_11;
    QFrame *line_12;
    QFrame *line_13;
    QFrame *line_14;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QComboBox *comboBox_netXPeriodicy;
    QComboBox *comboBox_netYPeriodicy;
    QFrame *frame_4;
    QFrame *line_17;
    QFrame *line_15;
    QFrame *line_16;
    QFrame *line_18;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *lineEdit_nameX;
    QLineEdit *lineEdit_nameY;
    QLabel *label_14;
    QFrame *line;

    void setupUi(QDialog *SettingsDialogXYZ)
    {
        if (SettingsDialogXYZ->objectName().isEmpty())
            SettingsDialogXYZ->setObjectName(QStringLiteral("SettingsDialogXYZ"));
        SettingsDialogXYZ->resize(1340, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsDialogXYZ->sizePolicy().hasHeightForWidth());
        SettingsDialogXYZ->setSizePolicy(sizePolicy);
        pushButton = new QPushButton(SettingsDialogXYZ);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 360, 341, 51));
        QFont font;
        font.setPointSize(20);
        pushButton->setFont(font);
        frame = new QFrame(SettingsDialogXYZ);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(180, 260, 161, 151));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame->setPalette(palette);
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        line_2 = new QFrame(frame);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(-1, 10, 21, 131));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(frame);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(140, 10, 21, 131));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(frame);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(9, 130, 141, 21));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(frame);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 0, 141, 21));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 121, 41));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 50, 21, 21));
        QFont font2;
        font2.setPointSize(10);
        label_2->setFont(font2);
        spinBox_centerX = new QDoubleSpinBox(frame);
        spinBox_centerX->setObjectName(QStringLiteral("spinBox_centerX"));
        spinBox_centerX->setGeometry(QRect(50, 50, 91, 22));
        spinBox_centerX->setFont(font2);
        spinBox_centerX->setDecimals(6);
        spinBox_centerX->setMinimum(-1e+14);
        spinBox_centerX->setMaximum(1e+17);
        spinBox_centerX->setSingleStep(0);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 21, 21));
        label_3->setFont(font2);
        spinBox_centerY = new QDoubleSpinBox(frame);
        spinBox_centerY->setObjectName(QStringLiteral("spinBox_centerY"));
        spinBox_centerY->setGeometry(QRect(50, 80, 91, 22));
        spinBox_centerY->setFont(font2);
        spinBox_centerY->setDecimals(6);
        spinBox_centerY->setMinimum(-1e+14);
        spinBox_centerY->setMaximum(1e+17);
        spinBox_centerY->setSingleStep(0);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 110, 21, 21));
        label_4->setFont(font2);
        spinBox_centerZ = new QDoubleSpinBox(frame);
        spinBox_centerZ->setObjectName(QStringLiteral("spinBox_centerZ"));
        spinBox_centerZ->setGeometry(QRect(50, 110, 91, 22));
        spinBox_centerZ->setFont(font2);
        spinBox_centerZ->setDecimals(6);
        spinBox_centerZ->setMinimum(-1e+14);
        spinBox_centerZ->setMaximum(1e+17);
        spinBox_centerZ->setSingleStep(0);
        frame_2 = new QFrame(SettingsDialogXYZ);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 260, 161, 151));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame_2->setPalette(palette1);
        frame_2->setAutoFillBackground(true);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        line_6 = new QFrame(frame_2);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(-1, 10, 21, 131));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(frame_2);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(140, 10, 21, 131));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(frame_2);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(9, 130, 141, 21));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(frame_2);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(10, 0, 141, 21));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 10, 121, 41));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 50, 21, 21));
        label_6->setFont(font2);
        spinBox_rangeX = new QDoubleSpinBox(frame_2);
        spinBox_rangeX->setObjectName(QStringLiteral("spinBox_rangeX"));
        spinBox_rangeX->setGeometry(QRect(50, 50, 91, 22));
        spinBox_rangeX->setFont(font2);
        spinBox_rangeX->setDecimals(6);
        spinBox_rangeX->setMinimum(0);
        spinBox_rangeX->setMaximum(1e+17);
        spinBox_rangeX->setSingleStep(0);
        spinBox_rangeX->setValue(1);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 80, 21, 21));
        label_7->setFont(font2);
        spinBox_rangeY = new QDoubleSpinBox(frame_2);
        spinBox_rangeY->setObjectName(QStringLiteral("spinBox_rangeY"));
        spinBox_rangeY->setGeometry(QRect(50, 80, 91, 22));
        spinBox_rangeY->setFont(font2);
        spinBox_rangeY->setDecimals(6);
        spinBox_rangeY->setMinimum(0);
        spinBox_rangeY->setMaximum(1e+17);
        spinBox_rangeY->setSingleStep(0);
        spinBox_rangeY->setValue(1);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 110, 21, 21));
        label_8->setFont(font2);
        spinBox_rangeZ = new QDoubleSpinBox(frame_2);
        spinBox_rangeZ->setObjectName(QStringLiteral("spinBox_rangeZ"));
        spinBox_rangeZ->setGeometry(QRect(50, 110, 91, 22));
        spinBox_rangeZ->setFont(font2);
        spinBox_rangeZ->setDecimals(6);
        spinBox_rangeZ->setMinimum(0);
        spinBox_rangeZ->setMaximum(1e+17);
        spinBox_rangeZ->setSingleStep(0);
        spinBox_rangeZ->setValue(1);
        frame_axis = new QFrame(SettingsDialogXYZ);
        frame_axis->setObjectName(QStringLiteral("frame_axis"));
        frame_axis->setGeometry(QRect(700, 260, 161, 181));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame_axis->setPalette(palette2);
        frame_axis->setAutoFillBackground(true);
        frame_axis->setFrameShape(QFrame::StyledPanel);
        frame_axis->setFrameShadow(QFrame::Raised);
        label_axis = new QLabel(frame_axis);
        label_axis->setObjectName(QStringLiteral("label_axis"));
        label_axis->setGeometry(QRect(20, 20, 121, 21));
        label_axis->setFont(font1);
        label_axis->setAlignment(Qt::AlignCenter);
        label_surfaceTopColor = new QLabel(frame_axis);
        label_surfaceTopColor->setObjectName(QStringLiteral("label_surfaceTopColor"));
        label_surfaceTopColor->setGeometry(QRect(120, 80, 21, 21));
        QPalette palette3;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_surfaceTopColor->setPalette(palette3);
        label_surfaceTopColor->setAutoFillBackground(true);
        pushButton_surfaceTopColor = new QPushButton(frame_axis);
        pushButton_surfaceTopColor->setObjectName(QStringLiteral("pushButton_surfaceTopColor"));
        pushButton_surfaceTopColor->setGeometry(QRect(20, 80, 91, 23));
        label_surfaceMiddleColor = new QLabel(frame_axis);
        label_surfaceMiddleColor->setObjectName(QStringLiteral("label_surfaceMiddleColor"));
        label_surfaceMiddleColor->setGeometry(QRect(120, 110, 21, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        label_surfaceMiddleColor->setPalette(palette4);
        label_surfaceMiddleColor->setAutoFillBackground(true);
        pushButton_surfaceMiddleColor = new QPushButton(frame_axis);
        pushButton_surfaceMiddleColor->setObjectName(QStringLiteral("pushButton_surfaceMiddleColor"));
        pushButton_surfaceMiddleColor->setGeometry(QRect(20, 110, 51, 23));
        label_surfaceBottomColor = new QLabel(frame_axis);
        label_surfaceBottomColor->setObjectName(QStringLiteral("label_surfaceBottomColor"));
        label_surfaceBottomColor->setGeometry(QRect(120, 140, 21, 21));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        label_surfaceBottomColor->setPalette(palette5);
        label_surfaceBottomColor->setAutoFillBackground(true);
        pushButton_surfaceBottomColor = new QPushButton(frame_axis);
        pushButton_surfaceBottomColor->setObjectName(QStringLiteral("pushButton_surfaceBottomColor"));
        pushButton_surfaceBottomColor->setGeometry(QRect(20, 140, 91, 23));
        line_axisBottom = new QFrame(frame_axis);
        line_axisBottom->setObjectName(QStringLiteral("line_axisBottom"));
        line_axisBottom->setGeometry(QRect(10, 160, 141, 20));
        line_axisBottom->setFrameShape(QFrame::HLine);
        line_axisBottom->setFrameShadow(QFrame::Sunken);
        line_axisTop = new QFrame(frame_axis);
        line_axisTop->setObjectName(QStringLiteral("line_axisTop"));
        line_axisTop->setGeometry(QRect(10, 0, 141, 20));
        line_axisTop->setFrameShape(QFrame::HLine);
        line_axisTop->setFrameShadow(QFrame::Sunken);
        line_axisLeft = new QFrame(frame_axis);
        line_axisLeft->setObjectName(QStringLiteral("line_axisLeft"));
        line_axisLeft->setGeometry(QRect(0, 9, 20, 161));
        line_axisLeft->setFrameShape(QFrame::VLine);
        line_axisLeft->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(frame_axis);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setGeometry(QRect(140, 10, 20, 161));
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);
        checkBox_surfaceEnabled = new QCheckBox(frame_axis);
        checkBox_surfaceEnabled->setObjectName(QStringLiteral("checkBox_surfaceEnabled"));
        checkBox_surfaceEnabled->setGeometry(QRect(20, 51, 121, 20));
        checkBox_surfaceEnabled->setFont(font2);
        checkBox_surfaceEnabled->setChecked(true);
        pushButton_surfaceMiddleColorAuto = new QPushButton(frame_axis);
        pushButton_surfaceMiddleColorAuto->setObjectName(QStringLiteral("pushButton_surfaceMiddleColorAuto"));
        pushButton_surfaceMiddleColorAuto->setGeometry(QRect(80, 110, 31, 23));
        frame_3 = new QFrame(SettingsDialogXYZ);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(870, 260, 171, 121));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame_3->setPalette(palette6);
        frame_3->setAutoFillBackground(true);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        line_11 = new QFrame(frame_3);
        line_11->setObjectName(QStringLiteral("line_11"));
        line_11->setGeometry(QRect(-1, 10, 21, 101));
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(frame_3);
        line_12->setObjectName(QStringLiteral("line_12"));
        line_12->setGeometry(QRect(150, 10, 21, 101));
        line_12->setFrameShape(QFrame::VLine);
        line_12->setFrameShadow(QFrame::Sunken);
        line_13 = new QFrame(frame_3);
        line_13->setObjectName(QStringLiteral("line_13"));
        line_13->setGeometry(QRect(9, 100, 151, 21));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);
        line_14 = new QFrame(frame_3);
        line_14->setObjectName(QStringLiteral("line_14"));
        line_14->setGeometry(QRect(10, 0, 151, 21));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(frame_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 10, 131, 41));
        label_9->setFont(font1);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(frame_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 50, 21, 21));
        label_10->setFont(font2);
        label_11 = new QLabel(frame_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 80, 21, 21));
        label_11->setFont(font2);
        comboBox_netXPeriodicy = new QComboBox(frame_3);
        comboBox_netXPeriodicy->setObjectName(QStringLiteral("comboBox_netXPeriodicy"));
        comboBox_netXPeriodicy->setGeometry(QRect(50, 50, 101, 22));
        comboBox_netXPeriodicy->setFont(font2);
        comboBox_netYPeriodicy = new QComboBox(frame_3);
        comboBox_netYPeriodicy->setObjectName(QStringLiteral("comboBox_netYPeriodicy"));
        comboBox_netYPeriodicy->setGeometry(QRect(50, 80, 101, 22));
        comboBox_netYPeriodicy->setFont(font2);
        frame_4 = new QFrame(SettingsDialogXYZ);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(350, 260, 341, 91));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame_4->setPalette(palette7);
        frame_4->setAutoFillBackground(true);
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        line_17 = new QFrame(frame_4);
        line_17->setObjectName(QStringLiteral("line_17"));
        line_17->setGeometry(QRect(0, 10, 21, 71));
        line_17->setFrameShape(QFrame::VLine);
        line_17->setFrameShadow(QFrame::Sunken);
        line_15 = new QFrame(frame_4);
        line_15->setObjectName(QStringLiteral("line_15"));
        line_15->setGeometry(QRect(10, 0, 321, 21));
        line_15->setFrameShape(QFrame::HLine);
        line_15->setFrameShadow(QFrame::Sunken);
        line_16 = new QFrame(frame_4);
        line_16->setObjectName(QStringLiteral("line_16"));
        line_16->setGeometry(QRect(10, 70, 321, 21));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);
        line_18 = new QFrame(frame_4);
        line_18->setObjectName(QStringLiteral("line_18"));
        line_18->setGeometry(QRect(320, 10, 21, 71));
        line_18->setFrameShape(QFrame::VLine);
        line_18->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(frame_4);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 20, 301, 21));
        label_12->setFont(font1);
        label_12->setAlignment(Qt::AlignCenter);
        label_13 = new QLabel(frame_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 50, 21, 21));
        label_13->setFont(font2);
        lineEdit_nameX = new QLineEdit(frame_4);
        lineEdit_nameX->setObjectName(QStringLiteral("lineEdit_nameX"));
        lineEdit_nameX->setGeometry(QRect(50, 50, 111, 20));
        lineEdit_nameX->setFont(font2);
        lineEdit_nameY = new QLineEdit(frame_4);
        lineEdit_nameY->setObjectName(QStringLiteral("lineEdit_nameY"));
        lineEdit_nameY->setGeometry(QRect(210, 50, 111, 20));
        lineEdit_nameY->setFont(font2);
        label_14 = new QLabel(frame_4);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(180, 50, 21, 21));
        label_14->setFont(font2);
        line = new QFrame(SettingsDialogXYZ);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 240, 1321, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(SettingsDialogXYZ);

        QMetaObject::connectSlotsByName(SettingsDialogXYZ);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialogXYZ)
    {
        SettingsDialogXYZ->setWindowTitle(QApplication::translate("SettingsDialogXYZ", "Dialog", 0));
        pushButton->setText(QApplication::translate("SettingsDialogXYZ", "Save", 0));
        label->setText(QApplication::translate("SettingsDialogXYZ", "Center:", 0));
        label_2->setText(QApplication::translate("SettingsDialogXYZ", "X:", 0));
        label_3->setText(QApplication::translate("SettingsDialogXYZ", "Y:", 0));
        label_4->setText(QApplication::translate("SettingsDialogXYZ", "F:", 0));
        label_5->setText(QApplication::translate("SettingsDialogXYZ", "Range:", 0));
        label_6->setText(QApplication::translate("SettingsDialogXYZ", "X:", 0));
        label_7->setText(QApplication::translate("SettingsDialogXYZ", "Y:", 0));
        label_8->setText(QApplication::translate("SettingsDialogXYZ", "F:", 0));
        label_axis->setText(QApplication::translate("SettingsDialogXYZ", "Surface:", 0));
        label_surfaceTopColor->setText(QString());
        pushButton_surfaceTopColor->setText(QApplication::translate("SettingsDialogXYZ", "Top", 0));
        label_surfaceMiddleColor->setText(QString());
        pushButton_surfaceMiddleColor->setText(QApplication::translate("SettingsDialogXYZ", "Middle", 0));
        label_surfaceBottomColor->setText(QString());
        pushButton_surfaceBottomColor->setText(QApplication::translate("SettingsDialogXYZ", "Bottom", 0));
        checkBox_surfaceEnabled->setText(QApplication::translate("SettingsDialogXYZ", "Enabled", 0));
        pushButton_surfaceMiddleColorAuto->setText(QApplication::translate("SettingsDialogXYZ", "auto", 0));
        label_9->setText(QApplication::translate("SettingsDialogXYZ", "Net periodicity:", 0));
        label_10->setText(QApplication::translate("SettingsDialogXYZ", "X:", 0));
        label_11->setText(QApplication::translate("SettingsDialogXYZ", "Y:", 0));
        comboBox_netXPeriodicy->clear();
        comboBox_netXPeriodicy->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialogXYZ", "Very low", 0)
         << QApplication::translate("SettingsDialogXYZ", "Low", 0)
         << QApplication::translate("SettingsDialogXYZ", "Decreased", 0)
         << QApplication::translate("SettingsDialogXYZ", "Middle", 0)
         << QApplication::translate("SettingsDialogXYZ", "Increased", 0)
         << QApplication::translate("SettingsDialogXYZ", "High", 0)
         << QApplication::translate("SettingsDialogXYZ", "Very high", 0)
         << QApplication::translate("SettingsDialogXYZ", "Ultra high", 0)
        );
        comboBox_netYPeriodicy->clear();
        comboBox_netYPeriodicy->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialogXYZ", "Very low", 0)
         << QApplication::translate("SettingsDialogXYZ", "Low", 0)
         << QApplication::translate("SettingsDialogXYZ", "Decreased", 0)
         << QApplication::translate("SettingsDialogXYZ", "Middle", 0)
         << QApplication::translate("SettingsDialogXYZ", "Increased", 0)
         << QApplication::translate("SettingsDialogXYZ", "High", 0)
         << QApplication::translate("SettingsDialogXYZ", "Very high", 0)
         << QApplication::translate("SettingsDialogXYZ", "Ultra high", 0)
        );
        label_12->setText(QApplication::translate("SettingsDialogXYZ", "Variables:", 0));
        label_13->setText(QApplication::translate("SettingsDialogXYZ", "X:", 0));
        lineEdit_nameX->setText(QApplication::translate("SettingsDialogXYZ", "x", 0));
        lineEdit_nameY->setText(QApplication::translate("SettingsDialogXYZ", "y", 0));
        label_14->setText(QApplication::translate("SettingsDialogXYZ", "Y:", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialogXYZ: public Ui_SettingsDialogXYZ {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOGXYZ_H
