#ifndef SETTINGSDIALOGPOLAR_H
#define SETTINGSDIALOGPOLAR_H

#include <QDialog>
#include <settingswidgetcommon.h>

namespace Ui {
class SettingsDialogPolar;
}

struct SettingsPolar
{
    SettingsCommon common;
    QString rName, phiName;
    uint netRPeriodicity, netPhiPeriodicity;
    QColor surfaceBottomColor;
    QColor surfaceMiddleColor;
    QColor surfaceTopColor;
    double centerZ;
    double rangeR, rangeZ;
    bool isSurfaceEnable;
};

class SettingsDialogPolar : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialogPolar(const SettingsPolar &sets, QWidget *parent = 0);
    ~SettingsDialogPolar();
    SettingsPolar getSettings() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_surfaceTopColor_clicked();

    void on_pushButton_surfaceMiddleColor_clicked();

    void on_pushButton_surfaceBottomColor_clicked();

    void on_pushButton_surfaceMiddleColorAuto_clicked();

    void on_checkBox_surfaceEnabled_clicked();

private:
    Ui::SettingsDialogPolar *ui;
    SettingsWidgetCommon *commonSettingsWidget;
};

#endif // SETTINGSDIALOGPOLAR_H
