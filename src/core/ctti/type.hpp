#pragma once

#include <core/collections/tuple.hpp>
#include <core/attr/name.hpp>
#include <core/attr/sizeof.hpp>
#include <core/attr/struct.hpp>
#include <core/attr/fundamental.hpp>

namespace core::ctti {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename T, typename... Attrs>
class Type : public collections::Tuple<Attrs...> {
public:
	constexpr Type(Attrs... attrs) 
		: collections::Tuple<Attrs...>(std::forward<Attrs>(attrs)...) {}

	constexpr const strings::ConstexprString& get_name() const { 
		return this->template get_one<attr::Name>(); 
	}

	constexpr size_t get_sizeof() const { return this->template get_one<attr::Sizeof>().m_size; }
	
	constexpr bool is_struct() const { return this->template has<attr::Struct>(); }
	constexpr bool is_fundamental() const { return this->template has<attr::Fundamental>(); }

}; // class Type

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename T>
class TypeFactory
{
public:
	template <typename... Attrs>
	static constexpr Type<T, Attrs...> get(Attrs... attrs) {
		return Type<T, Attrs...>(std::forward<Attrs>(attrs)...);
	}
}; // class TypeFactory

} // namespace core::ctti