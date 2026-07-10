#include "unity.h"
#include "odometry.hpp"

constexpr float PI = 3.14159265f;

void setUp(void) {}
void tearDown(void) {}


void test_calc_pos_straight_forward(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, 1.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.theta);
}

void test_calc_pos_straight_backward(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, -1.0, -1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.theta);
}

void test_calc_pos_only_rot_clock(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, 0.1, -0.1);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, position.theta);
}

void test_calc_pos_only_rot_counter_clock(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, -0.1, 0.1);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, position.theta);
}

void test_calc_pos_forward_rot_clock(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, 1.0, 0.8);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.9, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, position.theta);
}

void test_calc_pos_backward_rot_counter_clock(void) {
    core::pose old{0.0, 0.0, 0.0};
    core::pose position = core::calculate_new_position(old, 0.2, -1.0, -0.8);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -0.9, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, position.theta);
}

void test_calc_pos_forward_facing_pos_y(void) {
    core::pose old{0.0, 0.0, PI/2};
    core::pose position = core::calculate_new_position(old, 0.2, 1.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, PI/2, position.theta);
}

void test_calc_pos_forward_facing_neg_x(void) {
    core::pose old{0.0, 0.0, PI};
    core::pose position = core::calculate_new_position(old, 0.2, 1.0, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, -1.0, position.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, position.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, PI, position.theta);
}

void test_update_odometry(void) {
    core::Odometrie odom{0.2};
    odom.update_position(1.0, 1.0);
    odom.update_position(1.0, 1.0);
    core::pose odom_pose = odom.get_pose();
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 2.0, odom_pose.pos_x);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, odom_pose.pos_y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0, odom_pose.theta);

}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_calc_pos_straight_forward);
    RUN_TEST(test_calc_pos_straight_backward);
    RUN_TEST(test_calc_pos_only_rot_clock);
    RUN_TEST(test_calc_pos_only_rot_counter_clock);
    RUN_TEST(test_calc_pos_forward_rot_clock);
    RUN_TEST(test_calc_pos_backward_rot_counter_clock);
    RUN_TEST(test_calc_pos_forward_facing_pos_y);
    RUN_TEST(test_calc_pos_forward_facing_neg_x);
    RUN_TEST(test_update_odometry);
    return UNITY_END();
}
