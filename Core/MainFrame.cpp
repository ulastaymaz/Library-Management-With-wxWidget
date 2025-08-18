#include "MainFrame.hpp"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "../Dashboard/UserDashboard.hpp"
#include "../Dashboard/AdminDashboard.hpp"
MainFrame::MainFrame(const wxString& title) 
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition){
	
	//Reload data, for now it depends on text files, will be changed to sql databases
	data.reloadAdmins();
	data.reloadStudents();
	data.reloadBooks(data.dummy_books);
	wxPanel* panel = new wxPanel(this);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* userSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* passSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	
	wxStaticText* username_text = new wxStaticText(panel, wxID_ANY, "Username:");
	uid = new wxTextCtrl(panel, wxID_ANY, "");
	userSizer->Add(username_text, 0, wxLEFT, 10);
	userSizer->Add(uid, 1, wxEXPAND);

	wxStaticText* password_text = new wxStaticText(panel, wxID_ANY, "Password:");
	pwd = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	userSizer->Add(password_text, 0, wxLEFT, 10);
	userSizer->Add(pwd, 1, wxEXPAND);

	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
	wxButton* register_button = new wxButton(panel, wxID_ANY, "Register");
	buttonSizer->Add(loginButton, 1, wxLEFT, 10);
	buttonSizer->Add(register_button, 1, wxLEFT, 10);

	


	mainSizer->Add(userSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(passSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

	panel->SetSizerAndFit(mainSizer);

	loginButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoginUser, this);
	register_button->Bind(wxEVT_BUTTON, &MainFrame::OnRegisterUser, this);

	
}

void MainFrame::OnLoginUser(wxCommandEvent& event) {

    std::string username = uid->GetValue().ToStdString();
    std::string password = pwd->GetValue().ToStdString();

	//its better to check all of them at once, maybe i'll use some vector<User> users for all users
	std::optional<Student> student = utility.control_student_return(username, password, data.dummy_users);
	std::optional<Admin> admin = utility.control_admin_return(username, password, data.dummy_admins);

    if (student.has_value()) {

        UserDashboard* student_dashboard = new UserDashboard(this, "Student Dashboard", student.value(), this->books);
        student_dashboard->Show(true); // Show the student dashboard
        this->Hide();

    } 
	else if (admin.has_value()) {
		AdminDashboard* admin_dashboard = new AdminDashboard(this, "Admin Dashboard", admin.value(), this->books);
		admin_dashboard->Show(true); // Show the admin dashboard
		this->Hide();
	}
	else {
		wxMessageBox("Invalid user name or password", "Unsuccesful attempt", wxOK);
	}
	
    
}

void MainFrame::OnRegisterUser(wxCommandEvent& event) {
	//Initilize panel
	wxFrame* registerFrame = new wxFrame(this, wxID_ANY, "Register User");
	wxPanel* RegisterPanel = new wxPanel(registerFrame);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* userSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* passSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* birthSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* idSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* submit_button = new wxButton(RegisterPanel, wxID_ANY, "Submit");

	wxStaticText* name_text = new wxStaticText(RegisterPanel, wxID_ANY, "Name:");
	wxStaticText* password_text = new wxStaticText(RegisterPanel, wxID_ANY, "Password:");
	wxStaticText* birth_date_text = new wxStaticText(RegisterPanel, wxID_ANY, "Birth Date:");
	wxStaticText* id_text = new wxStaticText(RegisterPanel, wxID_ANY, "ID:");

	wxTextCtrl* name_input = new wxTextCtrl(RegisterPanel, wxID_ANY, "");
	wxTextCtrl* pwd_input = new wxTextCtrl(RegisterPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	wxTextCtrl* birth_date_input = new wxTextCtrl(RegisterPanel, wxID_ANY, "");
	wxTextCtrl* id_input = new wxTextCtrl(RegisterPanel, wxID_ANY, "");



	userSizer->Add(name_text, 0, wxLEFT, 10);
	userSizer->Add(name_input, 1, wxRIGHT | wxALL, 5);

	passSizer->Add(password_text, 0, wxLEFT, 10);
	passSizer->Add(pwd_input, 1, wxRIGHT | wxALL, 5);

	
	birthSizer->Add(birth_date_text, 0, wxLEFT, 10);
	birthSizer->Add(birth_date_input, 1, wxEXPAND | wxALL, 5);

	
	idSizer->Add(id_text, 0, wxRIGHT, 10);
	idSizer->Add(id_input, 1, wxEXPAND | wxALL, 5);

	
	buttonSizer->Add(submit_button, 1, wxALL | wxCENTER, 5);

	mainSizer->Add(userSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(passSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(birthSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(idSizer, 0, wxEXPAND | wxALL, 10);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

	RegisterPanel->SetSizerAndFit(mainSizer);

	registerFrame->SetSize(400, 300);
	registerFrame->Center();
	registerFrame->Show(true);

	//Need to change the bind function
	submit_button->Bind(wxEVT_BUTTON, [this, registerFrame, name_input, pwd_input, birth_date_input, id_input](wxCommandEvent& event) {
		wxString username = id_input->GetValue();
		if (utility.availiable_user_id(data.dummy_users, username.ToStdString()) == false) {
			wxMessageBox("Username already exists.", "Error", wxOK | wxICON_ERROR);
			return;
		}
		data.dummy_users.emplace_back(
			name_input->GetValue().ToStdString(),
			birth_date_input->GetValue().ToStdString(),
			id_input->GetValue().ToStdString(),
			pwd_input->GetValue().ToStdString()
		);
		//I have functions for SUCCESS and ERROR, need to change that too
		wxMessageBox("User registered successfully!", "Info", wxOK | wxICON_INFORMATION);
		registerFrame->Close();
		});
}

void MainFrame::Show() {
	wxFrame::Show();
	this->Center();
}

