#include "scene3d.h"

Scene3D::Scene3D(QWidget *parent) : QGLWidget(parent)
{
    setAutoFillBackground(false);

    setMouseTracking(true);
    timerId = -1;
    setDefaultCommon();
}

void Scene3D::setDefaultCommon()
{
    scaleRate = 1.1;
    sceneMoveMouseButton = Qt::LeftButton;
    timeName = QString("t");
    timeStep = 50;
    verticalExtension = 1.0;
    legendSizeRatio = 0.5;
    legendBackOpacity = 0.5;
    isSurfaceEnable = true;
    isNetEnable = true;
    isIsonetEnable = true;
    isActivatedTime = false;
    isNativeProportions = true;
    isPerspectiveEnabled = true;
    isShowedLegend = true;
    axis = CENTRAL_AXIS;
    radius = 1.0;
    isonetWidth = 1.0;
    netWidth = 1.0;
    isonetColor = Qt::white;
    netColor = Qt::black;
    axisLengthRatio = 0.2;
    setAxisColor(Qt::red, Qt::green, Qt::blue);
    setIsolinePeriodicy(DECREASED);
    setDefaultRotation();
}

void Scene3D::setDefaultRotation()
{
    xRot = -M_PI_4;
    yRot = 0.0;
    zRot = 0.0;
    xLookAroundRot = 0.0;
    yLookAroundRot = 0.0;
    zLookAroundRot = 0.0;
}

void Scene3D::setIsolinePeriodicy(uint periodicy)
{
    switch(periodicy) {
    case VERY_LOW: isolineMin = 4; isolinePeriodicity = periodicy; break;
    case LOW: isolineMin = 6; isolinePeriodicity = periodicy; break;
    case DECREASED: isolineMin = 9; isolinePeriodicity = periodicy; break;
    case MIDDLE: isolineMin = 12; isolinePeriodicity = periodicy; break;
    case INCREASED: isolineMin = 15; isolinePeriodicity = periodicy; break;
    case HIGH: isolineMin = 20; isolinePeriodicity = periodicy; break;
    case VERY_HIGH: isolineMin = 25; isolinePeriodicity = periodicy; break;
    case ULTRA_HIGH: isolineMin = 32; isolinePeriodicity = periodicy; break;
    }
}

void Scene3D::startSelfUpdating(double timeStep)
{
    if (timerId != -1)
        killTimer(timerId);
    this->timeStep = timeStep;
    timerId = this->startTimer((int)round((double)timeStep * 1000.0));
    isActivatedTime = true;
}

SettingsCommon Scene3D::getCommonSettings() const
{
    SettingsCommon sets;
    sets.funcString = this->getString();
    sets.axis = axis;
    sets.axis1Color = axis1Color;
    sets.axis2Color = axis2Color;
    sets.axis3Color = axis3Color;
    sets.contextFileName = contextFileName;
    sets.isActivatedTime = isActivatedTime;
    sets.isIsonetEnable = isIsonetEnable;
    sets.isNetEnable = isNetEnable;
    sets.isonetColor = isonetColor;
    sets.isonetWidth = isonetWidth;
    sets.netColor = netColor;
    sets.netWidth = netWidth;
    sets.radius = radius;
    sets.scaleRate = scaleRate;
    sets.sceneMoveMouseButton = sceneMoveMouseButton;
    sets.timeStep = timeStep;
    sets.timeName = timeName;
    sets.isolinePeriodicity = isolinePeriodicity;
    sets.verticalExtension = verticalExtension;
    sets.isShowedLegend = isShowedLegend;
    sets.legendSizeRatio = legendSizeRatio;
    sets.legendBackOpacity = legendBackOpacity;
    sets.isPerspectiveEnabled = isPerspectiveEnabled;
    sets.isNativeProportions = isNativeProportions;
    sets.surfaceQuality = surfaceQuality;
    return sets;
}

