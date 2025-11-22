#include "view_products.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "macro.h"

void viewProducts()
{
    int choice;
    bool continueLoop = true;
    
    while (continueLoop) {
        std::cout << "\n=== View Products Menu ===" << std::endl;
        std::cout << "1. Search by Name" << std::endl;
        std::cout << "2. Search by Author" << std::endl;
        std::cout << "3. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice)
        {
            case SEARCH_BY_NAME:
                searchProductsByName();
                break;
            case SEARCH_BY_AUTHOR:
                searchProductsByAuthor();
                break;
            case RETURN_TO_MAIN_MENU:
                continueLoop = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void searchProductsByName()
{
    std::string filename = "products.json";
    std::string searchProductName;
    
    std::cout << "Enter product name to search: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, searchProductName);
    
    // Convert search term to lowercase for case-insensitive search
    std::string searchLower = searchProductName;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    
    // Validate JSON file first
    if (!isValidJsonFile(filename)) {
        std::cout << "Error: Invalid JSON file format in '" << filename << "'" << std::endl;
        std::cout << "Please ensure the file contains valid JSON with an array of product objects." << std::endl;
        return;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file '" << filename << "'" << std::endl;
        std::cout << "Please make sure the products.json file exists in the current directory." << std::endl;
        return;
    }
    
    std::string line;
    std::vector<std::string> matchingProducts;
    bool found = false;
    bool inProductObject = false;
    std::string currentProduct;
    
    std::cout << "\nSearching for products with name containing: " << searchProductName << std::endl;
    std::cout << "===========================================" << std::endl;
    
    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        if (line == "{") {
            inProductObject = true;
            currentProduct = "";
        }
        else if (line == "}" || line == "},") {
            if (inProductObject && !currentProduct.empty()) {
                // Check if this product contains the [MATCH] marker for name search
                if (currentProduct.find("[MATCH]") != std::string::npos) {
                    // Remove the [MATCH] marker before adding to results
                    size_t matchPos = currentProduct.find("[MATCH] ");
                    if (matchPos != std::string::npos) {
                        currentProduct.erase(matchPos, 8); // Remove "[MATCH] "
                    }
                    matchingProducts.push_back(currentProduct);
                    found = true;
                }
            }
            inProductObject = false;
            currentProduct = "";
        }
        else if (inProductObject && line.find('"') != std::string::npos) {
            // Extract key-value pairs
            if (line.find("\"name\"") != std::string::npos) {
                std::string name = extractValue(line, "name");
                currentProduct += "Name: " + name + " | ";
                // Check if search term matches name field
                std::string nameLower = name;
                std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
                if (nameLower.find(searchLower) != std::string::npos) {
                    // Mark this product as a potential match
                    currentProduct += "[MATCH] ";
                }
            }
            else if (line.find("\"price\"") != std::string::npos) {
                std::string price = extractValue(line, "price");
                currentProduct += "Price: " + price + " | ";
            }
            else if (line.find("\"author\"") != std::string::npos) {
                std::string author = extractValue(line, "author");
                currentProduct += "Author: " + author;
            }
        }
    }
    
    file.close();
    
    if (found) {
        std::cout << "Found " << matchingProducts.size() << " matching product(s):" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (size_t i = 0; i < matchingProducts.size(); ++i) {
            std::cout << (i + 1) << ". " << matchingProducts[i] << std::endl;
            std::cout << std::endl;
        }
    } else {
        std::cout << "No products found containing: " << searchProductName << std::endl;
    }
}

void searchProductsByAuthor()
{
    std::string filename = "products.json";
    std::string searchAuthorName;
    
    std::cout << "Enter author name to search: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, searchAuthorName);
    
    // Convert search term to lowercase for case-insensitive search
    std::string searchLower = searchAuthorName;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    
    // Validate JSON file first
    if (!isValidJsonFile(filename)) {
        std::cout << "Error: Invalid JSON file format in '" << filename << "'" << std::endl;
        std::cout << "Please ensure the file contains valid JSON with an array of product objects." << std::endl;
        return;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file '" << filename << "'" << std::endl;
        std::cout << "Please make sure the products.json file exists in the current directory." << std::endl;
        return;
    }
    
    std::string line;
    std::vector<std::string> matchingProducts;
    bool found = false;
    bool inProductObject = false;
    std::string currentProduct;
    
    std::cout << "\nSearching for books by author containing: " << searchAuthorName << std::endl;
    std::cout << "===========================================" << std::endl;
    
    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        if (line == "{") {
            inProductObject = true;
            currentProduct = "";
        }
        else if (line == "}" || line == "},") {
            if (inProductObject && !currentProduct.empty()) {
                // Check if this product contains the [AUTHOR_MATCH] marker for author search
                if (currentProduct.find("[AUTHOR_MATCH]") != std::string::npos) {
                    // Remove the [AUTHOR_MATCH] marker before adding to results
                    size_t matchPos = currentProduct.find("[AUTHOR_MATCH] ");
                    if (matchPos != std::string::npos) {
                        currentProduct.erase(matchPos, 15); // Remove "[AUTHOR_MATCH] "
                    }
                    matchingProducts.push_back(currentProduct);
                    found = true;
                }
            }
            inProductObject = false;
            currentProduct = "";
        }
        else if (inProductObject && line.find('"') != std::string::npos) {
            // Extract key-value pairs
            if (line.find("\"name\"") != std::string::npos) {
                std::string name = extractValue(line, "name");
                currentProduct += "Name: " + name + " | ";
            }
            else if (line.find("\"price\"") != std::string::npos) {
                std::string price = extractValue(line, "price");
                currentProduct += "Price: " + price + " | ";
            }
            else if (line.find("\"author\"") != std::string::npos) {
                std::string author = extractValue(line, "author");
                currentProduct += "Author: " + author;
                // Check if search term matches author field
                std::string authorLower = author;
                std::transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
                if (authorLower.find(searchLower) != std::string::npos) {
                    // Mark this product as a potential match
                    currentProduct += " [AUTHOR_MATCH] ";
                }
            }
        }
    }
    
    file.close();
    
    if (found) {
        std::cout << "Found " << matchingProducts.size() << " matching book(s):" << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for (size_t i = 0; i < matchingProducts.size(); ++i) {
            std::cout << (i + 1) << ". " << matchingProducts[i] << std::endl;
            std::cout << std::endl;
        }
    } else {
        std::cout << "No books found by author containing: " << searchAuthorName << std::endl;
    }
}

std::string extractValue(const std::string& line, const std::string& key)
{
    size_t keyPos = line.find("\"" + key + "\"");
    if (keyPos == std::string::npos) return "";
    
    size_t colonPos = line.find(':', keyPos);
    if (colonPos == std::string::npos) return "";
    
    size_t valueStart = line.find('"', colonPos);
    if (valueStart == std::string::npos) return "";
    valueStart++; // Skip the opening quote
    
    size_t valueEnd = line.find('"', valueStart);
    if (valueEnd == std::string::npos) return "";
    
    return line.substr(valueStart, valueEnd - valueStart);
}

bool loadProductsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    return file.is_open();
}

bool isValidJsonFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string content;
    std::string line;
    int braceCount = 0;
    int bracketCount = 0;
    bool foundOpeningBracket = false;
    bool hasContent = false;
    
    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty()) continue;
        
        hasContent = true;
        
        // Check for opening bracket
        if (line.find('[') != std::string::npos && !foundOpeningBracket) {
            foundOpeningBracket = true;
        }
        
        // Count braces and brackets
        for (char c : line) {
            if (c == '{') braceCount++;
            else if (c == '}') braceCount--;
            else if (c == '[') bracketCount++;
            else if (c == ']') bracketCount--;
            
            // Check for negative counts (closing before opening)
            if (braceCount < 0 || bracketCount < 0) {
                file.close();
                return false;
            }
        }
    }
    
    file.close();
    
    // Validate: must have content, opening bracket, and balanced braces/brackets
    if (!hasContent || !foundOpeningBracket) {
        return false;
    }
    
    if (braceCount != 0 || bracketCount != 0) {
        return false;
    }
    
    return true;
}