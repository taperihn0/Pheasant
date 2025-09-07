#pragma once

#include "quaternion.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE quat4<T>::quat() PHS_MATH_NOEXCEPT
   : x(__Zero)
   , y(__Zero)
   , z(__Zero)
   , w(__Zero)
{}

template <typename T>
constexpr PHS_INLINE quat4<T>::quat(T w) PHS_MATH_NOEXCEPT
   : x(__Zero)
   , y(__Zero)
   , z(__Zero)
   , w(w)
{}

template <typename T>
constexpr PHS_INLINE quat4<T>::quat(T x, T y, T z, T w) PHS_MATH_NOEXCEPT
   : x(x)
   , y(y)
   , z(z)
   , w(w)
{}

template <typename T>
constexpr PHS_INLINE quat4<T>::quat(const vec4<T>& q) PHS_MATH_NOEXCEPT
   : x(q.x)
   , y(q.y)
   , z(q.z)
   , w(q.w)
{}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::quatwxyz(T w, T x, T y, T z) PHS_MATH_NOEXCEPT
{
   const quat4<T> res(x, y, z, w);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T>& quat4<T>::inversed() const
{
   const float64_t lensq = lengthSquared();
   const quat4<T> res = conjugated() / lensq;
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T>& quat4<T>::inverse()
{
   const quat4<T> inv = inversed();
   *this = inv;
   return inv;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T>& quat4<T>::conjugated() const PHS_MATH_NOEXCEPT
{
   const quat4<T> res = quatwxyz(w, -x, -y, -z);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T>& quat4<T>::conjugate()
{
   const quat4<T> cnj = conjugated();
   *this = cnj;
   return cnj;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD float64_t quat4<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   return sq(x) + sq(y) + sq(z) + sq(w);
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator+(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   const quat4<T> res(x + q.x, y + q.y, z + q.z, w + q.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator-(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   const quat4<T> res(x - q.x, y - q.y, z - q.z, w - q.w);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   const quat4<T> res(x * s, y * s, z * s, w * s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator/(T s) const
{
   const quat4<T> res(x / s, y / s, z / s, w / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator*(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   const quat4<T> res(
       x * q.w +
       y * q.z -
       z * q.y +
       w * q.x
       ,
      -x * q.z +
       y * q.w +
       z * q.x +
       w * q.y
       ,    
       x * q.y -
       y * q.x +
       z * q.w +
       w * q.z
       ,    
      -x * q.x -
       y * q.y -
       z * q.z +
       w * q.w
   );
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD quat4<T> quat4<T>::operator/(const quat4<T>& q) const
{
   const quat4<T> res;
   res = *this * q.inversed();
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD bool quat4<T>::operator==(const vec4<T>& q) const PHS_MATH_NOEXCEPT
{
   return x == q.x and y == q.y and z == q.z and w == q.w;
}

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const quat4<T>& v)
{
   static constexpr std::string_view vt_str = is_real<T> ? "quat4f" : "quat4i";
   return out << vt_str << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
}

template <typename T>
constexpr PHS_INLINE T dot(const quat4<T>& q0, const quat4<T>& q1) PHS_MATH_NOEXCEPT
{
   const T sum = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
   return sum;
}

template <typename T>
constexpr PHS_INLINE vec3<T> rotate(const vec3<T>& v, const quat4<T>& q)
{
   vec4<T> v4 = v;
   v4 = q * v4 * q.inversed();
   return static_cast<vec3<T>>(v4);
}

} // namespace Phs
