#include <iostream>
#include <type_traits>

using namespace std;

template <class T>
struct add_const_ref
{
    typedef typename add_lvalue_reference<typename add_const<T>::type>::type type;
};

template <class T>
struct add_const_ref<T&>
{
    typedef T type;
};

int main(int argc, char** argv)
{
    int t = 0;
    typename add_const_ref<int>::type i = t;
    cout<<"result: "<<is_same<int const&, typename add_const_ref<int>::type>::value<<endl;

    cout<<"result: "<<is_same<int const, typename add_const_ref<int const&>::type>::value<<endl;
    cout<<"result: "<<is_same<int, typename add_const_ref<int&>::type>::value<<endl;
}
