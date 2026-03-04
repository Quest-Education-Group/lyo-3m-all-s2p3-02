#ifndef _EDITORSERIALIZER__H
#define _EDITORSERIALIZER__H

#include "json.hpp"

#include <Define.h>
#include <Node.h>
#include <string>

using json = nlohmann::json;

/*
	* Object to Convert datas from Editor to Foundry
	* Object use to save sceneTree Data from Editor
	* Object use to use SaveFile(.json) in Foundry
*/

enum class Type : uint8 {
	NODE
};
class EditorSerializer
{

public:

	static void Save(std::string outPath, uptr<Node>& root);
	static uptr<Node> LoadFromJson(std::string path);

private:
};

#endif

