#ifndef PATIENTS_FUNCTIONS_H
#define PATIENTS_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "UserAuthentication.h"
#include <cstdio>

using namespace std;

void patientsMenu(const string&  patientLoginUsername);
void viewMedicalRecords(const string&  patientLoginUsername);
vector<vector<string>> scheduleAppointments(const string& patientLoginUsername);
void cancelAppointments(const string& patientLoginUsername, vector<vector<string>>& patientAppointments);
void updatePersonalInformation(const string&  patientLoginUsername);
void displayAppointments(const string& patientLoginUsername, vector<vector<string>>& patientAppointments);

#endif // PATIENTS_FUNCTIONS_H
