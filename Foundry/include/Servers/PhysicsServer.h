#ifndef PHYSICS_SERVER__H_
#define PHYSICS_SERVER__H_

#include "Server.hpp"
#include "Node.h"

#include <iostream>
#include <memory>

#include <reactphysics3d/reactphysics3d.h>
namespace rp = reactphysics3d;

template <>
struct Command<class PhysicsServer>
{
    enum class CmdType { CREATERIGIDBODY, APPLYFORCE } Type;

    Node* const To = nullptr;

};

using CommandTyp = Command<PhysicsServer>::CmdType;

class PhysicsServer : public Server<PhysicsServer>
{
public:

    PhysicsServer();
    ~PhysicsServer();

    static void Init();

    static rp::RigidBody* CreateRigidBody(const rp::Transform& transform, Node* const To);

    static rp::PhysicsCommon& GetPhysicsCommon() { return m_physicsCommon; }
    static rp::PhysicsWorld& GetPhysicsWorld() { return *m_pWorld; }

private:
    void FlushCommandsImpl() override;
    void BuildTasksImpl(TaskGraph& graph) override {};
    void OnInitialize() override {}
    

private:    
    static rp::PhysicsCommon m_physicsCommon;
    static rp::PhysicsWorld* m_pWorld;


};

#endif