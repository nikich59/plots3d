#ifndef SETTINGSCOMPLEXDIALOG_H
#define SETTINGSCOMPLEXDIALOG_H

#include <QDialog>
#include <settingswidgetcommon.h>

namespace Ui {
class SettingsComplexDialog;
}

struct SettingsComplex
{
    SettingsCommon common;
    double centerX, centerY, centerZ;
    double rangeX, rangeY, rangeZ;
    bool isSurfaceEnable;
    QString varName;
    uint netRePeriodicity, netImPeriodicity;
    QColor surfaceColor_0;
    QColor surfaceColor_Pi_2;
    QColor surfaceColor_Pi;
    QColor surfaceColor_3_Pi_2;
};

class SettingsComplexDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsComplexDialog(const SettingsComplex &settings, QWidget *parent = 0);
    ~SettingsComplexDialog();
    SettingsComplex getSettings() const;

private slots:
    void on_checkBox_surfaceEnabled_clicked();

    void on_pushButton_clicked();

    void on_pushButton_surfaceColor_0_clicked();

    void on_pushButton_surfaceColor_Pi_2_clicked();

    void on_pushButton_surfaceColor_Pi_clicked();

    void on_pushButton_surfaceColor_3_Pi_2_clicked();

private:
    Ui::SettingsComplexDialog *ui;
    SettingsWidgetCommon *commonSettingsWidget;
};

#endif // SETTINGSCOMPLEXDIALOG_H
