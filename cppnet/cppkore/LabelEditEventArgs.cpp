#include "stdafx.h"
#include "LabelEditEventArgs.h"

namespace ����
{
	LabelEditEventArgs::LabelEditEventArgs(int32_t Item)
		: Item(Item), Label(""), CancelEdit(false)
	{
	}

	LabelEditEventArgs::LabelEditEventArgs(int32_t Item, const string& Label)
		: Item(Item), Label(Label), CancelEdit(false)
	{
	}
}
