#pragma once
#include "../Widget.hpp"

class Hierarchy : public Widget
{
public:
	Hierarchy();
	void Tick() override;

private:
	void TreeShow();
};

