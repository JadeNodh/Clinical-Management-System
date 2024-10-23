#include "PatientsFunctions.h"
#include "UserAuthentication.h"
#include "DoctorsFunctions.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

bool isValidDate(const string& date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    // Extract year, month, and day from the date string
    int year, month, day;
    stringstream(date.substr(0, 4)) >> year;
    stringstream(date.substr(5, 2)) >> month;
    stringstream(date.substr(8, 2)) >> day;

    // Check if month and day are within valid ranges
    return (month >= 1 && month <= 12 && day >= 1 && day <= 31);
}

bool isValidTime(const string& time)
{
    if (time.size() != 5 || time[2] != ':') {
        return false;
    }

    // Extract hours and minutes from the time string
    int hours, minutes;
    stringstream(time.substr(0, 2)) >> hours;
    stringstream(time.substr(3, 2)) >> minutes;

    // Check if hours and minutes are within valid ranges
    return (hours >= 0 && hours <= 24 && minutes >= 0 && minutes < 60);
}

void patientsMenu(const string& patientLoginUsername)
{
    // Patient's menu
    cout << "\n________________________________________________________________________________________________________________________" << endl;
    cout << "\n\n\t\t\t\t\t\tPatients Menu\n" << endl;
    cout << "\t\t\t\t\t1. View medical records\n" << endl;
    cout << "\t\t\t\t\t2. Schedule Appointments\n" << endl;
    cout << "\t\t\t\t\t3. Cancel Appointments\n" << endl;
    cout << "\t\t\t\t\t4. Update Personal information\n" << endl;
    cout << "\t\t\t\t\t5. Display Appointments\n" << endl;
    cout << "\t\t\t\t\t6. Go Back to Main Menu" << endl;
}

void viewMedicalRecords(const string&  patientLoginUsername)
{

    ifstream viewPatientsRecords("patients_records.txt", ios::in);


    if(!viewPatientsRecords.is_open())
    {
        cerr<< "\n\t\t\t\t\tError opening records file" <<endl;
    }

    // variable declaration
    string line;
    string key;
    string value;
    string storedPatUsername;
    string storedpatientname;
    string diagnosisReport;
    string medicationsReport;
    string recommendationsReport;

     // Read and process each line in the schedule file
    while (getline(viewPatientsRecords, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            key = line.substr(0, colonPos);
            value = line.substr(colonPos + 2); // Skip the colon and the space
        }

        if (key == "Username")
        {
            storedPatUsername = value;
        }
        else if (key == "Name")
        {
            storedpatientname = value;
        }
        else if (key == "Diagnosis Report")
        {
            diagnosisReport = value;
        }
        else if (key == "Medications Report")
        {
            medicationsReport = value;

        }
        else if (key == "Recommendations Report")
        {
            recommendationsReport = value;

            // Check if the appointment belongs to the logged-in doctor
            if (storedPatUsername == patientLoginUsername)
            {
                cout << "\n________________________________________________________________________________________________________________________\n" << endl;
                cout<< "\n\t\t\t\t\tPatient Name: " << storedPatUsername << "\n"
                         << "\n\t\t\tDiagnosis Report: " << diagnosisReport << "\n"
                         << "\n\t\t\tMedications Report: " << medicationsReport << "\n"
                         << "\n\t\t\tRecommendations Report: " << recommendationsReport << "\n"
                         << endl;



           }
        }

    }


}

