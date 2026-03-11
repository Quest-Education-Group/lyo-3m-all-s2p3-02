#include "Servers/PhysicsServer.h"
#include "Nodes/NodeRigidBody.h"

reactphysics3d::PhysicsWorld* PhysicsServer::m_pWorld = nullptr;
reactphysics3d::PhysicsCommon PhysicsServer::m_physicsCommon;


PhysicsServer::PhysicsServer() : Server()
{
    //m_pWorld = m_physicsCommon.createPhysicsWorld(); JAMAIS APPELE
}

PhysicsServer::~PhysicsServer()
{
    PhysicsServer::GetPhysicsCommon().destroyPhysicsWorld(m_pWorld);
}

void PhysicsServer::Init()
{
  /*  rp::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 300;
    settings.defaultPositionSolverNbIterations = 150;
    settings.isSleepingEnabled = true;
    settings.gravity = rp::Vector3(0, -9.81, 0);
    m_pWorld = m_physicsCommon.createPhysicsWorld(settings);*/
    m_pWorld = m_physicsCommon.createPhysicsWorld();
}
rp::RigidBody* PhysicsServer::CreateRigidBody(const rp::Transform& transform, Node* const To)
{
    //Instance().m_commands.push({ CommandType::CREATERIGIDBODY, To });
	return m_pWorld->createRigidBody(transform);
}

void PhysicsServer::FlushCommandsImpl()
{
    while (m_commands.empty() == false)
    {
        Command<PhysicsServer>& command = m_commands.front();
        switch (command.Type)
        {
        case CommandTyp::CREATERIGIDBODY:
            //static_cast<NodeRigidBody*>(command.To).CreateRigidBody();
            m_commands.pop();
            break;
        case CommandTyp::APPLYFORCE:
            //m_commands.pop();
            break;
        }
    }
}
