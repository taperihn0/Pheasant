#pragma once

#include "mat4.h"

namespace Phs
{

   template <typename T>
   constexpr PHS_INLINE mat4<T>::mat() PHS_MATH_NOEXCEPT
      : _m{}
   {}

   template <typename T>
   constexpr PHS_INLINE mat4<T>::mat(const vec4<T>& r1,
                                     const vec4<T>& r2,
                                     const vec4<T>& r3,
                                     const vec4<T>& r4) PHS_MATH_NOEXCEPT
      : _m{ r1, r2, r3, r4 }
   {}

   template <typename T>
   constexpr PHS_INLINE mat4<T>::mat(T s) PHS_MATH_NOEXCEPT
      : _m{ vec4<T>{ s,      __Zero, __Zero, __Zero } ,
            vec4<T>{ __Zero, s,      __Zero, __Zero } ,
            vec4<T>{ __Zero, __Zero, s,      __Zero } ,
            vec4<T>{ __Zero, __Zero, __Zero, s      } }
   {}

   template <typename T>
   constexpr PHS_INLINE mat4<T>::mat(T s00, T s01, T s02, T s03,
                                     T s10, T s11, T s12, T s13,
                                     T s20, T s21, T s22, T s23,
                                     T s30, T s31, T s32, T s33) PHS_MATH_NOEXCEPT
      : _m{ vec4<T>{ s00, s01, s02, s03 } ,
            vec4<T>{ s10, s11, s12, s13 } ,
            vec4<T>{ s20, s21, s22, s23 } ,
            vec4<T>{ s30, s31, s32, s33 } }
   {}

   template <typename T>
   constexpr PHS_INLINE mat4<T>& mat4<T>::operator=(const mat4<T>& m) PHS_MATH_NOEXCEPT
   {
      _m[0] = m._m[0];
      _m[1] = m._m[1];
      _m[2] = m._m[2];
      _m[3] = m._m[3];
      return *this;
   }

   template <typename T>
   constexpr PHS_INLINE PHS_NODISCARD mat4<T> mat4<T>::operator+(const mat4<T>& m) const PHS_MATH_NOEXCEPT
   {
      const mat4<T> res(_m[0] + m._m[0], _m[1] + m._m[1], _m[2] + m._m[2], _m[3] + m._m[3]);
      return res;
   }

   template <typename T>
   constexpr PHS_INLINE PHS_NODISCARD mat4<T> mat4<T>::operator-(const mat4<T>& m) const PHS_MATH_NOEXCEPT
   {
      const mat4<T> res(_m[0] - m._m[0], _m[1] - m._m[1], _m[2] - m._m[2], _m[3] - m._m[3]);
      return res;
   }

   template <typename T>
   constexpr PHS_INLINE PHS_NODISCARD mat4<T> mat4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
   {
      const mat4<T> res(_m[0] * s, _m[1] * s, _m[2] * s, _m[3] * s);
      return res;
   }

   template <typename T>
   constexpr PHS_INLINE PHS_NODISCARD mat4<T> mat4<T>::operator/(T s) const
   {
      const mat4<T> res(_m[0] / s, _m[1] / s, _m[2] / s, _m[3] / s);
      return res;
   }

   template <typename T>
   constexpr PHS_INLINE PHS_NODISCARD mat4<T> mat4<T>::operator*(const mat4<T>& m) const PHS_MATH_NOEXCEPT
   {
      mat4<T> res;

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
   constexpr PHS_INLINE PHS_NODISCARD bool mat4<T>::operator==(const mat4<T>& m) const PHS_MATH_NOEXCEPT
   {
      return _m[0] == m._m[0] and _m[1] == m._m[1] and _m[2] == m._m[2] and _m[3] == m._m[3];
   }

} // namespace Phs
