#include "unity.h"
#include "pid.hpp"

void setUp(void) {}
void tearDown(void) {}


void test_p_controller(void) {
    core::PID pid{2.0, 0.0, 0.0, 100.0};
    float value = pid.update(10.0, 8.0, 0.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);
}

void test_i_controller_1(void) {
    core::PID pid{0.0, 2.0, 0.0, 100.0};
    float value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);

    value = pid.update(10.0, 9.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 6.0, value);
}

void test_i_controller_2(void) {
    core::PID pid{0.0, 2.0, 0.0, 100.0};
    float value = pid.update(10.0, 8.0, 0.5);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 2.0, value);

    value = pid.update(10.0, 9.0, 0.5);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 3.0, value);
}

void test_d_controller(void) {
    core::PID pid{0.0, 0.0, 2.0, 100.0};
    float value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);

    value = pid.update(10.0, 9.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -2.0, value);
}

void test_windup_p(void){
    core::PID pid{0.0, 2.0, 0.0, 10.0};
    float value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);

    value = pid.update(10.0, 10.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);

    value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 8.0, value);

    value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 10.0, value);

    value = pid.update(10.0, 8.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 10.0, value);

    value = pid.update(10.0, 10.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 8.0, value);

    value = pid.update(8.0, 10.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0, value);

    value = pid.update(8.0, 10.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, value);
}

void test_windup_mixed(void) {
    core::PID pid{1.0, 2.0, 0.0, 10.0};

    float value = pid.update(10.0, 6.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 10.0, value);

    value = pid.update(10.0, 6.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 10.0, value);

    value = pid.update(6.0, 6.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, value);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_p_controller);
    RUN_TEST(test_i_controller_1);
    RUN_TEST(test_i_controller_2);
    RUN_TEST(test_d_controller);
    RUN_TEST(test_windup_p);
    RUN_TEST(test_windup_mixed);

    return UNITY_END();
}
