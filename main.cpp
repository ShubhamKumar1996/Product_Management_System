#include "main.h"

using json = nlohmann::json;

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

    nlohmann::json jsonObj;

    // jsonObj[0]["Book Name"] = bookName;
    // jsonObj[0]["Author Name"] = authorName;
    // jsonObj[0]["Price"] = price;

    // jsonObj[1]["Book Name"] = bookName + bookName;
    // jsonObj[1]["Author Name"] = authorName + authorName;
    // jsonObj[1]["Price"] = price + price;

    // jsonObj["0"] = {
    //     {"Book Name", "Shubham Sandeep"},
    //     {"Author Name", "Shubham Sandeep"},
    //     {"Price", "Shubham Sandeep"}
    // };

    jsonObj["0"]["Book Name"] = "Shubham Sandeep";
    jsonObj["0"]["Author Name"] = "Shubham Sandeep";
    jsonObj["0"]["Price"] = "Shubham Sandeep";

    // jsonObj["1"] = {
    //     {"Book Name", bookName},
    //     {"Author Name", authorName},
    //     {"Price", price}
    // };

    std::fstream file("output.json", std::ios::in | std::ios::out);

    if(!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        showMenu();
    }

    file << jsonObj;
    file.close();

    std::cout << jsonObj.dump(4) << std::endl;  // pretty print JSON

    std::cout << "JSON written to output.json" << std::endl;

}

void deleteProduct()
{
    std::cout << "Product Deleted" << std::endl;
}