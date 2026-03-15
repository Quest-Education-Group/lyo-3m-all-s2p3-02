#include "Nodes/NodeCollider.h"


//void NodeCollider::SetBoxShape(const glm::vec3& halfExtents)
//{
//    auto* physicsCommon = PhysicsServer::GetPhysicsCommon();
//    m_pShape = physicsCommon->createBoxShape({ halfExtents.x, halfExtents.y, halfExtents.z });
//}
//
//void NodeCollider::AttachToRigidBody(NodeRigidBody* rigidBody)
//{
//    m_pRigidBody = rigidBody;
//    rp3d::Transform localTransform = rp3d::Transform::identity();
//    m_pCollider = rigidBody->GetRigidBody()->addCollider(m_pShape, localTransform);
//}
//
//void NodeCollider::SetBounciness(float bounciness)
//{
//    if (m_pCollider)
//        m_pCollider->getMaterial().setBounciness(bounciness);
//}
//
//void NodeCollider::SetIsTrigger(bool trigger)
//{
//    if (m_pCollider)
//        m_pCollider->setIsTrigger(trigger);
//    m_pCollider.
//}
//
//void NodeCollider::SetCollisionCategory(uint16_t category)
//{
//    if (m_pCollider)
//        m_pCollider->setCollisionCategoryBits(category);
//}
//
//void NodeCollider::SetCollideWithMask(uint16_t mask)
//{
//    if (m_pCollider)
//        m_pCollider->setCollideWithMaskBits(mask);
//}

