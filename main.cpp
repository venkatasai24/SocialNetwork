#include "SocialNetwork.cpp"

int main() {

    SocialNetwork VS;

    Heading("\tWelcome to the VS SocialNetwork Platform\t");

    cout << YELLOW << "Follow the below instructions:" << RESET << endl << endl ;
    cout << BLUE << "Please enter a number corresponding to your desired action" << RESET << endl << endl ;
    cout << "1 : Create a user" << endl;
    cout << "2 : Add a friend to a user" << endl;
    cout << "3 : Get mutual friends of two users" << endl;
    cout << "4 : Suggest friends to a user" << endl;
    cout << "5 : Remove a friend from a user" << endl;
    cout << "6 : List friends of a user" << endl;
    cout << "7 : Get user info" << endl;
    cout << "8 : Delete user" << endl;
    cout << "9 : Get list of all users" << endl ;
    cout << RED << "0 : Terminate" << RESET << endl << endl ;
    cout << MAGENTA << "Note: All usernames are case-sensitive!" << RESET << endl << endl ;

    string user, Friend, choice;

    VS.loadFromFile("VS_SocialNetwork_data.txt");

    while (true) {

        cout << endl << GREEN << "Enter Choice: ";
        getline(cin, choice);
        cout<< RESET << endl ;

        if (choice == "0") break;

        if (choice == "1") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            VS.addUser(user);
        }
        else if (choice == "2") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            cout << GREEN << "Enter friendname: ";
            getline(cin, Friend);
            VS.addFriend(user, Friend);
        }
        else if (choice == "3") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            cout << GREEN << "Enter friendname: ";
            getline(cin, Friend);
            VS.getMutualFriends(user, Friend);
        }
        else if (choice == "4") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            VS.suggestFriends(user);
        }
        else if (choice == "5") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            cout << GREEN << "Enter friendname: ";
            getline(cin, Friend);
            VS.removeFriend(user, Friend);
        }
        else if (choice == "6") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            VS.getFriends(user);
        }
        else if (choice == "7") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            VS.getInfo(user);
        }
        else if (choice == "8") {
            cout << GREEN << "Enter username: ";
            getline(cin, user);
            VS.deleteUser(user);
        }
        else if (choice == "9") VS.allUsers();
        else cout << RED << "Invalid input" << RESET << endl;

    }

    VS.saveToFile("VS_SocialNetwork_data.txt");

    cout << endl << CYAN << "\t\t\tThank You!!\t\t\t" << RESET << endl << endl ;

    return 0;
}
