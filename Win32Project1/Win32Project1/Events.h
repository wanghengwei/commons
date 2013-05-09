#pragma once
#include "RenderAdaptor.h"

struct ClickButtonEvent {};

class PaintEvent 
{
	
	RenderAdaptor *mRenderer;

public:

	explicit PaintEvent(RenderAdaptor * r) : mRenderer(r) {}

	RenderAdaptor & Renderer() const { return *mRenderer; }
};