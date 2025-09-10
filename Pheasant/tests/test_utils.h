#pragma once

#define PHS_RUNTIME_ASSERT_ENABLE
#include "precompile.h"
#include "logger/log.h"

namespace TestPlatform
{

#define TEST_CASE(testname)                                                               \
   static void __TEST_##testname();                                                       \
   struct __##testname##_registry {                                                       \
      __##testname##_registry() { Testcases::registerNew(#testname, __TEST_##testname); } \
   };                                                                                     \
   static __##testname##_registry testname##_registrar_instance;                          \
                                                                                          \
   static void __TEST_##testname()

#define REQUIRE(cond)                                              \
   do {                                                            \
      if (!(cond)) {                                               \
         PHS_LOG_FATAL_FULL_INFO("Requirement failed: {}", #cond); \
         std::exit(1);                                             \
      }                                                            \
   } while (0)

class Testcases
{
public:
   using TestFunc = void(*)();
   using TestcaseData = std::pair<std::string, TestFunc>;

   static std::vector<TestcaseData>& get();
   static void                       registerNew(const char* name, TestFunc f);
   static int                        runAll();
private:
   static inline std::vector<TestcaseData> _reg;
};

} // namespace TestPlatform
