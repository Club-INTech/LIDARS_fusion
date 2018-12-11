//
// Created by melanie on 12/11/18.
//

#include "../include/Show.hpp"

// (1,5) en cartésien = (origin_x + 1, -(origin_y + 5) ) en cartésien SFML
// (x,y) en cartésien = (distance*cos(angle_deg*pi/180), distance*sin(angle*pi/180))



bool Show::print_shell(std::array<DataPoint, Lidar::NBR_DATA> tmp, std::vector<std::string> *list_mesures) {

    list_mesures->clear();

    for (int i = 0; i < TIM561::NBR_DATA; i += 1) {
//                    list_mesures.push_back("[");
//                    list_mesures.push_back(std::to_string(tmp[i].angle));
//                    list_mesures.push_back(",");
//                    list_mesures.push_back(std::to_string(tmp[i].distance));
//                    list_mesures.push_back("] ");
        if (tmp[i].distance > 99) {
            list_mesures->push_back(std::to_string(tmp[i].distance));
        }
    }
//                for (std::string mesure : *list_mesures) {
//                    std::cout << mesure;
//                }
//                printf("\n\n");

    return false;
}

bool Show::show_shell(std::array<DataPoint, Lidar::NBR_DATA> tmp) {

    for (int i = 0; i < TIM561::NBR_DATA; i += 1) {
        if (tmp[i].distance < 500)
            printf("|");
        else
            printf(".");
    }

    return false;
}

bool Show::draw_origin(sf::RenderWindow *window, uint16_t *origin_x, uint16_t *origin_y) {

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    uint16_t radius = 5;
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    *origin_x = window->getSize().y / 2;
    *origin_y = window->getSize().x / 2;
    shape.setPosition(*origin_x, *origin_y);
    window->draw(shape); // L'origine du repère

    return false;
}

bool Show::draw_data(sf::RenderWindow *window, std::array<DataPoint, Lidar::NBR_DATA> tmp, uint16_t *origin_x,
                     uint16_t *origin_y) {

    std::vector<sf::CircleShape> data(tmp.size());
    double radius_data;
    if (!tmp.empty()) {
        for (int i = 0; i < tmp.size(); i++) {
            data[i].setFillColor(sf::Color(100, 10, 200));
            //radius_bound = Create_obstacle::list_obstacles[i].width;
            radius_data = 2;
            data[i].setRadius(radius_data);
            data[i].setOrigin(radius_data, radius_data);

            data[i].setPosition(*origin_x + (tmp[i].distance) *
                                            cos(tmp[i].angle * PI /
                                                180), *origin_y -
                                                      (tmp[i].distance) *
                                                      sin(tmp[i].angle *
                                                          PI / 180));
            window->draw(data[i]);

            //Play::close_play_kaamelott(tmp[i]);
        }
    }

    return false;
}

bool Show::draw_bounds(sf::RenderWindow *window, uint16_t *origin_x,
                       uint16_t *origin_y) {

    sf::CircleShape point(50);
    sf::CircleShape point2(50);
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
        point.setPosition(*origin_x + (bound.the_beginning_distance) * cos(bound.the_beginning_angle * PI / 180),
                          (*origin_y + (bound.the_beginning_distance) * sin(bound.the_beginning_angle * PI / 180)));
        //window.draw(point);
        //point2.setPosition((origin_x+bound.the_end_distance)*cos(bound.the_end_angle*PI/180), -((origin_y+bound.the_end_distance)*sin(bound.the_end_angle*PI/180)));
        point2.setPosition(*origin_x + (bound.the_end_distance) * cos(bound.the_end_angle * PI / 180),
                           (*origin_y - (bound.the_end_distance) * sin(bound.the_end_angle * PI / 180)));
        //window.draw(point2);

        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(
                                *origin_x + (bound.the_beginning_distance) * cos(bound.the_beginning_angle * PI / 180),
                                (*origin_y -
                                 (bound.the_beginning_distance) * sin(bound.the_beginning_angle * PI / 180)))),
                        sf::Vertex(
                                sf::Vector2f(*origin_x + (bound.the_end_distance) * cos(bound.the_end_angle * PI / 180),
                                             (*origin_y -
                                              (bound.the_end_distance) * sin(bound.the_end_angle * PI / 180)))),
                };

        window->draw(line, 2, sf::Lines); // Array, size, type

    }

    return false;
}

bool Show::draw_obstacles(sf::RenderWindow *window, uint16_t *origin_x, uint16_t *origin_y) {

    double radius_bound;
    if (!Create_obstacle::list_obstacles.empty()) {
        std::vector<sf::CircleShape> points(Create_obstacle::list_obstacles.size());
        for (int i = 0; i < Create_obstacle::list_obstacles.size(); i++) {
            points[i].setFillColor(sf::Color(10, 100, 200));
            //radius_bound = Create_obstacle::list_obstacles[i].width;
            radius_bound = 10;
            points[i].setRadius(radius_bound);
            points[i].setOrigin(radius_bound, radius_bound);

            //points[i].setPosition((float) (origin_x+Create_obstacle::list_obstacles[i].distance)*cos(Create_obstacle::list_obstacles[i].center_angle*PI/180), (float) (-((origin_y+Create_obstacle::list_obstacles[i].distance)*sin(Create_obstacle::list_obstacles[i].center_angle*PI/180))));
            points[i].setPosition(*origin_x + (Create_obstacle::list_obstacles[i].distance) *
                                              cos(Create_obstacle::list_obstacles[i].center_angle * PI /
                                                  180), *origin_y -
                                                        (Create_obstacle::list_obstacles[i].distance) *
                                                        sin(Create_obstacle::list_obstacles[i].center_angle *
                                                            PI / 180));
            window->draw(points[i]);
        }
    }

    return false;
}

bool Show::draw_all(sf::RenderWindow *window, std::array<DataPoint, Lidar::NBR_DATA> tmp) {

    // On fait tourner le programme tant que la fenêtre n'a pas été fermée
    if (window->isOpen()) {
        // On traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window->pollEvent(event)) {
            // Fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Effacement de la fenêtre (->noir)
        window->clear(sf::Color::Black);

        // Drawing
        uint16_t origin_x, origin_y;
        Show::draw_origin(window, &origin_x, &origin_y);  // Draw origin of the graphe
        Show::draw_data(window, tmp, &origin_x, &origin_y);  // Draw data
        Show::draw_bounds(window, &origin_x, &origin_y);  // Draw bounds of obstacles (line)
        Show::draw_obstacles(window, &origin_x, &origin_y);  // Draw obstacles

        window->display();  // Fin de la frame courante, affichage de tout ce qu'on a dessiné
    }

    return false;
}

