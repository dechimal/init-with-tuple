#include <utility>
#include <tuple>
 
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
 
#define INIT_WITH_TUPLE(seq, expr) INIT_WITH_TUPLE_I(seq, expr, BOOST_PP_CAT(init_with_tuple_tmp_, __LINE__),)
#define INIT_WITH_TUPLE_AUTO(seq, expr) INIT_WITH_TUPLE_I(seq, expr, BOOST_PP_CAT(init_with_tuple_tmp_, __LINE__), auto)
#define INIT_WITH_TUPLE_I(seq, expr, tmp, type) \
    auto && tmp = expr; \
    BOOST_PP_SEQ_FOR_EACH_I(INIT_WITH_TUPLE_M, (tmp, type), seq)
 
#define INIT_WITH_TUPLE_M(r, data, i, elem) INIT_WITH_TUPLE_M_I(BOOST_PP_TUPLE_REM(2) data, i, elem)
#define INIT_WITH_TUPLE_M_I(data, i, elem) INIT_WITH_TUPLE_M_II(data, i, elem)
#define INIT_WITH_TUPLE_M_II(tmp, type, i, elem) \
    BOOST_PP_IIF(BOOST_PP_IS_EMPTY(elem), BOOST_PP_TUPLE_EAT(1), ; type elem) \
    (std::get<i>(std::forward<decltype((tmp))>(tmp)))
    
