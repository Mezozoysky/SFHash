#include <SHXX/SHash32.hpp>
#include <xxhash.h>
#include <cstring>

namespace shxx
{

constexpr SHash32::SHash32() noexcept
: mValue(0)
{
}

constexpr SHash32::SHash32(const SHash32::ValueType& value) noexcept
: mValue(value)
{
}

SHash32::SHash32(const char* str)
{
    std::size_t length = std::strlen(str);
    mValue = (ValueType)XXH32(static_cast<const void*>(str), length, seed);
}

SHash32::SHash32(const std::string& str)
{
    mValue = (ValueType)XXH32(static_cast<const void*>(str.data()), str.size(), seed);
}

//SHash32::SHash32(const std::string_view& str)
//{
    //mValue = (ValueType)XXH32(static_cast<const void*>(str.data()), str.size(), seed);
//}

} // namespace shxx

