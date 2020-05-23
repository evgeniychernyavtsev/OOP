#pragma once
#include <memory>
#include "Shapes.h"

enum Shapes {Point_index, Circle_index, Rect_index, Square_index, Polyline_index, Polygon_index};

double Random(double x, double y)
{
	double random = (double)rand() / (double)RAND_MAX;
	double obl = y - x;
	double q = random * obl;
	return x + q;
}

class Factory_shapes
{
public:
	
	static std::shared_ptr<Shape> create_shape(Shapes const index)
	{
		std::shared_ptr<Shape> shape = nullptr;
		switch (index)
		{
		case Point_index:
		{
			double x = Random(0, 10), y = Random(0, 10);
			shape = std::shared_ptr<Shape>(new Point("", x, y));
			break;
		}
		case Circle_index:
		{
			double x = Random(0, 10), y = Random(0, 10), radius = Random(0.1, 10);
			shape = std::shared_ptr<Shape>(new Circle("", Point("", x, y), radius));
			break;
		}
		case Rect_index:
		{
			double x1 = Random(0, 10), x2 = Random(0, 10), y1 = Random(0, 10), y2 = Random(0, 10);
			shape = std::shared_ptr<Shape>(new Rect("", Point("", x1, y1), Point("", x2, y2)));
			break;
		}
		case Square_index:
		{
			double x = Random(0, 10), y = Random(0, 10), side = Random(0.1, 10);
			shape = std::shared_ptr<Shape>(new Square("", Point("", x, y), side));
			break;
		}
		case Polyline_index:
		{
			shape = std::shared_ptr<Shape>(new Polyline(""));
			unsigned int points = 2 + rand() % 10;
			for (unsigned int i = 0; i < points; i++)
				static_cast<Polyline*>(shape.get())->AddPoint(Point("", Random(0, 10), Random(0, 10)));
			break;
		}
		case Polygon_index:
		{
			shape = std::shared_ptr<Shape>(new Polygon(""));
			unsigned int points = 2 + rand() % 10;
			for (unsigned int i = 0; i < points; i++)
				static_cast<Polygon*>(shape.get())->AddPoint(Point("", Random(0, 10), Random(0, 10)));
			break;
		}
		}
		return shape;
	}
};