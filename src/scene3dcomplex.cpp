#include "scene3dcomplex.h"

Scene3DComplex::Scene3DComplex(QWidget *parent) : Scene3DRectangular(parent)
{
    varName = "z";
    netBaseReNum = 5;
    netBaseImNum = 5;
    netBaseZNum = 5;
    setNetRePeriodicity(DECREASED);
    setNetImPeriodicity(DECREASED);
    surfaceColor_0 = Qt::gray;
    surfaceColor_Pi_2 = Qt::gray;
    surfaceColor_Pi = Qt::gray;
    surfaceColor_3_Pi_2 = Qt::gray;
    setString(QString("0"));
    updateBase();
    updateScene();
}

void Scene3DComplex::setString(const QString &string)
{
    QOperationCompiler<Complex> compiler;
    compiler.initContextFromFile(contextFileName.toLatin1().data());
    function.setString(string, compiler);
}

void Scene3DComplex::setNetRePeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netReMin = 4; netRePeriodicity = periodicity; break;
    case LOW: netReMin = 6; netRePeriodicity = periodicity; break;
    case DECREASED: netReMin = 9; netRePeriodicity = periodicity; break;
    case MIDDLE: netReMin = 12; netRePeriodicity = periodicity; break;
    case INCREASED: netReMin = 15; netRePeriodicity = periodicity; break;
    case HIGH: netReMin = 20; netRePeriodicity = periodicity; break;
    case VERY_HIGH: netReMin = 25; netRePeriodicity = periodicity; break;
    case ULTRA_HIGH: netReMin = 32; netRePeriodicity = periodicity; break;
    }
}

void Scene3DComplex::setNetImPeriodicity(uint periodicity)
{
    switch(periodicity) {
    case VERY_LOW: netImMin = 4; netImPeriodicity = periodicity; break;
    case LOW: netImMin = 6; netImPeriodicity = periodicity; break;
    case DECREASED: netImMin = 9; netImPeriodicity = periodicity; break;
    case MIDDLE: netImMin = 12; netImPeriodicity = periodicity; break;
    case INCREASED: netImMin = 15; netImPeriodicity = periodicity; break;
    case HIGH: netImMin = 20; netImPeriodicity = periodicity; break;
    case VERY_HIGH: netImMin = 25; netImPeriodicity = periodicity; break;
    case ULTRA_HIGH: netImMin = 32; netImPeriodicity = periodicity; break;
    }
}

SettingsComplex Scene3DComplex::getSettings() const
{
    SettingsComplex sets;
    sets.common = getCommonSettings();
    sets.centerX = centerX;
    sets.centerY = centerY;
    sets.centerZ = centerZ;
    sets.isSurfaceEnable = isSurfaceEnable;
    sets.netRePeriodicity = netRePeriodicity;
    sets.netImPeriodicity = netImPeriodicity;
    sets.rangeX = rangeX;
    sets.rangeY = rangeY;
    sets.rangeZ = rangeZ;
    sets.surfaceColor_0 = surfaceColor_0;
    sets.surfaceColor_Pi_2 = surfaceColor_Pi_2;
    sets.surfaceColor_Pi = surfaceColor_Pi;
    sets.surfaceColor_3_Pi_2 = surfaceColor_3_Pi_2;
    sets.varName = varName;
    return sets;
}

