#include <iostream>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

int main(int argc, char** argv)
{
	typedef int type;
	typedef int** typepp;

	typedef typename mpl::lambda<
		typename mpl::apply<boost::add_pointer<_1>, 
		typename mpl::apply<boost::add_pointer<_1>, type>::type>::type>::type type2p;

	BOOST_STATIC_ASSERT((
					boost::is_same<type2p, typepp>::value));

	typedef typename mpl::lambda<
		typename mpl::apply<boost::add_pointer<_1>, type>::type>::type type1p;
	BOOST_STATIC_ASSERT((
					boost::is_same<type1p, int*>::value));

	type a = 6;
	type1p ap = &a;
	type2p app = &ap;

	std::cout<<a<<" "<<*ap<<" "<<*app<<std::endl;

	return 0;
}
