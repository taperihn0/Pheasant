#include "test_utils.h"
#include "math/math.h"

namespace TestPlatform
{

using namespace Phs;

TEST_CASE(test_vec_add) 
{
   vec2i a(1, 2);
   vec2i b(3, -1);
   vec2i sum = a + b;
   vec2i req0(4, 1);
   REQUIRE(sum == req0);

   vec4f c(3.1f, 2.2f, 9.f, 1.3f);
   vec3f d(2.2f, 1.1f, 8.f);
   vec4f e = c + static_cast<vec4f>(d);
   vec4f req1(5.3f, 3.3f, 17.f, 1.3f);
   REQUIRE(approxEqual(e, req1));
}

TEST_CASE(test_vec_sub) 
{
   vec2i a(5, 7);
   vec2i b(2, 3);
   vec2i diff = a - b;
   vec2i req(3, 4);
   REQUIRE(diff == req);
}

TEST_CASE(test_vec_mul_scalar)
{
   vec2i a(2, -3);
   vec2i prod = a * 4;
   vec2i req(8, -12);
   REQUIRE(prod == req);

   vec3f b(1.5f, -2.f, 0.5f);
   vec3f prodf = b * 2.f;
   vec3f reqf(3.f, -4.f, 1.f);
   REQUIRE(approxEqual(prodf, reqf));
}

TEST_CASE(test_vec_div_scalar)
{
   vec2i a(8, -4);
   vec2i div = a / 2;
   vec2i req(4, -2);
   REQUIRE(div == req);

   vec4f b(9.f, -6.f, 3.f, -12.f);
   vec4f divf = b / 3.f;
   vec4f reqf(3.f, -2.f, 1.f, -4.f);
   REQUIRE(approxEqual(divf, reqf));
}

TEST_CASE(test_vec_equality)
{
   vec2i a(1, 2);
   vec2i b(1, 2);
   vec2i c(2, 1);

   REQUIRE(a == b);
   REQUIRE(a != c);
}

TEST_CASE(test_vec_cast)
{
   vec3i a(1, 2, 3);
   vec4f b = static_cast<vec4f>(a); // promote
   vec4f req(1.f, 2.f, 3.f, 0.f);
   REQUIRE(approxEqual(b, req));

   vec4f c(5.5f, 6.6f, 7.7f, 8.8f);
   vec3i d = static_cast<vec3i>(c); // truncate
   vec3i reqd(5, 6, 7);
   REQUIRE(d == reqd);
}

TEST_CASE(test_vec_dot_product)
{
   vec2i a(1, 2);
   vec2i b(3, 4);
   int prod = dot(a, b);
   REQUIRE(prod == 11); // 1*3 + 2*4 = 11

   vec3f c(1.f, 0.f, -1.f);
   vec3f d(2.f, 3.f, 4.f);
   float dotf = dot(c, d);
   REQUIRE(approxEqual64f(dotf, -2.f));
}

TEST_CASE(test_vec_cross_product)
{
   vec3i a(1, 0, 0);
   vec3i b(0, 1, 0);
   vec3i cross_ab = cross(a, b);
   vec3i req(0, 0, 1);
   REQUIRE(cross_ab == req);

   vec3f c(0.f, 0.f, 1.f);
   vec3f d(1.f, 0.f, 0.f);
   vec3f cross_cd = cross(c, d);
   vec3f reqf(0.f, 1.f, 0.f);
   REQUIRE(approxEqual(cross_cd, reqf));
}

TEST_CASE(test_vec_length)
{
   vec3f v(3.0f, 4.0f, 0.0f);
   REQUIRE(approxEqual64f(v.length(), 5.0));  // 3-4-5 triangle
   REQUIRE(approxEqual64f(v.lengthSquared(), 25.0));
}

TEST_CASE(test_vec_normalized)
{
   vec3f v(10.0f, 0.0f, 0.0f);
   vec3f n = v.normalized();

   REQUIRE(approxEqual(n, vec3f(1.0f, 0.0f, 0.0f)));
   REQUIRE(approxEqual64f(n.length(), 1.0));

   // Ensure lengthSquared is exactly 1 for normalized vector
   REQUIRE(approxEqual64f(n.lengthSquared(), 1.0));
}

TEST_CASE(test_vec_casting)
{
   vec3f v3(1.0f, 2.0f, 3.0f);
   vec4f v4 = static_cast<vec4f>(v3);  // should preserve first 3 components
   vec4f expected(1.0f, 2.0f, 3.0f, 0.0f); // assuming cast sets w = 0
   REQUIRE(approxEqual(v4, expected));

   vec2f v2 = static_cast<vec2f>(v3);
   REQUIRE(approxEqual(v2, vec2f(1.0f, 2.0f)));
}

TEST_CASE(test_vec_combined_ops)
{
   vec3f a(1.0f, 2.0f, 3.0f);
   vec3f b(-1.0f, 0.0f, 1.0f);

   vec3f sum = a + b;
   REQUIRE(approxEqual(sum, vec3f(0.0f, 2.0f, 4.0f)));

   vec3f diff = a - b;
   REQUIRE(approxEqual(diff, vec3f(2.0f, 2.0f, 2.0f)));

   vec3f scaled = a * 2.0f;
   REQUIRE(approxEqual(scaled, vec3f(2.0f, 4.0f, 6.0f)));
}

TEST_CASE(test_vec_chained_ops_and_normalization)
{
   vec3f v(2.0f, 0.0f, 0.0f);
   vec3f res = (v * 3.0f).normalized();
   REQUIRE(approxEqual(res, vec3f(1.0f, 0.0f, 0.0f)));
}


} // namespace TestPlatform

int main()
{
   Phs::Log::init();
   return TestPlatform::Testcases::runAll();
}
