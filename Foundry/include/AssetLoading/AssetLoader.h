#ifndef FOUNDRY_ASSET_LOADER_H__
#define FOUNDRY_ASSET_LOADER_H__

// need struct of Objects
#include <string>
#include <Define.h>

struct SceneData
{};

class AssetLoader
{
public:

	uptr<SceneData> LoadFile(std::string const& filePath);
	// Load OBJ
	// Load Anim
private:
	uptr<SceneData> LoadFBXFile(std::string const& filePath);
	uptr<SceneData> LoadOBJFile(std::string const& filePath);

	

private:


};


#endif