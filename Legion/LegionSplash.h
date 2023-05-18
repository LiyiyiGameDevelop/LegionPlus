#pragma once

#include <Kore.h>
#include "PaintEventArgs.h"
#include "CreateParams.h"

class LegionSplash : public ����::Form
{
public:
	LegionSplash();
	virtual ~LegionSplash() = default;

	virtual void OnPaint(const std::unique_ptr<����::PaintEventArgs>& EventArgs);
	virtual void OnLoad();

protected:
	// Get custom control creation parameters for this instance.
	virtual ����::CreateParams GetCreateParams();

private:
	// Internal routine to setup the component
	void InitializeComponent();
	// Internal reference to the splash image
	std::unique_ptr<Gdiplus::Image> SplashImage;

	// Internal routine for the timer
	static void SleepTimer(void* Sender);
};