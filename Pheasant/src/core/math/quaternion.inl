#pragma once

#include "quaternion.h"
#include "simd/simd.h"

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
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::quatwxyz(T w, T x, T y, T z) PHS_MATH_NOEXCEPT
{
   const quat4<T> res(x, y, z, w);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::inversed() const
{
   const float64_t lensq = lengthSquared();
   quat4<T> res = conjugated() / lensq;
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::inverse()
{
   quat4<T> inv = inversed();
   *this = inv;
   return inv;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::conjugated() const PHS_MATH_NOEXCEPT
{
   quat4<T> res = quatwxyz(w, -x, -y, -z);
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::conjugate()
{
   quat4<T> cnj = conjugated();
   *this = cnj;
   return cnj;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE float64_t quat4<T>::lengthSquared() const PHS_MATH_NOEXCEPT
{
   const float64_t len = dot(*this, *this);
   return len;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator+(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   quat4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_add_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&q)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_add_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&q)));
   }
#else
   res = quat4<T>(x + q.x, y + q.y, z + q.z, w + q.w);
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator-(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   quat4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      _mm_store_ps((float32_t*)&res, _mm_sub_ps(_mm_load_ps((float32_t*)&res),
                                                _mm_load_ps((float32_t*)&q)));
   }
   if constexpr (_Integral)
   {
      _mm_storeu_si128((void*)&res, _mm_sub_epi32(_mm_loadu_si128((void*)&res),
                                                  _mm_loadu_si128((void*)&q)));
   }
#else
   res = quat4<T>(x - q.x, y - q.y, z - q.z, w - q.w);
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator*(T s) const PHS_MATH_NOEXCEPT
{
   quat4<T> res;

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
   res = quat4<T>(x * s, y * s, z * s, w * s);
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator/(T s) const
{
   quat4<T> res;

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
   res = quat4<T>(x / s, y / s, z / s, w / s);
#endif

   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator*(const quat4<T>& q) const PHS_MATH_NOEXCEPT
{
   quat4<T> res;

#ifdef PHS_SIMD_SSE2
   if constexpr (_Real)
   {
      // https://stackoverflow.com/questions/22215217/why-is-my-straightforward-quaternion-multiplication-faster-than-sse
      __m128 a = _mm_load_ps((float32_t*)this);
      __m128 b = _mm_load_ps((float32_t*)&q);
      __m128 a1123 = _mm_shuffle_ps(a, a, 0xE5);
      __m128 a2231 = _mm_shuffle_ps(a, a, 0x7A);
      __m128 b1000 = _mm_shuffle_ps(b, b, 0x01);
      __m128 b2312 = _mm_shuffle_ps(b, b, 0x9E);
      __m128 t1 = _mm_mul_ps(a1123, b1000);
      __m128 t2 = _mm_mul_ps(a2231, b2312);
      __m128 t12 = _mm_add_ps(t1, t2);
      const __m128i mask = _mm_set_epi32(0, 0, 0, 0x80000000);
      __m128 t12m = _mm_xor_ps(t12, _mm_castsi128_ps(mask));
      __m128 a3312 = _mm_shuffle_ps(a, a, 0x9F);
      __m128 b3231 = _mm_shuffle_ps(b, b, 0x7B);
      __m128 a0000 = _mm_shuffle_ps(a, a, 0x00);
      __m128 t3 = _mm_mul_ps(a3312, b3231);
      __m128 t0 = _mm_mul_ps(a0000, b);
      __m128 t03 = _mm_sub_ps(t0, t3);
      _mm_store_ps((float32_t*)&res, _mm_add_ps(t03, t12m));
      return res;
   }
   if constexpr (_Integral)
      // TODO
      ;
#endif
   res = quat4<T>(
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
PHS_NODISCARD constexpr PHS_INLINE quat4<T> quat4<T>::operator/(const quat4<T>& q) const
{
   quat4<T> res;
   res = *this * q.inversed();
   return res;
}

template <typename T>
PHS_NODISCARD constexpr PHS_INLINE bool quat4<T>::operator==(const vec4<T>& q) const PHS_MATH_NOEXCEPT
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
   T sum;

#ifdef PHS_SIMD_SSE4_1
   if constexpr (is_real<T>)
   {
      sum = _mm_cvtss_f32(_mm_dp_ps(_mm_load_ps((float32_t*)&q0),
                                    _mm_load_ps((float32_t*)&q1),
                                                0xF1));
      return sum;
   }
#endif

   sum = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
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
