#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include "UserAuthentication.h"
#include "DoctorsFunctions.h"
#include "PatientsFunctions.h"
#include <sstream>

using namespace std;

void displayMenu()
{

    cout << "________________________________________________________________________________________________________________________" << endl;
    cout << "\n\n\t\t\t\t\t\tUser Account System\n"
         << endl;
    cout << "\t\t\t\t\t1. Register\n" //sign-up
         << endl;
    cout << "\t\t\t\t\t2. Login\n" //sign-in
         << endl;
    cout << "\t\t\t\t\t3. Exit\n"
         << endl;
    cout << "\n________________________________________________________________________________________________________________________"
         << endl;

}

unsigned int Hash(const string &data)
{
    unsigned int result = 0;

    for (unsigned int ch : data)
        result = ch + (result << 4) + (result << 10) - result;

    return result;
}

void RegisterDoctor(int userType, vector<string> &doctorUsernames, vector<string> &doctorNames, vector<string> &doctorPasswords )
{
    system("cls");

    ofstream doctorsCredentials("doctors_credentials.txt", ios::app);
    ofstream doctorsDetails("doctors_details.txt", ios::app);


    string docfullName;
    string genderName;
    int age, gender, phone;
    string username, password;

    if(!doctorsCredentials.is_open() || !doctorsDetails.is_open())
    {
        cerr<< "\n\t\t\t\t\tError opening schedule file" <<endl;
    }


    // Declare hashedPassword variable
    unsigned int hashedPassword;


    cout << "\n\n\t\t\t\t\t\t  Doctor Registration Menu" << endl;
    cout << "________________________________________________________________________________________________________________________\n\n" << endl;
    // Entering the username
    cout << "\n\t\t\t\t\tEnter Doctor user-name\t: ";
    cin >> username;

    // Checking for duplicate usernames
    if (find(doctorUsernames.begin(), doctorUsernames.end(), username) != doctorUsernames.end())
    {
        cout << "\n\t\t\t\t\tUsername already exists. Please choose a different username.\n";
        cout << "\n\t\t\t\t\tEnter Doctor user-name\t: ";
        cin >> username;

    }

    // Entering the password without echoing
    cout << "\n\t\t\t\t\tEnter password: ";
    cin >> password;

    // Hash the password
    hashedPassword = Hash(password);
    // clear the password variable
    password.clear();

    // Personal details
    // Full name
    cout << "\n\t\t\t\t\tEnter your Full Name: ";
    cin.ignore(); // Add this line to clear the input buffer
    getline(cin, docfullName);

    // Age
    cout << "\n\t\t\t\t\tEnter your Age: ";
    while (!(cin >> age))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid Input.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\n\t\t\t\t\tEnter your Age\t: ";
    }


    // Gender
    cout << "\n\t\t\t\t\tEnter your Gender {Male - 1/ Female - 2}: ";
    while (!(cin >> gender))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid integer.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\t\t\t\t\tEnter your Gender {Male - 1/ Female - 2}\t: ";
    }

    // Phone number
    cout << "\n\t\t\t\t\tEnter your Phone number: ";
    while (!(cin >> phone))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid Input.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\n\t\t\t\t\tEnter your Phone number\t: ";
    }

    // Gender
    genderName = (gender == 1) ? "Male" : "Female";


    // Write to details file

    doctorsDetails << "Username: " << username << "\n"
                         << "Full Name: " << docfullName << "\n"
                         << "Age: " << age << "\n"
                         << "Gender: " << genderName << "\n"
                         << "Phone: " << phone << "\n\n"
                         << endl;

    doctorNames.push_back(docfullName);

    //


       // Write to credentials file
    doctorsCredentials << username << " " << hashedPassword << "\n";

    doctorUsernames.push_back(username);
    doctorPasswords.push_back(to_string(hashedPassword));

    cout << "\n\n\t\t\t\t\t Doctor account created successfully!\n";
    // Add the new username to the vector

    doctorsCredentials.close();
    doctorsDetails.close();

}

