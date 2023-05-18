#pragma once

#include <memory>
#include "DrawingBase.h"
#include "ContentAlignment.h"
#include "UIXRenderer.h"

namespace Themes
{
	class KoreTheme : public UIX::UIXRenderer
	{
	public:
		KoreTheme();
		virtual ~KoreTheme();

	private:
		// Inherited via UIXRenderer
		virtual void RenderControlBackground(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlButtonBackground(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlText(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State, Drawing::Rectangle LayoutRect, Drawing::ContentAlignment Alignment) const override;
		virtual void RenderControlGlyph(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlCheckBoxBorder(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlCheckBoxCheck(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlRadioBorder(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlRadioCheck(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlGroupBox(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlBorder(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State) const override;
		virtual void RenderControlProgressFill(const std::unique_ptr<窗体::PaintEventArgs>& EventArgs, 窗体::Control* Ctrl, UIX::UIXRenderState State, uint32_t Progress) const override;

		// Inherited via UIXRenderer
		virtual void RenderControlListHeader(const std::unique_ptr<Drawing::BufferedGraphics>& EventArgs) const override;
		virtual void RenderControlListColumnHeader(const std::unique_ptr<窗体::DrawListViewColumnHeaderEventArgs>& EventArgs, 窗体::Control* Ctrl) const override;
		virtual void RenderControlListItem(const std::unique_ptr<窗体::DrawListViewItemEventArgs>& EventArgs, 窗体::Control* Ctrl, Drawing::Rectangle SubItemBounds) const override;
		virtual void RenderControlListSubItem(const std::unique_ptr<窗体::DrawListViewSubItemEventArgs>& EventArgs, 窗体::Control* Ctrl) const override;

		// Inherited via UIXRenderer
		virtual void RenderControlToolTip(const std::unique_ptr<窗体::DrawToolTipEventArgs>& EventArgs, 窗体::Control* Ctrl) const override;

		// Inherited via UIXRenderer
		virtual Drawing::Color GetRenderColor(UIX::UIXRenderColor Color) const override;
	};
}