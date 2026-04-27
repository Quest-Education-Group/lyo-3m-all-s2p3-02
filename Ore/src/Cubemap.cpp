#include "Cubemap.h"
#include "Logger.hpp"
#include "dependencies/stb_image.h"

#include <array>

namespace Ore
{
    Cubemap::Cubemap(std::array<std::filesystem::path, 6> const& facesPaths)
    {
        Load(facesPaths);
    }

    void Cubemap::Load(std::array<std::filesystem::path, 6>const& faces)
    {
        glGenTextures(1, &m_cubeMap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);

        int32 width, height, nrChannels;
        byte* pData = nullptr;
        for (uint32 i = 0; i < faces.size(); i++)
        {
            pData = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (pData == nullptr)
            {
                Logger::LogWithLevel(LogLevel::ERROR, "Failed to load cubemap face : ", faces[i]);
                return;
            }

            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData
            );
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        if (pData) stbi_image_free(pData);
    }
}
