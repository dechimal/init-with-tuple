#if !defined INIT_WITH_TUPLE_TRAITS_STD_TUPLE_HPP_INCLUDED_
#define      INIT_WITH_TUPLE_TRAITS_STD_TUPLE_HPP_INCLUDED_

#include <tuple>
#include <init_with_tuple/init_with_tuple.hpp>

namespace init_with_tuple { namespace traits {

template<typename ...Elems>
struct element_access<std::tuple<Elems...>> {
    template<typename I, typename Tup>
    static auto get(I, Tup && tup) noexcept(noexcept(std::get<I::value>(std::forward<Tup>(tup)))) -> decltype(std::get<I::value>(std::forward<Tup>(tup))) {
        return std::get<I::value>(std::forward<Tup>(tup));
    }
};

}}

#endif
