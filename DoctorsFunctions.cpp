#include "DoctorsFunctions.h"
#include "PatientsFunctions.h"
#include "UserAuthentication.h"
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

void doctorsMenu(const string& doctorLoginUsername)
{
    cout << "\n________________________________________________________________________________________________________________________" << endl;
    cout << "\n\n\t\t\t\t\t\tDoctors Menu\n" << endl;
    cout << "\t\t\t\t\t1. View Schedule\n" << endl;
    cout << "\t\t\t\t\t2. Accept Appointments\n" << endl;
    cout << "\t\t\t\t\t3. View Accepted Appointments\n" << endl;
    cout << "\t\t\t\t\t4. View Pending Appointments\n" << endl;
    cout << "\t\t\t\t\t5. Update Patients Records\n" << endl;
    cout << "\t\t\t\t\t6. Access Patients Records\n" << endl;
    cout << "\t\t\t\t\t7. Mark Appointments Complete\n" << endl;
    cout << "\t\t\t\t\t8. Go Back to Main Menu" << endl;
}

void markAppointmentComplete(const string& doctorLoginUsername)
{
    // Open the accepted appointments file for reading
    ifstream acceptedFileIn("accepted_file.txt");

    if (!acceptedFileIn.is_open()) {
        cerr << "\n\t\t\t\t\tError opening accepted appointments file" << endl;
        return;
    }

    // Open the completed appointments file for appending
    ofstream completedFileOut("completed_file.txt", ios::app);

    if (!completedFileOut.is_open()) {
        cerr << "\n\t\t\t\t\tError opening completed appointments file" << endl;
        acceptedFileIn.close();
        return;
    }

    // Open a temporary file for writing
    ofstream tempFileOut("temp_accepted_file.txt");

    if (!tempFileOut.is_open()) {
        cerr << "\n\t\t\t\t\tError creating temporary file" << endl;
        acceptedFileIn.close();
        completedFileOut.close();
        return;
    }

    bool hasAppointments = false;
    string line;
    int appointmentNo = 0;
    string patientName, date, time;

    while (getline(acceptedFileIn, line))
    {
        if (line.substr(0, 15) == "Appointment No:") {
            ++appointmentNo;
            cout << "\n\t\t\t\t\tAppointment No: " << appointmentNo << "\n";
            cout << "\n\t\t\t\t\t" << line << endl;
        } else if (line.substr(0, 13) == "Patient Name:") {
            patientName = line.substr(14);
            cout << "\n\t\t\t\t\t" << line << endl; // Display patient name
        } else if (line.substr(0, 5) == "Date:") {
            date = line.substr(6);
            cout << "\n\t\t\t\t\t" << line << endl; // Display date
        } else if (line.substr(0, 5) == "Time:") {
            time = line.substr(6);
            cout << "\n\t\t\t\t\t" << line << endl; // Display time
        } else if (line.substr(0, 7) == "Status:" && line.find("Accepted") != string::npos) {
            hasAppointments = true;
            cout << "\n\t\t\t\t\t" << line << endl; // Display status

            char choice;
            cout << "\n\t\t\t\t\tDo you want to mark this appointment as complete? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                // Write the completed appointment to the completed file
                completedFileOut << "Appointment No: " << appointmentNo << "\n";
                completedFileOut << "Patient Name: " << patientName << "\n";
                completedFileOut << "Date: " << date << "\n";
                completedFileOut << "Time: " << time << "\n";
                completedFileOut << "Status: Completed" << "\n\n";

                // Print patient name, date, and time to console
                cout << "\n\t\t\t\tAppointment marked as complete for Patient: " << patientName << ", Date: " << date << ", Time: " << time << endl;
            } else {
                // Write the appointment back to the temporary file (exclude completed appointments)
                tempFileOut << line << endl; // Write appointment number or status
                getline(acceptedFileIn, line); // Skip the patient name line
                tempFileOut << line << endl; // Write patient name
                getline(acceptedFileIn, line); // Read date
                tempFileOut << line << endl; // Write date
                getline(acceptedFileIn, line); // Read time
                tempFileOut << line << endl; // Write time
                getline(acceptedFileIn, line); // Read status (Accepted)
            }
        }
    }

    // Check if there are any accepted appointments
    if (!hasAppointments) {
        cout << "\n\t\t\t\t\tNo accepted appointments available." << endl;
    }

    // Close file streams
    acceptedFileIn.close();
    completedFileOut.close();
    tempFileOut.close();

    // Remove the original accepted file
    if (remove("accepted_file.txt") != 0) {
        perror("Error removing original file");
        return;
    }

    // Rename the temporary file to the accepted file
    if (rename("temp_accepted_file.txt", "accepted_file.txt") != 0) {
        perror("Error renaming file");
        return;
    }
}

