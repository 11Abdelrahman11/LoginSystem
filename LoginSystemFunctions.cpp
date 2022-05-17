#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <regex>
#include "LoginSystemFunctionsheaders.h"

using namespace std;

bool loginCheck = false;
string loginedUserName;

void displayMenu(User& u, vector<string>& data, ofstream& ofile, ifstream& ifile){
    bool loop = true;
    int choice;
    while (loop){
        cout << "Choose an operation(0) to Exit: " << endl;
        cout << "1- Registration " << endl;
        cout << "2- Login " << endl;
        if(loginCheck){
            cout << "3- Change Password " << endl;
        }
        cin >> choice;
        if (choice == 0){
            loop = false;
        }
        else if (choice == 1){
            registration(u, data, ofile);
        }
        else if (choice == 2){
           login(u, data, ifile);
        }
        else if (choice == 3){
           changePassword(u, data, loginedUserName, ofile);
        }
    }
}
bool validEmail (const User& u){
    regex validMail ("[a-zA-Z0-9]+[@][a-zA-Z]+[.][a-zA-Z]+([.][a-zA-Z])*");
    return regex_match(u.emailAddress, validMail);
}
bool validMobileNumber (const User& u){
    regex validNumber ("[0][1][0215][0-9]+");
    if (u.mobileNumber.length() != 11){
        return false;
    }
    return regex_match(u.mobileNumber, validNumber);
}
bool validFirstName (const User& u){
    regex validFirstN ("[A-Z]*[a-z-]+");
    return regex_match(u.firstName, validFirstN);
}
bool validLastName (const User& u){
    regex validLastN ("[A-Z]*[a-z-]+");
    return regex_match(u.lastName, validLastN);
}
bool validUserName(const User& u){
    regex validUN ("[a-zA-Z0-9]+");
    return regex_match(u.userName, validUN);
}
bool validPassword(const User& u){
    regex validP ("[a-zA-Z0-9!#@$_]+");
    return regex_match(u.password, validP);
}
bool powerFulPaswword(const User& u){
    regex powerFullP ("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$_])[a-zA-Z0-9!#@$_]{12,}");
    return regex_match(u.password, powerFullP);
}
bool is_Empty(ifstream& file){
    return file.peek() == ifstream::traits_type::eof();
}
void printData (vector<string>& data){
    int vSize = data.size();
    for (int i = 0 ; i < vSize; i++){
        cout << data[i] << endl;
    }
}
void loadData (ifstream& file, vector<string>& data){
    char word[101];
    file.open("Data.txt");
    while(!file.eof() && !is_Empty(file)){
            file.getline(word, 100, '\n');
            data.push_back(string(word));
            data.push_back("\n");
    }
}
void saveData (ofstream& file, vector<string>& data){
    file.open("Data.txt");
    int vSize = data.size();
    for (int i = 0 ; i < vSize; i++){
        file << data[i];
    }
    file.close();
}
bool repeatedEmailAddress(User& u, vector<string>& data){
    bool result;
    int vSize = data.size();
    for (int i = 0 ; i < vSize ; i ++){
        if (data[i] == u.emailAddress){
            result = true;
            break;
        }
        else{
            result = false;
        }
    }
    return result;
}
bool repeatedMobileNumber(User& u, vector<string>& data){
    bool result;
    int vSize = data.size();
    for (int i = 0 ; i < vSize ; i ++){
        if (data[i] == u.mobileNumber){
            result = true;
            break;
        }
        else{
            result = false;
        }
    }
    return result;
}
void registration(User& u, vector<string>& data, ofstream& file){
    string newline = "\n", space = " ";
    cout << "Enter Your First Name: ";
    cin >> u.firstName;
    while(!validFirstName(u)){
        cout << "Not Valid Name " << endl;
        cout << "Enter Your First Name Again: ";
        cin >> u.firstName;
    }
    data.push_back(u.firstName);
    data.push_back(space);
    cout << "Enter Your Last Name: ";
    cin >> u.lastName;
    while(!validLastName(u)){
        cout << "Not Valid Name " << endl;
        cout << "Enter Your Last Name Again: ";
        cin >> u.lastName;
    }
    data.push_back(u.lastName);
    data.push_back(newline);
    cout << "Enter an UserName: ";
    cin >> u.userName;
    while(!validUserName(u)){
        cout << "Not Valid UserName " << endl;
        cout << "Enter Your UserName Again: ";
        cin >> u.userName;
    }
    data.push_back(u.userName);
    data.push_back(newline);
    cout << "Enter a Password: ";
    cin >> u.password;
    while(!validPassword(u)){
        cout << "Not Valid Password " << endl;
        cout << "Enter Your Password Again: ";
        cin >> u.password;
    }
    while(!powerFulPaswword(u)){
        cout << "Not a PowerFul Password " << endl;
        cout << "(Powerful Password Is Advised Contains Large letters, Small letters)" << endl;
        cout << "('!,@,#,$,_' , Numbers and Consists of 12 letters at least)" << endl;
        cout << "Enter Your Password Again Please: ";
        cin >> u.password;
    }
    data.push_back(encrypt(u.password));
    data.push_back(newline);
    cout << "Enter Your Mobile Number: ";
    cin >> u.mobileNumber;
    while(!validMobileNumber(u)){
        cout << "Not Valid Mobile Number " << endl;
        cout << "Enter Your Mobile Number Again: ";
        cin >> u.mobileNumber;
    }
    while(repeatedMobileNumber(u, data)){
        cout << "This Mobile Number Has Used Before " << endl;
        cout << "Enter Another Mobile Number: ";
        cin >> u.mobileNumber;
    }
    data.push_back(u.mobileNumber);
    data.push_back(newline);
    cout << "Enter Your Email Address: ";
    cin >> u.emailAddress;
    while(!validEmail(u)){
        cout << "Not Valid Email Address " << endl;
        cout << "Enter Your Email Address Again: ";
        cin >> u.emailAddress;
    }
    while(repeatedEmailAddress(u, data)){
        cout << "This Email Address Has Used Before " << endl;
        cout << "Enter Another Email Address: ";
        cin >> u.emailAddress;
    }
    data.push_back(u.emailAddress);
    data.push_back(newline);
    saveData(file, data);
}
void login (User& u, vector<string>& data, ifstream& file){
    int tries = 0;
    string UserName, Password;
    while(tries < 3 && !loginCheck){
        cout << "UserName: ";
        cin >> UserName;
        cout << "Password: ";
        Password = hidePassword(Password);
        tries++;
        for(int i = 0 ; i < data.size() ; i++){
            if((data[i] == UserName) && (decrypt(data[i+2]) == Password)){
                loginedUserName = UserName;
                loginCheck = true;
            }
        }
        if(!loginCheck){
            cout << "UserName or/and Password are/is Wrong D:" << endl;
        }
    }
    if(loginCheck){
            cout << "Login Success :D " << endl;
            cout << "welcome " << loginedUserName << endl;
        }
    else{
        cout << "Login Failed Quit to the Main Menu and Try Again D:" << endl;
    }
}
void changePassword(User& u, vector<string>& data, string& Username, ofstream& file){
    string oldPassword,passwordCheck,newPassword,newPasswordCheck;
    int tries = 0;
    for (int i = 0 ; i < data.size() ; i++){
        if(data[i] == Username){
            oldPassword = decrypt(data[i+2]);
        }
    }
    while(tries < 3){
        cout << "Enter Your Last Password: ";
        passwordCheck = hidePassword(passwordCheck);
        cout << "Enter a New password: ";
        cin >> newPassword;
        cout << "Enter New Password Again: ";
        cin >> newPasswordCheck;
        for (int i = 0 ; i < data.size() ; i++){
            if(data[i] == Username){
                if(passwordCheck == oldPassword && newPassword == newPasswordCheck){
                    data[i+2] = encrypt(newPassword);
                    cout << "Password Has Changed Successfully :D" << endl;
                    tries = 3;
                }
            }
        }
        if(passwordCheck != oldPassword){
            cout << "Old Password is wrong" << endl;
        }
        else if(newPasswordCheck != newPassword){
            cout << "New Password Confirm Failed" << endl;
        }
        tries++;
    }
    saveData(file, data);
}
string encrypt(string &password){
    int key = 2,pSize;
    string encrypted;
    pSize = password.length();
    char arr [key][pSize];
    for (int k = 0; k < key; ++k){ // 2D array with number of rows == encryption key and number of columns == message size (number of characters);
        for (int s = 0; s < pSize; ++s){
            arr [k][s] = 0;
        }
    }
    for (int k = 0,s = 0,d = 1; s < pSize; k+= d,++s){ //d for direction, s for message size, k for encryption key
        arr [k][s] = password[s];
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    for (int k = 0; k < key; ++k){
        for (int s = 0; s < pSize; ++s){
            if (arr [k][s] != 0){
                encrypted += (arr [k][s]-20);
            }
        }
    }
    return encrypted;
}
string decrypt(string &password){
    int key = 2,epSize;
    string message;
    epSize = password.length();
    char arr [key][epSize];
    for (int k = 0; k < key; ++k){ // 2D array with number of rows == encryption key and number of columns == encrypted message size (number of characters);
        for (int s = 0; s < epSize; ++s){
            arr [k][s] = 0;
        }
    }
    for (int k = 0,s = 0,d = 1; s < epSize; k += d,++s){ //d for direction, s for encrypted message size, k for encryption key
        arr [k][s] = '*'; // putting '*' char in the right positions of the encryption method
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    int counter = 0;
    for (int k = 0; k < key; ++k){ //d for direction, s for encrypted message size, k for encryption key
        for (int s = 0; s < epSize; ++s){
            if (arr [k][s] == '*'){
                arr [k][s] = password[counter++];
            }
        }
    }
    for (int k = 0,s = 0,d = 1; s < epSize; k += d,++s){ //d for direction, s for message size, k for encryption key
        message += (arr [k][s]+20);
        if (k == key-1){ // changing the direction
            d = -1;
        }
        else if (k == 0) { // taking the char/s in the bottom of the rows
            d = 1;
        }
    }
    return message;
}
string hidePassword (string& password){
    string pass;
    char chr;
    while(true){
        for(int i = 0; i < 100; i++){
            chr = getch();
            if(chr == '\b' && i >= 1){
                cout << '\b';
                cout << " ";
                cout << '\b';
                i = i - 2;
                //cout << i << endl;
            }
            else if(chr != '\b' && chr != '\r'){
                cout << '*';
                pass += chr;
            }
            else if(chr == '\r'){
                break;
            }
            else{
                //cout << " else ";
                if(i == 0){
                    i = i - 1;
                }
            }
            //cout << " i = " << i;
        }
        if(chr == '\r'){
            break;
        }
    }
    cout << endl;
    password = pass;
    return password;
}
