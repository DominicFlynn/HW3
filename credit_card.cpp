#include "credit_card.h"
#include <sstream>
#include <iomanip>

bool credit_card::make_purchase(double purchase_amount)
{
    // don't allow negative or zero purchases
    if (purchase_amount <= 0)
    {
        return false;
    }

    // make sure purchase does not exceed credit limit
    if (current_balance + purchase_amount > limit)
    {
        return false;
    }

    current_balance += purchase_amount;
    return true;
}
