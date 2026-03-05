#include "Nodes/Node3D.h"
#include "MathUtils.h"
#include <glm/detail/type_quat.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


Node3D::Node3D(std::string const& name) : 
	Node(name),
	m_isParentNode3D(false)
{
	OnParentChange.Subscribe([&](Node& n) {CheckParentTransform(); });
}

void Node3D::OnUpdate(float delta)
{
	Node::OnUpdate(delta);
	m_transform.Update();
	UpdateWorldTransform();
}
glm::mat4x4& Node3D::GetWorldMatrice()
{	
	//if (m_isParentNode3D == false)
	//{
	//	return GetMatrix();
	//}
	//else
	//{
	//	auto* parent = static_cast<Node3D*>(m_pOwner);
	//	auto& pMat = parent->GetWorldMatrice();
	//	glm::mat4x4 worldMat = pMat * GetMatrix();
	//	return worldMat;
	//}

	return m_worldTransform;
}

void Node3D::Reparent(Node& newParent, bool keepGlobalTransform)
{
	UpdateWorldTransform();
	Node::Reparent(newParent, keepGlobalTransform);
	if (!m_isParentNode3D) return;

	Node3D* parent = static_cast<Node3D*>(m_pOwner);
	
	glm::vec4 newLocal = m_worldPosition - parent->m_worldPosition;
	glm::mat4 posMatrix = Maths::Translate(newLocal);
	posMatrix = glm::inverse(glm::toMat4(glm::quat(parent->m_worldRotation))) * posMatrix;
	newLocal.x = posMatrix[3][0];
	newLocal.y = posMatrix[3][1];
	newLocal.z = posMatrix[3][2];
	newLocal /= parent->m_worldScale;
	newLocal.w = 1.0f;
	m_transform.SetPosition(newLocal);

	glm::vec4 newScale = m_worldScale / parent->m_worldScale;
	newScale.w = 1.0f;
	m_transform.SetScale(newScale);
	glm::vec4 newRot = m_worldRotation + parent->m_worldRotation;
	newRot.w = 1.0f;
	m_transform.SetRotation(newRot);
	//auto& mat = GetMatrix();
	//mat *= glm::inverse(static_cast<Node3D&>(newParent).GetMatrix());

}

void Node3D::CheckParentTransform()
{
	if (m_pOwner == nullptr) return;
		m_isParentNode3D = dynamic_cast<Node3D*>(GetParent());
}

void Node3D::UpdateWorldTransform()
{
	Node3D* parent = static_cast<Node3D*>(m_pOwner);
	if (m_isParentNode3D)
	{
		m_worldScale = m_transform.GetScale() * parent->m_worldScale;
		m_worldScale.w = 1.0f;

		m_worldRotation = m_transform.GetRotation() + parent->m_worldRotation;
		m_worldRotation.w = 1.0f;

		m_worldPosition = m_transform.GetPosition() * parent->m_worldScale;
		glm::mat4 posMatrix = Maths::Translate(m_worldPosition);
		posMatrix = glm::toMat4(glm::quat(parent->m_worldRotation)) * posMatrix;
		m_worldPosition.x = posMatrix[3][0];
		m_worldPosition.y = posMatrix[3][1];
		m_worldPosition.z = posMatrix[3][2];

		m_worldPosition += parent->m_worldPosition;
		m_worldPosition.w = 1.0f;
	}
	else
	{
		m_worldPosition = m_transform.GetPosition();
		m_worldScale = m_transform.GetScale();
		m_worldRotation = m_transform.GetRotation();
	}

	m_worldTransform = Maths::Translate(m_worldPosition)  * glm::toMat4(glm::quat(m_worldRotation))* Maths::Scale(m_worldScale)  ;
}