#pragma once

#include "common.h"
#include "types.h"
#include "vec_common.h"
#include "assert.h"

namespace Phs
{

template<typename T>
struct vec<2, T> : public vecbase<2, T>
{
   friend struct vecbase<2, T>;

   static constexpr T __Zero = static_cast<T>(0);

   constexpr PHS_INLINE                         vec()                              PHS_MATH_NOEXCEPT;
                                                                             
   template <dim_int_t Dim>                                                  
   constexpr PHS_INLINE explicit                vec(const vec<Dim, T>& v)          PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE explicit                vec(T s1, T s2 = __Zero)  PHS_MATH_NOEXCEPT;
                                                                                                  
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>&  round();
                                                                            
   constexpr PHS_INLINE PHS_NODISCARD float64_t lengthSquared()              const PHS_MATH_NOEXCEPT;

   template <dim_int_t Dim>
   constexpr PHS_INLINE vec2<T>&                operator=(const vec<Dim, T>& v)    PHS_MATH_NOEXCEPT;
                                                
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator+(const vec2<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator-(const vec2<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator*(T s)               const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator/(T s)               const;
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator*(const vec2<T>& v)  const PHS_MATH_NOEXCEPT;
   constexpr PHS_INLINE PHS_NODISCARD vec2<T>   operator/(const vec2<T>& v)  const;
                                                
   constexpr PHS_INLINE PHS_NODISCARD bool      operator==(const vec2<T>& v) const PHS_MATH_NOEXCEPT;

#if defined(PHS_EXTENSIONS) and defined(PHS_USE_ANONYMOUS_STRUCT)
   union 
   {
      struct { T x, y; };
      struct { T u, v; };
      struct { T s, t; };
   };
#else
   union
   {
      T x, u, s;
   };
   union
   {
      T y, v, t;
   };
#endif
private:
   static constexpr dim_int_t _Dimension = 2;
};

template <typename T>
PHS_INLINE std::ostream& operator<<(std::ostream& out, const vec2<T>& v);

template <typename T>
constexpr PHS_INLINE T dot(const vec2<T>& a, const vec2<T>& b) PHS_MATH_NOEXCEPT;

using vec2f = vec2<float32_t>;
using vec2i = vec2<int32_t>;

} // namespace Phs

#include "vec2.inl"
