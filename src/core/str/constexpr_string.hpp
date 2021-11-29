#pragma once

#include <cstdint>
#include <core/str/string_constant.hpp>

// from https://github.com/Manu343726/ctti

namespace core::str
{
	using hash_t = uint64_t;
	constexpr hash_t fnv_basis = 14695981039346656037ull;
	constexpr hash_t fnv_prime = 1099511628211ull;

	// FNV-1a 64 bit hash
	constexpr hash_t fnv1a_hash(size_t n, const char* str, hash_t hash = fnv_basis)
	{
		return n > 0 ? fnv1a_hash(n - 1, str + 1, (hash ^ *str) * fnv_prime) : hash;
	}

	template<size_t N>
	constexpr hash_t fnv1a_hash(const char(&array)[N])
	{
		return fnv1a_hash(N - 1, &array[0]);
	}

	//*********************************************************************************************
	//*********************************************************************************************
	//*********************************************************************************************
	class ConstexprString
	{
	public:
		constexpr ConstexprString(const char* begin, size_t length)
			: m_str{ begin }, m_length{ length }
		{
		}
		template<size_t N>
		constexpr ConstexprString(const char(&str)[N])
			: ConstexprString{ &str[0], N - 1 }
		{
		}
		constexpr ConstexprString(const char* begin) 
			: ConstexprString{ begin, length(begin) }
		{
		}
		static constexpr size_t length(const char* str)
		{
			return *str ? 1 + length(str + 1) : 0;
		}
		constexpr size_t length() const
		{
			return m_length;
		}
		constexpr const char* get() const
		{
			return m_str;
		}
		constexpr hash_t hash() const
		{
			return fnv1a_hash(length(), get());
		}
        
	private:
		const char* m_str;
		size_t m_length;
	};
}