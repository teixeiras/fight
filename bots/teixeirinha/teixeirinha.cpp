#include "teix_robot.h"
// C++ during compilation/linking change the methods name. So we need to path as
// C so the name is the same
extern "C" {
std::shared_ptr<robot_fight::Robot> build_robot();
}

std::shared_ptr<robot_fight::Robot> build_robot() {
    std::cout << "We have a robot" << std::endl;
    return std::make_shared<teixeira::robot::Robot>();
}