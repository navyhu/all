
#include <iostream>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/multiplies.hpp>

// refer to www.ccs.neu.edu/home/mbisson/CPP-TemplateMetaprog/exercise-3-1_8hpp_source.html

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

struct increase
{
	template <class T>
	struct apply : mpl::plus<T, mpl::int_<1> > { };
};

template <class T>
struct increaseVec : mpl::transform<T, increase> { };

struct squr
{
	template <class T>
	struct apply : mpl::multiplies<T, T> { };
};

template <class T>
struct squrVec : mpl::transform<T, squr> { };

int main(int argc, char** argv)
{
	typedef typename mpl::vector_c<int, 1, 2, 3>::type type123;
	typedef typename mpl::vector_c<int, 2, 3, 4>::type type234;
	typedef typename mpl::vector_c<int, 1, 4, 9>::type type149;

	//typedef typename mpl::transform<type123, mpl::plus<_1, mpl::int_<1> > >::type type123234;
	//typedef typename mpl::transform<type123, increase>::type type123234;
	typedef increaseVec<type123>::type type123234;
	BOOST_STATIC_ASSERT((mpl::equal<type234, type123234>::type::value));

	typedef squrVec<type123>::type type123149;
	BOOST_STATIC_ASSERT((mpl::equal<type149, type123149>::type::value));

	bool same = boost::is_same<type234, type123234>::value;

	std::cout<<"the same? "<<same<<std::endl;
}
