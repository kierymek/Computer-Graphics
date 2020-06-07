#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

//konstruktor
ChartClass::ChartClass(std::shared_ptr<ConfigClass> c, int w, int h) : _w{w}, _h{h}
{
    cfg= std::move(c);
    x_step=200;
}

//ustawienie zakresu
void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}

//zwraca wartosci wybranej funkcji
double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}



//funkcja rysujaca, poza osiami ukladu wspolrzenych
void ChartClass::Draw(wxDC *dc)
{

 dc->SetBackground(wxBrush(RGB(255, 255, 255)));
 dc->Clear();
 dc->SetPen(wxPen(RGB(255, 0, 0)));
 dc->DrawRectangle(10, 10, _w - 20, _h - 20);
 dc->SetClippingRegion(wxRect(10, 10, _w - 20, _h - 20));
 dc->SetPen(wxPen(RGB(0, 0, 255)));

 Matrix transformation;

 //sprawdzamy czy nie bylo obrotu
 if (cfg->RotateScreenCenter())
	 //wyliczenie macierzy transformacji
	 transformation = set_rotation(cfg->Get_Alpha()) * set_translation(cfg->Get_dX(), cfg->Get_dY()) * set_scale();
 else
	 transformation = set_translation(cfg->Get_dX(), cfg->Get_dY()) * set_rotation(cfg->Get_Alpha()) * set_scale();

 //transformacja osi ukladu wspolrzednuch
 axis(dc, transformation);

 dc->SetPen(wxPen(RGB(0, 255, 0)));

 //krok rysowania wykresu
 double step = (x_max - x_min) / x_step;

 //rysowanie wykresu krokami
 for (double i = x_min; i < x_max; i += step)
	 line2d(dc, transformation, i, GetFunctionValue(i), i + step, GetFunctionValue(i + step));


}

//rysowanie osi uk³adu wspó³rzêdnych
void ChartClass::axis(wxDC * dc, Matrix t)
{
	//oœ OX i OY
	line2d(dc, t, cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0);

	line2d(dc, t, 0, Get_Y_min() - 1.5, 0, Get_Y_max());

	//groty osi x
	line2d(dc, t, x_max + 0.05, 0, x_max - 0.07, 0.1);
	line2d(dc, t, x_max + 0.05, 0, x_max - 0.07, -0.1);
	//y
	line2d(dc, t, 0, y_max + 0.05, 0.03, y_max - 0.1);
	line2d(dc, t, 0, y_max + 0.05, -0.03, y_max - 0.1);

	double dy = 1. + int((cfg->Get_y1() - cfg->Get_y0()) / 10.);

	Vector coords;

	//wyrysowanie podzia³ek osi x
	for (double i = x_min; i <= x_max-0.2; i += 0.2)
	{
		//szerokosc podzialek
		line2d(dc, t, i, -0.06, i, 0.06);

		//koordynaty podzialek
		coords.Set(i - 0.1, -0.1);
		coords = t * coords;

		//podpisanie posia³ek osi
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coords.GetX(), _h - coords.GetY(), cfg->Get_Alpha());
	}

	//wyrysowanie podzialek osi y
	for (double i = y_min - 1.5; i <= y_max; i += M_PI / 8.)
	{
		//szerokosc podzialek
		line2d(dc, t, -0.02, i, 0.02, i);

		//koordynaty podzialek
		coords.Set(0.1, i);
		coords = t * coords;

		//podpisanie podzialek osi
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coords.GetX(), _h - coords.GetY() - 0.2, cfg->Get_Alpha());
	}
}

//rysowanie odcinkow
void ChartClass::line2d(wxDC *dc, Matrix t, double x1, double y1, double x2, double y2)
{

	Vector start_point, end_point;

	//ustawienie punktów pocz¹tkowych danego odcinka 
	start_point.Set(x1, y1);

	//pkt koncowy
	end_point.Set(x2, y2);

	//przekszta³cenie wektora macierz¹ transformacji t
	start_point = t * start_point;
	end_point = t * end_point;

	//wyrysowanie linii
	dc->DrawLine(start_point.GetX(), _h - start_point.GetY(), end_point.GetX(), _h - end_point.GetY());
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

//obliczenie macierzy obrotu
Matrix ChartClass::set_rotation(double alpha)
{
	double x, y;

	//sprawdzamy czy ekran juz obrocony
	if (cfg->RotateScreenCenter()) {
		x = _w / 2.0;
		y = _h / 2.0;
	}
	else {
		Matrix tmp = set_scale();
		x = tmp.data[0][2];
		y = tmp.data[1][2];
	}

	Matrix Rotation;

	//obliczenie potrzebnego sinusa i cosinusa
	double _cos = cos(alpha * M_PI / 180.);
	double _sin = sin(alpha * M_PI / 180.);

	//wype³nienie kolejnych pól macierzy wg wzoru
	Rotation.data[0][0] = _cos;
	Rotation.data[0][1] = -_sin;
	Rotation.data[1][0] = _sin;
	Rotation.data[1][1] = _cos;
	Rotation.data[0][2] = x * (1 - _cos) + y * _sin;
	Rotation.data[1][2] = -x * _sin + y * (1 - _cos);

	return Rotation;
}

//macierz skalowania
Matrix ChartClass::set_scale()
{
	Matrix Scale;

	//wype³nienie elementow wg wzoru
	Scale.data[0][0] = (_w - 20.0) / (cfg->Get_x1() - cfg->Get_x0());
	Scale.data[1][1] = (_h - 20.0) / (cfg->Get_y1() - cfg->Get_y0());

	Scale.data[0][2] = 10.0 - Scale.data[0][0] * cfg->Get_x0();
	Scale.data[1][2] = 10.0 - Scale.data[1][1] * cfg->Get_y0();

	return Scale;
}

//macierz translacji
Matrix ChartClass::set_translation(double x, double y)
{
	Matrix Translation;

	//wyep³nienie wg wzoru
	Translation.data[0][0] = 1.0;
	Translation.data[1][1] = 1.0;

	Translation.data[0][2] = x;
	Translation.data[1][2] = -y;

	return Translation;
}
