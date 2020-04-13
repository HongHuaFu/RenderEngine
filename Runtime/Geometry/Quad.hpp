#pragma once

#include "../Render/Mesh.hpp"

namespace RE
{
	class Quad: public Mesh
	{
	public:
		Quad()
		{
			Positions =
			{
				{ -1.0f,  1.0f, 0.0f, }, // 3
				{ -1.0f, -1.0f, 0.0f, }, // 2
				{  1.0f,  1.0f, 0.0f, }, // 0
				{  1.0f, -1.0f, 0.0f, }, // 1
			};
			UV = 
			{
				{ 0.0f, 1.0f, },
				{ 0.0f, 0.0f, },
				{ 1.0f, 1.0f, },
				{ 1.0f, 0.0f, },
			};


			Topology = TOPOLOGY::TRIANGLE_STRIP;

			Finalize();
		}


		Quad(float width,float height)
		{
			Positions =
			{
				{ -width,  height, 0.0f, },
				{ -width, -height, 0.0f, },
				{  width,  height, 0.0f, },
				{  width, -height, 0.0f, },
			};
			UV = 
			{
				{ 0.0f, 1.0f, },
				{ 0.0f, 0.0f, },
				{ 1.0f, 1.0f, },
				{ 1.0f, 0.0f, },
			};

			Topology = TOPOLOGY::TRIANGLE_STRIP;

			Finalize();
		}
	};
}


