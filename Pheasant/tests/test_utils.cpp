#include "test_utils.h"

namespace TestPlatform
{

std::vector<Testcases::TestcaseData>& Testcases::get()
{
   return _reg;
}

void Testcases::registerNew(const char* name, TestFunc f)
{
   _reg.emplace_back(name, f);
}

int Testcases::runAll()
{
   const size_t test_cnt = _reg.size();

   for (auto& [name, testcase_func] : Testcases::get())
   {
      PHS_LOG_INFO("[ TEST RUN ] {}", name);
      testcase_func();
      PHS_LOG_INFO("[ TEST OK  ] {}", name);
   }

   PHS_LOG_INFO("All {} tests passed.", test_cnt);
   return 0;
}

} // namespace TestPlatform
