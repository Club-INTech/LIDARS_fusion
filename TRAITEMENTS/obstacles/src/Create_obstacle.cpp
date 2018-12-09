//
// Created by melanie on 12/9/18.
//
#include <ctgmath>
#include <cmath>
#include <tkInt.h>
#include "../include/Create_obstacle.hpp"
#include "../../../TIM_SICK/lidar/include/TIM561.h"



std::vector<Obstacle> Create_obstacle::list_obstacles;
std::vector<Bounds> Create_obstacle::list_bounds;


bool Create_obstacle::analyse(std::array<DataPoint,TIM561::NBR_DATA> currentDataPoints) {
    double gapBtwPoints = 0;
    Bounds bound;
    bool in_obstacle = False;
    list_bounds.clear();

    if(currentDataPoints[0].distance < DISTANCE_MAX) {
        bound.the_beginning = currentDataPoints[0].angle;
        in_obstacle = True;
    }

    for (int i=1; i<TIM561::NBR_DATA; i++) {

        gapBtwPoints = sqrt(pow(currentDataPoints[i].distance,2) + pow(currentDataPoints[i-1].distance,2) - 2 * currentDataPoints[i].distance * currentDataPoints[i-1].distance * std::cos(abs(PI * TIM561::STEP_ANGLE / 180)));  // Al Kashi

        //printf("[%g, %d], [%g %d], ecart: %f \n",currentDataPoints[i-1].angle, currentDataPoints[i-1].distance, currentDataPoints[i].angle, currentDataPoints[i].distance, gapBtwPoints);



        if (in_obstacle==True && (gapBtwPoints>=MIN_GAP_BTW_OBSTACLES || currentDataPoints[i].distance>DISTANCE_MAX)) {
            bound.the_end=currentDataPoints[i-1].angle;
            list_bounds.push_back(bound);
            std::cout << "bound [" << bound.the_beginning << ", " << bound.the_end << "] \n";
            in_obstacle = False;
        }
        if (in_obstacle==False && currentDataPoints[i].distance<DISTANCE_MAX /*&& gapBtwPoints>=MIN_GAP_BTW_OBSTACLES*/) {
            bound.the_beginning=currentDataPoints[i].angle;
            in_obstacle = True;
        }

//        for (Bounds bounds : list_bounds) {
//            std::cout << "[" << bounds.the_end << ", " << bounds.the_end << "] ";
//        }
//        std::cout << "\n";
        //Obstacle o = {.center_angle=0, .distance=0};
        //list_obstacles.push_back(o);
    }
//    for (Bounds bound : list_bounds) {
//            std::cout << "[" << bound.the_end << ", " << bound.the_end << "] \n";
//    }
    std::cout << "\n\n\n";
    return 1;
}