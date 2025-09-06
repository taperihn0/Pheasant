#pragma once

#include "math_utils.h"

namespace Phs
{

template <dim_int_t Dim, typename T>
struct vec;

template <typename T>
using vec2 = vec<2, T>;

template <typename T>
using vec3 = vec<3, T>;

template <typename T>
using vec4 = vec<4, T>;

template <dim_int_t Dimension, typename T>
struct vecbase
{
   PHS_STATIC_ASSERT_LOG(Dimension >= 2, "1-Dimensional vector is not supported!");
   PHS_STATIC_ASSERT_LOG(is_numeric<T>, "Can't create non-numeric vector!");

   static constexpr PHS_INLINE PHS_NODISCARD uint dim()                                           PHS_MATH_NOEXCEPT;
                                                                                                  
   constexpr PHS_INLINE vec<Dimension, T>&        operator+=(const vec<Dimension, T>& v)          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE vec<Dimension, T>&        operator-=(const vec<Dimension, T>& v)          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE vec<Dimension, T>&        operator*=(T s)                                 PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE vec<Dimension, T>&        operator/=(T s);                                
   constexpr PHS_INLINE vec<Dimension, T>&        operator*=(const vec<Dimension, T>& v)          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE vec<Dimension, T>&        operator/=(const vec<Dimension, T>& v)          PHS_MATH_NOEXCEPT;
                                                                                                  
   constexpr PHS_INLINE PHS_NODISCARD T&          operator[](size_t i)                            PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD const T&    operator[](size_t i)                      const PHS_MATH_NOEXCEPT;
                                                                                            
   constexpr PHS_INLINE PHS_NODISCARD bool        operator!=(const vec<Dimension, T>& m)    const PHS_MATH_NOEXCEPT;
private:
   constexpr PHS_INLINE vec<Dimension, T>&        __asDerived(vecbase<Dimension, T>& self);
   constexpr PHS_INLINE const vec<Dimension, T>&  __asDerived(const vecbase<Dimension, T>& self)  const;
};

} // namespace Phs

#include "vec_common.inl"
