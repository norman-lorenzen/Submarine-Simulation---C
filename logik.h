#ifndef logik_H
#define logik_H

// here we will define the function for cardinal direction
const char* get_cardinal_direction(float course);

// calculate depth
float calculate_depth(float depth, float target_depth);

// calculate course
float calculate_course(float course, float target_course, float knots);

// calculate knots
float calculate_knots(float knots, float target_course, float course);

#endif