#pragma once

#include "vec_common.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "math_utils.h"

namespace Phs
{

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr vecbase<Dimension, T, Derived>::vecbase() PHS_MATH_NOEXCEPT 
{
   NONE_TOKEN;
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::__asDerived(vecbase<Dimension, T, Derived>& self)
{
   return static_cast<Derived<Dimension, T>&>(self);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE const Derived<Dimension, T>& vecbase<Dimension, T, Derived>::__asDerived(const vecbase<Dimension, T, Derived>& self) const
{
   return static_cast<const Derived<Dimension, T>&>(self);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_NODISCARD uint vecbase<Dimension, T, Derived>::dim() PHS_MATH_NOEXCEPT
{
   return Dimension;
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE PHS_NODISCARD float64_t vecbase<Dimension, T, Derived>::length() const
{
   return sqrt<float64_t>(__asDerived(*this).lengthSquared());
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T> vecbase<Dimension, T, Derived>::normalized() const
{
   const float64_t len = __asDerived(*this).length();
   const Derived<Dimension, T> res = __asDerived(*this) / len;
   return res;
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::normalize()
{
   __asDerived(*this) = normalized();
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator+=(const Derived<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) + m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator-=(const Derived<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) - m:
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator*=(T s) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * s;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator/=(T s)
{
   __asDerived(*this) = __asDerived(*this) / s;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator*=(const Derived<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) * m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE Derived<Dimension, T>& vecbase<Dimension, T, Derived>::operator/=(const Derived<Dimension, T>& m) PHS_MATH_NOEXCEPT
{
   __asDerived(*this) = __asDerived(*this) / m;
   return __asDerived(*this);
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE PHS_NODISCARD T& vecbase<Dimension, T, Derived>::operator[](size_t i) PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Dimension);
   T* addres = &(__asDerived(*this).x);
   return addres[i];
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE PHS_NODISCARD const T& vecbase<Dimension, T, Derived>::operator[](size_t i) const PHS_MATH_NOEXCEPT
{
   PHS_ASSERT(i < Dimension);
   const T* addres = &(__asDerived(*this).x);
   return addres[i];
}

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived>
constexpr PHS_INLINE PHS_NODISCARD bool vecbase<Dimension, T, Derived>::operator!=(const Derived<Dimension, T>& m) const PHS_MATH_NOEXCEPT
{
   return !(__asDerived(*this) == m);
}

} // namespace Phs
