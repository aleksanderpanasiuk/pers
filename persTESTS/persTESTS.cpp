#include "pch.h"
#include "CppUnitTest.h"

#include "../src/Objects/RigidBody.cpp"
#include "../src/Geometry/Plane.cpp"

#include <glm/gtx/string_cast.hpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace persTESTS
{
	const float FLOAT_ERROR = 0.00001f;

	void comparePlanes(std::vector<Plane> P1, std::vector<Plane> P2)
	{
		for (int i = 0; i < P1.size(); i++)
		{
			glm::vec3 expectedPlaneNormal = P2[i].getNormal();
			glm::vec3 expectedPlanePoint = P2[i].getPoint();

			glm::vec3 actualPlaneNormal = P1[i].getNormal();
			glm::vec3 actualPlanePoint = P1[i].getPoint();

			Assert::AreEqual(expectedPlaneNormal.x, actualPlaneNormal.x, FLOAT_ERROR);
			Assert::AreEqual(expectedPlaneNormal.y, actualPlaneNormal.y, FLOAT_ERROR);
			Assert::AreEqual(expectedPlaneNormal.z, actualPlaneNormal.z, FLOAT_ERROR);

			Assert::AreEqual(expectedPlanePoint.x, actualPlanePoint.x, FLOAT_ERROR);
			Assert::AreEqual(expectedPlanePoint.y, actualPlanePoint.y, FLOAT_ERROR);
			Assert::AreEqual(expectedPlanePoint.z, actualPlanePoint.z, FLOAT_ERROR);
		}
	}

	TEST_CLASS(RigidBodyTest)
	{
		TEST_METHOD(RigidBodyInitTest)
		{
			RigidBody rigidBody(
				RigidCube,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				true, 1.0f
			);

			Assert::IsTrue(rigidBody.isAffectedByForces);
			Assert::AreEqual(rigidBody.getMass(), 1.0f);
			Assert::AreEqual((int)rigidBody.getType(), (int)RigidCube);
			Assert::AreEqual(glm::to_string(rigidBody.getOrientation()).c_str(), "vec3(0.000000, 0.000000, 0.000000)");
			Assert::AreEqual(glm::to_string(rigidBody.getPosition()).c_str(), "vec3(0.000000, 0.000000, 0.000000)");
			Assert::AreEqual(glm::to_string(rigidBody.getScale()).c_str(), "vec3(1.000000, 1.000000, 1.000000)");
		}

		TEST_METHOD(RigidBodyGetPlanesTest)
		{
			RigidBody rigidBody(
				RigidCube,
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				true, 1.0f
			);

			std::vector<Plane> ExpectedPlanes = {
				Plane(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f)),
				Plane(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(-0.5f, 0.0f, 0.0f)), 
				Plane(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -0.5f, 0.0f)), 
				Plane(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f)),
				Plane(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, -0.5f)),
				Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.5f)),
			};

			std::vector<Plane> planes = rigidBody.getPlanes();

			comparePlanes(planes, ExpectedPlanes);
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

		TEST_METHOD(PlaneRotationOneAxisSimplePointTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 90.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 expectedNormal = glm::vec3(0.0f, 1.0f, 0.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationSameAxisNothingChangesTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 0.0f, 0.0f);

			plane.Rotate(rotationPoint, rotation);
			

			Assert::AreEqual(plane.getPoint().x, PointZero.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, PointZero.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, PointZero.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, NormalVector.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, NormalVector.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, NormalVector.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationOneAxisNonZeroPointTest)
		{
			glm::vec3 PointZero = glm::vec3(2.0f, 0.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 90.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(1.0f, 1.0f, 0.0f);
			glm::vec3 expectedNormal = glm::vec3(0.0f, 1.0f, 0.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationTwoAxesSimplePointTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 90.0f, 0.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 expectedNormal = glm::vec3(0.0f, 0.0f, -1.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationTwoAxesNonZeroPointTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 1.0f, -1.0f);
			glm::vec3 NormalVector = glm::vec3(0.0f, 0.0f, -1.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(1.0f, 1.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 90.0f, 0.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(1.0f, 2.0f, 0.0f);
			glm::vec3 expectedNormal = glm::vec3(0.0f, 1.0f, 0.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationThreeAxesSimplePointTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 1.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 90.0f, 90.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(0.0f, 1.0f, -1.0f);
			glm::vec3 expectedNormal = glm::vec3(0.0f, 0.0f, -1.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}

		TEST_METHOD(PlaneRotationThreeAxesNonZeroPointTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 1.0f, -1.0f);
			glm::vec3 NormalVector = glm::vec3(0.0f, 0.0f, -1.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(1.0f, 1.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 90.0f, 90.0f);

			plane.Rotate(rotationPoint, rotation);

			glm::vec3 expectedPoint = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 expectedNormal = glm::vec3(-1.0f, 0.0f, 0.0f);

			Assert::AreEqual(plane.getPoint().x, expectedPoint.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().y, expectedPoint.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getPoint().z, expectedPoint.z, FLOAT_ERROR);

			Assert::AreEqual(plane.getNormal().x, expectedNormal.x, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().y, expectedNormal.y, FLOAT_ERROR);
			Assert::AreEqual(plane.getNormal().z, expectedNormal.z, FLOAT_ERROR);
		}
	};
}
