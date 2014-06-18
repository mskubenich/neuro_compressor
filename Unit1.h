//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "frxDock.hpp"
#include "frxDesgnCtrls.hpp"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *NewNeuroNetwork1;
	TGroupBox *GroupBox2;
	TScrollBox *ScrollBox2;
	TImage *Image1;
	TMenuItem *N1;
	TScrollBox *LeftPanel;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *Edit1;
	TScrollBox *ScrollBox1;
	TEdit *Edit2;
	TButton *Button2;
	TGroupBox *GroupBox3;
	TSaveDialog *SaveDialog1;
	TButton *Button1;
	TEdit *Edit3;
	TLabel *Label2;
	TEdit *Edit4;
	TProgressBar *ProgressBar1;
	TButton *Button3;
	TFileOpenDialog *FileOpenDialog1;
	TGroupBox *GroupBox4;
	TButton *Button4;
	TEdit *Edit5;
	TProgressBar *ProgressBar2;
	TButton *Button5;
	TLabel *Label3;
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall —Ú‚ÓËÚËClick(TObject *Sender);
	void __fastcall NewNeuroNetwork1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Edit4Change(TObject *Sender);
	void __fastcall Edit4KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
