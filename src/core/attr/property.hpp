#pragma once

#include <core/collections/tuple.hpp>
#include <core/attr/name.hpp>

namespace core::ctti {

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <typename T, typename s, typename... Attrs>
class Property : public collections::Tuple<Attrs...> {
public:
    constexpr Property(Attrs... attrs) 
        : collections::Tuple<Attrs...>(std::forward<Attrs>(attrs)...) {}

	constexpr const strings::ConstexprString& get_name() const { 
		return this->template get_one<attr::Name>(); 
	}

	constexpr const T& get(const S& structure) const 

}; // class Property

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

