#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
    private:
        std::shared_ptr<ConfigClass> cfg;
        int x_step, _w, _h;         // liczba odcinkow z jakich bedzie sie skladal wykres oraz wymiary
        double x_min,x_max; // zakres zmiennej x
        double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje
        double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji
        
        void line2d(wxDC *dc, Matrix t,double x1,double y1,double x2,double y2);
        // powyzej sugerowana funkcja transformujaca odcinki 
		
		//funcja tworzaca uklad wspolrzednych
		void axis(wxDC *dc, Matrix t);

		//macierze przekszta³ceñ, które pozwol¹ na utworzenie amcierzy transformacji dla wektorow
		Matrix set_rotation(double alpha);
		Matrix set_scale();
		Matrix set_translation(double x, double y);

       
    public:
		//ustawienie wymiarow width height na sztywno
        ChartClass(std::shared_ptr<ConfigClass> c, int w = 600, int h = 400);
        void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
        double Get_Y_min(); // zwraca y_min
        double Get_Y_max(); // zwraca y_max
        void Draw(wxDC *dc);  // rysuje wykres
};

#endif
