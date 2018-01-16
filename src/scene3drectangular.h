#ifndef SCENE3DRECTANGULAR_H
#define SCENE3DRECTANGULAR_H

#include <scene3d.h>

class Scene3DRectangular : public Scene3D
{
public:
    Scene3DRectangular(QWidget *parent = nullptr);
    void zoomIn(float value) {rangeX /= value; rangeY /= value; rangeZ /= value; }
    void zoomOut(float value) {rangeX *= value; rangeY *= value; rangeZ *= value; }
    QVector<double> axisZPoints() const;
    void setSurfaceQuality(uint quality);

protected:
    double rangeX, rangeY, rangeZ;
    double centerX, centerY, centerZ;

    int xPolygonNum, yPolygonNum;

    void updateSurfaceBase();
    void glTransformations();
    void drawCentralAxis();
    virtual uint surfaceVertexNumber() const {return (xPolygonNum + 1) * (yPolygonNum + 1); }
    virtual uint surfacePolygonNumber() const {return xPolygonNum * yPolygonNum; }
};

#endif // SCENE3DRECTANGULAR_H
