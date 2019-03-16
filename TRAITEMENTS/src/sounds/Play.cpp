//
// Created by melanie on 12/11/18.
//

#include "sounds/Play.hpp"

sf::Sound Play::sound;
sf::SoundBuffer Play::buffer;

bool Play::init_kaamelott() {


    if (!Play::buffer.loadFromFile("../resources/cest_pas_des_fleches.wav")) {
        std::cout << "Error loading wav" << std::endl;
    }
    Play::sound.setBuffer(Play::buffer);

    Play::sound.play();

    return false;
}

bool Play::init_kaamelott_volume() {


    if (!Play::buffer.loadFromFile("../resources/cest_pas_des_fleches.wav")) {
        std::cout << "Error loading wav" << std::endl;
    }
    Play::sound.setBuffer(Play::buffer);

    Play::sound.setLoop(True);
    Play::sound.setVolume(25);

    Play::sound.play();

    return false;
}

bool Play::close_play_kaamelott(std::pair<float, uint16_t> tmp_i) {

    if ((Play::sound.getStatus() != Play::sound.Playing) && (tmp_i.second < 100) && (tmp_i.second > 90)) {
        Play::sound.play();
    }

    return false;
}

bool Play::distance_volume_kaamelott(double tmp_i_distance) {

    if (tmp_i_distance < 500) {
        Play::sound.setVolume((500 - tmp_i_distance) / 5);
    } else {
        Play::sound.setVolume(0);
    }

    return false;
}