void Scene3DComplex::drawLegend(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    QSize axisSize((float)legendSizeRatio * height() * 0.75, (float)legendSizeRatio *height()*0.75);
    QSize legendSize((float)legendSizeRatio * height() * 0.75, (float)legendSizeRatio * height()
                     * 1.5);
    QImage image(legendSize, QImage::Format_ARGB32);
    image.fill(QColor(0xff, 0xff, 0xff, round((float)legendBackOpacity * 0xff)));
    QPen pen(Qt::gray);
    pen.setWidthF(5.0);
    QFont font;
    font.setPointSizeF((float)axisSize.height() / 18.0 * 1.33);
    QFontMetrics fm(font);
    QPainter imagePainter;
    imagePainter.begin(&image);
    imagePainter.setRenderHint(QPainter::Antialiasing);
    imagePainter.setPen(pen);
    imagePainter.setFont(font);
    imagePainter.drawRect(0, 0, legendSize.width(), legendSize.height());
    QString s1 = QString("Re:"), s2 = QString("Im:"), s3("|F|:");
    pen.setColor(Qt::black);
    imagePainter.setPen(pen);
    imagePainter.drawText(axisSize.width() / 6 - fm.width(s1) / 2, axisSize.height() / 15 *1.33,s1);
    imagePainter.drawText(axisSize.width() / 2 - fm.width(s2), axisSize.height() / 15 * 1.33, s2);
    imagePainter.drawText(5 * axisSize.width() / 6 - fm.width(s3), axisSize.height() / 15 *1.33,s3);

    for (int i = 0; i < 3; i++) {
        imagePainter.setPen(Qt::NoPen);
        if (i == 0) {
            QBrush brush(axis1Color);
            imagePainter.setBrush(brush);
        } else if (i == 1) {
            QBrush brush(axis2Color);
            imagePainter.setBrush(brush);
        } else {
            QBrush brush(axis3Color);
            imagePainter.setBrush(brush);
        }
        imagePainter.drawRect(i * axisSize.width() / 3 + axisSize.width() / 50 + 3,
                              4 * axisSize.height() / 30,
                              axisSize.width() / 40 + 1, 25 * axisSize.height() / 30);
        QVector<double> points;
        double min, range;
        pen.setColor(Qt::black);
        pen.setWidthF((float)1.0 + (float)axisSize.width() / 200.0 * 1.33);
        imagePainter.setPen(pen);
        font.setPointSizeF((float)axisSize.height() / 50.0 * 1.33);
        imagePainter.setFont(font);
        if (i == 0) {
            points = axisXPoints();
            min = centerX - rangeX / 2.0;
            range = rangeX;
        } else if (i == 1){
            points = axisYPoints();
            min = centerY - rangeY / 2.0;
            range = rangeY;
        } else {
            points = axisZPoints();
            min = centerZ - rangeZ / 2.0;
            range = rangeZ;
        }
        for (int j = 0; j < points.length(); j++) {
            QLineF line((float)i * axisSize.width() / 3.0 + 3.0, (float)29.0 *
                        axisSize.height() / 30.0 - 25.0 * axisSize.height() / 30.0 *
                        (points[j] - min) / range, (float)i * axisSize.width() / 3.0 + 3.0 +
                        axisSize.width() / 50.0 + axisSize.width() / 40.0 + 1.0, (float)29.0 *
                        axisSize.height() / 30.0 - 25.0 * axisSize.height() / 30.0 *
                        (points[j] - min) / range);
            if (j % (points.length() / 5) == 0) {
                line.setP2(QPointF((float)line.x2() + axisSize.width() / 66.0, line.y2()));
                if (fabs(points[j] / points[j > 0 ? j - 1 : 0]) < 1.0e-8)
                    points[j] = 0.0;
                imagePainter.drawText((float)line.x2() + 3.0, (float)line.y1() + font.pointSizeF() /
                                      2.0, QString::number(points[j], 'g', 8));
            }
            imagePainter.drawLine(line);
        }
    }
    QConicalGradient gradient((float)legendSize.width() / 2.0, (float)legendSize.height() -
                              legendSize.width() / 2.0, 0.0);
    gradient.setColorAt(0.0, surfaceColor_0);
    gradient.setColorAt(0.25, surfaceColor_Pi_2);
    gradient.setColorAt(0.5, surfaceColor_Pi);
    gradient.setColorAt(0.75, surfaceColor_3_Pi_2);
    gradient.setColorAt(1.0, surfaceColor_0);
    imagePainter.setBrush(gradient);
    pen.setWidth(1);
    pen.setColor(Qt::black);
    imagePainter.setPen(pen);
    float phaseSize = 0.7;
    imagePainter.drawEllipse((float)legendSize.width() * (1.0 - phaseSize) / 2.0,
                             (float)legendSize.height() - legendSize.width() * (phaseSize + 1.0) / 2.0,
                             (float)legendSize.width() * phaseSize,
                             (float)legendSize.width() * phaseSize);
    font.setPointSizeF((float)legendSize.width() * (1.0 - phaseSize) / 2.0 / 4.0);
    imagePainter.setFont(font);
    imagePainter.drawText((float)legendSize.width() * (1.0 - phaseSize) / 2.0 -
                          imagePainter.fontMetrics().width("pi") - font.pointSizeF(),
                          (float)legendSize.height() - legendSize.width() / 2.0 + font.pointSizeF() /
                          2.0, QString("pi"));
    imagePainter.drawText((float)legendSize.width() / 2.0 -
                          imagePainter.fontMetrics().width("pi/2") / 2.0, (float)legendSize.height() -
                          legendSize.width() * (1.0 + phaseSize) / 2.0 - font.pointSizeF() / 2.0,
                          QString("pi/2"));
    imagePainter.drawText((float)legendSize.width() * (1.0 + phaseSize) / 2.0 + font.pointSizeF(),
                          (float)legendSize.height() - legendSize.width() / 2.0 + font.pointSizeF(),
                          QString("0"));
    imagePainter.drawText((float)legendSize.width() / 2.0 - imagePainter.fontMetrics().width("-pi/2") /
                          2.0, (float)legendSize.height() - legendSize.width() * (1 - phaseSize) /
                          2.0 + 1.5 * font.pointSizeF(), QString("-pi/2"));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(1.0);
    painter.drawImage(width() - legendSize.width() - 10, height() - legendSize.height() - 10, image);
}

