#pragma once

#include "../Render/Pipeline.hpp"

// 前向渲染
// 兰伯特光照

namespace RE
{
	class Material;
	class RenderTarget;
	class Mesh;
	class SceneNode;
	class TextureCube;
	class Texture;

	class PP_Defferd_Lambert : public Pipeline
	{
	public:
		virtual void Start(Renderer* renderer) override;
		virtual void RenderPushCommand(Renderer* renderer) override;

	private:
		Renderer* m_Renderer;
	};
}