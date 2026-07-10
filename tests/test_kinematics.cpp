#include "unity.h"
#include "kinematics.hpp"

void setUp(void) {}
void tearDown(void) {}

void test_drive_straight(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(1.0, 0.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, answer.right);
}

void test_rotate_right(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(0.0, 2.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -0.2, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.2, answer.right);
}
void test_rotate_left(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(0.0, -2.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.2, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -0.2, answer.right);
}
void test_drive_right(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(1.0, 2.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.8, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.2, answer.right);
}
void test_drive_left(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(1.0, -2.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.2, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.8, answer.right);
}
void test_no_drive(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(0.0, 0.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, answer.right);
}
void test_drive_backwards(void) {
    core::WheelSpeeds answer = core::inverse_kinematics(-1.0, 0.0, 0.2);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, answer.left);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, answer.right);
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_drive_straight);
    RUN_TEST(test_rotate_right);
    RUN_TEST(test_rotate_left);
    RUN_TEST(test_drive_right);
    RUN_TEST(test_drive_left);
    RUN_TEST(test_no_drive);
    RUN_TEST(test_drive_backwards);
    return UNITY_END();
}
