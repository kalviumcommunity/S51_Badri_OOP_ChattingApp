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
    virtual ~User(); // Added virtual destructor
    bool login(string pwd);
    void logout();
    string getUsername() const; // Added getter for username
};

// Constructor for User
User::User(string uname, string pwd) : username(uname), password(pwd), isLoggedIn(false) {}

User::~User() {} // Definition for virtual destructor
bool User::login(string pwd)
{
    if (pwd == this->password)
    {
        this->isLoggedIn = true;
        return true;
    }
    return false;
}

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
    time_t timestamp;

public:
    Message(string sndr, string rcvr, string cntnt);
    string getSender() const;
    string getReceiver() const;
    string getContent() const;
    time_t getTimestamp() const;
};

// Constructor for Message
Message::Message(string sndr, string rcvr, string cntnt) : sender(sndr), receiver(rcvr), content(cntnt), timestamp(time(0)) {}

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

time_t Message::getTimestamp() const
{
    return timestamp;
}

// ChatHistory Class
class ChatHistory
{
private:
    vector<Message> messages;

public:
    ChatHistory();
    void addMessage(const Message &message);
    void showMessages(const string &user1, const string &user2) const;
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
    ChatHistory chatHistory; // Private member
    User *currentUser;

public:
    ChatApp();
    ~ChatApp();
    void registerUser(string uname, string pwd, bool isAdmin, string adminKey = "");
    bool loginUser(string uname, string pwd);
    void logoutUser();
    User *findUserByUsername(const string &uname);
    void sendMessage(const string &receiver, const string &content);
    void showChatHistory(const string &user1, const string &user2) const; // Public method to access chatHistory
};

// Constructor for ChatApp
ChatApp::ChatApp() : currentUser(nullptr) {}

// Destructor for ChatApp to clean up allocated memory
ChatApp::~ChatApp()
{
    for (auto user : users)
    {
        delete user;
    }
}

void ChatApp::registerUser(string uname, string pwd, bool isAdmin, string adminKey)
{
    if (isAdmin)
    {
        users.push_back(new Admin(uname, pwd, adminKey));
    }
    else
    {
        users.push_back(new NormalUser(uname, pwd));
    }
}

bool ChatApp::loginUser(string uname, string pwd)
{
    User *user = findUserByUsername(uname);
    if (user && user->login(pwd))
    {
        currentUser = user;
        return true;
    }
    return false;
}

void ChatApp::logoutUser()
{
    if (currentUser)
    {
        currentUser->logout();
        currentUser = nullptr;
    }
}

User *ChatApp::findUserByUsername(const string &uname)
{
    for (auto user : users)
    {
        if (user->getUsername() == uname)
        {
            return user;
        }
    }
    return nullptr;
}

void ChatApp::sendMessage(const string &receiver, const string &content)
{
    if (currentUser)
    {
        User *receiverUser = findUserByUsername(receiver);
        if (receiverUser)
        {
            Message message(currentUser->getUsername(), receiver, content);
            chatHistory.addMessage(message);
        }
    }
}

void ChatApp::showChatHistory(const string &user1, const string &user2) const
{
    chatHistory.showMessages(user1, user2);
}

int main()
{

    return 0;
}
