#ifndef FOUNDRY_RAYCASTPROXY__H_
#define FOUNDRY_RAYCASTPROXY__H_

//#include <Define.h>
//
//#include <glm/vec3.hpp>
//#include <vector>

#include <optional>

class Node3D;

namespace HelperCallBack
{
	class RaycastCB : public rp3d::RaycastCallback
	{
	public:
		std::vector<RaycastHit> hits;

		rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info) override
		{
			hits.push_back({
				rp3dToGlm(info.worldPoint),
				rp3dToGlm(info.worldNormal),
				info.hitFraction,
				static_cast<Node3D*>(info.body->getUserData()) // plutot Node RigidBody ?
				});
			return 1.0;
		}
	};
};

namespace PhysicsProxy
{

	struct RaycastHit
	{
		glm::vec3 impactPos;
		glm::vec3 normal;
		float dist;
		Node3D* node; // plutot Node RigidBody ?
	};


	inline auto RaycastClosest = sol::overload(
		[](const glm::vec3& origin, const glm::vec3 direction, float maxDist = 1000, uint16 mask = 0xFFFF)
		{
			rp3d::Ray ray(origin, origin + dir * maxDist);
			HelperCallBack::RaycastCB cb;

			PhysicsServer::GetPhysicsWorld().raycast(ray, cb, mask);

			if (cb.hits.empty())
				return nullptr;

			// Can't simply get the first hit returned because the lib doesn't guarantee the order of the hits
			float minDist = maxDist;
			int closest = 0;
			for (int i = 0; i < cb.hits.size(); i++)
			{
				if (hit.dist < minDist)
				{
					minDist = hit.dist;
					closest = i;
				}
			}
			return cb.hits[closest];
		}
	);

	inline auto RaycastAll = sol::overload(
		[](const glm::vec3& origin, const glm::vec3 direction, float maxDist = 1000, uint16 mask = 0xFFFF)
		{
			rp3d::Ray ray(origin, origin + dir * maxDist);
			HelperCallBack::RaycastCB cb;

			PhysicsServer::GetPhysicsWorld().raycast(ray, cb, mask);

			return cb.hits;
		}
	);

	inline auto SetGravity = sol::overload(
		[](float gravity)
		{
			PhysicsServer::SetGravity(gravity);
		}
	);

	inline auto GetGravity = sol::overload(
		[](float gravity)
		{
			return PhysicsServer::GetGravity();
		}
	);

	struct PhysicsProxyBinding {
		static void Bind(Binder& binder)
		{
			auto physics = binder.GetOrCreateNamespace("physics");

			physics.set_function("RaycastClosest", PhysicsProxy::RaycastClosest);
			physics.set_function("RaycastAll", PhysicsProxy::RaycastAll);
			physics.set_function("SetGravity", PhysicsProxy::SetGravity);
			physics.set_function("GetGravity", PhysicsProxy::GetGravity);
		}
	};
};

REGISTER_PROXY(PhysicsProxyBinding, PhysicsProx);

#endif // FOUNDRY_RAYCASTPROXY__H_