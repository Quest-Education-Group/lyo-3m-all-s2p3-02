#ifndef FOUNDRY_ASSET_STRUCT_H__
#define FOUNDRY_ASSET_STRUCT_H__

#include <vector>
#include <string>
#include <Mesh.h>
#include <Texture.h>
#include <Passes/LightPass.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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

struct SceneData
{
	std::vector<sptr<Mesh>> meshes;
	std::vector<Light> lights;
	std::vector<Animation> animations;
	std::vector<sptr<Texture>> allTextures;
};

#endif // !FOUNDRY_ASSET_STRUCT_H__
