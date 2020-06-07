#include <wx/wx.h>
#include "GUIMyFrame1.h"
#include <math.h>
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

double shepard_interpolation(int N, float d[100][3], float x, float y) {
	double sum1 = 0, sum2 = 0;
	for (int i = 0; i < N; i++) {
		sum1 += 1. / (pow(x - d[i][0], 2) + pow(y - d[i][1], 2)) * d[i][2];
		sum2 += 1. / (pow(x - d[i][0], 2) + pow(y - d[i][1], 2));
	}
	return sum1 / sum2;
}


void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	//bitmapa 500x500pikseli
	double** points = new double*[500];

	for (int i = 0; i < 500; i++)
		points[i] = new double[500];

	double f_min, f_max;
	f_min = f_max = d[0][2];

	for (int i = 0; i < N; i++) {
		if (d[i][2] < f_min) f_min = d[i][2];
		if (d[i][2] > f_max) f_max = d[i][2];
	}

	//kolory dla kazdego z pikseli
	unsigned char* data = new unsigned char[500 * 500 * 3];

	//dyrekktywa dla procesora aby uzyl wielu watkow do petli
	#pragma omp parallel for
	for (int x = 0; x < 500; x++)
		for (int y = 0; y < 500; y++) {
			points[x][y] = shepard_interpolation(N, d, x / 100.0 - 2.5, -y / 100.0 + 2.5);
			float color = ((points[x][y] - f_min) / (f_max - f_min) - 0.5) * 2;
			switch (MappingType){
				//wypelnienie wg wzorow
			case 1:
				data[y * 500 * 3 + x * 3 + 0] = 127 - 127 * color;
				data[y * 500 * 3 + x * 3 + 1] = 0;
				data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
				break;
			case 2:
				data[y * 500 * 3 + x * 3 + 0] = color < 0 ? 255 * fabs(color) : 0;
				data[y * 500 * 3 + x * 3 + 1] = 255 - 255 * fabs(color);
				data[y * 500 * 3 + x * 3 + 2] = color > 0 ? 255 * fabs(color) : 0;
				break;
			case 3:
				data[y * 500 * 3 + x * 3 + 0] = 127 + 127 * color;
				data[y * 500 * 3 + x * 3 + 1] = 127 + 127 * color;
				data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
				break;
			default:
				break;
			}
		}

	if (MappingType) {
		wxImage tmp(500, 500, data);
		wxBitmap tmp2(tmp);
		memDC.DrawBitmap(tmp2, 0, 0);
	}



	 if (Contour) {
		 memDC.SetPen(*wxBLACK);//kolor poziomicy
		 memDC.SetBrush(*wxTRANSPARENT_BRUSH);

		 #pragma omp parallel for
		 for (int lvl = 0; lvl < NoLevels; lvl++) {
			 //wartosc poziomicy
			 double threshold_point = f_min + (lvl + 1.) * (f_max - f_min) / (NoLevels + 1.0);

			 for (int x = 0; x < 500; ++x) 
				 for (int y = 0; y < 500; ++y)
					 //sprawdzamy czy punkt jest powyzej poziomicy
					 if (points[x][y] > threshold_point) 
						 //sprawdzamy sasiednie punkty, oprocz naszego punktu
						 for (int i = -1; i <= 1; i++) 
							 for (int j = -1; j <= 1; j++)
								 //sprawdzamy czy punkty sasiednie sa po drugiej stronie poziomicy
								 if (i  && j  && x + i >= 0 && x + i < 500 && x + j >= 0 && y + j < 500 && points[x + i][y + j] < threshold_point) 
									 memDC.DrawPoint(x, y);
		 }
	 }

	 //wyswietlenie punktow dla ktorych symulujemy
	 if (ShowPoints) {
		 memDC.SetPen(*wxBLACK);
		 memDC.SetBrush(*wxTRANSPARENT_BRUSH);

		 #pragma omp parallel for
		 for (int i = 0; i < N; ++i) {
			 const int x = (d[i][0] + 2.5) * 100;
			 const int y = (2.5 - d[i][1]) * 100;

			 //krzyzyki
			 memDC.DrawLine(x, y + 3, x, y - 3);
			 memDC.DrawLine(x - 3, y, x + 3, y);
		 }
	 }


	 //zwolnienie pamieci
	 for (int i = 0; i < 500; i++)
		 delete[] points[i];
	 delete[] points;
}

