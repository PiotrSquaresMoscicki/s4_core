#pragma once

#include <core/ctti/type.hpp>
#include <core/attr/class.hpp>
#include <core/attr/name.hpp>
//#include <core/attr/fields.hpp>

namespace core::ctti {

//------------------------------------------------------------------------------------------------
template <typename T>
constexpr auto get_type() { return T::template getTypeInfo<T>(); }

} // namespace core::ctti

//------------------------------------------------------------------------------------------------
#define CTTI_DECLARE_CLASS(CLASS)\
	friend constexpr auto ::core::ctti::get_type<::CLASS>();\
	template <typename CttiDeclarationTypename>\
	static constexpr auto getTypeInfo()\
	{\
		return ::core::ctti::TypeFactory<CttiDeclarationTypename>::get\
		(\
			::core::attr::Name(#CLASS),

//------------------------------------------------------------------------------------------------
#define CTTI_END\
			::core::attr::Class()\
		);\
	}

//------------------------------------------------------------------------------------------------
#define CTTI_DECLARE_FUNDAMENTAL(TYPE)\
	template <>\
	constexpr auto ::core::ctti::getTypeInfo<TYPE>()\
	{\
		return ::core::ctti::TypeFactory<TYPE>::create(::core::attr::Name(#TYPE));\
	}

// #pragma once

// template <typename... Args>
// constexpr core::ConstexprString getFullTemplateClassName(core::ConstexprString className)
// {
// 	core::ConstexprString args = getFullTemplateClassName<Args...>();

// 	//auto classStatic = StringFactory<className.length()>(className.get());
// 	//auto argsStatic = StringFactory<args.length()>(args.get());

// 	//return core::ConstexprString((classStatic + "<" + argsStatic + ">").Get());
// 	return core::ConstexprString("asdf");
// }

// template <typename First, typename... Rest>
// constexpr const char* getFullTemplateClassName()
// {
// 	core::ConstexprString first = ctti::get<First>().template get<attr::Name>();
// 	core::ConstexprString rest = getFullTemplateClassName<Rest...>();
// 	auto firstStatic = StringFactory<first.length()>(first.get());
// 	auto restStatic = StringFactory<rest.length()>(rest.get());
// 	return (firstStatic + ", " + restStatic).Get();
// }

// template <typename Last>
// constexpr const char* getFullTemplateClassName()
// {
// 	return ctti::get<Last>().get<attr::Name>().get();
// }

// #define CTTI_DECLARE_TEMPLATE_CLASS(CLASS, ...)\
// 	friend constexpr auto ::ctti::get<::CLASS<__VA_ARGS__>>();\
// 	template <typename CttiDeclarationTypename>\
// 	static constexpr auto getTypeInfo()\
// 	{\
// 		return ::ctti::AttrArrayFactory<CttiDeclarationTypename>::get\
// 		(\
// 			::attr::Name(#CLASS),

// #define DECLARE_FIELD(FIELD, ...)\
// 	::ctti::AttrArrayFactory<CttiDeclarationTypename>::get\
// 	(\
// 		::attr::Name("d"), \
// 		attr::FieldPointer(&CttiDeclarationTypename::FIELD),\
// 		__VA_ARGS__\
// 	)