#include <iostream>
#include "TIM_SICK/lidar/include/TIM561.h"
#include "ROBERT_RP/lidar/include/RPLidar.hpp"
#include "TRAITEMENTS/obstacles/include/Create_obstacle.hpp"
#include <SFML/Graphics.hpp>


using namespace std;

int main(int argc, char **argv) {

    std::vector<Lidar *> lidars;
    std::vector<std::string> list_mesures;
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
                lidars[0]->update();
                auto tmp = lidars[0]->getDataPoints();
                list_mesures.clear();

//                for (int i = 0; i < TIM561::NBR_DATA; i += 1) {
////                    if (tmp[i].distance < 500)
////                        printf("|");
////                    else
////                        printf(".");
//                    list_mesures.push_back("[");
//                    list_mesures.push_back(std::to_string(tmp[i].angle));
//                    list_mesures.push_back(",");
//                    list_mesures.push_back(std::to_string(tmp[i].distance));
//                    list_mesures.push_back("] ");
//                    //printf("[%g, %d] ", tmp[i].angle, tmp[i].distance);
//                }
//                for (std::string mesure : list_mesures) {
//                    cout << mesure;
//                }
//                printf("\n\n");

                Create_obstacle::analyse(tmp);



            }
        }
    }
    
    lidars[0]->close();

    return 0;
}