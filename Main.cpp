#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Base User Class
class User
{
protected:
    string username;
    string password;
    bool isLoggedIn;

public:
    static int userCount; // Static variable to track number of users
    User(string uname, string pwd);
    virtual ~User();
    bool login(string pwd);
    void logout();
    string getUsername() const;
    bool isLoggedInStatus() const;
    static int getUserCount(); // Static member function to get user count
};

// Initialize static variable
int User::userCount = 0;

// Constructor for User
User::User(string uname, string pwd) : username(uname), password(pwd), isLoggedIn(false)
{
    userCount++; // Increment user count whenever a new user is created
}

User::~User() {}
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

bool User::isLoggedInStatus() const
{
    return isLoggedIn;
}

// Static member function to get user count
int User::getUserCount()
{
    return userCount;
}

// Derived NormalUser Class
class NormalUser : public User
{
public:
    NormalUser(string uname, string pwd);
    virtual ~NormalUser() {}
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
    virtual ~Admin() {}
    void viewAllUsers(const vector<User *> &users) const;
    void deleteUser(vector<User *> &users, const string &username); // Delete a user
};

// Constructor for Admin
Admin::Admin(string uname, string pwd, string AdminKey) : User(uname, pwd), adminKey(AdminKey) {}

void Admin::viewAllUsers(const vector<User *> &users) const
{
    for (const auto &user : users)
    {
        cout << "Username: " << user->getUsername() << ", Logged In: " << (user->isLoggedInStatus() ? "Yes" : "No") << endl;
    }
}

void Admin::deleteUser(vector<User *> &users, const string &username)
{
    auto it = remove_if(users.begin(), users.end(), [&](User *user)
                        {
                            if (user->getUsername() == username) {
                                delete user; // Free memory
                                userCount--; // Decrement user count when a user is deleted
                                return true;
                            }
                            return false;
                        });
    users.erase(it, users.end());
}

// Message Class
class Message
{
private:
    string sender;
    string receiver;
    string content;

public:
    static int totalMessages; // Static variable to track total number of messages
    Message(string sndr, string rcvr, string cntnt);
    string getSender() const;
    string getReceiver() const;
    string getContent() const;
    static int getTotalMessages(); // Static member function to get total messages count
};

// Initialize static variable
int Message::totalMessages = 0;

// Constructor for Message
Message::Message(string sndr, string rcvr, string cntnt) : sender(sndr), receiver(rcvr), content(cntnt)
{
    totalMessages++; // Increment message count whenever a new message is created
}

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

// Static member function to get total messages count
int Message::getTotalMessages()
{
    return totalMessages;
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
    ~ChatApp(); // Destructor to free memory
    void registerUser(User *user);
    bool loginUser(string uname, string pwd);
    void logoutUser();
    User *findUserByUsername(const string &uname);
    void sendMessage(const string &receiver, const string &content);
    void showChatHistory(const string &user1, const string &user2) const;
    void printUsers() const; // New method to print user details
    void deleteUser(const string &uname);
    void viewAllUsers() const;
};

// Constructor for ChatApp
ChatApp::ChatApp() : currentUser(nullptr) {}

// Destructor for ChatApp
ChatApp::~ChatApp()
{
    for (User *user : users)
    {
        delete user; // Free the memory allocated for each user
    }
}

void ChatApp::registerUser(User *user)
{
    this->users.push_back(user);
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
        cout << "User logged out" << endl;
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

void ChatApp::deleteUser(const string &uname)
{
    if (currentUser)
    {
        Admin *admin = dynamic_cast<Admin *>(currentUser);
        if (admin)
        {
            admin->deleteUser(users, uname);
            cout << "Deleted User-" << uname << endl;
        }
        else
        {
            cout << "Only admin can delete users." << endl;
        }
    }
    else
    {
        cout << "No user is logged in." << endl;
    }
}

void ChatApp::viewAllUsers() const
{
    if (currentUser)
    {
        Admin *admin = dynamic_cast<Admin *>(currentUser);
        if (admin)
        {
            admin->viewAllUsers(users);
        }
        else
        {
            cout << "Only admin can view all users." << endl;
        }
    }
    else
    {
        cout << "No user is logged in." << endl;
    }
}

void ChatApp::printUsers() const
{
    cout << "Registered Users: " << endl;
    for (const auto &user : users)
    {
        cout << "- " << user->getUsername() << endl;
    }
    cout << "Total Users: " << User::getUserCount() << endl; // Display total users using static member function
    cout << "Total Messages Sent: " << Message::getTotalMessages() << endl; // Display total messages using static member function
    cout << endl;
}

int main()
{
    ChatApp app;

    cout << "Registering users..." << endl;
    app.registerUser(new Admin("badri", "badriPass", "heybadrinath"));
    app.registerUser(new NormalUser("alice", "alicePass"));
    app.registerUser(new NormalUser("bob", "bobPass"));

    // Print users after registration
    app.printUsers();

    // Display static variables directly using static member functions
    cout << "Public Static Variables:" << endl;
    cout << "Total Users (User::getUserCount()): " << User::getUserCount() << endl;
    cout << "Total Messages (Message::getTotalMessages()): " << Message::getTotalMessages() << endl;
    cout << endl;

    cout << "Logging in user 'badri'..." << endl;
    if (app.loginUser("badri", "badriPass"))
    {
        cout << "User 'badri' logged in successfully." << endl;
    }
    else
    {
        cout << "Failed to log in user 'badri'." << endl;
    }

    app.sendMessage("alice", "Hello, Alice!");
    app.sendMessage("bob", "Hello, Bob!");

    app.showChatHistory("badri", "alice");
    app.showChatHistory("badri", "bob");

    app.deleteUser("bob");
    app.viewAllUsers();
    app.logoutUser();

    // Print users after deletion
    app.printUsers();

    // Display static variables directly after actions using static member functions
    cout << "Public Static Variables after actions:" << endl;
    cout << "Total Users (User::getUserCount()): " << User::getUserCount() << endl;
    cout << "Total Messages (Message::getTotalMessages()): " << Message::getTotalMessages() << endl;
    cout << endl;

    return 0;
}
