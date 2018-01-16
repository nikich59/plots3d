#include "settingswidgetcommon.h"
#include "ui_settingswidgetcommon.h"
#include <scene3d.h>

SettingsWidgetCommon::SettingsWidgetCommon(SettingsCommon sets, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidgetCommon)
{
    ui->setupUi(this);
    ui->lineEdit_functionString->setText(sets.funcString);
    if (sets.axis == Scene3D::NO_AXIS)
        ui->comboBox_axis->setCurrentIndex(0);
    else if (sets.axis == Scene3D::CENTRAL_AXIS)
        ui->comboBox_axis->setCurrentIndex(1);
    else if (sets.axis == Scene3D::BOUNDING_AXIS)
        ui->comboBox_axis->setCurrentIndex(2);
    else if (sets.axis == Scene3D::BOUNDING_AXIS_CELLULAR)
        ui->comboBox_axis->setCurrentIndex(3);
    QPalette palette;
    palette = ui->label_colorX->palette();
    palette.setColor(QPalette::Background, sets.axis1Color);
    ui->label_colorX->setPalette(palette);
    palette = ui->label_colorY->palette();
    palette.setColor(QPalette::Background, sets.axis2Color);
    ui->label_colorY->setPalette(palette);
    palette = ui->label_colorZ->palette();
    palette.setColor(QPalette::Background, sets.axis3Color);
    ui->label_colorZ->setPalette(palette);
    ui->lineEdit_configFile->setText(sets.contextFileName);
    ui->checkBox_timeEnabled->setChecked(sets.isActivatedTime);
    on_checkBox_timeEnabled_clicked();
    ui->checkBox_isonetEnabled->setChecked(sets.isIsonetEnable);
    ui->checkBox_netEnabled->setChecked(sets.isNetEnable);
    palette = ui->label_isonetColor->palette();
    palette.setColor(QPalette::Background, sets.isonetColor);
    ui->label_isonetColor->setPalette(palette);
    ui->spinBox_isonetWidth->setValue(sets.isonetWidth);
    palette = ui->label_netColor->palette();
    palette.setColor(QPalette::Background, sets.netColor);
    ui->label_netColor->setPalette(palette);
    ui->spinBox_netWidth->setValue(sets.netWidth);
    ui->spinBox_radius->setValue(sets.radius);
    ui->spinBox_scaleRate->setValue(sets.scaleRate);
    if (sets.sceneMoveMouseButton == Qt::LeftButton)
        ui->comboBox_movingButton->setCurrentIndex(0);
    else if (sets.sceneMoveMouseButton == Qt::MiddleButton)
        ui->comboBox_movingButton->setCurrentIndex(1);
    else if (sets.sceneMoveMouseButton == Qt::RightButton)
        ui->comboBox_movingButton->setCurrentIndex(2);
    ui->spinBox_timeStep->setValue(sets.timeStep);
    ui->lineEdit_timeVariableName->setText(sets.timeName);
    switch(sets.surfaceQuality) {
    case Scene3D::VERY_LOW: ui->comboBox_surfaceQuality->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_surfaceQuality->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_surfaceQuality->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_surfaceQuality->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_surfaceQuality->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_surfaceQuality->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_surfaceQuality->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_surfaceQuality->setCurrentIndex(7); break;
    }
    switch(sets.isolinePeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_isolinePeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_isolinePeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_isolinePeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_isolinePeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_isolinePeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_isolinePeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_isolinePeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_isolinePeriodicy->setCurrentIndex(7); break;
    }
    ui->slider_verticalscale->setValue(round((float)5.0 * sets.verticalExtension));
    ui->checkBox_isLegendShowed->setChecked(sets.isShowedLegend);
    ui->slider_legendSize->setValue(round((float)sets.legendSizeRatio * 100.0));
    ui->slider_legendOpacity->setValue(round((float)sets.legendBackOpacity * 100.0));
    ui->checkBox_perspective->setChecked(sets.isPerspectiveEnabled);
    ui->checkBox_proportions->setChecked(sets.isNativeProportions);
}

SettingsWidgetCommon::~SettingsWidgetCommon()
{
    delete ui;
}

