#pragma once

#include "mat2.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE mat2<T>::mat() PHS_MATH_NOEXCEPT
   : _m{}
{}

template <typename T>
constexpr PHS_INLINE mat2<T>::mat(const mat2<T>& m) PHS_MATH_NOEXCEPT
   : _m{ m._m[0], m._m[1] }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>::mat(const vec2<T>& r1, 
                                  const vec2<T>& r2) PHS_MATH_NOEXCEPT
   : _m{ r1, r2 }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>::mat(T s) PHS_MATH_NOEXCEPT
   : _m{ { s,                 static_cast<T>(0) } ,
         { static_cast<T>(0), s                 } }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>::mat(T s00, T s01, T s10, T s11) PHS_MATH_NOEXCEPT
   : _m{ { s00, s01 } ,
         { s10, s11 } }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>& mat2<T>::operator=(const mat2<T>& m) PHS_MATH_NOEXCEPT
{
   _m[0] = m._m[0];
   _m[1] = m._m[1];
   return *this;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat2<T> mat2<T>::operator+(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] + m._m[0], _m[1] + m._m[1]);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat2<T> mat2<T>::operator-(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] - m._m[0], _m[1] - m._m[1]);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat2<T> mat2<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] * s, _m[1] * s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat2<T> mat2<T>::operator/(T s) const
{
   const mat2<T> res(_m[0] / s, _m[1] / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat2<T> mat2<T>::operator*(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0].x * m._m[0].x + _m[0].y * m._m[1].x,
                     _m[0].x * m._m[0].y + _m[0].y * m._m[1].y,
                     _m[1].x * m._m[0].x + _m[1].y * m._m[1].x,
                     _m[1].x * m._m[0].y + _m[1].y * m._m[1].y);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD bool mat2<T>::operator==(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   return _m[0] == m._m[0] and _m[1] == m._m[1];
}

} // namespace Phs
