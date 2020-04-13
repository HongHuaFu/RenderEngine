#pragma once

#include "Pipeline.hpp"

namespace RE
{
	class PBRPipeline : public Pipeline
	{
	public:
		virtual void Start() override;
		virtual void RenderPushCommand(Renderer* renderer) override;
	};

}

