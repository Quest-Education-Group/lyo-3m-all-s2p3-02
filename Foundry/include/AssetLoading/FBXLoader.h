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

	struct FBXMesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<glm::mat4> bones;
		int32 matIndex = -1;
	};

	struct Material
	{
		std::map<TextureMaterialType,std::string> textures;
	};

	static sptr<SceneData> LoadFile(std::string const& path);
private:
	static void BuildMeshs(aiScene const* pScene, SceneData& outData);
	static void BuildMaterials(aiScene const* pScene, SceneData& outData);
	static void BuildLights(aiScene const* pScene, SceneData& outData);
	static void BuildBones(SceneData const& scene,aiMesh const* pMesh, std::vector<Vertex>& vertices, std::vector<uint32>& indices, std::vector<glm::mat4>& bones);

	static void BuildAnimations(aiScene const* pScene, SceneData& outData);
	static void BuildAnimationsChannles(aiAnimation const* pAnim, Animation& outAnim, uint32 channelID);

	static uint32 BuildNodesTree(aiScene const* pScene, aiNode const* pNode, int32 parentIndex, SceneData& outData);

	static void LoadTextures(SceneData& outData,std::vector<sptr<Texture>>& vect, std::vector<Texture*>& tempVect, uint32 matIndex);
	static sptr<SceneData> ConvertInGlobalSceneData(SceneData& outData);

private:
	static uint8 m_sTexTypes[];
	inline static std::unordered_map<std::string, sptr<SceneData>> m_loadedFiles = {};
};


#endif