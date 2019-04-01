#ifndef MAGIC_HPP
#define MAGIC_HPP
#include <type_traits>
namespace Magic{
//circle_for_each
template<typename InputIterator,
         typename Function,
         typename Size>
void inline circle_for_each_n(InputIterator first,
                            InputIterator last,
                            Size roll,
                            Function func){
    auto temp = first;
    for(decltype (roll) i=1; i<=roll; i++){
        while(first != last){
            func(*first);
            ++first;
        }
        first = temp;
    }
}
template<typename InputIterator,
         typename Predicate,
         typename Function>
void inline circle_for_each(InputIterator first,
                            InputIterator last,
                            Predicate pred,
                            Function func){
    auto temp = first;
    while(pred(*first)){
        func(*first);
        ++first;
        if(first == last){
            first = temp;
        }
    }
}

//Or
template<bool...>
struct Or;
template<>
struct Or<>{
    constexpr static bool value = false;
};
template<bool b>
struct Or<b>{
    constexpr static bool value = b;
};
template<bool b1, bool b2>
struct Or<b1, b2>{
    constexpr static bool value = b1 || b2;
};
template<bool b1, bool... bn>
struct Or<b1, bn...>{
    constexpr static bool value = Or<b1>::value || Or<bn...>::value;
};

//and
template<bool...>
struct And;
template<>
struct And<>{
    constexpr static bool value = false;
};
template<bool b1>
struct And<b1>{
    constexpr static bool value = b1;
};
template<bool b1, bool b2>
struct And<b1, b2>{
    constexpr static bool value = b1 && b2;
};
template<bool b1, bool... bn>
struct And<b1, bn...>{
    constexpr static bool value = And<b1>::value && And<bn...>::value;
};
template<bool...>
struct Not;
template<bool b>
struct Not<b>{
    constexpr static bool value = !b;
};
template<>
struct Not<>{
    constexpr static bool value = 1;
};
template<bool... b>
struct Nor{
    constexpr static bool value = !Or<b...>::value;
};
template<bool... b>
struct Nand{
    constexpr static bool value = !And<b...>::value;
};
template<bool... b>
struct Xor;
template<>
struct Xor<>{
    constexpr static bool value = 0;
};
template<bool b>
struct Xor<b>{
    constexpr static bool value = b;
};
template<bool b1, bool b2>
struct Xor<b1, b2>{
    constexpr static bool value = b1 ^ b2;
};
template<bool b1, bool... bn>
struct Xor<b1, bn...>{
    constexpr static bool value = Xor<b1>::value ^ Xor<bn...>::value;
};
template<bool... b>
struct Xnor{
    constexpr static bool value = !Xor<b...>::value;
};

template<typename T, bool>
struct Enable_if;
template<typename T>
struct Enable_if<T, 0>{
};
template<typename T>
struct Enable_if<T, 1>{
    using type = T;
};
//require
template<typename T, bool...b>
using require = Enable_if<T, And<b...>::value>;

//is_all_same
template<typename...>
struct is_all_same;
template<typename T1, typename T2>
struct is_all_same<T1, T2>{
    constexpr static bool value = false;
};
template<typename T>
struct is_all_same<T, T>{
    constexpr static bool value = true;
};
template<typename T1,
         typename T2,
         typename... Tn>
struct is_all_same<T1, T2, Tn...>{
    constexpr static bool value = is_all_same<T1, T2>::value && is_all_same<T2, Tn...>::value;
};
//expect some future change
}
#endif // MAGIC_HPP
