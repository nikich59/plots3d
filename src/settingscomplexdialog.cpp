#include "settingscomplexdialog.h"
#include "ui_settingscomplexdialog.h"
#include <scene3d.h>

SettingsComplexDialog::SettingsComplexDialog(const SettingsComplex &sets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsComplexDialog)
{
    ui->setupUi(this);

    setMaximumSize(width(), height());
    setMinimumSize(width(), height());
    commonSettingsWidget = new SettingsWidgetCommon(sets.common, this);
    commonSettingsWidget->setGeometry(0, 0, commonSettingsWidget->width(),
                                      commonSettingsWidget->height());

    ui->spinBox_centerX->setValue(sets.centerX);
    ui->spinBox_centerY->setValue(sets.centerY);
    ui->spinBox_centerZ->setValue(sets.centerZ);
    ui->spinBox_rangeX->setValue(sets.rangeX);
    ui->spinBox_rangeY->setValue(sets.rangeY);
    ui->spinBox_rangeZ->setValue(sets.rangeZ);
    ui->checkBox_surfaceEnabled->setChecked(sets.isSurfaceEnable);
    QPalette palette = ui->label_surfaceColor_0->palette();
    palette.setColor(QPalette::Background, sets.surfaceColor_0);
    ui->label_surfaceColor_0->setPalette(palette);
    palette = ui->label_surfaceColor_Pi_2->palette();
    palette.setColor(QPalette::Background, sets.surfaceColor_Pi_2);
    ui->label_surfaceColor_Pi_2->setPalette(palette);
    palette = ui->label_surfaceColor_pi->palette();
    palette.setColor(QPalette::Background, sets.surfaceColor_Pi);
    ui->label_surfaceColor_pi->setPalette(palette);
    palette = ui->label_surfaceColor_3_pi_2->palette();
    palette.setColor(QPalette::Background, sets.surfaceColor_3_Pi_2);
    ui->label_surfaceColor_3_pi_2->setPalette(palette);
    ui->lineEdit_varName->setText(sets.varName);
    switch(sets.netRePeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netRePeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netRePeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netRePeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netRePeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netRePeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netRePeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netRePeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netRePeriodicy->setCurrentIndex(7); break;
    }
    switch(sets.netImPeriodicity) {
    case Scene3D::VERY_LOW: ui->comboBox_netImPeriodicy->setCurrentIndex(0); break;
    case Scene3D::LOW: ui->comboBox_netImPeriodicy->setCurrentIndex(1); break;
    case Scene3D::DECREASED: ui->comboBox_netImPeriodicy->setCurrentIndex(2); break;
    case Scene3D::MIDDLE: ui->comboBox_netImPeriodicy->setCurrentIndex(3); break;
    case Scene3D::INCREASED: ui->comboBox_netImPeriodicy->setCurrentIndex(4); break;
    case Scene3D::HIGH: ui->comboBox_netImPeriodicy->setCurrentIndex(5); break;
    case Scene3D::VERY_HIGH: ui->comboBox_netImPeriodicy->setCurrentIndex(6); break;
    case Scene3D::ULTRA_HIGH: ui->comboBox_netImPeriodicy->setCurrentIndex(7); break;
    }
}

SettingsComplexDialog::~SettingsComplexDialog()
{
    delete ui;
    delete commonSettingsWidget;
}

