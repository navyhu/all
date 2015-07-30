#include <iostream>
#include <boost/static_assert.hpp>

template <unsigned long N>
struct binary
{
	BOOST_STATIC_ASSERT_MSG(N % 10 == 0 || N % 10 == 1, "Only 0/1 is allowed");
	static unsigned const value = binary<N / 10>::value * 2 + N % 10;
};

template <>
struct binary<0>
{
	static unsigned const value = 0;
};

int main(int argc, char** argv)
{
	unsigned const one = binary<1>::value;

	unsigned const three = binary<10>::value;

	unsigned const seven = binary<111>::value;

	std::cout<<"result: "<<one<<" "<<three<<" "<<seven<<std::endl;
}
