#ifndef ENGINE_SPHERE_HPP
#define ENGINE_SPHERE_HPP

#include "Mesh.hpp"
#include "../Math/Math.hpp"
#include <glm/glm.hpp>

namespace Engine
{
	class Sphere : public Mesh
	{
	public:
		Sphere(unsigned int xSegments, unsigned int ySegments)
		{
			for (unsigned int y = 0; y <= ySegments; ++y)
			{
				for (unsigned int x = 0; x <= xSegments; ++x)
				{
					float xSegment = (float)x / (float)xSegments;
					float ySegment = (float)y / (float)ySegments;
					float xPos = std::cos(xSegment * Math::TAU) * std::sin(ySegment * Math::PI); // TAU is 2PI
					float yPos = std::cos(ySegment * Math::PI);
					float zPos = std::sin(xSegment * Math::TAU) * std::sin(ySegment * Math::PI);

					Positions.push_back(glm::vec3(xPos, yPos, zPos));
					UV.push_back(glm::vec2(xSegment, ySegment));
					Normals.push_back(glm::vec3(xPos, yPos, zPos));
				}
			}

			bool oddRow = false;
			for (int y = 0; y < ySegments; ++y)
			{
				for (int x = 0; x < xSegments; ++x)
				{
					Indices.push_back((y + 1) * (xSegments + 1) + x);
					Indices.push_back(y       * (xSegments + 1) + x);
					Indices.push_back(y       * (xSegments + 1) + x + 1);

					Indices.push_back((y + 1) * (xSegments + 1) + x);
					Indices.push_back(y       * (xSegments + 1) + x + 1);
					Indices.push_back((y + 1) * (xSegments + 1) + x + 1);
				}
			}

			Topology = TRIANGLES;
			Finalize();
		}
	};
}


#endif // !ENGINE_SPHERE_HPP
