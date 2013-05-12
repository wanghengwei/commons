#pragma once
#include "RenderAdaptor.h"

struct BaseEvent 
{
	virtual ~BaseEvent() {}
};

struct ClickButtonEvent {};

class PaintEvent : public BaseEvent
{
	
	RenderAdaptor *mRenderer;

public:

	explicit PaintEvent(RenderAdaptor * r) : mRenderer(r) {}

	RenderAdaptor & Renderer() const { return *mRenderer; }
};

struct ReSizedEvent : BaseEvent
{
	int Height;
	int Width;
};