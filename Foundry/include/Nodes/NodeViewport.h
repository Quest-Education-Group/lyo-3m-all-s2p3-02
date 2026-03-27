#ifndef FOUNDRY_NODEVIEWPORT__H_
#define FOUNDRY_NODEVIEWPORT__H_

#include "Define.h"
#include "Node2D.h"
#include "Viewport.h"

#include "Passes/GeometryPass.h"
#include "Passes/LightPass.h"

class NodeViewport : public Node2D
{
public:
	//class Proxy

	explicit NodeViewport(std::string const& name);
	~NodeViewport() override = default;

	virtual void OnUpdate(double delta) override;
	void SetBackgroundColor(Color const& color) const;

	static ISerializable* CreateInstance();
private:
	void UpdateViewport() const;
	void LoadPrograms();

protected:
	uptr<Viewport> m_pViewPort;

	std::vector<Mesh*> m_visibleMeshes;
	std::vector<Light*> m_visibleLights;

	Program m_geometryProgram;
	Program m_ligthProgram;

	uptr<GeometryPass> m_pGeometryPass;
	uptr<LightPass> m_pLightPass;

	friend class GraphicServer;
};

REGISTER_ISERIALIZABLE(NodeViewport, NodeViewport::CreateInstance);

#endif