SettingsComplex SettingsComplexDialog::getSettings() const
{
    SettingsComplex sets;
    sets.common = commonSettingsWidget->getSettings();
    sets.centerX = ui->spinBox_centerX->value();
    sets.centerY = ui->spinBox_centerY->value();
    sets.centerZ = ui->spinBox_centerZ->value();
    sets.isSurfaceEnable = ui->checkBox_surfaceEnabled->isChecked();
    sets.rangeX = ui->spinBox_rangeX->value();
    sets.rangeY = ui->spinBox_rangeY->value();
    sets.rangeZ = ui->spinBox_rangeZ->value();
    sets.surfaceColor_0 = ui->label_surfaceColor_0->palette().background().color();
    sets.surfaceColor_Pi_2 = ui->label_surfaceColor_Pi_2->palette().background().color();
    sets.surfaceColor_Pi = ui->label_surfaceColor_pi->palette().background().color();
    sets.surfaceColor_3_Pi_2 = ui->label_surfaceColor_3_pi_2->palette().background().color();
    sets.varName = ui->lineEdit_varName->text();
    switch(ui->comboBox_netRePeriodicy->currentIndex()) {
    case 0: sets.netRePeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netRePeriodicity = Scene3D::LOW; break;
    case 2: sets.netRePeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netRePeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netRePeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netRePeriodicity = Scene3D::HIGH; break;
    case 6: sets.netRePeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netRePeriodicity = Scene3D::ULTRA_HIGH; break;
    }
    switch(ui->comboBox_netImPeriodicy->currentIndex()) {
    case 0: sets.netImPeriodicity = Scene3D::VERY_LOW; break;
    case 1: sets.netImPeriodicity = Scene3D::LOW; break;
    case 2: sets.netImPeriodicity = Scene3D::DECREASED; break;
    case 3: sets.netImPeriodicity = Scene3D::MIDDLE; break;
    case 4: sets.netImPeriodicity = Scene3D::INCREASED; break;
    case 5: sets.netImPeriodicity = Scene3D::HIGH; break;
    case 6: sets.netImPeriodicity = Scene3D::VERY_HIGH; break;
    case 7: sets.netImPeriodicity = Scene3D::ULTRA_HIGH; break;
    }

    return sets;
}

void SettingsComplexDialog::on_checkBox_surfaceEnabled_clicked()
{
    if (ui->checkBox_surfaceEnabled->isChecked()) {
        ui->pushButton_surfaceColor_0->setEnabled(true);
        ui->pushButton_surfaceColor_Pi_2->setEnabled(true);
        ui->pushButton_surfaceColor_Pi->setEnabled(true);
        ui->pushButton_surfaceColor_3_Pi_2->setEnabled(true);
    } else {
        ui->pushButton_surfaceColor_0->setEnabled(false);
        ui->pushButton_surfaceColor_Pi_2->setEnabled(false);
        ui->pushButton_surfaceColor_Pi->setEnabled(false);
        ui->pushButton_surfaceColor_3_Pi_2->setEnabled(false);
    }
}

void SettingsComplexDialog::on_pushButton_clicked()
{
    this->accept();
}

void SettingsComplexDialog::on_pushButton_surfaceColor_0_clicked()
{
    QColorDialog dialog;
    QPalette palette = ui->label_surfaceColor_0->palette();
    palette.setColor(QPalette::Background, dialog.getColor(palette.background().color()));
    ui->label_surfaceColor_0->setPalette(palette);
}

void SettingsComplexDialog::on_pushButton_surfaceColor_Pi_2_clicked()
{
    QColorDialog dialog;
    QPalette palette = ui->label_surfaceColor_Pi_2->palette();
    palette.setColor(QPalette::Background, dialog.getColor(palette.background().color()));
    ui->label_surfaceColor_Pi_2->setPalette(palette);
}

void SettingsComplexDialog::on_pushButton_surfaceColor_Pi_clicked()
{
    QColorDialog dialog;
    QPalette palette = ui->label_surfaceColor_pi->palette();
    palette.setColor(QPalette::Background, dialog.getColor(palette.background().color()));
    ui->label_surfaceColor_pi->setPalette(palette);
}

void SettingsComplexDialog::on_pushButton_surfaceColor_3_Pi_2_clicked()
{
    QColorDialog dialog;
    QPalette palette = ui->label_surfaceColor_3_pi_2->palette();
    palette.setColor(QPalette::Background, dialog.getColor(palette.background().color()));
    ui->label_surfaceColor_3_pi_2->setPalette(palette);
}
