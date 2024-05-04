#include <dlfcn.h>
#include <robot.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <thread>
#include <tuple>
#include <variant>

#include "headers/arena.h"
#include "headers/screen.h"
std::string libext = "so";

// multiple variables storage - https://en.cppreference.com/w/cpp/utility/tuple
typedef std::tuple<std::string, std::string, bool, std::string> ParametersType;

// https://www.bogotobogo.com/cplusplus/valuevsreference.php
// argc the elements is copied into the stack of the new procedure, any change will not go out
// argv the pointer is copied, but not the content, can only change the content pointed
// arena only the reference is passed, any change on this object will reflect outside
void ParseArguments(int argc, char** argv, Arena& arena) {
    std::map<std::string, std::string> arguments;
    std::list<ParametersType> parameters = {{"r", "robot", true, "Add new robot, can add multiples times. Expect the path for the object"},
                                            {"h", "help", false, "Show the menu for help"}};
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);

        auto first = parameters.begin();
        // std::find_if
        while ((first = std::find_if(first, end(parameters), [&argv, &i, &first, &arg](ParametersType param) {
                    return (arg == "-" + std::get<0>(*first) || arg == "--" + std::get<1>(*first));
                })) != parameters.end()) {
            std::string shortName, completeName, help;
            bool hasValue;
            // std::tie to retrieve at once multiple arguments -https://en.cppreference.com/w/cpp/utility/tuple/tie
            std::tie(shortName, completeName, hasValue, help) = *first;
            std::cout << "Parameter " << shortName << std::endl;

            if (shortName == "r") {
                if (argc >= i + 1) {
                    std::string robotPath(argv[i + 1]);
                    std::cout << "Loading robot from " << robotPath << std::endl;

                    arena.LoadRobot(robotPath);
                }
            } else if (shortName == "h") {
                std::cout << "Usage: " << argv[0] << " [options]\n";
                std::cout << "Options:\n";
                for (auto params : parameters) { std::cout << " -" << std::get<0>(params) << ", --" << std::get<1>(params) << " " << std::get<3>(params); }
            }
            first++;
        }
    }
}
int main(int argc, char** argv) {
    // https://0x00sec.org/t/c-dynamic-loading-of-shared-objects-at-runtime/1498
    Arena arena;
    ParseArguments(argc, argv, arena);
    std::thread timer([&arena]() {
        bool exit = false;
        while (!exit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            arena.Cycle();
        }

        // Or call to function, or whatever you want
    });
    Screen::Initialize();
    // code to do while waiting here.
    timer.detach();
    Screen::WaitForInput();
    return 0;
}