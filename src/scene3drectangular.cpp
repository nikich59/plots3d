#include "scene3drectangular.h"

Scene3DRectangular::Scene3DRectangular(QWidget *parent) : Scene3D(parent)
{
    rangeX = 1.0;
    rangeY = 1.0;
    rangeZ = 1.0;
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    setSurfaceQuality(LOW);
}

QVector<double> Scene3DRectangular::axisZPoints() const
{
    return axisPoints(centerZ, rangeZ, isolineMin);
}

void Scene3DRectangular::setSurfaceQuality(uint quality)
{
    switch(quality) {
    case VERY_LOW: xPolygonNum = 90; yPolygonNum = 90; surfaceQuality = quality; break;
    case LOW: xPolygonNum = 140; yPolygonNum = 140; surfaceQuality = quality; break;
    case DECREASED: xPolygonNum = 200; yPolygonNum = 200; surfaceQuality = quality; break;
    case MIDDLE: xPolygonNum = 300; yPolygonNum = 300; surfaceQuality = quality; break;
    case INCREASED: xPolygonNum = 450; yPolygonNum = 450; surfaceQuality = quality; break;
    case HIGH: xPolygonNum = 700; yPolygonNum = 700; surfaceQuality = quality; break;
    case VERY_HIGH: xPolygonNum = 1000; yPolygonNum = 1000; surfaceQuality = quality; break;
    case ULTRA_HIGH: xPolygonNum = 2500; yPolygonNum = 2500; surfaceQuality = quality; break;
    }
}

void Scene3DRectangular::updateSurfaceBase()
{
    surfaceColor.resize(surfaceVertexNumber() * 4);
    surfaceIndex.resize(surfacePolygonNumber() * 4);
    surfaceVertex.resize(surfaceVertexNumber() * 3);

    GLfloat *surfaceVertex = this->surfaceVertex.data();
    GLuint *surfaceIndex = this->surfaceIndex.data();
    GLfloat *surfaceColor = this->surfaceColor.data();

    for (int x = 0; x <= xPolygonNum; x++)
        for (int y = 0; y <= yPolygonNum; y++) {
            surfaceVertex[3 * (x * (yPolygonNum + 1) + y) + 0] = centerX - rangeX / 2.0 +
                    (GLfloat) x * rangeX / (xPolygonNum/* + 1*/); // X
            surfaceVertex[3 * (x * (yPolygonNum + 1) + y) + 1] = centerY - rangeY / 2.0 +
                    (GLfloat) y * rangeY / (yPolygonNum/* + 1*/); // Y
        }
    for (int x = 0; x < xPolygonNum; x++)
        for (int y = 0; y < yPolygonNum; y++) {
            surfaceIndex[4 * (x * yPolygonNum + y) + 0] = x * (yPolygonNum + 1) + y;
            surfaceIndex[4 * (x * yPolygonNum + y) + 1] = x * (yPolygonNum + 1) + y + 1;
            surfaceIndex[4 * (x * yPolygonNum + y) + 2] = (x + 1) * (yPolygonNum + 1) + y + 1;
            surfaceIndex[4 * (x * yPolygonNum + y) + 3] = (x + 1) * (yPolygonNum + 1) + y;
        }

    int length = this->surfaceColor.length() / 4;
    for (int i = 0; i < length; i++) {
        surfaceColor[i * 4 + 0] = 0.5;
        surfaceColor[i * 4 + 1] = 0.5;
        surfaceColor[i * 4 + 2] = 0.5;
        surfaceColor[i * 4 + 3] = 1.0;
    }
}

void Scene3DRectangular::glTransformations()
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

void Scene3DRectangular::drawCentralAxis()
{
    glLineWidth(2.0);
    glDisable(GL_DEPTH_TEST);
    GLfloat X[] = {centerX, centerY, centerZ, centerX + rangeX * axisLengthRatio, centerY, centerZ};
    GLfloat Y[] = {centerX, centerY, centerZ, centerX, centerY + rangeY * axisLengthRatio, centerZ};
    GLfloat Z[] = {centerX, centerY, centerZ, centerX, centerY, centerZ + rangeZ * axisLengthRatio /
                  verticalExtension};
    GLuint i[2] = {0, 1};
    glDisableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, X);
    glColor3f(axis1Color.redF(), axis1Color.greenF(), axis1Color.blueF());
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, i);
    glVertexPointer(3, GL_FLOAT, 0, Y);
    glColor3f(axis2Color.redF(), axis2Color.greenF(), axis2Color.blueF());
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, i);
    glVertexPointer(3, GL_FLOAT, 0, Z);
    glColor3f(axis3Color.redF(), axis3Color.greenF(), axis3Color.blueF());
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, i);
    glEnable(GL_DEPTH_TEST);
}
