////////////////////////////////////////////////////
// CMake Generator by Alexandre Glatz
// https://github.com/AlexandreGlatz/cmake-generator
////////////////////////////////////////////////////

#include "Define.h"
#include "Node.h"
#include "Servers/EngineServer.h"
#include "Servers/PhysicsServer.h"
#include "Scripting/Lua/LuaScriptInstance.hpp"

#include <memory>
#include <reactphysics3d/reactphysics3d.h>
#include "raylib.h"
#include "Transform3D.h"
#include "Nodes/Node3D.h"
#include "Nodes/NodeRigidBody.h"
#include "Clock.hpp"
#include <Debug.h>
//
//namespace rp = reactphysics3d;



#include "raymath.h"
#include "rlgl.h"
#include <Nodes/NodeCollider.h>

class OverlapCB : public rp3d::OverlapCallback {
public:
	bool hit = false;
	void onOverlap(CallbackData& data) override {
		hit = (data.getNbOverlappingPairs() > 0);
	}
};
class CollisionCB : public rp3d::CollisionCallback {
public:
	bool hit = false;
	void onContact(const rp3d::CollisionCallback::CallbackData& data) override {
		hit = (data.getNbContactPairs() > 0);
	}
};

//void MoveCharacter(rp3d::RigidBody* rb, const glm::vec3& direction, float speed)
//{
//	reactphysics3d::Vector3 currentVel = rb->getLinearVelocity();
//
//	rb->setLinearVelocity(reactphysics3d::Vector3(
//		direction.x * speed,
//		currentVel.y,          
//		direction.z * speed
//	));
//
//	rb->setAngularLockAxisFactor(reactphysics3d::Vector3(0, 0, 0));
//}
//void Jump(rp3d::RigidBody* rb, float force)
//{
//	reactphysics3d::Vector3 currentVel = rb->getLinearVelocity();
//	rb->setLinearVelocity(reactphysics3d::Vector3(
//		currentVel.x,
//		force,         
//		currentVel.z
//	));
//}