SettingsCommon SettingsWidgetCommon:: getSettings() const
{
    SettingsCommon settings;
    settings.funcString = ui->lineEdit_functionString->text();
    if (ui->comboBox_axis->currentIndex() == 0)
        settings.axis = Scene3D::NO_AXIS;
    else if (ui->comboBox_axis->currentIndex() == 1)
        settings.axis = Scene3D::CENTRAL_AXIS;
    else if (ui->comboBox_axis->currentIndex() == 2)
        settings.axis = Scene3D::BOUNDING_AXIS;
    else if (ui->comboBox_axis->currentIndex() == 3)
        settings.axis = Scene3D::BOUNDING_AXIS_CELLULAR;

    settings.axis1Color = ui->label_colorX->palette().background().color();
    settings.axis2Color = ui->label_colorY->palette().background().color();
    settings.axis3Color = ui->label_colorZ->palette().background().color();
    settings.contextFileName = ui->lineEdit_configFile->text();
    settings.isActivatedTime = ui->checkBox_timeEnabled->isChecked();
    settings.isIsonetEnable = ui->checkBox_isonetEnabled->isChecked();
    settings.isNetEnable = ui->checkBox_netEnabled->isChecked();
    settings.isonetColor = ui->label_isonetColor->palette().background().color();
    settings.isonetWidth = ui->spinBox_isonetWidth->value();
    settings.netColor = ui->label_netColor->palette().background().color();
    settings.netWidth = ui->spinBox_netWidth->value();
    settings.radius = ui->spinBox_radius->value();
    settings.scaleRate = ui->spinBox_scaleRate->value();

    if (ui->comboBox_movingButton->currentText() == "Left button")
        settings.sceneMoveMouseButton = Qt::LeftButton;
    else if (ui->comboBox_movingButton->currentText() == "Wheel button")
        settings.sceneMoveMouseButton = Qt::MiddleButton;
    else if (ui->comboBox_movingButton->currentText() == "Right button")
        settings.sceneMoveMouseButton = Qt::RightButton;
    settings.timeStep = ui->spinBox_timeStep->value();
    settings.timeName = ui->lineEdit_timeVariableName->text();
    switch(ui->comboBox_surfaceQuality->currentIndex()) {
    case 0: settings.surfaceQuality = Scene3D::VERY_LOW; break;
    case 1: settings.surfaceQuality = Scene3D::LOW; break;
    case 2: settings.surfaceQuality = Scene3D::DECREASED; break;
    case 3: settings.surfaceQuality = Scene3D::MIDDLE; break;
    case 4: settings.surfaceQuality = Scene3D::INCREASED; break;
    case 5: settings.surfaceQuality = Scene3D::HIGH; break;
    case 6: settings.surfaceQuality = Scene3D::VERY_HIGH; break;
    case 7: settings.surfaceQuality = Scene3D::ULTRA_HIGH; break;
    }
    switch(ui->comboBox_isolinePeriodicy->currentIndex()) {
    case 0: settings.isolinePeriodicity = Scene3D::VERY_LOW; break;
    case 1: settings.isolinePeriodicity = Scene3D::LOW; break;
    case 2: settings.isolinePeriodicity = Scene3D::DECREASED; break;
    case 3: settings.isolinePeriodicity = Scene3D::MIDDLE; break;
    case 4: settings.isolinePeriodicity = Scene3D::INCREASED; break;
    case 5: settings.isolinePeriodicity = Scene3D::HIGH; break;
    case 6: settings.isolinePeriodicity = Scene3D::VERY_HIGH; break;
    case 7: settings.isolinePeriodicity = Scene3D::ULTRA_HIGH; break;
    }
    settings.verticalExtension = (float)ui->slider_verticalscale->value() / 5.0;
    settings.isShowedLegend = ui->checkBox_isLegendShowed->isChecked();
    settings.legendSizeRatio = (float)ui->slider_legendSize->value() / 100.0;
    settings.legendBackOpacity = (float)ui->slider_legendOpacity->value() / 100.0;
    settings.isPerspectiveEnabled = ui->checkBox_perspective->isChecked();
    settings.isNativeProportions = ui->checkBox_proportions->isChecked();
    return settings;
}

void SettingsWidgetCommon::on_pushButton_colorX_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_colorX->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_colorX->setPalette(palette);
}

void SettingsWidgetCommon::on_pushButton_colorY_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_colorY->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_colorY->setPalette(palette);
}

void SettingsWidgetCommon::on_pushButton_colorZ_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_colorZ->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_colorZ->setPalette(palette);
}

void SettingsWidgetCommon::on_pushButton_configFile_clicked()
{
    QFileDialog dialog;
    ui->lineEdit_configFile->setText(dialog.getOpenFileName());
}

void SettingsWidgetCommon::on_pushButton_isonetColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_isonetColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_isonetColor->setPalette(palette);
}

void SettingsWidgetCommon::on_checkBox_isonetEnabled_clicked()
{
    if (ui->checkBox_isonetEnabled->isChecked()) {
        ui->comboBox_isolinePeriodicy->setEnabled(true);
        ui->spinBox_isonetWidth->setEnabled(true);
        ui->pushButton_isonetColor->setEnabled(true);
    } else {
        ui->comboBox_isolinePeriodicy->setEnabled(false);
        ui->spinBox_isonetWidth->setEnabled(false);
        ui->pushButton_isonetColor->setEnabled(false);
    }
}

void SettingsWidgetCommon::on_checkBox_timeEnabled_clicked()
{
    if (ui->checkBox_timeEnabled->isChecked()) {
        ui->lineEdit_timeVariableName->setEnabled(true);
        ui->spinBox_timeStep->setEnabled(true);
    } else {
        ui->lineEdit_timeVariableName->setEnabled(false);
        ui->spinBox_timeStep->setEnabled(false);
    }
}


void SettingsWidgetCommon::on_pushButton_netColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_netColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_netColor->setPalette(palette);
}

void SettingsWidgetCommon::on_checkBox_netEnabled_clicked()
{
    if (ui->checkBox_netEnabled->isChecked()) {
        ui->spinBox_netWidth->setEnabled(true);
        ui->pushButton_netColor->setEnabled(true);
    } else {
        ui->spinBox_netWidth->setEnabled(false);
        ui->pushButton_netColor->setEnabled(false);
    }
}
