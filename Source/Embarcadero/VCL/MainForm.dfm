object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'frmMain'
  ClientHeight = 1424
  ClientWidth = 2099
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 200
  TextHeight = 35
  object pnlControl: TPanel
    Left = 1730
    Top = 0
    Width = 369
    Height = 1383
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alRight
    TabOrder = 0
    object btnPersonNew: TButton
      Left = 27
      Top = 28
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnPersonNew'
      TabOrder = 0
      OnClick = btnPersonNewClick
    end
    object btnPersonEdit: TButton
      Left = 27
      Top = 92
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnPersonEdit'
      TabOrder = 1
      OnClick = btnPersonEditClick
    end
    object btnEmployeeNew: TButton
      Left = 27
      Top = 183
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnEmployeeNew'
      TabOrder = 2
      OnClick = btnEmployeeNewClick
    end
    object btnEmployeeEdit: TButton
      Left = 27
      Top = 241
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnEmployeeEdit'
      TabOrder = 3
      OnClick = btnEmployeeEditClick
    end
    object ListBox1: TListBox
      Left = 51
      Top = 710
      Width = 252
      Height = 202
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      ItemHeight = 35
      Items.Strings = (
        '1. Zeile'
        'Test'
        'noch eine Zeile'
        '4. Zeile'
        'am Ende')
      TabOrder = 4
    end
    object btnPersonList: TButton
      Left = 27
      Top = 340
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnPersonList'
      TabOrder = 5
      OnClick = btnPersonListClick
    end
    object btnRollDice: TButton
      Left = 27
      Top = 455
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnRollDice'
      TabOrder = 6
      OnClick = btnRollDiceClick
    end
    object edtValues: TEdit
      Left = 27
      Top = 512
      Width = 318
      Height = 43
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      TabOrder = 7
      Text = 'edtValues'
    end
    object btnWork: TButton
      Left = 27
      Top = 1069
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnWork'
      TabOrder = 8
      OnClick = btnWorkClick
    end
    object btnClose: TButton
      Left = 27
      Top = 1242
      Width = 318
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnClose'
      TabOrder = 9
      OnClick = btnCloseClick
    end
  end
  object sbMain: TStatusBar
    Left = 0
    Top = 1383
    Width = 2099
    Height = 41
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Panels = <>
    SimplePanel = True
    SimpleText = 'sbMain'
  end
  object pnlMain: TPanel
    Left = 0
    Top = 0
    Width = 1730
    Height = 1383
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    TabOrder = 2
    object Splitter1: TSplitter
      Left = 1
      Top = 1115
      Width = 1728
      Height = 6
      Cursor = crVSplit
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alBottom
      ExplicitTop = 1
      ExplicitWidth = 791
    end
    object memOutput: TMemo
      Left = 1
      Top = 1
      Width = 1728
      Height = 1114
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Lines.Strings = (
        'memOutput')
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object memError: TMemo
      Left = 1
      Top = 1121
      Width = 1728
      Height = 261
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alBottom
      Lines.Strings = (
        'memError')
      ScrollBars = ssBoth
      TabOrder = 1
    end
  end
end
