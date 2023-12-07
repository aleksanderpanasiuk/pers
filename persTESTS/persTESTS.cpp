#include "pch.h"
#include "CppUnitTest.h"

#include "../src/Objects/RigidBody.cpp"
#include "../src/Geometry/Plane.cpp"

#include <glm/gtx/string_cast.hpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace persTESTS
{
	const float FLOAT_ERROR = 0.00001f;

	void compareVectors3(glm::vec3 a, glm::vec3 b)
	{
		Assert::AreEqual(a.x, b.x, FLOAT_ERROR);
		Assert::AreEqual(a.y, b.y, FLOAT_ERROR);
		Assert::AreEqual(a.z, b.z, FLOAT_ERROR);
	}

	void comparePlanes(std::vector<Plane> P1, std::vector<Plane> P2)
	{
		for (int i = 0; i < P1.size(); i++)
		{
			glm::vec3 expectedPlaneNormal = P2[i].getNormal();
			glm::vec3 expectedPlanePoint = P2[i].getPoint();

			glm::vec3 actualPlaneNormal = P1[i].getNormal();
			glm::vec3 actualPlanePoint = P1[i].getPoint();

			compareVectors3(expectedPlaneNormal, actualPlaneNormal);
			compareVectors3(expectedPlanePoint, actualPlanePoint);
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

			compareVectors3(rigidBody.getOrientation(), glm::vec3(0.0f, 0.0f, 0.0f));
			compareVectors3(rigidBody.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
			compareVectors3(rigidBody.getScale(), glm::vec3(1.0f, 1.0f, 1.0f));
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

			compareVectors3(plane.getNormal(), NormalVector);
			compareVectors3(plane.getPoint(), PointZero);
		}

		TEST_METHOD(PlaneChangingPositionTest)
		{
			glm::vec3 PointZero = glm::vec3(0.0f, 1.0f, 2.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 newPosition = glm::vec3(1.0f, 21.0f, -10.0f);
			
			Plane plane(NormalVector, PointZero);
		
			plane.ChangePosition(newPosition);

			compareVectors3(plane.getPoint(), newPosition);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
		}

		TEST_METHOD(PlaneRotationSameAxisNothingChangesTest)
		{
			glm::vec3 PointZero = glm::vec3(1.0f, 0.0f, 0.0f);
			glm::vec3 NormalVector = glm::vec3(1.0f, 0.0f, 0.0f);
			Plane plane(NormalVector, PointZero);

			glm::vec3 rotationPoint = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 rotation = glm::vec3(90.0f, 0.0f, 0.0f);

			plane.Rotate(rotationPoint, rotation);

			compareVectors3(plane.getPoint(), PointZero);
			compareVectors3(plane.getNormal(), NormalVector);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
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

			compareVectors3(plane.getPoint(), expectedPoint);
			compareVectors3(plane.getNormal(), expectedNormal);
		}
	};
}
