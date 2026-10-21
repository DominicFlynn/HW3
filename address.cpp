#include "address.h"

string address::address_info()
{
    string info = "";

    info += "Address:\n";
    info += address_line1 + "\n";

    if (address_line2 != "")
    {
        info += address_line2 + "\n";
    }

    info += city + "\n";
    info += state + "\n";
    info += zip + "\n";

    return info;
}