// TRY THIS!!!
// 1) 20*sin(sqrt(x*x+y*y)+1/(sqrt(x*x+y*y)+1)-1-t)*(x*x+y*y<t*t)*(1+1/(sqrt(x*x+y*y)-1-t))^2/(x*x+y*y+5)
//


#ifndef SCENE3DXYZ_H
#define SCENE3DXYZ_H

#include <scene3drectangular.h>
#include <settingsdialogxyz.h>
#include <QPaintEvent>

class Scene3DXYZ : public Scene3DRectangular
{
public:
    Scene3DXYZ(QWidget *parent = nullptr);
    ~Scene3DXYZ();
    void setString(const QString &string);
    QString getString() const;
    void setVariableValue(const QString &name, double value) {
        function.setVariableValue(name, value); }
    void setNetXPeriodicity(uint periodicity);
    void setNetYPeriodicity(uint periodicity);
    SettingsXYZ getSettings() const;
    void drawLegend(QPainter &painter);
    virtual QVector<double> axisXPoints() const;
    virtual QVector<double> axisYPoints() const;

protected:
    QFunction<double> function;
    QOperationCompiler<double> compiler;
    QString xName, yName;
    uint netXMin, netYMin;
    uint netXPeriodicity, netYPeriodicity;
    uint netBaseXNum, netBaseYNum, netBaseZNum;
    QColor surfaceBottomColor;
    QColor surfaceMiddleColor;
    QColor surfaceTopColor;

    void updateTime();
    void updateSurface();
    void updateNetBase();
    void updateNet();
    void drawNet() const;
    void runSettings();
    void runArguments();
    void drawBoundingAxis();
    void glTransformations();
};

#endif // SCENE3DXYZ_H
