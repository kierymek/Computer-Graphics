///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNHIGHLIGHT ) );
	
	bSizer2->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_button_save = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_save, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_check_banana = new wxCheckBox( this, wxID_ANY, wxT("banan"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_check_banana, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_scrollBar1 = new wxScrollBar( this, wxID_ANY, wxPoint( 100,-1 ), wxSize( 185,-1 ), wxSB_HORIZONTAL );
	m_scrollBar1->SetFont( wxFont( 100, 70, 90, 90, false, wxEmptyString ) );
	m_scrollBar1->SetMaxSize( wxSize( 100,-1 ) );
	
	bSizer3->Add( m_scrollBar1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge1->SetValue( 0 ); 
	bSizer3->Add( m_gauge1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button_star_color = new wxButton( this, wxID_ANY, wxT("kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_star_color, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_textCtrl1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxString m_choice_shapeChoices[] = { wxT("gwiazdka"), wxT("ksiê¿yc"), wxT("s³onko") };
	int m_choice_shapeNChoices = sizeof( m_choice_shapeChoices ) / sizeof( wxString );
	m_choice_shape = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 80,-1 ), m_choice_shapeNChoices, m_choice_shapeChoices, 0 );
	m_choice_shape->SetSelection( 0 );
	m_choice_shape->SetFont( wxFont( 9, 74, 90, 90, false, wxT("Arial") ) );
	
	bSizer3->Add( m_choice_shape, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_panel1->Connect( wxEVT_PAINT, wxPaintEventHandler( MyFrame1::m_panel1OnPaint ), NULL, this );
	m_panel1->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_panel1OnUpdateUI ), NULL, this );
	m_button_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button_saveOnButtonClick ), NULL, this );
	m_check_banana->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_check_bananaOnCheckBox ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_button_star_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button_star_colorOnButtonClick ), NULL, this );
	m_textCtrl1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::m_textCtrl1OnText ), NULL, this );
	m_choice_shape->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::m_choice_shapeOnChoice ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_panel1->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MyFrame1::m_panel1OnPaint ), NULL, this );
	m_panel1->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MyFrame1::m_panel1OnUpdateUI ), NULL, this );
	m_button_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button_saveOnButtonClick ), NULL, this );
	m_check_banana->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame1::m_check_bananaOnCheckBox ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_scrollBar1->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MyFrame1::m_scrollBar1OnScroll ), NULL, this );
	m_button_star_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame1::m_button_star_colorOnButtonClick ), NULL, this );
	m_textCtrl1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyFrame1::m_textCtrl1OnText ), NULL, this );
	m_choice_shape->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::m_choice_shapeOnChoice ), NULL, this );
	
}
