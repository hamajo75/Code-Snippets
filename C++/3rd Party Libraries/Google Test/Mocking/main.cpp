#include <iostream>
#include <string.h>

#include "cut.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

/* Mocks are used to test logic that uses an API (or an Interface).
   It only checks the API function
   calls nothing inside the API. It's not testing the implementation of the API (only
   the Component under Test).

Notes:
It's neither a stub nor a fake.
Fake: working but usually heavily simplified implementation.
Stub: return predefined results, no real logic inside.
Mock: no implementation, just checking e.g. how often a function is called.
*/
//-----------------------------------------------------------------------------
class API {
 public:
  virtual ~API() {}
  virtual bool APICall(int x, int y) = 0;
};
class MockAPI : public API {
 public:
  MOCK_METHOD(bool, APICall, (int x, int y), (override));
};
//-----------------------------------------------------------------------------
// Component Under Test (CUT)
class UsingTheAPI {
  API& api_;

 public:
  explicit UsingTheAPI(API& api) : api_{api} {}

  void UseTheAPI() {
    if (api_.APICall(1, 2))
      std::cout << "Success\n";
  }
};

std::string fun2BMocked() {
  return "fun2BMocked_mocked";
}

//-----------------------------------------------------------------------------
TEST(Test1, Subtest1) {
  fun2BTested();
}
//-----------------------------------------------------------------------------
TEST(Test1, Subtest2) {
  ASSERT_FALSE(1 == 2);
}
//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}




