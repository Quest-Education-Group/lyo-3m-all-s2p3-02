#include "AssetLoading/FBXLoader.h"

#include <fstream>
#include <Mesh.h>
#include <Logger.hpp>


glm::mat4x4 AIMatrixToGLMMatrix(aiMatrix4x4 const& matrix)
{
    glm::mat4x4 out = {};
    memcpy(&out, &matrix, sizeof(aiMatrix4x4));
    return glm::transpose(out);
}


uptr<FBXLoader::SceneData> FBXLoader::LoadFile(std::string const& path)
{
    Assimp::Importer importer = Assimp::Importer();
    int importFlags = aiProcess_CalcTangentSpace |
                         aiProcess_Triangulate |
                         aiProcess_JoinIdenticalVertices |
                         aiProcess_SortByPType;

    aiScene const* pAScene = importer.ReadFile(path.c_str(), importFlags);

    if (pAScene == nullptr)
    {
        Logger::LogWithLevel(LogLevel::ERROR, "Failed Loading " + path + " file");
        return nullptr;
    }
    
    FBXLoader::SceneData uScene = {};

    BuildNodes(pAScene, pAScene->mRootNode, -1, uScene);
    BuildMeshs(pAScene, uScene);
    BuildMaterials(pAScene, uScene);
    BuildLights(pAScene, uScene);
    BuildBones(pAScene, uScene);
    BuildAnimations(pAScene, uScene);

    m_loadedFiles[path] = uScene;

    return std::make_unique<FBXLoader::SceneData>(uScene);
}


uint32 FBXLoader::BuildNodes(aiScene const* pScene, aiNode const* pNode, int32 parentIndex, SceneData& outData)
{
    Node node;
    node.parent = parentIndex;
    node.transform = AIMatrixToGLMMatrix(pNode->mTransformation);
    uint32 selfIndex = outData.nodes.size();
    node.meshesNames.reserve(pNode->mNumMeshes);
    for (uint32 i = 0; i < pNode->mNumMeshes; ++i)
    {
        node.meshesNames.push_back(pScene->mMeshes[pNode->mMeshes[i]]->mName.C_Str());
    }

    outData.nodes.push_back(node);
    for (uint32 i = 0; i < pNode->mNumChildren;i++)
    {
        uint32 cIndex = BuildNodes(pScene,pNode->mChildren[i], selfIndex,outData);
        node.children.push_back(cIndex);
    }
    return selfIndex;
}

void FBXLoader::BuildMeshs(aiScene const* pScene, FBXLoader::SceneData& outData)
{
    for (uint32 i = 0; i < pScene->mNumMeshes; ++i)
    {
        // Load Vertices
        aiMesh* pMesh = pScene->mMeshes[i];
        FBXLoader::Mesh mesh = {};
        mesh.vertices.reserve(pMesh->mNumVertices);
        mesh.indices.reserve(pMesh->mNumFaces * 3);

        mesh.matIndex = static_cast<int32>(pMesh->mMaterialIndex);
        for (uint32 vIndex = 0; vIndex < pMesh->mNumVertices; ++vIndex)
        {
            Vertex v = {};
            v.position = { pMesh->mVertices[vIndex].x, pMesh->mVertices[vIndex].y, pMesh->mVertices[vIndex].z };

            if (pMesh->HasNormals())
                v.normal = { pMesh->mNormals[vIndex].x, pMesh->mNormals[vIndex].y, pMesh->mNormals[vIndex].z };
            if (pMesh->HasTextureCoords(0))
                v.texCoords = { pMesh->mTextureCoords[0][vIndex].x, pMesh->mTextureCoords[0][vIndex].y }; // Each vertex can have up to 8 uvs
            mesh.vertices.push_back(v);
        }


        for (uint32 fIndex = 0; fIndex < pMesh->mNumFaces; ++fIndex)
        {
            aiFace pFace = pMesh->mFaces[fIndex];
            for (uint32 iIndex = 0; iIndex < pFace.mNumIndices; ++iIndex)
            {
                mesh.indices.push_back(pFace.mIndices[iIndex]);
            }

        }
        outData.meshs[pMesh->mName.C_Str()] = mesh;
    }
}

void FBXLoader::BuildMaterials(aiScene const* pScene, SceneData& outData)
{
    for (uint32 i = 0; i < pScene->mNumMaterials; ++i)
    {
        aiMaterial* pMat = pScene->mMaterials[i];
        Material mat = {};
        for (uint8 c = 0; c < 4; ++c)
        {
            if (pMat->GetTextureCount(FBXLoader::m_sTexTypes[c]) == 0)
                continue;

            aiString texturePath;
            if (pMat->GetTexture(FBXLoader::m_sTexTypes[c], 0, &texturePath) != AI_SUCCESS)
                continue;
            
            std::string path = texturePath.C_Str();

            if (texturePath.data[0] != '*')
            {
                mat.textures[static_cast<TextureMaterialType>(c)] = path;
                continue;
            }

            aiTexture const* pText = pScene->GetEmbeddedTexture(texturePath.C_Str());
            if (pText == nullptr)
                continue;

            if (pText->mHeight != 0)
            {
                Logger::LogWithLevel(LogLevel::WARNING, "Unable to Load Texture : " + path + " from FBX file : " + pScene->mName.C_Str());
                continue;
            }
            std::string ext = pText->achFormatHint;
            if (ext.empty())
            {
                Logger::LogWithLevel(LogLevel::WARNING, "Unable to Load Texture : " + path + " from FBX file : " + pScene->mName.C_Str() + " Extension Incorrect");
                continue;
            }

            std::string textureName = "embedded_" + std::to_string(i) + std::to_string(c) + "." + ext;
            std::string fullPath = "res/textures/" + textureName;
            std::ofstream file(fullPath, std::ios::binary);
            file.write((const char*)pText->pcData, pText->mWidth);

            mat.textures[static_cast<TextureMaterialType>(c)] = fullPath;
        }
    }
}


