#pragma once

#include "common.h"
#include "types.h"
#include "vec_common.h"
#include "assert.h"

namespace Phs
{

template<typename T>
struct vec<4, T> : public vecbase<4, T>
{
   friend struct vecbase<4, T>;

   static constexpr T __Zero = static_cast<T>(0);

   constexpr PHS_INLINE                        vec()                              PHS_MATH_NOEXCEPT;

   template <dim_int_t Dim>
   constexpr PHS_INLINE explicit               vec(const vec<Dim, T>& v)          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit               vec(T s1         , T s2 = __Zero,
                                                   T s3 = __Zero, T s4 = __Zero)  PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD vec4<T>& round();

   constexpr PHS_INLINE PHS_NODISCARD vec4<T>& lengthSquared()              const PHS_MATH_NOEXCEPT;

   template <dim_int_t Dim>
   constexpr PHS_INLINE vec3<T>&               operator=(const vec<Dim, T>& v)    PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator+(const vec4<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator-(const vec4<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator*(T s)               const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator/(T s)               const;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator*(const vec4<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator/(const vec4<T>& v)  const;

   constexpr PHS_INLINE PHS_NODISCARD bool     operator==(const vec4<T>& v) const PHS_MATH_NOEXCEPT;

#if defined(PHS_EXTENSIONS) and defined(PHS_USE_ANONYMOUS_STRUCT)
   union
   {
      struct { T x, y, z, w; };
      struct { T s, t, p, q; };
      struct { T r, g, b, a; };
   };
#else
   union { T x, s, r; };
   union { T y, t, g; };
   union { T z, p, b; };
   union { T w, q, a; };
#endif
private:
   static constexpr dim_int_t _Dimension = 4;
};

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec4<T>& v);

template <typename T>
constexpr PHS_INLINE T dot(const vec4<T>& a, const vec4<T>& b) PHS_MATH_NOEXCEPT;

using vec4f = vec4<float32_t>;
using vec4i = vec4<int32_t>;

} // namespace Phs

#include "vec4.inl"
