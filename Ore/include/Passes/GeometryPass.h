#ifndef ORE_GEOMETRY_PASS__H_
#define ORE_GEOMETRY_PASS__H_

#include "Pass.h"
#include <span>

class Mesh;
class GeometryPass final : public Pass
{
public:
    GeometryPass(Program const& shader, std::span<Mesh const> meshes, sptr<Camera> camera);
    ~GeometryPass() override;

    void Execute() override;
    
private:
    std::span<Mesh const> m_meshes;

};
#endif
 
