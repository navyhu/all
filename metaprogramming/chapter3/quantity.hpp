
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

namespace hahu
{
// basic dimensions
typedef mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amout_of_substance;


// composite dimensions
typedef mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0> velocity;
typedef mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0> acceleration;
typedef mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0> momentum;
typedef mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0> force;


// scalar
typedef mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0> scalar;


// class for the quantity
template <class T, class Dimensions>
struct quantity
{
	explicit quantity(T x) : m_value(x) { }

	template <class OtherDimensions>
	quantity(quantity<T, OtherDimensions> const& rhs) : m_value(rhs.value())
	{
		BOOST_STATIC_ASSERT((
			mpl::equal<Dimensions, OtherDimensions>::type::value
			));
	}

	T value() const { return m_value; }

	private:
	T m_value;
};

// plus operator
template <class T, class D>
quantity<T, D>
operator+(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() + y.value());
}

template <class T, class D1, class D2>
quantity<T, D1>
operator+(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, D1>(x.value() + y.value());
}

// minus operator 
template <class T, class D>
quantity<T, D>
operator-(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() - y.value());
}

template <class T, class D1, class D2>
quantity<T, D1>
operator-(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, D1>(x.value() - y.value());
}

// multiply operator
template <class D1, class D2>
struct multiple_dimensions : mpl::transform<D1, D2, mpl::plus<_1, _2> >
{ };

template <class T, class D1, class D2>
quantity<T, typename multiple_dimensions<D1, D2>::type>
operator*(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, typename multiple_dimensions<D1, D2>::type>(x.value() * y.value());
}

// division operator
template <class D1, class D2>
struct divide_dimensions : mpl::transform<D1, D2, mpl::minus<_1, _2> >
{ };

template <class T, class D1, class D2>
quantity<T, typename divide_dimensions<D1, D2>::type>
operator/(quantity<T, D1> x, quantity<T, D2> y)
{
	return quantity<T, typename divide_dimensions<D1, D2>::type>(x.value() / y.value());
}

} // namespace hahu
