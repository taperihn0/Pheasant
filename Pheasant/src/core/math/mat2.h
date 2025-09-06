#pragma once

#include "common.h"
#include "types.h"
#include "mat_common.h"
#include "assert.h"
#include "vec2.h"

namespace Phs
{

template <typename T>
struct mat<2, 2, T> : public matbase<2, 2, T>
{
   friend struct matbase<2, 2, T>;

   constexpr PHS_INLINE                       mat()                              PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                       mat(const mat2<T>& m)              PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                       mat(const vec2<T>& r1, 
                                                  const vec2<T>& r2)             PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit              mat(T s)                           PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE                       mat(T s00, T s01, T s10, T s11)    PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE mat2<T>&              operator=(const mat2<T>& m)        PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD mat2<T> operator+(const mat2<T>& m)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat2<T> operator-(const mat2<T>& m)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat2<T> operator*(T s)               const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD mat2<T> operator/(T s)               const;
   constexpr PHS_INLINE PHS_NODISCARD mat2<T> operator*(const mat2<T>& m)  const PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD bool    operator==(const mat2<T>& m) const PHS_MATH_NOEXCEPT;
private:
   static constexpr dim_int_t _Cols = 2;
   static constexpr dim_int_t _Rows = 2;
   vec<_Cols, T>              _m[_Rows];
};

using mat2f = mat2<float32_t>;
using mat2i = mat2<int32_t>;

} // namespace Phs

#include "mat2.inl"
