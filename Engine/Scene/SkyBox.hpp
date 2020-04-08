#ifndef ENGINE_SKYBOX_HPP
#define ENGINE_SKYBOX_HPP

#include "SceneNode.hpp"

namespace Engine
{
	class TextureCube;
	class Material;
	class Shader;
	class Renderer;
	class Cube;

	class SkyBox : public SceneNode
	{
	private:
		TextureCube* m_CubeMap;
		Shader* m_Shader;

	public:
		SkyBox();
		~SkyBox();

		void SetCubemap(TextureCube* cubemap);
	};
}

#endif // !ENGINE_SKYBOX_HPP
