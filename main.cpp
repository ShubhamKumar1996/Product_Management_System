#include "main.h"

int main() {
    int choice = INT_MIN;
    showMenu();
    std::cin >> choice;

    switch(choice)
    {
        case 1:
        {
            addProduct();
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            deleteProduct();
            break;
        }
        default:
        {
            break;
        }
    }
}

void showMenu()
{
    std::cout << "Menu" << std::endl;
    std::cout << "1. Add Product" << std::endl;
    std::cout << "4. Delete Product" << std::endl;
}

void addProduct()
{
    std::string bookName = "";
    std::string authorName = "";
    std::string price = "";

    std::cout << "********** Add Product Page **********" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush newline

    std::cout << "Book Name: ";
    std::getline(std::cin, bookName);
    std::cout << "Author Name: ";
    std::getline(std::cin, authorName);
    std::cout << "Price: ";
    std::getline(std::cin, price);

    std::cout << "PROVIDED INFO: " << std::endl;
    std::cout << "Book Name: " << bookName << std::endl;
    std::cout << "Author Name: " << authorName << std::endl;
    std::cout << "Price: " << price << std::endl;

    writeData(bookName, authorName, price);
}

void writeData(std::string bookName, std::string authorName, std::string price) {
    // using json = nlohmann::json;
    std::cout << "Writing Data" << std::endl;

}

void deleteProduct()
{
    std::cout << "Product Deleted" << std::endl;
}