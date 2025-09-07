#pragma once

#include "math_utils.h"

namespace Phs
{

template <dim_int_t Rows, dim_int_t Cols, typename T>
struct mat;

template <typename T>
using mat2 = mat<2, 2, T>;

template <typename T>
using mat3 = mat<3, 3, T>;

template <typename T>
using mat4 = mat<4, 4, T>;

template <dim_int_t Rows, dim_int_t Cols, typename T>
struct matbase
{
   PHS_STATIC_ASSERT_LOG(Rows >= 2 and Cols >= 2, "1x1 matrix is not supported!");
   PHS_STATIC_ASSERT_LOG(is_numeric<T>, "Only numeric types in matrix are allowed!");

   constexpr                                              matbase()                                      PHS_MATH_NOEXCEPT;

   static constexpr PHS_INLINE PHS_NODISCARD uint         rows()                                         PHS_MATH_NOEXCEPT;
   static constexpr PHS_INLINE PHS_NODISCARD uint         cols()                                         PHS_MATH_NOEXCEPT;

   template <dim_int_t CastRows, dim_int_t CastCols, typename CastT>
   constexpr PHS_INLINE PHS_NODISCARD explicit            operator mat<CastRows, CastCols, CastT>();

   constexpr PHS_INLINE mat<Rows, Cols, T>&               operator+=(const mat<Rows, Cols, T>& v)        PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE mat<Rows, Cols, T>&               operator-=(const mat<Rows, Cols, T>& v)        PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE mat<Rows, Cols, T>&               operator*=(T s)                                PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE mat<Rows, Cols, T>&               operator/=(T s);                               
   constexpr PHS_INLINE mat<Rows, Cols, T>&               operator*=(const mat<Rows, Cols, T>& v)        PHS_MATH_NOEXCEPT;
                                                                                                         
   constexpr PHS_INLINE PHS_NODISCARD vec<Cols, T>&       operator[](size_t i)                           PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD const vec<Cols, T>& operator[](size_t i)                     const PHS_MATH_NOEXCEPT;

   constexpr PHS_INLINE PHS_NODISCARD bool                operator!=(const mat<Rows, Cols, T>& m)  const PHS_MATH_NOEXCEPT;
private:
   constexpr PHS_INLINE mat<Rows, Cols, T>&               __asDerived(matbase<Rows, Cols, T>& self);
   constexpr PHS_INLINE const mat<Rows, Cols, T>&         __asDerived(const matbase<Rows, Cols, T>& self) const;
};

} // namespace Phs

#include "mat_common.inl"
