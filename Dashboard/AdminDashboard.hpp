#pragma once
#include "UserDashboard.hpp"
#include <memory>
class AdminDashboard : public UserDashboard
{

public:
	AdminDashboard(ParentFrameInterface* parent, wxString title, User& admin, std::vector<Book> books);
	void OnDeleteBook(wxCommandEvent& event);
	void OnEnterBook(wxCommandEvent& event);
	void OnDeleteUser(wxCommandEvent& event);
private:
	void SetupAdminUI();

};

