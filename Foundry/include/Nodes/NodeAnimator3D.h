#ifndef FOUNDRY_NODE_MESHANIMATED3D__H_
#define FOUNDRY_NODE_MESHANIMATED3D__H_

#include "Define.h"
#include "Node3D.h"

#include <Mesh.h>

class NodeMeshAnimated3D : public Node3D
{
public:
	//class Proxy
	explicit NodeMeshAnimated3D(std::string const& name);
	~NodeMeshAnimated3D() override = default;

	virtual void OnUpdate(double delta) override;

	void LinkAnimation() const;

	static ISerializable* CreateInstance();

private:
	void UpdateAnimatedTransform() const;

protected:
	uptr<Mesh> m_mesh;
};

REGISTER_ISERIALIZABLE(NodeViewport, NodeViewport::CreateInstance);

#endif

