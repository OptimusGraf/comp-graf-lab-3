#include "plot.h"
#include <QWheelEvent>
#include <qstatusbar.h>
#include<fstream>
plot::plot(QWidget* parent)
	:QOpenGLWidget(parent), func(1'000'000)
{
	boxMatrix = new QComboBox(this);
	boxMatrix->addItem(QString::fromLocal8Bit("Перспективная"));
	boxMatrix->addItem(QString::fromLocal8Bit("Ортогональная"));
	boxTypeOfPolygon = new QComboBox(this);

	boxTypeOfPolygon->addItem(QString::fromLocal8Bit("Точки"));
	boxTypeOfPolygon->addItem(QString::fromLocal8Bit("Линии"));
	boxTypeOfPolygon->addItem(QString::fromLocal8Bit("Треугольники"));

	layout = new QHBoxLayout;
	layout->addWidget(boxMatrix, 0, Qt::AlignTop | Qt::AlignLeft);
	layout->addWidget(boxTypeOfPolygon, 0, Qt::AlignTop | Qt::AlignRight);

	this->setLayout(layout);

	makeAIndexForLines();
	makeAIndexForTriangles();



}

void plot::makeAIndexForTriangles()
{
	int i = 0, j = 0, numberofline = 1;;
	indexForTriangles = new GLuint * [(int)sqrt(func.getCountOfPoint()) - 1];
	for (size_t i = 0; i < (int)sqrt(func.getCountOfPoint()); i++)
	{
		indexForTriangles[i] = new GLuint[(int)sqrt(func.getCountOfPoint()) * 2];
	}

	i = 0, j = 0, numberofline = 1;;
	while (numberofline - 1 < sqrt(func.getCountOfPoint()) - 1)
	{
		i = 0;
		while (i < sqrt(func.getCountOfPoint()) * 2 - 1)
		{
			indexForTriangles[numberofline - 1][i] = j;
			indexForTriangles[numberofline - 1][i + 1] = j + sqrt(func.getCountOfPoint());
			i += 2;
			j++;
		}
		numberofline++;
	}
}

void plot::makeAIndexForLines()
{
	indexForLines = new GLuint[func.getCountOfPoint()];

	int i = 0, j = 0, numberofline = 1;;
	while (i < func.getCountOfPoint())
	{
		int add = 0;
		if (numberofline % 2 == 1)
			add = 1;
		else
			add = -1;
		while (i < sqrt(func.getCountOfPoint()) * numberofline)
		{
			indexForLines[i++] = j;
			j += add;
		}
		numberofline++;
		j += sqrt(func.getCountOfPoint()) - add;
	}
}

plot::~plot()
{
	delete boxMatrix;
	delete boxTypeOfPolygon;
	delete layout;
	delete[] indexForLines;
	for (size_t i = 0; i < (int)sqrt(func.getCountOfPoint()) - 1; i++)
	{
		delete[] indexForTriangles[i];
	}
	delete[] indexForTriangles;
	func.~Function();

}

void plot::initializeGL()
{
	this->setMouseTracking(true);
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glClearColor(102.0 / 255, 102.0 / 255, 102.0 / 255, 1);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);


}

void plot::resizeGL(int w, int h)
{
	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glViewport(0, 0, w, h);

}

void plot::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);
	glLoadIdentity();
	changeMatrix();

	scalingGraph();
	rotateGraph();

	drawOses();
	drawFunction();

	update();
}
void plot::scalingGraph()
{
	if (wheelScroll > 0)
		glScaled(wheelScroll, wheelScroll, wheelScroll);
	else
		glScaled(1 / -wheelScroll, 1 / -wheelScroll, 1 / -wheelScroll);


}
void plot::changeMatrix()
{
	if (boxMatrix->currentText() == QString::fromLocal8Bit("Ортогональная"))
	{
		glOrtho(-1, 1, -1, 1, -1, 1);
	}
	else
	{
		glFrustum(-1, 1, -1, 1, -1, 1);
	}
}
void plot::rotateGraph()
{

	glRotated(rotateX, 1, 0, 0);
	glRotated(rotateY, 0, 1, 0);


}
void plot::drawFunction()
{

	glVertexPointer(3, GL_DOUBLE, 0, func.arrayOfPoint);
	glColor3d(0, 1, 0);
	if (boxTypeOfPolygon->currentText() == QString::fromLocal8Bit("Точки"))
	{
		glDrawArrays(GL_POINTS, 0, func.getCountOfPoint());
	}
	else if (boxTypeOfPolygon->currentText() == QString::fromLocal8Bit("Линии"))
	{
		glDrawElements(GL_LINE_STRIP, func.getCountOfPoint(), GL_UNSIGNED_INT, indexForLines);
	}
	else if (boxTypeOfPolygon->currentText() == QString::fromLocal8Bit("Треугольники"))
	{
		for (int i = 0; i < (int)sqrt(func.getCountOfPoint()); i++)
		{
			glDrawElements(GL_TRIANGLE_STRIP, (int)sqrt(func.getCountOfPoint()) * 2, GL_UNSIGNED_INT, indexForTriangles[i]);
		}
	}

}
void plot::drawOses()
{

	double ver_line[] = { coordinateScale(1),0,0,   coordinateScale(0.9),
		coordinateScale(0.05),0,    coordinateScale(1),0,0,
		coordinateScale(0.9),  coordinateScale(-0.05),0,
		coordinateScale(-1),0,0,   coordinateScale(1),0,0 };
	//float ver_line[6][3] = { {1,0,0,}, { 0.9,0.05,0}, {1,0,0}, { 0.9, -0.05,0}, {-1,0,0,}, {1,0,0} };
	glPushMatrix();
	glVertexPointer(3, GL_DOUBLE, 0, ver_line);

	drawOsX(ver_line);
	drawOsY(ver_line);
	drawOsZ(ver_line);

	glPopMatrix();



}

void plot::drawOsX(double* ver_line)
{
	glColor3d(248 / 255.0, 243 / 255.0, 43 / 255.0);
	glDrawArrays(GL_LINES, 0, 6);
}

void plot::drawOsZ(double* ver_line)
{
	glColor3d(1., 0., 0.);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glDrawArrays(GL_LINES, 0, 6);
	glPopMatrix();
}

void plot::drawOsY(double* ver_line)
{
	glColor3d(0., 0., 1.);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glDrawArrays(GL_LINES, 0, 6);
	glPopMatrix();
}


void plot::wheelEvent(QWheelEvent* event)
{
	event->accept();
	int delta = event->angleDelta().y() / 32;
	wheelScroll += delta;
	func.setSize(coordinateScale(2));
	update();
}
void plot::mousePressEvent(QMouseEvent* event)
{
	event->accept();
	mousePosition = event->localPos();

}

double plot::coordinateScale(double value)
{
	if (wheelScroll < 0)
		return value * -wheelScroll;
	else if (wheelScroll > 0)
		return  value / wheelScroll;

}

void plot::mouseMoveEvent(QMouseEvent* event)
{
	event->accept();
	if (event->buttons() & Qt::LeftButton)
	{
		qreal mouseMove = mousePosition.y() - event->localPos().y();
		rotateX += 1 / M_PI * (mouseMove);

		mouseMove = mousePosition.x() - event->localPos().x();
		rotateY += 1 / M_PI * (mouseMove);

		mousePosition = event->localPos();

	}
	update();

}
