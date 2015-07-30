#include <iostream>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <class UnaryMetaFunctionClass, class Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg>
{ };

template <class F, class X>
struct twice : apply1<F, typename apply1<F, X>::type>
{ };

template <class T>
struct twoPointers : twice<typename mpl::lambda<boost::add_pointer<_1> >::type, T>
{ };

template <class T>
struct fourPointers
{
	typedef typename twice<typename mpl::lambda<boost::add_pointer<_1> >::type, T>::type twoP;
	typedef typename twice<typename mpl::lambda<boost::add_pointer<_1> >::type, twoP>::type type;
};

template <class T>
struct fourPointers2
{
	typedef typename twice<typename mpl::lambda<boost::add_pointer<_1> >::type,
		typename twice<typename mpl::lambda<boost::add_pointer<_1> >::type, T>::type>
			::type type;
};

int main(int argc, char** argv)
{
	typedef int type;
	typedef int** typepp;
	typedef typename twoPointers<type>::type type2p;
	BOOST_STATIC_ASSERT((boost::is_same<type2p, typepp>::value));

	typedef typename fourPointers<type>::type type4p;
	BOOST_STATIC_ASSERT((boost::is_same<type4p, int****>::value));

	typedef typename fourPointers2<type>::type type4p2;
	BOOST_STATIC_ASSERT((boost::is_same<type4p2, int****>::value));
}
