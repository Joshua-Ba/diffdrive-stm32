#include "unity.h"
#include "complementary_filter.hpp"

void setUp(void) {}
void tearDown(void) {}


void test_only_gyro(void) {
    core::ComplementaryFilter complementary_filter{1.0};
    float value = complementary_filter.update(1.0, 0.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, value);
}

void test_only_gyro_mult_steps(void) {
    core::ComplementaryFilter complementary_filter{1.0};
    float value = complementary_filter.update(1.0, 0.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, value);
    value = complementary_filter.update(1.0, 0.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 2.0, value);
}

void test_only_odom(void) {
    core::ComplementaryFilter complementary_filter{0.0};
    float value = complementary_filter.update(0.0, 0.5, 0.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.5, value);
}

void test_mixed(void) {
    core::ComplementaryFilter complementary_filter{0.98};
    float value = complementary_filter.update(1.0, 0.5, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.99, value);
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_only_gyro);
    RUN_TEST(test_only_odom_mult_steps);
    RUN_TEST(test_only_odom);
    RUN_TEST(test_mixed);


    return UNITY_END();
}
