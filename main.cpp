#include <iostream>
#include <string.h>
#include <cstring>
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define BOLDRED "\033[1;31m"
#define BOLDBLUE "\033[1;34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PURPLE "\033[35m"
#define BOLDPURPLE "\033[1;35m"
#define RED_ON_BLACK "\033[1;31;40m"
using namespace std;

// global functions to avoid code redundancy
void setter_of_char(char *&des, char *source)
{
    if (des != nullptr)
        delete[] des;

    if (source != nullptr)
    {
        des = new char[strlen(source) + 1];
        strcpy(des, source);
    }
    else
    {
        des = nullptr;
    }
}

bool findthis(char *tobesearched, char *findthis)
{
    for (int i = 0, n = strlen(tobesearched); i < n; i++)
    {
        if (tobesearched[i] == findthis[0])
            return true;
    }
    return false;
}

class number
{
public:
    char *type;
    char *arr;

public:
    number(char *a = nullptr, char *t = nullptr)
    {
        //   cout << "number constructor" << endl;
        type = nullptr;
        arr = nullptr;
        setter_of_char(arr, a);
        setter_of_char(type, t);
    }

    number(number &obj)
    {
        type = nullptr;
        arr = nullptr;
        setter_of_char(arr, obj.arr);
        setter_of_char(type, obj.type);
    }

    number &operator=(number &obj)
    {
        if (this != &obj)
        {
            setter_of_char(arr, obj.arr);
            setter_of_char(type, obj.type);
        }
        return *this;
    }

    char *get_arr()
    {
        char *temp = nullptr;
        setter_of_char(temp, arr);
        return temp;
    }

    char *get_type()
    {
        char *temp = nullptr;
        setter_of_char(temp, type);
        return temp;
    }

    void set_arr(char *a)
    {
        setter_of_char(arr, a);
    }

    void set_type(char *a)
    {
        setter_of_char(type, a);
    }

    number(number &&obj) : type(obj.type), arr(obj.arr)
    {
        obj.type = nullptr;
        obj.arr = nullptr;
    }
    number &operator=(number &&obj)
    {
        if (this != &obj)
        {
            // Clean up current resources
            if (type != nullptr)
                delete[] type;

            type = obj.type;
            arr = obj.arr;

            obj.type = nullptr;
            obj.arr = nullptr;
        }
        return *this;
    }

    ~number()
    {
        if (type != nullptr)
            delete[] type;
        if (arr != nullptr)
            delete[] arr;
        //   cout << "number destructor " << endl;
    }
};

class contact
{
protected:
    friend class phonebook;
    char *name;
    char *email;
    char *address;
    int no;
    number numbers[4];

public:
    contact(char *n = nullptr, char *a = nullptr, char *e = nullptr, number num[4] = nullptr, int no = 0) : no(no)
    {
        //  cout << "contact constructor" << endl;
        name = nullptr;
        address = nullptr;
        email = nullptr;
        setter_of_char(name, n);
        setter_of_char(address, a);
        setter_of_char(email, e);

        if (num != nullptr)
        {
            for (int i = 0; i < 4; i++)
            {
                numbers[i] = num[i];
            }
        }
    }

    contact(contact &obj) : no(obj.no)
    {
        setter_of_char(name, obj.name);
        setter_of_char(address, obj.address);
        setter_of_char(email, obj.email);
        for (int i = 0; i < 4; i++)
        {
            numbers[i] = obj.numbers[i];
        }
    }

