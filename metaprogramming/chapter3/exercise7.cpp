#include <iostream>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/arg.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

int main(int argc, char** argv)
{
	// represent type _1
	typedef mpl::lambda<mpl::lambda<_1> >::type t1;
	BOOST_STATIC_ASSERT((
					boost::is_same<t1, _1>::value));

	return 0;
}
