#pragma once

#include "common.h"
#include "types.h"
#include "mat_common.h"
#include "assert.h"
#include "vec3.h"

namespace Phs
{

template <typename T>
struct mat<3, 3, T> : public matbase<3, 3, T>
{
   friend struct matbase<3, 3, T>;

   static constexpr T __Zero = static_cast<T>(0);

   constexpr PHS_INLINE                        mat()                              PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        mat(const vec3<T>& r1, 
                                                   const vec3<T>& r2, 
                                                   const vec3<T>& r3)             PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit               mat(T s)                           PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                        mat(T s00, T s01, T s02,
                                                   T s10, T s11, T s12, 
                                                   T s20, T s21, T s22)           PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE mat3<T>&               operator=(const mat3<T>& m)        PHS_MATH_NOEXCEPT;
                                                                     
   PHS_NODISCARD constexpr PHS_INLINE mat3<T>  operator+(const mat3<T>& m)  const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE mat3<T>  operator-(const mat3<T>& m)  const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE mat3<T>  operator*(T s)               const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE mat3<T>  operator/(T s)               const;
   PHS_NODISCARD constexpr PHS_INLINE mat3<T>  operator*(const mat3<T>& m)  const PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE vec3<T>  operator*(const vec3<T>& v)  const PHS_MATH_NOEXCEPT;

   PHS_NODISCARD constexpr PHS_INLINE bool     operator==(const mat3<T>& m) const PHS_MATH_NOEXCEPT;

private:
   static constexpr dim_int_t _Rows = 3;
   static constexpr dim_int_t _Cols = 3;
   vec3<T>                    _m[_Rows];
};

using mat3f = mat3<float32_t>;
using mat3i = mat3<int32_t>;

} // namespace Phs

#include "mat3.inl"
