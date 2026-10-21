#include "store.h"

// Default constructor
Store::Store()
{
    num_customers_ = 0;
    num_products_ = 0;
    num_transactions_ = 0;
}


// --------------------
// Customer count
// --------------------

void Store::num_customers(int customer_count)
{
    num_customers_ = customer_count;
}

int Store::num_customers()
{
    return num_customers_;
}


// --------------------
// Product count
// --------------------

void Store::num_products(int product_count)
{
    num_products_ = product_count;
}

int Store::num_products()
{
    return num_products_;
}


// --------------------
// Transaction count
// --------------------

void Store::num_transactions(int transaction_count)
{
    num_transactions_ = transaction_count;
}

int Store::num_transactions()
{
    return num_transactions_;
}


// --------------------
// Customers
// --------------------

bool Store::add_customer(Person customer)
{
    if (num_customers_ >= 100)
    {
        return false;
    }

    customers_[num_customers_] = customer;
    num_customers_++;

    return true;
}


Person Store::get_customer(int index)
{
    if (index >= 0 && index < num_customers_)
    {
        return customers_[index];
    }

    // Return empty Person if index is invalid
    return Person();
}


int Store::find_customer(Person cust)
{
    for (int i = 0; i < num_customers_; i++)
    {
        if (customers_[i].name() == cust.name())
        {
            return i;
        }
    }

    return -1;
}


bool Store::update_customer(int index, Person customer)
{
    if (index < 0 || index >= num_customers_)
    {
        return false;
    }

    // Make sure this is the same customer
    if (customers_[index].name() != customer.name())
    {
        return false;
    }

    customers_[index] = customer;

    return true;
}


// --------------------
// Products
// --------------------

bool Store::add_product(product item)
{
    if (num_products_ >= 100)
    {
        return false;
    }

    products_[num_products_] = item;
    num_products_++;

    return true;
}


product Store::get_product(int index)
{
    if (index >= 0 && index < num_products_)
    {
        return products_[index];
    }

    product empty_product;

    empty_product.name = "";
    empty_product.description = "";
    empty_product.price = 0.0;

    return empty_product;
}


// --------------------
// Transactions
// --------------------

bool Store::add_transaction(transaction ntransaction)
{
    if (num_transactions_ >= 100)
    {
        return false;
    }

    transactions_[num_transactions_] = ntransaction;
    num_transactions_++;

    return true;
}


transaction Store::get_transaction(int index)
{
    if (index >= 0 && index < num_transactions_)
    {
        return transactions_[index];
    }

    transaction empty_transaction;

    empty_transaction.transaction_number = 0;
    empty_transaction.quantity = 0;

    return empty_transaction;
}


// --------------------
// Make Purchase
// --------------------

bool Store::make_purchase(Person customer, product item, int amount)
{
    // Quantity must be positive
    if (amount <= 0)
    {
        return false;
    }

    // Find customer in the store
    int customer_index = find_customer(customer);

    if (customer_index == -1)
    {
        return false;
    }

    // Get the customer's current credit card
    credit_card card = customers_[customer_index].person_credit_card();

    double purchase_amount = item.price * amount;

    // Try making the purchase
    if (!card.make_purchase(purchase_amount))
    {
        return false;
    }

    // Update customer's credit card
    customers_[customer_index].person_credit_card(card);

    // Create transaction
    transaction new_transaction;

    new_transaction.transaction_number = num_transactions_ + 1;
    new_transaction.customer = customers_[customer_index];
    new_transaction.purchased_item = item;
    new_transaction.quantity = amount;

    // Store transaction
    if (!add_transaction(new_transaction))
    {
        return false;
    }

    return true;
}


// --------------------
// Product Information
// --------------------

string Store::product_info()
{
    string info = "";

    info += "Products:\n";

    for (int i = 0; i < num_products_; i++)
    {
        info += products_[i].product_info();
    }

    return info;
}


// --------------------
// Customer Information
// --------------------

string Store::customer_info()
{
    string info = "";

    info += "Customers:\n";

    for (int i = 0; i < num_customers_; i++)
    {
        info += customers_[i].person_info();
    }

    return info;
}


// --------------------
// Transaction Information
// --------------------

string Store::transaction_info()
{
    string info = "";

    info += "All Transactions:\n";

    for (int i = 0; i < num_transactions_; i++)
    {
        info += transactions_[i].transaction_info();
    }

    return info;
}


// --------------------
// Entire Store
// --------------------

string Store::store_info()
{
    string info = "";

    info += "Store info:\n\n";
    info += customer_info();
    info += "\n";
    info += product_info();
    info += "\n";
    info += transaction_info();

    return info;
}


// --------------------
// Customer Purchase History
// --------------------

string Store::purchase_history(Person customer)
{
    string info = "";

    for (int i = 0; i < num_transactions_; i++)
    {
        if (transactions_[i].customer.name() == customer.name())
        {
            info += transactions_[i].transaction_info();
        }
    }

    return info;
}