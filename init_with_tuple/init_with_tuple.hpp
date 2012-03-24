#include <utility>
 
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/tuple/eat.hpp"
#include "boost/preprocessor/tuple/rem.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"
#include "boost/preprocessor/facilities/is_empty.hpp"

namespace init_with_tuple {

struct ignore_t {
    template<typename T> ignore_t & operator=(T&&) const {}
};

constexpr ignore_t ignore{};

}

#define INIT_WITH_TUPLE(tupseq, ...) INIT_WITH_TUPLE_I(INIT_WITH_TUPLE_TO_SEQ(tupseq), (__VA_ARGS__), BOOST_PP_CAT(init_with_tuple_tmp_, __LINE__))
#define INIT_WITH_TUPLE_I(seq, expr, tmp) \
    auto && tmp = expr \
    BOOST_PP_SEQ_FOR_EACH_I(INIT_WITH_TUPLE_M, tmp, seq)
 
#define INIT_WITH_TUPLE_M(r, tmp, i, elem) \
    BOOST_PP_IIF(INIT_WITH_TUPLE_IS_PAREN(elem), INIT_WITH_TUPLE_M_I, BOOST_PP_TUPLE_EAT(3))(tmp, i, BOOST_PP_TUPLE_REM(1) elem)
#define INIT_WITH_TUPLE_M_I(tmp, i, elem) INIT_WITH_TUPLE_M_II(tmp, i, elem)
#define INIT_WITH_TUPLE_M_II(tmp, i, ...) \
    ; __VA_ARGS__ = std::get<i>(std::forward<decltype((tmp))>(tmp))

#define INIT_WITH_TUPLE_TO_SEQ(tupseq) BOOST_PP_CAT(INIT_WITH_TUPLE_PACK_A tupseq, _END)
#define INIT_WITH_TUPLE_PACK_A(...) ((__VA_ARGS__)) INIT_WITH_TUPLE_PACK_B
#define INIT_WITH_TUPLE_PACK_B(...) ((__VA_ARGS__)) INIT_WITH_TUPLE_PACK_A
#define INIT_WITH_TUPLE_PACK_A_END
#define INIT_WITH_TUPLE_PACK_B_END

#define INIT_WITH_TUPLE_IS_PAREN(...) BOOST_PP_TUPLE_ELEM(0, (INIT_WITH_TUPLE_CAT(INIT_WITH_TUPLE_IS_PAREN_CHECK_, INIT_WITH_TUPLE_IS_PAREN_HELPER __VA_ARGS__)))
#define INIT_WITH_TUPLE_IS_PAREN_HELPER(...) INIT_WITH_TUPLE_IS_PAREN_HELPER_I tokens

#define INIT_WITH_TUPLE_IS_PAREN_CHECK_INIT_WITH_TUPLE_IS_PAREN_HELPER 0,
#define INIT_WITH_TUPLE_IS_PAREN_CHECK_INIT_WITH_TUPLE_IS_PAREN_HELPER_I 1,

#define INIT_WITH_TUPLE_CAT(x, y, ...) INIT_WITH_TUPLE_CAT_I(x, y)
#define INIT_WITH_TUPLE_CAT_I(x, y) x ## y
