#pragma once

#include <cstdint>
#include <string>

namespace shxx
{

class SHash32
{
public:
    using ValueType = std::uint_fast32_t;

public:
    static unsigned int seed;

public:
    constexpr SHash32() noexcept;
    constexpr explicit SHash32(const ValueType& value) noexcept;

    SHash32(const char* str);
    SHash32(const std::string& str);
    //SHash32(const std::string_view& str);

    inline constexpr bool isValid() const
    {
        return (mValue != 0);
    }

    inline constexpr explicit operator bool() const
    {
        return isValid();
    }

    inline ValueType value() const noexcept
    {
        return mValue;
    }

private:
    ValueType mValue;
};

} // namespace shxx

