#include "UserDashboard.hpp"
#include <wx/wx.h>
#include "../Data_Models/User.hpp"
#include "../Data_Models/Book.hpp"

namespace {
	inline constexpr int DIALOG_WIDTH = 450;
	inline constexpr int DIALOG_HEIGHT = 300;
	inline constexpr std::string_view DEFAULT_OWNER = "None";
}

UserDashboard::UserDashboard(ParentFrameInterface* parent, wxString title, User& student, std::vector<Book> books)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), parent_frame(parent), student(student), books(books)
{
	Center();

	wxPanel* panel = new wxPanel(this);
	SetSize(600, 400);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);


	//Starting with welcome text is unnecessary maybe i will think about it laterr
	wxStaticText* welcome_text = new wxStaticText(panel, wxID_ANY, "Welcome, " + student.name);
	wxFont font = welcome_text->GetFont();
	font.SetPointSize(16);
	welcome_text->SetFont(font);

	//Buttons for actions, maybe unnecessary, i may be create something different dunno
	wxButton* user_info_button = new wxButton(panel, wxID_ANY, "User Info");
	wxButton* borrow_book_button = new wxButton(panel, wxID_ANY, "Borrow Book");
	wxButton* borrowed_book_button = new wxButton(panel, wxID_ANY, "Borrowed Books");
	wxButton* return_book_button = new wxButton(panel, wxID_ANY, "Return Book");
	wxButton* search_book_button = new wxButton(panel, wxID_ANY, "Search Book");
	wxButton* logout_button = new wxButton(panel, wxID_ANY, "Logout");

	mainSizer->Add(welcome_text, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(user_info_button, 0, wxALL | wxALIGN_CENTER, 5);
	mainSizer->Add(borrow_book_button, 0, wxALL | wxALIGN_CENTER, 5);
	mainSizer->Add(borrowed_book_button, 0, wxALL | wxALIGN_CENTER, 5);
	mainSizer->Add(return_book_button, 0, wxALL | wxALIGN_CENTER, 5);
	mainSizer->Add(search_book_button, 0, wxALL | wxALIGN_CENTER, 5);
	mainSizer->Add(logout_button, 0, wxALL | wxALIGN_CENTER, 5);

	panel->SetSizerAndFit(mainSizer);

	user_info_button->Bind(wxEVT_BUTTON, &UserDashboard::OnUserInfo, this);
	borrow_book_button->Bind(wxEVT_BUTTON, &UserDashboard::OnBorrowBook, this);
	return_book_button->Bind(wxEVT_BUTTON, &UserDashboard::OnReturnBook, this);
	search_book_button->Bind(wxEVT_BUTTON, &UserDashboard::OnSearchBook, this);
	borrowed_book_button->Bind(wxEVT_BUTTON, &UserDashboard::OnBorrowedBooks, this);
	logout_button->Bind(wxEVT_BUTTON, &UserDashboard::OnLogout, this);


}

void UserDashboard::OnUserInfo(wxCommandEvent& event) {
	auto info = wxString::Format("Name: %s\nBirth Date: %s\nUser ID: %s\nNumber of Books: %d",
		student.name, student.birth_date, student.user_id, student.number_of_books);
	wxMessageBox(info, "User Info", wxOK | wxICON_INFORMATION);
}

