#include "gtest/gtest.h"
#include "gtest/gtest-param-test.h"

#include <memory>

enum class State {
  kOff,
  kYellowLights,
  kRedLights,
  kGreenLights,
  kA2Alarm,
  kA2AlarmReduced,
  kA1Alarm,
  kWarning,
};

enum class EventNotification {
  kCheckInSuccessful,
  kCheckInFailed,
  kCheckOut,
};

using StateProposition = std::pair<
    State,  // expected emissions
    EventNotification  // input
  >;

class StateEmissionTestFixture :
  public testing::TestWithParam<std::vector<StateProposition>>
{};

TEST_P(StateEmissionTest, UpdateAndEmitState) {
  const auto& pairs = GetParam();        // get values from INSTANTIATE_TEST_CASE_P

  // do something with pairs
}

INSTANTIATE_TEST_CASE_P(
  StateEmissionTest,                            // test suite
  StateEmissionTestFixture,                     //
  ::testing::Values(                            // parameters to be used
    {kOff, kCheckInSuccessfull},
    {kYellowLights, kCheckInSuccessfull}
  )
);

//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}




