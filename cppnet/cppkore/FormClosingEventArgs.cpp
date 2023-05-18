#include "stdafx.h"
#include "FormClosingEventArgs.h"

namespace ´°Ìו
{
	FormClosingEventArgs::FormClosingEventArgs(CloseReason Reason, bool Cancel)
		: CancelEventArgs(Cancel), Reason(Reason)
	{
	}
}