void acceptAppointments(const string& doctorLoginUsername)
{

    // Open the accepted appointments file for appending
    ofstream acceptedFileOut("accepted_file.txt", ios::app);

    if (!acceptedFileOut.is_open()) {
        cerr << "\n\t\t\t\t\tError opening accepted appointments file" << endl;
        return;
    }

    // Open the pending appointments file for reading
    ifstream PendingFileIn("pending_file.txt");

    if (!PendingFileIn.is_open()) {
        cerr << "\n\t\t\t\t\tError opening schedule file" << endl;
        return;
    }

    // Check if the file is empty
    PendingFileIn.seekg(0, ios::end);

    if (PendingFileIn.tellg() == 0) {
        cout << "\n\t\t\t\t\tNo pending appointments." << endl;
        PendingFileIn.close();
        acceptedFileOut.close();
        return;
    }
    PendingFileIn.seekg(0, ios::beg); // Reset file pointer if not empty

    // Open a temporary file for writing
    ofstream tempFileOut("temp_pending_file.txt");

    if (!tempFileOut.is_open()) {
        cerr << "\n\t\t\t\t\tError creating temporary file" << endl;
        PendingFileIn.close();
        acceptedFileOut.close();
        return;
    }

    cout << "\n\t\t\t\t\tPending Appointments:" << endl;
    string line;
    int appointmentNo = 0;
    while (getline(PendingFileIn, line)) {
        if (line.substr(0, 15) == "Appointment No:") {
            ++appointmentNo;
            cout << "\n\t\t\t\t\t" << line << endl;
            string patientName;
            while (getline(PendingFileIn, line)) {
                if (line.find("Patient Name:") != string::npos) {
                    patientName = line.substr(line.find(":") + 2); // Extract patient name
                    break;
                }
            }
            cout << "\n\t\t\t\t\tPatient: " << patientName << endl; // Display patient name
            cout << "\n\t\t\t\t\tStatus: Pending" << endl;
            string choice;
            cout << "\n\t\t\t\t\tAccept this appointment? (yes/no): ";
            cin >> choice;
            if (choice == "yes" || choice == "YES") {
                // Update appointment status to "Accepted"
                acceptedFileOut << "Appointment No: " << appointmentNo << endl;
                acceptedFileOut << "Patient: " << patientName << endl; // Write patient name to accepted file
                while (getline(PendingFileIn, line) && !line.empty()) {
                    acceptedFileOut << line << endl;
                }
                acceptedFileOut << "Status: Accepted" << endl;
                cout << "\n\t\t\t\t\tAppointment accepted successfully." << endl;
            }
            else {
                // Skip the current appointment details
                cout << "\n\t\t\t\t\tNo appointment accepted." << endl;
                while (getline(PendingFileIn, line) && !line.empty()) {}
            }
        }
        else {
            // Write non-appointment lines to the temporary file
            tempFileOut << line << endl;
        }
    }

    // Close all file streams
    PendingFileIn.close();
    tempFileOut.close();
    acceptedFileOut.close();

    // Remove the original pending file
    if (remove("pending_file.txt") != 0) {
        perror("Error removing original file");
        return;
    }

    // Rename the temporary file to the pending file
    if (rename("temp_pending_file.txt", "pending_file.txt") != 0) {
        perror("Error renaming file");
        return;
    }
}

