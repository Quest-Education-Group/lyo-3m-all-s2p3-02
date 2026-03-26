#ifndef FOUNDRY_PHYSICSMANAGER__H_
#define FOUNDRY_PHYSICSMANAGER__H_



#include <optional>

class Node3D;

struct RaycastHit
{
	glm::vec3 impactPos;
	glm::vec3 normal;
	float dist;
	Node3D* node; // plutot Node RigidBody ?
};

class PhysicsManager
{
	//static RaycastHit* RaycastClosest(const glm::vec3&  origin, const glm::vec3 direction, float maxDist = 1000, uint16 mask = 0xFFFF);
	static std::optional<RaycastHit> RaycastClosest(const glm::vec3& origin, const glm::vec3 direction, float maxDist = 1000, uint16 mask = 0xFFFF);
	static std::vector<RaycastHit> RaycastAll(const glm::vec3& origin, const glm::vec3 direction, float maxDist = 1000, uint16 mask = 0xFFFF);

	void SetGravity(float gravity);
	glm::vec3 GetGravity();
};



#endif FOUNDRY_PHYSICSMANAGER__H_
