#pragma once

#include <cstdint>
#include "CancelEventArgs.h"
#include "CloseReason.h"

namespace ����
{
	// Provides data for the on closing event.
	class FormClosingEventArgs : public CancelEventArgs
	{
	public:
		FormClosingEventArgs(CloseReason Reason, bool Cancel);
		~FormClosingEventArgs() = default;

		// Provides the reason for the form close.
		CloseReason Reason;
	};
}