int main() {
	InitWindow(1280, 720, "Cube");
	SetTargetFPS(60);

	Camera3D cam = {};
	cam.position = { 0.0f, 10.0f, -20.0f };
	cam.target = { 0.0f,  0.0f,  0.0f };
	cam.up = { 0.0f,  1.0f,  0.0f };
	cam.fovy = 50.0f;
	cam.projection = CAMERA_PERSPECTIVE;

	PhysicsServer::Init();

	//// cube
	Vector3 pos = { 0.0f, 1.0f, 0.0f };
	Vector3 pSize = { 1.0f, 1.0f, 1.0f };
	float   rotY = 0.0f;
	float   rotX = 0.0f;

	//auto RB_player = Node::CreateNode<NodeRigidBody>("rb_player");
	//auto player = Node::CreateNode<Node3D>("player");
	//player.get()->SetLocalPosition({ pos.x,pos.y,pos.z });
	//player->AddLocalPitch(20);
	////player->Update(0.016);
	//RB_player->SetOwner(player.get());
	//RB_player->GetRigidBody().setType(rp3d::BodyType::DYNAMIC);
	//RB_player->AddBoxCollider({ pSize.x, pSize.y, pSize.z });
	//RB_player->GetRigidBody().enableGravity(false);
	//RB_player->GetRigidBody().setMass(1.0f);
	auto player = Node::CreateNode<Node3D>("player");
	auto RB_player = Node::CreateNode<NodeRigidBody>("rb_player");
	auto C_player = Node::CreateNode<NodeCollider>("c_player");

	player->SetLocalPosition({ 0.0f, 1.0f, 0.0f });

	C_player->SetBoxShape({ 1.0f, 1.0f, 1.0f });   // configure la shape AVANT d'attacher


	RB_player->SetOwner(player.get());
	RB_player->SetBodyType(RigidBodyType::DYNAMIC);
	RB_player->SetIsGravityEnabled(true);
	RB_player->SetMass(1.0f);
	RB_player->GetRigidBody().setAngularDamping(2.0f);
	RB_player->GetRigidBody().setAngularLockAxisFactor(rp3d::Vector3(1.0, 1.0, 1.0));

	RB_player->AddChild(std::move(C_player)); // ← OnSceneEnter déclenché ici, auto-attach


	//  Mur statique 
	const Vector3   WALL_POS = { 3.0f, 1.0f, 0.0f };
	const float     WALL_W = 1.0f;
	const float     WALL_H = 4.0f;
	const float     WALL_D = 6.0f;

	//auto RB_wall = Node::CreateNode<NodeRigidBody>("rb_wall");
	//auto wall = Node::CreateNode<Node3D>("wall");
	//wall.get()->SetLocalPosition({ WALL_POS.x,WALL_POS.y,WALL_POS.z });
	//RB_wall->SetOwner(wall.get());
	//RB_wall->GetRigidBody().setType(rp3d::BodyType::STATIC);
	//RB_wall->AddBoxCollider({ WALL_W / 2, WALL_H / 2, WALL_D / 2 });
	//RB_wall->GetRigidBody().enableGravity(false);
	//RB_wall->GetRigidBody().setMass(1.0f);

	auto wall = Node::CreateNode<Node3D>("wall");
	auto RB_wall = Node::CreateNode<NodeRigidBody>("rb_wall");
	auto C_wall = Node::CreateNode<NodeCollider>("c_wall");

	wall->SetLocalPosition({ 3.0f, 1.0f, 0.0f });
	C_wall->SetBoxShape({ 0.5f, 2.0f, 3.0f });

	RB_wall->SetOwner(wall.get());
	RB_wall->SetBodyType(RigidBodyType::STATIC);

	RB_wall->AddChild(std::move(C_wall));


		//  Sol statique 
	const Vector3   FLOOR_POS = { 0.0f, -1.0f, 0.0f };
	const float     FLOOR_W = 100.0f;
	const float     FLOOR_H = 2.0f;
	const float     FLOOR_D = 100.0f;

	//auto RB_floor = Node::CreateNode<NodeRigidBody>("rb_floor");
	//auto floor = Node::CreateNode<Node3D>("floor");
	//floor.get()->SetLocalPosition({ FLOOR_POS.x,FLOOR_POS.y,FLOOR_POS.z });
	//RB_floor->SetOwner(floor.get());
	//RB_floor->GetRigidBody().setType(rp3d::BodyType::STATIC);
	//RB_floor->AddBoxCollider({ FLOOR_W / 2, FLOOR_H / 2, FLOOR_D / 2 });
	auto floor = Node::CreateNode<Node3D>("floor");
	auto RB_floor = Node::CreateNode<NodeRigidBody>("rb_floor");
	auto C_floor = Node::CreateNode<NodeCollider>("c_floor");

	floor->SetLocalPosition({ 0.0f, -1.0f, 0.0f });
	C_floor->SetBoxShape({ 50.0f, 1.0f, 50.0f });

	RB_floor->SetOwner(floor.get());
	RB_floor->SetBodyType(RigidBodyType::STATIC);

	RB_floor->AddChild(std::move(C_floor));



	// params
	const float SPEED = 4.0f;
	const float ROT_SPEED = 90.0f;
	const float FIXED_DT = 1.0f / 60.0f;
	float accumulator = 0.0f;
	bool  isColliding = false;

	RB_player->GetRigidBody().setAngularLockAxisFactor(rp3d::Vector3(1.0, 1.0, 1.0));
	//RB_player->GetRigidBody().setLinearLockAxisFactor(rp3d::Vector3(1.0, 0.0, 0.0));
	//playerBody->setLinearLockAxisFactor
	//RB_player->GetRigidBody().setLinearDamping(8.0f);

	Mesh cubeMesh = GenMeshCube(2.0f, 2.0f, 2.0f);
	Material cubeMaterial = LoadMaterialDefault();

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		if (dt <= 0.0f || dt > 0.1f) dt = FIXED_DT;

		// --- move  ---
		rp3d::Vector3 currentVel = RB_wall->GetRigidBody().getLinearVelocity();

		rp3d::Vector3 input(0, 0, 0);
		if (IsKeyDown(KEY_W)) input.z += SPEED;
		if (IsKeyDown(KEY_S)) input.z -= SPEED;
		if (IsKeyDown(KEY_D)) input.x -= SPEED;
		if (IsKeyDown(KEY_A)) input.x += SPEED;
		if (IsKeyDown(KEY_E)) input.y += SPEED;
		if (IsKeyDown(KEY_Q)) input.y -= SPEED;



		rp3d::Vector3 newVel(
			input.x + currentVel.x,
			input.y + currentVel.y,
			input.z + currentVel.z
		);

		//MoveCharacter(&RB_player->GetRigidBody(), glm::vec3(input.x, input.y, input.z), SPEED);
		//Jump(&RB_player->GetRigidBody(), 5.0f);
		//playerBody->setLinearVelocity(newVel);
		RB_player->GetRigidBody().setLinearVelocity(newVel);

		//auto rotQuat = playerBody->getTransform().getOrientation();
		auto rotQuat = RB_player->GetRigidBody().getTransform().getOrientation();
		//auto aVel = playerBody->getAngularVelocity();
		auto aVel = RB_player->GetRigidBody().getAngularVelocity();
		// --- rotate ---
		if (IsKeyDown(KEY_LEFT))  aVel.x -= ROT_SPEED * dt;
		if (IsKeyDown(KEY_RIGHT)) aVel.x += ROT_SPEED * dt;
		if (IsKeyDown(KEY_DOWN))  aVel.y += ROT_SPEED * dt;
		if (IsKeyDown(KEY_UP))    aVel.y -= ROT_SPEED * dt;

		if (IsKeyDown(KEY_V))  RB_player->GetRigidBody().applyLocalForceAtLocalPosition({ 0, 0, 50 }, { 5, 0, 0 });
		if (IsKeyDown(KEY_B)) RB_player->GetRigidBody().applyLocalForceAtLocalPosition({ 0, 50, 0 }, { 5, 0, 0 });
		if (IsKeyDown(KEY_N))  RB_player->GetRigidBody().applyLocalForceAtLocalPosition({ 50, 0, 0 }, { 0, 0, 5 });

		if (IsKeyDown(KEY_C))  RB_player->ApplyLocalTorque({ 30,0,0 });

		if (IsKeyDown(KEY_G))
		{
			auto collider = RB_floor->FindChild<NodeCollider>();
			if (collider)
				collider->get().SetBounciness(collider->get().GetBounciness() + 0.1);
		}
		if (IsKeyDown(KEY_H))
		{
			auto collider = RB_floor->FindChild<NodeCollider>();
			if (collider)
				collider->get().SetBounciness(collider->get().GetBounciness() - 0.1);
		}


		//playerBody->setAngularVelocity(aVel);
		RB_player->GetRigidBody().setAngularVelocity(aVel);

		//playerBody->applyLocalForceAtLocalPosition({ 0.0,0.0,10.0 }, { 10.0,0.0,0.0 });
		//playerBody->applyLocalForceAtLocalPosition({ 0.0,0.0,10.0 }, {  0.0,0.0,10.0 }); // yaw
		//playerBody->applyLocalTorque({ 0.0,1000.0,100.0 });
		//playerBody->applyLocalForceAtLocalPosition({ 0.0,0.0,-1.0 }, { 1.0,0.0,0.0 }); // yaw


		// --- update physics ---
		accumulator += dt;
		while (accumulator >= FIXED_DT) {
			//world->update(FIXED_DT);
			//PhysicsServer::GetPhysicsWorld().update(FIXED_DT);
			PhysicsServer::UpdatePhysicsWorld(FIXED_DT);
			accumulator -= FIXED_DT;
		}
		RB_player->Update(dt);
		player->Update(dt);

		RB_wall->Update(dt);
		wall->Update(dt);
		RB_floor->Update(dt);
		floor->Update(dt);

		//rp3d::Vector3 p = playerBody->getTransform().getPosition();
		rp3d::Vector3 p = RB_player->GetRigidBody().getTransform().getPosition();
		pos = { p.x, p.y, p.z };

		// --- test overlap ---
		OverlapCB cb;
		PhysicsServer::GetPhysicsWorld().testOverlap(&RB_player->GetRigidBody(), cb);
		isColliding = cb.hit;

		// --- draw ---
		BeginDrawing();
		ClearBackground({ 20, 20, 30, 255 });

		BeginMode3D(cam);
		DrawGrid(30, 1.0f);

		glm::mat4 mat_player = player->GetWorldMatrix();

		auto getMat = [](glm::mat4 const& m) -> Matrix
			{
				return {
					m[0][0], m[1][0], m[2][0], m[3][0],
					m[0][1], m[1][1], m[2][1], m[3][1],
					m[0][2], m[1][2], m[2][2], m[3][2],
					m[0][3], m[1][3], m[2][3], m[3][3]
				};
			};

		Matrix rlMat_player = getMat(mat_player);


		auto draw = [&](Matrix const& mat, Color c)
			{
				cubeMaterial.maps[MATERIAL_MAP_DIFFUSE].color = c;
				DrawMesh(cubeMesh, cubeMaterial, mat);
			};


		draw(rlMat_player, BEIGE);

		// Mur
		DrawCube(WALL_POS, WALL_W, WALL_H, WALL_D, { 180, 140, 80, 255 });
		DrawCubeWires(WALL_POS, WALL_W, WALL_H, WALL_D, DARKBROWN);

		DrawCube(FLOOR_POS, FLOOR_W, FLOOR_H, FLOOR_D, { 130, 140, 95, 255 });
		DrawCubeWires(FLOOR_POS, FLOOR_W, FLOOR_H, FLOOR_D, DARKBROWN);

		EndMode3D();


		// HUD
		if (isColliding)
			DrawText(">>> COLLISION <<<", 20, 118, 20, RED);
		else
			DrawText("Aucune collision", 20, 118, 20, GREEN);

		DrawText(TextFormat("RB_Pos: (%.1f, %.1f, %.1f)", pos.x, pos.y, pos.z),
			10, GetScreenHeight() - 48, 16, BLACK);
		DrawText(TextFormat("PlayerPos: (%.1f, %.1f, %.1f)", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z),
			10, GetScreenHeight() - 26, 16, BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
