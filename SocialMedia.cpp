#include <iostream>
using namespace std;

// Forward Declaration of classes
class User;
class Post;
template <typename T>
class Node;
template <typename T>
class List;
class SocialMedia;

// Node class
template <typename T>
class Node
{
public:
    T val;
    Node<T> *next;
    Node(T data) : val(data), next(NULL) {}
};

// List class
template <typename T>
class List
{
private:
    Node<T> *head;

public:
    List() : head(NULL) {}
    List(Node<T> *ptr) : head(ptr) {}

    void insert(Node<T> *new_node)
    {
        new_node->next = head;
        head = new_node;
    }

    void remove(T key)
    {
        if (key == head->val)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node<T> *prev = head;
        Node<T> *temp = head->next;
        while (temp && temp->val != key)
        {
            temp = temp->next;
            prev = prev->next;
        }
        if (temp)
        {
            prev->next = temp->next;
            delete temp;
        }
    }

    int size()
    {
        Node<T> *temp = head;
        int count = 0;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    bool exists(const T data)
    {
        Node<T> *temp = head;
        while (temp)
        {
            if (temp->val == data)
                return true;
            temp = temp->next;
        }
        return false;
    }

    Node<T> *get_head()
    {
        return head;
    }

    void empty()
    {
        Node<T> *temp = head;
        while (temp)
        {
            Node<T> *next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
    }

    friend ostream &operator<<(ostream &output, const List<T> &list)
    {
        Node<T> *temp = list.head;
        while (temp)
        {
            output << temp->val << " ";
            temp = temp->next;
        }
        return output;
    }

    friend ostream &operator<<(ostream &output, const List<T *> &list);

private:
    void delete_all_nodes(Node<T> *head)
    {
        if (!head)
            return;
        delete_all_nodes(head->next);
        delete head;
    }
};

template <typename T>
ostream &operator<<(ostream &output, List<T *> &list)
{
    Node<T *> *temp = list.get_head();
    while (temp)
    {
        output << *(temp->val) << " ";
        temp = temp->next;
    }
    return output;
}

// Post Class
class Post
{
private:
    static int next_id;
    int id;
    string content;
    User *created_by;

public:
    Post(string content, User *creator) : content(content), created_by(creator)
    {
        id = next_id++;
    }

    ~Post() {}

    bool operator==(const Post &p)
    {
        return this->id == p.id;
    }

    bool operator==(int id)
    {
        return this->id == id;
    }

    friend ostream &operator<<(ostream &output, const Post &p)
    {
        output << "Post ID: " << p.id << ", Content: " << p.content << endl;
        return output;
    }
};

int Post::next_id = 1; // Initialize static member

// User class
class User
{
private:
    int id;
    string name;
    string password;
    List<User *> friends;
    List<Post *> posts;

public:
    User() : id(0), name(""), password("") {}

    User(int id, string name, string pass) : id(id), name(name), password(pass) {}

    void add_friend(User &requester)
    {
        friends.insert(new Node<User *>(&requester));
    }

    void show_friends()
    {
        cout << "Showing friends of: " << this->name << endl;
        cout << friends;
    }

    void remove_friends(User &u)
    {
        friends.remove(&u);
    }

    void add_post(string content)
    {
        if (content == "")
        {
            cout << "Nothing to post" << endl;
        }
        Post *new_post = new Post(content, this);
        posts.insert(new Node<Post *>(new_post));
        cout << "You posted: " << content << endl;
    }

    void remove_post(Post &u)
    {
        posts.remove(&u);
    }
    bool check_password(const string pass) const
    {
        return pass == this->password;
    }

    friend ostream &operator<<(ostream &output, const User &u)
    {
        output << "Name: " << u.name << ", ID: " << u.id << endl;
        return output;
    }

    bool operator==(const User &u)
    {
        return this->id == u.id;
    }

    bool operator==(int id)
    {
        return this->id == id;
    }

    bool operator!=(const User &u)
    {
        return this->id != u.id;
    }

    string get_name()
    {
        return name;
    }
    int get_id()
    {
        return id;
    }
    Node<User *> *get_friends()
    {
        return friends.get_head();
    }

    Node<Post *> *get_posts()
    {
        return posts.get_head();
    }
};

// Social Media class
class SocialMedia
{
private:
    List<User *> users;
    List<Post *> posts;

public:
    SocialMedia() {}

    void create_user(int id, string name, string password)
    {
        User *u = new User(id, name, password);
        users.insert(new Node<User *>(u));
    }

    void display_all_users()
    {
        cout << users << endl;
    }

    void display_all_posts()
    {
        cout << posts << endl;
    }

    void create_friendship(int id_1, int id_2)
    {
        if (id_1 == id_2)
        {
            cout << "A user cannot add himself" << endl;
            return;
        }
        User *u1 = find_user_by_id(id_1);
        User *u2 = find_user_by_id(id_2);
        if (are_friends(u1, u2))
        {
            cout << "Users are already friends" << endl;
            return;
        }
        if ((!(u1 && u2)))
        {
            cout << "User/Users do not exist" << endl;
            return;
        }
        u1->add_friend(*u2);
        u2->add_friend(*u1);
    }

    void show_mutual_friends(int id_1, int id_2)
    {
        User *u1 = find_user_by_id(id_1);
        User *u2 = find_user_by_id(id_2);
        List<User *> mutual_friends(get_mutual_friends(u1, u2));
        cout << "Showing mutual friends between " << u1->get_name() << " and " << u2->get_name() << ": " << endl;
        cout << mutual_friends;
        cout << endl;
    }

    void analyze_friends_count()
    {
        cout << "Analyzing number of friends each user has:" << endl;
        Node<User *> *temp = users.get_head();
        while (temp)
        {
            cout << temp->val->get_name() << " has: ";
            List<User *> frnds(temp->val->get_friends());
            cout << frnds.size() << " friends" << endl;
            temp = temp->next;
        }
    }

    void identify_user_with_most_friends()
    {
        cout << "Identifying user with the highest number of friends:" << endl;
        Node<User *> *temp = users.get_head();
        User *userWithMostFriends = nullptr;
        int maxFriends = 0;

        while (temp)
        {
            List<User *> friendsList(temp->val->get_friends());
            int friendCount = friendsList.size();

            if (friendCount > maxFriends)
            {
                maxFriends = friendCount;
                userWithMostFriends = temp->val;
            }

            temp = temp->next;
        }

        if (userWithMostFriends)
        {
            cout << "User with the most friends: " << userWithMostFriends->get_name() << " with " << maxFriends << " friends." << endl;
        }
        else
        {
            cout << "No users to analyze." << endl;
        }
    }

    void create_post(int user_id, string content)
    {
        User *user = find_user_by_id(user_id);
        if (user)
        {
            user->add_post(content);
        }
        else
        {
            cout << "User not found." << endl;
        }
    }

    // Display posts of a specific user
    void display_user_posts(int user_id)
    {
        User *user = find_user_by_id(user_id);
        if (!user)
        {
            cout << "User not found." << endl;
            return;
        }

        cout << "Posts by " << user->get_name() << ":" << endl;
        Node<Post *> *temp = user->get_posts();
        while (temp)
        {
            cout << *temp->val << endl;
            temp = temp->next;
        }
    }

    User *find_user_by_id(int id)
    {
        Node<User *> *temp = users.get_head();
        while (temp)
        {
            if (*temp->val == id)
                return temp->val;
            temp = temp->next;
        }
        return NULL;
    }

    Post *find_post_by_id(int id)
    {
        Node<Post *> *temp = posts.get_head();
        while (temp)
        {
            if (*temp->val == id)
                return temp->val;
            temp = temp->next;
        }
        return nullptr;
    }

    void explore_recommendations(int user_id)
    {
        User *user = find_user_by_id(user_id);
        if (user)
        {
            cout << "Exploring recommendations for " << user->get_name() << ":" << endl;

            // Calculate the similarity score based on mutual friends
            Node<User *> *temp = users.get_head();
            while (temp)
            {
                if (temp->val != user && !are_friends(user, temp->val))
                {
                    List<User *> user_friends(user->get_friends());
                    List<User *> temp_friends(temp->val->get_friends());
                    int mutualFriendsCount = count_mutual_friends(user, temp->val);
                    double similarityScore = static_cast<double>(mutualFriendsCount) / (user_friends.size() + temp_friends.size());

                    // You can customize this threshold based on your preference
                    if (similarityScore > 0.2)
                    {
                        cout << "Recommended: " << temp->val->get_name() << " (Similarity Score: " << similarityScore << ")" << endl;

                        // Display posts by the recommended user
                        cout << "Posts by " << temp->val->get_name() << ":" << endl;
                        Node<Post *> *postTemp = temp->val->get_posts();
                        while (postTemp)
                        {
                            cout << *postTemp->val << endl;
                            postTemp = postTemp->next;
                        }
                        cout << endl;
                    }
                }
                temp = temp->next;
            }
        }
        else
        {
            cout << "User not found." << endl;
        }
    }
    int count_mutual_friends(User *u1, User *u2)
    {
        List<User *> u1_friends = u1->get_friends();
        List<User *> u2_friends = u2->get_friends();
        int mutualFriendsCount = 0;

        Node<User *> *temp = u1_friends.get_head();
        while (temp)
        {
            if (u2_friends.exists(temp->val))
            {
                mutualFriendsCount++;
            }
            temp = temp->next;
        }

        return mutualFriendsCount;
    }

    void delete_user(User *user)
    {
        users.remove(user);
        Node<User *> *temp = users.get_head();
        while (temp)
        {
            temp->val->remove_friends(*user);
            temp = temp->next;
        }
        Node<Post *> *post_temp = user->get_posts();
        while (post_temp)
        {
            posts.remove(post_temp->val);
            post_temp = post_temp->next;
        }

        delete user;

        cout << "User deleted successfully!" << endl;
    }

private:
    bool are_friends(User *u1, User *u2)
    {
        List<User *> u1_friends(u1->get_friends());
        List<User *> u2_friends(u2->get_friends());
        return u1_friends.exists(u2) && u2_friends.exists(u1);
    }

    Node<User *> *get_mutual_friends(User *u1, User *u2)
    {
        List<User *> u1_friends = (u1->get_friends());
        List<User *> u2_friends = (u2->get_friends());
        List<User *> mutual_friends;
        Node<User *> *temp = u1_friends.get_head();
        while (temp)
        {
            if (u2_friends.exists(temp->val))
                mutual_friends.insert(new Node<User *>(temp->val));
            temp = temp->next;
        }
        return mutual_friends.get_head();
    }
};

void display_user_menu(User &current_user, SocialMedia &sm);

void display_admin_menu(SocialMedia &sm);

int main()
{
    SocialMedia socialMedia;

    // Creating 10 users
    socialMedia.create_user(1, "Alice", "password1");
    socialMedia.create_user(2, "Bob", "password2");
    socialMedia.create_user(3, "Charlie", "password3");
    socialMedia.create_user(4, "David", "password4");
    socialMedia.create_user(5, "Eva", "password5");
    socialMedia.create_user(6, "Frank", "password6");
    socialMedia.create_user(7, "Grace", "password7");
    socialMedia.create_user(8, "Hank", "password8");
    socialMedia.create_user(9, "Ivy", "password9");
    socialMedia.create_user(10, "Jack", "password10");

    // Creating Friendship between users
    socialMedia.create_friendship(1, 2);
    socialMedia.create_friendship(1, 3);
    socialMedia.create_friendship(1, 4);
    socialMedia.create_friendship(2, 5);
    socialMedia.create_friendship(3, 6);
    socialMedia.create_friendship(4, 7);
    socialMedia.create_friendship(5, 8);
    socialMedia.create_friendship(6, 9);
    socialMedia.create_friendship(7, 10);
    socialMedia.create_friendship(8, 9);
    for (int i = 1; i <= 10; ++i)
    {
        User *user = socialMedia.find_user_by_id(i);
        if (user)
        {
            socialMedia.create_post(user->get_id(), "This is a post by " + user->get_name());
            socialMedia.create_post(user->get_id(), "Another post by " + user->get_name());
        }
    }
    int choice;
    do
    {
        cout << "Main Menu:" << endl;
        cout << "1. User Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int user_id;
            string password = "";
            cout << "Enter user ID: ";
            cin >> user_id;
            cout << "Enter password: ";
            cin >> password;
            User *user = socialMedia.find_user_by_id(user_id);
            if (user && user->check_password(password))
            {
                cout << "Login successful!" << endl;
                display_user_menu(*user, socialMedia);
            }
            else
            {
                cout << "Invalid user ID or password." << endl;
            }
            break;
        }
        case 911:
        {
            string secret_code;
            cout << "Enter the secret code: ";
            cin >> secret_code;
            if (secret_code == "admin_secret")
            {
                display_admin_menu(socialMedia);
            }
            else
            {
                cout << "Invalid secret code." << endl;
            }
            break;
        }

        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}

void display_user_menu(User &current_user, SocialMedia &sm)
{
    int choice;
    do
    {
        cout << endl
             << "User Menu:" << endl;
        cout << "1. Display Friends" << endl;
        cout << "2. Add Friend" << endl;
        cout << "3. Create Post" << endl;
        cout << "4. View My Posts" << endl;
        cout << "5. Explore Recommended Posts" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)

        {
        case 1:
            current_user.show_friends();
            break;
        case 2:
        {
            int friend_id;
            cout << "Enter friend's ID to add: ";
            cin >> friend_id;
            User *friend_user = sm.find_user_by_id(friend_id);
            if (friend_user && friend_user != &current_user)
            {
                current_user.add_friend(*friend_user);
                cout << "Friend added successfully!" << endl;
            }
            else
            {
                cout << "Invalid user ID." << endl;
            }
            break;
        }
        case 3:
        {
            string post_content;
            cout << "Enter post content: ";
            cin.ignore();
            getline(cin, post_content);
            sm.create_post(current_user.get_id(), post_content);
            break;
        }
        case 4:
            sm.display_user_posts(current_user.get_id());
            break;
        case 5:
            sm.explore_recommendations(current_user.get_id());
            break;
        case 0:
            cout << "Logging out...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}

void display_admin_menu(SocialMedia &sm)
{
    int choice;
    do
    {
        cout << endl
             << "Admin Menu:" << endl;
        cout << "1. Create User" << endl;
        cout << "2. Display All Users" << endl;
        cout << "3. Display All Posts" << endl;
        cout << "4. Delete User" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id;
            string name = "";
            string password = "";
            cout << "Enter user ID: ";
            cin >> id;
            if (sm.find_user_by_id(id))
            {
                cout << "User with this ID already exists" << endl;
                break;
            }
            cout << "Enter user name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter user password: ";
            getline(cin, password);
            sm.create_user(id, name, password);
            break;
        }
        case 2:
            sm.display_all_users();
            break;
        case 3:
            sm.display_all_posts();
            break;
        case 4:
        {
            int user_id;
            cout << "Enter user ID to delete: ";
            cin >> user_id;
            User *user_to_delete = sm.find_user_by_id(user_id);
            if (user_to_delete)
            {
                // Deleting user also removes friendships and posts
                sm.delete_user(user_to_delete);
                cout << "User deleted successfully!" << endl;
            }
            else
            {
                cout << "Invalid user ID." << endl;
            }
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}
