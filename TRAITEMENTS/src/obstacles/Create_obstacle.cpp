//
// Created by melanie on 12/9/18.
//
#include <ctgmath>
#include <cmath>
#include <tkInt.h>
#include "obstacles/Create_obstacle.hpp"


std::vector<Obstacle> Create_obstacle::list_obstacles;
std::vector<Bounds> Create_obstacle::list_bounds;


bool Create_obstacle::analyse(const std::vector<std::pair<float, uint16_t>> *currentDataPoints, float step_angle) {

    double gapBtwPoints = 0;
    Bounds bound;
    Obstacle obstacle;
    bool in_obstacle = False;
    list_bounds.clear();
    list_obstacles.clear();

    if (currentDataPoints->at(0).second < DISTANCE_MAX) {
        bound.the_beginning_angle = currentDataPoints->at(0).first;
        bound.the_beginning_distance = currentDataPoints->at(0).second;
        in_obstacle = True;
    }

    for (int i = 1; i < currentDataPoints->size(); i++) {

        gapBtwPoints = sqrt(pow(currentDataPoints->at(i).second, 2) + pow(currentDataPoints->at(i-1).second, 2) -
                            2 * currentDataPoints->at(i).second * currentDataPoints->at(i-1).second *
                            std::cos(abs(PI * step_angle / 180)));  // Al Kashi

        //printf("[%g, %d], [%g %d], ecart: %f \n",currentDataPoints[i-1].angle, currentDataPoints[i-1].distance, currentDataPoints->at(i).angle, currentDataPoints->at(i).distance, gapBtwPoints);



        if (in_obstacle == True &&
            (gapBtwPoints >= MIN_GAP_BTW_OBSTACLES || currentDataPoints->at(i).second > DISTANCE_MAX)) {
            bound.the_end_angle = currentDataPoints->at(i-1).first;
            bound.the_end_distance = currentDataPoints->at(i-1).second;
            list_bounds.push_back(bound);
            //std::cout << "bound [" << bound.the_beginning_angle << ", " << bound.the_end_angle << "] \n";
            in_obstacle = False;
        }
        if (in_obstacle == False &&
            currentDataPoints->at(i).second < DISTANCE_MAX /*&& gapBtwPoints>=MIN_GAP_BTW_OBSTACLES*/) {
            bound.the_beginning_angle = currentDataPoints->at(i).first;
            bound.the_beginning_distance = currentDataPoints->at(i).second;
            in_obstacle = True;
        }
    }
    for (int j = 0; j < list_bounds.size(); j++) {
        obstacle.width = sqrt(pow(list_bounds[j].the_beginning_distance, 2) + pow(list_bounds[j].the_end_distance, 2)
                              - 2 * list_bounds[j].the_beginning_distance * list_bounds[j].the_end_distance *
                                cos(fmodf(list_bounds[j].the_end_angle - list_bounds[j].the_beginning_angle,
                                          (2 * PI))));  // Al Kashi
        if (obstacle.width > MIN_WIDTH) {
            obstacle.center_angle = (list_bounds[j].the_beginning_angle + list_bounds[j].the_end_angle) / 2;
            obstacle.distance = (list_bounds[j].the_end_distance + list_bounds[j].the_beginning_distance) / 2;
            //std::cout << obstacle.center_angle << ": " << obstacle.distance << ": " << obstacle.width << "\n";
            list_obstacles.push_back(obstacle);
        }
    }
    return 1;
}