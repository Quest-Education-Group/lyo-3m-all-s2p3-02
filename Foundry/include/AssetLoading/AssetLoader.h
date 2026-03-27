#ifndef FOUNDRY_ASSET_LOADER_H__
#define FOUNDRY_ASSET_LOADER_H__

#include <string>
#include <vector>
#include <Define.h>
#include <Mesh.h>
#include <Texture.h>
#include <Passes/LightPass.h>
#include <Expected.hpp>

struct SceneMeshs
{
	sptr<Mesh> mesh;
	std::vector<sptr<Texture>> textureOfMeshes;
};

struct Scene
{
	std::vector<SceneMeshs> meshes;
	std::vector<Light> lights;
	// anims
};

class AssetLoader
{
public:
	enum FileType
	{
		FBX,
	};
	static uptr<Scene> LoadSceneFromFile(std::string const& path, AssetLoader::FileType type);
	
private:
	static uptr<Scene> LoadFBXScene(std::string const& path);
};


#endif //! FOUNDRY_ASSET_LOADER_H__