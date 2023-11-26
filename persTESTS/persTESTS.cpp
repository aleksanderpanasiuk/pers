#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Objects/RigidBody.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace persTESTS
{
	TEST_CLASS(persTESTS)
	{
	public:
		
		
	};

	TEST_CLASS(RigidBodyTest)
	{
		TEST_METHOD(RigidBodyInitTest)
		{
			RigidBody rigidBody(
				RigidCube,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				true, 1.0f
			);

			Assert::AreEqual(rigidBody.isAffectedByForces, true);
		}
	};
}
