#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include

//#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
//#include <wx/colourdata.h>
//#include <wx/colordlg.h>
#include <wx/msgdlg.h>

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	protected:
		// Handlers for MyFrame1 events.
		void m_scrolledWindow_update( wxUpdateUIEvent& event );
		void m_b_grayscale_click( wxCommandEvent& event );
		void m_b_blur_click( wxCommandEvent& event );
		void m_b_mirror_click( wxCommandEvent& event );
		void m_b_replace_click( wxCommandEvent& event );
		void m_b_rescale_click( wxCommandEvent& event );
		void m_b_rotate_click( wxCommandEvent& event );
		void m_b_rotate_hue_click( wxCommandEvent& event );
		void m_b_mask_click( wxCommandEvent& event );
		void m_s_brightness_scroll( wxScrollEvent& event );
		void m_s_contrast_scroll( wxScrollEvent& event );
		void m_b_prewitt_click( wxCommandEvent& event );
		void m_b_threshold_click( wxCommandEvent& event );
	public:
		/** Constructor */
		GUIMyFrame1( wxWindow* parent );
	//// end generated class members

  wxImage Img_Org, // tu bedzie przechowywany oryginalny obrazek
   Img_Cpy,        // wszystkie zmiany beda wykonywane na tej kopii obrazka
   Img_Mask;       // tu bedzie przechowywana maska
  void Brightness(int value);     // funkcja zmieniajaca jasnosc obrazka
  void Contrast(int value);       // funkcja zmieniajaca kontrast obrazka
  void Repaint();
};

#endif // __GUIMyFrame1__