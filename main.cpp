#include <iostream>
#include "TIM_SICK/lidar/include/TIM561.h"
#include "ROBERT_RP/lidar/include/RPLidar.hpp"
#include "TRAITEMENTS/obstacles/include/Create_obstacle.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <tkInt.h>
#include "TRAITEMENTS/graphics/include/Show.hpp"
#include "TRAITEMENTS/sounds/include/Play.hpp"


int main(int argc, char **argv) {

    // Initialisation : Graphics
    uint16_t h = 1000;
    uint16_t H = 800;
    sf::RenderWindow window(sf::VideoMode(h, H), "My window");  // Création de la fenêtre

    // Initialisation
    std::vector<Lidar *> lidars;
    std::vector<std::string> list_mesures;

    // Sound
    //Play::init_kaamelott_volume();

    // LiDAR
    std::cout << "Connection..." << std::endl;
    if (std::string(argv[1]) == "tim") {
        printf("tim selected\n");
        lidars.push_back(new TIM561());
    } else if (std::string(argv[1]) == "rp") {
        printf("rp selected\n");
        lidars.push_back(new RPLidar(argc > 2 ? argv[argc - 1] : "/dev/ttyUSB0"));
    }

    if (lidars[0]->connect("192.168.1.93", 2112)) {
        std::cout << "Connected" << std::endl;

        if (lidars[0]->start()) {
            std::cout << "Started" << std::endl;

            while (true) {

                usleep(70000);

                // Get values
                lidars[0]->update();
                auto tmp = lidars[0]->getDataPoints();

                Show::print_shell(tmp, &list_mesures);
                std::string distance_min = *std::min_element(list_mesures.begin(), list_mesures.end());
                std::cout << distance_min << " \n";
                Play::distance_volume_kaamelott(atof(distance_min.c_str()));

                // In shell
                //Show::print_shell(tmp, &list_mesures);
                //Show::show_shell(tmp);

                // In window
                Create_obstacle::analyse(tmp);
                Show::draw_all(&window, tmp);
            }
        }
    }

    lidars[0]->close();

    return 0;
}