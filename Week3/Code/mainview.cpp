#include "mainview.h"
#include "math.h"
#include <iostream>

#include <QDateTime>
int numVertices = 0;
QVector<QVector3D> vertices;

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

    /* Add your other shaders below */
    a = glGetUniformLocation(mainShaderProg->programId(), "model");

    b = glGetUniformLocation(mainShaderProg->programId(), "view");

    c = glGetUniformLocation(mainShaderProg->programId(), "projection");

    glUniformMatrix4fv(a, 3, GL_FALSE, model.data());
    glUniformMatrix4fv(b, 3, GL_FALSE, view.data());
    glUniformMatrix4fv(c, 3, GL_FALSE, projection.data());

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
    glBindVertexArray(vao);

    glGenBuffers(1,&bo);
    glGenBuffers(1,&boCol);

    glBindBuffer(GL_ARRAY_BUFFER,bo);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,boCol);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);

    glBindVertexArray(0);

}


void MainView::loadModel(QString filename, GLuint bufferObject) {

    cubeModel = new Model(filename);
    numTris = cubeModel->getNumTriangles();

    Q_UNUSED(bufferObject);

    // TODO: implement loading of model into Buffer Objects
    vertices = cubeModel->getVertices();
    numVertices = vertices.length();
    srand (time(NULL));

    // Generate random colors
    QVector<QVector3D> colors;
    for (int i = 0; i < numVertices/3; i++)
    {
        //srand (time(NULL));
        QVector3D col = QVector3D(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX);
        colors.push_back(col);
    }
    glBindBuffer(GL_ARRAY_BUFFER,bo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*numVertices,vertices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,boCol);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*colors.length(),colors.data(),GL_STATIC_DRAW);


}

void MainView::updateBuffers() {
    // Change the data inside buffers (if you want)
    // make sure to change GL_STATIC_DRAW to GL_DYNAMIC_DRAW
    // in the call to glBufferData for better performance

}


void MainView::updateUniforms() {
    // TODO: update the uniforms in the shaders using the glUniform<datatype> functions

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
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
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

    projection.perspective(60.0, 1.0, 0.1, 100.0);

    model.translate(45,342,42);

    for (int i = 0; i < vertices.length(); i++){
        vertices[i]*model;
        vertices[i]*view;
        vertices[i]*projection;
    }
    // Clear the screen before rendering
    glClearColor(0.0f,0.0f,0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainShaderProg->bind();

    // TODO: implement your drawing functions
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,numVertices);

    mainShaderProg->release();
}

// Add your function implementations below

// TODO: add your code
