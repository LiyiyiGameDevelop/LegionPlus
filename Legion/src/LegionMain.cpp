#include "pch.h"
#include "LegionMain.h"

#include "UIXButton.h"
#include "UIXTextBox.h"
#include "UIXListView.h"
#include "LegionSettings.h"
#include "LegionTitanfallConverter.h"
#include "LegionTablePreview.h"
#include <version.h>

LegionMain::LegionMain()
	: 窗体::Form(), IsInExportMode(false)
{
	g_pLegionMain = this;
	this->InitializeComponent();
}

void LegionMain::InitializeComponent()
{
	this->SuspendLayout();
	this->SetAutoScaleDimensions({ 6, 13 });
	this->SetAutoScaleMode(窗体::AutoScaleMode::Font);
	this->SetText("Legion+ " UI_VER_STR);
	this->SetClientSize({ 844, 481 });
	this->SetMinimumSize({ 791, 520 });
	this->SetStartPosition(窗体::FormStartPosition::CenterScreen);

	this->TitanfallConverterButton = new UIX::UIXButton();
	this->TitanfallConverterButton->SetSize({ 78, 27 });
	this->TitanfallConverterButton->SetLocation({ 290, 446 });
	this->TitanfallConverterButton->SetTabIndex(9);
	this->TitanfallConverterButton->SetText("Titanfall 2");
	this->TitanfallConverterButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left);
	this->TitanfallConverterButton->Click += &OnTitanfallClick;
	this->AddControl(this->TitanfallConverterButton);

	this->RefreshAssetsButton = new UIX::UIXButton();
	this->RefreshAssetsButton->SetSize({ 78, 27 });
	this->RefreshAssetsButton->SetLocation({ 374, 446 });
	this->RefreshAssetsButton->SetTabIndex(9);
	this->RefreshAssetsButton->SetText("刷新");
	this->RefreshAssetsButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left);
	this->RefreshAssetsButton->Click += &OnRefreshClick;
	this->AddControl(this->RefreshAssetsButton);

	this->ClearSearchButton = new UIX::UIXButton();
	this->ClearSearchButton->SetSize({ 85, 24 });
	this->ClearSearchButton->SetLocation({ 381, 8 });
	this->ClearSearchButton->SetTabIndex(8);
	this->ClearSearchButton->SetText("清晰");
	this->ClearSearchButton->SetVisible(false);
	this->ClearSearchButton->SetAnchor(窗体::AnchorStyles::Top | 窗体::AnchorStyles::Left);
	this->ClearSearchButton->Click += &OnClearClick;
	this->AddControl(this->ClearSearchButton);

	this->StatusLabel = new UIX::UIXLabel();
	this->StatusLabel->SetSize({ 255, 24 });
	this->StatusLabel->SetLocation({ 577, 8 });
	this->StatusLabel->SetTabIndex(7);
	this->StatusLabel->SetText("空闲");
	this->StatusLabel->SetAnchor(窗体::AnchorStyles::Top | 窗体::AnchorStyles::Right);
	this->StatusLabel->SetTextAlign(Drawing::ContentAlignment::MiddleRight);
	this->AddControl(this->StatusLabel);

	this->SearchButton = new UIX::UIXButton();
	this->SearchButton->SetSize({ 85, 24 });
	this->SearchButton->SetLocation({ 290, 8 });
	this->SearchButton->SetTabIndex(6);
	this->SearchButton->SetText("搜索");
	this->SearchButton->SetAnchor(窗体::AnchorStyles::Top | 窗体::AnchorStyles::Left);
	this->SearchButton->Click += &OnSearchClick;
	this->AddControl(this->SearchButton);

	this->SearchBox = new UIX::UIXTextBox();
	this->SearchBox->SetSize({ 272, 24 });
	this->SearchBox->SetLocation({ 12, 8 });
	this->SearchBox->SetTabIndex(5);
	this->SearchBox->SetAnchor(窗体::AnchorStyles::Top | 窗体::AnchorStyles::Left);
	this->SearchBox->KeyPress += &OnSearchKeyPressed;
	this->AddControl(this->SearchBox);

	this->ExportAllButton = new UIX::UIXButton();
	this->ExportAllButton->SetSize({ 78, 27 });
	this->ExportAllButton->SetLocation({ 206, 446});
	this->ExportAllButton->SetTabIndex(4);
	this->ExportAllButton->SetText("全部导出");
	this->ExportAllButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left);
	this->ExportAllButton->Click += &OnExpAllClick;
	this->AddControl(this->ExportAllButton);

	this->ExportSelectedButton = new UIX::UIXButton();
	this->ExportSelectedButton->SetSize({ 97, 27 });
	this->ExportSelectedButton->SetLocation({ 103, 446});
	this->ExportSelectedButton->SetTabIndex(3);
	this->ExportSelectedButton->SetText("导出所选内容");
	this->ExportSelectedButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left);
	this->ExportSelectedButton->Click += &OnExpClick;
	this->AddControl(this->ExportSelectedButton);

	this->LoadRPakButton = new UIX::UIXButton();
	this->LoadRPakButton->SetSize({ 85, 27 });
	this->LoadRPakButton->SetLocation({ 12, 446});
	this->LoadRPakButton->SetTabIndex(2);
	this->LoadRPakButton->SetText("加载文件");
	this->LoadRPakButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left);
	this->LoadRPakButton->Click += &OnLoadClick;
	this->AddControl(this->LoadRPakButton);

	this->SettingsButton = new UIX::UIXButton();
	this->SettingsButton->SetSize({ 80, 27 });
	this->SettingsButton->SetLocation({ 752, 446});
	this->SettingsButton->SetTabIndex(1);
	this->SettingsButton->SetText("设置");
	this->SettingsButton->Click += &OnSettingsClick;
	this->SettingsButton->SetAnchor(窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Right);
	this->AddControl(this->SettingsButton);

	this->AssetsListView = new UIX::UIXListView();
	this->AssetsListView->SetSize({ 820, 398 });
	this->AssetsListView->SetLocation({ 12, 38 });
	this->AssetsListView->SetTabIndex(0);
	this->AssetsListView->SetAnchor(窗体::AnchorStyles::Top | 窗体::AnchorStyles::Bottom | 窗体::AnchorStyles::Left | 窗体::AnchorStyles::Right);
	this->AssetsListView->SetView(窗体::View::Details);
	this->AssetsListView->Columns.Add({ "名称", 250 });
	this->AssetsListView->Columns.Add({ "类型", 100 });
	this->AssetsListView->Columns.Add({ "状态", 100 });
	this->AssetsListView->Columns.Add({ "信息", 220 });
	this->AssetsListView->Columns.Add({ "调试信息", 130 });
	this->AssetsListView->SetVirtualMode(true);
	this->AssetsListView->SetFullRowSelect(true);
	this->AssetsListView->VirtualItemsSelectionRangeChanged += &OnSelectedIndicesChanged;
	this->AssetsListView->DoubleClick += &OnListDoubleClick;
	this->AssetsListView->MouseClick += &OnListRightClick;
	this->AssetsListView->KeyUp += &OnListKeyUp;
	this->AssetsListView->KeyPress += &OnListKeyPressed;
	this->AddControl(this->AssetsListView);

	this->ResumeLayout(false);
	this->PerformLayout();


	this->AssetsListView->RetrieveVirtualItem += &GetVirtualItem;
	//this->SetBackColor({ 30, 32, 55 });
	this->SetBackColor({ 33, 33, 33 });
}

