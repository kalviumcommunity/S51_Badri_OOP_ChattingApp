#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Base User Class
class User
{
protected:
    string username;
    string password;
    bool isLoggedIn;

public:
    User(string uname, string pwd);
    bool login(string pwd);
    void logout();
    string getUsername() const;
};

// Constructor for User
User::User(string uname, string pwd) : username(uname), password(pwd), isLoggedIn(false) {}

void User::logout()
{
    isLoggedIn = false;
}

string User::getUsername() const
{
    return username;
}




// Derived NormalUser Class
class NormalUser : public User
{
public:
    NormalUser(string uname, string pwd);
};

// Constructor for NormalUser
NormalUser::NormalUser(string uname, string pwd) : User(uname, pwd) {}



// Derived Admin Class
class Admin : public User
{
private:
    string adminKey;

public:
    Admin(string uname, string pwd, string AdminKey);
};

// Constructor for Admin
Admin::Admin(string uname, string pwd, string AdminKey) : User(uname, pwd), adminKey(AdminKey) {}





// Message Class
class Message
{
private:
    string sender;
    string receiver;
    string content;

public:
    Message(string sndr, string rcvr, string cntnt);
    string getSender() const;
    string getReceiver() const;
    string getContent() const;
};

// Constructor for Message
Message::Message(string sndr, string rcvr, string cntnt) : sender(sndr), receiver(rcvr), content(cntnt) {}

string Message::getSender() const
{
    return sender;
}

string Message::getReceiver() const
{
    return receiver;
}

string Message::getContent() const
{
    return content;
}

// ChatHistory Class
class ChatHistory
{
private:
    vector<Message> messages;

public:
    ChatHistory();
    void addMessage(const Message &message);
    // void showMessages(const string &user1, const string &user2) const;
};

// Constructor for ChatHistory
ChatHistory::ChatHistory() {}

void ChatHistory::addMessage(const Message &message)
{
    messages.push_back(message);
}

//-----------------------------------------------------------------------------
// ChatApp Class
class ChatApp
{
private:
    vector<User *> users;
    User *currentUser;

public:
    ChatHistory chatHistory;
    ChatApp();
    void registerUser(string uname, string pwd, bool isAdmin, string adminKey = "");
    // bool loginUser(string uname, string pwd);
    void logoutUser();
    // User *findUserByUsername(const string &uname);
    // void sendMessage(const string &receiver, const string &content);
    // void showChatHistory(const string &user1, const string &user2) const; // Public method to access chatHistory
};

// Constructor for ChatApp
ChatApp::ChatApp() : currentUser(nullptr) {}


void ChatApp::registerUser(string uname, string pwd, bool isAdmin, string adminKey)
{
    if (adminKey == "heybadrinath")
    {
        users.push_back(new Admin(uname, pwd, adminKey));
    }
    else
    {
        users.push_back(new NormalUser(uname, pwd));
        cout << "register user" << uname << pwd << adminKey;
    }
}


void ChatApp::logoutUser()
{
    if (currentUser)
    {
        currentUser->logout();
        currentUser = nullptr;
    }
}




int main()
{
    ChatApp app;
    
    app.registerUser("badri", "badriPass",true,"heybadrinath");

    return 0;
}
