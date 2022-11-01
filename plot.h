#ifndef PLOT_H
#define PLOT_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QComboBOx>
#include <QHBoxLayout >
#include "Function.h"
#define _USE_MATH_DEFINES ;
#include <math.h>


QT_BEGIN_NAMESPACE
namespace Ui { class plot; }
QT_END_NAMESPACE

class plot : public QOpenGLWidget
{
	Q_OBJECT

public:
	plot(QWidget* parent = nullptr);
	void makeAIndexForTriangles();
	void makeAIndexForLines();
	~plot();

private:

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	void rotateGraph();
	void scalingGraph();

	void changeMatrix();
	//void changeHowToDraw();

	void drawFunction();
	void drawOses();
	void  drawOsX(double* ver_line);
	void  drawOsZ(double* ver_line);
	void  drawOsY(double* ver_line);

	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

	double coordinateScale(double value);

	double wheelScroll = 1.;
	double rotateX = 0;
	double rotateY = 0;
	
	GLuint* indexForLines;
	GLuint** indexForTriangles;

	QPointF mousePosition;
	Function func;

	QComboBox* boxMatrix;
	QComboBox* boxTypeOfPolygon;
	QHBoxLayout* layout;
};
#endif // PLOT_H
