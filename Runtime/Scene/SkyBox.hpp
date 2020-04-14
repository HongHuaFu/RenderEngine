#pragma once

#include "SceneNode.hpp"


namespace RE
{
	class TextureCube;
	class Texture;

	class SkyBox : public SceneNode
	{
	private:
		TextureCube* m_CubeMap;
	public:
		SkyBox();
		~SkyBox();

		void SetCubemap(TextureCube* cubemap);
	};
}

