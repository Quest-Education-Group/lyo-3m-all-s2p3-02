#ifndef __INSPECTOR_H
#define __INSPECTOR_H

#include <variant>
#include <string>
#include <Node.h>



class InspectorNodePropreties {
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
public:
    void Draw(SerializedObject& selected);
    void SetWindow(int width, int height) { m_screenWidth, m_screenHeight = width, height; }
private:
    int m_screenWidth;
    int m_screenHeight;

};

#endif