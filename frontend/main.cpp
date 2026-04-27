//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <cstring>
#include <string>
 

using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

public:
    void create_account(int, string, char, int);  // ✅ updated
    void show_account() const;
    void modify(string, char, int);             
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

//***************************************************************
//        UPDATED create_account FUNCTION (WEB-COMPATIBLE)
//****************************************************************

void account::create_account(int acno_, string name_, char type_, int deposit_)
{
    // Validate account number first
    if (to_string(acno_).length() != 8) {
        cout << "Invalid account number";
        return;
    }

    acno = acno_;
    strcpy(name, name_.c_str());
    type = toupper(type_);
    deposit = deposit_;

    cout << "Account Created";
}


void account::show_account() const
{
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit << endl;
}

void account::modify(string name_, char type_, int deposit_)
{
    strcpy(name, name_.c_str());
    type = toupper(type_);
    deposit = deposit_;

    cout << "Account Modified";
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}

//***************************************************************
//    	function declaration
//****************************************************************
void write_account(int, string, char, int);
void display_sp(int);
void modify_account(int, string, char, int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int, int);

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************
int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "No operation provided";
        return 0;
    }

    int choice = atoi(argv[1]);

    switch(choice)
    {
        case 1: // Create account
        {
            int acno = atoi(argv[2]);
            string name = argv[3];
            char type = argv[4][0];
            int deposit = atoi(argv[5]);

            write_account(acno, name, type, deposit);
            break;
        }

        case 2: // Deposit
        {
            int acno = atoi(argv[2]);
            int amt = atoi(argv[3]);

            deposit_withdraw(acno, 1, amt);
            break;
        }

        case 3: // Withdraw
        {
            int acno = atoi(argv[2]);
            int amt = atoi(argv[3]);

            deposit_withdraw(acno, 2, amt);
            break;
        }

        case 4: // Balance enquiry
        {
            int acno = atoi(argv[2]);
            display_sp(acno);
            break;
        }

        case 5: // Display all
        {
            display_all();
            break;
        }

        case 6: // Delete account
        {
            int acno = atoi(argv[2]);
            delete_account(acno);
            break;
        }

        case 7: // Modify account
        {
            int acno = atoi(argv[2]);
            string name = argv[3];
            char type = argv[4][0];
            int deposit = atoi(argv[5]);

            modify_account(acno, name, type, deposit);
            break;
        }

        case 8:
            cout << "Exit";
            break;

        default:
            cout << "Invalid option";
    }

    return 0;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_account(int acno, string name, char type, int deposit)
{
    account ac;
    ac.create_account(acno, name, type, deposit);

    ofstream outFile("account.txt", ios::app);

    outFile << acno << " "
            << name << " "
            << type << " "
            << deposit << endl;

    outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}

//***************************************************************
//    	function to modify record of file
//****************************************************************
void modify_account(int n, string name, char type, int deposit)
{
    bool found = false;
    account ac;
    fstream File("account.dat", ios::binary | ios::in | ios::out);

    if (!File)
    {
        cout << "File could not be open";
        return;
    }

    while (File.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.modify(name, type, deposit);

            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));

            cout << "Record Updated";
            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "Record Not Found";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option, int amt)
{
    bool found = false;
    account ac;
    fstream File("account.dat", ios::binary | ios::in | ios::out);

    if (!File)
    {
        cout << "File could not be open";
        return;
    }

    while (File.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            if (option == 1) // Deposit
            {
                ac.dep(amt);
            }
            else if (option == 2) // Withdraw
            {
                int bal = ac.retdeposit() - amt;

                if ((bal < 500 && ac.rettype() == 'S') || 
                    (bal < 1000 && ac.rettype() == 'C'))
                {
                    cout << "Insufficient balance";
                }
                else
                {
                    ac.draw(amt);
                }
            }

            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));

            cout << "Transaction Successful";
            found = true;
            break;
        }
    }

    File.close();

    if (!found)
        cout << "Record Not Found";
}



//***************************************************************
//    			END OF PROJECT
//***************************************************************
