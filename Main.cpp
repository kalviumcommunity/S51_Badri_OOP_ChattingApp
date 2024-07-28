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

bool User::login(string pwd)
{
    if (this->password == pwd)
    {
        this->isLoggedIn = true;
        return true;
    }
    return false;
}

void User::logout()
{
    this->isLoggedIn = false;
}

string User::getUsername() const
{
    return this->username;
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
    return this->sender;
}

string Message::getReceiver() const
{
    return this->receiver;
}

string Message::getContent() const
{
    return this->content;
}

// ChatHistory Class
class ChatHistory
{
private:
    vector<Message> messages;

public:
    ChatHistory();
    void addMessage(const Message &message);
    vector<Message> getMessages() const;
};

// Constructor for ChatHistory
ChatHistory::ChatHistory() {}

void ChatHistory::addMessage(const Message &message)
{
    this->messages.push_back(message);
}

vector<Message> ChatHistory::getMessages() const
{
    return this->messages;
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
    bool loginUser(string uname, string pwd);
    void logoutUser();
    User *findUserByUsername(const string &uname);
    void sendMessage(const string &receiver, const string &content);
    void showChatHistory(const string &user1, const string &user2) const;
};

// Constructor for ChatApp
ChatApp::ChatApp() : currentUser(nullptr) {}

void ChatApp::registerUser(string uname, string pwd, bool isAdmin, string adminKey)
{
    if (isAdmin && adminKey == "heybadrinath")
    {
        this->users.push_back(new Admin(uname, pwd, adminKey));
    }
    else
    {
        this->users.push_back(new NormalUser(uname, pwd));
    }
}

bool ChatApp::loginUser(string uname, string pwd)
{
    User *user = this->findUserByUsername(uname);
    if (user && user->login(pwd))
    {
        this->currentUser = user;
        return true;
    }
    return false;
}

void ChatApp::logoutUser()
{
    if (this->currentUser)
    {
        this->currentUser->logout();
        this->currentUser = nullptr;
        cout << "user logged out" << endl;
    }
}

User *ChatApp::findUserByUsername(const string &uname)
{
    for (auto user : this->users)
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
    if (this->currentUser)
    {
        Message msg(this->currentUser->getUsername(), receiver, content);
        this->chatHistory.addMessage(msg);
    }
    else
    {
        cout << "No user is currently logged in!" << endl;
    }
}

void ChatApp::showChatHistory(const string &user1, const string &user2) const
{
    for (const auto &message : this->chatHistory.getMessages())
    {
        if ((message.getSender() == user1 && message.getReceiver() == user2) || (message.getReceiver() == user1 && message.getSender() == user2))
        {
            cout << message.getSender() << " to " << message.getReceiver() << ": " << message.getContent() << endl;
        }
    }
}

int main()
{
    ChatApp app;

    app.registerUser("badri", "badriPass", true, "heybadrinath");
    app.registerUser("alice", "alicePass", false);

    if (app.loginUser("badri", "badriPass"))
    {
        cout << "User 'badri' logged in successfully." << endl;
    }
    else
    {
        cout << "Failed to log in user 'badri'." << endl;
    }

    app.sendMessage("alice", "Hello, Alice!");

    app.showChatHistory("badri", "alice");

    app.logoutUser();

    if (app.loginUser("alice", "alicePass"))
    {
        cout << "User 'alice' logged in successfully." << endl;
    }
    else
    {
        cout << "Failed to log in user 'alice'." << endl;
    }

    app.showChatHistory("alice", "badri");

    app.logoutUser();

    return 0;
}
