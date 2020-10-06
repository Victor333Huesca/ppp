#pragma once

#include <type_traits>
#include <iterator> // std::begin

// Generator
// Enumerate

namespace ppp
{

template <typename T>
struct enum_it
{
    enum_it(T it, int c = 0);

    enum_it& operator++();
    auto operator++(int) -> enum_it;

    auto operator*(); // -> std::pair<typename _c, typename *it>
    auto operator->(); // -> std::unique_ptr<std::pair<int, typename T::value_type>>

    bool operator!= (const enum_it &rhs) const;

private:
    T _it;
    int _c;
};

template <typename T>
struct enum_type
{
    enum_type(T &ref);

    auto begin(); //-> decltype(auto); //enum_it<decltype(std::begin(std::declval<T&>()))>;
    auto end(); //-> decltype(auto); // enum_it<decltype(std::begin(std::declval<T&>()))>;

private:
    T &_ref;
};


template <typename T>
enum_type<T> enumerate(T &iterable);

} // namespace PPP

#include "PPP.tpp"