QVector<double> Scene3DComplex::axisXPoints() const
{
    return axisPoints(centerX, rangeX, netReMin);
}

QVector<double> Scene3DComplex::axisYPoints() const
{
    return axisPoints(centerY, rangeY, netImMin);
}

void Scene3DComplex::updateTime()
{
    if (isActivatedTime)
        function.setVariableValue(timeName, (double)startTime.msecsTo(QTime::currentTime())/1000.0);
}

void Scene3DComplex::updateSurface()
{
    double *pRe = nullptr, *pIm = nullptr;
    if (function.getVariable(varName) != nullptr)
        pRe = function.getVariable(varName)->getValuePtr()->pRe();
    if (function.getVariable(varName) != nullptr)
        pIm = function.getVariable(varName)->getValuePtr()->pIm();
    // Next are RGB of surface of different phases
    float r_0 = surfaceColor_0.redF();
    float g_0 = surfaceColor_0.greenF();
    float b_0 = surfaceColor_0.blueF();
    float r_Pi_2 = surfaceColor_Pi_2.redF();
    float g_Pi_2 = surfaceColor_Pi_2.greenF();
    float b_Pi_2 = surfaceColor_Pi_2.blueF();
    float r_Pi = surfaceColor_Pi.redF();
    float g_Pi = surfaceColor_Pi.greenF();
    float b_Pi = surfaceColor_Pi.blueF();
    float r_3_Pi_2 = surfaceColor_3_Pi_2.redF();
    float g_3_Pi_2 = surfaceColor_3_Pi_2.greenF();
    float b_3_Pi_2 = surfaceColor_3_Pi_2.blueF();
    float sR, sG, sB; // surface`s (r, g, b)
    Complex result;
    float phase;

    GLfloat *surfaceVertex = this->surfaceVertex.data();
    GLfloat *surfaceColor = this->surfaceColor.data();
    int length = this->surfaceVertex.length() / 3;
    for (int i = 0; i < length; i++) {
        if (pRe != nullptr)
            *pRe = surfaceVertex[3 * i + 0];
        if (pIm != nullptr)
            *pIm = surfaceVertex[3 * i + 1];
        result = function.result();
        if (qIsNaN(result)) {
            if (pRe != nullptr)
                *pRe = surfaceVertex[3 * i + 0] + rangeX / (double)xPolygonNum / 100.0;
            if (pIm != nullptr)
                *pIm = surfaceVertex[3 * i + 1] + rangeX / (double)yPolygonNum / 100.0;
            result = function.result();
            if (qIsNaN(result)) {
                if (pRe != nullptr)
                    *pRe = surfaceVertex[3 * i + 0] + rangeX / (double)xPolygonNum / 100.0;
                if (pIm != nullptr)
                    *pIm = surfaceVertex[3 * i + 1] - rangeX / (double)yPolygonNum / 100.0;
                result = function.result();
                if (qIsNaN(result))
                    result = centerZ;
            }
        }
        surfaceVertex[3 * i + 2] = fabs(result).re();
        phase = (argument(result).re()) / M_PI_2;
        if (phase <= -1.0) {
            sR = (r_Pi * (-phase - 1.0) + r_3_Pi_2 * (phase + 2.0));
            sG = (g_Pi * (-phase - 1.0) + g_3_Pi_2 * (phase + 2.0));
            sB = (b_Pi * (-phase - 1.0) + b_3_Pi_2 * (phase + 2.0));
        } else if (phase <= 0.0) {
            sR = (r_3_Pi_2 * (-phase) + r_0 * (phase + 1.0));
            sG = (g_3_Pi_2 * (-phase) + g_0 * (phase + 1.0));
            sB = (b_3_Pi_2 * (-phase) + b_0 * (phase + 1.0));
        } else if (phase <= 1.0) {
            sR = (r_0 * (-phase + 1.0) + r_Pi_2 * (phase));
            sG = (g_0 * (-phase + 1.0) + g_Pi_2 * (phase));
            sB = (b_0 * (-phase + 1.0) + b_Pi_2 * (phase));
        } else {
            sR = (r_Pi_2 * (-phase + 2.0) + r_Pi * (phase - 1.0));
            sG = (g_Pi_2 * (-phase + 2.0) + g_Pi * (phase - 1.0));
            sB = (b_Pi_2 * (-phase + 2.0) + b_Pi * (phase - 1.0));
        }
        surfaceColor[4 * i + 0] = sR;
        surfaceColor[4 * i + 1] = sG;
        surfaceColor[4 * i + 2] = sB;
    }
}

