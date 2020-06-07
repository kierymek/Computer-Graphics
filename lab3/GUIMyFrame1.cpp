#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1(nullptr), _isBananaActivated(false), _bananaPosition(0), _chosenFigure(star), _starColour(*wxBLACK), _textString("tekst"), _imageHandler(new wxPNGHandler())
{
	//ustawione na sztywno parametry suwaka
	m_scrollBar1->SetScrollbar(0, 1, 100, 1);

	//pobieramy obraz banana pozniej uzyty przy wlaczeniu opcji
	wxImage::AddHandler(_imageHandler);
	wxImage bananaImage = wxImage(wxSize(50, 38));

	bananaImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	_banana = new wxBitmap(bananaImage);
	_fileDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _("result.jpg"), _(".jpg"), wxFD_SAVE);

}

//wyrysowanie na panelu
void GUIMyFrame1::m_panel1OnPaint( wxPaintEvent& event )
{
	wxClientDC dcClient(m_panel1);
	m_panel1->Refresh();
	m_panel1->Update();
	draw(dcClient);
}

//update panelu
void GUIMyFrame1::m_panel1OnUpdateUI( wxUpdateUIEvent& event )
{
	wxClientDC dcClient(m_panel1);
	draw(dcClient);
}

//zapis wyniku do pliku
void GUIMyFrame1::m_button_saveOnButtonClick( wxCommandEvent& event )
{
	wxClientDC dcClient(m_panel1);
	wxBufferedDC dcBuffer(&dcClient);

	PrepareDC(dcBuffer);
	wxInitAllImageHandlers();

	wxString filePath;

	if (_fileDialog->ShowModal() == wxID_OK) {
		Refresh();

		//wybor sciezki
		filePath = _fileDialog->GetPath();

		//pobieramy wielkosc panelu
		wxSize size = m_panel1->GetVirtualSize();
		wxBitmap bitmapToSave(size);

		wxMemoryDC memory;
		memory.SelectObject(bitmapToSave);

		//przydzielenie odpowiedniej ilosci pamieci dla rozmiaru obrazu
		memory.Blit(0, 0, size.GetX(), size.GetY(), &dcBuffer, 0, 0, wxCOPY, true);

		//konwersja na image
		wxImage imageToSave = bitmapToSave.ConvertToImage();
		imageToSave.SaveFile(filePath, wxBITMAP_TYPE_JPEG);
	}
}

void GUIMyFrame1::m_check_bananaOnCheckBox( wxCommandEvent& event )
{
	//aktywacja banana
	_isBananaActivated = event.IsChecked();
	m_scrollBar1->Enable(_isBananaActivated);
	Refresh();
}

//suwak
void GUIMyFrame1::m_scrollBar1OnScroll( wxScrollEvent& event )
{
	_bananaPosition = event.GetPosition();
	m_gauge1->SetValue(_bananaPosition);
	Refresh();
}


//obsluga przycisku do wyboru koloru
void GUIMyFrame1::m_button_star_colorOnButtonClick( wxCommandEvent& event )
{
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		_starColour = colourDialog.GetColourData().GetColour();
	Refresh();
}

//wpisywany tekst
void GUIMyFrame1::m_textCtrl1OnText( wxCommandEvent& event )
{
	_textString = event.GetString();
	wxClientDC dcClient(m_panel1);
	draw(dcClient);
	Refresh();
}

//wybor figury
void GUIMyFrame1::m_choice_shapeOnChoice( wxCommandEvent& event )
{
	_chosenFigure = event.GetSelection();
	Refresh();
}


//destruktor
GUIMyFrame1::~GUIMyFrame1()
{
	delete _banana;
	delete _fileDialog;
}

//metoda rysująca na panelu wszystkie potrzebne kształty

