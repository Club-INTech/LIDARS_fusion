//
// Created by melanie on 12/9/18.
//

#ifndef LIDARS_FUSION_BOUNDS_HPP
#define LIDARS_FUSION_BOUNDS_HPP

#include <stdint-gcc.h>

typedef struct Bounds {
    float the_beginning_angle = 0.0;
    float the_beginning_distance = 0.0;
    float the_end_angle = 0.0;
    float the_end_distance = 0.0;
} Bounds;

#endif //LIDARS_FUSION_BOUNDS_HPP
