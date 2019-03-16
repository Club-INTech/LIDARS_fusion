#ifndef LIDARS_FUSION_LIDAR_HPP
#define LIDARS_FUSION_LIDAR_HPP

#include <string>
#include <array>
#include "LIDARS/TIM561/include/lidar/DataPoint.h"

class Lidar {

public:
    constexpr static uint16_t NBR_DATA = 320;

    virtual bool connect(const std::string &ip, int port)=0;

    virtual bool start()=0;

    virtual const std::array<std::pair<float, uint16_t>, NBR_DATA> &getDataPoints() const=0;

    virtual void update()=0;

    virtual void close()=0;
};


#endif //LIDARS_FUSION_LIDAR_HPP
