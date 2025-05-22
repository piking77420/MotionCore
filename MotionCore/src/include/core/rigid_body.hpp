
#include "motion_core_header.h"

namespace MotionCore
{
	enum class ShapeType
	{
		Sphere,
		Box,
		Capsule,

		Count
	};


	struct SphereShape
	{
		numeric radius;
	};

	struct BoxShape
	{
		Vec3 size;
	};

	struct CapsuleShape
	{
		Mat3 orientation;
		numeric height;
		numeric radius;
	};

	struct MeshShape
	{
		uint32_t meshId;
	};


	struct Shape
	{
		bool isTrigger;
		ShapeType type;
		union 
		{
			SphereShape sphereShape;
			BoxShape boxShape;
			CapsuleShape capsuleShape;
			MeshShape meshShape;
		}ShapeType;

	};

	
	struct RigidBody
	{
		numeric mass;
		Shape shape;

		Vec3 position;
		Vec3 velocity;
		Vec3 accmulateForce;

		Quat orientation;
		Vec3 rotation;
		
	};
}