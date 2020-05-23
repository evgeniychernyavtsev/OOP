#include <iostream>
#include "Shapes.h"
#include "Factory_shapes.h"
#include <time.h>

int Shape::shapes_count = 0;

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Vector<std::shared_ptr<Shape>> shapes;
	for (int i = 0; i < 10; i++)
	{
		unsigned int shape_index = rand() % 6;
		shapes.push(Factory_shapes::create_shape(Shapes(shape_index)));
	}
	std::cout << Shape::GetCount() << std::endl;
	for (int i = 0; i < 10; i++)
		shapes[i]->print(std::cout);
	for (int i = 0; i < 10; i++)
		shapes.pop();
	std::cout << Shape::GetCount() << std::endl;
	return 0;
}