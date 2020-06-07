#include "GUIMyFrame1.h"

#define height Img_Org.GetHeight()
#define width Img_Org.GetWidth()
#define size height*width*3

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

//przerysowanie po zmianach
void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

//wyglad w skali szarosci
void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.ConvertToGreyscale();
}

//rozmycie
void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Blur(5);
}

//odbicie lustrzane
void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Mirror();
}

//zamiana kolorów czerwonego na niebieski
void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();//na poczatku takich operacji wczytuje oryginalny obraz by modyfikowac oryginal
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

//pomniejszenie do rozmiaru 320 na 240 pikseli
void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Scale(320, 240);
}

//obrot o 30 stopni
void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Rotate(30 * M_PI/180, wxPoint(width/2, height/2));
}

//odwrocenie odcieni
void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

//obraz maski
void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

//filtracja metod¹ maski Prewitta
void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* _data = Img_Cpy.GetData();
	unsigned char* prewitt = new unsigned char[size];
	std::copy(_data, _data + size, prewitt);

	//wypelnienie wszystkich elementow
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++)
			for (int k = 0; k < 3; k++) {
				int new_val = 0;

				//rozpisanie wg wzoru podanej macierzy
				new_val += prewitt[k + ((i - 1) * width + j + 1) * 3];//3cia kolumna macierzy, 1 wiersz
				new_val -= prewitt[k + ((i - 1) * width + j - 1) * 3];//1sza kolumna macierzy
				new_val += prewitt[k + (i * width  + j + 1) * 3];//2 wiersz
				new_val -= prewitt[k + (i * width  + j - 1) * 3];
				new_val += prewitt[k + ((i + 1) * width + j + 1) * 3];//3 wiersz
				new_val -= prewitt[k + ((i + 1) * width + j - 1) * 3];

				_data[k + i * width * 3 + j * 3] = fabs(new_val) / 3.0;//wpisanie nowych danych
			}

}

//próg, odcina wartosci powyzej i ponizej 128
void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char * _data = Img_Cpy.GetData();

	for (int i = 0; i < size; i++) {
		if (_data[i] < 128) _data[i] = 0;
		else  _data[i] = 255;
	}
}

//zmiana kontrastu
void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char * _data = Img_Cpy.GetData();
	const double _contrast = (value + 100)/(100.000001 - value);

	for (int i = 0; i < size; i++) {
		int new_val = (_data[i] - 255.0 / 2) * _contrast + 255.0 / 2;

		if (new_val > 255) new_val = 255;
		else if (new_val < 0) new_val = 0;
		_data[i] = new_val;
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 wxBufferedDC buffer(&dc);			//kopia do buffer i odswiezamy w kazdym przypadku zmiany
 buffer.Clear();
 m_scrolledWindow->DoPrepareDC(buffer); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 buffer.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

//zmiana jasnosci
void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char * _data = Img_Cpy.GetData();

	for (int i = 0; i < size; i++) {
		int new_val = _data[i] + value;
		if (new_val > 255) new_val = 255;
		else if (new_val < 0) new_val = 0;
		_data[i] = new_val;
	}
}