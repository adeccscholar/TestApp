object frmWorker: TfrmWorker
  Left = 0
  Top = 0
  Caption = 'frmWorker'
  ClientHeight = 929
  ClientWidth = 2011
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  PixelsPerInch = 200
  TextHeight = 35
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 2011
    Height = 86
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alTop
    TabOrder = 0
    ExplicitLeft = 680
    ExplicitTop = 11
    ExplicitWidth = 385
    DesignSize = (
      2011
      86)
    object lblFile: TLabel
      Left = 33
      Top = 25
      Width = 64
      Height = 35
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'lblFile'
    end
    object edtFile: TEdit
      Left = 170
      Top = 22
      Width = 1446
      Height = 43
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Anchors = [akLeft, akTop, akRight]
      AutoSelect = False
      TabOrder = 0
      Text = 'edtFile'
    end
    object Panel4: TPanel
      Left = 1683
      Top = 1
      Width = 327
      Height = 84
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alRight
      TabOrder = 1
      object btnSelect: TButton
        Left = 34
        Top = 17
        Width = 256
        Height = 52
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'btnSelect'
        TabOrder = 0
        OnClick = btnSelectClick
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 844
    Width = 2011
    Height = 85
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alBottom
    TabOrder = 1
    ExplicitLeft = 646
    ExplicitTop = 833
    ExplicitWidth = 386
    object btnClose: TButton
      Left = 33
      Top = 12
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnClose'
      ModalResult = 8
      TabOrder = 0
    end
    object btnStart: TButton
      Left = 238
      Top = 12
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnStart'
      TabOrder = 1
      OnClick = btnStartClick
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 86
    Width = 2011
    Height = 758
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    TabOrder = 2
    ExplicitLeft = 679
    ExplicitTop = 391
    ExplicitWidth = 386
    ExplicitHeight = 86
    object lvData: TListView
      Left = 1
      Top = 1
      Width = 2009
      Height = 492
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Columns = <>
      TabOrder = 0
      ExplicitLeft = 408
      ExplicitTop = 12
      ExplicitWidth = 521
      ExplicitHeight = 313
    end
    object memError: TMemo
      Left = 1
      Top = 493
      Width = 2009
      Height = 264
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
