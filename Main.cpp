#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Base User Class
class User {
protected:
    string username;
    string password;
    bool isLoggedIn;

public:
    User(string uname, string pwd);
};

// Derived NormalUser Class
class NormalUser : public User {
public:
    NormalUser(string uname, string pwd);
};

// Derived Admin Class
class Admin : public User {
public:
    Admin(string uname, string pwd);
};

// Message Class
class Message {
private:
    string sender;
    string receiver;
    string content;
    time_t timestamp;

public:
    Message(string sndr, string rcvr, string cntnt);
};

// ChatHistory Class
class ChatHistory {
private:
    vector<Message> messages;

public:
    ChatHistory();
};

// ChatApp Class
class ChatApp {
private:
    vector<User*> users;
    ChatHistory chatHistory;
    User* currentUser;

public:
    ChatApp();
};


int main() {
    return 0;
}

