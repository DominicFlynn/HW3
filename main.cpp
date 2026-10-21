#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "address.h"
#include "credit_card.h"
#include "person.h"
#include "product.h"
#include "store.h"
#include "transaction.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::string;

int main()
{
    Store store1;

    // Temporary array for people before their
    // credit cards are assigned
    Person people[100];
    int people_count = 0;


    // =====================================================
    // IMPORT PRODUCTS
    // =====================================================

    ifstream product_file("products.txt");

    if (!product_file)
    {
        cout << "Error opening products.txt" << endl;
        return 1;
    }

    int product_count;

    product_file >> product_count;
    product_file.ignore();

    for (int i = 0; i < product_count; i++)
    {
        product item;

        string price_string;

        getline(product_file, item.name);
        getline(product_file, item.description);
        getline(product_file, price_string);

        item.price = stod(price_string);

        store1.add_product(item);
    }

    product_file.close();


    // =====================================================
    // IMPORT PEOPLE
    // =====================================================

    ifstream people_file("people.txt");

    if (!people_file)
    {
        cout << "Error opening people.txt" << endl;
        return 1;
    }

    people_file >> people_count;
    people_file.ignore();

    for (int i = 0; i < people_count; i++)
    {
        string name;
        string phone;

        address person_address;
        credit_card empty_card;

        getline(people_file, name);
        getline(people_file, phone);

        getline(people_file, person_address.address_line1);
        getline(people_file, person_address.address_line2);
        getline(people_file, person_address.city);
        getline(people_file, person_address.state);
        getline(people_file, person_address.zip);

        // Card will be assigned from credit_cards.txt
        empty_card.cc_number = 0;
        empty_card.limit = 0.0;
        empty_card.current_balance = 0.0;

        Person new_person(
            name,
            phone,
            person_address,
            empty_card
        );

        people[i] = new_person;
    }

    people_file.close();


    // =====================================================
    // IMPORT CREDIT CARDS
    // =====================================================

    ifstream card_file("credit_card.txt");

    if (!card_file)
    {
        cout << "Error opening credit_cards.txt" << endl;
        return 1;
    }

    int card_count;

    card_file >> card_count;
    card_file.ignore();

    for (int i = 0; i < card_count; i++)
    {
        string customer_name;
        string cc_string;
        string limit_string;
        string balance_string;

        getline(card_file, customer_name);
        getline(card_file, cc_string);
        getline(card_file, limit_string);
        getline(card_file, balance_string);

        credit_card card;

        card.cc_number = stoi(cc_string);
        card.limit = stod(limit_string);
        card.current_balance = stod(balance_string);

        // Find which person owns this credit card
        for (int j = 0; j < people_count; j++)
        {
            if (people[j].name() == customer_name)
            {
                people[j].person_credit_card(card);
                break;
            }
        }
    }

    card_file.close();


    // =====================================================
    // ADD PEOPLE TO STORE
    // =====================================================

    for (int i = 0; i < people_count; i++)
    {
        store1.add_customer(people[i]);
    }


    // =====================================================
    // PRINT INITIAL STORE INFORMATION
    // =====================================================

    cout << store1.store_info() << endl;


    // =====================================================
    // RANDOM TRANSACTIONS
    // =====================================================

    srand(time(0));

    // Requirement:
    // 10 < number of transactions < 100
    // This produces 11 through 99.
    int number_of_transactions = 11 + rand() % 89;

    for (int i = 0; i < number_of_transactions; i++)
    {
        // Pick a random customer
        int customer_index =
            rand() % store1.num_customers();

        // Pick a random product
        int product_index =
            rand() % store1.num_products();

        // Buy between 1 and 10 of the product
        int quantity = 1 + rand() % 10;

        Person customer =
            store1.get_customer(customer_index);

        product item =
            store1.get_product(product_index);

        bool successful_purchase =
            store1.make_purchase(
                customer,
                item,
                quantity
            );


        // =================================================
        // SUCCESSFUL PURCHASE
        // =================================================

        if (successful_purchase)
        {
            cout << endl;
            cout << "Successfull transaction!" << endl;
            cout << "Transaction Details:" << endl;

            // Get most recently created transaction
            transaction recent_transaction =
                store1.get_transaction(
                    store1.num_transactions() - 1
                );

            cout << recent_transaction.transaction_info()
                 << endl;
        }


        // =================================================
        // UNSUCCESSFUL PURCHASE
        // =================================================

        else
        {
            cout << endl;
            cout << "Unsuccessfull transaction!" << endl;
            cout << "Transaction Details:" << endl;

            cout << "Person:" << endl;
            cout << customer.person_info();

            cout << "Product:" << endl;
            cout << item.product_info();

            cout << "Purchase Quantity: "
                 << quantity << endl;

            cout << endl;
        }
    }


    // =====================================================
    // PRINT FINAL STORE INFORMATION
    // =====================================================

    cout << endl;
    cout << store1.store_info() << endl;


    return 0;
}
