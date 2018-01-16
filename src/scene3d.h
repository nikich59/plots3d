#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>
#include <QWheelEvent>
#include <qgl.h>
#include <qoperation.h>
#include <mathexpression.h>
#include <QLabel>
#include <GL/gl.h>
#include <QtOpenGL>
#include <stdlib.h>
#include <settingswidgetcommon.h>
#include <argumentsdialog.h>
#include <QtGui>
#include <QPainter>

class Scene3D : public QGLWidget
{
public:
    Scene3D(QWidget *parent = nullptr);
    virtual ~Scene3D() {}
    virtual void setString(const QString &string) = 0;
    virtual QString getString() const = 0;
    virtual void zoomIn(float value) = 0;
    virtual void zoomOut(float value) = 0;
    void setAxisColor(QColor axis1Color, QColor axis2Color, QColor axis3Color) {
        this->axis1Color = axis1Color; this->axis2Color = axis2Color; this->axis3Color =axis3Color;}
    virtual void setVariableValue(const QString &name, double value) = 0;
    void setRot(float rotX, float rotY, float rotZ) {xRot = rotX; yRot = rotY; zRot = rotZ; }

    void setContextFileName(const QString &fileName) {contextFileName = fileName; }

    virtual void setSurfaceQuality(uint quality) = 0;
    void activateTime(bool timeActivated) {isActivatedTime = timeActivated;
                                           startTime = QTime::currentTime(); }
    void setDefaultCommon();
    void setDefaultRotation();
    void setIsolinePeriodicy(uint periodicy);
    void startSelfUpdating(double timeStep);
    void stopSelfUpdating() {this->killTimer(timerId); isActivatedTime = false; timerId = -1;}

    SettingsCommon getCommonSettings() const;
    void setCommonSettings(const SettingsCommon &sets);

    void draw();
    void updateScene();
    void updateBase();

    virtual void timerEvent(QTimerEvent *);
    virtual void drawLegend(QPainter &painter) = 0;

public slots:
    virtual void wheelEvent(QWheelEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *) {}
    virtual void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    virtual void updateTime() = 0;
    virtual void runSettings() = 0;
    virtual void runArguments() = 0;

    int timerId;

    uint axis;
    QColor axis1Color, axis2Color, axis3Color;
    GLfloat axisLengthRatio;
    bool isNetEnable;
    float netWidth;
    QColor netColor;
    bool isIsonetEnable;
    QColor isonetColor;
    bool isSurfaceEnable;
    uint surfaceQuality;

    double verticalExtension;

    float xRot, yRot, zRot;
    float xLookAroundRot, yLookAroundRot, zLookAroundRot;
    float radius;


    QVector<GLfloat> surfaceVertex;
    QVector<GLuint> surfaceIndex;
    QVector<GLfloat> surfaceColor;

    QVector<GLfloat> netVertex;
    QVector<GLuint> netIndex;
    GLfloat isonetWidth;

    uint isolineMin;
    QVector<GLfloat> isolineVertex;
    QVector<GLuint> isolineIndex;
    uint isolinePeriodicity;

    bool isActivatedTime;
    QString timeName;
    QTime startTime;
    double timeStep;

    QString contextFileName;

    double scaleRate; // if > 1 then straight scaling otherwise it`s inversed

    QPoint lastCursorPos;

    int sceneMoveMouseButton;

    bool isShowedLegend;
    double legendSizeRatio;
    float legendBackOpacity;

    bool isNativeProportions;

    bool isPerspectiveEnabled;

    virtual void drawSurface() const;
    virtual void drawNet() const;
    virtual void updateSurfaceBase() = 0;
    virtual void updateSurface() = 0;
    virtual void updateNetBase() = 0;
    virtual void updateNet() = 0;
    virtual void updateIsoline();
    virtual void drawIsonet();
    virtual void drawCentralAxis() = 0;
    virtual void drawBoundingAxis() = 0;
    virtual void drawAxis();
    virtual QVector<double> axisPoints(double center, double range, int minNum) const;
    virtual QVector<double> axisXPoints() const = 0;
    virtual QVector<double> axisYPoints() const = 0;
    virtual QVector<double> axisZPoints() const = 0;
    virtual QVector<double> axisXBasePoints(uint num) const;
    virtual QVector<double> axisYBasePoints(uint num) const;
    virtual QVector<double> axisZBasePoints(uint num) const;
    virtual void glTransformations() = 0;

public:
    static const uint NO_AXIS = 0b1;
    static const uint CENTRAL_AXIS = 0b10;
    static const uint BOUNDING_AXIS = 0b100;
    static const uint BOUNDING_AXIS_CELLULAR = 0b1000;
    static const uint VERY_LOW = 1;
    static const uint LOW = 2;
    static const uint DECREASED = 3;
    static const uint MIDDLE = 4;
    static const uint INCREASED = 5;
    static const uint HIGH = 6;
    static const uint VERY_HIGH = 7;
    static const uint ULTRA_HIGH = 8;
};

#endif // SCENE3D_H
