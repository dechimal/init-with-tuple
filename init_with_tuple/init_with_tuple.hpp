#include <utility>
#include <type_traits>
 
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/facilities/is_empty.hpp"
#include "boost/preprocessor/tuple/eat.hpp"
#include "boost/preprocessor/tuple/rem.hpp"
#include "boost/preprocessor/control/iif.hpp"
#include "boost/preprocessor/logical/and.hpp"
#include "boost/preprocessor/logical/not.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"
#include "boost/preprocessor/seq/transform.hpp"

namespace init_with_tuple {

struct ignore_t {
    template<typename T> constexpr void operator=(T&&) const noexcept {}
};

constexpr ignore_t ignore{};

template<std::size_t N>
using nat = std::integral_constant<std::size_t, N>;

namespace traits {

template<typename, typename = void>
struct element_access;

template<typename ...Elems>
struct element_access<std::tuple<Elems...>> {
    template<typename I, typename Tup>
    static auto get(I, Tup && tup) noexcept -> decltype(std::get<I::value>(std::forward<Tup>(tup))) {
        return std::get<I::value>(std::forward<Tup>(tup));
    }
};

}

template<typename T>
struct element_access
    : traits::element_access<
          typename std::remove_reference<
              typename std::remove_cv<T>::type>::type>
{};

}

#define INIT_WITH_TUPLE(tupseq, ...) \
    INIT_WITH_TUPLE_I(INIT_WITH_TUPLE_TO_SEQ(tupseq), \
                      (__VA_ARGS__), \
                      typename std::decay<decltype(__VA_ARGS__)>::type, \
                      BOOST_PP_CAT(init_with_tuple_tmp_, __LINE__))
#define INIT_WITH_TUPLE_AUTO(names, ...) INIT_WITH_TUPLE(BOOST_PP_SEQ_TRANSFORM(INIT_WITH_TUPLE_AUTO_OP, ~, names), __VA_ARGS__)
#define INIT_WITH_TUPLE_I(seq, expr, type, tmp) \
    auto && tmp = expr \
    BOOST_PP_SEQ_FOR_EACH_I(INIT_WITH_TUPLE_M, (tmp, type), seq)

#define INIT_WITH_TUPLE_AUTO_OP(s, d, elem) BOOST_PP_EXPR_IIF(BOOST_PP_NOT(BOOST_PP_IS_EMPTY(elem)), auto && elem)

#define INIT_WITH_TUPLE_M(r, d, i, elem) INIT_WITH_TUPLE_M_I(BOOST_PP_TUPLE_REM(2) d, i, BOOST_PP_TUPLE_REM(1) elem)
#define INIT_WITH_TUPLE_M_I(d, i, elem) INIT_WITH_TUPLE_M_II(d, i, elem)
#define INIT_WITH_TUPLE_M_II(tmp, type, i, ...) \
    ; INIT_WITH_TUPLE_INSERT_IGNORE_IF_EMPTY(__VA_ARGS__) = init_with_tuple::element_access<type>().get(init_with_tuple::nat<i>{}, std::forward<type>(tmp))
#define INIT_WITH_TUPLE_INSERT_IGNORE_IF_EMPTY(...) \
    BOOST_PP_IIF(INIT_WITH_TUPLE_IS_EMPTY(__VA_ARGS__), init_with_tuple::ignore BOOST_PP_TUPLE_EAT, BOOST_PP_TUPLE_REM)()(__VA_ARGS__)

#define INIT_WITH_TUPLE_TO_SEQ(tupseq) BOOST_PP_CAT(INIT_WITH_TUPLE_PACK_A tupseq, _END)
#define INIT_WITH_TUPLE_PACK_A(...) ((__VA_ARGS__)) INIT_WITH_TUPLE_PACK_B
#define INIT_WITH_TUPLE_PACK_B(...) ((__VA_ARGS__)) INIT_WITH_TUPLE_PACK_A
#define INIT_WITH_TUPLE_PACK_A_END
#define INIT_WITH_TUPLE_PACK_B_END

#define INIT_WITH_TUPLE_IS_EMPTY(...) \
    INIT_WITH_TUPLE_IS_EMPTY_I(__VA_ARGS__)
#define INIT_WITH_TUPLE_IS_EMPTY_I(...) BOOST_PP_AND(BOOST_PP_NOT(INIT_WITH_TUPLE_IS_PAREN_LEFT(__VA_ARGS__)), \
                                                     INIT_WITH_TUPLE_IS_PAREN_RIGHT(__VA_ARGS__))
#define INIT_WITH_TUPLE_IS_PAREN_LEFT(...) \
    INIT_WITH_TUPLE_IS_PAREN_I(INIT_WITH_TUPLE_CAT(INIT_WITH_TUPLE_CHECK_, \
                               INIT_WITH_TUPLE_IS_PAREN_NG __VA_ARGS__))
#define INIT_WITH_TUPLE_IS_PAREN_RIGHT(...) \
    INIT_WITH_TUPLE_IS_PAREN_I(INIT_WITH_TUPLE_CAT(INIT_WITH_TUPLE_CHECK_, \
                               INIT_WITH_TUPLE_IS_PAREN_NG __VA_ARGS__ ()))
#define INIT_WITH_TUPLE_IS_PAREN_NG(...) INIT_WITH_TUPLE_IS_PAREN_OK
#define INIT_WITH_TUPLE_CHECK_INIT_WITH_TUPLE_IS_PAREN_OK 1,
#define INIT_WITH_TUPLE_CHECK_INIT_WITH_TUPLE_IS_PAREN_NG 0,
#define INIT_WITH_TUPLE_IS_PAREN_I(...) INIT_WITH_TUPLE_IS_PAREN_II(__VA_ARGS__)
#define INIT_WITH_TUPLE_IS_PAREN_II(cond, ...) cond

#define INIT_WITH_TUPLE_CAT(...) INIT_WITH_TUPLE_CAT_I(__VA_ARGS__)
#define INIT_WITH_TUPLE_CAT_I(x, ...) x ## __VA_ARGS__
