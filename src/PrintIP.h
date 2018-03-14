#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>

template<typename T>
struct HasBegin
{
	template<typename U>
	static std::true_type hasMember(decltype(std::declval<U>().begin())*);

	template<typename U>
	static std::false_type hasMember(...);

	using type = decltype(hasMember<T>(nullptr));
	static const bool value = type::value;
};

template<typename T>
struct HasEnd
{
	template<typename U>
	static std::true_type hasMember(decltype(std::declval<U>().end())*);

	template<typename U>
	static std::false_type hasMember(...);

	using type = decltype(hasMember<T>(nullptr));
	static const bool value = type::value;
};

template<typename T>
struct isContainer
{
	static const bool value = HasBegin<T>::value && HasEnd<T>::value;
};

template<typename T>
constexpr bool isContainer_v = isContainer<T>::value;

template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

template<class Container>
using containerType = typename Container::value_type;

template<typename T>
std::enable_if_t<isContainer_v<T> && is_integral_v<containerType<T>>, void> print_ip(const T &container)
{
	for (auto it = container.begin(); it != container.end(); ++it)
	{ 
		if (it != container.begin())
			std::cout << '.';
		std::cout << *it;
	}
	std::cout << std::endl;
}

template<typename T>
std::enable_if_t<is_integral_v<T>, void> print_ip(T value)
{
	auto* raw_str = reinterpret_cast<unsigned char*>(&value);
	std::vector<unsigned int> vec(raw_str, raw_str + sizeof(value));
	std::reverse(vec.begin(), vec.end());
	print_ip(vec);
  
}

void print_ip(const std::string &str)
{
	std::cout << str << std::endl;
}

template<typename Type, unsigned N, unsigned Last>
struct tuple_printer 
{
    static void print(const Type& value) 
    {
        std::cout << std::get<N>(value) << '.';
        tuple_printer<Type, N + 1, Last>::print(value);
    }
};

template<typename Type, unsigned N>
struct tuple_printer<Type, N, N> 
{
    static void print(const Type& value) 
    {
        std::cout << std::get<N>(value);
    }

};

template<typename... Args>
struct allSame: std::false_type {};

template<typename T>
struct allSame<T>: std::true_type{};

template<typename T, typename... Args>
struct allSame<T, T, Args...>: allSame<T, Args...> {};

template<typename... Args>
constexpr bool allSame_v = allSame<Args...>::value;

template<typename... Types>
std::enable_if_t<allSame_v<Types...>, void> print_ip(const std::tuple<Types...>& value) 
{
    tuple_printer<std::tuple<Types...>, 0, sizeof...(Types) - 1>::print(value);
    std::cout << std::endl;
}