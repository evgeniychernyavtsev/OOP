#pragma once

#include <string>
#include "Vector.h"

class Printable
{
public:
	virtual void print(std::ostream &out) const = 0;
};

class Named : public Printable
{
public:
	Named(const std::string& name)
	{
		_name = name;
	}
	void print(std::ostream& out) const override
	{
		out << _name << std::endl;
	}
	friend std::ostream & operator << (std::ostream& ioStream, const Printable& obj)
	{
		obj.print(ioStream);
		return ioStream;
	}
protected:
	std::string _name;
};