vector<vector<string>> scheduleAppointments(const string& patientLoginUsername)
{
    ifstream scheduleFileIn("pending_file.txt", ios::in);
    ofstream scheduleFileOut("pending_file.txt", ios::app);
    ifstream doctorsDetailsIn("doctors_details.txt", ios::in);

    vector<vector<string>> pendingappointments;
    vector<string> doctorUsernamesIn;
    vector<string> doctorNamesIn;

    if (!scheduleFileIn.is_open() || !doctorsDetailsIn.is_open() || !scheduleFileOut.is_open())
    {
        cerr << "\n\t\t\t\t\tError opening schedule file or doctor details file" << endl;
        return pendingappointments;
    }

    cout << "\n________________________________________________________________________________________________________________________\n" << endl;

    // Read doctor details from the file
    string line;
    string storedUsername;
    string storedName;
    while (getline(doctorsDetailsIn, line))
    {
        if (line.find("Username: ") != string::npos)
        {
            storedUsername = line.substr(line.find("Username: ") + 10); // Extract the username
            doctorUsernamesIn.push_back(storedUsername);
        }
        else if (line.find("Full Name: ") != string::npos)
        {
            storedName = line.substr(line.find("Full Name: ") + 11); // Extract the full name
            doctorNamesIn.push_back(storedName);
        }
    }

    cout << "\n\t\t\t\t\tAvailable Doctors:" << endl;
    for (size_t i = 0; i < doctorNamesIn.size(); ++i)
    {
        cout << "\n\t\t\t\t\t" << i + 1 << ". Name: " << doctorNamesIn[i] << endl;
    }



    int choice;
    cout << "\n\t\t\t\t\tSelect a doctor by entering the corresponding number: ";

    // Error handling
    while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(doctorUsernamesIn.size()))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "\n\t\t\t\t\tSelect a doctor by entering the corresponding number: ";
    }

    // Get the selected doctor's username and name
    string selectedDoctorUsername = doctorUsernamesIn[static_cast<size_t>(choice - 1)];
    string selectedDoctorName = doctorNamesIn[static_cast<size_t>(choice - 1)];

    string date;
    string time;
    bool isUniqueDateTime;

    // Prompt the user to enter a unique date and time for the appointment
   do {
        isUniqueDateTime = true;

        cout << "\n\t\t\t\t\tEnter the appointment date (YYYY-MM-DD): ";
        cin >> date;

        // Check if the date has the correct format and values
        if (!isValidDate(date)) {
            cout << "\n\t\t\t\t\tInvalid date format or value. Please enter the date in the correct format.\n";
            isUniqueDateTime = false;
            continue;
        }

        cout << "\n\t\t\t\t\tEnter the appointment time (HH:MM): ";
        cin >> time;

        // Check if the time has the correct format and values
        if (!isValidTime(time)) {
            cout << "\n\t\t\t\t\tInvalid time format or value. Please enter the time in the correct format.\n";
            isUniqueDateTime = false;
            continue;
        }

        // Checking whether the selected doctor already has an appointment at the specified time and date
        auto it = find_if(pendingappointments.begin(), pendingappointments.end(), [&](const vector<string>& appt)
                          {
                              return appt[2] == selectedDoctorUsername && appt[4] == date && appt[5] == time;
                          });

        if (it != pendingappointments.end())
        {
            cout << "\n\t\t\t\t\tThe selected doctor already has an appointment at the specified time and date.\n";
            isUniqueDateTime = false;
        }
    } while (!isUniqueDateTime);

    // Create a new appointment
    vector<string> newAppointment;
    int uniqueNumber = static_cast<int>(pendingappointments.size() + 1); // Use the number of existing appointments as a unique number
    newAppointment.push_back(to_string(uniqueNumber));
    newAppointment.push_back(patientLoginUsername);
    newAppointment.push_back(selectedDoctorUsername);
    newAppointment.push_back(selectedDoctorName);
    newAppointment.push_back(date);
    newAppointment.push_back(time);
    newAppointment.push_back("Pending");

    // Add the new appointment to the 2D vector
    pendingappointments.push_back(newAppointment);

    // Write the appointment request to the file
    scheduleFileOut << "Appointment No: " << uniqueNumber << "\n"
                    << "Patient Name: " << patientLoginUsername << "\n"
                    << "Doctor Username: " << selectedDoctorUsername << "\n"
                    << "Doctor Name: " << selectedDoctorName << "\n"
                    << "Date: " << date << "\n"
                    << "Time: " << time << "\n"
                    << "Status: Pending" << "\n"
                    << endl;

    cout << "\n\t\t\t\t\tAppointment scheduled to " << selectedDoctorName << ".\n";

    // Close file streams
    scheduleFileIn.close();
    scheduleFileOut.close();
    doctorsDetailsIn.close();




    // Return the updated appointments vector
    return pendingappointments;
}

