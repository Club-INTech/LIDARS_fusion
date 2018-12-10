#include <iostream>
#include "TIM_SICK/lidar/include/TIM561.h"
#include "ROBERT_RP/lidar/include/RPLidar.hpp"
#include "TRAITEMENTS/obstacles/include/Create_obstacle.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <tkInt.h>


using namespace std;

int main(int argc, char **argv) {

    // Initialisation : Graphics
    uint16_t h = 1000;
    uint16_t H = 800;
    sf::RenderWindow window(sf::VideoMode(h, H), "My window");  // création de la fenêtre

    // Initialisation
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

    //    // Sound
//    sf::SoundBuffer buffer;
//    if (!buffer.loadFromFile("../resources/cest_pas_des_fleches.wav"))
//    {
//        cout << "Error loading wav" << endl;
//    }
//    sf::Sound sound;
//    sound.setBuffer(buffer);
//    sound.setLoop(False);

    // Get values
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

                // On fait tourner le programme tant que la fenêtre n'a pas été fermée
                if (window.isOpen())
                {
                    // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        // Fermeture de la fenêtre lorsque l'utilisateur le souhaite
                        if (event.type == sf::Event::Closed)
                            window.close();
                    }

                    // Effacement de la fenêtre (->noir)
                    window.clear(sf::Color::Black);

                    // Drawing
                    sf::CircleShape shape(50);
                    sf::CircleShape point(50);
                    sf::CircleShape point2(50);
                    shape.setFillColor(sf::Color(100, 250, 50));
                    uint16_t radius = 5;
                    shape.setRadius(radius);
                    shape.setOrigin(radius, radius);
                    uint16_t origin_x = h/2;
                    uint16_t origin_y = H/2;
                    shape.setPosition(origin_x,origin_y);
                    window.draw(shape); // L'origine du repère

                    vector<sf::CircleShape> data(tmp.size());
                    double radius_data;
                    if (!tmp.empty()) {
                        for (int i = 0; i < tmp.size(); i++) {
                            data[i].setFillColor(sf::Color(100, 10, 200));
                            //radius_bound = Create_obstacle::list_obstacles[i].width;
                            radius_data = 2;
                            data[i].setRadius(radius_data);
                            data[i].setOrigin(radius_data, radius_data);

                            data[i].setPosition(origin_x + (tmp[i].distance) *
                                                           cos(tmp[i].angle * PI /
                                                               180), origin_y -
                                                                     (tmp[i].distance) *
                                                                     sin(tmp[i].angle *
                                                                         PI / 180));
                            window.draw(data[i]);


//                            if ((sound.getStatus() != sound.Playing) && (tmp[i].distance<100) && (tmp[i].distance>90)) {
                                //printf("angle: %f, distance: %d\n", tmp[i].angle, tmp[i].distance);
                                //sound.play();
//                            }

                        }
                    }

                    for (Bounds bound : Create_obstacle::list_bounds) {
                        point.setFillColor(sf::Color(100, 10, 200));
                        uint16_t radius_bound = 10;
                        point.setRadius(radius_bound);
                        point.setOrigin(radius_bound, radius_bound);

                        point2.setFillColor(sf::Color(100, 100, 200));
                        uint16_t radius_bound2 = 10;
                        point2.setRadius(radius_bound2);
                        point2.setOrigin(radius_bound2, radius_bound2);

                        //point.setPosition((origin_x+bound.the_beginning_distance)*cos(bound.the_beginning_angle*PI/180), -((origin_y+bound.the_beginning_distance)*sin(bound.the_beginning_angle*PI/180)));
                        point.setPosition(origin_x + (bound.the_beginning_distance)*cos(bound.the_beginning_angle*PI/180),  (origin_y + (bound.the_beginning_distance)*sin(bound.the_beginning_angle*PI/180)));
                        //window.draw(point);
                        //point2.setPosition((origin_x+bound.the_end_distance)*cos(bound.the_end_angle*PI/180), -((origin_y+bound.the_end_distance)*sin(bound.the_end_angle*PI/180)));
                        point2.setPosition(origin_x + (bound.the_end_distance)*cos(bound.the_end_angle*PI/180), (origin_y - (bound.the_end_distance)*sin(bound.the_end_angle*PI/180)));
                        //window.draw(point2);

                        sf::Vertex line[] =
                                {
                                        sf::Vertex(sf::Vector2f(origin_x + (bound.the_beginning_distance)*cos(bound.the_beginning_angle*PI/180),  (origin_y - (bound.the_beginning_distance)*sin(bound.the_beginning_angle*PI/180)))),
                                        sf::Vertex(sf::Vector2f(origin_x + (bound.the_end_distance)*cos(bound.the_end_angle*PI/180), (origin_y - (bound.the_end_distance)*sin(bound.the_end_angle*PI/180)))),
                                };

                        window.draw(line, 2, sf::Lines); // Array, size, type

                    }


                    // (1,5) en cartésien = (origin_x + 1, -(origin_y + 5) ) en cartésien SFML
                    // (x,y) en cartésien = (distance*cos(angle_deg*pi/180), distance*sin(angle*pi/180))

                    double radius_bound;
                    if (!Create_obstacle::list_obstacles.empty()) {
                          vector<sf::CircleShape> points(Create_obstacle::list_obstacles.size());
                        for (int i = 0; i < Create_obstacle::list_obstacles.size(); i++) {
                            points[i].setFillColor(sf::Color(10, 100, 200));
                            //radius_bound = Create_obstacle::list_obstacles[i].width;
                            radius_bound = 10;
                            points[i].setRadius(radius_bound);
                            points[i].setOrigin(radius_bound, radius_bound);

                            //points[i].setPosition((float) (origin_x+Create_obstacle::list_obstacles[i].distance)*cos(Create_obstacle::list_obstacles[i].center_angle*PI/180), (float) (-((origin_y+Create_obstacle::list_obstacles[i].distance)*sin(Create_obstacle::list_obstacles[i].center_angle*PI/180))));
                            points[i].setPosition(origin_x + (Create_obstacle::list_obstacles[i].distance) *
                                                             cos(Create_obstacle::list_obstacles[i].center_angle * PI /
                                                                 180), origin_y -
                                                                       (Create_obstacle::list_obstacles[i].distance) *
                                                                       sin(Create_obstacle::list_obstacles[i].center_angle *
                                                                           PI / 180));
                            window.draw(points[i]);
                        }
                    }

                    window.display();  // Fin de la frame courante, affichage de tout ce qu'on a dessiné
                }

            }
        }
    }
    
    lidars[0]->close();

    return 0;
}