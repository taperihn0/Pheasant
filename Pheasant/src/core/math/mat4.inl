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
PHS_NODISCARD constexpr PHS_INLINE mat4<T> mat4<T>::operator+(const mat4<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat4<T> res(_m[0] + m._m[0], _m[1] + m._m[1], _m[2] + m._m[2], _m[3] + m._m[3]);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat4<T> mat4<T>::operator-(const mat4<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat4<T> res(_m[0] - m._m[0], _m[1] - m._m[1], _m[2] - m._m[2], _m[3] - m._m[3]);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat4<T> mat4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   const mat4<T> res(_m[0] * s, _m[1] * s, _m[2] * s, _m[3] * s);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat4<T> mat4<T>::operator/(T s) const
{
   const mat4<T> res(_m[0] / s, _m[1] / s, _m[2] / s, _m[3] / s);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat4<T> mat4<T>::operator*(const mat4<T>& m) const PHS_MATH_NOEXCEPT
{
   mat4<T> res;

#ifdef PHS_SIMD_SSE4_1
   __m128 ps3ra[4];
   ps3ra[0] = _mm_load_ps((float32_t*)&_m[0]);
   ps3ra[1] = _mm_load_ps((float32_t*)&_m[1]);
   ps3ra[2] = _mm_load_ps((float32_t*)&_m[2]);
   ps3ra[3] = _mm_load_ps((float32_t*)&_m[3]);

   __m128 ps3cb[4];
   ps3cb[0] = _mm_setr_ps(m[0].x, m[1].x, m[2].x, m[3].x);
   ps3cb[1] = _mm_setr_ps(m[0].y, m[1].y, m[2].y, m[3].y);
   ps3cb[2] = _mm_setr_ps(m[0].z, m[1].z, m[2].z, m[3].z);
   ps3cb[3] = _mm_setr_ps(m[0].w, m[1].w, m[2].w, m[3].w);

   for (UINT j = 0; j < _Rows; j++) 
   {
      for (UINT i = 0; i < _Cols; i++) 
      {
         m.rc[j][i] = _mm_cvtss_f32(_mm_dp_ps(ps3ra[j],
                                              ps3cb[i],
                                              0xF1));
      }
   }
#else
   for (uint i = 0; i < _Rows; i++) 
   {
      for (uint j = 0; j < _Cols; j++) 
      {
         for (uint k = 0; k < _Rows; k++) 
         {
            res[j][i] += this[j][k] * m[k][i];
         }
      }
   }
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE vec4<T> mat4<T>::operator*(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   const vec4<T> res(dot(_m[0], v),
                     dot(_m[1], v),
                     dot(_m[2], v),
                     dot(_m[3], v));
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE bool mat4<T>::operator==(const mat4<T>& m) const PHS_MATH_NOEXCEPT
{
   return _m[0] == m._m[0] and _m[1] == m._m[1] and _m[2] == m._m[2] and _m[3] == m._m[3];
}

} // namespace Phs
