#ifndef ORE_CUBEMAP__H_
#define ORE_CUBEMAP__H_

#include "Define.h"
#include "Texture.h"

namespace Ore
{

    class Cubemap
    {
    public:
        Cubemap() = default;
        Cubemap(std::array<std::filesystem::path, 6> const& facesPaths);
        Cubemap(Cubemap const& other) = delete;
        Cubemap(Cubemap && other) noexcept = delete;
        ~Cubemap() = default;

        void Load(std::array<std::filesystem::path, 6> const& faces);

    private:
        GLuint m_cubeMap;

        friend class SkyboxPass;
    };
}
    #endif

