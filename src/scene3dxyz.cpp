#include "scene3dxyz.h"

Scene3DXYZ::Scene3DXYZ(QWidget *parent) : Scene3DRectangular(parent)
{
    xName = "x";
    yName = "y";
    netBaseXNum = 5;
    netBaseYNum = 5;
    netBaseZNum = 5;
    setNetXPeriodicity(DECREASED);
    setNetYPeriodicity(DECREASED);
    surfaceBottomColor = Qt::gray;
    surfaceMiddleColor = Qt::gray;
    surfaceTopColor = Qt::gray;
    setString(QString("0"));
    updateBase();
    updateScene();
}

Scene3DXYZ::~Scene3DXYZ()
{

}

void Scene3DXYZ::setString(const QString &string)
{
    function.setString(string, compiler);
    updateScene();
    updateGL();
}

QString Scene3DXYZ::getString() const
{
    return function.getString();
}

void Scene3DXYZ::updateTime()
{
    if (isActivatedTime)
        function.setVariableValue(timeName, (double)startTime.msecsTo(QTime::currentTime())/1000.0);
}

void Scene3DXYZ::updateSurface()
{
    double *px = nullptr, *py = nullptr;
    if (function.getVariable(xName) != nullptr)
        px = function.getVariable(xName)->getValuePtr();
    if (function.getVariable(yName) != nullptr)
        py = function.getVariable(yName)->getValuePtr();
    float r1 = surfaceBottomColor.redF() - surfaceMiddleColor.redF();
    float g1 = surfaceBottomColor.greenF() - surfaceMiddleColor.greenF();
    float b1 = surfaceBottomColor.blueF() - surfaceMiddleColor.blueF();
    float r2 = surfaceTopColor.redF() - surfaceMiddleColor.redF();
    float g2 = surfaceTopColor.greenF() - surfaceMiddleColor.greenF();
    float b2 = surfaceTopColor.blueF() - surfaceMiddleColor.blueF();
    float rm = surfaceMiddleColor.redF();
    float gm = surfaceMiddleColor.greenF();
    float bm = surfaceMiddleColor.blueF();
    float result;
    float ratio;

    GLfloat *surfaceVertex = this->surfaceVertex.data();
    GLfloat *surfaceColor = this->surfaceColor.data();
    int length = this->surfaceVertex.length() / 3;
    for (int i = 0; i < length; i++) {
        if (px != nullptr)
            *px = surfaceVertex[3 * i + 0];
        if (py != nullptr)
            *py = surfaceVertex[3 * i + 1];
        result = function.result();
        if (qIsNaN(result)) {
            if (px != nullptr)
                *px = surfaceVertex[3 * i + 0] + rangeX / (double)xPolygonNum / 100.0;
            if (py != nullptr)
                *py = surfaceVertex[3 * i + 1] + rangeY / (double)yPolygonNum / 100.0;
            result = function.result();
            if (qIsNaN(result)) {
                if (px != nullptr)
                    *px = surfaceVertex[3 * i + 0] + rangeX / (double)xPolygonNum / 100.0;
                if (py != nullptr)
                    *py = surfaceVertex[3 * i + 1] - rangeY / (double)yPolygonNum / 100.0;
                result = function.result();
                if (qIsNaN(result))
                    result = centerZ;
            }

        }
        surfaceVertex[3 * i + 2] = result;
        ratio = (result - centerZ) / rangeZ * 2.0;
        if (ratio < -1.0)
            ratio = -1.0;
        if (ratio > 1.0)
            ratio = 1.0;
        if (ratio < 0.0) {
            surfaceColor[4 * i + 0] = rm - r1 * ratio;
            surfaceColor[4 * i + 1] = gm - g1 * ratio;
            surfaceColor[4 * i + 2] = bm - b1 * ratio;
        } else {
            surfaceColor[4 * i + 0] = rm + r2 * ratio;
            surfaceColor[4 * i + 1] = gm + g2 * ratio;
            surfaceColor[4 * i + 2] = bm + b2 * ratio;
        }
    }
}

