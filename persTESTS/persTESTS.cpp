#include "pch.h"
#include "CppUnitTest.h"

#include "../src/Objects/RigidBody.cpp"
#include "../src/Geometry/Plane.cpp"

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

	TEST_CLASS(PlaneTest)
	{
		TEST_METHOD(PlaneInitTest)
		{
			glm::vec3 PointZero = glm::vec3(0.0f, 1.0f, 2.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);

			Plane plane(NormalVector, PointZero);

			Assert::AreEqual(plane.getNormal().x, NormalVector.x);
			Assert::AreEqual(plane.getNormal().y, NormalVector.y);
			Assert::AreEqual(plane.getNormal().z, NormalVector.z);

			Assert::AreEqual(plane.getPoint().x, PointZero.x);
			Assert::AreEqual(plane.getPoint().y, PointZero.y);
			Assert::AreEqual(plane.getPoint().z, PointZero.z);
		}

		TEST_METHOD(PlaneChangingPositionTest)
		{
			glm::vec3 PointZero = glm::vec3(0.0f, 1.0f, 2.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 newPosition = glm::vec3(1.0f, 21.0f, -10.0f);
			
			Plane plane(NormalVector, PointZero);
		
			plane.ChangePosition(newPosition);

			Assert::AreEqual(plane.getPoint().x, newPosition.x);
			Assert::AreEqual(plane.getPoint().y, newPosition.y);
			Assert::AreEqual(plane.getPoint().z, newPosition.z);
		}
	};
}
