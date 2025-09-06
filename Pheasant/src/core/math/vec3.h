#pragma once

#include "common.h"
#include "types.h"
#include "vec_common.h"
#include "assert.h"

namespace Phs
{

template<typename T>
struct vec<3, T> : public vecbase<3, T>
{
   friend struct vecbase<3, T>;

   constexpr PHS_INLINE                        vec()                              PHS_MATH_NOEXCEPT;

   template <dim_int_t Dim>
   constexpr PHS_INLINE                        vec(const vec<Dim, T>& v)          PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE explicit               vec(T s)                           PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        vec(T s1, T s2)                    PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        vec(T s1, T s2, T s3)              PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD vec3<T>& normalize();
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>& round();

   constexpr PHS_INLINE PHS_NODISCARD vec3<T>& lengthSquared()              const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>& length()                     const PHS_MATH_NOEXCEPT;

   template <dim_int_t Dim>
   constexpr PHS_INLINE vec3<T>&               operator=(const vec<Dim, T>& v)    PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator+(const vec3<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator-(const vec3<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator*(T s)               const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator/(T s)               const;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator*(const vec3<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec3<T>  operator/(const vec3<T>& v)  const;

   constexpr PHS_INLINE PHS_NODISCARD bool     operator==(const vec3<T>& v) const PHS_MATH_NOEXCEPT;

#if defined(PHS_EXTENSIONS) and defined(PHS_USE_ANONYMOUS_STRUCT)
   union
   {
      struct { T x, y, z; };
      struct { T s, t, p; };
      struct { T r, g, b; };
   };
#else
   union
   {
      T x, s, r;
   };
   union
   {
      T y, t, g;
   };
   union
   {
      T z, p, b;
   };
#endif
private:
   static constexpr dim_int_t _Dimension = 3;
};

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec3<T>& v);

template <typename T>
constexpr PHS_INLINE T dot(const vec3<T>& a, const vec3<T>& b) PHS_MATH_NOEXCEPT;

template <typename T>
constexpr PHS_INLINE vec3<T> cross(const vec3<T>& a, const vec3<T>& b) PHS_MATH_NOEXCEPT;

using vec3f = vec3<float32_t>;
using vec3i = vec3<int32_t>;

} // namespace Phs

#include "vec3.inl"
