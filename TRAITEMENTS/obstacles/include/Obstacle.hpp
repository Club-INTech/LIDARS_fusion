//
// Created by melanie on 12/9/18.
//

#ifndef LIDARS_FUSION_OBSTACLE_HPP
#define LIDARS_FUSION_OBSTACLE_HPP

#include <stdint-gcc.h>

typedef struct Obstacle {
    uint16_t center_angle = 0;
    uint16_t distance = 0;
} Obstacle;

#endif //LIDARS_FUSION_OBSTACLE_HPP
