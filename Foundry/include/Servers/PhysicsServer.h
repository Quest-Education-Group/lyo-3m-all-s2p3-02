#ifndef PHYSICS_SERVER__H_
#define PHYSICS_SERVER__H_

#include "Server.hpp"
#include "Node.h"

#include <iostream>
#include <memory>

#include <reactphysics3d/reactphysics3d.h>

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

    // FONCTION TEMPORAIRE
    static void Init();

    static rp3d::RigidBody* CreateRigidBody(const rp3d::Transform& transform, Node* const To);

    static rp3d::PhysicsCommon& GetPhysicsCommon() { return m_physicsCommon; }
    static rp3d::PhysicsWorld& GetPhysicsWorld() { return *m_pPhysicsWorld; }
    static void UpdatePhysicsWorld(double dt) { m_pPhysicsWorld->update(dt); }

private:
    void FlushCommandsImpl() override;
    void BuildTasksImpl(TaskGraph& graph) override {};
    void OnInitialize() override;
    

private:    
    static rp3d::PhysicsCommon m_physicsCommon;
    static rp3d::PhysicsWorld* m_pPhysicsWorld;


};

#endif