void RegisterPatient(vector<string> &patientUsernames,vector<string> &patientNames, vector<string> &patientPasswords )
{

    system("cls");

    ofstream patientsCredentials("patients_credentials.txt", ios::app);
    ofstream patientsDetails("patients_details.txt", ios::app);


    string patfullName;
    string genderName;
    int age, gender, phone;
    string bloodGp;
    string username, password;

    if(!patientsCredentials.is_open() || !patientsDetails.is_open())
    {
        cerr<< "\n\t\t\t\t\tError opening one or many file" <<endl;
    }


    // Declare hashedPassword variable
    unsigned int hashedPassword;


    cout << "\n\n\t\t\t\t\t\t  Patient Registration Menu" << endl;
    cout << "________________________________________________________________________________________________________________________\n\n" << endl;

    // Entering the username
    cout << "\n\t\t\t\t\tEnter Patient user-name\t: ";
    cin >> username;

    // Checking for duplicate usernames
    if (find(patientUsernames.begin(), patientUsernames.end(), username) != patientUsernames.end())
    {
        cout << "\n\t\t\t\t\tUsername already exists. Please choose a different username.\n";
        cout << "\n\t\t\t\t\tEnter Patient user-name\t: ";
        cin >> username;

    }

    // Entering the password without echoing
    cout << "\n\t\t\t\t\tEnter password: ";
    cin >> password;

    // Hash the password
    hashedPassword = Hash(password);
    // clear the password variable
    password.clear();

    // Personal details
    // Full name
    cout << "\n\t\t\t\t\tEnter your Full Name: ";
    cin.ignore(); // Add this line to clear the input buffer
    getline(cin, patfullName);

    // Age
    cout << "\n\t\t\t\t\tEnter your Age: ";
    while (!(cin >> age))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid Input.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\n\t\t\t\t\tEnter your Age\t: ";
    }


    // Gender
    cout << "\n\t\t\t\t\tEnter your Gender {Male - 1/ Female - 2}: ";
    while (!(cin >> gender))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid integer.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\t\t\t\t\tEnter your Gender {Male - 1/ Female - 2}\t: ";
    }

    // Blood Group
    cout << "\n\t\t\t\t\tEnter your Blood Group{A,B,AB,O}{+,-}: ";
    while (!(cin >> bloodGp))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid Input.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\n\t\t\t\t\tEnter Blood Group{A,B,AB,O}{+,-}: ";
    }


    // Phone number
    cout << "\n\t\t\t\t\tEnter your Phone number: ";
    while (!(cin >> phone))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid Input.\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        cout << "\n\t\t\t\t\tEnter your Phone number\t: ";
    }

    // Gender
    genderName = (gender == 1) ? "Male" : "Female";


    // Write to details file

    patientsDetails << "Username: " << username << "\n"
                         << "Full Name: " << patfullName << "\n"
                         << "Age: " << age << "\n"
                         << "Gender: " << genderName << "\n"
                         << "Blood Group: " << bloodGp << "\n"
                         << "Phone: " << phone << "\n\n"
                         << endl;
    patientsCredentials << username << " " << hashedPassword << "\n";

    patientNames.push_back(patfullName);
    patientUsernames.push_back(username);
    patientPasswords.push_back(to_string(hashedPassword));


    cout << "\n\n\t\t\t\t\t Patient account created successfully!\n";
    // Add the new username to the vector

    patientsCredentials.close();
    patientsDetails.close();

}

string doctorlogin(vector<string> &doctorUsernames, vector<string> &doctorPasswords)
{
    ifstream doctorsCredentialsIn("doctors_credentials.txt", ios::in);

    // Variable declaration
    string inputUsername;
    string inputPassword;
    string storedUsername;
    string storedHashedPassword;
    string line;



    // User input username and password
    cout << "\n\t\t\t\t\tEnter the Username\t: ";
    cin >> inputUsername;

    cout << "\n\t\t\t\t\tEnter the password\t: ";
    char ch;
    while ((ch = _getch()) != 13) {  // 13 is the ASCII code for Enter key
        if (ch == 8) {  // 8 is the ASCII code for Backspace
            if (!inputPassword.empty()) {
                inputPassword.pop_back();
                cout << "\b \b";  // Move the cursor back and overwrite the character with a space
            }
        } else if (ch != 32) {  // Ignore space character
            inputPassword.push_back(ch);
            cout << '*';
        }
    }

    //saving the credentials in the credentialsFile to the vectors.

    while (doctorsCredentialsIn >> storedUsername >> storedHashedPassword) {
        getline(doctorsCredentialsIn, line);  // Read the rest of the line and discard it

        // Store the values in the vectors
        doctorUsernames.push_back(storedUsername);
        doctorPasswords.push_back(storedHashedPassword);
    }

    // Hash input password
    unsigned int hashedInputPassword = Hash(inputPassword);

    // Compare input against vectors
    for (size_t i = 0; i < doctorUsernames.size(); ++i)
    {
        if (doctorUsernames[i] == inputUsername && doctorPasswords[i] == to_string(hashedInputPassword))
        {
            doctorsCredentialsIn.close();
            return inputUsername;
        }
    }

    doctorPasswords.clear();
    doctorUsernames.clear();
    doctorsCredentialsIn.close();

    return "";
}

string patientlogin(vector<string>& patientUsernames, vector<string>& patientPasswords)
{
    ifstream patientsCredentialsIn("patients_credentials.txt", ios::in);

    // Variable declaration
    string inputUsername;
    string inputPassword;
    string storedUsername;
    string storedHashedPassword;
    string line;



    // User input username and password
    cout << "\n\t\t\t\t\tEnter the Username\t: ";
    cin >> inputUsername;

    cout << "\n\t\t\t\t\tEnter the password\t: ";
    char ch;
    while ((ch = _getch()) != 13) {  // 13 is the ASCII code for Enter key
        if (ch == 8) {  // 8 is the ASCII code for Backspace
            if (!inputPassword.empty()) {
                inputPassword.pop_back();
                cout << "\b \b";  // Move the cursor back and overwrite the character with a space
            }
        } else if (ch != 32) {  // Ignore space character
            inputPassword.push_back(ch);
            cout << '*';
        }
    }

    //saving the credentials in the credentialsFile to the vectors.

    while (patientsCredentialsIn >> storedUsername >> storedHashedPassword) {
        getline(patientsCredentialsIn, line);  // Read the rest of the line and discard it

        // Store the values in the vectors
        patientUsernames.push_back(storedUsername);
        patientPasswords.push_back(storedHashedPassword);
    }

    // Hash input password
    unsigned int hashedInputPassword = Hash(inputPassword);

    // Compare input against vectors
    for (size_t i = 0; i < patientUsernames.size(); ++i)
    {
        if (patientUsernames[i] == inputUsername && patientPasswords[i] == to_string(hashedInputPassword))
        {
            patientsCredentialsIn.close();
            return inputUsername;
        }
    }

    patientPasswords.clear();
    patientUsernames.clear();
    patientsCredentialsIn.close();

    return "";
}
