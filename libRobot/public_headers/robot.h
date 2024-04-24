#pragma once
#include <iostream>
#include <list>
#include <memory>

#include "arm.h"
#include "bonus.h"
#include "land/armor_piece.h"
using namespace std;
#define MAX_ATTRIBUTE 200
// we use namespace to stop collision between projects
// https://en.cppreference.com/w/cpp/language/namespace
namespace robot_fight {
    class Robot {
        Attributes baseAttribute;
        std::list<Bonus> bonus;
        std::unique_ptr<Arm> leftArm;
        std::unique_ptr<Arm> rightArm;

       protected:
        void addBonus(Bonus bonus);
        void setLeftArm(std::unique_ptr<Arm> leftArm);
        void setRigtArm(std::unique_ptr<Arm> leftArm);
        Attributes& getMutableBaseAttribute();

       public:
        Robot() {}
        // https://isocpp.org/wiki/faq/const-correctness#ptr-to-const
        Attributes* const getBaseAttribute();

        // https://en.cppreference.com/w/cpp/language/friend
        // You use friend to make possible an external method to access private elements
        friend ostream& operator<<(ostream& os, const Robot& dt);
    };
    // https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/
    // Overloading ostream so it's cleaner to print object details
    // https://en.cppreference.com/w/cpp/language/operators
    // Operators possible to overload:
    //+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> ( ) [ ]
    extern ostream& operator<<(ostream& os, const Robot& robot);
    extern ostream& operator<<(ostream& os, const std::list<Bonus>& bonus_list);
}  // namespace robot_fight