void LegionMain::LoadApexFile(const List<string>& File)
{
	this->LoadPath = File;

	this->LoadRPakButton->SetEnabled(false);
	this->StatusLabel->SetText("正在处理文件...");

	Threading::Thread Th([](void* Data)
	{
		LegionMain* Main = (LegionMain*)Data;

		if (Main->LoadPath[0].EndsWith(".rpak"))
		{
			Main->AssetsListView->SetVirtualListSize(0);
			Main->RpakFileSystem = nullptr;
			Main->MilesFileSystem = nullptr;

			try
			{
				Main->RpakFileSystem = std::make_unique<RpakLib>();
				Main->RpakFileSystem->LoadRpaks(Main->LoadPath);
				Main->RpakFileSystem->PatchAssets();

				Main->RefreshView();
			}
			catch (...)
			{
				Main->Invoke([]()
				{
					窗体::MessageBox::Show("加载 RPak 时出错。", "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Warning);
				});
				Main->StatusLabel->SetText("空闲");
			}
		}
		else if (Main->LoadPath[0].EndsWith(".bsp"))
		{
			Main->StatusLabel->SetText("正在加载 bsp...");

			try
			{
				if (Main->RpakFileSystem != nullptr)
				{
					Main->RpakFileSystem->InitializeImageExporter((ImageExportFormat_t)ExportManager::Config.Get<System::SettingType::Integer>("ImageFormat"));
					Main->RpakFileSystem->InitializeModelExporter((ModelExportFormat_t)ExportManager::Config.Get<System::SettingType::Integer>("ModelFormat"));
				}
				
				// 导出 BSP 时强制短路径
				bool useFullPaths = ExportManager::Config.GetBool("UseFullPaths");
				ExportManager::Config.SetBool("UseFullPaths", false);

				if ((ModelExportFormat_t)ExportManager::Config.Get<System::SettingType::Integer>("ModelFormat") != ModelExportFormat_t::Cast)
				{
					auto msgAnswer = MessageBox::Show("您将要导出一个 bsp 文件，其选择的模型格式与“Cast”不同。继续吗？", "Legion+", 窗体::MessageBoxButtons::YesNo, 窗体::MessageBoxIcon::Question);
					if (msgAnswer == DialogResult::No)
					{
						Main->StatusLabel->SetText("Idle");
						Main->LoadRPakButton->SetEnabled(true);
						Main->RefreshView();
						return;
					}
				}

				if ((ImageExportFormat_t)ExportManager::Config.Get<System::SettingType::Integer>("ImageFormat") != ImageExportFormat_t::Png)
				{
					auto msgAnswer = MessageBox::Show("您将要导出一个 bsp 文件，其中包含与“PNG”不同的图像格式。是否继续？", "Legion+", 窗体::MessageBoxButtons::YesNo, 窗体::MessageBoxIcon::Question);
					if (msgAnswer == DialogResult::No)
					{
						Main->StatusLabel->SetText("Idle");
						Main->LoadRPakButton->SetEnabled(true);
						Main->RefreshView();
						return;
					}
				}

				InitializeBSPModelExporter((ModelExportFormat_t)ExportManager::Config.Get<System::SettingType::Integer>("ModelFormat"));
				ExportBsp(Main->RpakFileSystem, Main->LoadPath[0], ExportManager::GetMapExportPath());

				// restore original setting
				ExportManager::Config.SetBool("UseFullPaths", useFullPaths);

				Main->Invoke([]()
				{
					窗体::MessageBox::Show("已成功导出 bsp 映射文件。", "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Information);
				});
				Main->StatusLabel->SetText("Idle");
			}
			catch (const std::exception& e)
			{
				窗体::MessageBox::Show("导出 bsp 文件时出错：\n\n" + string(e.what()), "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Warning);
			}

			Main->RefreshView();
		}
		else
		{
			Main->AssetsListView->SetVirtualListSize(0);
			Main->RpakFileSystem = nullptr;
			Main->MilesFileSystem = nullptr;

			try
			{
				Main->MilesFileSystem = std::make_unique<MilesLib>();
				Main->MilesFileSystem->Initialize();
				Main->MilesFileSystem->MountBank(Main->LoadPath[0]);

				Main->RefreshView();
			}
			catch (const std::exception& e)
			{
				窗体::MessageBox::Show("加载 MBNK 时出错：\n\n" + string(e.what()), "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Warning);
				Main->StatusLabel->SetText("空闲");
			}
		}

		Main->LoadRPakButton->SetEnabled(true);
	});

	Th.Start(this);
}

void LegionMain::ExportSelectedAssets()
{
	if (!this->LoadRPakButton->Enabled())
		return;

	List<uint32_t> SelectedIndices = this->AssetsListView->SelectedIndices();

	if (SelectedIndices.Count() == 0)
	{
		窗体::MessageBox::Show("请至少选择一个要导出的资产。", "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Information);
		return;
	}

	List<ExportAsset> AssetsToExport(SelectedIndices.Count(), true);

	for (uint32_t i = 0; i < AssetsToExport.Count(); i++)
	{
		uint32_t& DisplayIndex = this->DisplayIndices[SelectedIndices[i]];
		ApexAsset& Asset = (*this->LoadedAssets.get())[DisplayIndex];

		AssetsToExport[i].AssetHash = Asset.Hash;
		AssetsToExport[i].AssetIndex = SelectedIndices[i];
	}

	this->ProgressWindow = std::make_unique<LegionProgress>();

	Threading::Thread([this, &AssetsToExport] {
		if (this->MilesFileSystem != nullptr)
		{
			ExportManager::ExportMilesAssets(this->MilesFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
		else
		{
			ExportManager::ExportRpakAssets(this->RpakFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
	}).Start();

	this->ProgressWindow->ShowDialog();
	this->AssetsListView->Refresh();
}

void LegionMain::ExportAllAssets()
{
	if (!this->LoadRPakButton->Enabled())
		return;

	if (this->DisplayIndices.Count() == 0)
	{
		窗体::MessageBox::Show("请找到一些要导出的资产。", "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Information);
		return;
	}

	List<ExportAsset> AssetsToExport(this->DisplayIndices.Count(), true);

	for (uint32_t i = 0; i < AssetsToExport.Count(); i++)
	{
		auto& DisplayIndex = this->DisplayIndices[i];
		auto& Asset = (*this->LoadedAssets.get())[DisplayIndex];

		AssetsToExport[i].AssetHash = Asset.Hash;
		AssetsToExport[i].AssetIndex = i;
	}

	this->ProgressWindow = std::make_unique<LegionProgress>();

	Threading::Thread([this, &AssetsToExport] {
		if (this->MilesFileSystem != nullptr)
		{
			ExportManager::ExportMilesAssets(this->MilesFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
		else
		{
			ExportManager::ExportRpakAssets(this->RpakFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
	}).Start();

	this->ProgressWindow->ShowDialog();
	this->AssetsListView->Refresh();
}

void LegionMain::SearchForAssets()
{
	if (this->LoadedAssets == nullptr)
		return;

	string SearchText = this->SearchBox->Text().ToLower();

	if (string::IsNullOrEmpty(SearchText))
	{
		this->ResetDisplayIndices();
		return;
	}

	bool isBlackList = SearchText.StartsWith("!");
	if (isBlackList)
		SearchText = SearchText.Substring(1);

	List<string> SearchMap = SearchText.Split(",");

	for (auto& Search : SearchMap)
		Search = Search.Trim();

	List<uint32_t> SearchResults;
	uint32_t CurrentIndex = 0;

	for (auto& Asset : *LoadedAssets)
	{
		string AssetNameLowercase = Asset.Name.ToLower();
		bool IsMatch = isBlackList;

		for (auto& Search : SearchMap)
		{
			bool Result = AssetNameLowercase.Contains(Search);

			if (!isBlackList && Result)
			{
				IsMatch = true;
				break;
			}
			else if (isBlackList && Result)
			{
				IsMatch = false;
				break;
			}
		}

		if (IsMatch)
			SearchResults.Add(CurrentIndex);

		CurrentIndex++;
	}

	this->AssetsListView->SetVirtualListSize(0);

	this->DisplayIndices = std::move(SearchResults);

	this->AssetsListView->SetVirtualListSize(this->DisplayIndices.Count());
	this->AssetsListView->Refresh();

	this->StatusLabel->SetText(string::Format("找到 %d 个资产", this->DisplayIndices.Count()));
	this->ClearSearchButton->SetVisible(true);
}

void LegionMain::ExportSingleAsset()
{
	if (!this->LoadRPakButton->Enabled())
		return;

	if (this->IsInExportMode)
		return;

	this->IsInExportMode = true;

	if (this->LoadedAssets == nullptr)
		return;

	List<uint32_t> SelectedIndices = this->AssetsListView->SelectedIndices();

	if (SelectedIndices.Count() == 0)
		return;

	List<ExportAsset> AssetsToExport(1, true);

	uint32_t& DisplayIndex = this->DisplayIndices[SelectedIndices[0]];
	ApexAsset& Asset = (*this->LoadedAssets.get())[DisplayIndex];

	Asset.Status = ApexAssetStatus::Exporting;
	this->AssetsListView->Refresh();

	AssetsToExport[0].AssetHash = Asset.Hash;
	AssetsToExport[0].AssetIndex = SelectedIndices[0];

	this->ProgressWindow = nullptr;

	Threading::Thread([this, &AssetsToExport] {
		if (this->MilesFileSystem != nullptr)
		{
			ExportManager::ExportMilesAssets(this->MilesFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
		else
		{
			ExportManager::ExportRpakAssets(this->RpakFileSystem, AssetsToExport, &LegionMain::ExportProgressCallback, &LegionMain::CheckStatusCallback, this);
		}
	}).Start();
}

void LegionMain::ExportProgressChanged(uint32_t Progress, bool Finished)
{
	if (Finished)
		this->IsInExportMode = false;

	if (this->ProgressWindow == nullptr)
	{
		if (Finished)
			this->AssetsListView->Refresh();

		return;
	}

	this->ProgressWindow->UpdateProgress(Progress, Finished);
}

bool LegionMain::CheckStatus(int32_t AssetIndex)
{
	if (AssetIndex < 0)
		return (this->ProgressWindow != nullptr) ? this->ProgressWindow->IsCanceled() : false;

	(*this->LoadedAssets)[this->DisplayIndices[AssetIndex]].Status = ApexAssetStatus::Exported;

	return (this->ProgressWindow != nullptr) ? this->ProgressWindow->IsCanceled() : false;
}

void LegionMain::SetAssetError(int32_t AssetIndex)
{
	(*this->LoadedAssets)[this->DisplayIndices[AssetIndex]].Status = ApexAssetStatus::Error;
}

void LegionMain::DoPreviewSwap()
{
	if (!this->RpakFileSystem || !this->PreviewWindow || this->PreviewWindow->GetHandle() == nullptr)
		return;

	List<uint32_t> Selected = this->AssetsListView->SelectedIndices();

	if (Selected.Count() <= 0)
		return;

	ApexAsset& Asset = (*this->LoadedAssets.get())[this->DisplayIndices[Selected[0]]];

	uint64_t fct = (Asset.FileCreatedTime / 10000000) - 0x2b6109100;

	switch (Asset.Type)
	{
	case ApexAssetType::Model:
	{
		auto Mdl = this->RpakFileSystem->BuildPreviewModel(Asset.Hash);
		if (Mdl == nullptr)
			return;
		this->PreviewWindow->AssignPreviewModel(*Mdl.get(), Asset.Name, fct);
	}
	break;
	case ApexAssetType::Image:
	case ApexAssetType::UIImage:
	case ApexAssetType::UIImageAtlas:
	{
		auto Texture = this->RpakFileSystem->BuildPreviewTexture(Asset.Hash);
		if (Texture == nullptr)
			return;
		this->PreviewWindow->AssignPreviewImage(*Texture.get(), Asset.Name, fct);
	}
	break;
	case ApexAssetType::Material:
	{
		auto Material = this->RpakFileSystem->BuildPreviewMaterial(Asset.Hash);
		if (Material == nullptr)
			return;
		this->PreviewWindow->AssignPreviewImage(*Material.get(), Asset.Name, fct);
	}
	break;
	}

}

std::unique_ptr<Assets::Texture> LegionMain::MaterialStreamCallback(string Source, uint64_t Hash)
{
	if (!this->RpakFileSystem)
		return nullptr;
	return this->RpakFileSystem->BuildPreviewTexture(Hash);
}

void LegionMain::RefreshView()
{
	string SearchText = this->SearchBox->Text();

	if (this->RpakFileSystem != nullptr)
	{
		this->AssetsListView->SetVirtualListSize(0);

		std::array<bool, 11> bAssets = {
			ExportManager::Config.GetBool("LoadModels"),
			ExportManager::Config.GetBool("LoadAnimations"),
			ExportManager::Config.GetBool("LoadAnimationSeqs"),
			ExportManager::Config.GetBool("LoadImages"),
			ExportManager::Config.GetBool("LoadMaterials"),
			ExportManager::Config.GetBool("LoadUIImages"),
			ExportManager::Config.GetBool("LoadDataTables"),
			ExportManager::Config.GetBool("LoadShaderSets"),
			ExportManager::Config.GetBool("LoadSettingsSets"),
			ExportManager::Config.GetBool("LoadRSONs"),
			ExportManager::Config.GetBool("LoadEffects")
		};

		this->LoadedAssets = this->RpakFileSystem->BuildAssetList(bAssets);
		this->LoadedAssets->Sort([](const ApexAsset& lhs, const ApexAsset& rhs) { return lhs.Name.Compare(rhs.Name) < 0; });

		this->ResetDisplayIndices();
	}
	else if (this->MilesFileSystem != nullptr)
	{
		this->AssetsListView->SetVirtualListSize(0);

		this->LoadedAssets = this->MilesFileSystem->BuildAssetList();
		this->LoadedAssets->Sort([](const ApexAsset& lhs, const ApexAsset& rhs) { return lhs.Name.Compare(rhs.Name) < 0; });

		this->ResetDisplayIndices();
	}
	
	// 刷新后恢复搜索框的文本
	// 是的，这会使窗口在执行搜索时刷新时闪烁
	if (SearchText.Length() > 0)
	{
		this->SearchBox->SetText(SearchText);

		this->SearchForAssets();
	}
}

void LegionMain::ResetDisplayIndices()
{
	this->AssetsListView->SetVirtualListSize(0);

	this->SearchBox->SetText("");
	this->ClearSearchButton->SetVisible(false);

	List<uint32_t> TempIndices(this->LoadedAssets->Count(), true);
	for (uint32_t i = 0; i < this->LoadedAssets->Count(); i++)
		TempIndices[i] = i;

	this->DisplayIndices = std::move(TempIndices);

	this->AssetsListView->SetVirtualListSize(this->DisplayIndices.Count());
	this->AssetsListView->Refresh();

	List<string> PathParts = LoadPath[0].Split("\\");

	if (this->LoadPath.Count() == 1)
		this->StatusLabel->SetText(string::Format("%s 已加载的 %d 资产", (PathParts[PathParts.Count()-1] + ": ").ToCString(), this->DisplayIndices.Count()));
	else
		this->StatusLabel->SetText(string::Format("加载 %d 个资产", this->DisplayIndices.Count()));
}

void LegionMain::OnLoadClick(窗体::Control* Sender)
{
	LegionMain* ThisPtr = (LegionMain*)Sender->FindForm();

	List<string> OpenFileD = OpenFileDialog::ShowMultiFileDialog("Legion+：选择要加载的文件", "", "Apex Legends 文件 (MBnk, RPak, Bsp)|*.mbnk;*.rpak;*.bsp", Sender->FindForm());

	for (uint32_t i = 0; i < OpenFileD.Count(); i++)
	{
		g_Logger.Info("加载 rpak： %s\n", OpenFileD[i].ToCString());
	}

	if (OpenFileD.Count() == 0)
		return;

	else if (OpenFileD.Count() > MAX_LOADED_FILES)
	{
		string msg = string::Format("请选择 %i 或更少的文件。", MAX_LOADED_FILES);
		MessageBox::Show(msg, "Legion+", 窗体::MessageBoxButtons::OK, 窗体::MessageBoxIcon::Warning);
		return;
	}

	ThisPtr->LoadApexFile(OpenFileD);
}

void LegionMain::OnSettingsClick(窗体::Control* Sender)
{
	auto Settings = std::make_unique<LegionSettings>();
	Settings->ShowDialog((窗体::Form*)Sender->FindForm());
}

void LegionMain::OnExpClick(窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->ExportSelectedAssets();
}

void LegionMain::OnExpAllClick(窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->ExportAllAssets();
}

void LegionMain::OnSearchClick(窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->SearchForAssets();
}

void LegionMain::OnClearClick(窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->ResetDisplayIndices();
}

void LegionMain::OnTitanfallClick(窗体::Control* Sender)
{
	auto Titanfall = std::make_unique<LegionTitanfallConverter>();
	Titanfall->ShowDialog((窗体::Form*)Sender->FindForm());
}

void LegionMain::OnRefreshClick(窗体::Control* Sender)
{
	LegionMain* ThisPtr = (LegionMain*)Sender->FindForm();

	ThisPtr->RefreshView();
}

void LegionMain::OnListRightClick(const std::unique_ptr<MouseEventArgs>& EventArgs, 窗体::Control* Sender)
{
	if (EventArgs->Button != 窗体::MouseButtons::Right)
		return;

	LegionMain* ThisPtr = ((LegionMain*)Sender->FindForm());
	UIX::UIXListView* AssetsListView = ThisPtr->AssetsListView;

	List<uint32_t> SelectedIndices = AssetsListView->SelectedIndices();
	string endString = "";

	g_Logger.Info("选定的资产名称：\n");
	for (uint32_t i = 0; i < SelectedIndices.Count(); i++)
	{
		uint32_t& DisplayIndex = ThisPtr->DisplayIndices[SelectedIndices[i]];
		ApexAsset& Asset = (*ThisPtr->LoadedAssets.get())[DisplayIndex];

		g_Logger.Info(Asset.Name + "\n");

		if (i != SelectedIndices.Count() - 1)
			endString += Asset.Name + "\n";
		else
			endString += Asset.Name;
	}

	clip::set_text(endString.ToCString());

	g_Logger.Info("将 %i 资产的名称 %s 复制到剪贴板\n", SelectedIndices.Count(), SelectedIndices.Count() == 1 ? "" : "s");
}

void LegionMain::OnListDoubleClick(窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->ExportSingleAsset();
}

void LegionMain::OnListKeyUp(const std::unique_ptr<KeyEventArgs>& EventArgs, 窗体::Control* Sender)
{
	if (EventArgs->KeyCode() == Keys::E)
	{
		((LegionMain*)Sender->FindForm())->ExportSingleAsset();
	}
	else if (EventArgs->KeyCode() == Keys::P)
	{
		LegionMain* Form = (LegionMain*)Sender->FindForm();

		if (!Form->LoadRPakButton->Enabled())
			return;


		if (!Form->RpakFileSystem)
			return;

		List<uint32_t> Selected = Form->AssetsListView->SelectedIndices();

		if (Selected.Count() <= 0)
			return;

		ApexAsset& Asset = (*Form->LoadedAssets.get())[Form->DisplayIndices[Selected[0]]];

		switch (Asset.Type) {
		case ApexAssetType::DataTable:
		{
			if (Form->TablePreviewWindow == nullptr || Form->TablePreviewWindow->GetState(窗体::ControlStates::StateDisposed))
			{
				Form->TablePreviewWindow = std::make_unique<LegionTablePreview>();
				Form->TablePreviewWindow->Show();
				auto& RpakAsset = Form->RpakFileSystem->Assets[Asset.Hash];
				Form->TablePreviewWindow->SetDataTable(Form->RpakFileSystem->ExtractDataTable(RpakAsset));
			}

			Form->TablePreviewWindow->BringToFront();
			break;
		}
		default:
		{
			if (Form->PreviewWindow == nullptr || Form->PreviewWindow->GetState(窗体::ControlStates::StateDisposed))
			{
				Form->PreviewWindow = std::make_unique<LegionPreview>();
				Form->PreviewWindow->SetMaterialStreamer([Form](string source, uint64_t hash)
					{
						return Form->MaterialStreamCallback(source, hash);
					});
				Form->PreviewWindow->Show();
			}

			Form->PreviewWindow->BringToFront();
			Form->DoPreviewSwap();
			break;
		}
		}
	}
}

void LegionMain::OnListKeyPressed(const std::unique_ptr<KeyPressEventArgs>& EventArgs, 窗体::Control* Sender)
{
	EventArgs->SetHandled(true);
}

void LegionMain::OnSearchKeyPressed(const std::unique_ptr<KeyPressEventArgs>& EventArgs, 窗体::Control* Sender)
{
	if (EventArgs->KeyChar == '\r')
	{
		EventArgs->SetHandled(true);
		((LegionMain*)Sender->FindForm())->SearchForAssets();
	}
}

void LegionMain::OnSelectedIndicesChanged(const std::unique_ptr<窗体::ListViewVirtualItemsSelectionRangeChangedEventArgs>& EventArgs, 窗体::Control* Sender)
{
	((LegionMain*)Sender->FindForm())->DoPreviewSwap();
}

void LegionMain::GetVirtualItem(const std::unique_ptr<窗体::RetrieveVirtualItemEventArgs>& EventArgs, 窗体::Control* Sender)
{
	LegionMain* ThisPtr = (LegionMain*)Sender->FindForm();

	if (ThisPtr->LoadedAssets == nullptr)
		return;
	if (EventArgs->ItemIndex > (int32_t)ThisPtr->DisplayIndices.Count())
		return;

	uint32_t RemappedDisplayIndex = ThisPtr->DisplayIndices[EventArgs->ItemIndex];

	static const char* AssetTypes[] = { "模型", "动画集","动画序列", "图像", "材质", "数据表", "声音", "字幕", "着色器设置", "UI 图像", "UI 图像图集", "设置","设置布局", "RSON", "RUI" , "地图", "效果" };
	static const Drawing::Color AssetTypesColors[] = 
	{
		Drawing::Color(0, 157, 220),  // 模型
		Drawing::Color(219, 80, 74),  // 动画集
		Drawing::Color(220, 75, 109), // 动画序列
		Drawing::Color(202, 97, 195), // 图像
		Drawing::Color(27, 153, 139), // 材质
		Drawing::Color(211, 7, 247),  // 数据表
		Drawing::Color(216, 30, 91),  // 声音,
		Drawing::Color(239, 130, 13), // 字幕
		Drawing::Color(255, 246, 138),// 着色器设置
		Drawing::Color(114, 142, 230),// UI 图像
		Drawing::Color(114, 142, 230),// UI 图像图集
		Drawing::Color(255, 196, 0),  // 设置
		Drawing::Color(255, 127,0),  // 设置布局
		Drawing::Color(54, 249, 249), // RSON
		Drawing::Color(4, 197, 4),    // RUI
		Drawing::Color(131 ,69, 255), // 地图
		Drawing::Color(17, 221, 191), // 效果
	};

	static const char* AssetStatus[] = { "加载", "导出中", "已导出", "错误" };
	static const Drawing::Color AssetStatusColors[] = 
	{
		Drawing::Color(35,  206, 107),
		Drawing::Color(144, 122, 214),
		Drawing::Color(33,  184, 235),
		Drawing::Color(255, 102, 102),
	};

	auto AssetList = ThisPtr->LoadedAssets.get();
	ApexAsset& Asset = (*AssetList)[RemappedDisplayIndex];

	EventArgs->Style.ForeColor = Drawing::Color::White;
	EventArgs->Style.BackColor = Sender->BackColor();

	switch (EventArgs->SubItemIndex)
	{
	case 0:
		EventArgs->Text = Asset.Name;
		break;
	case 1:
		EventArgs->Text = AssetTypes[(uint32_t)Asset.Type] + string::Format(" v%i", Asset.Version);
		EventArgs->Style.ForeColor = AssetTypesColors[(uint32_t)Asset.Type];
		break;
	case 2:
		EventArgs->Text = AssetStatus[(uint32_t)Asset.Status];
		EventArgs->Style.ForeColor = AssetStatusColors[(uint32_t)Asset.Status];
		break;
	case 3:
		EventArgs->Text = Asset.Info;
		break;
	case 4:
		EventArgs->Text = Asset.DebugInfo;
		break;
	}
}

void LegionMain::ExportProgressCallback(uint32_t Progress, 窗体::Form* MainForm, bool Finished)
{
	((LegionMain*)MainForm)->ExportProgressChanged(Progress, Finished);
}

bool LegionMain::CheckStatusCallback(int32_t AssetIndex, 窗体::Form* MainForm)
{
	return ((LegionMain*)MainForm)->CheckStatus(AssetIndex);
}

LegionMain* g_pLegionMain;
