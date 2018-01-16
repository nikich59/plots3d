#include "scene3dpolar.h"

Scene3DPolar::Scene3DPolar(QWidget *parent) : Scene3D(parent)
{
    rName = "r";
    phiName = "phi";
    setNetRPeriodicity(DECREASED);
    setNetPhiPeriodicity(DECREASED);
    surfaceBottomColor = Qt::gray;
    surfaceMiddleColor = Qt::gray;
    surfaceTopColor = Qt::gray;
    centerZ = 0.0;
    rangeR = 1.0; rangeZ = 1.0;
    setSurfaceQuality(LOW);
    setString(QString("0"));
    updateBase();
    updateScene();
}

SettingsPolar Scene3DPolar::getSettings() const
{
    SettingsPolar sets;
    sets.common = getCommonSettings();
    sets.centerZ = centerZ;
    sets.isSurfaceEnable = isSurfaceEnable;
    sets.netRPeriodicity = netRPeriodicity;
    sets.netPhiPeriodicity = netPhiPeriodicity;
    sets.rangeR = rangeR;
    sets.rangeZ = rangeZ;
    sets.surfaceBottomColor = surfaceBottomColor;
    sets.surfaceMiddleColor = surfaceMiddleColor;
    sets.surfaceTopColor = surfaceTopColor;
    sets.rName = rName;
    sets.phiName = phiName;
    return sets;
}

void Scene3DPolar::setNetRPeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netRMin = 4; netRPeriodicity = periodicity; break;
    case LOW: netRMin = 6; netRPeriodicity = periodicity; break;
    case DECREASED: netRMin = 9; netRPeriodicity = periodicity; break;
    case MIDDLE: netRMin = 12; netRPeriodicity = periodicity; break;
    case INCREASED: netRMin = 15; netRPeriodicity = periodicity; break;
    case HIGH: netRMin = 20; netRPeriodicity = periodicity; break;
    case VERY_HIGH: netRMin = 25; netRPeriodicity = periodicity; break;
    case ULTRA_HIGH: netRMin = 32; netRPeriodicity = periodicity; break;
    }
}

void Scene3DPolar::setNetPhiPeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netPhi = 4; netPhiPeriodicity = periodicity; break;
    case LOW: netPhi = 6; netPhiPeriodicity = periodicity; break;
    case DECREASED: netPhi = 8; netPhiPeriodicity = periodicity; break;
    case MIDDLE: netPhi = 12; netPhiPeriodicity = periodicity; break;
    case INCREASED: netPhi = 16; netPhiPeriodicity = periodicity; break;
    case HIGH: netPhi = 20; netPhiPeriodicity = periodicity; break;
    case VERY_HIGH: netPhi = 25; netPhiPeriodicity = periodicity; break;
    case ULTRA_HIGH: netPhi = 32; netPhiPeriodicity = periodicity; break;
    }
}

QString Scene3DPolar::getString() const
{
    return function.getString();
}

void Scene3DPolar::drawLegend(QPainter &painter)
{

}

QVector<double> Scene3DPolar::axisXPoints() const
{
    if (rangeR < 1e-125)
        return QVector<double>();
    double step = pow(10.0, ceil(log(rangeR / netRMin) / log(10.0)));
    if (rangeR / step < netRMin)
        step /= 2.0;
    if (rangeR / step < netRMin)
        step /= 2.5;
    if (rangeR / step < netRMin)
        step /= 2.0;
    double min = step;
    double max = rangeR;
    QVector<double> v;
    for (double i = min; i <= max; i += step)
        v.push_back(i);
    return v;
}

QVector<double> Scene3DPolar::axisYPoints() const
{
    QVector<double> v;
    return v;
}

QVector<double> Scene3DPolar::axisZPoints() const
{
    return axisPoints(centerZ, rangeZ, isolineMin);
}

void Scene3DPolar::setSurfaceQuality(uint quality)
{
    switch(quality) {
    case VERY_LOW: rPolygonNum = 36; surfaceQuality = quality; break;
    case LOW: rPolygonNum = 56; surfaceQuality = quality; break;
    case DECREASED: rPolygonNum = 80; surfaceQuality = quality; break;
    case MIDDLE: rPolygonNum = 120; surfaceQuality = quality; break;
    case INCREASED: rPolygonNum = 180; surfaceQuality = quality; break;
    case HIGH: rPolygonNum = 280; surfaceQuality = quality; break;
    case VERY_HIGH: rPolygonNum = 400; surfaceQuality = quality; break;
    case ULTRA_HIGH: rPolygonNum = 1000; surfaceQuality = quality; break;
    }
}

