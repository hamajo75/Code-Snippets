#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::InSequence;
using ::testing::Return;

class MockClass {
public:
    MOCK_METHOD0(FunctionA, void());
    MOCK_METHOD0(FunctionB, void());
};

TEST(StateHandlerTest, SequenceTest) {
    MockClass mock;

    InSequence seq;                       // Make sure that EXPECT_CALLs are called in the order they are defined.

    EXPECT_CALL(mock, FunctionA());
    EXPECT_CALL(mock, FunctionB());

    mock.FunctionA();
    mock.FunctionB();
}