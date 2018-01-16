#include "settingsdialogpolar.h"
#include "ui_settingsdialogpolar.h"
#include <scene3d.h>

SettingsDialogPolar::SettingsDialogPolar(const SettingsPolar &sets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialogPolar)
{
    ui->setupUi(this);

    setMaximumSize(width(), height());
    setMinimumSize(width(), height());
    commonSettingsWidget = new SettingsWidgetCommon(sets.common, this);
    commonSettingsWidget->setGeometry(0, 0, commonSettingsWidget->width(),
                                      commonSettingsWidget->height());
    this->setModal(true);
    ui->spinBox_centerZ->setValue(sets.centerZ);
    ui->checkBox_surfaceEnabled->setChecked(sets.isSurfaceEnable);
    ui->spinBox_rangeX->setValue(sets.rangeR);
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
    ui->lineEdit_nameX->setText(sets.rName);
    ui->lineEdit_nameY->setText(sets.phiName);
    switch(sets.netRPeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netRPeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netRPeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netRPeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netRPeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netRPeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netRPeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netRPeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netRPeriodicy->setCurrentIndex(7); break;
    }
    switch(sets.netPhiPeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netPhiPeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netPhiPeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netPhiPeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netPhiPeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netPhiPeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netPhiPeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netPhiPeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netPhiPeriodicy->setCurrentIndex(7); break;
    }
}

SettingsDialogPolar::~SettingsDialogPolar()
{
    delete ui;
    delete commonSettingsWidget;
}

SettingsPolar SettingsDialogPolar::getSettings() const
{
    SettingsPolar sets;
    sets.common = commonSettingsWidget->getSettings();
    sets.centerZ = ui->spinBox_centerZ->value();
    sets.isSurfaceEnable = ui->checkBox_surfaceEnabled->isChecked();
    sets.rangeR = ui->spinBox_rangeX->value();
    sets.rangeZ = ui->spinBox_rangeZ->value();
    sets.surfaceBottomColor = ui->label_surfaceBottomColor->palette().background().color();
    sets.surfaceMiddleColor = ui->label_surfaceMiddleColor->palette().background().color();
    sets.surfaceTopColor = ui->label_surfaceTopColor->palette().background().color();
    sets.rName = ui->lineEdit_nameX->text();
    sets.phiName = ui->lineEdit_nameY->text();
    switch(ui->comboBox_netRPeriodicy->currentIndex()) {
    case 0: sets.netRPeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netRPeriodicity = Scene3D::LOW; break;
    case 2: sets.netRPeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netRPeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netRPeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netRPeriodicity = Scene3D::HIGH; break;
    case 6: sets.netRPeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netRPeriodicity = Scene3D::ULTRA_HIGH; break;
    }
    switch(ui->comboBox_netPhiPeriodicy->currentIndex()) {
    case 0: sets.netPhiPeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netPhiPeriodicity = Scene3D::LOW; break;
    case 2: sets.netPhiPeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netPhiPeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netPhiPeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netPhiPeriodicity = Scene3D::HIGH; break;
    case 6: sets.netPhiPeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netPhiPeriodicity = Scene3D::ULTRA_HIGH; break;
    }

    return sets;
}

void SettingsDialogPolar::on_pushButton_clicked()
{
    this->accept();
}

void SettingsDialogPolar::on_pushButton_surfaceTopColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceTopColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceTopColor->setPalette(palette);
}

void SettingsDialogPolar::on_pushButton_surfaceMiddleColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceMiddleColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceMiddleColor->setPalette(palette);
}

void SettingsDialogPolar::on_pushButton_surfaceBottomColor_clicked()
{
    QColorDialog colorDialog;
    QPalette palette = ui->label_surfaceBottomColor->palette();
    palette.setColor(QPalette::Background, colorDialog.getColor(palette.background().color()));
    ui->label_surfaceBottomColor->setPalette(palette);
}

void SettingsDialogPolar::on_pushButton_surfaceMiddleColorAuto_clicked()
{
    QPalette palette = ui->label_surfaceMiddleColor->palette();
    QColor topColor = ui->label_surfaceTopColor->palette().background().color();
    QColor bottomColor = ui->label_surfaceBottomColor->palette().background().color();
    palette.setColor(QPalette::Background, QColor((topColor.red() + bottomColor.red()) / 2,
                                                  (topColor.green() + bottomColor.green()) / 2,
                                                  (topColor.blue() + bottomColor.blue()) / 2));
    ui->label_surfaceMiddleColor->setPalette(palette);
}

void SettingsDialogPolar::on_checkBox_surfaceEnabled_clicked()
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
