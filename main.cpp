#include <iostream>
#include "TIM_SICK/lidar/include/TIM561.h"
#include "ROBERT_RP/lidar/include/RPLidar.hpp"

using namespace std;

int main(int argc, char **argv) {

    vector<Lidar *> lidars;
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

                for (int i = 0; i < TIM561::NBR_DATA; i += 5) {
                    if (tmp[i].distance < 500)
                        printf("|");
                    else
                        printf(".");
                }
                printf("\n");

            }
        }
    }
    
    lidars[0]->close();

    return 0;
}