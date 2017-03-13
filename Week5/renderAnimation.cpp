#include "mainview.h"

void MainView::renderObject(QVector3D pos, QVector3D lightpos, QVector3D animateRotation, QVector3D animateTranslation)
{
    // OpenGL assignment 1, part 2: create a function to render the sphere
    // Use Model(":/models/sphere.obj") for the model

    model.setToIdentity();      //reset matrix
    model.translate(centre);    //rotate around the point the camera is focussed on
    model.rotate(newX + newX*animateRotation.x(),1,0,0);
    model.rotate(newY + newY*animateRotation.y(),0,1,0);
    model.rotate(newZ + newZ*animateRotation.z(),0,0,1);
    //qDebug() << animateRotation.x() << endl;
    model.rotate(animateRotation.x(),1,0,0);
    model.rotate(animateRotation.y(),0,1,0);
    model.rotate(animateRotation.z(),0,0,1);

    model.scale(newScale,newScale,newScale);
    model.translate(pos-centre);
    //pass uniforms
    /*
    ULintensities = glGetUniformLocation(mainShaderProg->programId(), "intensities");
    glUniform4fv(ULintensities, 1, &material[0]);
    ULmatCol= glGetUniformLocation(mainShaderProg->programId(), "matColor");
    glUniform3fv(ULmatCol,1, &color[0]);
    */
    ULlightPos = glGetUniformLocation(mainShaderProg->programId(), "lightPos");
    glUniform3fv(ULlightPos,1, &lightpos[0]);

    //normalMatrix = (view * model).normalMatrix();

    updateUniforms();

    /*
    colors.clear();
    for (int i=0; i<numVertices; i++){
        colors.push_back(color);
    }
    */

    //updateBuffers();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,numVertices);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texPointer);
    glUniform1i(texUniform,0);
}

/**
 * Renders a similar scene used for the raytracer:
 * 5 colored spheres with a single light
 */
void MainView::renderAnimation()
{
    QVector3D lightpos = QVector3D(-200,600,1500);
    // Blue sphere
    renderObject(QVector3D(0,0,0),lightpos,QVector3D(0,2,0),QVector3D(0,0,0));

    renderObject(QVector3D(1,0,0),lightpos,QVector3D(0,-2.7,0),QVector3D(0,0,0));

    renderObject(QVector3D(2,0,0),lightpos,QVector3D(0,-1.1,0),QVector3D(0,0,0));

    renderObject(QVector3D(3,0,0),lightpos,QVector3D(0,-1.5,0),QVector3D(0,0,0));

    renderObject(QVector3D(4,0,0),lightpos,QVector3D(0,-1.3,0),QVector3D(0,0,0));

    renderObject(QVector3D(5,0,0),lightpos,QVector3D(0,-1.5,0),QVector3D(0,0,0));

    renderObject(QVector3D(6,0,0),lightpos,QVector3D(0,-2.0,0),QVector3D(0,0,0));

    renderObject(QVector3D(7,0,0),lightpos,QVector3D(0,-1.8,0),QVector3D(0,0,0));

    renderObject(QVector3D(8,0,0),lightpos,QVector3D(0,-2.5,0),QVector3D(0,0,0));



}
