#include "mainview.h"
#include "math.h"
#include <iostream>

#include <QDateTime>

QVector<QVector3D> vertices;
QVector<QVector3D> normals;

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    delete cubeModel;

    // Free Buffer Objects before Vertex Arrays

    // Free the main shader
    delete mainShaderProg;

    //1.5
    glDeleteBuffers(1,&bo);
    glDeleteBuffers(1,&boCol);
    glDeleteVertexArrays(1,&vao);

    glDeleteTextures(1,&texBendi);

    debugLogger->stopLogging();

    qDebug() << "MainView destructor";
}

/**
 * @brief MainView::createShaderPrograms
 *
 * Creates the shaderprogram for OpenGL rendering
 */
void MainView::createShaderPrograms() {
    // Qt wrapper (way cleaner than using pure OpenGL)
    mainShaderProg = new QOpenGLShaderProgram();
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.glsl");
    mainShaderProg->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.glsl");
    mainShaderProg->link();

    ULmodel = glGetUniformLocation(mainShaderProg->programId(), "model");
    ULview = glGetUniformLocation(mainShaderProg->programId(), "view");
    ULprojection = glGetUniformLocation(mainShaderProg->programId(), "projection");
    ULnormal = glGetUniformLocation(mainShaderProg->programId(), "normalMatrix");

    ULtexCol = glGetUniformLocation(mainShaderProg->programId(),"texCol");
    /* Add your other shaders below */

    /* End of custom shaders */

    // Store the locations (pointers in gpu memory) of uniforms in Glint's

}

/**
 * @brief MainView::createBuffers
 *
 * Creates necessary buffers for your application
 */
void MainView::createBuffers() {
    // 1.6
    glGenVertexArrays(1,&vao);
    qDebug() << "vao" << endl;
    glBindVertexArray(vao);

    glGenBuffers(1,&bo);
    glGenBuffers(1,&boCol);

    glBindBuffer(GL_ARRAY_BUFFER,bo);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,boCol);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);


   // glGenVertexArrays(3,&texBendi);
    glGenBuffers(1,&texBendi);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(float)*textureVec.length()* 3,textureVec.data(),GL_STATIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, texBendi);

    //glBindVertexArray(texBendi);
    glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(3);


    //empty bind
    glBindVertexArray(0);
}


void MainView::loadModel(QString filename, GLuint bufferObject) {

    cubeModel = new Model(filename);
    numTris = cubeModel->getNumTriangles();

    Q_UNUSED(bufferObject);

    // TODO: implement loading of model into Buffer Objects
    vertices = cubeModel->getVertices();
    normals = cubeModel->getNormals();
    numVertices = vertices.length();
    srand (time(NULL));

    // Generate random colors
   /* for (int i = 0; i < numVertices; i++)
    {
        //srand (time(NULL));
        QVector3D col = QVector3D(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        colors.push_back(col);
    }*/
    glBindBuffer(GL_ARRAY_BUFFER,bo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*vertices.length() * 3,vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,boCol);
    //updateBuffers();
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*normals.length()* 3,normals.data(),GL_STATIC_DRAW);

}

//1.2
void MainView::loadTexture(QString file, GLuint texBendi) {
    qDebug() << "Loading texture" << endl;
    QImage texture;
    texture.load(file);
    //1.3
    QVector<quint8> textureVec = imageToBytes(texture);

    //1.4
    glBindTexture(GL_TEXTURE_2D, texBendi);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    //1.5
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width(),texture.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,textureVec.data());
    //1.6 Optional for mipmapping
    //glGenerateMipmap(GL_TEXTURE_2D);

}




void MainView::updateBuffers() {
    // Change the data inside buffers (if you want)
    // make sure to change GL_STATIC_DRAW to GL_DYNAMIC_DRAW
    // in the call to glBufferData for better performance
    //glBufferData(GL_ARRAY_BUFFER,sizeof(float)*colors.length()* 3,colors.data(),GL_DYNAMIC_DRAW);
}


void MainView::updateUniforms() {
    // TODO: update the uniforms in the shaders using the glUniform<datatype> functions

    glUniformMatrix4fv(ULmodel, 1, GL_FALSE, model.data());
    glUniformMatrix4fv(ULview, 1, GL_FALSE, view.data());
    glUniformMatrix4fv(ULprojection, 1, GL_FALSE, projection.data());
    glUniformMatrix3fv(ULnormal, 1, GL_FALSE, normalMatrix.data());

    glUniform1i(ULtexCol,1);

    //glUniformMatrix4fv(ULprojection, 1, GL_FALSE, projection.data());
    //glUniform3f();
    //glUniform4fv(ULintensities, 1, intensities);
}

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /* TODO: call your initialization functions here */



    createShaderPrograms();


    createBuffers();

    loadModel(":/models/cube.obj", NULL);

    //1.7

    loadTexture(":/textures/rug_logo.png",texBendi);
    glGenTextures(1,&texBendi);



    // For animation, you can start your timer here

}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) {

    // TODO: Update projection to fit the new aspect ratio
    screenWidth = newWidth;
    screenHeight = newHeight;

    qDebug() << newWidth << " " << newHeight << endl;
}

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {

    model.setToIdentity();
    view.setToIdentity();
    projection.setToIdentity();


    /*
    model.rotate(newX,1,0,0);
    model.rotate(newY,0,1,0);
    model.rotate(newZ,0,0,1);
    */
    //model.translate(1,0,0);

    //qDebug() << newWidth << endl;

    //eye declared in mainview.h

    QVector3D up = QVector3D(0,1,0);

    //model.scale(newScale,newScale,newScale);
    eye.setX(camPosX);
    eye.setY(camPosY);
    eye.setZ(camPosZ);
    view.lookAt(eye,centre,up);
    //view.translate(,0,0);
    projection.perspective(30.0, 1.0, 50.0, 1000.0);
    qDebug() << "eye " << eye << endl;
    //model.translate(0,0,4);

    // Clear the screen before rendering
    glClearColor(0.0f,0.0f,0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texBendi);
    //renderRaytracerScene();
    glDrawArrays(GL_TRIANGLES,0,numVertices);
    glBindVertexArray(0);

    mainShaderProg->bind();




    mainShaderProg->release();
}

// Add your function implementations below

// TODO: add your code