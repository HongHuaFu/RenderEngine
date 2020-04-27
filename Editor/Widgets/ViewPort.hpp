#pragma once
#include "../Widget.hpp"

namespace RE
{
	class Renderer;
}

class ViewPort : public Widget
{
public:
	ViewPort(RE::Renderer* renderer);
	void Tick() override;

private:
	float m_timeSinceLastResChange  = 0.0f;
	float m_window_padding  = 4.0f;
	RE::Renderer* m_Renderer;
};
