#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <optional>
#include <string_view>
#include <ranges>
#include <format>
#include "../Data_Models/Book.hpp"
#include "../Data_Models/User.hpp"
#pragma warning(disable : 4996)
#include <wx/msgdlg.h>
enum class BorrowResult {
    Success,
    BookNotFound,
    BookNotAvailable
};

class Utility {
    public:
    Utility();
    std::optional<Student> control_student_return(std::string user_id_entered, std::string user_password_entered, const std::vector<Student>& student_vector);
    BorrowResult borrow_book(std::vector<Book>& books, User& user_in_process, std::string_view isbn);
    bool availiable_user_id(const std::vector<Student>& students, const std::string& user_id);
    std::optional<std::vector<Book>> borrowed_books(const std::vector<Book>& books, const User& user_in_process);
    bool return_book(User& user, std::string isbn, std::vector<Book>& books);
    std::optional<size_t> find_book_by_isbn(std::vector<Book>& books);
    std::optional<Admin> control_admin_return(std::string_view admin_id_entered, const std::string_view admin_password_entered, const std::vector<Admin>& admin_vector);
	std::optional<Book> search_book(const std::vector<Book>& books, std::string_view isbn);
};
