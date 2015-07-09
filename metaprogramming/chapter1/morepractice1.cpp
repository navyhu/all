#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
struct add_const_ref
{
    typedef typename add_lvalue_reference<typename add_const<T>::type>::type type;
};

template <typename T>
struct add_const_ref<T&>
{
    typedef typename remove_reference<T>::type type;
};

int main(int argc, char** argv)
{
    int test = 0;
    int const& cr = 0;
    const int& rc = 0;
    cout<<is_same<int const&, const int&>::value<<endl;
    cout<<is_same<int const*, const int*>::value<<endl;
    cout<<is_same<int const*, int* const>::value<<endl;
}