void Scene3D::setCommonSettings(const SettingsCommon &sets)
{
    this->setString(sets.funcString);
    axis = sets.axis;
    axis1Color = sets.axis1Color;
    axis2Color = sets.axis2Color;
    axis3Color = sets.axis3Color;
    contextFileName = sets.contextFileName;
    isActivatedTime = sets.isActivatedTime;
    timeStep = sets.timeStep;
    if (isActivatedTime)
        startSelfUpdating(timeStep);
    else
        stopSelfUpdating();
    isIsonetEnable = sets.isIsonetEnable;
    isNetEnable = sets.isNetEnable;
    netColor = sets.netColor;
    netWidth = sets.netWidth;
    isonetColor = sets.isonetColor;
    isonetWidth = sets.isonetWidth;
    radius = sets.radius;
    scaleRate = sets.scaleRate;
    sceneMoveMouseButton = sets.sceneMoveMouseButton;
    startTime = QTime::currentTime();
    timeName = sets.timeName;
    setIsolinePeriodicy(sets.isolinePeriodicity);
    verticalExtension = sets.verticalExtension;
    isShowedLegend = sets.isShowedLegend;
    legendSizeRatio = sets.legendSizeRatio;
    legendBackOpacity = sets.legendBackOpacity;
    isPerspectiveEnabled = sets.isPerspectiveEnabled;
    isNativeProportions = sets.isNativeProportions;
    setSurfaceQuality(sets.surfaceQuality);
}

void Scene3D::draw()
{
    if (isSurfaceEnable) {
        drawSurface();
    }
    if (isNetEnable) {
        drawNet();
    }
    if (isIsonetEnable) {
        drawIsonet();
    }
    drawAxis();
}

void Scene3D::updateScene()
{
    updateTime();
    if (isSurfaceEnable || isIsonetEnable) {
        updateSurface();
    }
    if (isNetEnable) {
        updateNet();
    }
    if (isIsonetEnable) {
        updateIsoline();
    }
}

void Scene3D::updateBase()
{
    updateSurfaceBase();
    updateNetBase();
    updateScene();
    startTime = QTime::currentTime();
}

void Scene3D::timerEvent(QTimerEvent *)
{
    updateScene();
    repaint();
}

void Scene3D::wheelEvent(QWheelEvent *event)
{
    if (event->buttons() == Qt::NoButton) {
        if (event->delta() > 0)
            zoomIn(scaleRate);
        else
            zoomOut(scaleRate);
        updateBase();
        updateScene();
        repaint();
    }
    if (event->buttons() == sceneMoveMouseButton) {
        radius = (event->delta() > 0) ? radius / scaleRate : radius * scaleRate;
        repaint();
    }
}

void Scene3D::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::NoButton)
        this->setCursor(Qt::ArrowCursor);
    else if (event->buttons() == sceneMoveMouseButton)
        this->setCursor(Qt::ClosedHandCursor);
    else this->setCursor(Qt::ArrowCursor);

    if (event->buttons() == sceneMoveMouseButton) {
        setRot(xRot - M_PI * (float)(event->pos() - lastCursorPos).y() / this->height(),
               yRot,
               zRot + 2.0 * M_PI * (float)(event->pos() - lastCursorPos).x() / this->width());
        lastCursorPos = event->pos();
        repaint();
    }
}

void Scene3D::mousePressEvent(QMouseEvent *event)
{
    lastCursorPos = event->pos();
}

void Scene3D::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F:
        if (this->windowState() != Qt::WindowFullScreen)
            setWindowState(Qt::WindowFullScreen);
        else
            setWindowState(Qt::WindowMaximized);
        break;
    case Qt::Key_S: runSettings(); break;
    case Qt::Key_A: runArguments(); break;
    }
}

void Scene3D::paintEvent(QPaintEvent *)
{
    const double closest = 0.003;
    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    qglClearColor(Qt::white);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width(), height());

    GLfloat whratio;
    if (isNativeProportions)
        whratio = (GLfloat) this->width() / (GLfloat) this->height();
    else
        whratio = 1.0;
    if (isPerspectiveEnabled)
        glFrustum(-closest * whratio, closest * whratio, -closest, closest, closest, 10.0);
    else
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    this->glTransformations();

    draw();

    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    QPainter painter;
    painter.begin(this);
    if (isShowedLegend) {
        drawLegend(painter);
    }
    painter.end();
}

void Scene3D::closeEvent(QCloseEvent *event)
{
    delete this;
}

void Scene3D::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void Scene3D::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}


void Scene3D::drawSurface() const
{
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, surfaceVertex.data());
    glColorPointer(4, GL_FLOAT, 0, surfaceColor.data());
    glDrawElements(GL_QUADS, surfaceIndex.length(), GL_UNSIGNED_INT, surfaceIndex.data());
}

