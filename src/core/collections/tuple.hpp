#pragma once

#include <functional>
#include <type_traits>
#include <cassert>

namespace core::collections {

// IsInstanceOf - check if given parameter pack contains instance of template T
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <template <typename...> typename T, typename... I>
struct IsInstanceOf : public std::false_type {};

//------------------------------------------------------------------------------------------------
template <template <typename...> typename T, typename... I>
struct IsInstanceOf<T, T<I...>> : public std::true_type {};

// IsUnique - check if parameter pack doesn't contain two elements of the same type or instances of the same template
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename...>
inline constexpr auto IsUnique = std::true_type{};

//------------------------------------------------------------------------------------------------
template <typename T, typename... Rest>
inline constexpr auto IsUnique<T, Rest...> = std::bool_constant<(!std::is_same_v<T, Rest> && ...) && IsUnique<Rest...>>{};

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template<typename... Args>
class Tuple {};

//------------------------------------------------------------------------------------------------
template <typename First, typename... Rest>
class Tuple<First, Rest...> {
public:
	constexpr Tuple(First first, Rest... rest) : m_first(std::forward<First>(first)), m_rest(std::forward<Rest>(rest)...) {}

	// size
	constexpr size_t size() const { return 1 + sizeof...(Rest); }

	// has given type
	template<typename T>
	constexpr bool has() const { return std::disjunction_v<std::is_same<T, First>, std::is_same<T, Rest>...>; }
	template<template <typename...> typename T>
	constexpr bool has() const { return std::disjunction_v<IsInstanceOf<T, First>, IsInstanceOf<T, Rest>...>; }

	// get by index
	template<size_t idx>
	constexpr auto& at()
	{
		if constexpr (idx == 0)
			return m_first;
		else
			return m_rest.template at<idx - 1>();
	}

	template<size_t idx>
	constexpr const auto& at() const
	{
		if constexpr (idx == 0)
			return m_first;
		else
			return m_rest.template at<idx - 1>();
	}

	// get by type
	template <typename T>
	constexpr T& get()
	{
		if constexpr (std::is_same<T, First>::value)
			return m_first;
		else
			return m_rest.template get<T>();
	}

	template <typename T>
	constexpr const T& get() const

	{
		if constexpr (std::is_same<T, First>::value)
			return m_first;
		else
			return m_rest.template get<T>();
	}

	template<template <typename...> typename T>
	constexpr auto& get()
	{
		if constexpr (IsInstanceOf<T, First>::value)
			return m_first;
		else
			return m_rest.template get<T>();
	}

	template<template <typename...> typename T>
	constexpr const auto& get() const
	{
		if constexpr (IsInstanceOf<T, First>::value)
			return m_first;
		else
			return m_rest.template get<T>();
	}

	// @todo: implement rest of get methods

private:
	First m_first;
	Tuple<Rest...> m_rest;

}; // class Tuple<First, Rest...>

//------------------------------------------------------------------------------------------------
template<typename First>
class Tuple<First>
{
public:
	constexpr Tuple(First first) : m_first(std::forward<First>(first)) {}

	// size
	constexpr size_t size() const { return 1; }

	// has given type
	template<typename T>
	constexpr bool has() const { return std::is_same<T, First>::value; }
	template<template <typename...> typename T>
	constexpr bool has() const { return IsInstanceOf<T, First>::value; }

	// get by index
	template<size_t idx>
	constexpr First& at() { assert(idx == 0); return m_first; }
	template<size_t idx>
	constexpr const First& at() const { assert(idx == 0); return m_first; }

	// get by type
	template <typename T>
	constexpr T& get() { static_assert(std::is_same<T, First>::value); return m_first; }
	template <typename T>
	constexpr const T& get() const { static_assert(std::is_same<T, First>::value); return m_first; }
	template<template <typename...> typename T>
	constexpr auto& get() { static_assert(IsInstanceOf<T, First>::value); return m_first; }
	template<template <typename...> typename T>
	constexpr const auto& get() const { static_assert(IsInstanceOf<T, First>::value); return m_first; }

private:
	First m_first;

}; // class Tuple<First>

//------------------------------------------------------------------------------------------------
template <typename First, typename... Rest>
Tuple(First, Rest...)->Tuple<First, Rest...>;

template <typename First>
Tuple(First)->Tuple<First>;

} // namespace core {