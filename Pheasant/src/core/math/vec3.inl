#pragma once

#include "vec2.h"
#include "precompile.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE vec3<T>::vec() PHS_MATH_NOEXCEPT
   : x(__Zero)
   , y(__Zero)
   , z(__Zero)
{}

template <typename T>
template <dim_int_t Dim, typename CastT>
constexpr PHS_INLINE vec3<T>::vec(const vec<Dim, CastT>& v) PHS_MATH_NOEXCEPT
{
   x = static_cast<T>(v.x);
   y = static_cast<T>(v.y);

   if constexpr (Dim == 2)
      z = __Zero;
   else
      z = static_cast<T>(v.z);
}

template <typename T>
constexpr PHS_INLINE vec3<T>::vec(T s1, T s2, T s3) PHS_MATH_NOEXCEPT
   : x(s1)
   , y(s2)
   , z(s3)
{}

template <typename T>
constexpr PHS_INLINE vec3<T>& vec3<T>::round()
{
   if constexpr (is_real<T>)
   {
      x = round64f(x);
      y = round64f(y);
      z = round64f(z);
      return *this;
   }

   if constexpr (is_integral<T>)
   {
      return *this;
   }

   return *this;
}

template <typename T>
constexpr PHS_INLINE float64_t vec3<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   return sq(x) + sq(y) + sq(z);
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator+(const vec3<T>& v) const PHS_MATH_NOEXCEPT
{
   vec3<T> res(x + v.x, y + v.y, z + v.z);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator-(const vec3<T>& v) const PHS_MATH_NOEXCEPT
{
   vec3<T> res(x - v.x, y - v.y, z - v.z);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   vec3<T> res(s * x, s * y, s * z);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator/(T s) const
{
   vec3<T> res(x / s, y / s, z / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator*(const vec3<T>& v) const PHS_MATH_NOEXCEPT
{
   vec3<T> res(x * v.x, y * v.y, z * v.z);
   return res;
}

template <typename T>
constexpr PHS_INLINE vec3<T> vec3<T>::operator/(const vec3<T>& v) const
{
   vec2<T> res(x / v.x, y / v.y, z / v.z);
   return res;
}

template <typename T>
constexpr PHS_INLINE bool vec3<T>::operator==(const vec3<T>& v) const PHS_MATH_NOEXCEPT
{
   return x == v.x and y == v.y and z == v.z;
}

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec3<T>& v)
{
   static constexpr std::string_view vt_str = is_real<T> ? "vec3f" : "vec3i";
   return out << vt_str << '(' << v.x << ',' << v.y << ',' << v.z << ')';
}

template <typename T>
constexpr PHS_INLINE T dot(const vec3<T>& a, const vec3<T>& b) PHS_MATH_NOEXCEPT
{
   const T sum = a.x * b.x + a.y * b.y + a.z * b.z;
   return sum;
}

template <typename T>
constexpr PHS_INLINE vec3<T> cross(const vec3<T>& a, const vec3<T>& b) PHS_MATH_NOEXCEPT
{
   vec3<T> res;
   res.x = a.y * b.z - a.z * b.y;
   res.y = b.x * a.z - b.z * a.x;
   res.z = a.x * b.y - a.y * b.x;
   return res;
}

template <typename T>
constexpr PHS_INLINE bool approxEqual(const vec3<T>& a, const vec3<T>& b) PHS_MATH_NOEXCEPT
{
   if constexpr (is_integral<T>)
      return a == b;

   return approxEqual64f(a.x, b.x) and
          approxEqual64f(a.y, b.y) and
          approxEqual64f(a.z, b.z);
}

} // namespace Phs
