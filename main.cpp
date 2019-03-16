#include <iostream>
#include "LIDARS/RPLIDAR_A2/include/lidar/RPLidar.hpp"
#include "LIDARS/TIM561/include/lidar/TIM561.h"
#include "obstacles/Create_obstacle.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <tkInt.h>
#include <socket/DataSocket.hpp>
#include "graphics/Show.hpp"
#include "sounds/Play.hpp"


const static char* SERVER_ADDRESS = "127.0.0.1";
static const uint16_t  SERVER_PORT    =	17685;
constexpr static float STEP_TIM       = 0.3345719;
constexpr static float STEP_RP        = 0.9;

bool running = true;
void signal_handler(int signo){
    if(signo==SIGTERM || signo==SIGINT)
        running = false;
}

enum LIDAR_TYPE{
    NONE = 0,
    RP   = 1,
    TIM  = 2
};

int main(int argc, char **argv) {

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    running=false;

    // Connexion HL
    DataSocket HL(SERVER_ADDRESS, SERVER_PORT); //Connection to the client
    while(!HL.accept_client());

    // Initialisation : Graphics
    uint16_t h = 1000;
    uint16_t H = 800;
    sf::RenderWindow window(sf::VideoMode(h, H), "My window");  // Création de la fenêtre

    // Initialisation
    LIDAR_TYPE lidar = NONE;
    RPLidar lidar_rp;
    TIM561 lidar_tim;
    if(!strcmp(argv[1], "rp")){
        std::cout << "Connection to RPLiDAR A2..." << std::endl;
        lidar_rp.init(argc>2?argv[argc-1] : "/dev/ttyUSB0"); // /dev/ttyUSB0 default
        lidar = RP;
        running = true;
    }
    if(!strcmp(argv[1], "tim")){
        std::cout << "Connection to TIM561..." << std::endl;
        if(lidar_tim.connect(SERVER_ADDRESS, SERVER_PORT)) {
            std::cout << "Connected" << std::endl;
            lidar = TIM;
            running = true;
        }
    }
    std::vector<std::string> list_mesures;

    char * buffer;
    std::cout << "Started" << std::endl;

    while (running) {
        usleep(70000);
        // Get values
        if(lidar == RP){
            lidar_rp.update();
            const std::vector<std::pair<float, uint16_t>>* tmp = lidar_rp.getDataPoints();
            Show::print_shell(tmp, &list_mesures); // update aussi list_mesures
            std::string distance_min = *std::min_element(list_mesures.begin(), list_mesures.end());
            std::cout << distance_min << " \n";
            buffer = new char[distance_min.size()];
            auto result = HL.send_data(buffer);
            // In window
            Create_obstacle::analyse(tmp, STEP_RP);
            Show::draw_all(&window, tmp);
        }
        else if (lidar == TIM){
            lidar_tim.update();
            const std::vector<std::pair<float, uint16_t>>* tmp = lidar_tim.getDataPoints();
            Show::print_shell(tmp, &list_mesures); // update aussi list_mesures
            std::string distance_min = *std::min_element(list_mesures.begin(), list_mesures.end());
            std::cout << distance_min << " \n";
            buffer = new char[distance_min.size()];
            auto result = HL.send_data(buffer);
            // In window
            Create_obstacle::analyse(tmp, STEP_TIM);
            Show::draw_all(&window, tmp);
        }

    }

    delete[] buffer;
    if(lidar==RP)
        lidar_rp.close();
    else if (lidar==TIM)
        lidar_tim.close();


    return 0;
}