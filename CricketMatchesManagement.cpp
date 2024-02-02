#include <iostream>
#include <fstream>
#include <vector>

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
    vector<Player> players;
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
    vector<Team> teams;
    vector<Match> matches;

public:
    bool isTeamExists(const string &teamName)
    {
        for (const Team &team : teams)
        {
            if (team.teamName == teamName)
            {
                return true;
            }
        }
        return false;
    }

    bool isPlayerExists(const string &playerName)
    {
        for (const Team &team : teams)
        {
            for (const Player &player : team.players)
            {
                if (player.playerName == playerName)
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

        cout << "\tEnter number of players in the team: ";
        int numPlayers;
        cin >> numPlayers;
        cin.ignore();

        for (int i = 0; i < numPlayers; ++i)
        {
            Player newPlayer;
            cout << "\tEnter Player Name: ";
            getline(cin, newPlayer.playerName);

            while (isPlayerExists(newPlayer.playerName))
            {
                cout << "\tPlayer with the same name already exists. Please choose a different name.\n";
                cout << "\tEnter Player Name: ";
                getline(cin, newPlayer.playerName);
            }

            cout << "\tEnter Player Role: ";
            getline(cin, newPlayer.playerRole);

            newTeam.players.push_back(newPlayer);
        }

        teams.push_back(newTeam);
        cout << "\n\tTeam added successfully!\n";
    }

    void viewAllTeams()
    {
        cout << "\n\tAll Teams:\n";
        for (const Team &team : teams)
        {
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
            cout << "\tTeam Name: " << team.teamName << "\n\tCoach: " << team.coachName << "\n\tCaptain: " << team.captainName << endl;
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

        matches.push_back(newMatch);
        cout << "\n\tMatch scheduled successfully!\n";
    }

    void viewSchedule()
    {
        cout << "\n\tMatch Schedule:\n";
        for (const Match &match : matches)
        {
            cout << "\n\t||||||||||||||||||||||||||||||||||||||\n\n";
            cout << "\t-===========================\n";
            cout << "\t" << match.team1 << " Vs " << match.team2 << endl;
            cout << "\t````````````````````````````" << endl;
            cout << "\tVenue: " << match.venue << " | Date: " << match.date << endl;
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

        for (const Team &team : teams)
        {
            file << team.teamName << endl;
            file << team.coachName << endl;
            file << team.captainName << endl;
            file << team.players.size() << endl;

            for (const Player &player : team.players)
            {
                file << player.playerName << endl;
                file << player.playerRole << endl;
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

        file << matches.size() << endl;
        for (const Match &match : matches)
        {
            file << match.team1 << endl;
            file << match.team2 << endl;
            file << match.venue << endl;
            file << match.date << endl;
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

        Team tempTeam;
        Player tempPlayer;
        int numPlayers;

        while (getline(file, tempTeam.teamName))
        {
            getline(file, tempTeam.coachName);
            getline(file, tempTeam.captainName);
            file >> numPlayers;
            file.ignore();

            tempTeam.players.clear();
            for (int i = 0; i < numPlayers; ++i)
            {
                getline(file, tempPlayer.playerName);
                getline(file, tempPlayer.playerRole);
                tempTeam.players.push_back(tempPlayer);
            }

            teams.push_back(tempTeam);
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

        Match tempMatch;
        int numMatches;

        file >> numMatches;
        file.ignore();
        matches.clear();
        for (int i = 0; i < numMatches; ++i)
        {
            getline(file, tempMatch.team1);
            getline(file, tempMatch.team2);
            getline(file, tempMatch.venue);
            getline(file, tempMatch.date);
            matches.push_back(tempMatch);
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
