#pragma once
#define _USE_MATH_DEFINES 
#include <math.h>
class Function
{
public:
	Function(const int CountOfPoint);
	~Function();

	double calculateZ(double x, double y);
	void calculateArray();

	int getCountOfPoint();
	void setSize(double size);
	double getSize();
	double* arrayOfPoint;
private:
	int CountOfPoint;
	double size = 2;
	void setCountOfPoint(int count);


};

