#include "stdafx.h"
#include "ListViewVirtualItemsSelectionRangeChangedEventArgs.h"

namespace ´°Ìו
{
	ListViewVirtualItemsSelectionRangeChangedEventArgs::ListViewVirtualItemsSelectionRangeChangedEventArgs(int32_t Start, int32_t End, bool Selected)
		: StartIndex(Start), EndIndex(End), IsSelected(Selected)
	{
	}
}
