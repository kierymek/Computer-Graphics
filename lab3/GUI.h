///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxButton* m_button_save;
		wxCheckBox* m_check_banana;
		wxScrollBar* m_scrollBar1;
		wxGauge* m_gauge1;
		wxButton* m_button_star_color;
		wxTextCtrl* m_textCtrl1;
		wxChoice* m_choice_shape;
		
		// Virtual event handlers, overide them in your derived class
		virtual void m_panel1OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void m_panel1OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_button_saveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_check_bananaOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_scrollBar1OnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void m_button_star_colorOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_textCtrl1OnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_choice_shapeOnChoice( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GFK lab03 Adrian Góral"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 603,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MyFrame1();
	
};

#endif //__GUI_H__
