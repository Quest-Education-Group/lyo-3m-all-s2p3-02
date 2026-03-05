
#include "EditorSerializer.h"
#include "SerializeObject.hpp"

#include <fstream>
#include <map>


void EditorSerializer::Save(std::string outPath, uptr<Node>& root)
{
	json jsonRoot;
	SerializedObject object;
	object.SetType("Node");
	root.get()->Serialize(object);
	jsonRoot["Root"] = object.m_elementsInSerializedObject;

	std::fstream File;
	File.open("../res/" + outPath, std::ios::out);
	File << jsonRoot;
	File.close();
}
//
//json EditorSerializer::ParseNodeToJson(Node& pNode)
//{
//	json objectChildren = json::object();
//	SerializedObject object = {};
//	pNode.Serialize(object);
//	objectChildren = object.m_elementsInSerializedObject;
//	return objectChildren;
//}

uptr<Node> EditorSerializer::LoadFromJson(std::string path)
{
	//TODO replace with SceneTree
	// Read File nlhoman aled

	std::fstream file;
	file.open("../res/" + path, std::ios::in);
	json jsonFile{ json::parse(file) };
	file.close();

	SerializedObject object = {};
	object.m_elementsInSerializedObject = jsonFile["Root"];
	uptr<Node> firstNode = Node::CreateNode<Node>("Node");
	firstNode.get()->Deserialize(object);
	return std::move(firstNode);
}
//
//uptr<Node> EditorSerializer::ParseNodeData(json data)
//{
//	int nodeType = data["TYPE"];
//	std::map<std::string, std::string> tempMap;
//	data["Datas"].get_to(tempMap);
//	SerializeData datas = SerializeData();
//	datas.m_datas = tempMap;
//
//	uptr<Node> newNode = CreateNodeFromType((Type)nodeType,tempMap["m_name"]);
//	newNode.get()->DeserializeVariables(datas);
//	json childrenList = data["Children"];
//	for (uint8 i = 0; i < childrenList.size(); i++)
//	{
//		newNode.get()->AddChild(ParseNodeData(childrenList[i]));
//	}
//	return std::move(newNode);
//}
//
//uptr<Node> EditorSerializer::CreateNodeFromType(Type nodeType, std::string const& name)
//{
//	
//	switch (nodeType)
//	{
//	case Type::NODE:
//		return std::move(Node::CreateNode<Node>(name));
//		break;
//	default:
//		break;
//	}
//
//	// TODO: insérer une instruction return ici
//}
//
//Type EditorSerializer::GetTypeFromNode(Node* pNode)
//{
//	if (dynamic_cast<Node*>(pNode))
//		return Type::NODE;
//}
//
