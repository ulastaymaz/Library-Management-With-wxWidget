#include "App.hpp"
#include "MainFrame.hpp"
#include <wx/wx.h>
#include <wx/dialog.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {

	//Main function of the program
	MainFrame* mainFrame = new MainFrame("C++ GUI");
	mainFrame->SetClientSize(500, 300);
	mainFrame->Center();
	mainFrame->Show();
	return true;

}