void Scene3DXYZ::updateNetBase()
{
    QVector<double> pointsX = axisXPoints();
    QVector<double> pointsY = axisYPoints();
    if (pointsX.length() < 2 || pointsY.length() < 2)
        return;
    double xMin = pointsX.first();
    double xMax = pointsX.last();
    uint xNum = pointsX.length();
    double yMin = pointsY.first();
    double yMax = pointsY.last();
    uint yNum = pointsY.length();

    int netVertexNumber = xNum * (yPolygonNum + 1) + yNum * (xPolygonNum + 1);
    int netLineNumber = xNum * yPolygonNum + yNum * xPolygonNum;
    netIndex.resize(netLineNumber * 2);
    netVertex.resize(netVertexNumber * 3);

    GLuint *netIndex = this->netIndex.data();
    GLfloat *netVertex = this->netVertex.data();

    for (int x = 0; x < xNum; x++)
        for (int y = 0; y < yPolygonNum; y++) {
            netIndex[2 * (x * yPolygonNum + y)] = x * (yPolygonNum + 1) + y;
            netIndex[2 * (x * yPolygonNum + y) + 1] = x * (yPolygonNum + 1) + y + 1;
        }
    int i = xNum * yPolygonNum * 2;
    int i1 = xNum * (yPolygonNum + 1);
    for (int y = 0; y < yNum; y++)
        for (int x = 0; x < xPolygonNum; x++) {
            netIndex[i + 2 * (y * xPolygonNum + x)] = i1 + y * (xPolygonNum + 1) + x;
            netIndex[i + 2 * (y * xPolygonNum + x) + 1] = i1 + y * (xPolygonNum + 1) + x + 1;
        }
    double xVertexStep = (double)rangeX / xPolygonNum;
    double yVertexStep = (double)rangeY / yPolygonNum;
    for (int x = 0; x < xNum; x++)
        for (int y = 0; y <= yPolygonNum; y++) {
            netVertex[3 * (x * (yPolygonNum + 1) + y)] = pointsX[x];
            netVertex[3 * (x * (yPolygonNum + 1) + y) + 1] = centerY - rangeY / 2.0 +
                    (double)y * yVertexStep;
        }
    for (int y = 0; y < yNum; y++)
        for (int x = 0; x <= xPolygonNum; x++) {
            netVertex[3 * (y * (xPolygonNum + 1) + x + i1)] = centerX - rangeX / 2.0 +
                    (double)x * xVertexStep;
            netVertex[3 * (y * (xPolygonNum + 1) + x + i1) + 1] = pointsY[y];
        }
}

void Scene3DXYZ::updateNet()
{
    double *px = nullptr, *py = nullptr;
    if (function.getVariable(xName) != nullptr)
        px = function.getVariable(xName)->getValuePtr();
    if (function.getVariable(yName) != nullptr)
        py = function.getVariable(yName)->getValuePtr();

    GLfloat *netVertex = this->netVertex.data();
    int length = this->netVertex.length() / 3;
    for (int i = 0; i < length; i++) {
        if (px != nullptr)
            *px = netVertex[3 * i + 0];
        if (py != nullptr)
            *py = netVertex[3 * i + 1];
        netVertex[3 * i + 2] = function.result();
    }
}

void Scene3DXYZ::drawNet() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, netVertex.data());
    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(netColor.redF(), netColor.greenF(), netColor.blueF());
    glLineWidth(netWidth);
    glDrawElements(GL_LINES, netIndex.length(), GL_UNSIGNED_INT, netIndex.data());
}

void Scene3DXYZ::setNetXPeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netXMin = 4; netXPeriodicity = periodicity; break;
    case LOW: netXMin = 6; netXPeriodicity = periodicity; break;
    case DECREASED: netXMin = 9; netXPeriodicity = periodicity; break;
    case MIDDLE: netXMin = 12; netXPeriodicity = periodicity; break;
    case INCREASED: netXMin = 15; netXPeriodicity = periodicity; break;
    case HIGH: netXMin = 20; netXPeriodicity = periodicity; break;
    case VERY_HIGH: netXMin = 25; netXPeriodicity = periodicity; break;
    case ULTRA_HIGH: netXMin = 32; netXPeriodicity = periodicity; break;
    }
}

void Scene3DXYZ::setNetYPeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netYMin = 4; netYPeriodicity = periodicity; break;
    case LOW: netYMin = 6; netYPeriodicity = periodicity; break;
    case DECREASED: netYMin = 9; netYPeriodicity = periodicity; break;
    case MIDDLE: netYMin = 12; netYPeriodicity = periodicity; break;
    case INCREASED: netYMin = 15; netYPeriodicity = periodicity; break;
    case HIGH: netYMin = 20; netYPeriodicity = periodicity; break;
    case VERY_HIGH: netYMin = 25; netYPeriodicity = periodicity; break;
    case ULTRA_HIGH: netYMin = 32; netYPeriodicity = periodicity; break;
    }
}

