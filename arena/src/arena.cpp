#include "headers/arena.h"

#include <dlfcn.h>
typedef std::shared_ptr<robot_fight::Robot> (*buildRobot)();

using namespace robot_fight;
void Arena::LoadRobot(std::string path) {
    void* myso = dlopen(path.c_str(), RTLD_NOW);
    // You can see the methods that are defined using nm -gC binaries
    auto func = reinterpret_cast<buildRobot>(dlsym(myso, "build_robot"));
    if (!func) {
        std::cerr << "Unable to get symbol: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
    AddRobot(func());
    dlclose(myso);
}
void Arena::AddRobot(std::shared_ptr<robot_fight::Robot> robot) {
    if (isValid(robot)) {
        robots.push_back(robot);
    } else {
        std::cerr << "This robot is not valid: " << *robot;
    }
}
bool Arena::isValid(std::shared_ptr<robot_fight::Robot> robot) {
    return true;
}
void Arena::GenerateBoard() {}
void Arena::Cycle() {}
char Cell::toChar() {
    return '0';
}