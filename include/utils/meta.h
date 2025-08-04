#pragma once
#include <type_traits>

struct any_type {
    template <typename T>
    operator T();
};

template <typename, template <typename> class, typename = void>
struct detect : std::false_type {};

template <typename T, template <typename> class Op>
struct detect<T, Op, std::void_t<Op<T>>> : std::true_type {};

template <typename T, template <typename> class Op>
constexpr bool detect_v = detect<T, Op>::value;

template <typename T>
using has_to_string =
    decltype(std::declval<const T>().to_string(any_type {}));

template <typename T>
using has_stream_op = decltype(std::declval<std::ostream&>() << std::declval<T>());