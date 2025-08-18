
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>
#include <optional>
#include "User.hpp"
#include "Book.hpp"
using namespace std;

User::User() {};


string User::return_name() {
    return name;
}
Admin::Admin() {
    name = "";
	birth_date = "";
	user_id = "";
    password = "";
}
Admin::Admin(string name, string birth_date, string user_id, string password) {
        this->name=name; 
        this->birth_date=birth_date; 
        this->user_id=user_id; 
        this->password=password;
    }


void Admin::delete_book_user(const string& id, vector<Student> &students, vector<Admin> &admins) {
    for (auto &student : students) {
        if (student.user_id == id) {
            student.number_of_books--;
            return;
        }
    }
    for(auto &admin : admins) {
        if (admin.user_id == id) {
			admin.number_of_books--;
            return;
        }
	}
}

void Admin::delete_book_by_isbn(vector<Book> &current_books, vector<Student> &users, vector<Admin> & admins) {  
    string isbn_1;
    cin >> isbn_1;
    for (int i = 0;i<current_books.size();i++)
    {  
        Book temp = current_books[i];
        if (temp.isbn==isbn_1)
        {
			delete_book_user(temp.borrowed_by, users, admins); 
            current_books.erase(current_books.begin() + i);
            
            return;
        }
    }
    return;

}

//I need to change that, it was left from console app
void Admin::enter_book(vector<Book> &current_books) {
    Book temp;
    std::cout<<"Enter book name: ";
    std::cin>>temp.book_name;
    std::cout<<std::endl;

    std::cout<<"Enter author name: ";
    std::cin>>temp.author_name;
    std::cout<<std::endl;

    std::cout<<"Enter book ISBN: ";
    std::cin>>temp.isbn;
    std::cout<<std::endl;

    std::cout<<"Book registered."<<std::endl;
    current_books.push_back(temp);
    if( !_kbhit() )
            _getch();


}

Student::Student(string name, string birth_date, string user_id, string password) {
        this->name=name; this->birth_date=birth_date; this->user_id=user_id; this->password=password;
    }

    //Unnecessary, it iw
Student::Student() {
    name = "";
	birth_date = "";
	user_id = "";
    password = "";
}
