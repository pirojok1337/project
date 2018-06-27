object Form1: TForm1
  Left = 131
  Top = 322
  Width = 372
  Height = 164
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'Keylogger'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Run: TButton
    Left = 40
    Top = 72
    Width = 97
    Height = 33
    Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1080
    ParentShowHint = False
    ShowHint = False
    TabOrder = 0
    OnClick = RunClick
  end
  object Stop: TButton
    Left = 184
    Top = 72
    Width = 97
    Height = 33
    Caption = #1047#1091#1087#1080#1085#1080#1090#1080
    Enabled = False
    TabOrder = 1
    OnClick = StopClick
  end
  object Panel1: TPanel
    Left = 4
    Top = 2
    Width = 349
    Height = 25
    BevelInner = bvRaised
    BiDiMode = bdLeftToRight
    BorderStyle = bsSingle
    ParentBiDiMode = False
    TabOrder = 2
    object Label2: TLabel
      Left = 2
      Top = 3
      Width = 72
      Height = 13
      Caption = #1047#1072#1087#1080#1089' '#1074' '#1092#1072#1081#1083':'
    end
    object Label1: TLabel
      Left = 88
      Top = 4
      Width = 61
      Height = 13
      Caption = 'C:\\out.txt'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Button1: TButton
    Left = 3
    Top = 30
    Width = 81
    Height = 17
    Caption = #1042#1082#1072#1079#1072#1090#1080' '#1092#1072#1081#1083
    TabOrder = 3
    OnClick = Button1Click
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1081' '#1092#1072#1081#1083' (.txt)|*.txt'
    Left = 8
    Top = 72
  end
end
