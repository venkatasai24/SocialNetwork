#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Define ANSI escape codes for text colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void drawHorizontalLine(int length) {
    cout << YELLOW << "\t+";
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << "+" << RESET << endl;
}

void drawVerticalLine(int length) {
    cout << YELLOW << "\t|";
    for (int i = 0; i < length; i++) {
        cout << " ";
    }
    cout << "|" << RESET << endl;
}

void Heading(string s)
{
    cout<<endl;

    drawHorizontalLine(55);
    drawVerticalLine(55);

    cout << YELLOW << "\t|" << CYAN << s << YELLOW << "|" << RESET << endl;

    drawVerticalLine(55);
    drawHorizontalLine(55);

    cout<<endl;
}


class SocialNetwork 
{
    private:

        unordered_map<string, unordered_set<string>> adj;

    public:

        void addUser(string& user) {
            if (adj.count(user)) {
                cout << endl << RED << "Sorry!! user with that name already exists in the data, please use another name" << endl;
                return;
            }
            adj[user] = unordered_set<string>();
            cout << endl << GREEN << user << " created successfully!" << endl;
        }

        void addFriend(string& user, string& friendName) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(friendName) == 0) {
                cout << endl << RED << "Sorry!! " << friendName << " not found in the data, please create an account" << endl;
                return;
            }
            adj[user].insert(friendName);
            adj[friendName].insert(user);
            cout << endl << GREEN << "Friend added successfully!" << endl;
        }

        void removeFriend(string& user, string& friendName) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(friendName) == 0) {
                cout << endl << RED << "Sorry!! " << friendName << " not found in the data, please create an account" << endl;
                return;
            }
            adj[user].erase(friendName);
            adj[friendName].erase(user);
            cout << endl << RED << "Friend removed successfully!" << endl;
        }

        void getFriends(string& user) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj[user].empty()) {
                cout << endl << MAGENTA << "Oh no! " << user << " has zero friends. Please connect with your colleagues" << endl;
                return;
            }
            cout << endl << BLUE << "Friends of " << user << ": ";
            for (auto& friendName : adj[user]) {
                cout << friendName << ", ";
            }
            cout << endl;
        }

        void getMutualFriends(string& user1, string& user2) {
            if (adj.count(user1) == 0) {
                cout << endl << RED << "Sorry!! " << user1 << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(user2) == 0) {
                cout << endl << RED << "Sorry!! " << user2 << " not found in the data, please create an account" << endl;
                return;
            }
            cout << endl << BLUE << "Mutual Friends of " << user1 << " and " << user2 << ": ";
            int cnt = 0;
            for (auto& friendName : adj[user2]) {
                if (adj[user1].count(friendName)) {
                    cnt++;
                    cout << friendName << ", ";
                }
            }
            if (cnt == 0) {
                cout << "Oops! None";
            }
            cout << endl;
        }

        void suggestFriends(string& user) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            cout << endl << YELLOW << "You can make requests to the following people: ";
            if (adj[user].empty()) {
                cout << endl << MAGENTA <<  "Oh no! " << user << " has zero friends. Please connect with your colleagues" << endl;
                return;
            }
            unordered_set<string> suggestedFriends;
            for (auto& friendName : adj[user]) {
                for (auto& suggestedFriend : adj[friendName]) {
                    if (suggestedFriend != user && adj[user].count(suggestedFriend) == 0) {
                        suggestedFriends.insert(suggestedFriend);
                    }
                }
            }
            for (auto& friendName : suggestedFriends) {
                cout << friendName << ", ";
            }
            cout << endl;
        }

        void getInfo(string& user) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            cout << endl << BLUE << user ;
            getFriends(user);
            cout << BLUE << "Friends count: " << adj[user].size() << endl;
        }

        void deleteUser(string& user) {
            if (adj.count(user) == 0) {
                cout << endl << RED << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            for (auto& friendName : adj[user]) {
                adj[friendName].erase(user);
            }
            adj.erase(user);
            cout << endl << RED << "Deleted successfully!!" << endl;
        }

        void allUsers() {
            cout << MAGENTA <<  "List of users in VS socialNetwork : ";
            if (adj.empty()) {
                cout << endl << MAGENTA <<  "Oh No!!, users are zero" << endl;
                return;
            }
            for (auto& user : adj) {
                cout << endl << MAGENTA << user.first;
            }
            cout << endl;
        }

        void saveToFile(const string& filename) {
            ofstream file(filename);
            if (file.is_open()) {
                for (auto& pair : adj) {
                    const string& username = pair.first;
                    unordered_set<string>& friends = pair.second;

                    file << username << ":";
                    auto it = friends.begin();
                    if (it != friends.end()) {
                        file << *it;
                        ++it;
                    }
                    for (; it != friends.end(); ++it) {
                        file << "," << *it;
                    }
                    file << endl;
                }
                file.close();
                cout << "VS SocialNetwork data saved to file: " << filename << endl;
            } else {
                cout << "Failed to open file for saving: " << filename << endl;
            }
        }

        void loadFromFile(const string& filename) {
            ifstream file(filename);
            if (file.is_open()) {
                adj.clear();
                string line;
                while (getline(file, line)) {
                    size_t pos = line.find(":");
                    if (pos == string::npos) {
                        cout << "Invalid line format: " << line << endl;
                        continue;
                    }

                    string username = line.substr(0, pos);
                    string friendsList = line.substr(pos + 1);

                    unordered_set<string> friends;
                    istringstream ss(friendsList);
                    string friendName;
                    while (getline(ss, friendName, ',')) {
                        friends.insert(friendName);
                    }

                    adj[username] = friends;
                }
                file.close();
                cout << "VS SocialNetwork data loaded from file: " << filename << endl;
            } else {
                cout << "Failed to open file for loading: " << filename << endl;
            }
        }

};
