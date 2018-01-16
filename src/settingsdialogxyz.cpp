#include "settingsdialogxyz.h"
#include "ui_settingsdialogxyz.h"
#include <scene3d.h>

SettingsDialogXYZ::SettingsDialogXYZ(SettingsXYZ sets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialogXYZ)
{
    ui->setupUi(this);

    setMaximumSize(width(), height());
    setMinimumSize(width(), height());
    commonSettingsWidget = new SettingsWidgetCommon(sets.common, this);
    commonSettingsWidget->setGeometry(0, 0, commonSettingsWidget->width(),
                                      commonSettingsWidget->height());
    this->setModal(true);
    ui->spinBox_centerX->setValue(sets.centerX);
    ui->spinBox_centerY->setValue(sets.centerY);
    ui->spinBox_centerZ->setValue(sets.centerZ);
    ui->checkBox_surfaceEnabled->setChecked(sets.isSurfaceEnable);
    ui->spinBox_rangeX->setValue(sets.rangeX);
    ui->spinBox_rangeY->setValue(sets.rangeY);
    ui->spinBox_rangeZ->setValue(sets.rangeZ);
    QPalette palette = ui->label_surfaceBottomColor->palette();
    palette.setColor(QPalette::Background, sets.surfaceBottomColor);
    ui->label_surfaceBottomColor->setPalette(palette);
    palette = ui->label_surfaceTopColor->palette();
    palette.setColor(QPalette::Background, sets.surfaceTopColor);
    ui->label_surfaceTopColor->setPalette(palette);
    palette = ui->label_surfaceMiddleColor->palette();
    palette.setColor(QPalette::Background, sets.surfaceMiddleColor);
    ui->label_surfaceMiddleColor->setPalette(palette);
    ui->lineEdit_nameX->setText(sets.xName);
    ui->lineEdit_nameY->setText(sets.yName);
    switch(sets.netXPeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netXPeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netXPeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netXPeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netXPeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netXPeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netXPeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netXPeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netXPeriodicy->setCurrentIndex(7); break;
    }
    switch(sets.netYPeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netYPeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netYPeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netYPeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netYPeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netYPeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netYPeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netYPeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netYPeriodicy->setCurrentIndex(7); break;
    }
}

SettingsDialogXYZ::~SettingsDialogXYZ()
{
    delete ui;
    delete commonSettingsWidget;
}

SettingsXYZ SettingsDialogXYZ::getSettings() const
{
    SettingsXYZ sets;
    sets.common = commonSettingsWidget->getSettings();
    sets.centerX = ui->spinBox_centerX->value();
    sets.centerY = ui->spinBox_centerY->value();
    sets.centerZ = ui->spinBox_centerZ->value();
    sets.isSurfaceEnable = ui->checkBox_surfaceEnabled->isChecked();
    sets.rangeX = ui->spinBox_rangeX->value();
    sets.rangeY = ui->spinBox_rangeY->value();
    sets.rangeZ = ui->spinBox_rangeZ->value();
    sets.surfaceBottomColor = ui->label_surfaceBottomColor->palette().background().color();
    sets.surfaceMiddleColor = ui->label_surfaceMiddleColor->palette().background().color();
    sets.surfaceTopColor = ui->label_surfaceTopColor->palette().background().color();
    sets.xName = ui->lineEdit_nameX->text();
    sets.yName = ui->lineEdit_nameY->text();
    switch(ui->comboBox_netXPeriodicy->currentIndex()) {
    case 0: sets.netXPeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netXPeriodicity = Scene3D::LOW; break;
    case 2: sets.netXPeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netXPeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netXPeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netXPeriodicity = Scene3D::HIGH; break;
    case 6: sets.netXPeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netXPeriodicity = Scene3D::ULTRA_HIGH; break;
    }
    switch(ui->comboBox_netYPeriodicy->currentIndex()) {
    case 0: sets.netYPeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netYPeriodicity = Scene3D::LOW; break;
    case 2: sets.netYPeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netYPeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netYPeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netYPeriodicity = Scene3D::HIGH; break;
    case 6: sets.netYPeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netYPeriodicity = Scene3D::ULTRA_HIGH; break;
    }

    return sets;
}

void SettingsDialogXYZ::on_pushButton_clicked()
{
    this->accept();
}

void SettingsDialogXYZ::on_pushButton_surfaceTopColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceTopColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceTopColor->setPalette(palette);
}

void SettingsDialogXYZ::on_pushButton_surfaceMiddleColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceMiddleColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceMiddleColor->setPalette(palette);
}

void SettingsDialogXYZ::on_pushButton_surfaceBottomColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceBottomColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceBottomColor->setPalette(palette);
}

void SettingsDialogXYZ::on_pushButton_surfaceMiddleColorAuto_clicked()
{
    QPalette palette = ui->label_surfaceMiddleColor->palette();
    QColor topColor = ui->label_surfaceTopColor->palette().background().color();
    QColor bottomColor = ui->label_surfaceBottomColor->palette().background().color();
    palette.setColor(QPalette::Background, QColor((topColor.red() + bottomColor.red()) / 2,
                                                  (topColor.green() + bottomColor.green()) / 2,
                                                  (topColor.blue() + bottomColor.blue()) / 2));
    ui->label_surfaceMiddleColor->setPalette(palette);
}

void SettingsDialogXYZ::on_checkBox_surfaceEnabled_clicked()
{
    if (ui->checkBox_surfaceEnabled->isChecked()) {
        ui->pushButton_surfaceBottomColor->setEnabled(true);
        ui->pushButton_surfaceMiddleColor->setEnabled(true);
        ui->pushButton_surfaceTopColor->setEnabled(true);
        ui->pushButton_surfaceMiddleColorAuto->setEnabled(true);
    } else {
        ui->pushButton_surfaceBottomColor->setEnabled(false);
        ui->pushButton_surfaceMiddleColor->setEnabled(false);
        ui->pushButton_surfaceTopColor->setEnabled(false);
        ui->pushButton_surfaceMiddleColorAuto->setEnabled(false);
    }
}
