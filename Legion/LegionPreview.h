#pragma once

#include <Kore.h>

class LegionPreview : public ����::Form
{
public:
	LegionPreview();
	virtual ~LegionPreview() = default;

	// Assign the preview model
	void AssignPreviewModel(const Assets::Model& Model, const string& Name, uint64_t DebugVersion);
	// Assign the preview image
	void AssignPreviewImage(const Assets::Texture& Texture, const string& Name, uint64_t DebugVersion);

	// Sets the material preview loading routine
	void SetMaterialStreamer(Assets::AssetRenderer::MaterialStreamCallback Callback);

	Assets::AssetRenderer* GetRenderer();

private:
	// Internal routine to setup the component
	void InitializeComponent();

	// Internal controls reference
	Assets::AssetRenderer* ModelPreview;
};