void cancelAppointments(const string& patientLoginUsername)
{
    ifstream scheduleFileIn("pending_file.txt");
    ofstream tempFileOut("temp_pending_file.txt");

    // Check if the files are open
    if (!scheduleFileIn.is_open() || !tempFileOut.is_open()) {
        cerr << "Error opening schedule files." << endl;
        return;
    }

    vector<string> patientAppointments;
    string line;
    bool appointmentFound = false;
    bool inAppointment = false;
    string currentAppointment;

    // Read appointments from the file
    while (getline(scheduleFileIn, line)) {
        // Check if the line contains appointment information
        if (line.substr(0, 15) == "Appointment No:") {
            // If already in an appointment, add the previous one to the vector
            if (inAppointment) {
                patientAppointments.push_back(currentAppointment);
            }
            // Start a new appointment
            inAppointment = true;
            currentAppointment = line + "\n"; // Initialize with the current line
        } else if (line.substr(0, 6) == "Status" && line.find("Pending") != string::npos) {
            // Check if the appointment is pending and belongs to the patient
            if (currentAppointment.find("Patient Name: " + patientLoginUsername) != string::npos) {
                appointmentFound = true;
                currentAppointment += line + "\n"; // Add status line to current appointment
            }
        } else if (inAppointment) {
            // Add other lines of the appointment
            currentAppointment += line + "\n";
        }
    }

    // Add the last appointment if it's pending
    if (inAppointment && currentAppointment.find("Patient Name: " + patientLoginUsername) != string::npos) {
        patientAppointments.push_back(currentAppointment);
    }

    scheduleFileIn.close();
    tempFileOut.close();

    // If no appointment was found for the patient
    if (!appointmentFound) {
        cout << "\n\t\t\t\t\tYou have no pending appointments." << endl;
        return;
    }

    // Display patient's appointments
    cout << "\n\t\t\t\t\tYour Pending Appointments:" << endl;
    cout << "\n________________________________________________________________________________________________________________________\n" << endl;
    for (const auto& appointment : patientAppointments) {
        // Split appointment details by newline and add indentation to each line
        stringstream ss(appointment);
        string line;
        while (getline(ss, line)) {
            cout << "\n\t\t\t\t\t" << line << endl;
        }
}

    // Ask the patient to choose an appointment to cancel
    int choice;
    cout << "\n\t\t\tEnter the number of the appointment you want to cancel (or 0 to cancel nothing): ";
    cin >> choice;

    if (choice >= 1 && static_cast<size_t>(choice) <= patientAppointments.size()) {
        char deleteOption;
        cout << "\n\t\t\tAre You Sure You Want To Delete This Appointment (y/n)? ";
        cin >> deleteOption;

        if (deleteOption == 'Y' || deleteOption == 'y') {
            // Remove the selected appointment from the vector
            patientAppointments.erase(patientAppointments.begin() + choice - 1);

            // Rewrite the file with updated appointments
            ofstream scheduleFileOut("pending_file.txt");
            if (!scheduleFileOut.is_open()) {
                cerr << "Error opening schedule file for writing." << endl;
                return;
            }

            for (const auto& appointment : patientAppointments) {
                scheduleFileOut << appointment;
            }

            scheduleFileOut.close();

            cout << "\n\t\t\tThe Appointment Has Been Successfully Canceled." << endl;
        } else {
            cout << "\n\t\t\tNo appointments were canceled." << endl;
        }
    } else if (choice != 0) {
        cout << "\n\t\t\tInvalid input. No appointments were canceled." << endl;
    }
}

