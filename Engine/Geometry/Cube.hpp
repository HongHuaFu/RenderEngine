#ifndef ENGINE_CUBE_HPP
#define ENGINE_CUBE_HPP

#include "Mesh.hpp"

namespace Engine
{
	/* 

	A 3D cube in the range [-0.5, 0.5]. Vertices are hard-coded.

	*/
	class Cube : public Mesh
	{
	public:
		Cube();
	};
}

#endif // !ENGINE_CUBE_HPP
