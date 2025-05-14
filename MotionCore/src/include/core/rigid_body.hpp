
#include "motion_core_header.h"

namespace MotionCore
{
	enum class ColliderType
	{
		Sphere,
		Box,
		Capsule,

		Count
	};


	struct SphereCollider
	{
		numeric radius;
	};

	struct BoxCollider
	{
		Tbx::Matrix3x3<numeric> orientation;
		Tbx::Vector3<numeric> size;
	};

	struct CapsuleCollider
	{
		Tbx::Matrix3x3<numeric> orientation;
		numeric height;
		numeric radius;
	};

	struct MeshCollider
	{
		uint32_t meshId;
	};


	struct Collider
	{
		ColliderType type;
		union 
		{
			SphereCollider sphereCollider;
			BoxCollider boxCollider;
			CapsuleCollider capsuleCollider;
			MeshCollider meshCollider;
		}colliderType;

	};

	
	struct RigidBody
	{
		numeric mass;
		Collider collider;
	};
}