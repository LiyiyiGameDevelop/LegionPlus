#pragma once

#include "ListView.h"

namespace UIX
{
	// Represents a UIX themed listview header control.
	class UIXListViewHeader
	{
	public:
		UIXListViewHeader(HWND Handle, ����::ListView* Parent);

		// The standard windows message pump for this control.
		virtual void WndProc(����::Message& Msg);
		// Invokes the default window procedure associated with this Window. It is
		// an error to call this method when the Handle property is zero.
		void DefWndProc(����::Message& Msg);

	protected:
		// The control handle
		HWND _Handle;

		// The parent listview
		����::ListView* _Parent;

		// An internal routine that is the root window message processor.
		static LRESULT CALLBACK InternalWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	};
}