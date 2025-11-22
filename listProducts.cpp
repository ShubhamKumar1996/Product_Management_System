#include "listProducts.hpp"

using json = nlohmann::json;

struct Book {
    std::string name;
    std::string author;
    std::string price;
};

/*method to list all the products*/
void listAllBooks() {
    std::string filePath = "books.json";
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Error: Cannot open file " << filePath << "\n";
        return;
    }

    json j;
    inFile >> j;

    std::vector<Book> books;
    std::cout << "Before for loop:\n";
    for (const auto& item : j) {
        Book b;
        b.name = item.value("name", "");
        b.author = item.value("author", "");
        b.price = item.value("price", "");
        books.push_back(b);
    }

    std::cout << "Books List:\n";
    int index = 1;
    for (const auto& b : books) {
        std::cout << index++ << ". Bookname: " << b.name<<"\n"
                  << "     Author: " << b.author<<"\n"
                  << "     Price: ₹" << b.price << "\n";
    }

    return;
}