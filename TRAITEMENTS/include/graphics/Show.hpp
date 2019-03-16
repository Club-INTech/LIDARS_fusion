//
// Created by melanie on 12/11/18.
//

#ifndef LIDARS_FUSION_SHOW_HPP
#define LIDARS_FUSION_SHOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TIM_SICK/include/lidar/DataPoint.h"
#include "../../../Lidar.hpp"
#include <iostream>
#include "../obstacles/Bounds.hpp"
#include "../obstacles/Create_obstacle.hpp"
#include "../sounds/Play.hpp"
#include <tkInt.h>


class Show {
public:
    static bool print_shell(std::array<DataPoint, Lidar::NBR_DATA> tmp, std::vector<std::string> *list_mesures);

    static bool show_shell(std::array<DataPoint, Lidar::NBR_DATA> tmp);

    static bool draw_origin(sf::RenderWindow *window, uint16_t *origin_x, uint16_t *origin_y);

    static bool draw_data(sf::RenderWindow *window, std::array<DataPoint, Lidar::NBR_DATA> tmp, uint16_t *origin_x,
                          uint16_t *origin_y);

    static bool draw_bounds(sf::RenderWindow *window, uint16_t *origin_x, uint16_t *origin_y);

    static bool draw_obstacles(sf::RenderWindow *window, uint16_t *origin_x, uint16_t *origin_y);

    static bool draw_all(sf::RenderWindow *window, std::array<DataPoint, Lidar::NBR_DATA> tmp);
};

#endif //LIDARS_FUSION_SHOW_HPP
