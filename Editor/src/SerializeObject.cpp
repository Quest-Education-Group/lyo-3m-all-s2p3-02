
#include "SerializeObject.h"

#include <fstream>
#include <map>


void SerializeObject::Save(std::string outPath, uptr<Node>& root)
{
	json jsonRoot;
	jsonRoot["Root"] = json::object();
	std::map<std::string, std::string> mapDatas = root.get()->Serialize();
	jsonRoot["Root"]["Children"] = json::array();
	for (uint8 i = 0; i < root.get()->GetChildCount();i++)
	{
		jsonRoot["Root"]["Children"][i] = ParseNodeToJson(root.get()->GetChild(i));
	}
	jsonRoot["Root"]["Datas"] = mapDatas;
	jsonRoot["Root"]["TYPE"] = 0;

	std::fstream File;
	File.open("../res/" + outPath, std::ios::out);
	File << jsonRoot;
	File.close();
}

json SerializeObject::ParseNodeToJson(Node& pNode)
{
	json objectChildren = json::object();
	objectChildren["TYPE"] = GetTypeFromNode(&pNode);
	std::map<std::string, std::string> mapDatas = pNode.Serialize();
	objectChildren["Datas"] = mapDatas;
	objectChildren["Children"] = json::array();
	for (uint8 i = 0; i < pNode.GetChildCount(); i++)
	{
		objectChildren["Children"][i] = ParseNodeToJson(pNode.GetChild(i));
	}

	return objectChildren;
}

uptr<Node> SerializeObject::LoadFromJson(std::string path)
{
	//TODO replace with SceneTree
	// Read File nlhoman aled

	std::fstream file;
	file.open("../res/" + path, std::ios::in);
	json jsonFile{ json::parse(file) };

	uptr<Node> firstNode = Node::CreateNode<Node>("Node");
	std::map<std::string, std::string> tempMap;
	jsonFile["Root"]["Datas"].get_to(tempMap);
	firstNode.get()->Deserialize(tempMap);
	json childrenList = jsonFile["Root"]["Children"];
	for (uint8 i = 0; i < childrenList.size(); i++)
	{
		json child = childrenList[i];
		firstNode.get()->AddChild(ParseNodeData(child));
	}

	file.close();

	return std::move(firstNode);
}

uptr<Node> SerializeObject::ParseNodeData(json data)
{
	int nodeType = data["TYPE"];
	std::map<std::string, std::string> tempMap;
	data["Datas"].get_to(tempMap);

	uptr<Node> newNode = CreateNodeFromType((Type)nodeType,tempMap["m_name"]);
	newNode.get()->Deserialize(tempMap);
	json childrenList = data["Children"];
	for (uint8 i = 0; i < childrenList.size(); i++)
	{
		newNode.get()->AddChild(ParseNodeData(childrenList[i]));
	}
	return std::move(newNode);
}

uptr<Node> SerializeObject::CreateNodeFromType(Type nodeType, std::string const& name)
{
	
	switch (nodeType)
	{
	case Type::NODE:
		return std::move(Node::CreateNode<Node>(name));
		break;
	default:
		break;
	}

	// TODO: insérer une instruction return ici
}

Type SerializeObject::GetTypeFromNode(Node* pNode)
{
	if (dynamic_cast<Node*>(pNode))
		return Type::NODE;
}

