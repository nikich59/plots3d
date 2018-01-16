#ifndef SCENE3DCOMPLEX_H
#define SCENE3DCOMPLEX_H

#include <scene3drectangular.h>
#include <settingscomplexdialog.h>

class Scene3DComplex : public Scene3DRectangular
{
public:
    Scene3DComplex(QWidget *parent = nullptr);
    void setString(const QString &string);
    QString getString() const {return function.getString(); }
    void setVariableValue(const QString &name, double value) {
        function.setVariableValue(name, value); }
    void setNetRePeriodicity(uint periodicity);
    void setNetImPeriodicity(uint periodicity);
    SettingsComplex getSettings() const;
    void drawLegend(QPainter &painter);
    virtual QVector<double> axisXPoints() const;
    virtual QVector<double> axisYPoints() const;

private:
    QFunction<Complex> function;
    QOperationCompiler<Complex> compiler;
    QString varName;
    uint netReMin, netImMin;
    uint netRePeriodicity, netImPeriodicity;
    QColor surfaceColor_0;
    QColor surfaceColor_Pi_2;
    QColor surfaceColor_Pi;
    QColor surfaceColor_3_Pi_2;
    uint netBaseReNum, netBaseImNum, netBaseZNum;

    void updateTime();
    void updateSurface();
    void updateNetBase();
    void updateNet();
    void drawNet() const;
    void runSettings();
    void runArguments();
    void drawBoundingAxis();
};

#endif // SCENE3DCOMPLEX_H
