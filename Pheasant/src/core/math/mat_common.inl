#pragma once

#include "mat_common.h"
#include "mat2.h"
#include "mat3.h"

namespace Phs
{

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr matbase<Rows, Cols, T>::matbase() PHS_MATH_NOEXCEPT
{
   NONE_TOKEN;
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::__asDerived(matbase<Rows, Cols, T>& self)
{
   return static_cast<mat<Rows, Cols, T>&>(self);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE const mat<Rows, Cols, T>& matbase<Rows, Cols, T>::__asDerived(const matbase<Rows, Cols, T>& self) const
{
   return static_cast<const mat<Rows, Cols, T>&>(self);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_NODISCARD uint matbase<Rows, Cols, T>::rows() PHS_MATH_NOEXCEPT
{
   return Rows;
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE PHS_NODISCARD uint matbase<Rows, Cols, T>::cols() PHS_MATH_NOEXCEPT
{
   return Cols;
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
template <dim_int_t CastRows, dim_int_t CastCols, typename CastT>
constexpr PHS_INLINE PHS_NODISCARD matbase<Rows, Cols, T>::operator mat<CastRows, CastCols, CastT>()
{
   const mat<Rows, Cols, T>& self = __asDerived(*this);
   mat<CastRows, CastCols, CastT> res;

   for (dim_int_t r = 0; r < CastRows and r < Rows; ++r)
   {
      for (dim_int_t c = 0; c < CastCols and c < Cols; ++c)
      {
         res[r][c] = static_cast<CastT>(self[r][c]);
      }
   }

   return res;
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::operator+=(const mat<Rows, Cols, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) + m;
   return __asDerived(*this);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::operator-=(const mat<Rows, Cols, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) - m:
   return __asDerived(*this);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::operator*=(T s) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * s;
   return __asDerived(*this);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::operator/=(T s)
{
   __asDerived(*this) = __asDerived(*this) / s;
   return __asDerived(*this);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE mat<Rows, Cols, T>& matbase<Rows, Cols, T>::operator*=(const mat<Rows, Cols, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * m;
   return __asDerived(*this);
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE PHS_NODISCARD vec<Cols, T>& matbase<Rows, Cols, T>::operator[](size_t i) PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Rows);
   return __asDerived(*this)._m[i];
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE PHS_NODISCARD const vec<Cols, T>& matbase<Rows, Cols, T>::operator[](size_t i) const PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Rows);
   return __asDerived(*this)._m[i];
}

template <dim_int_t Rows, dim_int_t Cols, typename T>
constexpr PHS_INLINE PHS_NODISCARD bool matbase<Rows, Cols, T>::operator!=(const mat<Rows, Cols, T>& m) const PHS_MATH_NOEXCEPT
{
   return !(__asDerived(*this) == m);
}

} // namespace Phs
