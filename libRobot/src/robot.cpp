#include "robot.h"
namespace robot_fight {
    ostream& operator<<(ostream& os, const Robot& robot) {
        os << "Active Bonues" << robot;  // We can access robot because is a friend
        return os;
    }
    ostream& operator<<(ostream& os, const std::list<Bonus>& bonus_list) {
        // We can make operator even from non friends objects
    }

    void Robot::addBonus(Bonus bonus) {}
    void Robot::setLeftArm(std::unique_ptr<Arm> leftArm) {
        this->leftArm = std::move(leftArm);
    }
    void Robot::setRigtArm(std::unique_ptr<Arm> rightArm) {
        this->rightArm = std::move(rightArm);
    }
    Attributes& Robot::getMutableBaseAttribute() {
        return baseAttribute;
    }
    Attributes* const Robot::getBaseAttribute() {
        return &baseAttribute;
    }

}  // namespace robot_fight