SettingsXYZ Scene3DXYZ::getSettings() const
{
    SettingsXYZ sets;
    sets.common = getCommonSettings();
    sets.centerX = centerX;
    sets.centerY = centerY;
    sets.centerZ = centerZ;
    sets.isSurfaceEnable = isSurfaceEnable;
    sets.netXPeriodicity = netXPeriodicity;
    sets.netYPeriodicity = netYPeriodicity;
    sets.rangeX = rangeX;
    sets.rangeY = rangeY;
    sets.rangeZ = rangeZ;
    sets.surfaceBottomColor = surfaceBottomColor;
    sets.surfaceMiddleColor = surfaceMiddleColor;
    sets.surfaceTopColor = surfaceTopColor;
    sets.xName = xName;
    sets.yName = yName;
    return sets;
}

void Scene3DXYZ::drawLegend(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    QSize legendSize((float)legendSizeRatio * height() * 0.75, (float)legendSizeRatio * height());
    QImage image(legendSize, QImage::Format_ARGB32);
    image.fill(QColor(0xff, 0xff, 0xff, round((float)legendBackOpacity * 0xff)));
    QPen pen(Qt::gray);
    pen.setWidthF(5.0);
    QFont font;
    font.setPointSizeF((float)legendSize.height() / 18.0);
    QFontMetrics fm(font);
    QPainter imagePainter;
    imagePainter.begin(&image);
    imagePainter.setRenderHint(QPainter::Antialiasing);
    imagePainter.setPen(pen);
    imagePainter.setFont(font);
    imagePainter.drawRect(0, 0, legendSize.width(), legendSize.height());
    QString s1 = xName + QString(":"), s2 = yName + QString(":"), s3("Z:");
    pen.setColor(Qt::black);
    imagePainter.setPen(pen);
    imagePainter.drawText(legendSize.width() / 6 - fm.width(s1) / 2, legendSize.height() / 15, s1);
    imagePainter.drawText(legendSize.width() / 2 - fm.width(s2), legendSize.height() / 15, s2);
    imagePainter.drawText(5 * legendSize.width() / 6 - fm.width(s3), legendSize.height() / 15, s3);

    for (int i = 0; i < 3; i++) {
        imagePainter.setPen(Qt::NoPen);
        if (i == 0) {
            QBrush brush(axis1Color);
            imagePainter.setBrush(brush);
        } else if (i == 1) {
            QBrush brush(axis2Color);
            imagePainter.setBrush(brush);
        } else {
            QLinearGradient gradient(0.0, (float)25.0 * legendSize.height() / 30.0,
                                     0.0, (float)4.0 * legendSize.height() / 30.0);
            gradient.setColorAt(0.0, surfaceBottomColor);
            gradient.setColorAt(0.5, surfaceMiddleColor);
            gradient.setColorAt(1.0, surfaceTopColor);
            imagePainter.setBrush(gradient);
        }
        imagePainter.drawRect(i * legendSize.width() / 3 + legendSize.width() / 50 + 3,
                              4 * legendSize.height() / 30,
                              legendSize.width() / 40 + 1, 25 * legendSize.height() / 30);
        QVector<double> points;
        QVector<double> basePoints;
        double min, range;
        pen.setColor(Qt::black);
        pen.setWidthF((float)1.0 + (float)legendSize.width() / 200.0);
        imagePainter.setPen(pen);
        font.setPointSizeF((float)legendSize.height() / 50.0);
        imagePainter.setFont(font);
        if (i == 0) {
            points = axisXPoints();
            basePoints = axisXBasePoints(netBaseXNum);
            min = centerX - rangeX / 2.0;
            range = rangeX;
        } else if (i == 1){
            points = axisYPoints();
            basePoints = axisYBasePoints(netBaseXNum);
            min = centerY - rangeY / 2.0;
            range = rangeY;
        } else {
            points = axisZPoints();
            basePoints = axisZBasePoints(netBaseXNum);
            min = centerZ - rangeZ / 2.0;
            range = rangeZ;
        }
        for (int j = 0; j < points.length(); j++) {
            QLineF line((float)i * legendSize.width() / 3.0 + 3.0, (float)29.0 *
                        legendSize.height() / 30.0 - 25.0 * legendSize.height() / 30.0 *
                        (points[j] - min) / range, (float)i * legendSize.width() / 3.0 + 3.0 +
                        legendSize.width() / 50.0 + legendSize.width() / 40.0 + 1.0, (float)29.0 *
                        legendSize.height() / 30.0 - 25.0 * legendSize.height() / 30.0 *
                        (points[j] - min) / range);
            imagePainter.drawLine(line);
        }
        for (int j = 0; j < basePoints.length(); j++) {
            QLineF line((float)i * legendSize.width() / 3.0 + 3.0, (float)29.0 *
                        legendSize.height() / 30.0 - 25.0 * legendSize.height() / 30.0 *
                        (basePoints[j] - min) / range, (float)i * legendSize.width() / 3.0 + 3.0 +
                        legendSize.width() / 50.0 + legendSize.width() / 40.0 + 1.0 +
                        legendSize.width() / 66.0, (float)29.0 * legendSize.height() / 30.0 - 25.0 *
                        legendSize.height() / 30.0 * (basePoints[j] - min) / range);
            if (fabs(basePoints[j] / basePoints[j > 0 ? j - 1 : 0]) < 1.0e-3)
                basePoints[j] = 0.0;
            imagePainter.drawText((float)line.x2() + 3.0, (float)line.y1() + font.pointSizeF() /
                                  2.0, QString::number(basePoints[j], 'g', 8));
            imagePainter.drawLine(line);
        }
    }
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(1.0);
    painter.drawImage(width() - legendSize.width() - 10, height() - legendSize.height() - 10,image);
}

