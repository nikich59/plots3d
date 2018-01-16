#ifndef SCENE3DPOLAR_H
#define SCENE3DPOLAR_H

#include <scene3d.h>
#include <settingsdialogpolar.h>

class Scene3DPolar : public Scene3D
{
public:
    Scene3DPolar(QWidget *parent = nullptr);
    void setString(const QString &string) {function.setString(string); }
    void setVariableValue(const QString &name, double value) {
        function.setVariableValue(name, value); }
    void setNetRPeriodicity(uint periodicity);
    void setNetPhiPeriodicity(uint periodicity);
    QString getString() const;
    void drawLegend(QPainter &painter);
    SettingsPolar getSettings() const;
    QVector<double> axisXPoints() const;
    QVector<double> axisYPoints() const;
    QVector<double> axisZPoints() const;
    void zoomIn(float value) {rangeR /= value; rangeR /= value; rangeZ /= value; }
    void zoomOut(float value) {rangeR *= value; rangeR *= value; rangeZ *= value; }
    void setSurfaceQuality(uint quality);

private:
    QFunction<double> function;
    QOperationCompiler<double> compiler;
    QString rName, phiName;
    uint netRMin, netPhi;
    uint netRPeriodicity, netPhiPeriodicity;
    QColor surfaceBottomColor;
    QColor surfaceMiddleColor;
    QColor surfaceTopColor;
    QVector<GLfloat> vertexInPolar;
    double rangeR, rangeZ;
    double centerZ;
    int rPolygonNum;

    uint surfacePolygonNumber() const {return 0; }
    uint surfaceVertexNumber() const {return 0; }
    void updateTime();
    void updateSurface();
    void updateSurfaceBase();
    void updateNetBase();
    void updateNet();
    void runSettings();
    void runArguments();
    void drawCentralAxis();
    void drawBoundingAxis();
    void glTransformations();
};

#endif // SCENE3DPOLAR_H
