#pragma once

#include "Base.h"
#define pi 3.1415926535

class Shape : public Printable
{
public:
	static int shapes_count;
	static int GetCount()
	{
		return shapes_count;
	}
	Shape()
	{
		shapes_count++;
	}
	Shape(Shape const & shape)
	{
		shapes_count++;
	}
	virtual ~Shape()
	{
		shapes_count--;
	}
};

class Point : public Shape, public Named
{
public:
	Point(std::string const & name, double const x, double const y) : Shape(), Named(name), _x(x), _y(y) {}
	void print(std::ostream& out) const override
	{
		out << _name << " Point(" << _x << "," << _y << ")" << std::endl;
	}
	double get_x() const
	{
		return _x;
	}
	double get_y() const
	{
		return _y;
	}
	double distance(Point const& point)
	{
		double X = abs(this->get_x() - point.get_x());
		double Y = abs(this->get_y() - point.get_y());
		return sqrt(X*X + Y*Y);
	}
private:
	double _x, _y;
};

class Circle : public Shape, public Named
{
public:
	Circle(std::string const & name, Point const & center, double const & radius) : Shape(), Named(name), _center(center), _r(radius)
	{
		if(radius <= 0)
			throw std::runtime_error("radius should be more 0");
	}
	double area() const
	{
		return pi*_r*_r;
	}
	void print(std::ostream& out) const override
	{
		out << _name << " Circle with center (" << _center.get_x() << "," << _center.get_y() << "), with radius " << _r << " and with area " << this->area() << std::endl;
	}
private:
	Point _center;
	double _r;
};

class Rect : public Shape, public Named
{
public:
	Rect(std::string const & name, Point const & left_p, Point const & right_p) : Shape(), Named(name), _lpoint(left_p), _rpoint(right_p)
	{
		_h = abs(_lpoint.get_y() - _rpoint.get_y());
		_w = abs(_lpoint.get_x() - _rpoint.get_x());
		if (_w == 0 || _h == 0)
			throw std::runtime_error("width and height should be more 0");
	}
	double area() const
	{
		return _w*_h;
	}
	void print(std::ostream& out) const override
	{
		out << _name << " Rect with width " << _w << " and height " << _h << ", with area " << this->area() << std::endl;
	}
private:
	Point _lpoint, _rpoint;
	double _w, _h;
};

class Square : public Shape, public Named
{
public:
	Square(std::string const & name, Point const & point, double const side) : Shape(), Named(name), _point(point), _side(side) {}
	double area() const
	{
		return _side*_side;
	}
	void print(std::ostream& out) const override
	{
		out << _name << " Square with side " << _side << ", with point (" << _point.get_x() << "," << _point.get_y() << "), with area " << this->area() << std::endl;
	}
private:
	Point _point;
	double _side;
};

class Polyline : public Shape, public Named
{
public:
	Polyline(std::string const & name) : Shape(), Named(name) {}
	void AddPoint(Point const & point)
	{
		_points.push(point);
	}
	double lenght() const
	{
		if (_points.size() < 2)
			return double(0);
		double l = 0;
		for (unsigned int i = 0; i < _points.size() - 1; i++)
			l += _points[i].distance(_points[i + 1]);
		return l;
	}
	void print_poly(std::ostream& out) const
	{
		for (unsigned int i = 0; i < _points.size(); i++)
			_points[i].print(out);
		out << "} Lenght: " << this->lenght() << std::endl;
	}
	void print(std::ostream& out) const override
	{
		out << _name << " Polyline{";
		print_poly(out);
	}
	
protected:
	Vector<Point> _points;
};

class Polygon : public Polyline
{
public:
	Polygon(std::string const& name) : Polyline(name) {}
	double lenght() const
	{
		return Polyline::lenght() + _points[0].distance(_points[_points.size() - 1]);
	}
	void print(std::ostream& out) const override
	{
		out << _name << " Polygon{" << std::endl;
		Polyline::print_poly(out);
	}
};