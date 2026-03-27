#ifndef FOUNDRY_FBX_LOADER_H__
#define FOUNDRY_FBX_LOADER_H__

#include <string>
#include <map>
#include <vector>
#include <Define.h>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Texture.h>
#include <Color.h>
#include <Geometry.h>
#include <Passes/LightPass.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class FBXLoader
{
public:

	struct VertexWeight
	{
		int32 vertexIndex;
		float vertexWieght;
	};

	struct Bone
	{
		glm::mat4x4 positionInMesh;
		std::vector<VertexWeight> vertexWeight;
	};

	struct Node
	{
		std::string name;
		glm::mat4x4 transform = glm::mat4x4{ 1.0f };
		int32 parent = -1;
		std::vector<int32> children;
		std::vector<std::string> meshesNames;
	};

	struct AnimationChannel
	{
		struct FrameVec3
		{
			float time;
			glm::vec3 vec;
		};
		struct FrameQuat
		{
			float time;
			glm::quat quaternion;
		};
		std::vector<FrameVec3> positionKeys;
		std::vector<FrameQuat> rotationKeys;
		std::vector<FrameVec3> scalingKeys;
	};

	struct Animation
	{
		std::string name;
		float duration;
		std::vector<AnimationChannel> animationTransform;
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<uint32> indices;
		std::vector<Bone> bones;
		
		int32 matIndex = -1;
	};

	struct Material
	{
		std::map<TextureMaterialType,std::string> textures;
	};

	struct SceneData
	{
		std::vector<Node> nodes;
		std::map<std::string,Mesh> meshs;
		std::vector<Material> textures;
		std::vector<Light> lights;
		std::vector<Animation> animations;

	};

	static uptr<SceneData> LoadFile(std::string const& path);
private:
	static uint32 BuildNodes(aiScene const* pScene, aiNode const* pNode, int32 parentIndex, SceneData& outData);
	static void BuildMeshs(aiScene const* pScene, SceneData& outData);
	static void BuildMaterials(aiScene const* pScene, SceneData& outData);
	static void BuildLights(aiScene const* pScene, SceneData& outData);
	static void BuildBones(aiScene const* pScene, SceneData& outData);
	static void BuildAnimations(aiScene const* pScene, SceneData& outData);
	static void BuildAnimationsChannles(aiAnimation const* pAnim, Animation& outAnim, uint32 channelID);

private:
	inline static aiTextureType m_sTexTypes[] = {
			aiTextureType_DIFFUSE,
			aiTextureType_SPECULAR,
			aiTextureType_NORMALS,
			aiTextureType_HEIGHT,
			aiTextureType_EMISSIVE
		};


	inline static std::unordered_map<std::string, SceneData> m_loadedFiles = {};
};


#endif