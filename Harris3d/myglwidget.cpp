#include "myglwidget.h"
#include <QtWidgets>
#include <QtOpenGL>


MyGLWidget::MyGLWidget(HarrisDetector H, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->H = H;
    this->vV = H.getMesh().getVertices();
    this->F = H.getMesh().getFaces();

    interestPoints = H.getInterestPoints();
    zoomingFactor = 0.005f;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(160*3, 90*3);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(1600, 900);
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int D = event->delta();
    cout << D << endl;
    if (D > 0)
    {
        cout <<"unzoom" << endl;
        zoomingFactor -= 0.0001;
    }
    else if (D < 0)
    {
        cout <<"zoom" << endl;
        zoomingFactor += 0.0001;
    }

    resizeGL(width(), height());

    /*
    double side = qMax(height(), width());
    glViewport((width() - side), (height() - side), side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(zoomingFactor, zoomingFactor, zoomingFactor);
    glMatrixMode(GL_MODELVIEW);

    */
    refresh();
}


void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    curPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - curPos.x();
    int dy = event->y() - curPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setRX(rx + 8 * dy);
        setRY(ry + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setRX(rx + 8 * dy);
        setRZ(rz + 8 * dx);
    }
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);

    float dLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float aLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    float sLight[] = {1.0f,1.0f,1.0f,1.0f};


    glLightfv(GL_LIGHT0, GL_DIFFUSE, dLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, aLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sLight);
    glEnable(GL_LIGHTING);

    GLfloat amb[] = {0.0,0.0,0.0,1.0};
    GLfloat spec[] = {1.0,1.0,1.0,1.0};
    GLfloat shine[] = {20.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, amb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glColorMaterial (GL_FRONT_AND_BACK, GL_EMISSION);
    glEnable (GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat pos[] = {0,0,15,1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_NORMALIZE);

}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMax(height, width);

    glViewport((width - side), (height - side), side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(zoomingFactor, zoomingFactor, zoomingFactor);
    glMatrixMode(GL_MODELVIEW);

}

void MyGLWidget::draw()
{
    cout << "loops" << endl;
    vector<vector <uint>> :: iterator it;
    for (it = F.begin(); it != F.end(); it++)
    {
        unsigned int a = 12, b = 9, c = 8;
        a = (*it).at(0);
        b = (*it).at(1);
        c = (*it).at(2);
        glColor3ub(64, 128, 255);    // give a color to our triangles
        glBegin(GL_TRIANGLES);
        double nx=0, ny=0, nz=0, ux=0, uy=0, uz=0, vx=0, vy=0, vz=0;


        glVertex3d(vV[a].x(), vV[a].y(), vV[a].z());
        glVertex3d(vV[b].x(), vV[b].y(), vV[b].z());
        glVertex3d(vV[c].x(), vV[c].y(), vV[c].z());

        ux = vV[c].x() - vV[a].x();
        uy = vV[c].y() - vV[a].y();
        uz = vV[c].z() - vV[a].z();

        vx = vV[b].x() - vV[c].x();
        vy = vV[b].y() - vV[c].y();
        vz = vV[b].z() - vV[c].z();

        nx = uy*vz-uz*vy;
        ny = uz*vx-ux*vz;
        nz = ux*vy-uy*vx;

        Eigen::Vector3d Norm (nx, ny, nz);

        nx /= Norm.norm();
        ny /= Norm.norm();
        nz /= Norm.norm();

        glNormal3d(nx, ny, nz);
        glVertex3d(vV[a].x(), vV[a].y(), vV[a].z());
        glVertex3d(vV[b].x(), vV[b].y(), vV[b].z());
        glVertex3d(vV[c].x(), vV[c].y(), vV[c].z());
        glEnd();

    }
    vector<Vertex>::iterator it2;
    for (it2 = interestPoints.begin(); it2 != interestPoints.end(); it2++)
    {
        double offset = 1.5;
        double x = (*it2).x();
        double y = (*it2).y();
        double z = (*it2).z();

        glColor3ub(255, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3d(x-offset, y-offset, z);
        glVertex3d(x+offset, y+offset, z);
        glVertex3d(x-offset, y-offset, z+offset);
        glVertex3d(x-offset, y-offset, z-offset);
        glEnd();
    }
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // remove what already exists before painting
    glLoadIdentity();
    glTranslated(0.0, 0.0, -10.0);

    glRotated(double(rx) / 16.0, 1.0, 0.0, 0.0);
    glRotated(double(ry) / 16.0, 0.0, 1.0, 0.0);
    glRotated(double(rz) / 16.0, 0.0, 0.0, 1.0);
    draw();

}

void MyGLWidget::refresh()
{
    paintGL();
    draw();
    updateGL();     // update modifications of

}

void assertAngle(int angle)
{
    while (angle < 0)
    {
        angle += 360;
    }
    while (angle> 360)
    {
        angle -= 360;
    }
}

void MyGLWidget::setRX(int angle)
{
    assertAngle(angle);

    if (angle != this->rx)
    {
        rx = angle;
        emit RXChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setRY(int angle)
{
    assertAngle(angle);

    if (angle != this->ry)
    {
        ry = angle;
        emit RYChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setRZ(int angle)
{
    assertAngle(angle);

    if (angle != this->rz)
    {
        rz = angle;
        emit RZChanged(angle);
        updateGL();
    }
}
