#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"
#include "math.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}

//macierz translacji i wypelnienie wg wzoru
Matrix4 GUIMyFrame1::translation(float x, float y, float z)
{
	Matrix4 A;

	A.data[0][0] = 1;
	A.data[1][1] = 1;
	A.data[2][2] = 1;
	A.data[0][3] = x;
	A.data[1][3] = -y;
	A.data[2][3] = z;

	return A;
}

//macierz centrujaca 
Matrix4 GUIMyFrame1::center()
{
	Matrix4 center;

	center.data[0][0] = 1;
	center.data[1][1] = 1;
	center.data[2][2] = 1;
	center.data[0][3] = 0.5;
	center.data[1][3] = 0.5;

	return center;
}

//macierz rotacji x
Matrix4 GUIMyFrame1::rotation_x(float coefficient)
{
	Matrix4 X;

	float cos_value = cos(coefficient * M_PI / 180.);
	float sin_value = sin(coefficient * M_PI / 180.);

	X.data[0][0] = 1;
	X.data[1][1] = cos_value;
	X.data[1][2] = -sin_value;
	X.data[2][1] = sin_value;
	X.data[2][2] = cos_value;

	return X;
}

//macierz rotacji y
Matrix4 GUIMyFrame1::rotation_y(float coefficient)
{
	Matrix4 Y;

	float cos_value = cos(coefficient * M_PI / 180.);
	float sin_value = sin(coefficient * M_PI / 180.);

	Y.data[0][0] = cos_value;
	Y.data[1][1] = 1;
	Y.data[2][0] = sin_value;
	Y.data[0][2] = -sin_value;
	Y.data[2][2] = cos_value;

	return Y;
}

//macierz rotacji z
Matrix4 GUIMyFrame1::rotation_z(float coefficient)
{
	Matrix4 Z;

	float cos_value = cos(coefficient * M_PI / 180.);
	float sin_value = sin(coefficient * M_PI / 180.);

	Z.data[0][0] = cos_value;
	Z.data[1][1] = cos_value;
	Z.data[0][1] = -sin_value;
	Z.data[1][0] = sin_value;
	Z.data[2][2] = 1;

	return Z;
}

//macierz skalowania
Matrix4 GUIMyFrame1::scale(float x, float y, float z)
{
	Matrix4 scale;

	scale.data[0][0] = x;
	scale.data[1][1] = -y;
	scale.data[2][2] = z;

	return scale;
}

//funkcja rysujaca
void GUIMyFrame1::Repaint()
{
	//dlugosc i szerokosc
	int _w, _h;
	
	//panel wyswietlajacy
	wxClientDC dcClient(WxPanel);
	wxBufferedDC dcBuffer(&dcClient);
	WxPanel->GetSize(&_w, &_h);

	dcBuffer.SetBackground(wxBrush(RGB(255, 255, 255))); // ustawineie tla
	dcBuffer.Clear();	//odswiezenie
	dcBuffer.SetClippingRegion(wxRect(0, 0, _w, _h)); //ustawienie krawedzi ucinania

	//ustawienie i przeliczenei macierzy transformacji
	Matrix4 rotation_matrix = rotation_x(WxSB_RotateX->GetValue()) * rotation_y(WxSB_RotateY->GetValue()) * rotation_z(WxSB_RotateZ->GetValue());
	Matrix4 translation_matrix = translation((WxSB_TranslationX->GetValue() - 100.0) / 50.0, (WxSB_TranslationY->GetValue() - 100.0) / 50.0, (WxSB_TranslationZ->GetValue() - 100.0) / 50.0 + 2.00001);
	Matrix4 center_matrix = center();
	Matrix4 scale_matrix = scale(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0, WxSB_ScaleZ->GetValue() / 100.0);

	Matrix4 transformation_matrix = translation_matrix * rotation_matrix * scale_matrix;

	//dla kazdaego segmentu danych
	for (const auto& seg : data)
	{
		//ustawienie punktow poczatkowych i koncowych
		Vector4 first, last;
		first.Set(seg.begin.x, seg.begin.y, seg.begin.z);
		last.Set(seg.end.x, seg.end.y, seg.end.z);
		first = transformation_matrix * first;
		last = transformation_matrix * last;

		//kolor odcinka
		dcBuffer.SetPen(wxPen(RGB(seg.color.R, seg.color.G, seg.color.B)));

		//warunki rysowania i przycinania
		
		if (first.GetZ() < 0) first.Set(first.GetX(), first.GetY(),	0.0001);
		if (last.GetZ() < 0) last.Set(first.GetX(), first.GetY(), 0.0001);
		if (first.GetZ() > 0 && last.GetZ() > 0) {
			first.Set(first.GetX() / first.GetZ(), first.GetY() / first.GetZ(), first.GetZ());
			first = center_matrix * first;
			last.Set(last.GetX() / last.GetZ(), last.GetY() / last.GetZ(), last.GetZ());
			last = center_matrix * last;
			dcBuffer.DrawLine(first.GetX() * _w, first.GetY() * _h, last.GetX() * _w, last.GetY() * _h);
		}
	}
}