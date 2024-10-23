// UserAuthentication.h
#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <conio.h>

using namespace std;

extern vector<string> doctorUsernames;
extern vector<string> doctorPasswords;
extern vector<string> patientUsernames;
extern vector<string> patientPasswords;

// Function prototypes for user authentication system
void displayMenu();
void RegisterPatient(vector<string> &patientUsernames,vector<string> &patientNames, vector<string> &patientPasswords );
void RegisterDoctor(int userType, vector<string> &doctorUsernames,vector<string> &doctorNames, vector<string> &doctorPasswords );
string doctorlogin(vector<string> &doctorUsernames, vector<string> &doctorPasswords);
string patientlogin(vector<string>& patientUsernames, vector<string>& patientPasswords);
unsigned int Hash(const string& data);

#endif // USER_AUTHENTICATION_H
