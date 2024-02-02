#include <iostream>
#include <fstream>

using namespace std;

struct Player
{
    string playerName;
    string playerRole;
};

struct Team
{
    string teamName;
    string coachName;
    string captainName;
    Player players[11]; // Assuming each team has at most 11 players
    int numPlayers;
};

struct Match
{
    string team1;
    string team2;
    string venue;
    string date;
};

class CricketManagementSystem
{
private:
    Team teams[10]; // Assuming there are at most 10 teams
    int numTeams;
    Match matches[10]; // Assuming there are at most 10 matches
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
        Team newTeam;
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
        cout << "\n\tAll Teams:\n";
        for (int i = 0; i < numTeams; ++i)
        {
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
            cout << "\tTeam Name: " << teams[i].teamName << "\n\tCoach: " << teams[i].coachName << "\n\tCaptain: " << teams[i].captainName << endl;
            cout << "\n\tPlayers:\n";
            for (int j = 0; j < teams[i].numPlayers; ++j)
            {
                cout << "\tPlayer Name: " << teams[i].players[j].playerName << "\tRole: " << teams[i].players[j].playerRole << endl;
            }
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
        }
    }

    void scheduleMatch()
    {
        Match newMatch;
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
        cout << "\n\tMatch scheduled successfully!\n";
    }

    void viewSchedule()
    {
        cout << "\n\tMatch Schedule:\n";
        for (int i = 0; i < numMatches; ++i)
        {
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
            cout << "\t-===========================\n";
            cout << "\t" << matches[i].team1 << " Vs " << matches[i].team2 << endl;
            cout << "\t````````````````````````````" << endl;
            cout << "\tVenue: " << matches[i].venue << " | Date: " << matches[i].date << endl;
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
        }
    }

    void saveTeamsPlayersDataToFile()
    {
        ofstream file("teamsPlayersData.txt");
        if (file.fail())
        {
            cout << "\n\tError saving teams and players data to file.\n";
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
        ofstream file("matchScheduleData.txt");
        if (file.fail())
        {
            cout << "\n\tError saving match schedule data to file.\n";
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
        ifstream file("teamsPlayersData.txt");
        if (file.fail())
        {
            return;
        }

        numTeams = 0;
        Player tempPlayer;
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
        ifstream file("matchScheduleData.txt");
        if (file.fail())
        {
            return;
        }

        numMatches = 0;
        Match tempMatch;
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
    int select;
    while (1)
    {
        system("cls");
        cout << "\n\t>>>>>>>>>>>>>> Welcome to Cricket Matches Management System <<<<<<<<<<<<<<<\n\n";

        if (cricketSystem.isTeamExists(""))
        {
            cout << "\tNo teams found in the database. To unlock other options, please add a team first.\n";
            cout << "\t1) Add a new team\n";
            cout << "\t2) Exit the app\n";
            cout << "\n\tEnter your option: ";
            cin >> select;
            cin.ignore();

            switch (select)
            {
            case 1:
                cricketSystem.addTeam();
                break;
            case 2:
                cricketSystem.saveTeamsPlayersDataToFile();
                cricketSystem.saveMatchScheduleDataToFile();
                return;
            default:
                cout << "\tInvalid option. Please try again.\n";
                break;
            }
        }
        else
        {
            cout << "\t1) Add a new team\n";
            cout << "\t2) View all teams\n";
            cout << "\t3) Schedule a match\n";
            cout << "\t4) View match schedule\n";
            cout << "\t5) Exit the app\n";
            cout << "\n\tEnter your option: ";
            cin >> select;
            cin.ignore();

            switch (select)
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
                cout << "\tInvalid option. Please try again.\n";
                break;
            }
        }

        cout << "\n\tPress enter to continue!";
        getchar();
    }
}

int main()
{
    system("color 0D");

    cricketSystem.readTeamsPlayersDataFromFile();
    cricketSystem.readMatchScheduleDataFromFile();

    adminAccess();

    return 0;
}
