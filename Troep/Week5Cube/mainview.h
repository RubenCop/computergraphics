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
    float newScale = 1.0;
    float newX, newY, newZ;
    //##The eye/camera position and the center (focuspoint of the camera) can be initialized here. They are used in mainview.cpp
    float camPosX = 0, camPosY = 0, camPosZ = 4; //Starting camera position
    float centerX = 0, centerY = 0, centerZ = 0; //Center position

    float initCamPosX = camPosX; //set initial camera positions (used for reset button)
    float initCamPosY = camPosY;
    float initCamPosZ = camPosZ;
    float initCenterPosX = centerX;
    float initCenterPosY = centerY;
    float initCenterPosZ = centerZ;
    QVector3D eye = QVector3D(camPosX,camPosY,camPosZ); //Initialize camera position
    QVector3D centre = QVector3D(centerX,centerY,centerZ);
    int xStart, yStart;
    int screenWidth, screenHeight;
    int numVertices = 0;
    QVector<QVector3D> colors;
    void loadTexture(QString file, GLuint texPointer);
    QVector<quint8> imageToBytes(QImage image);

    /* Add your public members below */

    /* End of public members */

    QVector3D convertHSLtoRGB(float H, float S, float L);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

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
    void renderRaytracerScene();

    /* Add your private members below */
    void loadModel(QString filename, GLuint bufferObject);

    // Shader programs, GLint for uniforms/buffer objects, other variables
    QOpenGLShaderProgram *mainShaderProg;

    QTimer timer; // timer used for animation

    Model *cubeModel;
    GLuint cubeBO;

    //1.4
    GLuint vao;
    GLuint bo;
    GLuint boCol;
    GLuint texCoords;
    GLuint normalInt;

    GLuint texPointer;
    GLint texUniform;


    QVector<QVector2D> textureCoords;

    unsigned numTris;

    //T2
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix3x3 normalMatrix;
    QVector3D matColor, lightPos;
    QVector4D intensities;

    QVector<quint8> textureVector;

    GLint ULmodel, ULview, ULprojection, ULnormal;
    GLint ULintensities, ULmatCol, ULlightPos;


    /* End of private members */

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

};

#endif // MAINVIEW_H
