
#pragma once
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
#include "../Data_Models/User.hpp"

class Book
{
private:
    
public:    
    std::string book_name, author_name, isbn, borrowed_by;
    bool available;

    Book();
    Book(std::string book_name, std::string author_name, std::string isbn, bool available=true, std::string borrowed_by = "None");
    void list_book() const;
    


};


