#ifndef SETTINGSDIALOGXYZ_H
#define SETTINGSDIALOGXYZ_H

#include <QDialog>
#include <settingswidgetcommon.h>

namespace Ui {
class SettingsDialogXYZ;
}

struct SettingsXYZ
{
    SettingsCommon common;
    double centerX, centerY, centerZ;
    double rangeX, rangeY, rangeZ;
    bool isSurfaceEnable;
    QColor surfaceBottomColor;
    QColor surfaceMiddleColor;
    QColor surfaceTopColor;
    QString xName, yName;
    //uint netXMin, netYMin;
    uint netXPeriodicity, netYPeriodicity;
};

class SettingsDialogXYZ : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialogXYZ(SettingsXYZ sets, QWidget *parent = 0);
    ~SettingsDialogXYZ();
    SettingsXYZ getSettings() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_surfaceTopColor_clicked();

    void on_pushButton_surfaceMiddleColor_clicked();

    void on_pushButton_surfaceBottomColor_clicked();

    void on_pushButton_surfaceMiddleColorAuto_clicked();

    void on_checkBox_surfaceEnabled_clicked();

private:
    Ui::SettingsDialogXYZ *ui;
    SettingsWidgetCommon *commonSettingsWidget;
};

#endif // SETTINGSDIALOGXYZ_H
