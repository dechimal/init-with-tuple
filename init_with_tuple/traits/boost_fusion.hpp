#if !defined INIT_WITH_TUPLE_TRAITS_BOOST_FUSION_HPP_INCLUDED_
#define      INIT_WITH_TUPLE_TRAITS_BOOST_FUSION_HPP_INCLUDED_

#include <type_traits>
#include <utility>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/at.hpp>
#include <init_with_tuple/init_with_tuple.hpp>

namespace init_with_tuple { namespace traits {

template<typename Seq>
struct element_access<Seq, typename std::enable_if<boost::fusion::traits::is_sequence<Seq>::value>::type> {
    template<typename I>
    static auto get(I, Seq const & seq) noexcept(noexcept(boost::fusion::at<I>(seq))) -> decltype(boost::fusion::at<I>(seq)) {
        return boost::fusion::at<I>(seq);
    }
    template<typename I>
    static auto get(I, Seq && seq) noexcept(noexcept(boost::fusion::at<I>(std::move(seq)))) -> decltype(boost::fusion::at<I>(std::move(seq))) {
        return boost::fusion::at<I>(std::move(seq));
    }
};

}}

#endif
