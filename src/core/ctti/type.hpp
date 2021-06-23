#pragma once

#include <core/collections/tuple.h>

namespace core::ctti {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename T, typename... Attrs>
class Type : public collections::Tuple<Attrs...> {
public:
	constexpr Type(Attrs... attrs) 
		: collections::Tuple<Attrs...>(std::forward<Attrs>(attrs)...) {}
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