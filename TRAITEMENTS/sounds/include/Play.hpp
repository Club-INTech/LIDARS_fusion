//
// Created by melanie on 12/11/18.
//

#ifndef LIDARS_FUSION_PLAY_HPP
#define LIDARS_FUSION_PLAY_HPP

#include "SFML/Audio.hpp"
#include <iostream>
#include <tkPort.h>
#include "../../../TIM_SICK/lidar/include/DataPoint.h"


class Play {
public:
    static bool init_kaamelott();
    static bool init_kaamelott_volume();
    static sf::Sound sound;
    static sf::SoundBuffer buffer;
    static bool close_play_kaamelott(DataPoint tmp_i);
    static bool distance_volume_kaamelott(double tmp_i_distance);
};

#endif //LIDARS_FUSION_PLAY_HPP