QVector<double> Scene3DXYZ::axisXPoints() const
{
    return axisPoints(centerX, rangeX, netXMin);
}

QVector<double> Scene3DXYZ::axisYPoints() const
{
    return axisPoints(centerY, rangeY, netYMin);
}

void Scene3DXYZ::runSettings()
{
    SettingsDialogXYZ dialog(getSettings());
    double tStep = this->timeStep;
    this->stopSelfUpdating();
    if (dialog.exec() == QDialog::Accepted) {
        this->startSelfUpdating(tStep);
        SettingsXYZ sets = dialog.getSettings();
        this->setCommonSettings(sets.common);
        centerX = sets.centerX; centerY = sets.centerY; centerZ = sets.centerZ;
        rangeX = sets.rangeX; rangeY = sets.rangeY; rangeZ = sets.rangeZ;
        isSurfaceEnable = sets.isSurfaceEnable;
        setNetXPeriodicity(sets.netXPeriodicity);
        setNetYPeriodicity(sets.netYPeriodicity);
        surfaceBottomColor = sets.surfaceBottomColor;
        surfaceMiddleColor = sets.surfaceMiddleColor;
        surfaceTopColor = sets.surfaceTopColor;
        xName = sets.xName;
        yName = sets.yName;
        compiler.initContextFromFile(this->contextFileName);
        setString(sets.common.funcString);
        updateBase();
        updateScene();
        repaint();
    }
}

void Scene3DXYZ::runArguments()
{
    QVector<QString> names;
    QVector<QString> values;
    for (int i = 0; i < function.getVariableList()->length(); i++) {
        QString name = (*function.getVariableList())[i].getName();
        if (name == xName || name == yName || name == timeName)
            continue;
        names.push_back(name);
        values.push_back(QString::number((*function.getVariableList())[i].getValue()));
    }
    ArgumentsDialog dialog(names, values, nullptr);
    dialog.show();
    double tStep = this->timeStep;
    this->stopSelfUpdating();
    if (dialog.exec() == QDialog::Accepted) {
        this->startSelfUpdating(tStep);
        QVector<QString> values = dialog.getValues();
        QFunction<double> F;
        int o = 0;
        for (int i = 0; i < function.getVariableNumber(); i++) {
            QString name = (*function.getVariableList())[i].getName();
            if (name == xName || name == yName || name == timeName)
                continue;
            F.setString(values[o], compiler);
            (*function.getVariableList())[i].setValue(F.result());
            o++;
        }
        updateScene();
        repaint();
    }
}