void viewAcceptedAppointments(string& doctorLoginUsername)
{
    // Open the accepted appointments file for reading
    ifstream acceptedFileIn("accepted_file.txt");

    if (!acceptedFileIn.is_open()) {
        cerr << "\n\t\t\t\t\tError opening schedule file" << endl;
        return;
    }

    bool hasAcceptedAppointments = false;
    int appointmentCount = 0;

    string line;
    string patientName, date, time;

    // Read and process each line in the schedule file
    while (getline(acceptedFileIn, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2); // Skip the colon and the space

            if (key == "Appointment No")
            {
                appointmentCount++;
                cout << "\n________________________________________________________________________________________________________________________\n" << endl;
                cout << "\n\t\t\t\t\tAppointment No: " << value << endl;
            }
            else if (key == "Doctor Username" && value == doctorLoginUsername)
            {
                hasAcceptedAppointments = true;
            }
            else if (key == "Patient")
            {
                patientName = value;
            }
            else if (key == "Date")
            {
                date = value;
            }
            else if (key == "Time")
            {
                time = value;
            }
            else if (key == "Status" && value == "Accepted")
            {
                // Display patient's name, date, and time
                cout << "\n\t\t\t\t\tPatient Name: " << patientName << endl;
                cout << "\n\t\t\t\t\tDate: " << date << endl;
                cout << "\n\t\t\t\t\tTime: " << time << endl;
            }
        }
    }

    // Check if there are any accepted appointments
    if (appointmentCount == 0 || !hasAcceptedAppointments)
    {
        cout << "\n\t\t\t\t\tNo accepted appointments found for " << doctorLoginUsername << "." << endl;
    }

    // Close file stream
    acceptedFileIn.close();

}

void viewPendingAppointments(string& doctorLoginUsername)
{
    // Open the pending appointments file for reading
    ifstream PendingFileIn("pending_file.txt");

    if (!PendingFileIn.is_open()) {
        cerr << "\n\t\t\t\t\tError opening schedule file" << endl;
        return;
    }

    // Check if the file is empty
    PendingFileIn.seekg(0, ios::end);

    if (PendingFileIn.tellg() == 0) {
        cout << "\n\t\t\t\t\tNo pending appointments." << endl;
        PendingFileIn.close();
        return;
    }
    PendingFileIn.seekg(0, ios::beg); // Reset file pointer if not empty

    string line;
    string doctorName, doctorUsername, patientName, date, time;

    // Read and process each line in the schedule file
    while (getline(PendingFileIn, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2); // Skip the colon and the space

            if (key == "Appointment No")
            {

                cout << "\n________________________________________________________________________________________________________________________\n" << endl;
                cout << "\n\t\t\t\t\tAppointment No: " << value << endl;
            }
            else if (key == "Patient Name")
            {
                patientName = value;
            }
            else if (key == "Doctor Username" && value == doctorLoginUsername)
            {
                doctorUsername = value;
            }
            else if (key == "Doctor Name")
            {
                doctorName = value;
            }
            else if (key == "Date")
            {
                date = value;
            }
            else if (key == "Time")
            {
                time = value;
            }
            else if (key == "Status" && value == "Pending")
            {
                // Display patient's name, date, and time
                cout << "\n\t\t\t\t\tPatient Name: " << patientName << endl;
                cout << "\n\t\t\t\t\tDoctor Name: " << doctorName << endl;
                cout << "\n\t\t\t\t\tDate: " << date << endl;
                cout << "\n\t\t\t\t\tTime: " << time << endl;
            }
        }
    }


    PendingFileIn.close();

}

