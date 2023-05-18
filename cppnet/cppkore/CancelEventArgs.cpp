#include "stdafx.h"
#include "CancelEventArgs.h"

namespace ´°Ìו
{
	CancelEventArgs::CancelEventArgs()
		: CancelEventArgs(false)
	{
	}

	CancelEventArgs::CancelEventArgs(bool Cancel)
		: Cancel(Cancel)
	{
	}
}
