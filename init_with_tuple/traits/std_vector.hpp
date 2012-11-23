#if !defined INIT_WITH_TUPLE_TRAITS_BOOST_FUSION_HPP_INCLUDED_
#define      INIT_WITH_TUPLE_TRAITS_BOOST_FUSION_HPP_INCLUDED_

#include <vector>
#include <utility>
#include <init_with_tuple/init_with_tuple.hpp>

template<typename T>
struct element_access<std::vector<T>> {
    template<typename I>
    static auto get(I, std::vector<T> const & v) noexcept(noexcept(v[I::value])) -> decltype(v[I::value]) {
        return v[I::value];
    }
    template<typename I>
    static auto get(I, std::vector<T> && v) noexcept(noexcept(std::move(v[I::value]))) -> decltype(std::move(v[I::value])) {
        return std::move(v[I::value]);
    }
};

#endif
