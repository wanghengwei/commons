#include "stdafx.h"
#include "RectButton.h"
#include "state.h"

Output RectButton::Transit(PaintEvent const &e)
{
	return [&e, this]()
	{
		this->Draw(e.Renderer(), Color::Red);
	};
}