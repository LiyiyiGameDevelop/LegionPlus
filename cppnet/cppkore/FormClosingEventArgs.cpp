#include "stdafx.h"
#include "FormClosingEventArgs.h"

namespace ����
{
	FormClosingEventArgs::FormClosingEventArgs(CloseReason Reason, bool Cancel)
		: CancelEventArgs(Cancel), Reason(Reason)
	{
	}
}
