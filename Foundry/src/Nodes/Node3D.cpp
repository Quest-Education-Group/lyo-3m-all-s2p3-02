#include "Nodes/Node3D.h"


Node3D::Node3D(std::string const& name) : 
	Node(name),
	m_isParentNode3D(false)
{
	OnParentChange.Subscribe([&](Node& n) {CheckParentTransform(); });
}

void Node3D::OnUpdate(float delta)
{
	Node::OnUpdate(delta);
	if (m_isParentNode3D)
		ApplyTransform(static_cast<Node3D*>(m_pOwner)->m_transform);
	m_transform.Update();
}
glm::mat4x4& Node3D::GetWorldMatrice()
{	
	if (m_isParentNode3D == false)
	{
		return GetMatrix();
	}
	else
	{
		auto* parent = static_cast<Node3D*>(m_pOwner);
		auto& pMat = parent->GetWorldMatrice();
		glm::mat4x4 worldMat = pMat * GetMatrix();
		return worldMat;
	}
}

void Node3D::Reparent(Node& newParent, bool keepGlobalTransform)
{
	Node::Reparent(newParent, keepGlobalTransform);
	if (!m_isParentNode3D) return;

	auto& mat = GetMatrix();
	mat -= static_cast<Node3D&>(newParent).GetMatrix();
}

void Node3D::CheckParentTransform()
{
	if (m_pOwner == nullptr) return;
		m_isParentNode3D = dynamic_cast<Node3D*>(GetParent());
}