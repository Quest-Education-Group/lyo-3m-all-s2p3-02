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
    enum class CmdType { APPLYFORCE, ATTACH } Type;



};

using CommandType = Command<EngineServer>::CmdType;

class PhysicsServer : public Server<PhysicsServer>
{
public:


private:
    void FlushCommandsImpl() override;
    void BuildTasksImpl(TaskGraph& graph) override;
    void OnInitialize() override {}

private:    
    rp::PhysicsCommon physicsCommon;
    rp::PhysicsWorld* world;


};

#endif