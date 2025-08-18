#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <optional>
#include "Utility.hpp"
using namespace std;

Utility::Utility() {};


std::optional<Student> Utility::control_student_return(std::string id, std::string pass, const vector<Student>& student_vector)
{
    auto find_student = std::ranges::find_if(student_vector, [&](const Student& student) { return student.user_id == id && student.password == pass; });
    if (find_student != student_vector.end()) return *find_student;
    else return {};
    

}

BorrowResult Utility::borrow_book(std::vector<Book>& books, User& user_in_process, std::string_view isbn)
{

    auto it = std::find_if(books.begin(), books.end(), [isbn](const Book& book) {
        return book.isbn == isbn;
        });
    if (it == books.end()) return BorrowResult::BookNotFound;
    else if (!it->available) return BorrowResult::BookNotAvailable;

    //Book borrowed
    it->available = false;
    it->borrowed_by = user_in_process.user_id;
    user_in_process.number_of_books++;
    
    return BorrowResult::Success;

}

bool Utility::availiable_user_id(const std::vector<Student>& students, const std::string& user_id) {

    return std::ranges::none_of(students, [&](const Student& s) { return s.user_id == user_id; });
}

std::optional<std::vector<Book>> Utility::borrowed_books(const std::vector<Book>& books, const User& user_in_process) {
    if (user_in_process.number_of_books == 0) {
        return {};
    }
    auto filter_books = books | std::views::filter([&](const Book& book) {return book.borrowed_by == user_in_process.user_id; });
    std::vector<Book> result(filter_books.begin(), filter_books.end());
    return result;
}

bool Utility::return_book(User& user, std::string isbn, std::vector<Book>& books) {

    auto find_book = std::ranges::find_if(books, [&](const Book& book) { return book.isbn == isbn && book.borrowed_by == user.user_id; });
    if (find_book != books.end()) {
        find_book->available = true;
        find_book->borrowed_by = "None";
        user.number_of_books -= 1;
        return true;
    } 

    return false;
}

std::optional<Admin> Utility::control_admin_return(string_view id, string_view pass, const vector<Admin>& admin_vector)
{
    auto find_admin = std::ranges::find_if(admin_vector, [&](const Admin& admins) { return admins.user_id == id && admins.password == pass; });
    if (find_admin != admin_vector.end()) return *find_admin;
    else return {};
}

std::optional<Book> Utility::search_book(const vector<Book>& books, std::string_view isbn) {
    auto find_book = std::ranges::find(books, isbn, &Book::isbn);
    if (find_book != books.end()) return *find_book;
    return {};
}
