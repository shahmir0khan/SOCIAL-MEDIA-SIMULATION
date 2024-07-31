# Social Media Simulation in C++

## Overview

This project is a simple simulation of a social media platform using C++. It provides basic functionalities such as user management, friend connections, posting content, and exploring user recommendations based on mutual friends. The platform includes both user and admin interfaces for interacting with the system.

## Features

### User Management
- **Create Users**: Users can be created with unique IDs, names, and passwords.
- **Display All Users**: List all users registered on the platform.
- **User Login**: Users can log in using their ID and password.
- **Admin Capabilities**: Admins can manage users, including creating and deleting users.

### Friendship Management
- **Add Friends**: Users can add friends by their user ID.
- **Display Friends**: View a user's list of friends.
- **Mutual Friends**: Check and display mutual friends between two users.

### Post Management
- **Create Posts**: Users can create posts with text content.
- **View User Posts**: Display all posts made by a specific user.
- **Admin View**: Admins can view all posts across the platform.

### Recommendations
- **Explore Recommendations**: Users can explore friend and content recommendations based on mutual friends and other criteria.

## Classes

- **Node\<T\>**: Template class representing a node in a linked list.
- **List\<T\>**: Template class implementing a linked list with operations like insertion and deletion.
- **User**: Represents a user with attributes such as ID, name, password, friends, and posts.
- **Post**: Represents a post with attributes such as ID, content, and the creator.
- **SocialMedia**: The main class managing users, posts, friendships, and providing various platform functionalities.

## How to Use

### Compile and Run

1. **Compile**: Use a C++ compiler to compile the source code.
   ```bash
   g++ -o social_media main.cpp
**Main Menu**
User Login: Log in as a user by entering your user ID and password.
Admin Login: Access the admin menu with a secret code.
Exit: Exit the application.
**User Menu**
Display Friends: Show your list of friends.
Add Friend: Add a new friend by entering their user ID.
Create Post: Make a new post with text content.
View My Posts: View all your posts.
Explore Recommended Posts: Explore recommendations for new friends and content.
Logout: Logout and return to the main menu.
**Admin Menu**
Create User: Create a new user with a unique ID, name, and password.
Display All Users: List all users on the platform.
Display All Posts: List all posts made on the platform.
Delete User: Remove a user and all associated data from the platform.
Exit: Return to the main menu.
**Acknowledgments**
This project is a basic simulation and may not include all the features of a real-world social media platform. It is intended for educational purposes to demonstrate object-oriented programming concepts and data structures in C++.
