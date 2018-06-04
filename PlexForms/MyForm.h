#pragma once

#include "TDrawing.h"

#include <string>

namespace PlexForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			isInCreationMode = false;
			gContext = this->CreateGraphics();
		}

	private:
		bool isInCreationMode;
		TDrawing *drawing;
		int x1, y1;
	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
			 Graphics^ gContext;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private:
		void MarshalString(String ^ s, std::string& os) 
		{
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1334, 42);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->newToolStripMenuItem,
					this->saveToolStripMenuItem, this->openToolStripMenuItem, this->closeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(64, 38);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(324, 38);
			this->newToolStripMenuItem->Text = L"New";
			this->newToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::newToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(324, 38);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(324, 38);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(324, 38);
			this->closeToolStripMenuItem->Text = L"Close";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closeToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(192, 192);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->ClientSize = System::Drawing::Size(1334, 819);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void newToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		isInCreationMode = true;
		delete drawing;
		gContext->Clear(Color::WhiteSmoke);
		drawing = new TDrawing();
	}



			 /* The whole process takes place here */
private: System::Void MyForm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	x1 = e->X;
	y1 = e->Y;
}
private: System::Void MyForm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (isInCreationMode) {
		drawing->addLine(x1, y1, e->X, e->Y);
		drawing->draw(gContext);
	}
}
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (drawing != nullptr) {
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
		saveFileDialog1->Filter = "Plex files (*.plex)|*.plex|All files (*.*)|*.*";
		saveFileDialog1->FilterIndex = 1;
		saveFileDialog1->RestoreDirectory = true;
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			std::string fileName;
			MarshalString(saveFileDialog1->FileName, fileName);

			drawing->save(fileName);
			//if ((myStream = saveFileDialog1->OpenFile()) != nullptr)
			//{
			//	
			//	// Code to write the stream goes here.
			//	myStream->Close();
			//}
		}
	}
}
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	OpenFileDialog ^openFileDialog = gcnew OpenFileDialog();
	openFileDialog->Filter = "Plex files (*.plex)|*.plex|All files (*.*)|*.*";
	openFileDialog->FilterIndex = 1;
	openFileDialog->RestoreDirectory = true;

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		gContext->Clear(Color::WhiteSmoke);
		delete drawing;
		drawing = new TDrawing();

		std::string fileName;
		MarshalString(openFileDialog->FileName, fileName);

		drawing->open(fileName);
		drawing->draw(gContext);

		isInCreationMode = true;
	}
}
private: System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	gContext->Clear(Color::WhiteSmoke);
	delete drawing;
	isInCreationMode = false;
}
};
}
