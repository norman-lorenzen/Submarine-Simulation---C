#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logik.h"

float calculate_depth(float depth, float target_depth)
{
    float error = target_depth - depth;
    float tolerance = 0.15;

    if (error > -tolerance && error < tolerance)
    {
        return target_depth;
    }

    if (depth < target_depth)
    {
        depth += 0.2;
    }
    else if (depth > target_depth)
    {
        depth -= 0.1;
    }
    return depth;
}

float calculate_course(float course, float target_course, float knots)
{
    float difference = fabs(target_course - course);


    // brake to 4 knots
    if (difference > 30 && knots > 4.05)
    {
        if (course < target_course) 
        {
            if (difference > 180) course -= 0.1;

            else course += 0.1;
        }
        if (course > target_course)
        {
            if (difference > 180) course += 0.1;

            else course -= 0.1;
        }
    }
    // brake to 8 knots
    else if (15 < difference && difference < 30 && knots > 8.05)
    {
        if (course < target_course) 
        {
            if (difference > 180) course -= 0.5;

            else course += 0.5;
        }
        if (course > target_course)
        {
            if (difference > 180) course += 0.5;

            else course -= 0.5;
        }
    }   
    // if ist less than course 15
    else if (course < target_course)
    {
        course += 1.0;
    }
    else if (course > target_course)
    {
        course -= 1.0;
    }
     if (course >= 360)
    {
        course -= 360;
    }
    else if (course < 0)
    {
        course += 360;
    }
    return course;
}

float calculate_knots(float knots, float target_course, float course)
{
    float difference = fabs(target_course - course);

        // for over 30
        if (difference > 30)
        {
            if (knots > 4.05) knots -= 0.1;
            if (knots < 3.95) knots += 0.3;
        }
        // for 15 - 30
        if (15 < difference && difference < 30)
        {
            if (knots > 8.05) knots -= 0.1;
            if (knots < 7.95) knots += 0.3;
        }
        // for under 15
        if (difference < 15)
        {
            if (knots > 12.05) knots -= 0.1;
            if (knots < 11.95) knots += 0.3;    
        }
        
    return knots;
}

const char* get_cardinal_direction(float course)
{
    // Sicherheitsgurt: Kurs mathematisch auf den Bereich 0.0 bis 359.999 normieren
    while (course < 0.0)    course += 360.0;
    while (course >= 360.0) course -= 360.0;

    // North (N): 337.5° - 22.5° 
    if (course >= 337.5 || course < 22.5) {
        return "N";
    }
    // North east (NE); 22.5 - 67.5
    else if (course >= 22.5 && course < 67.5) {
        return "NE";
    }
    // East (E): 67.5 - 112.5
    else if (course >= 67.5 && course < 112.5) {
        return "E";
    }
    // South east (SE): 112.5 - 157.5
    else if (course >= 112.5 && course < 157.5) {
        return "SE";
    }
    // South (S): 157.5 - 202.5
    else if (course >= 157.5 && course < 202.5) {
        return "S";
    }
    // South west (SW): 202.5 - 247.5
    else if (course >= 202.5 && course < 247.5) {
        return "SW";
    }
    // West (W): 247.5 - 292.5
    else if (course >= 247.5 && course < 292.5) {
        return "W";
    }
    else {
        return "NW";
    }
}
