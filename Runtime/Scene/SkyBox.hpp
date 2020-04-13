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
		RE::Material* m_Hdr2CubeMap;
	public:
		SkyBox();
		~SkyBox();

		void SetCubemap(Texture* hdr);
		void SetCubemap(TextureCube* cubemap);
	};
}

