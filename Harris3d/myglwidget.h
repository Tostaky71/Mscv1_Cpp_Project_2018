#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include "harrisdetector.h"
#include<set>
#include <vector>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT

private:
    QPoint curPos;
    float zoomingFactor;
    int rx, ry, rz;     // for paintGL function. We use int type because all angles are int type
    HarrisDetector H;
    vector<Vertex> vV;
    vector<vector <unsigned int>> F;
    vector<Vertex> interestPoints;

    void draw();
    void paintGL();
    void initializeGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public:
    explicit MyGLWidget(QWidget *parent = nullptr){}
    MyGLWidget(HarrisDetector H, QWidget *parent = nullptr);
    ~MyGLWidget();

    void refresh();
signals:
public slots:

    void setRX(int angle);
    void setRY(int angle);
    void setRZ(int angle);

signals:
    void RXChanged(int angle);
    void RYChanged(int angle);
    void RZChanged(int angle);


};



#endif // MYGLWIDGET_H
