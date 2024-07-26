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

// Constructor for User
User::User(string uname, string pwd) : username(uname), password(pwd), isLoggedIn(false) {}

// Derived NormalUser Class
class NormalUser : public User {
public:
    NormalUser(string uname, string pwd);
};

// Constructor for NormalUser
NormalUser::NormalUser(string uname, string pwd) : User(uname, pwd) {}

// Derived Admin Class
class Admin : public User {
private:
    string adminKey;

public:
    Admin(string uname, string pwd, string AdminKey);
};

// Constructor for Admin
Admin::Admin(string uname, string pwd, string AdminKey) : User(uname, pwd), adminKey(AdminKey) {}

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

// Constructor for Message
Message::Message(string sndr, string rcvr, string cntnt)
    : sender(sndr), receiver(rcvr), content(cntnt), timestamp(time(0)) {}

// ChatHistory Class
class ChatHistory {
private:
    vector<Message> messages;

public:
    ChatHistory();
};

// Constructor for ChatHistory
ChatHistory::ChatHistory() {}

// ChatApp Class
class ChatApp {
private:
    vector<User*> users;
    ChatHistory chatHistory;
    User* currentUser;

public:
    ChatApp();
};

// Constructor for ChatApp
ChatApp::ChatApp() : currentUser(nullptr) {}

int main() {
    return 0;
}
