#include <iostream>
#include <fstream>

using namespace std;

//--------------------------> Class declaration <-------------------------------------
struct Player
{
    string fullName;
    string email;
    string phoneNumber;
    string address;
    int age;
};

class TeamManagement
{
private:
    Player *players;
    int capacity;
    int size;

public:
    TeamManagement() : players(nullptr), capacity(0), size(0) {}

    ~TeamManagement()
    {
        delete[] players;
    }

    bool isPlayerExists(const string &email)
    {
        for (int i = 0; i < size; ++i)
        {
            if (players[i].email == email)
            {
                return true;
            }
        }
        return false;
    }

    void addPlayer()
    {
        Player newPlayer;

        cout << "\n\tEnter Full Name: ";
        getline(cin, newPlayer.fullName);

        string email;
        do
        {
            cout << "\tEnter Email: ";
            getline(cin, email);

            if (isPlayerExists(email))
            {
                cout << "\tPlayer with the same email already exists. Please choose a different email.\n";
            }
        } while (isPlayerExists(email));

        newPlayer.email = email;

        cout << "\tEnter Phone Number: ";
        getline(cin, newPlayer.phoneNumber);
        cout << "\tEnter Address: ";
        getline(cin, newPlayer.address);
        cout << "\tEnter Age: ";
        cin >> newPlayer.age;
        cin.ignore();

        if (size == capacity)
        {
            // Resize the array if necessary
            capacity = (capacity == 0) ? 1 : capacity * 2;
            Player *newPlayers = new Player[capacity];
            for (int i = 0; i < size; ++i)
            {
                newPlayers[i] = players[i];
            }
            delete[] players;
            players = newPlayers;
        }

        players[size++] = newPlayer;
        cout << "\n\tPlayer added successfully!\n";
    }

    void showAllPlayers()
    {
        cout << "\n\tAll Players:\n";
        for (int i = 0; i < size; ++i)
        {
            const Player &player = players[i];
            cout << "\tName: " << player.fullName << " | Email: " << player.email << " | Phone: " << player.phoneNumber << " | Address: " << player.address << " | Age: " << player.age << endl;
        }
    }

    void deletePlayerByEmail()
    {
        string email;
        cout << "\n\tEnter Email of the player to delete: ";
        getline(cin, email);

        for (int i = 0; i < size; ++i)
        {
            if (players[i].email == email)
            {
                for (int j = i; j < size - 1; ++j)
                {
                    players[j] = players[j + 1];
                }
                --size;
                cout << "\n\tPlayer with email " << email << " deleted successfully!\n";
                return;
            }
        }

        cout << "\n\tNo player found with email " << email << endl;
    }

    void editPlayerByEmail()
    {
        string email;
        cout << "\n\tEnter Email of the player to edit: ";
        getline(cin, email);

        for (int i = 0; i < size; ++i)
        {
            if (players[i].email == email)
            {
                cout << "\n\tEditing player with email " << email << ":\n";
                cout << "\tEnter New Full Name: ";
                getline(cin, players[i].fullName);
                cout << "\tEnter New Phone Number: ";
                getline(cin, players[i].phoneNumber);
                cout << "\tEnter New Address: ";
                getline(cin, players[i].address);
                cout << "\tEnter New Age: ";
                cin >> players[i].age;
                cin.ignore();

                cout << "\n\tPlayer with email " << email << " edited successfully!\n";
                return;
            }
        }

        cout << "\n\tNo player found with email " << email << endl;
    }

    void saveDataToFile()
    {
        ofstream file("teamData.txt");
        for (int i = 0; i < size; ++i)
        {
            file << players[i].fullName << endl;
            file << players[i].email << endl;
            file << players[i].phoneNumber << endl;
            file << players[i].address << endl;
            file << players[i].age << endl;
        }

        file.close();
    }

    void readDataFromFile()
    {
        ifstream file("teamData.txt");
        if (file.fail())
        {
            return;
        }

        while (true)
        {
            Player tempPlayer;
            getline(file, tempPlayer.fullName);
            if (file.eof())
            {
                break;
            }
            getline(file, tempPlayer.email);
            getline(file, tempPlayer.phoneNumber);
            getline(file, tempPlayer.address);
            file >> tempPlayer.age;
            file.ignore(); // to consume the newline after age

            if (size == capacity)
            {
                // Resize the array if necessary
                capacity = (capacity == 0) ? 1 : capacity * 2;
                Player *newPlayers = new Player[capacity];
                for (int i = 0; i < size; ++i)
                {
                    newPlayers[i] = players[i];
                }
                delete[] players;
                players = newPlayers;
            }

            players[size++] = tempPlayer;
        }

        file.close();
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

TeamManagement teamManagement;

//----------------------> User Profile & Admin interface functions <--------------------------
void coach()
{
    int select;
    while (1)
    {
        system("cls");
        cout << "\n\t==>> Player Management System <<==\n\n";
        cout << "\t1) Add new player\n";
        cout << "\t2) Show All Players\n";
        cout << "\t3) Delete Player by Email\n";
        cout << "\t4) Edit Player by Email\n";
        cout << "\t5) Exit the app\n";
        cout << "\n\tEnter your option: ";
        cin >> select;
        cin.ignore();

        switch (select)
        {
        case 1:
            teamManagement.addPlayer();
            break;
        case 2:
            teamManagement.showAllPlayers();
            break;
        case 3:
            teamManagement.deletePlayerByEmail();
            break;
        case 4:
            teamManagement.editPlayerByEmail();
            break;
        case 5:
            teamManagement.saveDataToFile();
            return;
        default:
            cout << "\tInvalid option. Please try again.\n";
            break;
        }

        cout << "\n\tPress enter to continue...";
        getchar();
    }
}

// ----------------------------> Starting of the App <---------------------------
int main()
{

    // reading data from the file
    teamManagement.readDataFromFile();

    // startup of the first page of the program from here.
    coach();

    return 0;
}
// ----------------------------> End of the App <----------------------------
