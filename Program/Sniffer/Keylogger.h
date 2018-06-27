//---------------------------------------------------------------------------

#ifndef KeyloggerH
#define KeyloggerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Run;
        TButton *Stop;
        TSaveDialog *SaveDialog1;
        TLabel *Label2;
        TButton *Button1;
        TLabel *Label1;
        TPanel *Panel1;
        void __fastcall RunClick(TObject *Sender);
        void __fastcall StopClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        void __fastcall OnWMCopyData(TMessage &Msg);

        //таблиця відповідей на повідомлення
        BEGIN_MESSAGE_MAP
        //при повідомленні WH_KEYBOARD викликати функцію OnWMCopyData
             MESSAGE_HANDLER(WH_KEYBOARD, TMessage, OnWMCopyData);
        END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
