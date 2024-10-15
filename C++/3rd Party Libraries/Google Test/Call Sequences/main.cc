#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::InSequence;
using ::testing::Return;

class MockClass {
public:
    MOCK_METHOD(void, FunctionA, (int));
    MOCK_METHOD(void, FunctionB, (int));
};

TEST(StateHandlerTest, SequenceTest) {
    MockClass mock;

    InSequence seq;                       // Make sure that EXPECT_CALLs are called in the order they are defined.

    // gMock will search for expectations in the reverse order they are defined!

    // EXPECT_CALL(mock, FunctionA(1));
    // EXPECT_CALL(mock, FunctionB(2)).Times(2);
    EXPECT_CALL(mock, FunctionA(3)).Times(1);
    EXPECT_CALL(mock, FunctionA(3)).Times(1);

    // mock.FunctionA(1);
    // mock.FunctionB(2);
    // mock.FunctionB(2);
    mock.FunctionA(3);
    mock.FunctionA(3);
}