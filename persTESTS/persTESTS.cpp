#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Objects/RigidBody.cpp"
#include <glm/gtx/string_cast.hpp>

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

			Assert::IsTrue(rigidBody.isAffectedByForces);
			Assert::AreEqual(rigidBody.getMass(), 1.0f);
			Assert::AreEqual((int)rigidBody.getType(), (int)RigidCube);
			Assert::AreEqual(glm::to_string(rigidBody.getOrientation()).c_str(), "vec3(0.000000, 0.000000, 0.000000)");
			Assert::AreEqual(glm::to_string(rigidBody.getPosition()).c_str(), "vec3(0.000000, 0.000000, 0.000000)");
			Assert::AreEqual(glm::to_string(rigidBody.getScale()).c_str(), "vec3(0.000000, 0.000000, 0.000000)");
		}
	};
}
