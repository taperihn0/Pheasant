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
   : _m{ vec2<T>{ s,      __Zero } ,
         vec2<T>{ __Zero, s      } }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>::mat(T s00, T s01, T s10, T s11) PHS_MATH_NOEXCEPT
   : _m{ vec2<T>{ s00, s01 } ,
         vec2<T>{ s10, s11 } }
{}

template <typename T>
constexpr PHS_INLINE mat2<T>& mat2<T>::operator=(const mat2<T>& m) PHS_MATH_NOEXCEPT
{
   _m[0] = m._m[0];
   _m[1] = m._m[1];
   return *this;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat2<T> mat2<T>::operator+(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] + m._m[0], _m[1] + m._m[1]);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat2<T> mat2<T>::operator-(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] - m._m[0], _m[1] - m._m[1]);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat2<T> mat2<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   const mat2<T> res(_m[0] * s, _m[1] * s);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat2<T> mat2<T>::operator/(T s) const
{
   const mat2<T> res(_m[0] / s, _m[1] / s);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE mat2<T> mat2<T>::operator*(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   mat2<T> res;

#ifdef PHS_SIMD_SSE4_1
   __m128 ps4a = _mm_load_ps((float32_t*)this);
   __m128 ps4b = _mm_setr_ps(m[0].x, m[1].x, m[0].y, m[1].y);
   __m128 ps4br= _mm_setr_ps(m[0].y, m[1].y, m[0].x, m[1].x);

   res[0].x = _mm_cvtss_f32(_mm_dp_ps(ps4a, ps4b, 0x21));
   res[1].y = _mm_cvtss_f32(_mm_dp_ps(ps4a, ps4b, 0xC1));
   res[0].y = _mm_cvtss_f32(_mm_dp_ps(ps4a, ps4br, 0x21));
   res[1].x = _mm_cvtss_f32(_mm_dp_ps(ps4a, ps4br, 0xC1));
#else
   res = mat2<T>(_m[0].x * m._m[0].x + _m[0].y * m._m[1].x,
                 _m[0].x * m._m[0].y + _m[0].y * m._m[1].y,
                 _m[1].x * m._m[0].x + _m[1].y * m._m[1].x,
                 _m[1].x * m._m[0].y + _m[1].y * m._m[1].y);
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE vec2<T> mat2<T>::operator*(const vec2<T>& v) const PHS_MATH_NOEXCEPT
{
   const vec2<T> res(_m[0].x * v.x + _m[0].y * v.y,
                     _m[1].x * v.x + _m[1].y * v.y);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE bool mat2<T>::operator==(const mat2<T>& m) const PHS_MATH_NOEXCEPT
{
   return _m[0] == m._m[0] and _m[1] == m._m[1];
}

} // namespace Phs