void Scene3D::drawNet() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, netVertex.data());
    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(netColor.redF(), netColor.greenF(), netColor.blueF());
    glLineWidth(netWidth);
    glDrawElements(GL_LINES, netIndex.length(), GL_UNSIGNED_INT, netIndex.data());
}

void Scene3D::updateIsoline()
{
#define err 0.0
    isolineIndex.clear();
    isolineVertex.clear();
    GLfloat p1x, p1y, p1z;
    GLfloat p2x, p2y, p2z;
    GLfloat p3x, p3y, p3z;
    GLfloat p4x, p4y, p4z;
    QVector<double> points = axisZPoints();
    double step = points.length() > 1 ? points[1] - points[0] : 0.0;
    long long min = round(points.first() / step);
    long long max = round(points.last() / step);
    long long delta = (max - min) / 2;
    min -= delta;
    max += delta;
    long long isolineNum1, isolineNum2, isolineNum3;
    long long isolineNumMin, isolineNumMax;
    GLfloat pointX, pointY, pointZ;

    int length = surfaceIndex.length() / 4;
    GLfloat *surfaceVertex = this->surfaceVertex.data();
    GLuint *surfaceIndex = this->surfaceIndex.data();
    for (int i = 0; i < length; i++) {
        p1x = surfaceVertex[3 * surfaceIndex[4 * i]];
        p1y = surfaceVertex[3 * surfaceIndex[4 * i] + 1];
        p1z = surfaceVertex[3 * surfaceIndex[4 * i] + 2];
        p2x = surfaceVertex[3 * surfaceIndex[4 * i + 1]];
        p2y = surfaceVertex[3 * surfaceIndex[4 * i + 1] + 1];
        p2z = surfaceVertex[3 * surfaceIndex[4 * i + 1] + 2];
        p3x = surfaceVertex[3 * surfaceIndex[4 * i + 2]];
        p3y = surfaceVertex[3 * surfaceIndex[4 * i + 2] + 1];
        p3z = surfaceVertex[3 * surfaceIndex[4 * i + 2] + 2];
        p4x = surfaceVertex[3 * surfaceIndex[4 * i + 3]];
        p4y = surfaceVertex[3 * surfaceIndex[4 * i + 3] + 1];
        p4z = surfaceVertex[3 * surfaceIndex[4 * i + 3] + 2];
        isolineNum1 = round(p1z / step - 0.5);
        isolineNum2 = round(p2z / step - 0.5);
        isolineNum3 = round(p3z / step - 0.5);
        if (isolineNum1 != isolineNum2 || isolineNum2 != isolineNum3) {
            isolineNumMin = std::min(isolineNum1, std::min(isolineNum2, isolineNum3));
            isolineNumMax = std::max(isolineNum1, std::max(isolineNum2, isolineNum3));
            if (isolineNumMin > max)
                continue;
            if (isolineNumMax < min)
                continue;
            if (isolineNumMin < min)
                isolineNumMin = min;
            if (isolineNumMax > max)
                isolineNumMax = max;
            for (long long i = isolineNumMin; i <= isolineNumMax; i++) {
                pointZ = (double)i * step;
                if ((pointZ - p1z) * (p2z - pointZ) >= err) {
                    if ((pointZ - p2z) * (p3z - pointZ) >= err) {
                        pointX = (pointZ - p1z) / (p2z - p1z) * (p2x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p2z - p1z) * (p2y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p2z) / (p3z - p2z) * (p3x - p2x) + p2x;
                        pointY = (pointZ - p2z) / (p3z - p2z) * (p3y - p2y) + p2y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    } else if ((pointZ - p1z) * (p3z - pointZ) >= 0.0) {
                        pointX = (pointZ - p1z) / (p2z - p1z) * (p2x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p2z - p1z) * (p2y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p1z) / (p3z - p1z) * (p3x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p3z - p1z) * (p3y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    }
                } else if ((pointZ - p2z) * (p3z - pointZ) >= err) {
                    if ((pointZ - p1z) * (p3z - pointZ) >= err) {
                        pointX = (pointZ - p3z) / (p2z - p3z) * (p2x - p3x) + p3x;
                        pointY = (pointZ - p3z) / (p2z - p3z) * (p2y - p3y) + p3y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p1z) / (p3z - p1z) * (p3x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p3z - p1z) * (p3y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    }
                }
            }
        }
        p2x = p4x;
        p2y = p4y;
        p2z = p4z;
        isolineNum2 = round(p2z / step - 0.5);
        if (!(isolineNum1 == isolineNum2 && isolineNum2 == isolineNum3)) {
            isolineNumMin = std::min(isolineNum1, std::min(isolineNum2, isolineNum3));
            isolineNumMax = std::max(isolineNum1, std::max(isolineNum2, isolineNum3));
            if (isolineNumMin > max)
                continue;
            if (isolineNumMax < min)
                continue;
            if (isolineNumMin < min)
                isolineNumMin = min;
            if (isolineNumMax > max)
                isolineNumMax = max;
            for (int i = isolineNumMin; i <= isolineNumMax; i++) {
                pointZ = (GLfloat)i * step;
                if ((pointZ - p1z) * (p2z - pointZ) >= err) {
                    if ((pointZ - p2z) * (p3z - pointZ) >= err) {
                        pointX = (pointZ - p1z) / (p2z - p1z) * (p2x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p2z - p1z) * (p2y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p2z) / (p3z - p2z) * (p3x - p2x) + p2x;
                        pointY = (pointZ - p2z) / (p3z - p2z) * (p3y - p2y) + p2y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    } else if ((pointZ - p1z) * (p3z - pointZ) >= 0.0) {
                        pointX = (pointZ - p1z) / (p2z - p1z) * (p2x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p2z - p1z) * (p2y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p1z) / (p3z - p1z) * (p3x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p3z - p1z) * (p3y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    }
                } else if ((pointZ - p2z) * (p3z - pointZ) >= err) {
                    if ((pointZ - p1z) * (p3z - pointZ) >= err) {
                        pointX = (pointZ - p3z) / (p2z - p3z) * (p2x - p3x) + p3x;
                        pointY = (pointZ - p3z) / (p2z - p3z) * (p2y - p3y) + p3y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        pointX = (pointZ - p1z) / (p3z - p1z) * (p3x - p1x) + p1x;
                        pointY = (pointZ - p1z) / (p3z - p1z) * (p3y - p1y) + p1y;
                        isolineVertex.push_back(pointX);
                        isolineVertex.push_back(pointY);
                        isolineVertex.push_back(pointZ);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 2);
                        isolineIndex.push_back(isolineVertex.length() / 3 - 1);
                    }
                }
            }
        }
    }
#undef err
}

void Scene3D::drawIsonet()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, isolineVertex.data());
    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(isonetColor.redF(), isonetColor.greenF(), isonetColor.blueF());
    glLineWidth(isonetWidth);
    glDrawElements(GL_LINES, isolineIndex.length(), GL_UNSIGNED_INT, isolineIndex.data());
}

