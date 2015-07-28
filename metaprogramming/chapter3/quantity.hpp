
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/equal.hpp>

namespace mpl = boost::mpl;
//using namespace boost;

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

// minus operator 
template <class T, class D>
quantity<T, D>
operator-(quantity<T, D> x, quantity<T, D> y)
{
	return quantity<T, D>(x.value() - y.value());
}

// multiply operator
struct plus_f
{
	template <class T1, class T2>
	struct apply
	{
		typedef typename mpl::plus<T1, T2>::type type;
	};
};

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type>
operator*(quantity<T, D1> x, quantity<T, D2> y)
{
	typedef typename mpl::transform<D1, D2, plus_f>::type dim;
	return quantity<T, dim>(x.value() * y.value());
}

} // namespace hahu
