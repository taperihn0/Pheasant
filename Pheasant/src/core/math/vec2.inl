#pragma once

#include "vec2.h"
#include "precompile.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE vec2<T>::vec() PHS_MATH_NOEXCEPT
   : x(__Zero)
   , y(__Zero)
{}

template <typename T>
template <dim_int_t Dim, typename CastT>
constexpr PHS_INLINE vec2<T>::vec(const vec<Dim, CastT>& v) PHS_MATH_NOEXCEPT
{
   x = static_cast<T>(v.x);
   y = static_cast<T>(v.y);
}

template <typename T>
constexpr PHS_INLINE vec2<T>::vec(T s1, T s2) PHS_MATH_NOEXCEPT
   : x(s1)
   , y(s2)
{}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::round()
{
   if constexpr (is_real<T>)
   {
      x = round64f(x);
      y = round64f(y);
      return *this;
   }

   if constexpr (is_integral<T>)
   {
      return *this;
   }

   return *this;
}

template <typename T>
constexpr PHS_INLINE float64_t vec2<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   return sq(x) + sq(y);
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator+(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   vec2<T> res(x + v.x, y + v.y);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator-(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   vec2<T> res(x - v.x, y - v.y);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   vec2<T> res(s * x, s * y);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator/(T s) const
{
   vec2<T> res(x / s, y / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator*(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   vec2<T> res(x * v.x, y * v.y);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec2<T> vec2<T>::operator/(const vec2<T>& v) const
{
   vec2<T> res(x / v.x, y / v.y);
   return res;
}

template <typename T>
constexpr PHS_INLINE bool vec2<T>::operator==(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   return x == v.x and y == v.y;
}

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec2<T>& v)
{
   static constexpr std::string_view vt_str = is_real<T> ? "vec2f" : "vec2i";
   return out << vt_str << '(' << v.x << ',' << v.y << ')';
}

template <typename T>
constexpr PHS_INLINE T dot(const vec2<T>& a, const vec2<T>& b) PHS_MATH_NOEXCEPT
{
   const T sum = a.x * b.x + a.y * b.y;
   return sum;
}

template <typename T>
constexpr PHS_INLINE bool approxEqual(const vec2<T>& a, const vec2<T>& b) PHS_MATH_NOEXCEPT
{
   if constexpr (is_integral<T>)
      return a == b;

   return approxEqual64f(a.x, b.x) and
          approxEqual64f(a.y, b.y);
}

} // namespace Phs
