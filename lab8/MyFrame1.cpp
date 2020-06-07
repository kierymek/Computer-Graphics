#include "MyFrame1.h"
#include <FreeImage.h>
#include "CImg.h"
#include <wx/dcbuffer.h>
#include <wx/window.h>
#include <string>
#include <array>

void MyFrame1::FrameOnUpdateUI(wxUpdateUIEvent& event) {
	//aktualizacja okna
	wxClientDC dc(_panel);
	refresh(dc);
}

void MyFrame1::_loadButtonOnButtonClick(wxCommandEvent& event) {
	
	wxClientDC dc(_panel);
	//okno dialogowe do wczytywania pliku
	wxFileDialog * dialog = new wxFileDialog(this, "Proszę wybrać zdjęcie", "", "", wxT("Obraz JPEG (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	//sprawdzamy czy wczytaliśmy obraz, jeśli wyszlismy z okna nie bedzie zmian
	if (dialog->ShowModal() == wxID_OK)
	{
		//po wczytaniu czyscimy dane z poprzedniego obrazu
		_imageInfo->Clear();
		std::string info("Rozmiar obrazka: ");
		_image->LoadFile(dialog->GetPath(), wxBITMAP_TYPE_JPEG);
		_image1 = *_image;

		//zapis metadanych w formacie FreeImage
		FIBITMAP *bit_map = FreeImage_Load(FIF_JPEG, dialog->GetPath(), JPEG_DEFAULT);
		FITAG *tag = NULL;

		//informacje odtyczące obrazu
		info += std::to_string(FreeImage_GetWidth(bit_map)) + "*" + std::to_string(FreeImage_GetHeight(bit_map)) + "\n EXIF Info:\n";
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "Artist", &tag);
		info += std::string("Artist: ") + std::string((FreeImage_TagToString(FIMD_EXIF_MAIN, tag))) + std::string("\n");
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "Copyright", &tag);
		info += std::string("Copyright: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tag) + std::string("\n");
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "ResolutionUnit", &tag);
		info += std::string("Resolution Unit: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tag) + std::string("\n");
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "XResolution", &tag);
		info += std::string("XResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tag) + std::string("\n");
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "YCbCrPositioning", &tag);
		info += std::string("YCbCrPositioning: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tag) + std::string("\n");
		FreeImage_GetMetadata(FIMD_EXIF_MAIN, bit_map, "YResolution", &tag);
		info += std::string("YResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tag);
		FreeImage_Unload(bit_map);
		
		_imageInfo->AppendText(info);
	}
	refresh(dc);
}

void MyFrame1::_cenzuraButtonOnButtonClick(wxCommandEvent& event) {
	//przywracamy pierwotny obraz
	*_image = _image1;
	wxClientDC dc(_panel);
	if (_image->Ok()) {
		//pobieramy dane obrazu
		const int _height = 0.1 * _image->GetHeight();
		const int _width = 0.2 * _image->GetWidth();
		const int x_start = 0.55 * _image->GetWidth();
		const int y_start = 0.05 * _image->GetHeight();

		//wykorzystujemy biblioteke CIMG
		cimg_library::CImg<unsigned char> cImage(_width, _height, 1, 3);
		for (int i = 0; i < _width; i++) 
			for (int j = 0; j < _height; j++) {
				//pobieramy wycinek cenzurowanego obrazu do formatu cimg
				cImage(i, j, 0) = _image->GetRed(x_start + i, y_start + j);
				cImage(i, j, 1) = _image->GetGreen(x_start + i, y_start + j);
				cImage(i, j, 2) = _image->GetBlue(x_start + i, y_start + j);
			}
		//rozmywamy pobrany wycinek
		cImage.blur(2.5);
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _height; j++)
				//zamieniamy ocenzurowane piksele
				_image->SetRGB(x_start + i, y_start + j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		//przerysowujemy zmiany
		refresh(dc);
	}
}

void MyFrame1::_erodeButtonOnButtonClick(wxCommandEvent& event) {
	*_image = _image1;
	wxClientDC dc(_panel);

	if (_image->Ok()) {
		const int height = _image->GetHeight();
		const int width = _image->GetWidth();

		//wykorzystujemy biblioteke CIMG
		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				//pobieramy cały obraz do formatu cimg
				cImage(i, j, 0) = _image->GetRed(i, j);
				cImage(i, j, 1) = _image->GetGreen(i, j);
				cImage(i, j, 2) = _image->GetBlue(i, j);
			}
		}
		//dokonujemy rozmycia
		cImage.erode(5, 5);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				//zczytujemy spowrotem zmieniony obraz
				_image->SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		refresh(dc);
	}
}

void MyFrame1::_checkBoxOnCheckBox(wxCommandEvent& event) {
	*_image = _image1;
	wxClientDC dc(_panel);

	/*if (_image->Ok()) {
		/*const int height = _image->GetHeight();
		const int width = _image->GetWidth();

		float* spec = new float[3]{ 1.0f, 1.0f, 1.0f };
		#pragma omp parallel
		#pragma omp for schedule(dynamic, 16)
		for (int i = 720; i >= 0; --i) {
			cimg_library::CImg<float> cImage1(width, height, 1, 3);
			cimg_library::CImg<float> cImage2(width, height, 1, 3);
			for (int k = 0; k < width; ++k) {
				for (int j = 0; j < height; ++j) {
					//pobieramy cały obraz do formatu cimg
					cImage1(k, j, 0) = _image->GetRed(k, j);
					cImage1(k, j, 1) = _image->GetGreen(k, j);
					cImage1(k, j, 2) = _image->GetBlue(k, j);
				}
			}
			for (int k = 0; k < width; ++k) {
				for (int j = 0; j < height; ++j) {
					//pobieramy cały obraz do formatu cimg
					cImage2(k, j, 0) = _image->GetRed(k, j);
					cImage2(k, j, 1) = _image->GetGreen(k, j);
					cImage2(k, j, 2) = _image->GetBlue(k, j);
				}
			}
			cImage1.draw_gaussian(width / 2 + (width * 0.4) * cos(i / 2 * acos(-1) / 180.0),
				height / 2 + (height * 0.4) * sin(1 / 2 * acos(-1) / 180.0), 150.0f, spec, 1.0f);
			cImage2.draw_gaussian(width / 2 + (width * 0.4) * cos(((i / 2 + 180) % 360) * acos(-1) / 180.0),
				height / 2 + (height * 0.4) * sin(((i / 2 + 180) % 360) * acos(-1) / 180.0), 150.0f, spec, 1.0f);
			cImage1 += cImage2;
			for (int k = 0; k < width; k++)
				for (int l = 0; l < height; l++)
					//zczytujemy spowrotem zmieniony obraz
					_image->SetRGB(k, l, cImage1(k, l, 0), cImage1(k, l, 1), cImage1(k, l, 2));

			refresh(dc);
		}
	}*/
	refresh(dc);
}

void MyFrame1::refresh(wxClientDC &dc) {
	wxBufferedDC dc_buffer(&dc);
	if (_image->Ok()) {
		//przeskalowanie obrazu do okna
		_image->Rescale(dc.GetSize().x, dc.GetSize().y);
		wxBitmap bitmap(*_image);
		dc_buffer.DrawBitmap(bitmap, 0, 0);
	}
}