#include "UserAuthentication.h"
#include "UserAuthenticationSystem.cpp"
#include "DoctorsFunctions.h"
#include "DoctorsFunctions.cpp"
#include "PatientsFunctions.h"
#include "PatientsFunctions.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    // Vectors declaration
    vector<string> doctorUsernames;
    vector<string> doctorPasswords;
    vector<string> patientUsernames;
    vector<string> patientPasswords;
    vector<string> doctorNames;
    vector<string> patientNames;
    vector<string> patientReports;
    vector<vector<string>> pendingAppointments;

    // Choices
    int choice1;
    int choice2;
    int choice3;

    cout << "\n\t\t\t\t\tWelcome To Clinical Management System" << endl;

    do {
        displayMenu();
        cout << "\n\t\t\t\t\tEnter your choice\t: ";

        // Check if the input is an integer
        while (!(cin >> choice1)) {
            cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "\n\t\t\t\t\tEnter your choice\t: ";
        }

        switch (choice1) {
            case 1:
                // Registration
                system("cls");
                cout << "\n\n\t\t\t\t\t\t  Registration" << endl;
                cout << "________________________________________________________________________________________________________________________" << endl;
                int userType;
                cout << "\n\t\t\t\t\tEnter account type (Doctor - 1/ Patient - 2)\t: ";
                cin >> userType;
                if (userType == 1) {
                    RegisterDoctor(userType, doctorUsernames, doctorNames, doctorPasswords);
                } else if (userType == 2) {
                    RegisterPatient(patientUsernames, patientNames, patientPasswords);
                } else {
                    cout << "\n\t\t\t\t\tInvalid Input. Please choose 'Doctor - 1' or 'Patient - 2' ";
                }
                break;

            case 2:
                // Log-In
                system("cls");
                cout << "\n\n\t\t\t\t\t\t      Log-In" << endl;
                cout << "________________________________________________________________________________________________________________________" << endl;
                cout << "\n\t\t\t\t\tEnter user type (Doctor - 1/ Patient - 2)\t: ";
                cin >> userType;
                if (userType == 1) {
                    string doctorLoginUsername = doctorlogin(doctorUsernames, doctorPasswords);
                    if (!doctorLoginUsername.empty()) {
                        cout << "\033[1;34m\n\n\t\t\t\t\tWelcome " << doctorLoginUsername << ".....\033[0m" << endl;

                        do {
                            // Display a wait message
                            cout << "\n\n\t\t\t\t\tLoading...";

                            // Add a delay of 2 seconds before displaying the menu
                            std::this_thread::sleep_for(std::chrono::seconds(2));



                            doctorsMenu(doctorLoginUsername);
                            cout << "\n\t\t\t\t\tEnter your choice\t: ";
                            while (!(cin >> choice2)) {
                                cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "\n\t\t\t\t\tEnter your choice\t: ";
                            }
                            // Switch case for doctor's functions
                            switch (choice2)
                            {
                            case 1:
                                viewSchedule(doctorLoginUsername);
                                break;
                            case 2:
                                acceptAppointments(doctorLoginUsername);
                                break;
                            case 3:
                                viewAcceptedAppointments(doctorLoginUsername);
                                break;
                            case 4:
                                viewPendingAppointments(doctorLoginUsername);
                                break;
                            case 5:
                                patientReports = updatePatientRecords(doctorLoginUsername,patientNames,patientUsernames);
                                break;
                            case 6:
                                accessPatientRecords();
                                break;
                            case 7:
                                markAppointmentComplete(doctorLoginUsername);
                                break;
                            case 8:
                                system("cls");
                                break;

                            }
                        } while (choice2 != 6);
                    } else {
                        cout << "\n\n\t\t\t\t\t\033[1;31mLogin failed. Please check your username and password.\033[0m" << endl;
                    }
                } else if (userType == 2) {
                    string patientLoginUsername = patientlogin(patientUsernames, patientPasswords);
                    if (!patientLoginUsername.empty()) {
                        cout << "\033[1;34m\n\n\t\t\t\t\tWelcome " << patientLoginUsername << ".....\033[0m" << endl;

                        do {
                            // Display a wait message
                            cout << "\n\n\t\t\t\t\tLoading...";

                            // Add a delay of 2 seconds before displaying the menu
                            std::this_thread::sleep_for(std::chrono::seconds(2));



                            patientsMenu(patientLoginUsername);
                            cout << "\n\t\t\t\t\tEnter your choice\t: ";
                            while (!(cin >> choice3)) {
                                cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "\n\t\t\t\t\tEnter your choice\t: ";
                            }
                            // Switch case for patient's functions
                            switch (choice3)
                            {
                            case 1:
                                viewMedicalRecords(patientLoginUsername);
                                break;
                            case 2:
                                pendingAppointments = scheduleAppointments(patientLoginUsername);
                                break;
                            case 3:
                                cancelAppointments(patientLoginUsername);
                                break;
                            case 4:
                                updatePersonalInformation(patientLoginUsername);
                                break;
                            case 5:
                                displayAppointments(patientLoginUsername);
                                break;
                            case 6:
                                system("cls");
                                break;
                            }
                        } while (choice3 != 6);
                    } else {
                        cout << "\n\n\t\t\t\t\t\033[1;31mLogin failed. Please check your username and password.\033[0m" << endl;
                    }
                } else {
                    cout << "\n\t\t\t\t\tWrong UserType" << endl;
                }
                break;

            case 3:
                cout << "\n\t\t\t\t\tExiting the program." << endl;
                cout << "________________________________________________________________________________________________________________________" << endl;
                exit(0);

            default:
                cout << "\n\t\t\t\t\tInvalid choice, Try Again.." << endl;
                break;
        }
    } while (choice1 != 3 || choice2 != 5 || choice3 != 6); // Infinite loop until exit

    return 0;
}