void GUIMyFrame1::draw(wxClientDC & dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();

	//pobranie wymiarow panelu
	wxSize center = m_panel1->GetVirtualSize();

	//wyśrodkowanie
	int x = center.GetWidth() / 2;
	int y = center.GetHeight() / 2;
	dcBuffer.SetDeviceOrigin(0, 0);


	//rysowanie człowieka

	dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
	//tulow rece nogi
	dcBuffer.DrawLine(x, y - 20, x, y + 73); 
	dcBuffer.DrawLine(x, y, x + 40, y + 25); 

	dcBuffer.DrawLine(x, y + 73, x + 33, y + 100); 
	dcBuffer.DrawLine(x, y + 73, x - 33, y + 100);
	//glowa
	dcBuffer.DrawCircle(x, y - 30, 20); 

	//oczy
	dcBuffer.DrawCircle(x + 8, y - 32, 6); 
	dcBuffer.DrawCircle(x - 8, y - 32, 6); 

	dcBuffer.SetBrush(wxBrush(*wxBLACK_BRUSH));
	//zrenice
	dcBuffer.DrawCircle(x + 10, y - 34, 1); 
	dcBuffer.DrawCircle(x - 10, y - 34, 1); 

	//ustawienie pozycji gwiazdy
	_starPosition[0] = wxPoint(x - 100, y - 120);
	_starPosition[1] = wxPoint(x - 85, y - 75);

	_starPosition[2] = wxPoint(x - 125, y - 100);

	_starPosition[3] = wxPoint(x - 75, y - 100);
	_starPosition[4] = wxPoint(x - 115, y - 75);

	dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));

	//rysowanie banana
	if (_isBananaActivated)
	{
		dcBuffer.DrawBitmap(*_banana, x - 80, y - _bananaPosition / 2);

		dcBuffer.DrawLine(x, y, x - 40, y + 25 - _bananaPosition / 2); 
		dcBuffer.DrawEllipticArc(x - 13, y - 30, 26, 15, 0, -180); 
	}

	else 
	{
		dcBuffer.DrawLine(x, y, x - 40, y + 25 - _bananaPosition / 2); 
		dcBuffer.DrawEllipticArc(x - 13, y - 25, 26, 15, 0, 180); 
	}

	//ustawienie koloru
	dcBuffer.SetPen(wxPen(wxColour(_starColour)));
	dcBuffer.SetBrush(wxBrush(wxColour(_starColour)));
	
	
	//stworzenie kształtu w zaleznosci od wyboru
	switch (_chosenFigure) 
	{

	case star:
		dcBuffer.DrawPolygon(5, _starPosition, wxWINDING_RULE); 
		break;

	case moon:
		dcBuffer.SetPen(wxPen(*wxLIGHT_GREY_PEN));
		dcBuffer.SetBrush(wxBrush(*wxLIGHT_GREY_BRUSH));
		dcBuffer.DrawCircle(x - 100, y - 100, 30); 

		dcBuffer.SetPen(wxPen(*wxWHITE_PEN));
		dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));

		dcBuffer.DrawCircle(x - 115, y - 115, 30);
		dcBuffer.SetPen(wxPen(*wxBLACK_PEN));

		dcBuffer.SetBrush(wxBrush(*wxBLACK_BRUSH));
		dcBuffer.DrawCircle(x - 80, y - 100, 3); 

		dcBuffer.DrawEllipticArc(x - 90, y - 85, 14, 3, 38, -220); 
		break;

	case sun:
		dcBuffer.SetPen(wxPen(*wxYELLOW_PEN));
		dcBuffer.SetBrush(wxBrush(*wxYELLOW_BRUSH));

		dcBuffer.DrawCircle(x - 100, y - 100, 30); 
		break;
	}

	//wypisanie tekstu i ustawienie czcionek
	dcBuffer.SetPen(wxPen(wxColour(*wxBLACK), 3));
	dcBuffer.DrawText(_textString, x - 100, y + 90);

	dcBuffer.SetFont(wxFont(wxFontInfo(40).FaceName("Consolas")));
	dcBuffer.SetPen(wxPen(wxColour(*wxBLACK), 20));
	dcBuffer.DrawRotatedText(_textString, x + 70, y + 100, 90);

}
