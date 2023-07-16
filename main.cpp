#include "SocialNetwork.h"

int main() {

    SocialNetwork VS;

    cout << "--------------------Welcome to the VS SocialNetwork Platform--------------------" << endl;
    cout << "Follow the below instructions:" << endl;
    cout << "Please enter a number corresponding to your desired action" << endl;
    cout << "1: Create a user" << endl;
    cout << "2: Add a friend to a user" << endl;
    cout << "3: Get mutual friends of two users" << endl;
    cout << "4: Suggest friends to a user" << endl;
    cout << "5: Remove a friend from a user" << endl;
    cout << "6: List friends of a user" << endl;
    cout << "7: Get user info" << endl;
    cout << "8: Delete user" << endl;
    cout << "9: Get list of all users" << endl;
    cout << "0: Terminate" << endl;
    cout << "Note: All usernames are case-sensitive!" << endl;

    string user, Friend , choice;

    VS.loadFromFile("VS_SocialNetwork_data.txt");

    while (true) {

        cout << "Enter Choice: ";
        getline(cin, choice);

        if (choice == "0") break;

        if (choice == "1") {
            cout << "Enter username: ";
            getline(cin, user);
            VS.addUser(user);
        }
        else if (choice == "2") {
            cout << "Enter username: ";
            getline(cin, user);
            cout << "Enter friendname: ";
            getline(cin, Friend);
            VS.addFriend(user, Friend);
        }
        else if (choice == "3") {
            cout << "Enter username: ";
            getline(cin, user);
            cout << "Enter friendname: ";
            getline(cin, Friend);
            VS.getMutualFriends(user, Friend);
        }
        else if (choice == "4") {
            cout << "Enter username: ";
            getline(cin, user);
            VS.suggestFriends(user);
        }
        else if (choice == "5") {
            cout << "Enter username: ";
            getline(cin, user);
            cout << "Enter friendname: ";
            getline(cin, Friend);
            VS.removeFriend(user, Friend);
        }
        else if (choice == "6") {
            cout << "Enter username: ";
            getline(cin, user);
            VS.getFriends(user);
        }
        else if (choice == "7") {
            cout << "Enter username: ";
            getline(cin, user);
            VS.getInfo(user);
        }
        else if (choice == "8") {
            cout << "Enter username: ";
            getline(cin, user);
            VS.deleteUser(user);
        }
        else if (choice == "9") VS.allUsers();
        else cout << "Invalid input" << endl;

        cout << endl;

    }

    VS.saveToFile("VS_SocialNetwork_data.txt");

    cout << "--------------------Thank you!--------------------" << endl;
    
    return 0;
}
