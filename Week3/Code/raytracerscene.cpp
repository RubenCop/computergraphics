#include "mainview.h"

void MainView::renderSphere(QVector3D pos, QVector3D color, QVector4D material, QVector3D lightpos)
{
    // OpenGL assignment 1, part 2: create a function to render the sphere
    // Use Model(":/models/sphere.obj") for the model

    // you must remove these Q_UNUSED when you implement this function
    //Q_UNUSED(pos)
    //Q_UNUSED(color)
    Q_UNUSED(material)
    Q_UNUSED(lightpos)
    model.setToIdentity();
    model.rotate(newX,1,0,0);
    model.rotate(newY,0,1,0);
    model.rotate(newZ,0,0,1);
    model.scale(newScale,newScale,newScale);
    //qDebug() << "start model " << model << endl;
    model.translate(pos);

    intensities = material;

    updateUniforms();

    QVector3D intensities = QVector3D(1,1,1);
    //qDebug() << "translated model " << model << endl;
    colors.clear();
    for (int i=0; i<numVertices; i++){
        colors.push_back(color);
    }
    updateBuffers();

    glBindVertexArray(vao);
    //qDebug() << model << endl;

    glDrawArrays(GL_TRIANGLES,0,numVertices);

    //Needs to call drawVertexArrays
    //we have vertices from mainview
    //
    //qDebug() << "hello" << endl;
}

/**
 * Renders a similar scene used for the raytracer:
 * 5 colored spheres with a single light
 */
void MainView::renderRaytracerScene()
{
    QVector3D lightpos = QVector3D(-200,600,1500);

    // Blue sphere
    renderSphere(QVector3D(90,320,100),QVector3D(0,0,1),QVector4D(0.2f,0.7f,0.5f,64),lightpos);

    // Green sphere
    renderSphere(QVector3D(210,270,300),QVector3D(0,1,0),QVector4D(0.2f,0.3f,0.5f,8),lightpos);

    // Red sphere
    renderSphere(QVector3D(290,170,150),QVector3D(1,0,0),QVector4D(0.2f,0.7f,0.8f,32),lightpos);

    // Yellow sphere
    renderSphere(QVector3D(140,220,400),QVector3D(1,0.8f,0),QVector4D(0.2f,0.8f,0.0f,1),lightpos);

    // Orange sphere
    renderSphere(QVector3D(110,130,200),QVector3D(1,0.5f,0),QVector4D(0.2f,0.8f,0.5f,32),lightpos);
}
