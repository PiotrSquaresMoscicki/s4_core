#pragma once

#include <core/collections/tuple.hpp>
#include <core/attr/name.hpp>

namespace core::ctti {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename... Attrs>
class Fields : public collections::Tuple<Attrs...> {
public:
    constexpr Fields(Attrs... attrs) 
        : Tuple<Attrs...>(std::forward<Attrs>(attrs)...) {}

}; // class Fields

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename T, typename C>
class FieldPointer {
public:
    constexpr FieldPointer(T C::* p) : m_ptr(p) {}

    constexpr T& get(C& c) const { return c.*m_ptr; }
    constexpr const T& get(const C& c) const { return c.*m_ptr; }

private:
    T C::* m_ptr = nullptr;

}; // class FieldPointer

} // namespace core::ctti

//------------------------------------------------------------------------------------------------
#define DECLARE_FIELD(FIELD, ...)\
	::ctti::AttrArrayFactory<CttiDeclarationTypename>::get\
	(\
		::attr::Name("d"), \
		attr::FieldPointer(&CttiDeclarationTypename::FIELD),\
		__VA_ARGS__\
	)

