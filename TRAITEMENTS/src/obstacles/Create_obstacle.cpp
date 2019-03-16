//
// Created by melanie on 12/9/18.
//
#include <ctgmath>
#include <cmath>
#include <tkInt.h>
#include "../../include/obstacles/Create_obstacle.hpp"
#include "../../../TIM_SICK/lidar/TIM561.h"


std::vector<Obstacle> Create_obstacle::list_obstacles;
std::vector<Bounds> Create_obstacle::list_bounds;


bool Create_obstacle::analyse(std::array<DataPoint, TIM561::NBR_DATA> currentDataPoints) {

    double gapBtwPoints = 0;
    Bounds bound;
    Obstacle obstacle;
    bool in_obstacle = False;
    list_bounds.clear();
    list_obstacles.clear();

    if (currentDataPoints[0].distance < DISTANCE_MAX) {
        bound.the_beginning_angle = currentDataPoints[0].angle;
        bound.the_beginning_distance = currentDataPoints[0].distance;
        in_obstacle = True;
    }

    for (int i = 1; i < TIM561::NBR_DATA; i++) {

        gapBtwPoints = sqrt(pow(currentDataPoints[i].distance, 2) + pow(currentDataPoints[i - 1].distance, 2) -
                            2 * currentDataPoints[i].distance * currentDataPoints[i - 1].distance *
                            std::cos(abs(PI * TIM561::STEP_ANGLE / 180)));  // Al Kashi

        //printf("[%g, %d], [%g %d], ecart: %f \n",currentDataPoints[i-1].angle, currentDataPoints[i-1].distance, currentDataPoints[i].angle, currentDataPoints[i].distance, gapBtwPoints);



        if (in_obstacle == True &&
            (gapBtwPoints >= MIN_GAP_BTW_OBSTACLES || currentDataPoints[i].distance > DISTANCE_MAX)) {
            bound.the_end_angle = currentDataPoints[i - 1].angle;
            bound.the_end_distance = currentDataPoints[i - 1].distance;
            list_bounds.push_back(bound);
            //std::cout << "bound [" << bound.the_beginning_angle << ", " << bound.the_end_angle << "] \n";
            in_obstacle = False;
        }
        if (in_obstacle == False &&
            currentDataPoints[i].distance < DISTANCE_MAX /*&& gapBtwPoints>=MIN_GAP_BTW_OBSTACLES*/) {
            bound.the_beginning_angle = currentDataPoints[i].angle;
            bound.the_beginning_distance = currentDataPoints[i].distance;
            in_obstacle = True;
        }

//        for (Bounds bounds : list_bounds) {
//            std::cout << "[" << bounds.the_end_angle << ", " << bounds.the_end_angle << "] ";
//        }
//        std::cout << "\n";
        //Obstacle o = {.center_angle=0, .distance=0};
        //list_obstacles.push_back(o);
    }
//    for (Bounds bound : list_bounds) {
//            std::cout << "[" << bound.the_end_angle << ", " << bound.the_end_angle << "] \n";
//    }
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
    std::cout << "\n\n\n";
    return 1;
}