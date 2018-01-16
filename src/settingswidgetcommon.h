#ifndef SETTINGSWIDGETCOMMON_H
#define SETTINGSWIDGETCOMMON_H

#include <QWidget>
#include <QColorDialog>
#include <GL/gl.h>
#include <QTime>
#include <QFileDialog>
#include <qoperation.h>

namespace Ui {
class SettingsWidgetCommon;
}

struct SettingsCommon
{
    QString funcString;
    uint axis;
    QColor axis1Color, axis2Color, axis3Color;
    bool isNetEnable;
    float netWidth;
    QColor netColor;
    bool isIsonetEnable;
    GLfloat isonetWidth;
    uint isolinePeriodicity;
    QColor isonetColor;
    uint surfaceQuality;
    bool isActivatedTime;
    QString timeName;
    double timeStep;
    float radius;
    double scaleRate; // if > 1 then straight scaling otherwise it`s inversed
    int sceneMoveMouseButton;
    double verticalExtension;
    bool isShowedLegend;
    double legendSizeRatio;
    float legendBackOpacity;
    QString contextFileName;
    bool isNativeProportions;
    bool isPerspectiveEnabled;
};

class SettingsWidgetCommon : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidgetCommon(SettingsCommon sets, QWidget *parent = 0);
    ~SettingsWidgetCommon();
    SettingsCommon getSettings() const;

private slots:
    void on_pushButton_colorX_clicked();

    void on_pushButton_configFile_clicked();

    void on_pushButton_isonetColor_clicked();

    void on_checkBox_isonetEnabled_clicked();

    void on_checkBox_timeEnabled_clicked();

    void on_pushButton_colorY_clicked();

    void on_pushButton_colorZ_clicked();

    void on_pushButton_netColor_clicked();

    void on_checkBox_netEnabled_clicked();

private:
    Ui::SettingsWidgetCommon *ui;
};

#endif // SETTINGSWIDGETCOMMON_H
