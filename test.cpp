#include "init_with_tuple/init_with_tuple.hpp"
#include <iostream>

int main()
{
    INIT_WITH_TUPLE((const int x)(const int y)(const int z), std::make_tuple(1, 2, 3));
    std::cout << x << "," << y << "," << z << std::endl;
 
    INIT_WITH_TUPLE_AUTO((a)()(str), std::make_tuple(4, 5, "hoge"));
    std::cout << a << "," << str << std::endl;
    return 0;
}