void Scene3DPolar::updateTime()
{
    if (isActivatedTime)
        function.setVariableValue(timeName, (double)startTime.msecsTo(QTime::currentTime())/1000.0);
}

void Scene3DPolar::updateSurface()
{
    function.setVariableValue(timeName, (double)startTime.msecsTo(QTime::currentTime()) / 1000.0);
    double *pr = nullptr, *pphi = nullptr;
    if (function.getVariable(rName) != nullptr)
        pr = function.getVariable(rName)->getValuePtr();
    if (function.getVariable(phiName) != nullptr)
        pphi = function.getVariable(phiName)->getValuePtr();
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
    double r, phi;

    GLfloat *surfaceColor = this->surfaceColor.data();
    GLfloat *surfaceVertex = this->surfaceVertex.data();
    GLfloat *vertexInPolar = this->vertexInPolar.data();
    int length = this->surfaceVertex.length() / 3;
    for (int i = 0; i < length; i++) {
        r = vertexInPolar[2 * i];
        phi = vertexInPolar[2 * i + 1];
        if (pr != nullptr)
            *pr = r;
        if (pphi != nullptr)
            *pphi = phi;

        result = function.result();

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

void Scene3DPolar::updateSurfaceBase()
{
    if (rangeR < 1e-120 || rangeR < 1e-120 || rangeZ < 1e-120)
        return;
    surfaceVertex.clear();
    surfaceIndex.clear();
    surfaceColor.clear();
    vertexInPolar.clear();
    int currentFirst = 0;
    QVector<GLfloat> lastRing;
    QVector<GLfloat> currentRing;
    for (int coilNum = 0; coilNum <= rPolygonNum; coilNum++) {
        if (coilNum == 0) {
            lastRing.push_back(0.0);
            lastRing.push_back(0.0);
            lastRing.push_back(0.0);
            vertexInPolar.push_back(0.0);
            vertexInPolar.push_back(0.0);
            continue;
        }
        double r = (double)coilNum / (double)rPolygonNum * rangeR;
        int phiPointsNum = round((float)coilNum * M_PI * 2);
        float phiStep = 2 * M_PI / (float)phiPointsNum;
        int closest = 0;
        int currentNum = 0;
        for (int phiNum = 0; phiNum < phiPointsNum; phiNum++) {
            float phi = phiStep * (float)phiNum - M_PI;
            double X = r * cos(phi);
            double Y = r * sin(phi);
            double X1 = r * cos(phi + phiStep);
            double Y1 = r * sin(phi + phiStep);
            currentRing.push_back(X);
            currentRing.push_back(Y);
            currentRing.push_back(0.0);
            vertexInPolar.push_back(r);
            vertexInPolar.push_back(phi);
            if (phiNum != phiPointsNum - 1) {
                surfaceIndex.push_back(surfaceVertex.length() / 3 + closest);
                surfaceIndex.push_back(surfaceVertex.length() / 3 + lastRing.length() / 3 +
                                       currentNum);
                float x1, y1, x2, y2, r1, r2;
                if (closest + 1 < lastRing.length() / 3) {
                    x1 = lastRing[3 * closest];
                    y1 = lastRing[3 * closest + 1];
                    x2 = lastRing[3 * closest + 3];
                    y2 = lastRing[3 * closest + 4];
                    r1 = ((X1 - x1) * (X1 - x1) + (Y1 - y1) * (Y1 - y1));
                    r2 = ((X1 - x2) * (X1 - x2) + (Y1 - y2) * (Y1 - y2));
                }
                while ((closest + 1 < lastRing.length() / 3) && r1 > r2) {
                    closest++;
                    if (closest + 1 < lastRing.length() / 3) {
                        x1 = lastRing[3 * closest];
                        y1 = lastRing[3 * closest + 1];
                        x2 = lastRing[3 * closest + 3];
                        y2 = lastRing[3 * closest + 4];
                        r1 = ((X1 - x1) * (X1 - x1) + (Y1 - y1) * (Y1 - y1));
                        r2 = ((X1 - x2) * (X1 - x2) + (Y1 - y2) * (Y1 - y2));
                    }
                }
                currentNum++;
                surfaceIndex.push_back(surfaceVertex.length() / 3 + lastRing.length() / 3 +
                                       currentNum);
                surfaceIndex.push_back(surfaceVertex.length() / 3 + closest);
            } else {
                surfaceIndex.push_back(surfaceVertex.length() / 3 + closest);
                surfaceIndex.push_back(surfaceVertex.length() / 3 + lastRing.length() / 3 +
                                       currentRing.length() / 3 - 1);
                surfaceIndex.push_back(surfaceVertex.length() / 3 + lastRing.length() / 3);
                surfaceIndex.push_back(surfaceVertex.length() / 3);
                surfaceVertex += lastRing;
                lastRing = currentRing;
                currentRing.clear();
            }
        }
    }
    surfaceVertex += lastRing;

    for (int i = 0; i < surfaceVertex.length() / 3; i++) {
        float l = 0.5;
        surfaceColor.push_back(l);
        surfaceColor.push_back(l);
        surfaceColor.push_back(l);
        surfaceColor.push_back(1.0);
    }
}

void Scene3DPolar::updateNetBase()
{
    netVertex.clear();
    netIndex.clear();
    int vertNum = 0;
    for (int rayNum = 0; rayNum < netPhi; rayNum++) {
        float phi = (float)rayNum / (float)netPhi * M_PI * 2.0;
        float cosPhi = cos(phi);
        float sinPhi = sin(phi);
        for (int ringNum = 0; ringNum <= rPolygonNum; ringNum++) {
            float r = (float)ringNum / (float)rPolygonNum * rangeR;
            float x = r * cosPhi;
            float y = r * sinPhi;
            netVertex.push_back(x);
            netVertex.push_back(y);
            netVertex.push_back(0.0);
            vertNum++;
            if (ringNum == 0)
                continue;
            netIndex.push_back(vertNum - 2);
            netIndex.push_back(vertNum - 1);
        }
    }
    QVector<double> rPoints = axisXPoints();
    for (int i = 0; i < rPoints.length(); i++) {
        float r = rPoints[i];
        int rayMax = round(r / rangeR * (float)rPolygonNum * M_PI * 2.0);
        int currentFirst = netVertex.length() / 3;
        for (int rayNum = 0; rayNum < rayMax; rayNum++) {
            float phi = (float)rayNum / (float)rayMax * M_PI * 2.0;
            float x = r * cos(phi);
            float y = r * sin(phi);
            netVertex.push_back(x);
            netVertex.push_back(y);
            netVertex.push_back(0.0);
            netIndex.push_back(vertNum);
            if (rayNum < rayMax - 1)
                netIndex.push_back(vertNum + 1);
            else
                netIndex.push_back(currentFirst);
            vertNum++;
        }
    }
}

void Scene3DPolar::updateNet()
{
    double *pr = nullptr, *pphi = nullptr;
    if (function.getVariable(rName) != nullptr)
        pr = function.getVariable(rName)->getValuePtr();
    if (function.getVariable(phiName) != nullptr)
        pphi = function.getVariable(phiName)->getValuePtr();

    GLfloat *netVertex = this->netVertex.data();
    int length = this->netVertex.length() / 3;
    for (int i = 0; i < length; i++) {
        if (pr != nullptr)
            *pr = sqrt(netVertex[3 * i] * netVertex[3 * i] + netVertex[3 * i + 1] *
                    netVertex[3 * i + 1]);
        if (pphi != nullptr)
            *pphi = atan2(netVertex[3 * i + 1], netVertex[3 * i]);
        netVertex[3 * i + 2] = function.result();
    }
}

void Scene3DPolar::runArguments()
{
    QVector<QString> names;
    QVector<QString> values;
    for (int i = 0; i < function.getVariableList()->length(); i++) {
        QString name = (*function.getVariableList())[i].getName();
        if (name == rName || name == phiName || name == timeName)
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
            if (name == rName || name == phiName || name == timeName)
                continue;
            F.setString(values[o], compiler);
            (*function.getVariableList())[i].setValue(F.result());
            o++;
        }
        updateScene();
        repaint();
    }
}

void Scene3DPolar::drawCentralAxis()
{
    glLineWidth(2.0);
    glDisable(GL_DEPTH_TEST);
    GLfloat R[] = {0.0, 0.0, centerZ, 0.0 + rangeR * axisLengthRatio, 0.0, centerZ};
    GLfloat Z[] = {0.0, 0.0, centerZ, 0.0, 0.0, centerZ + rangeZ * axisLengthRatio /
                  verticalExtension};
    GLuint i[2] = {0, 1};
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, R);
    glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, i);
    glVertexPointer(3, GL_FLOAT, 0, Z);
    glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, i);
    glBegin(GL_LINE_STRIP);
    glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
    const int arrowLineNum = 20;
    float r = rangeR * axisLengthRatio;
    for (int i = 0; i <= arrowLineNum; i++) {
        float phi = (float)i / (float)arrowLineNum * M_PI / 2.0;
        float x = r * cos(phi);
        float y = r * sin(phi);
        glVertex3d(x, y, centerZ);
    }
    glEnd();

    glEnable(GL_DEPTH_TEST);
}

