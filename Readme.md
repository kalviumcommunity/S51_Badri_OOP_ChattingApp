# Simple Chatting App in C++

## Overview

This is a simple C++ console application for a chatting system. The application supports user login, sending messages, and viewing chat history. It also includes an admin user with the capability to delete users.

## Features

- User registration and login
- Sending messages to other registered users
- Viewing chat history
- Admin user functionality to delete users

## Class Structure

1. **User** (Base Class)
2. **NormalUser** (Derived Class)
3. **Admin** (Derived Class)
4. **Message**
5. **ChatHistory**
6. **ChatApp**

### User Class

- **Attributes:**
  - `username`
  - `password`
  - `isLoggedIn`
  
- **Constructor:** 
  - `User(string uname, string pwd)`

### NormalUser Class

- Inherits from `User`
- **Constructor:** 
  - `NormalUser(string uname, string pwd)`

### Admin Class

- Inherits from `User`
- **Constructor:** 
  - `Admin(string uname, string pwd)`

### Message Class

- **Attributes:**
  - `sender`
  - `receiver`
  - `content`
  - `timestamp`
  
- **Constructor:** 
  - `Message(string sndr, string rcvr, string cntnt)`

### ChatHistory Class

- **Attributes:**
  - `messages`
  
- **Constructor:** 
  - `ChatHistory()`

### ChatApp Class

- **Attributes:**
  - `users`
  - `chatHistory`
  - `currentUser`
  
- **Constructor:** 
  - `ChatApp()`
  
- **Destructor:** 
  - `~ChatApp()`

## Setup and Compilation

1. Clone the repository:
    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. Compile the code using a C++ compiler. For example, using `g++`:
    ```sh
    g++ -o chat_app main.cpp
    ```

3. Run the application:
    ```sh
    ./chat_app
    ```
