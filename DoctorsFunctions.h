#ifndef DOCTORS_FUNCTIONS_H
#define DOCTORS_FUNCTIONS_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Function prototypes for doctor functionalities
void doctorsMenu(const string& loggedInUsername);
void acceptAppointments(const string& doctorLoginUsername);
void viewSchedule(const string& doctorloggedInUsername);
void accessPatientRecords(const vector<string>& patientUsernames, const vector<string>& patientNames, vector<string>& patientReports);
vector<string> updatePatientRecords(const string& doctorLoginUsername, vector<string>& patientNames, vector<string>& patientUsernames);
void markAppointmentComplete(const string& doctorloggedInUsername);
#endif  // DOCTORS_FUNCTIONS_H