void Scene3DComplex::updateNetBase()
{
    QVector<double> pointsX = axisXPoints();
    QVector<double> pointsY = axisYPoints();
    if (pointsX.length() < 2 || pointsY.length() < 2)
        return;
    uint xNum = pointsX.length();
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

void Scene3DComplex::updateNet()
{
    double *pRe = nullptr, *pIm = nullptr;
    if (function.getVariable(varName) != nullptr)
        pRe = function.getVariable(varName)->getValuePtr()->pRe();
    if (function.getVariable(varName) != nullptr)
        pIm = function.getVariable(varName)->getValuePtr()->pIm();

    int length = netVertex.length() / 3;
    GLfloat *netVertex = this->netVertex.data();
    for (int i = 0; i < length; i++) {
        if (pRe != nullptr)
            *pRe = netVertex[3 * i + 0];
        if (pIm != nullptr)
            *pIm = netVertex[3 * i + 1];
        netVertex[3 * i + 2] = fabs(function.result()).re();
    }
}
void Scene3DComplex::runSettings()
{
    SettingsComplexDialog dialog(getSettings());
    double tStep = this->timeStep;
    this->stopSelfUpdating();
    if (dialog.exec() == QDialog::Accepted) {
        this->startSelfUpdating(tStep);
        SettingsComplex sets = dialog.getSettings();
        setCommonSettings(sets.common);
        centerX = sets.centerX;
        centerY = sets.centerY;
        centerZ = sets.centerZ;
        isSurfaceEnable = sets.isSurfaceEnable;
        setNetRePeriodicity(sets.netRePeriodicity);
        setNetImPeriodicity(sets.netImPeriodicity);
        rangeX = sets.rangeX;
        rangeY = sets.rangeY;
        rangeZ = sets.rangeZ;
        surfaceColor_0 = sets.surfaceColor_0;
        surfaceColor_Pi_2 = sets.surfaceColor_Pi_2;
        surfaceColor_Pi = sets.surfaceColor_Pi;
        surfaceColor_3_Pi_2 = sets.surfaceColor_3_Pi_2;
        varName = sets.varName;
        compiler.initContextFromFile(this->contextFileName);
        setString(sets.common.funcString);
        updateBase();
        updateScene();
        repaint();
    }
}

void Scene3DComplex::runArguments()
{
    QVector<QString> names;
    QVector<QString> values;
    for (int i = 0; i < function.getVariableList()->length(); i++) {
        QString name = (*function.getVariableList())[i].getName();
        if (name == varName || name == timeName)
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
        QFunction<Complex> F;
        int o = 0;
        for (int i = 0; i < function.getVariableNumber(); i++) {
            QString name = (*function.getVariableList())[i].getName();
            if (name == varName || name == timeName)
                continue;
            F.setString(values[o], compiler);
            (*function.getVariableList())[i].setValue(F.result());
            o++;
        }
        updateScene();
        repaint();
    }
}

void Scene3DComplex::drawNet() const
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, netVertex.data());
    glDisableClientState(GL_COLOR_ARRAY);
    glColor3f(netColor.redF(), netColor.greenF(), netColor.blueF());
    glLineWidth(netWidth);
    glDrawElements(GL_LINES, netIndex.length(), GL_UNSIGNED_INT, netIndex.data());
}

