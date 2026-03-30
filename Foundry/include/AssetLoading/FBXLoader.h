#ifndef FOUNDRY_FBX_LOADER_H__
#define FOUNDRY_FBX_LOADER_H__

#include "AssetLoading/AssetsStructs.h"

#include <Define.h>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>
#include <Texture.h>
#include <Geometry.h>

struct aiMesh;
struct aiScene;
struct aiNode;
struct aiAnimation;

class FBXLoader
{
public:

	struct Node
	{
		std::string name;
		glm::mat4x4 transform = glm::mat4x4{ 1.0f };
		int32 parent = -1;
		std::vector<int32> children;
		std::vector<uint32> meshesIndex;
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<sptr<SceneBone>> bones;
		int32 matIndex = -1;
	};

	struct Material
	{
		std::map<TextureMaterialType,std::string> textures;
	};

	struct SceneData
	{
		std::vector<sptr<Node>> nodes;
		std::vector<sptr<Mesh>> meshs;
		std::vector<Material> textures;
		std::vector<Light> lights;
		std::vector<Animation> animations;
	};

	static sptr<SceneData> LoadFile(std::string const& path);
private:
	static uint32 BuildNodes(aiScene const* pScene, aiNode const* pNode, int32 parentIndex, SceneData& outData);
	static void BuildMeshs(aiScene const* pScene, SceneData& outData);
	static void BuildMaterials(aiScene const* pScene, SceneData& outData);
	static void BuildLights(aiScene const* pScene, SceneData& outData);
	static void BuildBones(aiMesh const* pScene, Mesh& outData);
	static void BuildAnimations(aiScene const* pScene, SceneData& outData);
	static void BuildAnimationsChannles(aiAnimation const* pAnim, Animation& outAnim, uint32 channelID);

private:
	static uint8 m_sTexTypes[];
	inline static std::unordered_map<std::string, sptr<SceneData>> m_loadedFiles = {};
};


#endif