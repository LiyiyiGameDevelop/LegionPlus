#include "stdafx.h"
#include "ListViewVirtualItemsSelectionRangeChangedEventArgs.h"

namespace ����
{
	ListViewVirtualItemsSelectionRangeChangedEventArgs::ListViewVirtualItemsSelectionRangeChangedEventArgs(int32_t Start, int32_t End, bool Selected)
		: StartIndex(Start), EndIndex(End), IsSelected(Selected)
	{
	}
}
