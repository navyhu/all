
#include <iostream>

#include "quantity.hpp"

int main(int argc, char** argv)
{
	hahu::quantity<float, hahu::mass> m(5.0f);
	hahu::quantity<float, hahu::acceleration> a(9.8f);

	hahu::quantity<float, hahu::force> f = m * a;

	//hahu::quantity<float hahu::time> t = m * a;

	std::cout<<"force = "<<(m * a).value()<<std::endl;
}
