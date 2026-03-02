#ifndef _SERIALIZEOBJECT__H
#define _SERIALIZEOBJECT__H

#include "json.hpp"

#include <vector>
#include <string>
#include <map>

class Node;
using json = nlohmann::json;

/*
	* Add Every node class usable in the editor in this enum
	* Add Type to Class Converter in CreateNodeFromType 
	* And Class to Type Converter in GetTypeFromNode functions
*/
enum class Type : uint8
{
	NODE,
};

/*
	* Object to Convert datas from Editor to Foundry
	* Object use to save sceneTree Data from Editor
	* Object use to use SaveFile(.json) in Foundry
*/
class SerializeObject
{

public:
	// TODO replace Node with SceneTree
	static void Save(std::string outPath, uptr<Node>& root);
	static uptr<Node> LoadFromJson(std::string path);

private:
	json ParseNodeToJson(uptr<Node>& pNode, json jsonData);
	Type GetTypeFromNode(uptr<Node>& pNode);

	uptr<Node> ParseNodeData(json jsonData);
	uptr<Node> CreateNodeFromType(Type nodeType);
};

#endif

