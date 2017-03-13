#include "mainview.h"

#include <QDebug>

void MainView::updateRotation(int x, int y, int z)
{
    qDebug() << "updateRotation(" << x << "," << y << "," << z << ");";
    // divide by 100 to decrease sensitivity
    newX = x;
    newY = y;
    newZ = z;
    update();
}

void MainView::resetCameraView()
{
    camPosX = initCamPosX;
    camPosY = initCamPosY;
    camPosZ = initCamPosZ;
    update();
}

void MainView::resetScale()
{
    newScale = 1;
    update();
}


void MainView::updateModel(QString name)
{
    qDebug() << "updateModel(" << name << ")";
    // TODO: load new model, based on name

    update();
}

void MainView::updateShader(QString name)
{
    qDebug() << "updateShader(" << name << ")";
    // TODO: switch shaders/renderingprocesses, based on name

    update();
}

void MainView::updateScale(float scale)
{
    qDebug() << "updateScale(" << scale << ")";
    // TODO: update model scale
    newScale = scale;

    update();
}


// Triggered by pressing a key
void MainView::keyPressEvent(QKeyEvent *ev)
{
    int moveStep = 1; //Initialize the unit (speed) with which the camera should move around
    switch(ev->key()) {
    case 'Q': qDebug() << "Q pressed";
        camPosX = camPosX - moveStep;
        break;
    case 'W': qDebug() << "W pressed";
        camPosX = camPosX + moveStep;
        break;
    case 'A': qDebug() << "A pressed";
        camPosY = camPosY - moveStep;
        break;
    case 'S': qDebug() << "S pressed";
        camPosY = camPosY + moveStep;
        break;
    case 'Z': qDebug() << "Z pressed";
        camPosZ = camPosZ - moveStep;
        break;
    case 'X': qDebug() << "X pressed";
        camPosZ = camPosZ + moveStep;
        break;
    default:
        // ev->key() is an integer. For alpha numeric characters keys it equivalent with the char value ('A' == 65, '1' == 49)
        // Alternatively, you could use Qt Key enums, see http://doc.qt.io/qt-5/qt.html#Key-enum
        qDebug() << ev->key() << "pressed";
        break;
    }

    // Used to update the screen after changes
    update();
}

// Triggered by releasing a key
void MainView::keyReleaseEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
    case 'A': qDebug() << "A released"; break;
    default:
        qDebug() << ev->key() << "released";
        break;
    }

    update();
}

// Triggered by clicking two subsequent times on any mouse button
// It also fires two mousePress and mouseRelease events!
void MainView::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse double clicked:" << ev->button();

    update();
}

// Triggered when moving the mouse inside the window (only when the mouse is clicked!)
void MainView::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "x" << ev->x() << "y" << ev->y();

    float currentX = ev->x();
    float currentY = ev->y();
    // divide by 10 to decrease sensitivity
    newX += (currentY - yStart)/10;
    newY += (currentX - xStart)/10;

    xStart = currentX;
    yStart = currentY;


    update();
}

// Triggered when pressing any mouse button
void MainView::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button pressed:" << ev->button();
    xStart = ev->x();
    yStart = ev->y();

    update();
    // Do not remove the line below, clicking must focus on this widget!
    this->setFocus();
}

// Triggered when releasing any mouse button
void MainView::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button released" << ev->button();

    update();
}

// Triggered when clicking scrolling with the scroll wheel on the mouse
void MainView::wheelEvent(QWheelEvent *ev)
{
    // Implement something
    qDebug() << "Mouse wheel:" << ev->delta();
    newScale += (float)ev->delta()/10000;
    qDebug() << "wheel scale " << newScale << endl;

    update();
}
