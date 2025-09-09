#pragma once

#include "vec2.h"
#include "precompile.h"
#include "simd/simd.h"

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
   if constexpr (_Integral)
      return *this;

#ifdef PHS_SIMD_SSE4_1
   _mm_store_ps((float32_t*)this, _mm_round_ps(_mm_load_ps((float32_t*)this),
                                               _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
#else
   if constexpr (_Real)
   {
      x = round64f(x);
      y = round64f(y);
      z = round64f(z);
      w = round64f(w);
      return *this;
   }
#endif

   return *this;
}

template <typename T>
constexpr PHS_INLINE float32_t vec4<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   const float64_t len = dot(*this, *this);
   return len;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator+(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_add_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&v)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_add_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&v)));
   }
#else
   res = vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
#endif

   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator-(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_sub_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&v)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_sub_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&v)));
   }
#else
   res = vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
#endif

   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   vec4<T> res;

#ifdef PHS_SIMD_SSE4_1
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_mul_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps1((float32_t*)&s)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_mul_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si32((void*)&s)));
   }
#else
   res = vec4<T>(s * x, s * y, s * z, s * w);
#endif

   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator/(T s) const
{
   vec4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_div_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps1((float32_t*)&s)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_div_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si32((void*)&s)));
   }
#else
   res = vec4<T>(x / s, y / s, z / s, w / s);
#endif

   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator*(const vec4<T>& v) const PHS_MATH_NOEXCEPT
{
   vec4<T> res;

#ifdef PHS_SIMD_SSE4_1
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_mul_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&v)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_mul_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&v)));
   }
#else
   res = vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
#endif

   return res;
}

template <typename T>
constexpr PHS_INLINE vec4<T> vec4<T>::operator/(const vec4<T>& v) const
{
   vec4<T> res;
   
#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_div_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&v)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_div_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&v)));
   }
#else
   res = vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
#endif

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
   T sum;

#ifdef PHS_SIMD_SSE4_1
   if constexpr (is_real<T>)
   {
      sum = _mm_cvtss_f32(_mm_dp_ps(_mm_load_ps((float32_t*)&a),
                                    _mm_load_ps((float32_t*)&b),
                                                0xF1));
      return sum;
   }
#endif

   sum = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
   return sum;
}


} // namespace Phs
