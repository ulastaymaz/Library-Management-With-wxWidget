#include "Data.hpp"


Data::Data() {}

void Data::reloadStudents() {
    int test = 0;
    this->reloadUser("student_text.txt", dummy_users);
}

void Data::reloadAdmins() {
	this->reloadUser("admins_text.txt", dummy_admins);
}

void Data::reloadBooks(std::vector<Book>& books)
{
    std::string line;
    std::ifstream myfile1("books_text.txt");

    if (myfile1.is_open())
    {
        while (std::getline(myfile1, line))
        {
            Book temp;
            std::stringstream ss(line);
            std::string word;
            int i = 0;
            while (getline(ss, word, '|'))
            {
                switch (i)
                {
                case 0:
                {
                    temp.book_name = word;
                    break;
                }
                case 1:
                {
                    temp.author_name = word;
                    break;
                }
                case 2:
                {
                    temp.isbn = word;
                    break;
                }
                case 3:
                {
                    if (word == "true") temp.available = true;
                    else temp.available = false;
                    break;
                }
                case 4:
                {
                    if (word == "None") temp.borrowed_by = "None";
                    else temp.borrowed_by = word;
                    break;
                }
                default:
                    break;
                }
                i++;
            }
            dummy_books.push_back(temp);

        }
        myfile1.close();
    }

}