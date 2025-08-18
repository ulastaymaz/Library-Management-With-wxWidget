#pragma once
#include <wx/wx.h>
#include <string>
#include <vector>
#include <optional>
#include <map>
#include "../Data_Models/User.hpp"
#include "../Data_Models/Book.hpp"
#include "../Utility/Utility.hpp"
class Data
{
public:
	Data();
	std::vector<Student> dummy_users;
    std::vector<Book> dummy_books;
    std::vector<Admin> dummy_admins;
    void reloadBooks(std::vector<Book>& books);
	void reloadStudents();
	void reloadAdmins();

    template<typename T>
    void reloadUser(const std::string& file_name, std::vector<T>& data_vector) {
        std::ifstream file(file_name);
        std::string line;
        if (file.is_open()) {
            while (std::getline(file, line))
            {
                T temp(" ", " ", " ", " ");
                std::stringstream ss(line);
                std::string word;
                int i = 0;
                while (getline(ss, word, '|'))
                {
                    switch (i)
                    {
                    case 0:
                    {
                        temp.name = word;
                        break;
                    }
                    case 1:
                    {
                        temp.birth_date = word;
                        break;
                    }
                    case 2:
                    {
                        temp.user_id = word;
                        break;
                    }
                    case 3:
                    {
                        temp.password = word;
                        break;
                    }
                    case 4:
                    {
                        temp.number_of_books = stoi(word);
                        break;
                    }
                    default:
                        break;
                    }
                    i++;
                }
                data_vector.push_back(temp);

            }
            file.close();
        }
        else {
            std::cerr << "Error: Unable to open file " << file_name << std::endl;
        }
    }
};

