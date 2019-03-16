#include "Lidar.hpp"

bool Lidar::connect(const std::string &ip, int port) {}

bool Lidar::start() {}

const std::array<std::pair<float, uint16_t>, Lidar::NBR_DATA> &Lidar::getDataPoints() const {}

void Lidar::update() {}

void Lidar::close() {}
