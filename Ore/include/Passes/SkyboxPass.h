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
public:
    SkyboxPass(Program& program) : Pass(program) {};
    SkyboxPass(Program& program, Camera* camera);

    void SetCubeMap(sptr<Cubemap> const& cubemap) { m_pCubeMap = cubemap; }
private:
    void Execute() override;

    constexpr std::vector<Vertex> GenerateCubeVertices();
    constexpr std::vector<uint8> GenerateCubeIndices();

private:
    sptr<Cubemap>               m_pCubeMap;
    uptr<VertexArrayObject>     m_pVertexArray;
    uptr<Buffer<uint8>>         m_pIndicesBuffer;
    uptr<Buffer<Vertex>>        m_pVertexBuffer;
    GLuint m_frameBufferId;

};
}
#endif