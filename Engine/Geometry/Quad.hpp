#ifndef ENGINE_QUAD_HPP
#define ENGINE_QUAD_HPP

#include "Mesh.hpp"

namespace Engine
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


			Topology = TRIANGLE_STRIP;

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

			Topology = TRIANGLE_STRIP;

			Finalize();
		}
	};
}

#endif // !ENGINE_QUAD_HPP
