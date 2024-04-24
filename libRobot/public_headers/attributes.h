#include <list>
#include <map>
namespace robot_fight {
    class AttributesEnum {
       public:
        enum Value { WEIGHT, SPEED, STRENGTH, ARMOR, LIFE };
        AttributesEnum() = default;
        constexpr AttributesEnum(Value value) : value(value) {}

        constexpr operator Value() const {
            return value;
        }
        explicit operator bool() const = delete;
        constexpr bool operator==(AttributesEnum a) const {
            return value == a.value;
        }
        constexpr bool operator!=(AttributesEnum a) const {
            return value != a.value;
        }

       private:
        Value value;
    };

    class Attributes {
        std::map<AttributesEnum, unsigned int> attributes_list;

       public:
        Attributes() {}
        unsigned int GetAttribute(AttributesEnum attrs) {
            return attributes_list[attrs];
        }

        void setAttribute(AttributesEnum attr, unsigned int value) {
            attributes_list[attr] = value;
        }
    };
}  // namespace robot_fight