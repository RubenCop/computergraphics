#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
    void resetCameraView();
    void resetScale();
    void updateRotation(int x, int y, int z);
    void updateModel(QString name);
    void updateShader(QString name);
    void updateScale(float scale);
    //camera initialization
    float camPosX = 0, camPosY = 0, camPosZ = 4; //Starting camera position
    QVector3D eye = QVector3D(camPosX,camPosY,camPosZ); //Initialize camera position
    float initCamPosX = camPosX; //set initial camera positions (used for reset button)
    float initCamPosY = camPosY;
    float initCamPosZ = camPosZ;

    //center initializtion model 1
    float centerX = 0, centerY = 0, centerZ = 0; //Center position
    float initCenterPosX = centerX;
    float initCenterPosY = centerY;
    float initCenterPosZ = centerZ;
    QVector3D centre = QVector3D(centerX,centerY,centerZ);
    //rotate/translate initialization model 1
    float newX, newY, newZ;

    //center initializtion model 2
    float centerX2 = 2, centerY2 = 2, centerZ2 = 4; //Center position
    float initCenterPosX2 = centerX2;
    float initCenterPosY2 = centerY2;
    float initCenterPosZ2 = centerZ2;
    QVector3D centre2 = QVector3D(centerX2,centerY2,centerZ2);
    //rotate/translate initialization model 2
    float newX2, newY2, newZ2;

    //other variables
    int xStart, yStart;
    float newScale = 1.0;
    int screenWidth, screenHeight;
    int numVertices = 0;
    QVector<QVector3D> colors;
    void loadTexture(QString file, GLuint texPointer);
    QVector<quint8> imageToBytes(QImage image);
    QVector3D convertHSLtoRGB(float H, float S, float L);

    //Animation parameters from animate() in mainview.cpp
    float xRate = 1.0;

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();
    void animate();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private:
    QOpenGLDebugLogger *debugLogger;

    void createShaderPrograms();
    void createBuffers();
    void updateBuffers();
    void updateUniforms();

    // Raytracer scene functions
    void renderSphere(QVector3D pos, QVector3D color, QVector4D material, QVector3D lightpos);
    void renderObject(QVector3D pos, QVector3D lightpos, QVector3D animateRotation, QVector3D animateTranslation);
    void renderRaytracerScene();
    void renderAnimation();

    /* Add your private members below */
    void loadModel(QString filename, GLuint bufferObject);

    // Shader programs, GLint for uniforms/buffer objects, other variables
    QOpenGLShaderProgram *mainShaderProg;

    QTimer timer; // timer used for animation

    Model *currentModel;
    GLuint cubeBO;

    //1.4
    GLuint vao;
    GLuint bo;
    GLuint boCol;
    GLuint texCoords, texCoords2;
    GLuint normalInt;

    GLuint texPointer, texPointer2;
    GLint texUniform, texUniform2;


    QVector<QVector2D> textureCoords, textureCoords2;

    unsigned numTris;

    //T2
    QMatrix4x4 model;
    QMatrix4x4 model2;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix3x3 normalMatrix;
    QVector3D matColor, lightPos;
    QVector4D intensities;

    QVector<quint8> textureVector, textureVector2;

    GLint ULmodel, ULmodel2, ULview, ULprojection, ULnormal;
    GLint ULintensities, ULmatCol, ULlightPos;


    /* End of private members */

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

};

#endif // MAINVIEW_H