//#include "Servers/PhysicsServer.h"
//
//NodeCollider::NodeCollider(std::string const& name)
//{
//	m_name = name;
//
//	m_pCollider = nullptr;
//	m_pShape = nullptr;
//	m_pOwner = nullptr;
//}
//
//NodeCollider::~NodeCollider()
//{
//    Detach();
//    DestroyCurrentShape();
//}
//
//// -------------------------------------------------------
//// Shapes
//// -------------------------------------------------------
//void NodeCollider::DestroyCurrentShape()
//{
//    if (m_pShape == nullptr) return;
//    auto& pc = PhysicsServer::GetPhysicsCommon();
//
//    // On doit caster pour appeler la bonne destroy
//    if (auto* s = dynamic_cast<rp3d::BoxShape*>(m_pShape))
//        pc.destroyBoxShape(s);
//    else if (auto* s = dynamic_cast<rp3d::SphereShape*>(m_pShape))
//        pc.destroySphereShape(s);
//    else if (auto* s = dynamic_cast<rp3d::CapsuleShape*>(m_pShape))
//        pc.destroyCapsuleShape(s);
//
//    m_pShape = nullptr;
//}
//
//void NodeCollider::SetBoxShape(const glm::vec3& halfExtents)
//{
//    Detach();
//    DestroyCurrentShape();
//    m_pShape = PhysicsServer::GetPhysicsCommon().createBoxShape(
//        { halfExtents.x, halfExtents.y, halfExtents.z }
//    );
//}
//
//void NodeCollider::SetSphereShape(float radius)
//{
//    Detach();
//    DestroyCurrentShape();
//    m_pShape = PhysicsServer::GetPhysicsCommon().createSphereShape(radius);
//}
//
//void NodeCollider::SetCapsuleShape(float radius, float height)
//{
//    Detach();
//    DestroyCurrentShape();
//    m_pShape = PhysicsServer::GetPhysicsCommon().createCapsuleShape(radius, height);
//}
//
//// -------------------------------------------------------
//// Transform local
//// -------------------------------------------------------
//rp3d::Transform NodeCollider::GetLocalRp3dTransform() const
//{
//    return rp3d::Transform(
//        { m_localPosition.x, m_localPosition.y, m_localPosition.z },
//        { m_localRotation.w, m_localRotation.x, m_localRotation.y, m_localRotation.z }
//    );
//}
//
//void NodeCollider::SetLocalPosition(const glm::vec3& pos)
//{
//    m_localPosition = pos;
//    if (m_pCollider)
//        m_pCollider->setLocalToBodyTransform(GetLocalRp3dTransform());
//}
//
//void NodeCollider::SetLocalRotation(const glm::quat& rot)
//{
//    m_localRotation = rot;
//    if (m_pCollider)
//        m_pCollider->setLocalToBodyTransform(GetLocalRp3dTransform());
//}
//
//glm::vec3 NodeCollider::GetLocalPosition() const { return m_localPosition; }
//glm::quat NodeCollider::GetLocalRotation() const { return m_localRotation; }
//
//
//void NodeCollider::AttachToRigidBody(rp3d::RigidBody* rigidBody)
//{
//    if (m_pShape == nullptr) return; // pas de shape = pas de collider
//    m_pRigidBody = rigidBody;
//    m_pCollider = rigidBody->addCollider(m_pShape, GetLocalRp3dTransform());
//}
//
//void NodeCollider::Detach()
//{
//    if (m_pCollider && m_pRigidBody)
//        m_pRigidBody->removeCollider(m_pCollider);
//    m_pCollider = nullptr;
//    m_pRigidBody = nullptr;
//}
//
//
//void NodeCollider::SetBounciness(float v)
//{
//    if (m_pCollider) m_pCollider->getMaterial().setBounciness(v);
//}
//float NodeCollider::GetBounciness() const
//{
//    return m_pCollider ? m_pCollider->getMaterial().getBounciness() : 0.0f;
//}
//void NodeCollider::SetFrictionCoefficient(float v)
//{
//    if (m_pCollider) m_pCollider->getMaterial().setFrictionCoefficient(v);
//}
//float NodeCollider::GetFrictionCoefficient() const
//{
//    return m_pCollider ? m_pCollider->getMaterial().getFrictionCoefficient() : 0.0f;
//}
//void NodeCollider::SetMassDensity(float v)
//{
//    if (m_pCollider) m_pCollider->getMaterial().setMassDensity(v);
//}
//float NodeCollider::GetMassDensity() const
//{
//    return m_pCollider ? m_pCollider->getMaterial().getMassDensity() : 1.0f;
//}
//
//
//void NodeCollider::SetIsTrigger(bool v)
//{
//    if (m_pCollider) m_pCollider->setIsTrigger(v);
//}
//bool NodeCollider::IsTrigger() const
//{
//    return m_pCollider ? m_pCollider->getIsTrigger() : false;
//}
//void NodeCollider::SetIsSimulationCollider(bool v)
//{
//    if (m_pCollider) m_pCollider->setIsSimulationCollider(v);
//}
//bool NodeCollider::IsSimulationCollider() const
//{
//    return m_pCollider ? m_pCollider->getIsSimulationCollider() : false;
//}
//void NodeCollider::SetIsWorldQueryCollider(bool v)
//{
//    if (m_pCollider) m_pCollider->setIsWorldQueryCollider(v);
//}
//bool NodeCollider::IsWorldQueryCollider() const
//{
//    return m_pCollider ? m_pCollider->getIsWorldQueryCollider() : false;
//}
//
//
//void NodeCollider::SetCollisionCategoryBits(uint16_t category)
//{
//    if (m_pCollider) m_pCollider->setCollisionCategoryBits(category);
//}
//uint16_t NodeCollider::GetCollisionCategoryBits() const
//{
//    return m_pCollider ? m_pCollider->getCollisionCategoryBits() : 0x0001;
//}
//void NodeCollider::SetCollideWithMaskBits(uint16_t mask)
//{
//    if (m_pCollider) m_pCollider->setCollideWithMaskBits(mask);
//}
//uint16_t NodeCollider::GetCollideWithMaskBits() const
//{
//    return m_pCollider ? m_pCollider->getCollideWithMaskBits() : 0xFFFF;
//}

#include "Servers/PhysicsServer.h"

NodeCollider::NodeCollider(std::string const& name) : Node(name) {}

NodeCollider::~NodeCollider()
{
	Detach();
	DestroyShape();
}

void NodeCollider::DestroyShape()
{
	if (!m_pShape) return;

	auto& pc = PhysicsServer::GetPhysicsCommon();

	if (auto* s = dynamic_cast<rp3d::BoxShape*>(m_pShape))
		pc.destroyBoxShape(s);
	else if (auto* s = dynamic_cast<rp3d::SphereShape*>(m_pShape))
		pc.destroySphereShape(s);
	else if (auto* s = dynamic_cast<rp3d::CapsuleShape*>(m_pShape))
		pc.destroyCapsuleShape(s);

	m_pShape = nullptr;
}

