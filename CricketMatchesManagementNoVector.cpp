#include <iostream>
#include <fstream>

using namespace std;

struct CricketPlayer
{
    string playerName;
    string playerRole;
};

struct CricketTeam
{
    string teamName;
    string coachName;
    string captainName;
    CricketPlayer players[11]; 
    int numPlayers;
};

struct CricketMatch
{
    string team1;
    string team2;
    string venue;
    string date;
};

class CricketManagementSystem
{
private:
    CricketTeam teams[10]; 
    int numTeams;
    CricketMatch matches[10]; 
    int numMatches;

public:
    bool isTeamExists(const string &teamName)
    {
        for (int i = 0; i < numTeams; ++i)
        {
            if (teams[i].teamName == teamName)
            {
                return true;
            }
        }
        return false;
    }

    bool isPlayerExists(const string &playerName)
    {
        for (int i = 0; i < numTeams; ++i)
        {
            for (int j = 0; j < teams[i].numPlayers; ++j)
            {
                if (teams[i].players[j].playerName == playerName)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void addTeam()
    {
        CricketTeam newTeam;
        cout << "\n\tEnter Team Name: ";
        getline(cin, newTeam.teamName);

        while (isTeamExists(newTeam.teamName))
        {
            cout << "\tTeam with the same name already exists. Please choose a different name.\n";
            cout << "\tEnter Team Name: ";
            getline(cin, newTeam.teamName);
        }

        cout << "\tEnter Coach Name: ";
        getline(cin, newTeam.coachName);
        cout << "\tEnter Captain Name: ";
        getline(cin, newTeam.captainName);

        cout << "\tEnter number of players in the team (max 11): ";
        cin >> newTeam.numPlayers;
        cin.ignore();

        for (int i = 0; i < newTeam.numPlayers; ++i)
        {
            cout << "\tEnter Player Name: ";
            getline(cin, newTeam.players[i].playerName);

            while (isPlayerExists(newTeam.players[i].playerName))
            {
                cout << "\tPlayer with the same name already exists. Please choose a different name.\n";
                cout << "\tEnter Player Name: ";
                getline(cin, newTeam.players[i].playerName);
            }

            cout << "\tEnter Player Role: ";
            getline(cin, newTeam.players[i].playerRole);
        }

        teams[numTeams++] = newTeam;
        cout << "\n\tTeam added successfully!\n";
    }

    void viewAllTeams()
    {
        cout << "\n\tAll Cricket Teams:\n";
        for (int i = 0; i < numTeams; ++i)
        {
            cout << "\n\t======================================\n\n";
            cout << "\tTeam Name: " << teams[i].teamName << "\n\tCoach: " << teams[i].coachName << "\n\tCaptain: " << teams[i].captainName << endl;
            cout << "\n\tPlayers:\n";
            for (int j = 0; j < teams[i].numPlayers; ++j)
            {
                cout << "\t" << teams[i].players[j].playerRole << " :"
                     << "\t" << teams[i].players[j].playerName << endl;
            }
            cout << "\n\t======================================\n\n";
        }
    }

    void scheduleMatch()
    {
        CricketMatch newMatch;
        cout << "\n\tEnter Team 1: ";
        getline(cin, newMatch.team1);

        while (!isTeamExists(newMatch.team1))
        {
            cout << "\tTeam 1 does not exist. Please enter a valid team name.\n";
            cout << "\tEnter Team 1: ";
            getline(cin, newMatch.team1);
        }

        cout << "\tEnter Team 2: ";
        getline(cin, newMatch.team2);

        while (!isTeamExists(newMatch.team2) || newMatch.team1 == newMatch.team2)
        {
            cout << "\tTeam 2 does not exist or cannot be the same as Team 1. Please enter a valid team name.\n";
            cout << "\tEnter Team 2: ";
            getline(cin, newMatch.team2);
        }

        cout << "\tEnter Venue: ";
        getline(cin, newMatch.venue);
        cout << "\tEnter Date: ";
        getline(cin, newMatch.date);

        matches[numMatches++] = newMatch;
        cout << "\n\tCricket match scheduled successfully!\n";
    }

    void viewSchedule()
    {
        cout << "\n\tCricket Match Schedule:\n";
        for (int i = 0; i < numMatches; ++i)
        {
            cout << "\n\t======================================\n\n";
            cout << "\tTeam " << matches[i].team1 << " Vs Team " << matches[i].team2 << endl;
            cout << "\tVenue: " << matches[i].venue << " | Date: " << matches[i].date << endl;
            cout << "\n\t======================================\n\n";
        }
    }

    void saveTeamsPlayersDataToFile()
    {
        ofstream file("cricketTeamsPlayersData.txt");
        if (file.fail())
        {
            cout << "\n\tError saving cricket teams and players data to file.\n";
            return;
        }

        for (int i = 0; i < numTeams; ++i)
        {
            file << teams[i].teamName << endl;
            file << teams[i].coachName << endl;
            file << teams[i].captainName << endl;
            file << teams[i].numPlayers << endl;

            for (int j = 0; j < teams[i].numPlayers; ++j)
            {
                file << teams[i].players[j].playerName << endl;
                file << teams[i].players[j].playerRole << endl;
            }
        }

        file.close();
    }

    void saveMatchScheduleDataToFile()
    {
        ofstream file("cricketMatchScheduleData.txt");
        if (file.fail())
        {
            cout << "\n\tError saving cricket match schedule data to file.\n";
            return;
        }

        file << numMatches << endl;
        for (int i = 0; i < numMatches; ++i)
        {
            file << matches[i].team1 << endl;
            file << matches[i].team2 << endl;
            file << matches[i].venue << endl;
            file << matches[i].date << endl;
        }

        file.close();
    }

    void readTeamsPlayersDataFromFile()
    {
        ifstream file("cricketTeamsPlayersData.txt");
        if (file.fail())
        {
            return;
        }

        numTeams = 0;
        CricketPlayer tempPlayer;
        int numPlayers;

        while (getline(file, teams[numTeams].teamName))
        {
            getline(file, teams[numTeams].coachName);
            getline(file, teams[numTeams].captainName);
            file >> numPlayers;
            file.ignore();

            teams[numTeams].numPlayers = numPlayers;
            for (int i = 0; i < numPlayers; ++i)
            {
                getline(file, teams[numTeams].players[i].playerName);
                getline(file, teams[numTeams].players[i].playerRole);
            }

            numTeams++;
        }

        file.close();
    }

    void readMatchScheduleDataFromFile()
    {
        ifstream file("cricketMatchScheduleData.txt");
        if (file.fail())
        {
            return;
        }

        numMatches = 0;
        CricketMatch tempMatch;
        int tempNumMatches;

        file >> tempNumMatches;
        file.ignore();

        for (int i = 0; i < tempNumMatches; ++i)
        {
            getline(file, tempMatch.team1);
            getline(file, tempMatch.team2);
            getline(file, tempMatch.venue);
            getline(file, tempMatch.date);
            matches[numMatches++] = tempMatch;
        }

        file.close();
    }
};

CricketManagementSystem cricketSystem;

void adminAccess()
{
    int choice;
    while (1)
    {
        system("cls");
        cout << "\n\t>>>>>>>>>>>>>> Welcome to Cricket Matches Management System <<<<<<<<<<<<<<<\n\n";

        if (cricketSystem.isTeamExists(""))
        {
            cout << "\tNo cricket teams found in the database. To unlock other options, please add a team first.\n";
            cout << "\t1) Add a new cricket team\n";
            cout << "\t2) Exit the application\n";
            cout << "\n\tEnter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cricketSystem.addTeam();
                break;
            case 2:
                cricketSystem.saveTeamsPlayersDataToFile();
                cricketSystem.saveMatchScheduleDataToFile();
                return;
            default:
                cout << "\tInvalid choice. Please try again.\n";
                break;
            }
        }
        else
        {
            cout << "\t1) Add a new cricket team\n";
            cout << "\t2) View all cricket teams\n";
            cout << "\t3) Schedule a cricket match\n";
            cout << "\t4) View cricket match schedule\n";
            cout << "\t5) Exit the application\n";
            cout << "\n\tEnter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cricketSystem.addTeam();
                break;
            case 2:
                cricketSystem.viewAllTeams();
                break;
            case 3:
                cricketSystem.scheduleMatch();
                break;
            case 4:
                cricketSystem.viewSchedule();
                break;
            case 5:
                cricketSystem.saveTeamsPlayersDataToFile();
                cricketSystem.saveMatchScheduleDataToFile();
                return;
            default:
                cout << "\tInvalid choice. Please try again.\n";
                break;
            }
        }

        cout << "\n\tPress enter to continue!";
        getchar();
    }
}

int main()
{
    cricketSystem.readTeamsPlayersDataFromFile();
    cricketSystem.readMatchScheduleDataFromFile();

    adminAccess();

    return 0;
}