    contact &operator=(contact &obj)
    {
        if (this != &obj)
        {
            setter_of_char(name, obj.name);
            setter_of_char(address, obj.address);
            setter_of_char(email, obj.email);
            no = obj.no;
            for (int i = 0; i < 4; i++)
            {
                numbers[i] = obj.numbers[i];
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, contact &c);
    ~contact()
    {
        if (name != nullptr)
            delete[] name;
        if (address != nullptr)
            delete[] address;

        if (email != nullptr)
            delete[] email;
        //  cout << "contact destructor " << endl;
    }
};

ostream &operator<<(ostream &out, contact &c)
{

    out << GREEN << "  ------------------------------" << RESET << endl;
    out << YELLOW << "  Name     : ";
    (c.name) ? out << c.name << endl : out << "Unknown" << endl;

    for (int i = 0; i < 4; i++)
    {
        out << "  Number " << i + 1 << " : ";
        (c.numbers[i].get_arr()) ? out << c.numbers[i].get_arr() : out << "no number";
        out << BLUE << " --> ";
        (c.numbers[i].get_type()) ? out << c.numbers[i].get_type() : out << "no type";
        out << "" << YELLOW;

        out << endl;
    }

    out << "  Email    : ";
    (c.email) ? out << c.email << endl : out << "no email" << endl;

    out << "  Address  : ";
    (c.address) ? out << c.address << endl : out << "no address" << endl;
    out << RESET;
    out << GREEN << "  ------------------------------" << RESET << endl;

    return out;
}

class phonebook
{
protected:
    contact *contact_list;
    int count;
    int max_count;

public:
    // constructor
    // max count will be initalized at 10
    phonebook(contact *c = nullptr, int count = 0, int max = 10) : count(count), max_count(max)
    {
        cout << "constructor phonebook" << endl;
        contact_list = new contact[10];
        if (c != nullptr)
        {
            for (int i = 0; i < count; i++)
            {
                contact_list[i] = c[i];
            }
        }
    }

    void manage_size_add()
    {
        if (count >= max_count)
        {
            // growth logic
            max_count = max_count * 2;

            contact *temp = new contact[max_count];
            for (int i = 0; i < count; i++)
            {
                temp[i] = contact_list[i];
            }
            delete[] contact_list;
            contact_list = temp;
        }
    }

    void manage_size_sub()
    {
        if (count < max_count / 2 && max_count > 1)
        {
            // shrink logic
            max_count = max_count / 2;

            contact *temp = new contact[max_count];
            for (int i = 0; i < count; i++)
            {
                temp[i] = contact_list[i];
            }
            delete[] contact_list;
            contact_list = temp;
        }
    }
    void search_by_num(char *temp)
    {
        if (findthis(temp, (char *)"*"))
        {
            char *copy = new char[strlen(temp) + 1];
            strcpy(copy, temp); // This creates a pointer to a string literal, which resides in read-only memory. When you pass it to strtok, which modifies the input string (in this case, it inserts '\0' where it finds delimiters like spaces), it tries to modify a read-only string, causing undefined behavior or a crash.

            // idhar tokenize karna * sa phla wala part ko
            bool dont_check_first_loop = false, dont_check_sec_loop = false, foundmatch = false, foundmatch_2 = false, display = false;

            char *ptr = strtok(copy, "*");
            char *rest_ptr = strtok(NULL, "*");
            int m = 0;

            if (copy[0] == '*')
            {
                char *temp = ptr;
                ptr = rest_ptr;
                rest_ptr = temp;
            }

            if (rest_ptr == nullptr)
                dont_check_sec_loop = true;

            if (ptr == nullptr)
                dont_check_first_loop = true;

            // cout << "ptr "<< ptr ;
            // cout<< " rst_ptr " << rest_ptr << endl;;
            // ; // A pointer to the string to begin splitting. After the first call, pass NULL to this parameter to get more pieces from the same string.

            for (int i = 0; i < count; i++)
            {
                foundmatch = false;
                display = false;
                if (!dont_check_first_loop)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (contact_list[i].numbers[j].get_arr() != nullptr)
                        {
                            if (contact_list[i].numbers[j].get_arr()[0] == ptr[0])
                            {
                                foundmatch = true;
                                display = true;
                                if (strlen(ptr) > 1)
                                {
                                    for (int k = 1, m = strlen(contact_list[i].numbers[j].get_arr()), n = strlen(ptr); k < m && k < n; k++)
                                    {
                                        if (contact_list[i].numbers[j].get_arr()[k] != ptr[k])
                                        {
                                            foundmatch = false;
                                            display = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    foundmatch = true;
                }

                if (foundmatch)
                {
                    if (!dont_check_sec_loop)
                    {
                        foundmatch_2 = false;
                        display = false;
                        for (int j = 0; j < 4; j++)
                        {
                            if (contact_list[i].numbers[j].get_arr() != nullptr)
                            {
                                int m = strlen(contact_list[i].numbers[j].get_arr()), n = strlen(rest_ptr);

                                if (contact_list[i].numbers[j].get_arr()[m - 1] == rest_ptr[n - 1])
                                {
                                    foundmatch_2 = true;
                                    display = true;
                                    if (strlen(rest_ptr) > 1)
                                    {
                                        for (int k = 1; k < m && k < n; k++)
                                        {
                                            if (contact_list[i].numbers[j].get_arr()[m - 1 - k] != rest_ptr[n - 1 - k])
                                            {
                                                foundmatch_2 = false;
                                                display = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (display)
                {
                    cout << contact_list[i] << endl;
                }
            }
        }
        // normal match
        else
        {
            for (int i = 0; i < count; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (contact_list[i].numbers[j].get_arr() != nullptr)
                    {
                        if (strcmp(contact_list[i].numbers[j].get_arr(), temp) == 0)
                        {
                            cout << contact_list[i] << endl;
                            cout << endl;
                        }
                    }
                }
            }
        }
    }

    void convert_to_lower(char*&s){
        for (int i = 0; i < strlen(s); i++)
        {
           if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] += 32;
           }
        }

    }
    void search(char *str)
    {
        // wildcard
        convert_to_lower(str);

        if (findthis(str, (char *)"*"))
        {
            char *copy = new char[strlen(str) + 1];
            strcpy(copy, str); // This creates a pointer to a string literal, which resides in read-only memory. When you pass it to strtok, which modifies the input string (in this case, it inserts '\0' where it finds delimiters like spaces), it tries to modify a read-only string, causing undefined behavior or a crash.

            // idhar tokenize karna * sa phla wala part ko
            bool dont_check_first_loop = false, dont_check_sec_loop = false, foundmatch = false, foundmatch_2 = false, display = false;

            char *ptr = strtok(copy, "*");
            char *rest_ptr = strtok(NULL, "*");
            int m = 0;

            if (copy[0] == '*')
            {
                char *temp = ptr;
                ptr = rest_ptr;
                rest_ptr = temp;
            }

            if (rest_ptr == nullptr)
                dont_check_sec_loop = true;

            if (ptr == nullptr)
                dont_check_first_loop = true;

            // cout << "ptr "<< ptr ;
            // cout<< " rst_ptr " << rest_ptr << endl;;
            // ; // A pointer to the string to begin splitting. After the first call, pass NULL to this parameter to get more pieces from the same string.
            char*temp ;

            for (int i = 0; i < count; i++)
            {
                setter_of_char(temp,contact_list[i].name );
                convert_to_lower(temp);
                foundmatch = false;
                display = false;
                if (!dont_check_first_loop)
                {
                    convert_to_lower(ptr);
                    if (temp[0] == ptr[0])
                    {
                        foundmatch = true;
                        display = true;
                        if (strlen(ptr) > 1)
                        {
                            for (int k = 1, m = strlen(contact_list[i].name), n = strlen(ptr); k < m && k < n; k++)
                            {
                                if (contact_list[i].name[k] != ptr[k])
                                {
                                    foundmatch = false;
                                    display = false;
                                }
                            }
                        }
                    }
                }
                else
                {
                    foundmatch = true;
                }

                if (foundmatch)
                {
                    if (!dont_check_sec_loop)
                    {
                        convert_to_lower(rest_ptr);
                        foundmatch_2 = false;
                        display = false;
                        int m = strlen(contact_list[i].name), n = strlen(rest_ptr);

                        if (contact_list[i].name[m - 1] == rest_ptr[n - 1])
                        {
                            foundmatch_2 = true;
                            display = true;
                            if (strlen(rest_ptr) > 1)
                            {
                                for (int k = 1; k < m && k < n; k++)
                                {
                                    if (contact_list[i].name[m - 1 - k] != rest_ptr[n - 1 - k])
                                    {
                                        foundmatch_2 = false;
                                        display = false;
                                    }
                                }
                            }
                        }
                    }
                }

                if (display)
                {
                    cout << contact_list[i] << endl;
                }
            }
            if(temp != nullptr) delete[]temp;
            if(copy != nullptr) delete[]copy;

           
        }
        // normal match
        else
        {
            // traverse through all the name jahan strcmp == 0 wahan output
            char*temp ;



            for (int i = 0; i < count; i++)
            {
                setter_of_char(temp,contact_list[i].name );
                convert_to_lower(temp);
    
                if (!(strcmp(temp, str)))
                {
                    cout << contact_list[i] << endl;
                    cout << endl;
                }
            }

           if(temp != nullptr) delete[]temp;
        }
    }

    phonebook &operator+(contact &c)
    {
        contact_list[count] = c;
        count++;
        manage_size_add();
        cout << BOLDBLUE << "Contact Succesfully Added...\n"
             << RESET;
        return *this;
    }
    void del_contact(int index)
    {
        for (int j = index; j < count - 1; j++)
        {
            contact_list[j] = contact_list[j + 1];
        }
        count--;

        manage_size_sub();
    }
    phonebook &operator-(contact &c)
    {
        // two exceptions
        // delete by name
        bool removed = false;
        if (c.numbers != nullptr)

            if (c.name != nullptr)
            {
                for (int i = 0; i < count; i++)
                {
                    if (strcmp(c.name, contact_list[i].name) == 0)
                    {
                        removed = true;
                        del_contact(i);
                    }
                }
            }
            // delete by number
            else if (c.name == nullptr)
            {
                for (int i = 0; i < count; i++)
                {
                    for (int j = 0; j < contact_list[i].no; j++)
                    {
                        if (strcmp(c.numbers[0].arr, contact_list[i].numbers[j].arr) == 0)
                        {
                            contact_list[i].numbers[j].arr = nullptr;
                            contact_list[i].no--;
                            removed = true;
                        }
                        if (contact_list[i].no == 0)
                        { // delete the whole contact and left shift or right shift
                            del_contact(i);
                        }
                    }
                }
            }

        if (removed)
            cout << BOLDBLUE << "Removed Succesfully" << RESET << endl;
        else
            cout << BOLDBLUE << "Invalid Name / Number" << endl;
        return *this;
    }

    friend ostream &operator<<(ostream &out, phonebook &obj);
    // for making - operation commutative
    friend phonebook &operator-(contact &c, phonebook &p1);

    ~phonebook()
    {

        if (contact_list != nullptr)
            delete[] contact_list;
        // cout << "phonebook destructor " << endl;
    }
};

phonebook &operator-(contact &c, phonebook &p1)
{
    // two exceptions
    return (p1 - c);
}

ostream &operator<<(ostream &out, phonebook &obj)
{
    out << RED << "**************************************************" << RESET << endl;
    // ANSI escape codes change the state of the console's text color. So, if you don’t reset, everything after the colored output stays that color
    out << BOLDRED << "Maximum Capacity " << obj.max_count << endl;
    out << "Current Count    " << obj.count << RESET << endl;

    for (int i = 0; i < obj.count; i++)
    {
        cout << obj.contact_list[i] << endl;
    }
    out << RED << "*************************************************" << RESET << endl;

    return out;
}

int main()
{
    char *name = nullptr;
    char *email = nullptr;
    char *address = nullptr;
    char *temp = new char[100];
    int n = 1, choice = 0;
    char *arr = new char[15];
    // DIUMMY DATA
    number num[4];
    num[0].set_arr((char *)"+923331234567"); // Qurrat
    num[0].set_type((char *)"mobile");

    number num1[4];
    num1[0].set_arr((char *)"03211234567"); // Zain & Samina
    num1[0].set_type((char *)"home");
    num1[1].set_arr((char *)"+923001112233");
    num1[1].set_type((char *)"mobile");

    number num2[4];
    num2[0].set_arr((char *)"03451234567"); // Akmal
    num2[0].set_type((char *)"home");
    num2[1].set_arr((char *)"+923221234567");
    num2[1].set_type((char *)"work");
    num2[2].set_arr((char *)"03001239876");
    num2[2].set_type((char *)"mobile");

    number num8[4];
    num8[0].set_arr((char *)"03011234567");
    num8[0].set_type((char *)"mobile");

    number num9[4];
    num9[0].set_arr((char *)"+923341112233");
    num9[0].set_type((char *)"work");

    number num10[4];
    num10[0].set_arr((char *)"03229998888");
    num10[0].set_type((char *)"mobile");

    number num11[4];
    num11[0].set_arr((char *)"+923001234567");
    num11[0].set_type((char *)"other");

    number num12[4];
    num12[0].set_arr((char *)"03451112233");
    num12[0].set_type((char *)"home");

    contact *c = new contact[9]{
        contact((char *)"qurrat", (char *)"Lahore, PK", (char *)"qurrat@mail.com", num, 1),
        contact((char *)"ali", (char *)"Islamabad, PK", (char *)"ali.khan@gmail.com", num, 1),
        contact((char *)"zain", (char *)"Karachi, PK", (char *)"zain123@yahoo.com", num1, 2),
        contact((char *)"samina", (char *)"Multan, PK", (char *)"samina_b@hotmail.com", num1, 2),
        contact((char *)"rehan", (char *)"Lahore", (char *)"rehan786@gmail.com", num8, 1),
        contact((char *)"reham", (char *)"Karachi", (char *)"reham90@hotmail.com", num9, 1),
        contact((char *)"rahim", (char *)"Islamabad", (char *)"rahim_1@yahoo.com", num10, 1),
        contact((char *)"rehaan", (char *)"Peshawar", (char *)"rehaan999@gmail.com", num11, 1),
        contact((char *)"rehmat", (char *)"Quetta", (char *)"rehmat@outlook.com", num12, 1)};

    phonebook myphonebook(c, 9, 10);

    for (int i = 0; i < 4; i++)
    {
        num[i].set_arr(nullptr);
    }

    do
    {
        cout << endl;
        cout << PURPLE << "1. To display all the contacts \n";
        cout << "2. To add a contact\n";
        cout << "3. To delete a contact\n";
        cout << "4. To search through contacts\n";
        cout << "5. To terminate the program\n"
             << RESET;
        cout << BOLDPURPLE << "Enter your choice (1 - 5): \n"
             << RESET;
        cin >> choice;

        while (choice <= 0 || choice > 5)
        {
            cout << RED << "Invalid choice, Please enter a number from (1 - 5)\t" << RESET;
            cin >> choice;
        }

        if (choice == 1)
        {
            // Display all contacts
            cout << BOLDBLUE << "Displaying all contacts:\n"
                 << RESET;
            cout << myphonebook << endl;
        }
        else if (choice == 2)
        {
            // Add a contact
            name = new char[50];

            cout << BOLDBLUE << "Adding a contact...\n"
                 << RESET;
            cout << BLUE << "Please Enter a name: ";
            cin >> name;

            cout << "how many numbers you want to add? ";
            cin >> n;

            while (n < 1 || n > 4)
            {
                cout << RESET << RED << "Invalid, please enter between (1 - 4) " << RESET << BLUE << endl;
                cin >> n;
            }

            for (int i = 0; i < n; i++)
            {
                cout << "Enter Number " << i + 1 << " : ";
                cin >> arr;

                // Declare and initialize char array temp
                char *temp = new char[50];

                // Prompt user to select number type
                int type_choice;
                cout << "Select number type for this entry:\n";
                cout << "1. Mobile\n";
                cout << "2. Work\n";
                cout << "3. Home\n";
                cout << "4. Other\n";

                // Input validation loop
                do
                {
                    cout << "Enter choice (1-4): ";
                    cin >> type_choice;
                    if (type_choice < 1 || type_choice > 4)
                        cout << RED << "Invalid input. Please enter a number between 1 and 4.\n"
                             << BLUE;
                } while (type_choice < 1 || type_choice > 4);

                // Set the type based on user choice
                if (type_choice == 1)
                    num[i].set_type("Mobile");
                else if (type_choice == 2)
                    num[i].set_type("Work");
                else if (type_choice == 3)
                    num[i].set_type("Home");
                else if (type_choice == 4)
                    num[i].set_type("Other");

                // Set the array or other data as needed
                num[i].set_arr(arr);
                cout << endl;
                // Null the temp pointer at the end
                delete[] temp;
            }

            char choice_email;
            cout << "Do you want to enter an email? (y/n): ";
            cin >> choice_email;
            cin.ignore();
            if (choice_email == 'y' || choice_email == 'Y')
            {
                email = new char[100];
                cout << "Enter email: ";
                cin.getline(email, 100);
            }

            // Optional address
            char choice_address;
            cout << "Do you want to enter an address? (y/n): ";
            cin >> choice_address;
            cin.ignore();
            if (choice_address == 'y' || choice_address == 'Y')
            {
                address = new char[100];
                cout << "Enter address: ";
                cin.getline(address, 100);
            }

            cout << RESET;
            contact temp(name, address, email, num, n);
            myphonebook + temp;

            for (int i = 0; i < 4; i++)
            {
                num[i].set_arr(nullptr);
            }

            n = 0;
            name = nullptr;
            email = nullptr;
            address = nullptr;
        }
        else if (choice == 3)
        {
            // Delete a contact
            name = new char[50];
            cout << BOLDBLUE << "Deleting a contact...\n"
                 << RESET;

            int delChoice = 0;
            cout << BLUE << "Delete by:\n1. Name\n2. Number\nEnter your choice: ";
            cin >> delChoice;

            while (delChoice <= 0 || delChoice > 2)
            {
                cout << RED << "Invalid option. Please choose 1 or 2.\n"
                     << RESET;
                cin >> delChoice;
            }

            if (delChoice == 1)
            {
                cout << "Enter the name to delete: ";
                cin.ignore(); // flush newline from input buffer
                cin.getline(name, 50);

                contact toDelete(name);
                myphonebook - toDelete;
            }
            else if (delChoice == 2)
            {
                cout << "Enter the number to delete: ";
                cin.ignore(); // flush newline
                cin.getline(arr, 15);

                number todelnum[4];
                todelnum[0].set_arr(arr);

                contact toDelete(nullptr, nullptr, nullptr, todelnum, 1);
                myphonebook - toDelete;
                todelnum[0].set_arr(nullptr);
            }

            n = 0;
            name = nullptr;
        }
        // else if (choice == 4)
        // {
        //     // Search for a contact
        //     cout << BOLDBLUE << "Enter (either enter full name or wildcard(only with one *)): "
        //          << RESET;
        //     cin >> temp;
        //     myphonebook.search(temp);
        // }
        else if (choice == 4)
        {
            cout << BOLDBLUE << "Searching a contact...\n"
                 << RESET;

            int searchChoice = 0;
            cout << BLUE << "Search by:\n1. Name\n2. Number\nEnter your choice: " << BLUE;
            cin >> searchChoice;

            while (searchChoice <= 0 || searchChoice > 2)
            {
                cout << RED << "Invalid option. Please choose 1 or 2.\n"
                     << BLUE;
                cin >> searchChoice;
            }

            if (searchChoice == 1)
            {
                // Search by name
                cout << BOLDBLUE << "Enter name (either full name or wildcard with one '*'): " << RESET;
                cin >> temp;
                myphonebook.search(temp);
            }
            else if (searchChoice == 2)
            {
                // Search by number
                cout << BOLDBLUE << "Enter number: " << RESET;
                cin >> temp;
                myphonebook.search_by_num(temp); // assuming same function handles number search
            }
        }

        else if (choice == 5)
        {
            cout << BOLDBLUE << "Terminating program. Goodbye!\n"
                 << RESET;
        }

    } while (choice != 5);

    cout << "end of main" << endl;
    delete[] name;
    delete[] arr;
    return 0;
}
