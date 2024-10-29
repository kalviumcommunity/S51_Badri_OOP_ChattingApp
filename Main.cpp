#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


//For Single Responsibility Principal
class User
{
protected:
    string username;
    string password;
    bool isLoggedIn;

public:
    static int userCount;
    User();
    User(string uname, string pwd);
    virtual ~User();

    virtual bool login(string pwd) = 0; 
    virtual void logout() = 0;         
    string getUsername() const;
    bool isLoggedInStatus() const;
    static int getUserCount();
};

int User::userCount = 0;

User::User() : username(""), password(""), isLoggedIn(false)
{
    userCount++;
}

User::User(string uname, string pwd) : username(uname), password(pwd), isLoggedIn(false)
{
    userCount++;
}

User::~User() {}

string User::getUsername() const
{
    return this->username;
}

bool User::isLoggedInStatus() const
{
    return isLoggedIn;
}

int User::getUserCount()
{
    return userCount;
}

class NormalUser : public User
{
public:
    NormalUser();
    NormalUser(string uname, string pwd);
    ~NormalUser() {}

    bool login(string pwd) override; 
    void logout() override;          
};

NormalUser::NormalUser() : User() {}

NormalUser::NormalUser(string uname, string pwd) : User(uname, pwd) {}

bool NormalUser::login(string pwd)
{
    if (this->password == pwd)
    {
        this->isLoggedIn = true;
        return true;
    }
    return false;
}

void NormalUser::logout()
{
    this->isLoggedIn = false;
}

class Admin : public User
{
private:
    string adminKey;

public:
    Admin();
    Admin(string uname, string pwd, string AdminKey);
    ~Admin() {}

    bool login(string pwd) override;  
    void logout() override;             
    void viewAllUsers(const vector<User *> &users) const;
    void deleteUser(vector<User *> &users, const string &username);
};

Admin::Admin() : User(), adminKey("") {}

Admin::Admin(string uname, string pwd, string AdminKey) : User(uname, pwd), adminKey(AdminKey) {}

bool Admin::login(string pwd)
{
    if (this->password == pwd && !adminKey.empty())
    {
        this->isLoggedIn = true;
        return true;
    }
    return false;
}

void Admin::logout()
{
    this->isLoggedIn = false;
}

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
            delete user;
            userCount--;
            return true;
        }
        return false; });
    users.erase(it, users.end());
}

class PremiumUser : public NormalUser
{
private:
    int subscriptionLevel;

public:
    PremiumUser();
    PremiumUser(string uname, string pwd, int subLevel);
    ~PremiumUser() {}

    void setSubscriptionLevel(int level);
    int getSubscriptionLevel() const;
    void accessPremiumContent() const;
};

PremiumUser::PremiumUser() : NormalUser(), subscriptionLevel(0) {}

PremiumUser::PremiumUser(string uname, string pwd, int subLevel)
    : NormalUser(uname, pwd), subscriptionLevel(subLevel) {}

void PremiumUser::setSubscriptionLevel(int level)
{
    this->subscriptionLevel = level;
}

int PremiumUser::getSubscriptionLevel() const
{
    return this->subscriptionLevel;
}

void PremiumUser::accessPremiumContent() const
{
    if (subscriptionLevel > 0)
    {
        cout << getUsername() << " is accessing premium content with subscription level " << subscriptionLevel << endl;
    }
    else
    {
        cout << getUsername() << " does not have a valid subscription." << endl;
    }
}

class Message
{
private:
    string sender;
    string receiver;
    string content;

public:
    static int totalMessages;
    Message();
    Message(string sndr, string rcvr, string cntnt);
    string getSender() const;
    string getReceiver() const;
    string getContent() const;
    static int getTotalMessages();
};

int Message::totalMessages = 0;

Message::Message() : sender(""), receiver(""), content("") {}

Message::Message(string sndr, string rcvr, string cntnt) : sender(sndr), receiver(rcvr), content(cntnt)
{
    totalMessages++;
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

int Message::getTotalMessages()
{
    return totalMessages;
}

class ChatHistory
{
private:
    vector<Message> messages;

public:
    ChatHistory();
    void addMessage(const Message &message);
    vector<Message> getMessages() const;
};

ChatHistory::ChatHistory() {}

void ChatHistory::addMessage(const Message &message)
{
    this->messages.push_back(message);
}

vector<Message> ChatHistory::getMessages() const
{
    return this->messages;
}

class ChatApp
{
private:
    vector<User *> users;
    User *currentUser;

public:
    ChatHistory chatHistory;
    ChatApp();
    ~ChatApp();
    void registerUser(User *user);
    bool loginUser(string uname, string pwd);
    void logoutUser();
    User *findUserByUsername(const string &uname);
    void sendMessage(const string &receiver, const string &content);
    void showChatHistory(const string &user1, const string &user2) const;
    void printUsers() const;
    void deleteUser(const string &uname);
    void viewAllUsers() const;
};

ChatApp::ChatApp() : currentUser(nullptr) {}

ChatApp::~ChatApp()
{
    for (User *user : users)
    {
        delete user;
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
}

int main()
{
    ChatApp chatApp;

    NormalUser *user1 = new NormalUser("user1", "password1");
    Admin *admin1 = new Admin("admin1", "adminpass", "adminkey123");
    PremiumUser *premiumUser1 = new PremiumUser("premiumUser1", "premiumPassword", 2);

    chatApp.registerUser(user1);
    chatApp.registerUser(admin1);
    chatApp.registerUser(premiumUser1);

    if (chatApp.loginUser("admin1", "adminpass"))
    {
        chatApp.viewAllUsers();
    }

    chatApp.sendMessage("user1", "Hello user1!");

    if (chatApp.loginUser("user1", "password1"))
    {
        chatApp.sendMessage("admin1", "Hello admin!");
        chatApp.logoutUser();
    }

    chatApp.showChatHistory("admin1", "user1");

    if (chatApp.loginUser("admin1", "adminpass"))
    {
        chatApp.deleteUser("user1");
        chatApp.viewAllUsers();
    }

    return 0;
}
