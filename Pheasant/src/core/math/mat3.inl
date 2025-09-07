#pragma once

#include "mat3.h"

namespace Phs
{

template <typename T>
constexpr PHS_INLINE mat3<T>::mat() PHS_MATH_NOEXCEPT
   : _m{}
{}

template <typename T>
constexpr PHS_INLINE mat3<T>::mat(const vec3<T>& r1, 
                                  const vec3<T>& r2,
                                  const vec3<T>& r3) PHS_MATH_NOEXCEPT
   : _m{ r1, r2, r3 }
{}

template <typename T>
constexpr PHS_INLINE mat3<T>::mat(T s) PHS_MATH_NOEXCEPT
   : _m{ vec3<T>{ s,      __Zero, __Zero } ,
         vec3<T>{ __Zero, s,      __Zero } ,
         vec3<T>{ __Zero, __Zero, s      } }
{}

template <typename T>
constexpr PHS_INLINE mat3<T>::mat(T s00, T s01, T s02,
                                  T s10, T s11, T s12,
                                  T s20, T s21, T s22) PHS_MATH_NOEXCEPT
   : _m{ vec3<T>{ s00, s01, s02 } ,
         vec3<T>{ s10, s11, s12 } ,
         vec3<T>{ s20, s21, s22 } }
{}

template <typename T>
constexpr PHS_INLINE mat3<T>& mat3<T>::operator=(const mat3<T>& m) PHS_MATH_NOEXCEPT
{
   _m[0] = m._m[0];
   _m[1] = m._m[1];
   _m[2] = m._m[2];
   return *this;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat3<T> mat3<T>::operator+(const mat3<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat3<T> res(_m[0] + m._m[0], _m[1] + m._m[1], _m[2] + m._m[2]);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat3<T> mat3<T>::operator-(const mat3<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat3<T> res(_m[0] - m._m[0], _m[1] - m._m[1], _m[2] - m._m[2]);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat3<T> mat3<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   const mat3<T> res(_m[0] * s, _m[1] * s, _m[2] * s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat3<T> mat3<T>::operator/(T s) const
{
   const mat3<T> res(_m[0] / s, _m[1] / s, _m[2] / s);
   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD mat3<T> mat3<T>::operator*(const mat3<T>& m) const PHS_MATH_NOEXCEPT
{
   mat3<T> res;

   for (uint i = 0; i < _Rows; i++) {
      for (uint j = 0; j < _Cols; j++) {
         for (uint k = 0; k < _Rows; k++) {
            res[j][i] += this[j][k] * m[k][i];
         }
      }
   }

   return res;
}

template <typename T>
constexpr PHS_INLINE PHS_NODISCARD bool mat3<T>::operator==(const mat3<T>& m) const PHS_MATH_NOEXCEPT
{
   return _m[0] == m._m[0] and _m[1] == m._m[1] and _m[2] == m._m[2];
}

} // namespace Phs
