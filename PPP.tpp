#include "PPP.hpp"

#include <memory> // unique_ptr

namespace ppp
{

template <typename T>
enum_it<T>::enum_it(T it, int c) : _it{it}, _c{c} {}

template <typename T>
enum_it<T>& enum_it<T>::operator++() {
	++_it;
	++_c;
	return *this;
}

template <typename T>
auto enum_it<T>::operator++(int) -> enum_it {
	return {_it++, _c++};
}

template <typename T>
auto enum_it<T>::operator*() { return std::pair(_c, *_it); }

template <typename T>
auto enum_it<T>::operator->() {
	std::pair<int, typename T::value_type> *ptr = new std::pair(_c, *_it);
	return std::unique_ptr<std::pair<int, typename T::value_type>> (ptr);
}

template <typename T>
bool enum_it<T>::operator!=(const enum_it &rhs) const { return _it != rhs._it; }

template <typename T>
enum_type<T>::enum_type(T &ref) : _ref {ref} {}

template <typename T>
auto enum_type<T>::begin() { //-> decltype(auto) {
	return enum_it { std::begin(_ref) };
}

template <typename T>
auto enum_type<T>::end() { //-> decltype(auto) {
	return enum_it { std::end(_ref) };
}

template <typename T>
enum_type<T> enumerate(T &iterable) {
	return enum_type<T> {iterable};
}

} // namespace PPP
