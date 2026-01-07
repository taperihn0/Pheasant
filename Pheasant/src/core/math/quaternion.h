#pragma once

#include "vec_common.h"

namespace Phs
{

template <typename T>
struct PHS_ALIGN(16) quat<4, T> : vecbase<4, T, quat>
{
   friend struct vecbase<4, T>;

   static constexpr T __Zero = static_cast<T>(0);

   constexpr PHS_INLINE                               quat()                             PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit                      quat(T w)                          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                               quat(T x, T y, 
                                                           T z = __Zero, T w = __Zero)   PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit                      quat(const vec4<T>& q)             PHS_MATH_NOEXCEPT;

   PHS_NODISCARD static constexpr PHS_INLINE quat4<T> quatwxyz(T w, T x, T y, T z)       PHS_MATH_NOEXCEPT;

   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        inversed()                   const;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        inverse();
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        conjugated()                 const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        conjugate();

   PHS_NODISCARD constexpr PHS_INLINE float64_t       lengthSquared()              const PHS_MATH_NOEXCEPT;

   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator+(const quat4<T>& q) const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator-(const quat4<T>& q) const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator*(T s)               const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator/(T s)               const;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator*(const quat4<T>& q) const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE quat4<T>        operator/(const quat4<T>& q) const;
                                                      
   PHS_NODISCARD constexpr PHS_INLINE bool            operator==(const vec4<T>& q) const PHS_MATH_NOEXCEPT;

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
   static constexpr bool      _Real = is_real<T>;
   static constexpr bool      _Integral = is_integral<T>;
};

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const quat4<T>& v);

template <typename T>
constexpr PHS_INLINE T dot(const quat4<T>& q0, const quat4<T>& q1) PHS_MATH_NOEXCEPT;

template <typename T>
constexpr PHS_INLINE vec3<T> rotate(const vec3<T>& v, const quat4<T>& q);

using quat4f = quat4<float32_t>;
using quat4i = quat4<uint32_t>;

} // namespace Phs

#include "quaternion.inl"
