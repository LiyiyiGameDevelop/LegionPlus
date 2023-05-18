#pragma once

#include <Kore.h>

#include "UIXButton.h"
#include "UIXTextBox.h"
#include "UIXLabel.h"
#include "UIXListView.h"

#include "RpakLib.h"
#include "bsplib.h"
#include "MilesLib.h"
#include "ApexAsset.h"
#include "ExportAsset.h"
#include "ExportManager.h"
#include "LegionPreview.h"
#include "LegionProgress.h"

class LegionMain : public ����::Form
{
public:
	LegionMain();
	virtual ~LegionMain() = default;

	// Reloads the view
	void RefreshView();
	// Resets display indices
	void ResetDisplayIndices();
	// Internal routine to load a file
	void LoadApexFile(const List<string>& File);

	void SetAssetError(int32_t AssetIndex);
protected:
	static void OnLoadClick(����::Control* Sender);
	static void OnSettingsClick(����::Control* Sender);
	static void OnExpClick(����::Control* Sender);
	static void OnExpAllClick(����::Control* Sender);
	static void OnSearchClick(����::Control* Sender);
	static void OnClearClick(����::Control* Sender);
	static void OnTitanfallClick(����::Control* Sender);
	static void OnRefreshClick(����::Control* Sender);
	static void OnListRightClick(const std::unique_ptr<MouseEventArgs>& EventArgs, ����::Control* Sender);
	static void OnListDoubleClick(����::Control* Sender);
	static void OnListKeyUp(const std::unique_ptr<KeyEventArgs>& EventArgs, ����::Control* Sender);
	static void OnListKeyPressed(const std::unique_ptr<KeyPressEventArgs>& EventArgs, ����::Control* Sender);
	static void OnSearchKeyPressed(const std::unique_ptr<KeyPressEventArgs>& EventArgs, ����::Control* Sender);
	static void OnSelectedIndicesChanged(const std::unique_ptr<����::ListViewVirtualItemsSelectionRangeChangedEventArgs>& EventArgs, ����::Control* Sender);
	static void GetVirtualItem(const std::unique_ptr<����::RetrieveVirtualItemEventArgs>& EventArgs, ����::Control* Sender);

	// A trampoline for the callback, then, invoke normal method...
	static void ExportProgressCallback(uint32_t Progress, ����::Form* MainForm, bool Finished);
	static bool CheckStatusCallback(int32_t AssetIndex, ����::Form* MainForm);

private:
	// Internal routine to setup the component
	void InitializeComponent();
	// Internal routine to export selected assets
	void ExportSelectedAssets();
	// Internal routine to export all assets
	void ExportAllAssets();
	// Internal routine to search for assets
	void SearchForAssets();
	// Internal routine to export a single asset
	void ExportSingleAsset();

	// A lock for exporting
	bool IsInExportMode;

	// Internal routine to change the progress value
	void ExportProgressChanged(uint32_t Progress, bool Finished);
	bool CheckStatus(int32_t AssetIndex);
	void DoPreviewSwap();

	std::unique_ptr<Assets::Texture> MaterialStreamCallback(string Source, uint64_t Hash);

	// Internal controls reference
	UIX::UIXButton* TitanfallConverterButton;
	UIX::UIXButton* ClearSearchButton;
	UIX::UIXLabel* StatusLabel;
	UIX::UIXButton* SearchButton;
	UIX::UIXTextBox* SearchBox;
	UIX::UIXButton* ExportAllButton;
	UIX::UIXButton* ExportSelectedButton;
	UIX::UIXButton* LoadRPakButton;
	UIX::UIXButton* SettingsButton;
	UIX::UIXButton* RefreshAssetsButton;
	UIX::UIXListView* AssetsListView;

	// Internal RPak buffer
	std::unique_ptr<RpakLib> RpakFileSystem;
	// Internal Miles buffer
	std::unique_ptr<MilesLib> MilesFileSystem;

	// Converted assets for the list...
	std::unique_ptr<List<ApexAsset>> LoadedAssets;
	
	// List of display indices for the list...
	List<uint32_t> DisplayIndices;

	// Preview window
	std::unique_ptr<LegionPreview> PreviewWindow;
	// Table Preview window
	std::unique_ptr<class LegionTablePreview> TablePreviewWindow;
	// Progress window
	std::unique_ptr<LegionProgress> ProgressWindow;

	// Internal load path
	List<string> LoadPath;
};

extern LegionMain* g_pLegionMain;