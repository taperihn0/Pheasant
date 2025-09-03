#pragma once

#include "vec.h"
#include "precompile.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE vec2<T>::vec() PHS_MATH_NOEXCEPT
   : x(static_cast<T>(0)), y(static_cast<T>(0))
{}

template <typename T>
template <dim_int_t Dim>
constexpr PHS_INLINE vec2<T>::vec(const vec<Dim, T>& v) PHS_MATH_NOEXCEPT
{
   PHS_STATIC_ASSERT(Dim >= 2);
   x = v.x;
   y = v.y;
}

template <typename T>
constexpr PHS_INLINE vec2<T>::vec(T s) PHS_MATH_NOEXCEPT
{
   x = s;
}

template <typename T>
constexpr PHS_INLINE vec2<T>::vec(T s1, T s2) PHS_MATH_NOEXCEPT
{
   x = s1;
   y = s2;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::dim() PHS_MATH_NOEXCEPT
{
   return _Dimension;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::normalize() PHS_MATH_NOEXCEPT
{
   const float64_t len = length();
   *this /= len;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::round() PHS_MATH_NOEXCEPT
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
constexpr PHS_INLINE vec2<T>& vec2<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   return sq(x) + sq(y);
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::length() const PHS_MATH_NOEXCEPT
{
   return std::sqrt(lengthSquared());
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
constexpr PHS_INLINE vec2<T>& vec2<T>::operator+=(const vec2<T>& v) PHS_MATH_NOEXCEPT
{
   *this = *this + v;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::operator-=(const vec2<T>& v) PHS_MATH_NOEXCEPT
{
   *this = *this - v;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::operator*=(T s) PHS_MATH_NOEXCEPT
{
   *this = *this * s;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::operator/=(T s)
{
   *this = *this / s;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::operator*=(const vec2<T>& v) PHS_MATH_NOEXCEPT
{
   *this = *this * v;
   return *this;
}

template <typename T>
constexpr PHS_INLINE vec2<T>& vec2<T>::operator/=(const vec2<T>&v)
{
   *this = *this / v;
   return *this;
}

template <typename T>
constexpr PHS_INLINE T& vec2<T>::operator[](size_t i) PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i <= 1);
   return *((&x) + i * sizeof(T));
}

template <typename T>
constexpr PHS_INLINE bool vec2<T>::operator==(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   return x == v.x and y == v.y;
}

template <typename T>
constexpr PHS_INLINE bool vec2<T>::operator!=(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   return x != v.x or y != v.y;
}

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec2<T>& v)
{
   static constexpr std::string_view vt_str = is_real<T> ? "vec2f" : "vec2i";
   return out << vt_str << '(' << v.x << ',' << v.y << ')';
}

template <typename T>
constexpr PHS_INLINE vec2<T> dot(const vec2<T>& a, const vec2<T>& b) PHS_MATH_NOEXCEPT
{
   vec2<T> res = a * b;
   return res;
}

} // namespace Phs