void updatePersonalInformation(const string& patientLoginUsername)
{
    ifstream detailsFile("patients_details.txt");
    ofstream detailsFileOut("tempDetailsFile.txt");

    if (!detailsFile.is_open() || !detailsFileOut.is_open()) {
        cerr << "\n\t\t\t\t\tError opening details file" << endl;
        return;
    }

    // Read existing patient details from the file
    vector<string> patientDetails;
    string line;

    bool patientFound = false;

    while (getline(detailsFile, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2); // Skip the colon and the space

            if (key == "Username" && value == patientLoginUsername) {
                // Found the patient's details, update them
                patientFound = true;

                cout << "\n\t\t\t\t\tUpdating Personal Information for Patient: " << patientLoginUsername << endl;
                cout << "\n________________________________________________________________________________________________________________________\n" << endl;


                // Update any relevant information here
                vector<string> updatedDetails;

                updatedDetails.push_back("Username: " + patientLoginUsername);

                cout << "\n\t\t\t\t\tEnter new Full Name: ";
                cin.ignore(); // Clear input buffer
                getline(cin, line);
                updatedDetails.push_back("Full Name: " + line);

                cout << "\n\t\t\t\t\tEnter new Age: ";
                getline(cin, line);
                updatedDetails.push_back("Age: " + line);

                cout << "\n\t\t\t\t\tEnter Gender: ";
                getline(cin, line);
                updatedDetails.push_back("Gender: " + line);

                cout << "\n\t\t\t\t\tEnter Blood Group: ";
                getline(cin, line);
                updatedDetails.push_back("Blood Group: " + line);

                cout << "\n\t\t\t\t\tEnter new Phone: ";
                getline(cin, line);
                updatedDetails.push_back("Phone: " + line);
                updatedDetails.push_back("\n");

                // Write the updated details back to the file with the same format
                for (const string& detail : updatedDetails) {
                    detailsFileOut << detail << "\n";
                }

                // Add an empty line after each patient's details
                detailsFileOut << "\n";

                // Skip the remaining lines for this patient in the input file
                while (getline(detailsFile, line) && !line.empty()) {}
            } else {
                // Keep the details for other patients unchanged
                detailsFileOut << line << "\n";
            }
        }
    }

    // Close file streams
    detailsFile.close();
    detailsFileOut.close();

    if (!patientFound) {
        cerr << "\n\t\t\t\t\tPatient not found in the details file." << endl;
        return;
    }

    // Remove the original details file
    if (remove("patients_details.txt") != 0) {
        perror("Error removing original file");
        return;
    }

    // Rename the temporary file to the original details file
    if (rename("tempDetailsFile.txt", "patients_details.txt") != 0) {
        perror("Error renaming file");
        return;
    }

    cout << "\n\t\t\t\t\tPersonal Information updated successfully.\n";
}

void displayAppointments(const string& patientLoginUsername)
{
    ifstream acceptedFileIn("accepted_file.txt", ios::in);

    if (!acceptedFileIn.is_open())
    {
        cerr << "\n\t\t\t\t\tError opening appointments file" << endl;
        return;
    }

    bool hasAcceptedAppointments = false;

    cout << "\n\t\t\t\t\tPatient's Appointments:" << endl;
    cout << "\n________________________________________________________________________________________________________________________\n" << endl;


    // Read and process each line in the accepted appointments file
    string line;
    string key, value;
    string storedPatientName, storedDocName, storedDate, storedTime, status;

    while (getline(acceptedFileIn, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            key = line.substr(0, colonPos);
            value = line.substr(colonPos + 2); // Skip the colon and the space
        }

        if (key == "Patient Name")
        {
            storedPatientName = value;
        }
        else if (key == "Doctor Name")
        {
            storedDocName = value;
        }
        else if (key == "Date")
        {
            storedDate = value;
        }
        else if (key == "Time")
        {
            storedTime = value;
        }
        else if (key == "Status")
        {
            status = value;

            // Check if the appointment is for the logged-in patient and has the status "Accepted"
            if (storedPatientName == patientLoginUsername && status == "Accepted")
            {
                hasAcceptedAppointments = true;
                cout << "\n\t\t\t\t\tPatient UserName: " << storedPatientName << endl;
                cout << "\n\t\t\t\t\tDoctor Name: " << storedDocName << endl;
                cout << "\n\t\t\t\t\tDate: " << storedDate << endl;
                cout << "\n\t\t\t\t\tTime: " << storedTime << endl;
            }
        }
    }

    if (!hasAcceptedAppointments)
    {
        cout << "\n\t\t\t\t\tNo accepted appointments found for " << patientLoginUsername << "." << endl;
    }

    acceptedFileIn.close();
}
