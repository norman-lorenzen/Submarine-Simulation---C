#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "sensoren.c"
#include "logik.c"

// prototypes for the sensor functions
int get_depth(int real_depth);
int get_course(int real_course);

// for the cardinal direction
const char* get_cardinal_direction(float course);

// full function
int main() {

    // asking for start depth
    int start_depth;
    printf("Start Depth: ");
    scanf("%d", &start_depth);

    // asking for start course
    int start_course;
    printf("Start Course: ");
    scanf("%d", &start_course);

    // asking for target depth
    float target_depth;
    printf("Target Depth: ");
    scanf("%f", &target_depth);

    // asking for target course
    int target_course;
    printf("Target Course: ");
    scanf("%d", &target_course);

    // asking for march speed
    int get_knots;
    printf("Knots (0.0 - 20.0 avaible): ");
    scanf("%d", &get_knots);

    if (get_knots > 20)
    {
        get_knots = 20;
    }
    if (get_knots < 0)
    {
        get_knots = 0;
    }

    // copy get_depth to depth
    float depth = (float)start_depth;
    float course = (float)start_course;
    float knots = (float)get_knots;

    // starting mission
    printf("====================================\n");
    printf("Mission start...\n");
    printf("====================================\n");

    // copy cardinal direction in direction
    const char* direction = get_cardinal_direction(course);

    while (depth != target_depth || course != target_course)
    {
        // real time
        char time_string[9];
        time_t rohe_zeit;
        time(&rohe_zeit);
        struct tm *time_info = localtime(&rohe_zeit);
        strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);

        // print out time, depth, course and diretion, in real time
        printf("[%s] Live-Data -> SPEED: %.2f DEPTH: %.3f m | COURSE: %.3f Grad | DIRECTION: %s\n", time_string, knots, depth, course, direction);

        // simulate real time delay
        sleep(1);
        
        // new depth
        depth = calculate_depth(depth, target_depth);

        // new course
        course = calculate_course(course, target_course, knots);

        // new direction
        direction = get_cardinal_direction(course);

        // new march speed
        knots = calculate_knots(knots, target_course, course);
    } 
    printf("====================================\n");
    printf("Mission accomplished!\n");
    printf("====================================\n");

    return 0;
}