void FBXLoader::BuildLights(aiScene const* pScene, SceneData& outData)
{
    if (pScene->HasLights() == false)
        return;

    outData.lights.reserve(pScene->mNumLights);
    for (uint32 i = 0; i < pScene->mNumLights; ++i)
    {
        Light l = {};
        l.position = { pScene->mLights[i]->mPosition.x,pScene->mLights[i]->mPosition.y,pScene->mLights[i]->mPosition.z },
        l.constant = pScene->mLights[i]->mAttenuationConstant;
        l.quadratic = pScene->mLights[i]->mAttenuationQuadratic;
        l.linear = pScene->mLights[i]->mAttenuationLinear;
        l.color = Color(pScene->mLights[i]->mColorAmbient.r, pScene->mLights[i]->mColorAmbient.g, pScene->mLights[i]->mColorAmbient.b, 1.0f);
        outData.lights.push_back(l);
    }
}

void FBXLoader::BuildBones(aiScene const* pScene, SceneData& outData)
{
    if (pScene->HasSkeletons() == false)
        return;

    for (uint32 i = 0; i < pScene->mNumSkeletons; ++i)
    {
        for (uint32 bIndex = 0; bIndex < pScene->mSkeletons[i]->mNumBones; ++bIndex)
        {
            aiSkeletonBone* pBone = pScene->mSkeletons[i]->mBones[bIndex];
            Bone bone = {};
            bone.positionInMesh = AIMatrixToGLMMatrix(pBone->mOffsetMatrix);
            bone.vertexWeight.reserve(pBone->mNumnWeights);
            for (uint32 wIndex = 0; wIndex < pBone->mNumnWeights; ++wIndex)
            {
                VertexWeight v = {};
                v.vertexIndex = pBone->mWeights[wIndex].mVertexId;
                v.vertexWieght = pBone->mWeights[wIndex].mWeight;
                bone.vertexWeight.push_back(v);
            }

            outData.meshs[pScene->mSkeletons[i]->mBones[bIndex]->mMeshId->mName.C_Str()].bones.push_back(bone);
        }
    }
}


void FBXLoader::BuildAnimations(aiScene const* pScene, SceneData& outData)
{
    if (pScene->HasAnimations() == false)
        return;

    outData.animations.reserve(pScene->mNumAnimations);
    for (uint32 i = 0; i < pScene->mNumAnimations; ++i)
    {
        Animation anim = {};
        aiAnimation* pAnim = pScene->mAnimations[i];
        anim.duration = pAnim->mDuration;
        anim.name = pAnim->mName.C_Str();

        for (uint32 animCount = 0; animCount < pAnim->mNumChannels; animCount++)
        {
            BuildAnimationsChannles(pAnim, anim, animCount);
        }
    }
}

void FBXLoader::BuildAnimationsChannles(aiAnimation const* pAnim, Animation& outAnim, uint32 channelID)
{
    AnimationChannel channel = {};
    aiNodeAnim* pAnimNode = pAnim->mChannels[channelID];
    channel.positionKeys.reserve(pAnimNode->mNumPositionKeys);
    channel.rotationKeys.reserve(pAnimNode->mNumRotationKeys);
    channel.scalingKeys.reserve(pAnimNode->mNumScalingKeys);
    for (uint32 k = 0; k < pAnimNode->mNumPositionKeys; ++k)
    {
        AnimationChannel::FrameVec3 f = {};
        f.time = pAnimNode->mPositionKeys[k].mTime;
        f.vec = { pAnimNode->mPositionKeys[k].mValue.x, pAnimNode->mPositionKeys[k].mValue.y,pAnimNode->mPositionKeys[k].mValue.z };
        channel.positionKeys.push_back(f);
    }
    for (uint32 k = 0; k < pAnimNode->mNumRotationKeys; ++k)
    {
        AnimationChannel::FrameQuat f = {};
        f.time = pAnimNode->mRotationKeys[k].mTime;
        f.quaternion = { pAnimNode->mRotationKeys[k].mValue.x, pAnimNode->mRotationKeys[k].mValue.y,pAnimNode->mRotationKeys[k].mValue.z,pAnimNode->mRotationKeys[k].mValue.w };
        channel.rotationKeys.push_back(f);
    }
    for (uint32 k = 0; k < pAnimNode->mNumScalingKeys; ++k)
    {
        AnimationChannel::FrameVec3 f = {};
        f.time = pAnimNode->mScalingKeys[k].mTime;
        f.vec = { pAnimNode->mScalingKeys[k].mValue.x, pAnimNode->mScalingKeys[k].mValue.y,pAnimNode->mScalingKeys[k].mValue.z };
        channel.scalingKeys.push_back(f);
    }

    outAnim.animationTransform.push_back(channel);
}