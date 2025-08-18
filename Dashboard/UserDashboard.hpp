#pragma once
#include <wx/wx.h>
#include "../Data_Models/User.hpp"
#include "../Data_Models/Book.hpp"
#include "../Core/ParentFrameInterface.hpp"
#include "../Data/Data.hpp"
class UserDashboard :public wxFrame
{
public:
	UserDashboard(ParentFrameInterface* parent, wxString title, User& student, std::vector<Book> books);
	ParentFrameInterface* parent_frame;
protected:
	void OnUserInfo(wxCommandEvent& event);
	void OnBorrowBook(wxCommandEvent& event);
	void OnReturnBook(wxCommandEvent& event);
	void OnSearchBook(wxCommandEvent& event);
	void OnBorrowedBooks(wxCommandEvent& event);
	void OnLogout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	std::pair<wxStaticText*, wxTextCtrl*> CreateInputField(wxWindow* parent, std::string label, int width);
	User student;
	std::vector<Book> books;

	Utility utility;

	inline static const std::string ERROR_TITLE = "Error";
	inline static const std::string SUCCESS_TITLE = "Success";


	void ErrorMessage(std::string message) {
		wxMessageBox(wxString(message), wxString(ERROR_TITLE), wxOK | wxICON_ERROR);
	}
	void SuccessMessage(std::string message) {
		wxMessageBox(wxString(message), wxString(SUCCESS_TITLE), wxOK | wxICON_INFORMATION);
	}


};

