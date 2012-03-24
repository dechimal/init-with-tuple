#include "init_with_tuple/init_with_tuple.hpp"
#include <tuple>
#include <iostream>
#include <string>

template<typename, typename>
using hoge = int;

int main()
{
    using init_with_tuple::ignore;
    INIT_WITH_TUPLE((int x)(ignore)(auto z), std::make_tuple(1, 2, std::string("hoge")));
    std::cout << x << "," << z << std::endl;

    INIT_WITH_TUPLE((x)(hoge<int, int> y)(z), std::make_tuple<int, int, std::string>(3, 4, "fuga"));
    std::cout << x << "," << y << "," << z << std::endl;
    return 0;
}
