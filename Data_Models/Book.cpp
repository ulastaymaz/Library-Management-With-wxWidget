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
#include "Book.hpp"
using namespace std;


Book::Book() : book_name(""), author_name(""), isbn(""), available(true), borrowed_by("None") {}

Book::Book(string book_name, string author_name, string isbn, bool available, string borrowed_by)
{
    this->book_name = book_name;
    this->author_name = author_name;
    this->isbn = isbn;
    this->available = available;
    this->borrowed_by = borrowed_by;
}



void Book::list_book() const{

    std::cout<<"Book Name: "<< book_name<<std::endl;
    std::cout<<"Book Author: "<< author_name<<std::endl;
    std::cout<<"Book ISBN: "<< isbn<<std::endl;
    if (available) std::cout<<"Book Avaiable: "<< "Yes"<<std::endl;
    else std::cout<<"Book Avaiable:"<< "No"<<std::endl;
    std::cout<<"Book borrowed by: "<<borrowed_by<<std::endl;
    std::cout<<"==================================="<<std::endl;
    
};



