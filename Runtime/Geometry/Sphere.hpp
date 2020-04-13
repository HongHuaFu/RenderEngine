#pragma once

#include "../Render/Mesh.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace RE
{
	class Sphere : public Mesh
	{
	public:
		Sphere(unsigned int xSegments, unsigned int ySegments)
		{
			float pi = glm::pi<float>();
			float pi2 = pi + pi;
			
			for (unsigned int y = 0; y <= ySegments; ++y)
			{
				for (unsigned int x = 0; x <= xSegments; ++x)
				{
					float xSegment = (float)x / (float)xSegments;
					float ySegment = (float)y / (float)ySegments;
					float xPos = std::cos(xSegment * pi2) * std::sin(ySegment * pi);
					float yPos = std::cos(ySegment * pi);
					float zPos = std::sin(xSegment * pi2) * std::sin(ySegment * pi);

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
					Indices.push_back(y * (xSegments + 1) + x);
					Indices.push_back(y * (xSegments + 1) + x + 1);

					Indices.push_back((y + 1) * (xSegments + 1) + x);
					Indices.push_back(y * (xSegments + 1) + x + 1);
					Indices.push_back((y + 1) * (xSegments + 1) + x + 1);
				}
			}

			Topology = TOPOLOGY::TRIANGLES;
			Finalize();
		}
	};
}