void Scene3DComplex::drawBoundingAxis()
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
    const int rtianglesInTip = 20;
    const float darker = 0.5;
    const double arrowLength = 1.0 / 20.0;
    const double arrowWidth = 1.0 / 70.0;
    glEnd();

    // Tips of arrows
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < rtianglesInTip; i++) {
        x1 = cos(2.0 * M_PI / (double)rtianglesInTip * (double)i);
        y1 = sin(2.0 * M_PI / (double)rtianglesInTip * (double)i);
        x2 = cos(2.0 * M_PI / (double)rtianglesInTip * (double)(i + 1.0));
        y2 = sin(2.0 * M_PI / (double)rtianglesInTip * (double)(i + 1.0));
        glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
        glVertex3d(centerX, centerY - rangeY / 2.0, centerZ - rangeZ / 2.0);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x1,
                   centerZ - rangeZ / 2.0 + rangeZ * arrowWidth * y1);
        glVertex3d(centerX - rangeX * arrowLength, centerY - rangeY / 2.0 + rangeY * arrowWidth *x2,
                   centerZ - rangeZ / 2.0 + rangeZ * arrowWidth * y2);
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF()*darker,axis1Color.blueF()*darker);
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
        glColor3f(axis1Color.redF() * darker, axis1Color.greenF()*darker,axis1Color.blueF()*darker);
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
        glColor3f(axis2Color.redF() * darker, axis2Color.greenF()*darker,axis2Color.blueF()*darker);
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
        glColor3f(axis2Color.redF() * darker, axis2Color.greenF()*darker,axis2Color.blueF()*darker);
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
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF()*darker,axis3Color.blueF()*darker);
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
        glColor3f(axis3Color.redF() * darker, axis3Color.greenF()*darker,axis3Color.blueF()*darker);
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
        QVector<double> baseXPoints = axisXBasePoints(netBaseReNum);
        QVector<double> baseYPoints = axisYBasePoints(netBaseImNum);
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
