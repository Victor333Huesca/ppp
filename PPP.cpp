#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>

// Generator
// Enumerate

namespace ppp 
{
	template <typename T>
	struct enum_it
	{
		enum_it(T it, int c = 0) : _it{it}, _c{c} {}

		enum_it & operator ++() { 
			++_it;
			++_c;
			return *this;
		}
		auto operator ++(int) -> enum_it {
			return {_it++, _c++};
		}

		auto operator *() { return std::pair(_c, *_it); }
		auto operator ->() { 
			std::pair<int, typename T::value_type> *ptr = new std::pair(_c, *_it);
			return std::unique_ptr<std::pair<int, typename T::value_type>> (ptr);
		}

		bool operator !=(const enum_it &rhs) const { return _it != rhs._it; }

	private:
		T _it;
		int _c;
	};

	template <typename T>
	struct enum_type
	{
		enum_type(T &ref) : _ref {ref} {}

		auto begin() {
			return enum_it { std::begin(_ref) };
		}
		auto end() {
			return enum_it { std::end(_ref) };
		}

	private:
		T &_ref;
	};


	template <typename T>
	enum_type<T> enumerate(T &iterable)
	{
		return enum_type<T> {iterable};
	}
}


int main(int argc, const char **argv)
{
	// std::vector v {1l, 2l, 3l, 4l, 5l};
	std::vector v {std::make_pair(0, 1l),
				   std::make_pair(1, 2l),
				   std::make_pair(2, 3l),
				   std::make_pair(3, 4l),
				   std::make_pair(4, 5l)};


	
	for (auto [i, k] : v) {
		std::cout << i << ", " << k << '\n';
	}
	std::cout << std::endl;

	for (auto it = std::begin(v); it != std::end(v); ++it) {
		// auto [a1, a2] = it;
		auto [b1, b2] = *it;
		auto a = it;
		auto b = *it;
	}
	std::cout << std::endl;




	for (auto [i, k] : ppp::enumerate(v)) {
		auto [j, r] = k;
		std::cout << i << ", " << j << ", " << r << '\n';
	}
	std::cout << std::endl;

	auto en = ppp::enumerate(v);
	for (auto it = std::begin(en); it != std::end(en); ++it) {
		// auto [a1, a2] = it;
		auto [b1, b2] = *it;
		auto [a,c] = it->second;
		auto b = *it;
	}
	std::cout << std::endl;


	std::cout << "\nFin\n" << std::endl;
	return EXIT_SUCCESS;
}
