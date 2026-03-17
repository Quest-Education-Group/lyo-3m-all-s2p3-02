#include "Servers/PhysicsServer.h"
#include "Nodes/NodeRigidBody.h"

reactphysics3d::PhysicsWorld* PhysicsServer::m_pPhysicsWorld = nullptr;
reactphysics3d::PhysicsCommon PhysicsServer::m_physicsCommon;


PhysicsServer::PhysicsServer() : Server()
{
}

PhysicsServer::~PhysicsServer()
{
    PhysicsServer::GetPhysicsCommon().destroyPhysicsWorld(m_pPhysicsWorld);
}

void PhysicsServer::OnInitialize()
{
  /*  rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 300;
    settings.defaultPositionSolverNbIterations = 150;
    settings.isSleepingEnabled = true;
    settings.gravity = rp3d::Vector3(0, -9.81, 0);
    m_pWorld = m_physicsCommon.createPhysicsWorld(settings);*/
    m_pPhysicsWorld = m_physicsCommon.createPhysicsWorld();
}

void PhysicsServer::Init()
{
    rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 300;
    settings.defaultPositionSolverNbIterations = 150;
    settings.isSleepingEnabled = true;
    settings.gravity = rp3d::Vector3(0, -9.81, 0);
    m_pPhysicsWorld = m_physicsCommon.createPhysicsWorld(settings);
    //m_pPhysicsWorld = m_physicsCommon.createPhysicsWorld();
}
rp3d::RigidBody* PhysicsServer::CreateRigidBody(const rp3d::Transform& transform, Node* const To)
{
    //Instance().m_commands.push({ CommandType::CREATERIGIDBODY, To });
	return m_pPhysicsWorld->createRigidBody(transform);
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
