#pragma once

#include "vec_common.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

namespace Phs
{

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::__asDerived(vecbase<Dimension, T>& self)
{
   return static_cast<vec<Dimension, T>&>(self);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE const vec<Dimension, T>& vecbase<Dimension, T>::__asDerived(const vecbase<Dimension, T>& self) const
{
   return static_cast<const vec<Dimension, T>&>(self);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_NODISCARD uint vecbase<Dimension, T>::dim() PHS_MATH_NOEXCEPT
{
   return Dimension;
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator+=(const vec<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) + m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator-=(const vec<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) - m:
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator*=(T s) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * s;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator/=(T s)
{
   __asDerived(*this) = __asDerived(*this) / s;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator*=(const vec<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE vec<Dimension, T>& vecbase<Dimension, T>::operator/=(const vec<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) / m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE PHS_NODISCARD T& vecbase<Dimension, T>::operator[](size_t i) PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Dimension);
   T* addres = &(__asDerived(*this).x);
   return addres[i];
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE PHS_NODISCARD const T& vecbase<Dimension, T>::operator[](size_t i) const PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Dimension);
   const T* addres = &(__asDerived(*this).x);
   return addres[i];
}

template <dim_int_t Dimension, typename T>
constexpr PHS_INLINE PHS_NODISCARD bool vecbase<Dimension, T>::operator!=(const vec<Dimension, T>& m) const PHS_MATH_NOEXCEPT
{
   return !(__asDerived(*this) == m);
}

} // namespace Phs
