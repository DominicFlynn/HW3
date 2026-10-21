#include "product.h"
#include <sstream>
#include <iomanip>

std::string product::product_info()
{
    std::ostringstream output;

    output << "Name: " << name << "\n";
    output << "Description: " << description << "\n";
    output << "Price: $"
           << std::fixed << std::setprecision(2)
           << price << "\n";

    return output.str();
}