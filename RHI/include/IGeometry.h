#ifndef RHI_IGEOMETRY__H_
#define RHI_IGEOMETRY__H_

#include "Define.h"

#include <vector>
class IGeometry 
{
public:
    virtual ~IGeometry() = 0;

protected:
    virtual void AddPoints(std::vector<float> const& points) = 0;
    virtual void AddIndices(std::vector<uint32> const& indices) = 0;
};

#endif //!RHI_IGEOMETRY__H_