void Scene3DXYZ::drawBoundingAxis()
{
    QVector<double> xPoints = axisXPoints();
    QVector<double> yPoints = axisYPoints();
    QVector<double> zPoints = axisZPoints();
    glLineWidth(1.5);
    glBegin(GL_LINES);
    // Lines of arrows
    glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY, centerZ + rangeZ / 2.0);
    glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ);
    double x1, y1, x2, y2;
    const int trianglesInTip = 20;
    const float darker = 0.5;
    const double arrowLength = 1.0 / 20.0;
    const double arrowWidth = 1.0 / 70.0;
    glEnd();

    // Tips of arrows
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < trianglesInTip; i++) {
        x1 = cos(2.0 * M_PI / (double)trianglesInTip * (double)i);
        y1 = sin(2.0 * M_PI / (double)trianglesInTip * (double)i);
        x2 = cos(2.0 * M_PI / (double)trianglesInTip * (double)(i + 1.0));
        y2 = sin(2.0 * M_PI / (double)trianglesInTip * (double)(i + 1.0));
        glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
        glVertex3d(centerX, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x1,
                   centerZ - rangeZ / 2.0 + rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x2,
                   centerZ - rangeZ / 2.0 + rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF() * darker,
                  axis1Color.blueF() * darker);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x1,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x2,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
        glVertex3d(centerX, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
        glVertex3d(centerX - rangeX * arrowLength, centerY + rangeY / 2.0 + rangeY * arrowWidth *x1,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX * arrowLength, centerY + rangeY / 2.0 + rangeY * arrowWidth *x2,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF() * darker,
                  axis1Color.blueF() * darker);
        glVertex3d(centerX - rangeX * arrowLength, centerY + rangeY / 2.0 + rangeY * arrowWidth *x1,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX * arrowLength, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
        glVertex3d(centerX - rangeX * arrowLength, centerY + rangeY / 2.0 + rangeY * arrowWidth *x2,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y2);

        glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
        glVertex3d(centerX - rangeX / 2.0, centerY, centerZ - rangeZ / 2.0);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY *arrowLength,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY *arrowLength,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y2);
        glColor3f(axis2Color.redF() * darker, axis2Color.greenF() * darker,
                  axis2Color.blueF() * darker);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY *arrowLength,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX / 2.0, centerY - rangeY * arrowLength, centerZ - rangeZ / 2.0);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY *arrowLength,
                   centerZ - rangeZ / 2.0 - rangeZ * arrowWidth * y2);
        glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
        glVertex3d(centerX + rangeX / 2.0, centerY, centerZ + rangeZ / 2.0);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY *arrowLength,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY *arrowLength,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y2);
        glColor3f(axis2Color.redF() * darker, axis2Color.greenF() * darker,
                  axis2Color.blueF() * darker);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY *arrowLength,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y1);
        glVertex3d(centerX + rangeX / 2.0, centerY - rangeY * arrowLength, centerZ + rangeZ / 2.0);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY *arrowLength,
                   centerZ + rangeZ / 2.0 - rangeZ * arrowWidth * y2);

        glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
        glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY / 2.0 +
                   rangeY * arrowWidth * y1, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY / 2.0 +
                   rangeY * arrowWidth * y2, centerZ - rangeZ * arrowLength);
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF() * darker,
                  axis3Color.blueF() * darker);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x1, centerY - rangeY / 2.0 +
                   rangeY * arrowWidth * y1, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX - rangeX / 2.0 + rangeX * arrowWidth * x2, centerY - rangeY / 2.0 +
                   rangeY * arrowWidth * y2, centerZ - rangeZ * arrowLength);
        glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
        glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x1, centerY + rangeY / 2.0 +
                   rangeY * arrowWidth * y1, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x2, centerY + rangeY / 2.0 +
                   rangeY * arrowWidth * y2, centerZ - rangeZ * arrowLength);
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF() * darker,
                  axis3Color.blueF() * darker);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x1, centerY + rangeY / 2.0 +
                   rangeY * arrowWidth * y1, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ * arrowLength);
        glVertex3d(centerX + rangeX / 2.0 + rangeX * arrowWidth * x2, centerY + rangeY / 2.0 +
                   rangeY * arrowWidth * y2, centerZ - rangeZ * arrowLength);
    }
    glEnd();

    // Everything else of the cube
    glBegin(GL_LINES);
    float GRAY = 0.8;
    glColor3f(GRAY, GRAY, GRAY);
    glVertex3d(centerX, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ);
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);

    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX - rangeX / 2.0, centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);

    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
    glVertex3d(centerX + rangeX / 2.0, centerY + rangeY / 2.0, centerZ);
    glEnd();

    // Points on sides of cube
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < xPoints.length(); i++) {
        glVertex3f(xPoints[i], centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
        glVertex3f(xPoints[i], centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
        glVertex3f(xPoints[i], centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
        glVertex3f(xPoints[i], centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
    }
    for (int i = 0; i < yPoints.length(); i++) {
        glVertex3f(centerX - rangeX / 2.0, yPoints[i], centerZ - rangeZ / 2.0);
        glVertex3f(centerX + rangeX / 2.0, yPoints[i], centerZ - rangeZ / 2.0);
        glVertex3f(centerX + rangeX / 2.0, yPoints[i], centerZ + rangeZ / 2.0);
        glVertex3f(centerX - rangeX / 2.0, yPoints[i], centerZ + rangeZ / 2.0);
    }
    for (int i = 0; i < zPoints.length(); i++) {
        glVertex3f(centerX - rangeX / 2.0, centerY - rangeY / 2.0, zPoints[i]);
        glVertex3f(centerX + rangeX / 2.0, centerY - rangeY / 2.0, zPoints[i]);
        glVertex3f(centerX + rangeX / 2.0, centerY + rangeY / 2.0, zPoints[i]);
        glVertex3f(centerX - rangeX / 2.0, centerY + rangeY / 2.0, zPoints[i]);
    }
    glEnd();

    // Cells
    if (axis == BOUNDING_AXIS_CELLULAR) {
        glLineWidth(1.0);
        glColor3f(GRAY, GRAY, GRAY);
        QVector<double> baseXPoints = axisXBasePoints(netBaseXNum);
        QVector<double> baseYPoints = axisYBasePoints(netBaseYNum);
        QVector<double> baseZPoints = axisZBasePoints(netBaseZNum);
        glBegin(GL_LINES);
        for (int i = 0; i < baseXPoints.length(); i++) {
            glVertex3f(baseXPoints[i], centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
            glVertex3f(baseXPoints[i], centerY - rangeY / 2.0, centerZ + rangeZ / 2.0);
            glVertex3f(baseXPoints[i], centerY + rangeY / 2.0, centerZ - rangeZ / 2.0);
            glVertex3f(baseXPoints[i], centerY + rangeY / 2.0, centerZ + rangeZ / 2.0);
        }
        for (int i = 0; i < baseYPoints.length(); i++) {
            glVertex3f(centerX - rangeX / 2.0, baseYPoints[i], centerZ - rangeZ / 2.0);
            glVertex3f(centerX - rangeX / 2.0, baseYPoints[i], centerZ + rangeZ / 2.0);
            glVertex3f(centerX + rangeX / 2.0, baseYPoints[i], centerZ - rangeZ / 2.0);
            glVertex3f(centerX + rangeX / 2.0, baseYPoints[i], centerZ + rangeZ / 2.0);
        }
        glEnd();
        for (int i = 0; i < baseZPoints.length(); i++) {
            glBegin(GL_LINE_LOOP);
            glVertex3f(centerX - rangeX / 2.0, centerY - rangeY / 2.0, baseZPoints[i]);
            glVertex3f(centerX + rangeX / 2.0, centerY - rangeY / 2.0, baseZPoints[i]);
            glVertex3f(centerX + rangeX / 2.0, centerY + rangeY / 2.0, baseZPoints[i]);
            glVertex3f(centerX - rangeX / 2.0, centerY + rangeY / 2.0, baseZPoints[i]);
            glEnd();
        }
    }
}

void Scene3DXYZ::glTransformations()
{
    if (isPerspectiveEnabled) {
        glTranslatef(0.0, 0.0, -radius);
        glRotatef(-90.0 - xRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot * 180.0 / M_PI, 0.0f, 1.0f, 0.0f);
        glRotatef(zRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glRotatef(-xLookAroundRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(zLookAroundRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glScalef(1.0 / rangeX, 1.0 / rangeY, 1.0 / rangeZ * verticalExtension);
        glTranslatef(-centerX, -centerY, -centerZ);
    } else {
        glScalef(2.0 / ((float)width() / (float)height()) / radius, 2.0 / radius, radius);
        glRotatef(-90.0 - xRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot * 180.0 / M_PI, 0.0f, 1.0f, 0.0f);
        glRotatef(zRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glRotatef(-xLookAroundRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(zLookAroundRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glScalef(1.0 / rangeX / radius, 1.0 / rangeY / radius, 1.0 / rangeZ *
                 verticalExtension / radius);
        glTranslatef(-centerX, -centerY, -centerZ);
    }
}
