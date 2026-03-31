#ifndef FOUNDRY_ASSET_STRUCT_H__
#define FOUNDRY_ASSET_STRUCT_H__

#include "AnimationStructs.h"

#include <Define.h>
#include <vector>
#include <string>
#include <Mesh.h>
#include <Texture.h>
#include <Passes/LightPass.h>
#include <glm/glm.hpp>


enum SceneNodeType
{
	GLOBAL,
	MESH,
	BONE,
};

struct SceneNode
{
	SceneNodeType type = GLOBAL;

	std::string name;
	glm::mat4 transform;

	int32 boneIndexInMesh = -1;
	int32 parent = -1;
	std::vector<uint32> meshesIndex;
	std::vector<uint32> children;
};

struct SceneData
{
	sptr<SceneNode> rootNode;
	bool isAnimated = false;
	std::vector<sptr<SceneNode>> allNode;
	std::vector<sptr<Light>> alllights;
	std::vector<sptr<Animation>> animations;
	std::vector<sptr<Mesh>> allMesh;
	std::vector<sptr<Texture>> allTextures;
};

#endif // !FOUNDRY_ASSET_STRUCT_H__
