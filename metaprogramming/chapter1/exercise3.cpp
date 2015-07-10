#include <iostream>
#include <boost/polymorphic_downcast.hpp>

template <typename Target, typename Source>
Target polymorphic_downcast(Source* x)
{
	assert( dynamic_cast<Target>(x) == x );
	return static_cast<Target>(x);
};

template <typename Target, typename Source>
Target polymorphic_downcast(Source& x)
{
	assert( dynamic_cast<typename std::remove_lvalue_reference<Target>::type
				>::type>(&x) == &x);
	return static_cast<Target>(x);
};

class A { virtual ~A {} };
class B:A {};

int main(int argc, char** argv)
{
	B b;
	A* a_ptr = &b;
	B* b_ptr = polymorphic_downcast<B*>(a_ptr);

	A& a_ref = b;
	B& b_ref = polymorphic_downcast<B&>(a_ref);
}
