#pragma once

#include "vec2.h"
#include "precompile.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE vec4<T>::vec() PHS_MATH_NOEXCEPT
   : x(__Zero)
   , y(__Zero)
   , z(__Zero)
   , w(__Zero)
{}

template <typename T>
template <dim_int_t Dim>
constexpr PHS_INLINE vec4<T>::vec(const vec<Dim, T>& v) PHS_MATH_NOEXCEPT
{
   x = v.x;
   y = v.y;

   if constexpr (Dim <= 2)
      z = __Zero;
   else
      z = v.z;

   if constexpr (Dim <= 3)
      w = __Zero;
   else
      w = v.w;
}

template <typename T>
constexpr PHS_INLINE vec4<T>::vec(T s1, T s2, T s3, T s4) PHS_MATH_NOEXCEPT
   : x(s1)
   , y(s2)
   , z(s3)
   , w(s4)
{}

template <typename T>
constexpr PHS_INLINE vec4<T>& vec4<T>::round()
{
   if constexpr (is_real<T>)
   {
      x = round64f(x);
      y = round64f(y);
      z = round64f(z);
      w = round64f(w);
      return *this;
   }
   else if constexpr (is_integral<T>)
      return *this;
   else
      PHS_STATIC_ASSERT(false);

   return *this;
}

template <typename T>
constexpr PHS_INLINE vec4<T>& vec4<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   return sq(x) + sq(y) + sq(z) + sq(w);
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator+(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec4<T> res(x + v.x, y + v.y, z + v.z, w + v.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator-(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec4<T> res(x - v.x, y - v.y, z - v.z, w - v.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   vec4<T> res(s * x, s * y, s * z, s * w);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator/(T s) const
{
   vec4<T> res(x / s, y / s, z / s, w / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator*(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec3<T> res(x * v.x, y * v.y, z * v.z, w * v.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator/(const vec4<T>& v) const
{
   vec2<T> res(x / v.x, y / v.y, z / v.z, w / v.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE bool vec4<T>::operator==(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   return x == v.x and y == v.y and z == v.z and w == v.w;
}

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec4<T>& v)
{
   static constexpr std::string_view vt_str = is_real<T> ? "vec4f" : "vec4i";
   return out << vt_str << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
}

template <typename T>
constexpr PHS_INLINE T dot(const vec4<T>& a, const vec4<T>& b) PHS_MATH_NOEXCEPT
{
   const T sum = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
   return sum;
}


} // namespace Phs
