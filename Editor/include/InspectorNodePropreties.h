#ifndef __INSPECTOR_H
#define __INSPECTOR_H

#include <string>
#include <Serialization/json.hpp>
#include <map>

using json = nlohmann::json;

class InspectorNodePropreties {
public:
    bool Draw(json& publicDataJson);
    void SetWindow(int width, int height) { m_screenWidth = width; m_screenHeight = height; }

    void SetInspectedObject(json& object);
    bool IsModified();

    void Draw();

private:
    json inspectedObject;

    int m_screenWidth = 0;
    int m_screenHeight = 0;
    std::map<std::string, json> m_objectsJsonData;
    std::map<std::string, bool> m_objectsStatus;

};

#endif