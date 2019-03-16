//
// Created by melanie on 12/9/18.
//

#ifndef LIDARS_FUSION_CREATE_HPP
#define LIDARS_FUSION_CREATE_HPP

#include <string>
#include <vector>
#include "Obstacle.hpp"
#include "Bounds.hpp"
#include "../../../TIM_SICK/lidar/DataPoint.h"
#include "../../../TIM_SICK/lidar/TIM561.h"

class Create_obstacle {
public:
    static bool analyse(std::array<DataPoint, TIM561::NBR_DATA> currentDataPoints);

    static std::vector<Obstacle> list_obstacles;
    static std::vector<Bounds> list_bounds;
private:
    constexpr static uint16_t DISTANCE_MAX = 800;
    constexpr static uint16_t MIN_GAP_BTW_OBSTACLES = 100;
    constexpr static uint16_t MIN_DISTANCE = 150;
    constexpr static uint16_t MIN_WIDTH = 20;
};

#endif //LIDARS_FUSION_CREATE_HPP