#ifndef ORE_SKYBOX_PASS__H_
#define ORE_SKYBOX_PASS__H_

#include "Buffer.h"
#include "Cubemap.h"
#include "Geometry.h"
#include "Pass.h"
#include "VertexArrayObject.h"

namespace Ore
{
class SkyboxPass : public Pass
{
    SkyboxPass(Program& program) : Pass(program) {};
    SkyboxPass(Program& program, Camera* camera);

    void Execute() override;
    void SetCubeMap(sptr<Cubemap> const& cubemap) { m_pCubeMap = cubemap; }

private:
    constexpr std::array<Vertex, 24> GenerateCubeVertices();
    constexpr std::array<uint8, 36> GenerateCubeIndices();

private:
    sptr<Cubemap>               m_pCubeMap;
    uptr<VertexArrayObject>     m_pVertexArray;
    uptr<Buffer<uint8>>         m_pIndicesBuffer;
    uptr<Buffer<Vertex>>        m_pVertexBuffer;
};
}
#endif