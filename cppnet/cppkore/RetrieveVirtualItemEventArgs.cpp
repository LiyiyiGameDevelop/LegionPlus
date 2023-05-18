#include "stdafx.h"
#include "RetrieveVirtualItemEventArgs.h"

namespace ´°Ìו
{
	RetrieveVirtualItemEventArgs::RetrieveVirtualItemEventArgs(int32_t Index, int32_t SubIndex)
		: ItemIndex(Index), SubItemIndex(SubIndex), Text(""), Style()
	{
	}
}
