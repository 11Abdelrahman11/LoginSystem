#ifndef LOGINSYSTEMFUNCTIONSHEADERS_H_INCLUDED
#define LOGINSYSTEMFUNCTIONSHEADERS_H_INCLUDED

using namespace std;

struct User {
    string firstName;
    string lastName;
    string userName;
    string password;
    string mobileNumber;
    string emailAddress;
};
bool validEmail (const User& u);
bool validMobileNumber (const User& u);
bool validName (const User& u);
bool validUserName (const User& u);
bool validPassword (const User& u);
bool powerFulPaswword (const User& u);
void loadData (ifstream& file, vector<string>& data);
void saveData (ofstream& file, vector<string>& data);
void registration (User& u, vector<string>& data, ofstream& file);
bool repeatedEmailAddress (User& u, vector<string>& data);
bool repeatedMobileNumber (User& u, vector<string>& data);
void displayMenu (User& u, vector<string>& data, ofstream& file, ifstream& ifile);
void login (User& u, vector<string>& data, ifstream& file);
void changePassword (User& u, vector<string>& data, string& Username, ofstream& file);
string hidePassword (string& password);
bool is_Empty(ifstream& pFile);
string encrypt(string &text);
string decrypt(string &text);

#endif // LOGINSYSTEMFUNCTIONSHEADERS_H_INCLUDED
