#pragma once

#include "common.h"
#include "types.h"
#include "mat_common.h"
#include "assert.h"
#include "vec3.h"

namespace Phs
{

template <typename T>
struct mat<4, 4, T> : public matbase<4, 4, T>
{
   friend struct matbase<4, 4, T>;

   static constexpr T __Zero = static_cast<T>(0);

   constexpr PHS_INLINE                        mat()                              PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        mat(const vec4<T>& r1,
                                                   const vec4<T>& r2,
                                                   const vec4<T>& r3,
                                                   const vec4<T>& r4)             PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit               mat(T s)                           PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        mat(T s00, T s01, T s02, T s03,
                                                   T s10, T s11, T s12, T s13,
                                                   T s20, T s21, T s22, T s23,
                                                   T s30, T s31, T s32, T s33)    PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE mat4<T>&               operator=(const mat4<T>& m)        PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD mat4<T>  operator+(const mat4<T>& m)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat4<T>  operator-(const mat4<T>& m)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat4<T>  operator*(T s)               const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat4<T>  operator/(T s)               const;
   constexpr PHS_INLINE PHS_NODISCARD mat4<T>  operator*(const mat4<T>& m)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec4<T>  operator*(const vec4<T>& v)  const PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD bool     operator==(const mat4<T>& m) const PHS_MATH_NOEXCEPT;

private:
   static constexpr dim_int_t _Rows = 4;
   static constexpr dim_int_t _Cols = 4;
   vec4<T>                    _m[_Rows];
};

using mat4f = mat4<float32_t>;
using mat4i = mat4<int32_t>;

} // namespace Phs

#include "mat4.inl"
