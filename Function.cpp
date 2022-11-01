#include "Function.h"

Function::Function(const int CountOfPoint)
{
	setCountOfPoint(CountOfPoint);
	calculateArray();
}

Function::~Function()
{
	/*for (size_t i = 0; i < CountOfPoint; i++)
	{
		delete[] arrayOfPoint[i];
	}*/
	delete[] arrayOfPoint;
}

double Function::calculateZ(double x, double y)
{
	return x * x - y * y;
	
}

void Function::calculateArray()
{
	for (size_t i = 0; i < CountOfPoint * 3; i += 3)
	{
		int number = i / 3;
		double x = number / ((int)sqrt(CountOfPoint)) * size / ((int)sqrt(CountOfPoint) - 1) - size / 2;
		double y = number % ((int)sqrt(CountOfPoint)) * size / ((int)sqrt(CountOfPoint) - 1) - size / 2;
		double z = calculateZ(x, y);

		arrayOfPoint[i] = x;
		arrayOfPoint[i + 1] = y;
		arrayOfPoint[i + 2] = z;
	}
}

void Function::setCountOfPoint(int count)
{
	CountOfPoint = count;
	arrayOfPoint = new double [CountOfPoint*3];
	/*for (size_t i = 0; i < CountOfPoint; i++)
	{
		arrayOfPoint[i] = new double[3];
	}*/

	calculateArray();
}

int Function::getCountOfPoint()
{
	return CountOfPoint;
}

void Function::setSize(double size)
{
	this->size = size;
	calculateArray();
}

double Function::getSize()
{
	return size;
}
