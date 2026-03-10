#ifndef __INSPECTOR_H
#define __INSPECTOR_H

#include <variant>
#include <string>
class Instector {
	enum class PropertyType {
        INT,
        FLOAT,
        BOOL,
        STRING,
        VEC2,
        VEC3,
        COLOR,
        ENUM
	};

    using PropertyValue = std::variant<
        int,
        float,
        bool,
        std::string,
        std::pair<float, float>,      // Vec2
        std::tuple<float, float, float>, // Vec3
        std::tuple<float, float, float, float> // Vec4
    >;

        

};

#endif