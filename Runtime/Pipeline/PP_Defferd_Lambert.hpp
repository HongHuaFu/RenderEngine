#pragma once

#include "../Render/Pipeline.hpp"

// ǰ����Ⱦ
// �����ع���

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