#include <iostream>
#include <type_traits>
#include <string>

template <typename T>
struct type_descriptor_helper
{
};

template <>
struct type_descriptor_helper<int>
{
	type_descriptor_helper()
	{
		value = "int";
	}
	std::string value;
};

template <>
struct type_descriptor_helper<char>
{
	type_descriptor_helper()
	{
		value = "char";
	}
	std::string value;
};

template <>
struct type_descriptor_helper<short>
{
	type_descriptor_helper()
	{
		value = "short";
	}
	std::string value;
};

template <>
struct type_descriptor_helper<long>
{
	type_descriptor_helper()
	{
		value = "long";
	}
	std::string value;
};

template <typename T>
struct type_descriptor_helper<T*>
{
	type_descriptor_helper()
	{
		value = mtype.value + "*";
	}
	type_descriptor_helper<T> mtype;
	std::string value;
};

template <typename T>
struct type_descriptor_helper<T&>
{
	type_descriptor_helper()
	{
		value = mtype.value + "&";
	}
	type_descriptor_helper<T> mtype;
	std::string value;
};

template <typename T>
struct type_descriptor_helper<T const>
{
	type_descriptor_helper()
	{
		value = mtype.value + " const";
	}
	type_descriptor_helper<T> mtype;
	std::string value;
};

template <typename T>
std::string type_descriptor()
{
	return type_descriptor_helper<T>().value;
}

int main(int argc, char** argv)
{
	std::cout<<type_descriptor<int*>()<<std::endl;

	std::cout<<type_descriptor<char*>()<<std::endl;

	std::cout<<type_descriptor<char* const>()<<std::endl;

	std::cout<<type_descriptor<short&>()<<std::endl;

	std::cout<<type_descriptor<int>()<<std::endl;

	std::cout<<type_descriptor<long const*&>()<<std::endl;

	return 0;
}
