#ifndef ORE_GEOMETRY__H_
#define ORE_GEOMETRY__H_

#include "IGeometry.h"

class Geometry final : public IGeometry
{
public:
    Geometry(std::vector<float> const& points, std::vector<uint32> const& indices);
    ~Geometry() override;

protected:
    void AddPoints(std::vector<float> const& points) override;
    void AddIndices(std::vector<uint32> const& indices) override;
};

#endif //!ORE_GEOMETRY__H_