void Scene3D::drawAxis()
{
    if (axis == CENTRAL_AXIS)
        drawCentralAxis();
    else if (axis == BOUNDING_AXIS || axis == BOUNDING_AXIS_CELLULAR)
        drawBoundingAxis();
}

QVector<double> Scene3D::axisXBasePoints(uint num) const
{
    QVector<double> points = axisXPoints();
    QVector<double> base;
    for (int i = 0; i < points.length(); i++) {
        if (i % (points.length() / num) == 0) {
            base.push_back(points[i]);
        }
    }
    return base;
}

QVector<double> Scene3D::axisYBasePoints(uint num) const
{
    QVector<double> points = axisYPoints();
    QVector<double> base;
    for (int i = 0; i < points.length(); i++) {
        if (i % (points.length() / num) == 0) {
            base.push_back(points[i]);
        }
    }
    return base;
}

QVector<double> Scene3D::axisZBasePoints(uint num) const
{
    QVector<double> points = axisZPoints();
    QVector<double> base;
    for (int i = 0; i < points.length(); i++) {
        if (i % (points.length() / num) == 0) {
            base.push_back(points[i]);
        }
    }
    return base;
}

QVector<double> Scene3D::axisPoints(double center, double range, int minNum) const
{
    if (range < 1e-125)
        return QVector<double>();
    double step = pow(10.0, ceil(log(range / minNum) / log(10.0)));
    if (range / step < minNum)
        step /= 2.0;
    if (range / step < minNum)
        step /= 2.5;
    if (range / step < minNum)
        step /= 2.0;
    double min = step * round((center - range / 2.0) / step + 0.5);
    double max = step * (round((center + range / 2.0) / step - 0.5) + 0.5);
    QVector<double> v;
    for (double i = min; i <= max; i += step)
        v.push_back(i);
    return v;
}
