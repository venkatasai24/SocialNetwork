#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class SocialNetwork 
{
    private:

        unordered_map<string, unordered_set<string>> adj;

    public:

        void addUser(string& user) {
            if (adj.count(user)) {
                cout << "Sorry!! " << user << " with that name already exists in the data, please use another name" << endl;
                return;
            }
            adj[user] = unordered_set<string>();
            cout << user << " created successfully!" << endl;
        }

        void addFriend(string& user, string& friendName) {
            if (adj.count(user) == 0) {
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(friendName) == 0) {
                cout << "Sorry!! " << friendName << " not found in the data, please create an account" << endl;
                return;
            }
            adj[user].insert(friendName);
            adj[friendName].insert(user);
            cout << "Friend added successfully!" << endl;
        }

        void removeFriend(string& user, string& friendName) {
            if (adj.count(user) == 0) {
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(friendName) == 0) {
                cout << "Sorry!! " << friendName << " not found in the data, please create an account" << endl;
                return;
            }
            adj[user].erase(friendName);
            adj[friendName].erase(user);
            cout << "Friend removed successfully!" << endl;
        }

        void getFriends(string& user) {
            if (adj.count(user) == 0) {
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj[user].empty()) {
                cout << "Oh no! " << user << " has zero friends. Please connect with your colleagues" << endl;
                return;
            }
            cout << "Friends of " << user << ": ";
            for (auto& friendName : adj[user]) {
                cout << friendName << ", ";
            }
            cout << endl;
        }

        void getMutualFriends(string& user1, string& user2) {
            if (adj.count(user1) == 0) {
                cout << "Sorry!! " << user1 << " not found in the data, please create an account" << endl;
                return;
            }
            if (adj.count(user2) == 0) {
                cout << "Sorry!! " << user2 << " not found in the data, please create an account" << endl;
                return;
            }
            cout << "Mutual Friends of " << user1 << " and " << user2 << ": ";
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
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            cout << "You can make requests to the following people: ";
            if (adj[user].empty()) {
                cout << "Oh no! " << user << " has zero friends. Please connect with your colleagues" << endl;
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
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            cout << user << endl;
            getFriends(user);
            cout << "Friends count: " << adj[user].size() << endl;
        }

        void deleteUser(string& user) {
            if (adj.count(user) == 0) {
                cout << "Sorry!! " << user << " not found in the data, please create an account" << endl;
                return;
            }
            for (auto& friendName : adj[user]) {
                adj[friendName].erase(user);
            }
            adj.erase(user);
            cout << "Deleted successfully!!" << endl;
        }

        void allUsers() {
            cout << "List of users in VS socialNetwork : ";
            if (adj.empty()) {
                cout << "Oh No!!, users are zero" << endl;
                return;
            }
            for (auto& user : adj) {
                cout << user.first << ", ";
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

#endif 