void viewSchedule(const string& doctorLoginUsername)
{
    // Open the accepted appointments file for reading
    ifstream acceptedFileIn("accepted_file.txt");

    if (!acceptedFileIn.is_open()) {
        cerr << "\n\t\t\t\t\tError opening schedule file" << endl;
        return;
    }

    bool hasAcceptedAppointments = false;
    int appointmentCount = 0;

    string line;
    string patientName, date, time;

    // Read and process each line in the schedule file
    while (getline(acceptedFileIn, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2); // Skip the colon and the space

            if (key == "Appointment No")
            {
                appointmentCount++;
                cout << "\n________________________________________________________________________________________________________________________\n" << endl;
                cout << "\n\t\t\t\t\tAppointment No: " << value << endl;
            }
            else if (key == "Doctor Username" && value == doctorLoginUsername)
            {
                hasAcceptedAppointments = true;
            }
            else if (key == "Patient")
            {
                patientName = value;
            }
            else if (key == "Date")
            {
                date = value;
            }
            else if (key == "Time")
            {
                time = value;
            }
            else if (key == "Status" && value == "Accepted")
            {
                // Display patient's name, date, and time
                cout << "\n\t\t\t\t\tPatient Name: " << patientName << endl;
                cout << "\n\t\t\t\t\tDate: " << date << endl;
                cout << "\n\t\t\t\t\tTime: " << time << endl;
            }
        }
    }

    // Check if there are any accepted appointments
    if (appointmentCount == 0 || !hasAcceptedAppointments)
    {
        cout << "\n\t\t\t\t\tNo accepted appointments found for " << doctorLoginUsername << "." << endl;
    }

    // Close file stream
    acceptedFileIn.close();
}

vector<string> updatePatientRecords(const string& doctorLoginUsername, vector<string>& patientNames, vector<string>& patientUsernames)
{
    ofstream changepatientRecords("patients_records.txt", ios::app);
    ifstream patientsDetailsIn("patients_details.txt", ios::in);

    vector<string> patientReports; // Initialize an empty vector to store patient reports

    int selectedPatientIndex;

    if (!changepatientRecords.is_open() || !patientsDetailsIn.is_open())
    {
        cerr << "\n\t\t\t\t\tError opening patient records file" << endl;
        return patientReports;
    }

    // Clear the vectors before reading data
    patientUsernames.clear();
    patientNames.clear();

    string storedUsername;
    string storedName;
    string line;

    // Read patient details from the patients_details.txt file
    while (getline(patientsDetailsIn, line))
    {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos)
        {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2); // Skip the colon and the space

            if (key == "Username")
            {
                storedUsername = value;
                patientUsernames.push_back(storedUsername);
            } else if (key == "Full Name")
            {
                storedName = value;
                patientNames.push_back(storedName);
            }
        }
    }

    // Check if there are registered patients
    if (patientNames.empty())
    {
        cout << "\n\t\t\t\t\tNo registered patients found." << endl;
        return patientReports;
    }

    // Display the registered patients
    cout << "\n\t\t\t\t\tRegistered Patients:" << endl;
    cout << "\n________________________________________________________________________________________________________________________\n" << endl;

    for (size_t i = 0; i < patientNames.size(); ++i)
    {
        cout << "\n\t\t\t\t\t" << i + 1 << ". " << patientNames[i] << endl;
    }

    // Prompt the doctor to select a patient to update records
    cout << "\n\t\t\t\t\tEnter the number of the patient you want to update: ";
    while (!(cin >> selectedPatientIndex) || selectedPatientIndex < 1 || selectedPatientIndex > static_cast<int>(patientNames.size()))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "\n\t\t\t\t\tEnter the number of the patient you want to update: ";
    }

    selectedPatientIndex--; // Adjust index to match vector index (0-based)

    // Update patient records
    string diagnosisReport, medicationsReport, recommendationsReport;

    // Update the Diagnosis Report
    cout << "\n\t\t\t\t\tUpdate the Diagnosis Report for " << patientNames[selectedPatientIndex] << ":\n";
    cout << "________________________________________________________________________________________________________________________" << endl;
    cin.ignore();
    getline(cin, diagnosisReport);
    cout << "________________________________________________________________________________________________________________________" << endl;

    // Update the Medications Report
    cout << "\n\t\t\t\t\tUpdate the Medications Report for " << patientNames[selectedPatientIndex] << ":\n";
    cout << "________________________________________________________________________________________________________________________" << endl;
    getline(cin, medicationsReport);
    cout << "________________________________________________________________________________________________________________________" << endl;

    // Update the Recommendations Report
    cout << "\n\t\t\t\t\tUpdate the Recommendations Report for " << patientNames[selectedPatientIndex] << ":\n";
    cout << "________________________________________________________________________________________________________________________" << endl;
    getline(cin, recommendationsReport);
    cout << "________________________________________________________________________________________________________________________" << endl;

    // Construct the complete report
    string completeReport = "\nDiagnosis Report: " + diagnosisReport + "\nMedications Report: " + medicationsReport + "\nRecommendations Report: " + recommendationsReport;

    // Add the complete report to the patientReports vector
    patientReports.push_back(completeReport);

    // Write the updated patient record to the patients_records.txt file
    changepatientRecords << "Username: " << patientUsernames[selectedPatientIndex] << "\n";
    changepatientRecords << "Full Name: " << patientNames[selectedPatientIndex] << "\n";
    changepatientRecords << "Report: " << completeReport << "\n\n";

    cout << "\n\t\t\t\t\tPatient records for " << patientNames[selectedPatientIndex] << " updated successfully." << endl;

    // Close file streams
    changepatientRecords.close();
    patientsDetailsIn.close();

    return patientReports;
}

