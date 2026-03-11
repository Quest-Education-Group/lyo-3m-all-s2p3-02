#include "InspectorNodePropreties.h"
#include <Serialization/SerializeObject.hpp>

#include <iostream>
#include <imgui.h>

bool InspectorNodePropreties::Draw(json& publicDataJson)
{
	bool wasModified = false;
	for (auto& [key, value] : publicDataJson.items())
	{
		ImGui::PushID(key.c_str());

		if (value.is_number_float())
		{
			float floatVal = value.get<float>();
			
			if (ImGui::DragFloat(key.c_str(), &floatVal, 0.1f))
			{
				// Direcly the JSON
				publicDataJson[key] = floatVal;
				wasModified = true;
			}
		}
		else if (value.is_number_integer())
		{
			int intVal = value.get<int>();
			
			if (ImGui::DragInt(key.c_str(), &intVal))
			{
				publicDataJson[key] = intVal;
				wasModified = true;
			}
		}
		else if (value.is_boolean())
		{
			bool boolVal = value.get<bool>();
			
			if (ImGui::Checkbox(key.c_str(), &boolVal))
			{
				publicDataJson[key] = boolVal;
				wasModified = true;
			}
		}
		else if (value.is_string())
		{
			std::string strVal = value.get<std::string>();
			char buffer[256];
			strncpy(buffer, strVal.c_str(), sizeof(buffer));
			ImGui::InputText(key.c_str(), buffer, sizeof(buffer), 32);
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				publicDataJson[key] = std::string(buffer);
				wasModified = true;
			}
		}
		else if (value.is_object()) {
			//if (!m_objectsStatus.contains(key)) {
			//	ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(value["PRIVATE_DATAS"]["TYPE"]);
			//	SerializedObject obj;
			//	outObject->Serialize(obj);
			//	m_objectsJsonData[key] = obj.GetJson();
			//	m_objectsStatus.insert(std::pair<std::string, bool>(key, true));
			//}
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			{
				flags |= ImGuiTreeNodeFlags_Selected;
			}
			bool objOpen = ImGui::TreeNodeEx(key.c_str(), flags);

			if (objOpen)
			{
				bool dataModified = false;
				json& publicdata = publicDataJson[key]["PUBLIC_DATAS"];
				dataModified = Draw(publicdata);
				ImGui::TreePop();
				if (dataModified == true) {
					publicDataJson[key]["PUBLIC_DATAS"] = publicdata;
					wasModified = true;
				}
			}
		}
		ImGui::PopID();
	}

	ImGui::Separator();

	//ImGui::Text("Raw JSON:");
	//std::string jsonStr = publicDataJson.dump(2);
	//ImGui::TextWrapped("%s", jsonStr.c_str());

	return wasModified;
}