object frmPersonList: TfrmPersonList
  Left = 0
  Top = 0
  Caption = 'frmPersonList'
  ClientHeight = 929
  ClientWidth = 1307
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -25
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 200
  TextHeight = 35
  object Panel1: TPanel
    Left = 0
    Top = 844
    Width = 1307
    Height = 85
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alBottom
    TabOrder = 0
    ExplicitLeft = 715
    ExplicitTop = 850
    ExplicitWidth = 385
    object btnOk: TButton
      Left = 69
      Top = 17
      Width = 156
      Height = 52
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'btnOk'
      ModalResult = 1
      TabOrder = 0
    end
  end
  object lvPersons: TListView
    Left = 0
    Top = 0
    Width = 1307
    Height = 844
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    Columns = <>
    TabOrder = 1
    ExplicitLeft = 596
    ExplicitTop = 375
    ExplicitWidth = 521
    ExplicitHeight = 313
  end
end
