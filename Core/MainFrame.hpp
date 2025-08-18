#pragma once
#include <wx/wx.h>
#include <map>
#include "../Data/Data.hpp"
#include "../Utility/Utility.hpp"
#include "../Core/ParentFrameInterface.hpp"
#include "../Dashboard/AdminDashboard.hpp"
class MainFrame : public wxFrame, public ParentFrameInterface
{
public:
	MainFrame(const wxString& title);
	Data data;

	wxTextCtrl* uid;
	wxTextCtrl* pwd;
	wxTextCtrl* result;
	
	std::vector<Book> books = data.dummy_books;
	std::vector<Student> students = data.dummy_users;
	std::vector<Admin> admins = data.dummy_admins;

	Utility utility;

	void OnLoginUser(wxCommandEvent& event);
	void OnRegisterUser(wxCommandEvent& event);
	void clear();
	void Show() override;

};
