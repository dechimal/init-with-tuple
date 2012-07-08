#include "init_with_tuple/init_with_tuple.hpp"
#include <tuple>
#include <iostream>
#include <string>
#include <cassert>

template<typename, typename>
using hoge = int;

int main()
{
    using init_with_tuple::ignore;
    INIT_WITH_TUPLE((int x)(ignore)(auto z), std::make_tuple(1, 2, std::string("hoge")));
    assert(x == 1);
    assert(z == "hoge");
    std::cout << x << "," << z << std::endl;

    INIT_WITH_TUPLE((x)(hoge<int, int> y)(z), std::make_tuple<int, int, std::string>(3, 4, "fuga"));
    assert(x == 3);
    assert(y == 4);
    assert(z == "fuga");
    std::cout << x << "," << y << "," << z << std::endl;

    INIT_WITH_TUPLE_AUTO(()(b)(c), std::make_tuple<int, int>(3, 4, std::string("fuga")));
    assert(b == 4);
    assert(c == "fuga");
    std::cout << b << "," << c << std::endl;

    INIT_WITH_TUPLE_AUTO((e1)(e2)(e3), std::vector<int>{1, 2, 3});
    std::cout << '[' << e1 << ", " << e2 << ", " << e3 << "]\n";

    return 0;
}
