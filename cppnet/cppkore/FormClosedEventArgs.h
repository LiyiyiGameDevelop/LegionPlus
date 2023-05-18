#pragma once

#include <cstdint>
#include "CloseReason.h"

namespace ´°Ìו
{
	// Provides data for the on closed event.
	class FormClosedEventArgs
	{
	public:
		FormClosedEventArgs(CloseReason Reason);
		~FormClosedEventArgs() = default;

		// Provides the reason for the form close.
		CloseReason Reason;
	};
}