void NodeCollider::SetBoxShape(const glm::vec3& halfExtents)
{
	Detach();
	DestroyShape();
	m_pShape = PhysicsServer::GetPhysicsCommon().createBoxShape({ halfExtents.x, halfExtents.y, halfExtents.z });

	if (m_pRigidBody)
		AttachToRigidBody(m_pRigidBody);
}

void NodeCollider::SetSphereShape(float radius)
{
	Detach();
	DestroyShape();
	m_pShape = PhysicsServer::GetPhysicsCommon().createSphereShape(radius);
	if (m_pRigidBody) AttachToRigidBody(m_pRigidBody);
}

void NodeCollider::SetCapsuleShape(float radius, float height)
{
	Detach();
	DestroyShape();
	m_pShape = PhysicsServer::GetPhysicsCommon().createCapsuleShape(radius, height);
	if (m_pRigidBody) AttachToRigidBody(m_pRigidBody);
}

rp3d::Transform NodeCollider::GetLocalRp3dTransform() const
{
	return rp3d::Transform(
		{ m_localPosition.x, m_localPosition.y, m_localPosition.z },
		{ m_localRotation.w, m_localRotation.x, m_localRotation.y, m_localRotation.z }
	);
}

void NodeCollider::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	if (m_pCollider)
		m_pCollider->setLocalToBodyTransform(GetLocalRp3dTransform());
}

void NodeCollider::SetLocalRotation(const glm::quat& rot)
{
	m_localRotation = rot;
	if (m_pCollider)
		m_pCollider->setLocalToBodyTransform(GetLocalRp3dTransform());
}


void NodeCollider::AttachToRigidBody(rp3d::RigidBody* rigidBody)
{
	if (!m_pShape) return;
	m_pRigidBody = rigidBody;
	m_pCollider = rigidBody->addCollider(m_pShape, GetLocalRp3dTransform());
}

void NodeCollider::Detach()
{
	if (m_pCollider && m_pRigidBody)
		m_pRigidBody->removeCollider(m_pCollider);
	m_pCollider = nullptr;
}

void  NodeCollider::SetBounciness(float v)
{
	if (m_pCollider) m_pCollider->getMaterial().setBounciness(v);
}
float NodeCollider::GetBounciness() const
{
	return m_pCollider ? m_pCollider->getMaterial().getBounciness() : 0.0f;
}
void  NodeCollider::SetFrictionCoefficient(float v)
{
	if (m_pCollider) m_pCollider->getMaterial().setFrictionCoefficient(v);
}
float NodeCollider::GetFrictionCoefficient() const
{
	return m_pCollider ? m_pCollider->getMaterial().getFrictionCoefficient() : 0.0f;
}
void  NodeCollider::SetMassDensity(float v)
{
	if (m_pCollider) m_pCollider->getMaterial().setMassDensity(v);
}
float NodeCollider::GetMassDensity() const
{
	return m_pCollider ? m_pCollider->getMaterial().getMassDensity() : 1.0f;
}

void NodeCollider::SetIsTrigger(bool v)
{
	if (m_pCollider) m_pCollider->setIsTrigger(v);
}
bool NodeCollider::IsTrigger() const
{
	return m_pCollider ? m_pCollider->getIsTrigger() : false;
}
void NodeCollider::SetIsSimulationCollider(bool v)
{
	if (m_pCollider) m_pCollider->setIsSimulationCollider(v);
}
bool NodeCollider::IsSimulationCollider() const
{
	return m_pCollider ? m_pCollider->getIsSimulationCollider() : false;
}
void NodeCollider::SetIsWorldQueryCollider(bool v)
{
	if (m_pCollider) m_pCollider->setIsWorldQueryCollider(v);
}
bool NodeCollider::IsWorldQueryCollider() const
{
	return m_pCollider ? m_pCollider->getIsWorldQueryCollider() : false;
}


void     NodeCollider::SetCollisionCategoryBits(uint16_t v)
{
	if (m_pCollider) m_pCollider->setCollisionCategoryBits(v);
}
uint16_t NodeCollider::GetCollisionCategoryBits() const
{
	return m_pCollider ? m_pCollider->getCollisionCategoryBits() : 0x0001;
}
void     NodeCollider::SetCollideWithMaskBits(uint16_t v) {
	if (m_pCollider) m_pCollider->setCollideWithMaskBits(v);
}
uint16_t NodeCollider::GetCollisionBitsMask() const
{
	return m_pCollider ? m_pCollider->getCollideWithMaskBits() : 0xFFFF;
}