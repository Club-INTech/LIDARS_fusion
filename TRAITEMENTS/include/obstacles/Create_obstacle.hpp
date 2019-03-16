//
// Created by melanie on 12/9/18.
//

#ifndef LIDARS_FUSION_CREATE_HPP
#define LIDARS_FUSION_CREATE_HPP

#include <string>
#include <vector>
#include "Obstacle.hpp"
#include "Bounds.hpp"

class Create_obstacle {
public:
    static bool analyse(const std::vector<std::pair<float, uint16_t>> *currentDataPoints, float step_angle);

    static std::vector<Obstacle> list_obstacles;
    static std::vector<Bounds> list_bounds;
private:
    constexpr static uint16_t DISTANCE_MAX = 800;
    constexpr static uint16_t MIN_GAP_BTW_OBSTACLES = 100;
    constexpr static uint16_t MIN_DISTANCE = 150;
    constexpr static uint16_t MIN_WIDTH = 20;
};

#endif //LIDARS_FUSION_CREATE_HPP
