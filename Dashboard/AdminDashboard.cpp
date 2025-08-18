#include "AdminDashboard.hpp"
#include <wx/wx.h>
namespace {
    inline constexpr int DIALOG_WIDTH = 450;
    inline constexpr int DIALOG_HEIGHT = 300;
    inline constexpr std::string_view DEFAULT_OWNER = "None";
}

AdminDashboard::AdminDashboard(ParentFrameInterface* parent, wxString title, User& admin, std::vector<Book> books)
    : UserDashboard(parent, title, admin, books)
{
    SetTitle(title + " - Admin Panel");
    SetupAdminUI();
}

void AdminDashboard::SetupAdminUI()
{   
    //i should change that
    auto* panel = static_cast<wxPanel*>(GetChildren().GetFirst()->GetData());
    auto* mainSizer = static_cast<wxBoxSizer*>(panel->GetSizer());

    auto* add_book_button = new wxButton(panel, wxID_ANY, "Add Book");
    auto* delete_book_button = new wxButton(panel, wxID_ANY, "Delete Book");

    int logout_index = mainSizer->GetItemCount() - 1;
    mainSizer->Insert(logout_index, add_book_button, 0, wxALL | wxALIGN_CENTER, 5);
    mainSizer->Insert(logout_index + 1, delete_book_button, 0, wxALL | wxALIGN_CENTER, 5);

    add_book_button->Bind(wxEVT_BUTTON, &AdminDashboard::OnEnterBook, this);
    delete_book_button->Bind(wxEVT_BUTTON, &AdminDashboard::OnDeleteBook, this);

    panel->Layout();

    SetSize(600, 500);
}

void AdminDashboard::OnEnterBook(wxCommandEvent& event)
{
    wxDialog addBookDialog(this, wxID_ANY, "Add New Book");
    addBookDialog.SetSize(DIALOG_WIDTH, DIALOG_HEIGHT);
    addBookDialog.Center();

    auto* panel = new wxPanel(&addBookDialog);
    auto* mainSizer = new wxBoxSizer(wxVERTICAL);

	auto [nameLabel, nameInput] = CreateInputField(panel, "Book Name:", 300);
    auto [authorLabel, authorInput] = CreateInputField(panel, "Author Name:", 300);
    auto [isbnLabel, isbnInput] = CreateInputField(panel, "ISBN:", 300);

    auto* availableCheck = new wxCheckBox(panel, wxID_ANY, "Available");
    availableCheck->SetValue(true);

    auto* addButton = new wxButton(panel, wxID_ANY, "Add Book");
    auto* cancelButton = new wxButton(panel, wxID_ANY, "Cancel");

    auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    mainSizer->Add(nameLabel, 0, wxALL, 5);
    mainSizer->Add(nameInput, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(authorLabel, 0, wxALL, 5);
    mainSizer->Add(authorInput, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(isbnLabel, 0, wxALL, 5);
    mainSizer->Add(isbnInput, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(availableCheck, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER, 10);

    panel->SetSizerAndFit(mainSizer);

    addButton->Bind(wxEVT_BUTTON, [this, nameInput, authorInput, isbnInput, availableCheck, &addBookDialog](wxCommandEvent& event) {
        std::string bookName = nameInput->GetValue().ToStdString();
        std::string authorName = authorInput->GetValue().ToStdString();
        std::string isbn = isbnInput->GetValue().ToStdString();
        bool available = availableCheck->GetValue();

        if (bookName.empty() || authorName.empty() || isbn.empty()) {
			ErrorMessage("Please fill in all fields.");
            return;
        }
        auto it = std::find_if(books.begin(), books.end(), [&isbn](const Book& book) {
            return book.isbn == isbn;
            });

        if (it != books.end()) {
			ErrorMessage("A book with this ISBN already exists.");
            return;
        }

        books.emplace_back(bookName, authorName, isbn, available, "None");

		SuccessMessage("Book added successfully!");
        addBookDialog.Destroy();
        });

    cancelButton->Bind(wxEVT_BUTTON, [&addBookDialog](wxCommandEvent& event) {
        addBookDialog.Destroy();
        });

    addBookDialog.ShowModal();
}

void AdminDashboard::OnDeleteBook(wxCommandEvent& event)
{
    wxDialog deleteDialog(this, wxID_ANY, "Delete Book");
    auto* panel = new wxPanel(&deleteDialog, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    deleteDialog.SetSize(DIALOG_WIDTH, DIALOG_HEIGHT);
    deleteDialog.Center();

	auto [deleteText, isbnInput] = CreateInputField(panel, "Enter ISBN of the book to delete:", 300);

    auto* deleteButton = new wxButton(panel, wxID_ANY, "Delete");
    auto* cancelButton = new wxButton(panel, wxID_ANY, "Cancel");

    auto* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(deleteButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    mainSizer->Add(deleteText, 0, wxALL | wxALIGN_CENTER, 10);
    mainSizer->Add(isbnInput, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER, 10);

    panel->SetSizerAndFit(mainSizer);

    deleteButton->Bind(wxEVT_BUTTON, [this, isbnInput, &deleteDialog](wxCommandEvent& event) {
        std::string isbn = isbnInput->GetValue().ToStdString();

        if (isbn.empty()) {
			ErrorMessage("Please enter a valid ISBN.");
            return;
        }

        // Find book by ISBN, it was in utility, maybe i can change that
        auto it = std::find_if(books.begin(), books.end(), [&isbn](const Book& book) {
            return book.isbn == isbn;
            });

        if (it != books.end()) {
            // Check if book is currently borrowed
            if (!it->available) {
                int result = wxMessageBox(
                    wxString::Format("Book '%s' is currently borrowed by %s. Do you still want to delete it?",
                        it->book_name, it->borrowed_by),
                    "Warning", wxYES_NO | wxICON_WARNING);

                if (result == wxNO) {
                    return;
                }
            }

            int result = wxMessageBox(
                wxString::Format("Are you sure you want to delete '%s' by %s?",
                    it->book_name, it->author_name),
                "Confirm Deletion", wxYES_NO | wxICON_QUESTION);

            if (result == wxYES) {
                books.erase(it);

				SuccessMessage("Book deleted successfully!");
                deleteDialog.Destroy();
            }
        }
        else {
			ErrorMessage("Book with this ISBN not found.");
        }
        });

    cancelButton->Bind(wxEVT_BUTTON, [&deleteDialog](wxCommandEvent& event) {
        deleteDialog.Destroy();
        });

    deleteDialog.ShowModal();
}