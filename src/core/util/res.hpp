#pragma once

#include <optional>
#include <variant>

namespace core::util {

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    template <typename OK = void>
	class Ok final
	{
	public:
		Ok() = delete;
		Ok(Ok&) = delete;
		constexpr Ok(Ok&&) = default;
		Ok& operator=(Ok&) = delete;
		Ok& operator=(Ok&&) = delete;

		explicit constexpr Ok(OK val) : m_value(std::move(val)) {}

		constexpr OK&& get() && { return std::move(m_value); }

	private:
		OK m_value;

	}; // class Ok

    //*********************************************************************************************
	template <>
	class Ok<void> final
	{
	public:
		constexpr Ok() = default;
		Ok(Ok&) = delete;
		constexpr Ok(Ok&&) = default;
		Ok& operator=(Ok&) = delete;
		Ok& operator=(Ok&&) = delete;
	
	}; // class Ok<void>

	Ok()->Ok<void>;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
	template <typename ERR>
	class Err final
	{
	public:
		Err() = delete;
		Err(Err&) = delete;
		constexpr Err(Err&&) = default;
		Err& operator=(Err&) = delete;
		Err& operator=(Err&&) = delete;

		explicit constexpr Err(ERR val) : m_value(std::move(val)) {}

		constexpr ERR&& get() && { return std::move(m_value); }

	private:
		ERR m_value;
	
	}; // class Err

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    template <typename OK, typename ERR>
	class Res final
	{
	public:
		Res() = delete;
		constexpr Res(Res&) = default;
		constexpr Res(Res&&) = default;
		constexpr Res& operator=(Res&) = default;
		constexpr Res& operator=(Res&&) = default;
		constexpr Res(Ok<OK> ok) : m_value(std::move(ok).get()) {}
		constexpr Res(Err<ERR> err) : m_value(std::move(err).get()) {}

		constexpr bool is_ok() const { return m_value.index() == 0; }
		constexpr bool is_err() const { return m_value.index() == 1; }

		constexpr OK& ok() & { return std::get<OK>(m_value); }
		constexpr const OK& ok() const & { return std::get<OK>(m_value); }
		constexpr OK&& ok() && { return std::get<OK>(std::move(m_value)); }

		constexpr ERR& err() & { return std::get<ERR>(m_value); }
		constexpr const ERR& err() const & { return std::get<ERR>(m_value); }
		constexpr ERR&& err() && { return std::get<ERR>(std::move(m_value)); }

	private:
		std::variant<OK, ERR> m_value;
	
	}; // class Res

    //*********************************************************************************************
	template <typename ERR>
	class Res<void, ERR> final
	{
	public:
		constexpr Res() = delete;
		constexpr Res(Res&) = default;
		constexpr Res(Res&&) = default;
		constexpr Res& operator=(Res&) = default;
		constexpr Res& operator=(Res&&) = default;
		constexpr Res(Ok<void> ok) {}
		constexpr Res(Err<ERR> err) : m_value(std::move(err).get()) {}

		constexpr bool is_ok() const { return !is_err(); }
		constexpr bool is_err() const { return m_value.has_value(); }
        
		constexpr ERR& err() & { return m_value.value(); }
		constexpr const ERR& err() const & { return m_value.value(); }
		constexpr ERR&& err() && { return std::move(m_value).value(); }

	private:
		std::optional<ERR> m_value;
	}; // class Res<void, ERR>

} // namespace core
