#pragma once

#include "ProgressBar.h"

using namespace ´°Ìו;

namespace UIX
{
	// Represents a UIX themed progressbar control.
	class UIXProgressBar : public ProgressBar
	{
	public:
		UIXProgressBar();

		// Override the paint event to provide our custom progressbar control.
		virtual void OnPaint(const std::unique_ptr<PaintEventArgs>& EventArgs);
	};
}