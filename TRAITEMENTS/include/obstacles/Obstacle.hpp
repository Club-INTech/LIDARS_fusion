//
// Created by melanie on 12/9/18.
//

#ifndef LIDARS_FUSION_OBSTACLE_HPP
#define LIDARS_FUSION_OBSTACLE_HPP

#include <stdint-gcc.h>

typedef struct Obstacle {
    double center_angle = 0;
    double distance = 0;
    double width = 0;
} Obstacle;

#endif //LIDARS_FUSION_OBSTACLE_HPP
