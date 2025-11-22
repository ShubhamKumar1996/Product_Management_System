#ifndef VIEW_PRODUCTS_H
#define VIEW_PRODUCTS_H

#include <string>

// Function to handle viewing and searching products
void viewProducts();

// Helper function to extract values from JSON lines
std::string extractValue(const std::string& line, const std::string& key);

// Function to search products by name
void searchProductsByName();

// Function to search products by author
void searchProductsByAuthor();

// Function to display all products
void displayAllProducts();

// Function to load products from JSON file
bool loadProductsFromFile(const std::string& filename);

// Function to validate JSON file structure
bool isValidJsonFile(const std::string& filename);

#endif // VIEW_PRODUCTS_H