void Scene3DPolar::drawBoundingAxis()
{
    int coilLineNum = rPolygonNum * 6; // 6 ~ 2*pi
    const float GRAY = 0.5;
    glLineWidth(2.0);
    glBegin(GL_LINES);
    float r = rangeR * 1.1;
    for (int i = 0; i < coilLineNum; i++) {
        float phi = (float)i / (float)coilLineNum * 2.0 * M_PI;
        float phi1 = (float)(i + 1) / (float)coilLineNum * 2.0 * M_PI;
        float x = rangeR * cos(phi);
        float y = rangeR * sin(phi);
        float x1 = rangeR * cos(phi1);
        float y1 = rangeR * sin(phi1);
        glColor3f(GRAY, GRAY, GRAY);
        glVertex3d(x, y, centerZ - rangeZ / 2.0);
        glVertex3d(x1, y1, centerZ - rangeZ / 2.0);
        glVertex3d(x, y, centerZ + rangeZ / 2.0);
        glVertex3d(x1, y1, centerZ + rangeZ / 2.0);
        if (phi < M_PI * 0.5 || phi > M_PI * 1.5) {
            glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
            float x = r * cos(phi);
            float y = r * sin(phi);
            float x1 = r * cos(phi1);
            float y1 = r * sin(phi1);
            glVertex3d(x, y, centerZ);
            glVertex3d(x1, y1, centerZ);
        }
    }
    glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
    glVertex3d(r, 0.0, centerZ);
    glVertex3d(r, 0.0, centerZ + rangeZ / 2.0);
    glVertex3d(-r, 0.0, centerZ);
    glVertex3d(-r, 0.0, centerZ + rangeZ / 2.0);

    glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
    glVertex3d(0.0 + r + rangeR * axisLengthRatio, 0.0, centerZ);
    glVertex3d(0.0 + rangeR, 0.0, centerZ);
    glVertex3d(0.0 - r - rangeR * axisLengthRatio, 0.0, centerZ);
    glVertex3d(0.0 - rangeR, 0.0, centerZ);
    glEnd();

    double x1, y1, x2, y2;
    const int trianglesInTip = 20;
    const float darker = 0.5;
    const double arrowLength = 1.0 / 20.0;
    const double arrowWidth = 1.0 / 70.0;
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < trianglesInTip; i++) {
        x1 = cos(2.0 * M_PI / (double)trianglesInTip * (double)i);
        y1 = sin(2.0 * M_PI / (double)trianglesInTip * (double)i);
        x2 = cos(2.0 * M_PI / (double)trianglesInTip * (double)(i + 1.0));
        y2 = sin(2.0 * M_PI / (double)trianglesInTip * (double)(i + 1.0));
        glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
        glVertex3d(0.0 + r + rangeR * axisLengthRatio, 0.0, centerZ);
        glVertex3d(0.0 + r + rangeR * axisLengthRatio - rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x1, centerZ + rangeZ * arrowWidth * y1);
        glVertex3d(0.0 + r + rangeR * axisLengthRatio - rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x2, centerZ + rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF() * darker,
                  axis1Color.blueF() * darker);
        glVertex3d(0.0 + r + rangeR * axisLengthRatio - rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x1, centerZ - rangeZ * arrowWidth * y1);
        glVertex3d(0.0 + r + rangeR * axisLengthRatio - rangeR * arrowLength, 0.0, centerZ);
        glVertex3d(0.0 + r + rangeR * axisLengthRatio - rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x2, centerZ - rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
        glVertex3d(0.0 - r - rangeR * axisLengthRatio, 0.0, centerZ);
        glVertex3d(0.0 - r - rangeR * axisLengthRatio + rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x1, centerZ - rangeZ * arrowWidth * y1);
        glVertex3d(0.0 - r - rangeR * axisLengthRatio + rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x2, centerZ - rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF() * darker,
                  axis1Color.blueF() * darker);
        glVertex3d(0.0 - r - rangeR * axisLengthRatio + rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x1, centerZ  - rangeZ * arrowWidth * y1);
        glVertex3d(0.0 - r - rangeR * axisLengthRatio + rangeR * arrowLength, 0.0, centerZ);
        glVertex3d(0.0 - r - rangeR * axisLengthRatio + rangeR * arrowLength, 0.0 + rangeR *
                   arrowWidth * x2, centerZ - rangeZ * arrowWidth * y2);

        glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
        glVertex3d(0.0, 0.0 + r, centerZ);
        glVertex3d(0.0 + rangeR * arrowLength, 0.0 + r + rangeR * arrowWidth * x1,
                   centerZ + rangeZ * arrowWidth * y1);
        glVertex3d(0.0 + rangeR * arrowLength, 0.0 + r + rangeR * arrowWidth * x2,
                   centerZ + rangeZ * arrowWidth * y2);
        glColor3f(axis2Color.redF() * darker, axis2Color.greenF() * darker,
                  axis2Color.blueF() * darker);
        glVertex3d(0.0 + rangeR * arrowLength, 0.0 + r + rangeR * arrowWidth * x1,
                   centerZ - rangeZ * arrowWidth * y1);
        glVertex3d(0.0 + rangeR * arrowLength, 0.0 + r, centerZ);
        glVertex3d(0.0 + rangeR * arrowLength, 0.0 + r + rangeR * arrowWidth * x2,
                   centerZ - rangeZ * arrowWidth * y2);

        glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
        glVertex3d(0.0 - r, 0.0, centerZ + rangeZ / 2.0);
        glVertex3d(0.0 - r + rangeR * arrowWidth * x1, 0.0 +
                   rangeR * arrowWidth * y1, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 - r + rangeR * arrowWidth * x2, 0.0 +
                   rangeR * arrowWidth * y2, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF() * darker,
                  axis3Color.blueF() * darker);
        glVertex3d(0.0 - r + rangeR * arrowWidth * x1, 0.0 +
                   rangeR * arrowWidth * y1, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 - r, 0.0, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 - r + rangeR * arrowWidth * x2, 0.0 +
                   rangeR * arrowWidth * y2, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
        glVertex3d(0.0 + r, 0.0, centerZ + rangeZ / 2.0);
        glVertex3d(0.0 + r + rangeR * arrowWidth * x1, 0.0 +
                   rangeR * arrowWidth * y1, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 + r + rangeR * arrowWidth * x2, 0.0 +
                   rangeR * arrowWidth * y2, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF() * darker,
                  axis3Color.blueF() * darker);
        glVertex3d(0.0 + r + rangeR * arrowWidth * x1, 0.0 +
                   rangeR * arrowWidth * y1, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 + r, 0.0, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
        glVertex3d(0.0 + r + rangeR * arrowWidth * x2, 0.0 +
                   rangeR * arrowWidth * y2, centerZ - rangeZ * arrowLength + rangeZ / 2.0);
    }
    glEnd();
}

void Scene3DPolar::glTransformations()
{
    if (isPerspectiveEnabled) {
        glTranslatef(0.0, 0.0, -radius);
        glRotatef(-90.0 - xRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot * 180.0 / M_PI, 0.0f, 1.0f, 0.0f);
        glRotatef(zRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glRotatef(-xLookAroundRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(zLookAroundRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glScalef(1.0 / rangeR, 1.0 / rangeR, 1.0 / rangeZ * verticalExtension);
        glTranslatef(-0.0, -0.0, -centerZ);
    } else {
        glScalef(2.0 / ((float)width() / (float)height()) / radius, 2.0 / radius, radius);
        glRotatef(-90.0 - xRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot * 180.0 / M_PI, 0.0f, 1.0f, 0.0f);
        glRotatef(zRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glRotatef(-xLookAroundRot * 180.0 / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(zLookAroundRot * 180.0 / M_PI, 0.0f, 0.0f, 1.0f);
        glScalef(1.0 / rangeR / radius, 1.0 / rangeR / radius, 1.0 / rangeZ *
                 verticalExtension / radius);
        glTranslatef(-0.0, -0.0, -centerZ);
    }
}

void Scene3DPolar::runSettings()
{
    SettingsDialogPolar dialog(getSettings());
    double tStep = this->timeStep;
    this->stopSelfUpdating();
    if (dialog.exec() == QDialog::Accepted) {
        this->startSelfUpdating(tStep);
        SettingsPolar sets = dialog.getSettings();
        this->setCommonSettings(sets.common);
        centerZ = sets.centerZ;
        rangeR = sets.rangeR;
        rangeZ = sets.rangeZ;
        //this->setSurfaceEnable(sets.isSurfaceEnable);
        isSurfaceEnable = sets.isSurfaceEnable;
        setNetRPeriodicity(sets.netRPeriodicity);
        setNetPhiPeriodicity(sets.netPhiPeriodicity);
        surfaceBottomColor = sets.surfaceBottomColor;
        surfaceMiddleColor = sets.surfaceMiddleColor;
        surfaceTopColor = sets.surfaceTopColor;
        rName = sets.rName;
        phiName = sets.phiName;
        compiler.initContextFromFile(this->contextFileName);
        setString(sets.common.funcString);
        updateBase();
        repaint();
    }
}
