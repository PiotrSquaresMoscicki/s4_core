#pragma once

#include <functional>
#include <type_traits>
#include <cassert>

namespace core::collections {

	// IsInstanceOf - check if given parameter pack contains instance of template T
	//*********************************************************************************************
	//*********************************************************************************************
	//*********************************************************************************************
	template <template <typename...> typename T, typename... I>
	struct IsInstanceOf : public std::false_type {};

	//*********************************************************************************************
	template <template <typename...> typename T, typename... I>
	struct IsInstanceOf<T, T<I...>> : public std::true_type {};

	// IsUnique - check if parameter pack doesn't contain two elements of the same type or instances of the same template
	//*********************************************************************************************
	//*********************************************************************************************
	//*********************************************************************************************
	template <typename...>
	inline constexpr auto IsUnique = std::true_type{};

	//*********************************************************************************************
	template <typename T, typename... Rest>
	inline constexpr auto IsUnique<T, Rest...> = std::bool_constant<(!std::is_same_v<T, Rest> && ...) && IsUnique<Rest...>>{};

	//*********************************************************************************************
	//*********************************************************************************************
	//*********************************************************************************************
	template<typename... Args>
	class Tuple {
	public:
		// length
		constexpr size_t length() const { return 0; }

		// has given type
		template<typename T>
		constexpr bool has() const { return false; }
		template<template <typename...> typename T>
		constexpr bool has() const { return false; }
	};

	//*********************************************************************************************
	template <typename First, typename... Rest>
	class Tuple<First, Rest...> {
	public:
		constexpr Tuple(First first, Rest... rest) 
			: m_first(std::forward<First>(first)), m_rest(std::forward<Rest>(rest)...) {}

		// length
		constexpr size_t length() const { return 1 + sizeof...(Rest); }

		// has given type
		template<typename T>
		constexpr bool has() const { 
			return std::disjunction_v<std::is_same<T, First>, std::is_same<T, Rest>...>; 
		
		}
		template<template <typename...> typename T>
		constexpr bool has() const { 
			return std::disjunction_v<IsInstanceOf<T, First>, IsInstanceOf<T, Rest>...>; 
		}

		// get_one by index
		template<size_t idx>
		constexpr auto& at() {
			if constexpr (idx == 0)
				return m_first;
			else
				return m_rest.template at<idx - 1>();
		}

		template<size_t idx>
		constexpr const auto& at() const {
			if constexpr (idx == 0)
				return m_first;
			else
				return m_rest.template at<idx - 1>();
		}

		// get_one by type
		template <typename T>
		constexpr T& get_one() {
			if constexpr (std::is_same<T, First>::value)
				return m_first;
			else
				return m_rest.template get_one<T>();
		}

		template <typename T>
		constexpr const T& get_one() const {
			if constexpr (std::is_same<T, First>::value)
				return m_first;
			else
				return m_rest.template get_one<T>();
		}

		template<template <typename...> typename T>
		constexpr auto& get_one() {
			if constexpr (IsInstanceOf<T, First>::value)
				return m_first;
			else
				return m_rest.template get_one<T>();
		}

		template<template <typename...> typename T>
		constexpr const auto& get_one() const {
			if constexpr (IsInstanceOf<T, First>::value)
				return m_first;
			else
				return m_rest.template get_one<T>();
		}

		// get_all by type
		template <typename T>
		constexpr auto get_all() const {
			return this->template get_all_internal_1<T>(this->m_rest.template get_all<T>());
		}

		template<template <typename...> typename T>
		constexpr auto get_all() const {
			return this->template get_all_internal_1<T>(this->m_rest.template get_all<T>());
		}

		// @todo: implement rest of get_one methods

	private:
		template <typename T, typename... Args>
		constexpr auto get_all_internal_1(Tuple<Args...> from_rest) const {
			constexpr auto from_rest_len = from_rest.length();

			if constexpr (from_rest_len > 0) {
				if constexpr (std::is_same<T, First>::value) {
					return get_all_internal_2(std::make_index_sequence<from_rest_len>{}, m_first, 
						from_rest);
				}
				else 
					return from_rest;
			}
			else{
				if constexpr (std::is_same<T, First>::value)
					return ::core::collections::Tuple(m_first);
				else 
					return ::core::collections::Tuple();
			}
		}

		template <size_t... Indexes, typename T, typename... Args>
		constexpr auto get_all_internal_2(std::index_sequence<Indexes...>, T first, 
			Tuple<Args...> rest) const {
			return ::core::collections::Tuple(first, rest.template at<Indexes>()...);
		}

		template <template <typename...> typename T, typename... Args>
		constexpr auto get_all_internal_1(Tuple<Args...> from_rest) const {
			constexpr auto from_rest_len = from_rest.length();

			if constexpr (from_rest_len > 0) {
				if constexpr (IsInstanceOf<T, First>::value) {
					return get_all_internal_2(std::make_index_sequence<from_rest_len>{}, m_first, 
						from_rest);
				}
				else 
					return from_rest;
			}
			else{
				if constexpr (IsInstanceOf<T, First>::value)
					return ::core::collections::Tuple(m_first);
				else 
					return ::core::collections::Tuple();
			}
		}

		First m_first;
		Tuple<Rest...> m_rest;

	}; // class Tuple<First, Rest...>

	//*********************************************************************************************
	template<typename First>
	class Tuple<First>
	{
	public:
		constexpr Tuple(First first) : m_first(std::forward<First>(first)) {}

		// length
		constexpr size_t length() const { return 1; }

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

		// get_one by type
		template <typename T>
		constexpr T& get_one() { static_assert(std::is_same<T, First>::value); return m_first; }
		template <typename T>
		constexpr const T& get_one() const { static_assert(std::is_same<T, First>::value); return m_first; }
		template<template <typename...> typename T>
		constexpr auto& get_one() { static_assert(IsInstanceOf<T, First>::value); return m_first; }
		template<template <typename...> typename T>
		constexpr const auto& get_one() const { static_assert(IsInstanceOf<T, First>::value); return m_first; }

		// get_all by type
		template <typename T>
		constexpr auto get_all() const {
			if constexpr (std::is_same<T, First>::value)
				return ::core::collections::Tuple(m_first);
			else 
				return ::core::collections::Tuple();
		}
		
		template<template <typename...> typename T>
		constexpr auto get_all() const {
			if constexpr (IsInstanceOf<T, First>::value)
				return ::core::collections::Tuple(m_first);
			else 
				return ::core::collections::Tuple();
		}

	private:
		First m_first;

	}; // class Tuple<First>

	//*********************************************************************************************
	template <typename First, typename... Rest>
	Tuple(First, Rest...)->Tuple<First, Rest...>;

	template <typename First>
	Tuple(First)->Tuple<First>;

} // namespace core::collections