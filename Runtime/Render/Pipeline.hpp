#pragma once

namespace RE
{
	class Renderer;
	class Pipeline
	{
	public:
		Pipeline() { }
		virtual ~Pipeline() { }

		virtual void Start(){ }
		virtual void RenderPushCommand(Renderer* renderer){ }
	};
}