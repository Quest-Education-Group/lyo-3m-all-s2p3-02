#include "AssetLoading/AssetLoader.h"
#include "AssetLoading/FBXLoader.h"

#include <Mesh.h>
#include <Geometry.h>
#include <Logger.hpp>

uptr<Scene> AssetLoader::LoadSceneFromFile(std::string const& path, AssetLoader::FileType type)
{
	switch (type)
	{
	case AssetLoader::FBX:
		return LoadFBXScene(path);
	default:
		Logger::LogWithLevel(LogLevel::ERROR, "Unable to load " + path + ". Extension File not supported");
		return nullptr;
	}
	Logger::LogWithLevel(LogLevel::ERROR, "File : " + path +" not loaded");
	return nullptr;
}


uptr<Scene> AssetLoader::LoadFBXScene(std::string const& path)
{
	sptr<FBXLoader::SceneData> fbxScene = FBXLoader::LoadFile(path);
	Scene outScene = {};
	outScene.meshes.reserve(fbxScene->meshs.size());
	for (uint32 i = 0; i < fbxScene->nodes.size(); ++i)
	{
		for (uint32 meshCount = 0; meshCount < fbxScene->nodes[i]->meshesIndex.size(); ++meshCount)
		{
			FBXLoader::Mesh mesh = *fbxScene->meshs[fbxScene->nodes[i]->meshesIndex[meshCount]];
			Geometry geo = Geometry(mesh.vertices, mesh.indices);
			std::vector<sptr<Texture>> texts = {};
			std::vector<Texture*> meshcreationTexts = {};
			FBXLoader::Material meshMat = {};

			if (fbxScene->textures.size() != 0)
			{
				meshMat = fbxScene->textures[mesh.matIndex];
				for (std::map<TextureMaterialType, std::string>::iterator it = meshMat.textures.begin(); it != meshMat.textures.end(); ++it)
				{
					sptr<Texture> text = std::make_shared<Texture>(Texture(it->second, TextureType::TYPE_2D, it->first));
					texts.push_back(text);
					meshcreationTexts.push_back(text.get());
				}
			}

			if (fbxScene->textures.size() == 0 || meshMat.textures.size() == 0)
			{
				sptr<Texture> text = std::make_shared<Texture>("res/textures/NormalMap.png", TextureType::TYPE_2D, TextureMaterialType::NORMAL);
				texts.push_back(text);
				meshcreationTexts.push_back(text.get());
				sptr<Texture> text2 = std::make_shared<Texture>("res/textures/diffuse.jpg", TextureType::TYPE_2D, TextureMaterialType::DIFFUSE);
				texts.push_back(text2);
				meshcreationTexts.push_back(text2.get());
				sptr<Texture> text3 =std::make_shared<Texture>("res/textures/specular.jpg", TextureType::TYPE_2D, TextureMaterialType::SPECULAR);
				texts.push_back(text3);
				meshcreationTexts.push_back(text3.get());

			}

			glm::mat4x4 mat = fbxScene->nodes[i]->transform;
			//mat = glm::scale(mat, { 0.1f,0.1f,0.1f });
			SceneMeshs outMesh = {};
			outMesh.mesh = std::make_shared<Mesh>(geo, meshcreationTexts, mat);
			outMesh.textureOfMeshes = texts;

			outScene.meshes.push_back(outMesh);
			meshcreationTexts.clear();
		}
	}
	if (fbxScene->lights.size() > 0)
		outScene.lights = fbxScene->lights;

	return std::make_unique<Scene>(outScene);
}

