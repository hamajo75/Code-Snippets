#ifndef TEST_H
#define TEST_H

#include <string>

using namespace std;

#define RUN_TEST(x, y) run_test(x, #x, y)

typedef bool (*test_fct_t)(void);

void run_test(test_fct_t test_fct, string test_fct_name, bool& result);

#endif /* TEST_H */
