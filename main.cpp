#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill
{
private:
    string Item;
    int Rate;
    int Quantity;

public:
    Bill() : Item(""), Rate(0), Quantity(0) {}
    void setItem(string item)
    {
        Item = item; // Change this using ->
    }
    void setRate(int rate)
    {
        Rate = rate; // Change this using ->
    }
    void setQuantity(int quantity)
    {
        Quantity = quantity; // Change this using ->
    }
    string getItem()
    {
        return Item;
    }
    int getQuantity()
    {
        return Quantity;
    }
    int getRate()
    {
        return Rate;
    }
};

void addItem(Bill b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1.Add" << endl;
        cout << "\t2.Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;
        if (choice == 1)
        {
            system("cls");
            string item;
            int rate;
            int quantity;

            cout << "\tEnter Item name: ";
            cin >> item;
            cout << "\tEnter Rate of Item: ";
            cin >> rate;
            cout << "\tEnter Quantity of Item: ";
            cin >> quantity;

            b.setItem(item);
            b.setRate(rate);
            b.setQuantity(quantity);

            ofstream out("Bill.txt", ios::app);
            if (!out)
            {
                cout << "\tError: File can not open!" << endl;
            }
            else
            {
                out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuantity() << endl
                    << endl;
            }
            out.close();
            cout << "\tItem added successfully" << endl;
            Sleep(3000);
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tBack to main menu!" << endl;
            Sleep(3000);
        }
    }
}

void printBill()
{
    system("cls");
    int count = 0;
    bool close = false;
    while (!close)
    {
        system("cls");
        int choice;
        cout << "\t1.Add Bill" << endl;
        cout << "\t2.Close Session" << endl;
        cout << "\tEnter Choice" << endl;
        cin >> choice;
        if (choice == 1)
        {
            string item;
            int quantity;

            cout << "\tEnter Item name: ";
            cin >> item;
            cout << "\tEnter Quantity of Item: ";
            cin >> quantity;

            ifstream in("Bill.txt");
            ofstream out("BillTemp.txt");

            string line;
            bool found = false;
            while (getline(in, line))
            {
                stringstream ss;
                ss << line;
                string itemName;
                int itemRate;
                int itemQuantity;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuantity;

                if (item == itemName)
                {
                    found = true;
                    if (quantity <= itemQuantity)
                    {
                        int amount = itemRate * quantity;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << " \t" << itemRate << "\t" << itemQuantity << "\t" << amount << endl;
                        int newQuantity = itemQuantity - quantity;
                        itemQuantity = newQuantity;
                        count += amount;
                        out << "\t" << itemName << " : " << itemRate << " : " << itemQuantity << endl
                            << endl;
                    }
                    else
                    {
                        cout << "\tSorry, " << item << "Ended!" << endl;
                    }
                }
                else
                {
                    out << line << endl;
                }
            }
            if (!found)
            {
                cout << "\tItem not available.";
            }
            out.close();
            in.close();
            remove("Bill.txt");
            rename("BillTemp.txt", "Bill.txt");
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout << endl
         << endl;
    cout << "\tTotal Bill ------------------------: " << count << endl
         << endl;
    cout << "\tThanks for Shopping!" << endl;
    Sleep(5000);
}

int main()
{
    Bill b;
    bool exit = false;

    while (!exit)
    {
        system("cls");
        int val;
        cout << "\tWelcome to Supermarket Billing System" << endl;
        cout << "\t*************************************" << endl;
        cout << "\t\t1. Add Item." << endl;
        cout << "\t\t2. Print Bill." << endl;
        cout << "\t\t3. Exit." << endl;
        cout << "\t\t Enter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            Sleep(3000);
            addItem(b);
        }
        else if (val == 2)
        {
            printBill();
        }
        else if (val == 3)
        {
            system("cls");
            exit = true;
            cout << "\t Good Luck!" << endl;
            Sleep(3000);
        }
    }
}