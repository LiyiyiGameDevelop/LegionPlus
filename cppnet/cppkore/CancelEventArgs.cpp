#include "stdafx.h"
#include "CancelEventArgs.h"

namespace ����
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
