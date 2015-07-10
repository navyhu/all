#include <iostream>
#include <type_traits>

template <typename C, typename X, typename Y>
struct replace_type
{
	// error when following into this template
};

/// handle when C equals X or not
template <typename C, typename X, typename Y, bool isEqual>
struct replace_type_helper
{
};

/// handle cases of C with pointer
template <typename Cp, typename X, typename Y>
struct replace_type<Cp*, X, Y>
{
	typedef typename std::add_pointer<
		typename replace_type_helper<
		Cp, X, Y, 
		std::is_same<Cp, X>::value>::type
			>::type type;
};

/// handle cases of C with reference
template <typename Cr, typename X, typename Y>
struct replace_type<Cr&, X, Y>
{
	typedef typename std::add_lvalue_reference<
		typename replace_type_helper<
		Cr, X, Y,
		std::is_same<Cr, X>::value>::type
			>::type type;
};

/// handle cases of function without any parameter
template <typename Cfn, typename X, typename Y>
struct replace_type<Cfn(*)(), X, Y>
{
	typedef typename replace_type_helper<
		Cfn, X, Y,
		std::is_same<Cfn, X>::value>::type (*type)();
};

/// handle cases of function with one parameter
template <typename Cfn, typename Cpar, typename X, typename Y>
struct replace_type<Cfn(*)(Cpar), X, Y>
{
	typedef typename replace_type_helper<
		Cfn, X, Y,
		std::is_same<Cfn, X>::value>::type (*type)
			(typename replace_type<Cpar, X, Y>::type);
};

/// handle cases of function with more than one parameters
template <typename Cfn, typename Cpar1, typename Cpar2, typename X, typename Y>
struct replace_type<Cfn(*)(Cpar1, Cpar2), X, Y>
{
	typedef typename replace_type_helper<
		Cfn, X, Y,
		std::is_same<Cfn, X>::value>::type (*type)
			(typename replace_type_helper<
			 Cpar1, X, Y,
			 std::is_same<Cpar1, X>::value>::type,
			 typename replace_type_helper<
			 Cpar2, X, Y,
			 std::is_same<Cpar2, X>::value>::type);
};

/// handle cases with extend(array)
template <typename C, typename X, typename Y, size_t N>
struct replace_type<C[N], X, Y>
{
	typedef typename replace_type_helper<
		C, X, Y,
		std::is_same<C, X>::value>::type type[N];
};

template <typename C, typename X, typename Y>
struct replace_type<C*, X*, Y>
{
	typedef typename replace_type_helper<
		C, X, Y, 
		std::is_same<C, X>::value>::type type;
};

template <typename C, typename X, typename Y>
struct replace_type<C&, X&, Y>
{
	typedef typename replace_type_helper<
		C, X, Y,
		std::is_same<C, X>::value>::type type;
};

template <typename C, typename X, typename Y>
struct replace_type_helper<C, X, Y, true>
{
	typedef Y type;
};

template <typename C, typename X, typename Y>
struct replace_type_helper<C, X, Y, false>
{
	typedef typename replace_type<C, X, Y>::type type;
};

int main(int argc, char** argv)
{
	std::cout<<"void*, void, int: "
		<<std::is_same<typename replace_type<void*, void, int>::type, int*>::value
		<<std::endl;

	std::cout<<"void*, void*, int: "
		<<std::is_same<typename replace_type<void*, void*, int>::type, int>::value
		<<std::endl;

	std::cout<<"int const*[10], int const, long: "
		<<std::is_same<
		typename replace_type<int const*[10], int const, long>::type, long*[10]>
		::value
		<<std::endl;

	std::cout<<"char& (*)(char&), char&, long&: "
		<<std::is_same<typename replace_type<char&(*)(char&), char&, long&>::type, long& (*)(long&)>
		::value
		<<std::endl;

	std::cout<<"char& (*)(char&, char), char, long: "
		<<std::is_same<
		typename replace_type<
			char& (*)(char&, char), char, long>::type, 
			long& (*)(long&, long)>
		::value
		<<std::endl;
}