void UserDashboard::OnBorrowBook(wxCommandEvent& event) {

	wxDialog borrowFrame (this, wxID_ANY, "Borrow Book");
	borrowFrame.SetSize(DIALOG_WIDTH, DIALOG_HEIGHT);
	borrowFrame.Center();

	auto* panel = new wxPanel(&borrowFrame);
	auto* mainSizer = new wxBoxSizer(wxVERTICAL);

	auto [borrowText, borrowIsbn] = CreateInputField(panel, "ISBN: ", 200);
	auto* borrowButton = new wxButton(panel, wxID_ANY, "Borrow");

	mainSizer->Add(borrowText, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(borrowIsbn, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(borrowButton, 0, wxALL | wxALIGN_CENTER, 10);
	panel->SetSizerAndFit(mainSizer);

	borrowButton->Bind(wxEVT_BUTTON, [this, borrowIsbn, &borrowFrame](wxCommandEvent& event) {

		std::string isbn = borrowIsbn->GetValue().ToStdString();

		if (isbn.empty()) {
			ErrorMessage("Please enter a valid ISBN.");
			return;
		}

		BorrowResult result = utility.borrow_book(books, student, isbn);
		switch (result) {
			case BorrowResult::Success :
				SuccessMessage("Book borrowed successfully.");
				break;
			case BorrowResult::BookNotFound :
				ErrorMessage("Book could not found.");
				break;
			case BorrowResult::BookNotAvailable :
				ErrorMessage("Book is not available.");
				break;
		}
		borrowFrame.Destroy();
	});
	borrowFrame.ShowModal();
}

void UserDashboard::OnBorrowedBooks(wxCommandEvent& event) {
	auto borrowed_books = utility.borrowed_books(books, student);
	if (borrowed_books.has_value() && !borrowed_books->empty()) {
		wxString bookList;
		for (const auto& book : *borrowed_books) {
			bookList += wxString::Format("Name: %s, Author: %s, ISBN: %s\n",
				book.book_name, book.author_name, book.isbn);
		}
		wxMessageBox(bookList, "Borrowed Books", wxOK | wxICON_INFORMATION);
	} else {
		wxMessageBox("You have no borrowed books.", "Info", wxOK | wxICON_INFORMATION);
	}
}

void UserDashboard::OnReturnBook(wxCommandEvent& event) {
	wxDialog returnDialog(this, wxID_ANY, "Return Book");
	returnDialog.SetSize(DIALOG_WIDTH, DIALOG_HEIGHT);
	returnDialog.Center();

	auto* panel = new wxPanel(&returnDialog);
	auto* mainSizer = new wxBoxSizer(wxVERTICAL);


	auto [returnText, isbnInput] = CreateInputField(panel, "Enter ISBN of the book to return ", 200);
	auto* returnButton = new wxButton(panel, wxID_ANY, "Return");


	mainSizer->Add(returnText, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(isbnInput, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(returnButton, 0, wxALL | wxALIGN_CENTER, 10);
	panel->SetSizerAndFit(mainSizer);

	returnButton->Bind(wxEVT_BUTTON, [this, isbnInput, &returnDialog](wxCommandEvent& event) {
		std::string isbn = isbnInput->GetValue().ToStdString();
		wxLogStatus(wxString::Format("ISBN: %s", isbn));
		if (isbn.empty()) {
			ErrorMessage("Please enter a valid ISBN.");
			return;
		}
		else if (utility.return_book(student, isbn, books)) {
			SuccessMessage("Book returned successfully!");
			returnDialog.Destroy();
		} 
		else {
			ErrorMessage("Failed to return book. Please check the ISBN or if the book is borrowed by you.");
		}	
	});
	returnDialog.ShowModal();

}

void UserDashboard::OnSearchBook(wxCommandEvent& event) {
	wxDialog searchDialog(this, wxID_ANY, "Search Book");
	searchDialog.SetSize(DIALOG_WIDTH, DIALOG_HEIGHT);
	searchDialog.Center();

	auto* panel = new wxPanel(&searchDialog);
	auto* mainSizer = new wxBoxSizer(wxVERTICAL);

	auto [searchText, isbnInput] = CreateInputField(panel, "Enter ISBN", 200);
	auto* searchButton = new wxButton(panel, wxID_ANY, "Search");

	mainSizer->Add(searchText, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(isbnInput, 0, wxALL | wxALIGN_CENTER, 10);
	mainSizer->Add(searchButton, 0, wxALL | wxALIGN_CENTER, 10);
	panel->SetSizerAndFit(mainSizer);

	searchButton->Bind(wxEVT_BUTTON, [this, isbnInput, &searchDialog](wxCommandEvent& event) {
		std::string isbn = isbnInput->GetValue().ToStdString();
		if (isbn.empty()) {
			ErrorMessage("Please enter a valid ISBN.");
			return;
		}

		std::optional<Book> found_book = utility.search_book(books, isbn);
		if (!found_book.has_value()) {
			ErrorMessage("Couldn't find the book");
			return;
		}
		else {
			wxString book_info = wxString::Format("Name: %s\n Author: %s\n ISBN: %s\n Available: %s",
				found_book->book_name, found_book->author_name, found_book->isbn, found_book->available ? "Yes" : "No");
			SuccessMessage("Book found");
		}
		searchDialog.Destroy();
		});
	searchDialog.ShowModal();

}

void UserDashboard::OnLogout(wxCommandEvent& event) {
	this->Destroy();
	if(parent_frame) parent_frame->Show();
}

void UserDashboard::OnClose(wxCloseEvent& event) {
	this->Destroy();
	if (parent_frame) parent_frame->Show();
}


std::pair<wxStaticText*, wxTextCtrl*> UserDashboard::CreateInputField(wxWindow* parent, std::string label, int width) {
	auto* textWidget = new wxStaticText(parent, wxID_ANY, wxString(label));
	auto* inputWidget = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxSize(width, -1));
	return{ textWidget, inputWidget };
}