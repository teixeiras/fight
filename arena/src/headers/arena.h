// https://includeguardian.io/article/pragma-once-vs-ifndef
// https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html
// Pragma can also pass arguments for compiler for optimizations per object file.
#pragma once
#include <robot.h>
// https://jmmv.dev/2013/12/header-files-avoid-c-using-directives.html
// You shouldn't use using inside headers since it can bring naming caos into files that include this
// files
// using namespace robot_fight; don't make using on headers

class Cell {};
class Arena {
    // since we are out of namespace, we need to refer the namespace
    std::list<std::shared_ptr<robot_fight::Robot>> robots;
    // https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization
    Cell board[100][100];
    void AddRobot(std::shared_ptr<robot_fight::Robot> robot);
    bool isValid(std::shared_ptr<robot_fight::Robot> robot);

   public:
    void LoadRobot(std::string path);
    void GenerateBoard();
    void Cycle();
};