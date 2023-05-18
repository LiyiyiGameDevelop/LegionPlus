#include "pch.h"
#include "LegionProgress.h"

LegionProgress::LegionProgress()
	: ����::Form(), CanClose(false), Canceled(false), AutoClose(false)
{
	this->InitializeComponent();
}

void LegionProgress::UpdateProgress(uint32_t Progress, bool Finished)
{
	this->ExportProgressBar->SetValue(Progress);

	if (Finished)
	{
		this->FinishButton->SetEnabled(true);
		this->CancelButton->SetEnabled(false);
		this->CanClose = true;
		this->SetText("Legion+ | �������");

		if (this->Canceled || this->AutoClose)
			this->Close();
	}
}

bool LegionProgress::IsCanceled()
{
	return this->Canceled;
}

void LegionProgress::SetAutoClose(bool Value)
{
	this->AutoClose = Value;
}

void LegionProgress::InitializeComponent()
{
	this->SuspendLayout();
	this->SetAutoScaleDimensions({ 6, 13 });
	this->SetAutoScaleMode(����::AutoScaleMode::Font);
	this->SetText("Legion+ | ���ڵ����ʲ�...");
	this->SetClientSize({ 409, 119 });
	this->SetFormBorderStyle(����::FormBorderStyle::FixedSingle);
	this->SetStartPosition(����::FormStartPosition::CenterParent);
	this->SetMinimizeBox(false);
	this->SetMaximizeBox(false);
	this->SetShowInTaskbar(false);

	this->ExportLabel = new UIX::UIXLabel();
	this->ExportLabel->SetSize({ 385, 17 });
	this->ExportLabel->SetLocation({ 12, 18 });
	this->ExportLabel->SetTabIndex(3);
	this->ExportLabel->SetText("��չ��");
	this->ExportLabel->SetAnchor(����::AnchorStyles::Top | ����::AnchorStyles::Left | ����::AnchorStyles::Right);
	this->ExportLabel->SetTextAlign(Drawing::ContentAlignment::TopLeft);
	this->AddControl(this->ExportLabel);

	this->CancelButton = new UIX::UIXButton();
	this->CancelButton->SetSize({ 87, 31 });
	this->CancelButton->SetLocation({ 310, 76 });
	this->CancelButton->SetTabIndex(2);
	this->CancelButton->SetText("ȡ��");
	this->CancelButton->SetAnchor(����::AnchorStyles::Bottom | ����::AnchorStyles::Right);
	this->CancelButton->Click += &OnCancelClick;
	this->AddControl(this->CancelButton);

	this->FinishButton = new UIX::UIXButton();
	this->FinishButton->SetSize({ 87, 31 });
	this->FinishButton->SetLocation({ 217, 76 });
	this->FinishButton->SetTabIndex(1);
	this->FinishButton->SetText("Ok");
	this->FinishButton->SetEnabled(false);
	this->FinishButton->SetAnchor(����::AnchorStyles::Bottom | ����::AnchorStyles::Right);
	this->FinishButton->Click += &OnFinishClick;
	this->AddControl(this->FinishButton);

	this->ExportProgressBar = new UIX::UIXProgressBar();
	this->ExportProgressBar->SetSize({ 385, 29 });
	this->ExportProgressBar->SetLocation({ 12, 38 });
	this->ExportProgressBar->SetTabIndex(0);
	this->ExportProgressBar->SetAnchor(����::AnchorStyles::Top | ����::AnchorStyles::Left | ����::AnchorStyles::Right);
	this->AddControl(this->ExportProgressBar);

	this->ResumeLayout(false);
	this->PerformLayout();
	// END DESIGNER CODE

	//this->SetBackColor({ 30, 32, 55 });
	this->SetBackColor({ 33, 33, 33 });
}

void LegionProgress::OnFinishClick(����::Control* Sender)
{
	((����::Form*)Sender->FindForm())->Close();
}

void LegionProgress::OnCancelClick(����::Control* Sender)
{
	((LegionProgress*)Sender->FindForm())->CancelProgress();
}

void LegionProgress::CancelProgress()
{
	this->CancelButton->SetEnabled(false);
	this->CancelButton->SetText("ȡ��...");
	this->Canceled = true;
}
