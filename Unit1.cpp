//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "NeuroLib.h"
#include <io.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxDock"
#pragma link "frxDesgnCtrls"
#pragma resource "*.dfm"

NeuralNetwork* netCompressor = NULL;
int n_of_layers = 0;
int *neurons_in_layer = NULL;


TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
if ((Key >= '0') && (Key <= '9')) {
}else if (Key == 8) {
}else{
  Key=0;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
if((Edit1->Text!="") && (StrToInt(Edit1->Text)>20)){
  Edit1->Text = "20";
}
if (Edit1->Text!="") {
  Edit1->Text = IntToStr(StrToInt(Edit1->Text));
}
for(int i=0;i<n_of_layers;i++){
  delete (TLabel*)ScrollBox1->FindComponent("LabelT"+String(i));
  delete (TEdit*)ScrollBox1->FindComponent("EditT"+String(i));
}

if (Edit1->Text == "") {
  n_of_layers = 0;
}else{
  n_of_layers = StrToInt(Edit1->Text);
}

for(int i=0;i<n_of_layers;i++)
 {
		TLabel* l = new TLabel(ScrollBox1);
		l->Caption = "ʳ������ �������� ���� �"+String(i);
		l->Parent = ScrollBox1;
		l->Name = "LabelT"+String(i);
		l->Left = 5;
		l->Top = i*20;
		l->Visible = true;
		TEdit* e = new TEdit(ScrollBox1);
		e->Text = "0";
		e->Parent = ScrollBox1;
		e->Name = "EditT"+String(i);
		e->Left = 160;
		e->Top = i*20;
		e->Visible = true;
		e->Width = 40;
		e->OnKeyPress = Edit1->OnKeyPress;
		e->OnChange = Edit2->OnChange;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
  TEdit *e = (TEdit*)Sender;
  if((e->Text!="") && (StrToInt(e->Text)>20)){
	e->Text = "20";
  }
  if (e->Text!="") {
	e->Text = IntToStr(StrToInt(e->Text));
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::��������Click(TObject *Sender)
{
 Image1->Picture = NULL;
 bool flag = true;
 if (Edit1->Text == "" || Edit1->Text == "0") {
   flag = false;
 }
 for(int i=0; i<n_of_layers;i++){
   if (((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text == "" || StrToInt(((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text) == 0){
	 flag = false;
   }
 }

if (flag) {

  GroupBox1->Enabled = false;

  neurons_in_layer = new int[n_of_layers];

  int max = 0;
  for(int i=0; i<n_of_layers;i++){
	neurons_in_layer[i] = StrToInt(((TEdit*)ScrollBox1->FindComponent("EditT"+String(i)))->Text);
   if (neurons_in_layer[i] > max){
	 max = neurons_in_layer[i];
   }
  }

  int min_ver_separator = 90;
  int height = min_ver_separator*(max+1);
  Image1->Height = height;
  int hor_separator = 120;
  Image1->Width = 2*hor_separator*(n_of_layers)+hor_separator;
  int radius = 15;
  //coder
  for(int i=1; i<n_of_layers;i++){
   int x = i*hor_separator;
   int n_of_neuron = neurons_in_layer[i-1];
   int ver_separator = height/(n_of_neuron+1);
   for(int y=1; y<=n_of_neuron; y++){
	 //paint powers
	   int next_x = (i+1)*hor_separator;
	   int next_n_of_neuron = neurons_in_layer[i];
	   int next_ver_separator = height/(next_n_of_neuron+1);
	   for(int j=1; j<=next_n_of_neuron; j++){
		 Image1->Canvas->Brush->Color = RGB(0,0,255);
		 Image1->Canvas->MoveTo(x,y*ver_separator);
		 Image1->Canvas->LineTo(next_x, j*next_ver_separator);
	   }
	 //paint powers
	 if (i == 1) {
	   Image1->Canvas->Brush->Color = RGB(255,0,0);
	 }else{
	   Image1->Canvas->Brush->Color = RGB(255,215,0);
	 }
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
 }
   int x = n_of_layers*hor_separator;
   int n_of_neuron = neurons_in_layer[n_of_layers-1];
   int ver_separator = height/(n_of_neuron+1);
   for(int y=1; y<=n_of_neuron; y++){
	 Image1->Canvas->MoveTo(x,y*ver_separator);
	 Image1->Canvas->LineTo(x+hor_separator, y*ver_separator);
	 Image1->Canvas->Brush->Color = RGB(255,0,0);
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
  //end coder
  //decoder
   x += hor_separator;
   for(int i = n_of_layers-1; i>0 ;i--){
	 int n_of_neuron = neurons_in_layer[i];
	 int ver_separator = height/(n_of_neuron+1);
	 for(int y=1; y<=n_of_neuron; y++){
	 //paint powers
	   int next_x = x+hor_separator;
	   int next_n_of_neuron = neurons_in_layer[i-1];
	   int next_ver_separator = height/(next_n_of_neuron+1);
	   for(int j=1; j<=next_n_of_neuron; j++){
		 Image1->Canvas->Brush->Color = RGB(0,0,255);
		 Image1->Canvas->MoveTo(x,y*ver_separator);
		 Image1->Canvas->LineTo(next_x, j*next_ver_separator);
	   }
	 //paint powers
	 if (i == n_of_layers-1) {
	   Image1->Canvas->Brush->Color = RGB(255,0,0);
	 }else{
	   Image1->Canvas->Brush->Color = RGB(255,215,0);
	 }
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
   x += hor_separator;
 }
   n_of_neuron = neurons_in_layer[0];
   ver_separator = height/(n_of_neuron+1);
   for(int y=1; y<=n_of_neuron; y++){
	 Image1->Canvas->MoveTo(x,y*ver_separator);
	 Image1->Canvas->Brush->Color = RGB(255,0,0);
	 Image1->Canvas->Ellipse(x-radius,y*ver_separator-radius,x+radius,y*ver_separator+radius);
   }
  //end decoder */

  int *reverse_neurons_in_layer = new int[n_of_layers];
  int k = n_of_layers-1;
  for (int i = 0; i < n_of_layers; i++) {
	reverse_neurons_in_layer[i] = neurons_in_layer[k];
	k--;
  }

  //netCompressor = new NeuralNetwork(neurons_in_layer, n_of_layers);

}else{
  ShowMessage("�������� �� ������ ���� ���������!!!");
}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NewNeuroNetwork1Click(TObject *Sender)
{
  ShowMessage("�������� ������ ���� ��������");
  GroupBox1->Enabled = true;
  Image1->Picture = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
  FileOpenDialog1->Execute();
  Edit3->Text = FileOpenDialog1->FileName;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
  TEdit *e = (TEdit*)Sender;
  if((e->Text!="") && (StrToInt(e->Text)>100000)){
	e->Text = "100000";
  }
  if (e->Text!="") {
	e->Text = IntToStr(StrToInt(e->Text));
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4KeyPress(TObject *Sender, System::WideChar &Key)
{
if ((Key >= '0') && (Key <= '9')) {
  }else if (Key == 8) {
  }else{
	Key=0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{

  ProgressBar1->Visible = true;

	ProgressBar1->StepBy(2);
/*
  UnicodeString name = (FileOpenDialog1->FileName);
  FILE *f = fopen((char *)name.c_str(), "rb");
  int c;
  int i = 0;
  String str;
  while ( !feof(f) ){
	c = fgetc(f);
	str += String(c);
	ShowMessage("ju");
  }
  Memo1->Text = str;
  */
}
//---------------------------------------------------------------------------