void accessPatientRecords()
{
    ifstream patientDetails("patients_credentials.txt", ios::in); // Corrected file name

    if (!patientDetails.is_open())
    {
        cerr << "\n\t\t\t\t\tError opening patient credentials file" << endl;
        return;
    }

    vector<string> patientUsernames;
    vector<string> patientNames;

    // Read patient credentials
    string line;
    while (getline(patientDetails, line))
    {
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos)
        {
            string username = line.substr(0, spacePos);
            patientUsernames.push_back(username);
        }
    }

    // Close the patient credentials file
    patientDetails.close();

    // Display registered patients
    cout << "\n\t\t\t\t\tRegistered Patients:" << endl;
    cout << "\n________________________________________________________________________________________________________________________\n" << endl;
    for (size_t i = 0; i < patientUsernames.size(); ++i)
    {
        cout << "\n\t\t\t\t\t" << i + 1 << ". " << patientUsernames[i] << endl;
    }

    // Prompt the doctor to select a patient to access records
    int selectedPatientIndex;
    cout << "\n\t\t\t\t\tEnter the number of the patient you want to access: ";

    // Check if the input is an integer
    while (!(cin >> selectedPatientIndex) || selectedPatientIndex < 1 || selectedPatientIndex > static_cast<int>(patientUsernames.size()))
    {
        cout << "\n\t\t\t\t\tInvalid input. Please enter a valid number.\n";
        cin.clear();                      // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');       // Discard invalid input
        cout << "\n\t\t\t\t\tEnter the number of the patient you want to access: ";
    }

    // Adjust index to match vector index (0-based)
    selectedPatientIndex--;

    // Open patient reports file
    ifstream patientReports("patients_records.txt", ios::in);

    if (!patientReports.is_open())
    {
        cerr << "\n\t\t\t\t\tError opening patient records file" << endl;
        return;
    }

    // Search for the selected patient's report
    string report;
    string patientUsername = patientUsernames[selectedPatientIndex];
    bool found = false;
    while (getline(patientReports, line))
    {
        if (line.find("Username: " + patientUsername) != string::npos)
        {
            found = true;
            getline(patientReports, line); // Skip the "Report: " line
            while (getline(patientReports, line) && line != "")
            {
                report += "\n\t\t\t\t\t" + line;

            }
            break;
        }
    }

    // Display patient report if found
    if (found)
    {
        cout << "\n________________________________________________________________________________________________________________________\n" << endl;
        cout << "\n\t\t\t\t\tPatient Username: " << patientUsername << "\n";
        cout << report << endl;
    }
    else
    {
        cout << "\n\t\t\t\t\tReport not found for patient with Username: " << patientUsername << endl;
    }

    // Close file streams
    patientReports.close();
}
