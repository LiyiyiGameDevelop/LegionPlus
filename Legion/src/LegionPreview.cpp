#include "pch.h"
#include "LegionPreview.h"

LegionPreview::LegionPreview()
	: ����::Form()
{
	this->InitializeComponent();
}

void LegionPreview::AssignPreviewModel(const Assets::Model& Model, const string& Name, uint64_t DebugVersion)
{
	this->ModelPreview->SetViewModel(Model);
	this->ModelPreview->SetAssetName(Name);
	this->ModelPreview->SetDebugVersion(DebugVersion);
}

void LegionPreview::AssignPreviewImage(const Assets::Texture& Texture, const string& Name, uint64_t DebugVersion)
{
	this->ModelPreview->SetViewTexture(Texture);
	this->ModelPreview->SetAssetName(Name);
	this->ModelPreview->SetDebugVersion(DebugVersion);
}

void LegionPreview::SetMaterialStreamer(Assets::AssetRenderer::MaterialStreamCallback Callback)
{
	this->ModelPreview->SetMaterialStreamer(Callback);
}

Assets::AssetRenderer* LegionPreview::GetRenderer()
{
	return this->ModelPreview;
}

void LegionPreview::InitializeComponent()
{
	this->SuspendLayout();
	this->SetAutoScaleDimensions({ 6, 13 });
	this->SetAutoScaleMode(����::AutoScaleMode::Font);
	this->SetText("Asset Preview");
	this->SetClientSize({ 775, 481 });
	this->SetMinimumSize({ 791, 520 });
	this->SetStartPosition(����::FormStartPosition::CenterScreen);

	this->ModelPreview = new Assets::AssetRenderer();
	this->ModelPreview->SetSize({ 775, 481 });
	this->ModelPreview->SetBackColor({ 33, 33, 33 });
	this->ModelPreview->SetAnchor(����::AnchorStyles::Top | ����::AnchorStyles::Left | ����::AnchorStyles::Right | ����::AnchorStyles::Bottom);
	this->AddControl(this->ModelPreview);

	this->ResumeLayout(false);
	this->PerformLayout();
	// END DESIGNER CODE
}
