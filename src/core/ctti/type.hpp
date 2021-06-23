#pragma once

#include <core/collections/tuple.hpp>
#include <core/attr/class.hpp>
#include <core/attr/name.hpp>
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
		return this->template get<attr::Name>(); 
	}
	
	constexpr bool is_class() const { return this->template has<attr::Class>(); }

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