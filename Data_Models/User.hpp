#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <optional>

class Book;
class User
{
    public:
        std::string name;
        std::string birth_date;
        std::string user_id;
        std::string password;
        int number_of_books = 0;
        User();
        

        std::string return_name();

    protected:

};

class Student : public User
{
public:
    Student(std::string name, std::string birth_date, std::string user_id, std::string password);
    Student();
};

class Admin : public User{

    private:


    public:
        Admin();
        Admin(std::string name, std::string birth_date, std::string user_id, std::string password);
        
        void delete_book_by_isbn(std::vector<Book> &current_books, std::vector<Student>& users, std::vector<Admin>& admins);
        void enter_book(std::vector<Book> &current_books);
        void delete_book_user(const std::string& id, std::vector<Student>& students, std::vector<Admin>& admins);
};






