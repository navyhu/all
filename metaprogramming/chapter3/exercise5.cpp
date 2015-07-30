
#include <iostream>
#include <algorithm>

#include "quantity.hpp"

int main(int argc, char** argv)
{
	hahu::quantity<float, hahu::mass> m(5.0f);
	hahu::quantity<float, hahu::acceleration> a(9.8f);

	hahu::quantity<float, hahu::force> f = m * a;

	f = f + m * a;

	f = m * a + f;

	hahu::quantity<float, hahu::mass> m2 = f / a;

	hahu::quantity<float, hahu::length> l(5.0f);
	hahu::quantity<float, hahu::time> t(2.0f);

	hahu::quantity<float, hahu::velocity> v = l / t;

	std::cout<<"force = "<<(m * a).value()<<std::endl;
	std::cout<<"mass = "<<std::abs((m2 - m).value())<<std::endl;
}
