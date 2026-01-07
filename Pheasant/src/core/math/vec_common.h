#pragma once

#include "math_utils.h"

namespace Phs
{

template <dim_int_t Dim, typename T>
struct vec;

template <dim_int_t Dim, typename T>
struct quat;

template <typename T>
using vec2 = vec<2, T>;

template <typename T>
using vec3 = vec<3, T>;

template <typename T>
using vec4 = vec<4, T>;

template <typename T>
using quat4 = quat<4, T>;

template <dim_int_t Dimension, typename T, template <dim_int_t, typename> typename Derived = vec>
struct vecbase
{
   PHS_STATIC_ASSERT_LOG(Dimension >= 2, "1-Dimensional vector is not supported!");
   PHS_STATIC_ASSERT_LOG(is_numeric<T>, "Can't create non-numeric vector!");
   PHS_STATIC_ASSERT_LOG((!is_same<Derived<Dimension, T>, quat<Dimension, T>> or Dimension == 4), 
                         "Can't create other than 4-dimensional quaternion!");

   constexpr                                          vecbase()                                        PHS_MATH_NOEXCEPT;

   PHS_NODISCARD static constexpr PHS_INLINE uint     dim()                                            PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE float64_t       length()                                   const;
                                                                                                 
   constexpr PHS_INLINE Derived<Dimension, T>         normalized()                               const;                        
   constexpr PHS_INLINE Derived<Dimension, T>&        normalize();                               
                                                                                                 
   constexpr PHS_INLINE Derived<Dimension, T>&        operator+=(const Derived<Dimension, T>& v)       PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE Derived<Dimension, T>&        operator-=(const Derived<Dimension, T>& v)       PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE Derived<Dimension, T>&        operator*=(T s)                                  PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE Derived<Dimension, T>&        operator/=(T s);                                 
   constexpr PHS_INLINE Derived<Dimension, T>&        operator*=(const Derived<Dimension, T>& v)       PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE Derived<Dimension, T>&        operator/=(const Derived<Dimension, T>& v)       PHS_MATH_NOEXCEPT;
                                                                                                       
   PHS_NODISCARD constexpr PHS_INLINE T&              operator[](size_t i)                             PHS_MATH_NOEXCEPT;
   PHS_NODISCARD constexpr PHS_INLINE const T&        operator[](size_t i)                       const PHS_MATH_NOEXCEPT;
                                                                                                
   PHS_NODISCARD constexpr PHS_INLINE bool            operator!=(const Derived<Dimension, T>& m) const PHS_MATH_NOEXCEPT;
private:
   constexpr PHS_INLINE Derived<Dimension, T>&        __asDerived(vecbase<Dimension, T, Derived>& self);
   constexpr PHS_INLINE const Derived<Dimension, T>&  __asDerived(const vecbase<Dimension, T, Derived>& self) const;
};

} // namespace Phs

#include "vec_common.inl"
