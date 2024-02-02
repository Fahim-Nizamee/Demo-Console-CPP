#include <iostream>
#include <fstream>
#include <vector>

#define NL endl

using namespace std;

//--------------------------> Class declaration <-------------------------------------
struct Donor
{
  string fullName;
  string email;
  string phoneNumber;
  string bloodGroup;
};

class BloodBank
{
private:
  vector<Donor> donors;

public:
  bool isDonorExists(const string &email)
  {
    for (const Donor &donor : donors)
    {
      if (donor.email == email)
      {
        return true;
      }
    }
    return false;
  }

  void addDonor()
  {
    Donor newDonor;
    cout << "\n\tEnter Full Name: ";
    getline(cin, newDonor.fullName);

    string email;
    do
    {
      cout << "\tEnter Email: ";
      getline(cin, email);

      if (isDonorExists(email))
      {
        cout << "\tDonor with the same email already exists. Please choose a different email.\n";
      }
    } while (isDonorExists(email));

    newDonor.email = email;

    cout << "\tEnter Phone Number: ";
    getline(cin, newDonor.phoneNumber);
    cout << "\tEnter Blood Group: ";
    getline(cin, newDonor.bloodGroup);

    donors.push_back(newDonor);
    cout << "\n\tDonor added successfully!\n";
  }

  void searchByBloodGroup()
  {
    string bloodGroup;
    cout << "\n\tEnter Blood Group to search: ";
    getline(cin, bloodGroup);

    bool found = false;
    cout << "\n\tDonors with Blood Group " << bloodGroup << ":\n";
    for (const Donor &donor : donors)
    {
      if (donor.bloodGroup == bloodGroup)
      {
        cout << "\tName: " << donor.fullName << " | Email: " << donor.email << " | Phone: " << donor.phoneNumber << NL;
        found = true;
      }
    }

    if (!found)
    {
      cout << "\tNo donors found with Blood Group " << bloodGroup << NL;
    }
  }

  void showAllDonors()
  {
    cout << "\n\tAll Donors:\n";
    for (const Donor &donor : donors)
    {
      cout << "\tName: " << donor.fullName << " | Email: " << donor.email << " | Phone: " << donor.phoneNumber << " | Blood Group: " << donor.bloodGroup << NL;
    }
  }

  void deleteDonorByEmail()
  {
    string email;
    cout << "\n\tEnter Email of the donor to delete: ";
    getline(cin, email);

    for (auto it = donors.begin(); it != donors.end(); ++it)
    {
      if (it->email == email)
      {
        donors.erase(it);
        cout << "\n\tDonor with email " << email << " deleted successfully!\n";
        return;
      }
    }

    cout << "\n\tNo donor found with email " << email << NL;
  }

  void editDonorByEmail()
  {
    string email;
    cout << "\n\tEnter Email of the donor to edit: ";
    getline(cin, email);

    for (Donor &donor : donors)
    {
      if (donor.email == email)
      {
        cout << "\n\tEditing donor with email " << email << ":\n";
        cout << "\tEnter New Full Name: ";
        getline(cin, donor.fullName);
        cout << "\tEnter New Phone Number: ";
        getline(cin, donor.phoneNumber);
        cout << "\tEnter New Blood Group: ";
        getline(cin, donor.bloodGroup);

        cout << "\n\tDonor with email " << email << " edited successfully!\n";
        return;
      }
    }

    cout << "\n\tNo donor found with email " << email << NL;
  }

  void readDataFromFile()
  {
    ifstream file("bloodBankData.txt");
    if (file.fail())
    {
      return;
    }

    Donor tempDonor;
    while (getline(file, tempDonor.fullName))
    {
      getline(file, tempDonor.email);
      getline(file, tempDonor.phoneNumber);
      getline(file, tempDonor.bloodGroup);
      donors.push_back(tempDonor);
    }

    file.close();
  }

  void saveDataToFile()
  {
    ofstream file("bloodBankData.txt");
    for (const Donor &donor : donors)
    {
      file << donor.fullName << NL;
      file << donor.email << NL;
      file << donor.phoneNumber << NL;
      file << donor.bloodGroup << NL;
    }

    file.close();
  }

  bool isEmpty()
  {
    return donors.empty();
  }
};

BloodBank bloodBank;

//----------------------> User Profile & Admin interface functions <--------------------------
void adminAccess()
{
  int select;
  while (1)
  {
    system("cls");
    cout << "\n\t=============== Welcome to Blood bank management system ===============\n\n";
    cout << "\n\t>>>>>>>>>>>>>>>  Always Exit manually to save the  Data <<<<<<<<<<<<<<<\n\n";

    if (bloodBank.isEmpty())
    {
      cout << "\tNo donors found in database. To unlock other options, Please add a donor first.\n";
      cout << "\tPress following numbers:\n";
      cout << "\t1) Add new donor\n";
      cout << "\t2) Exit the app\n";
      cout << "\n\tEnter your option: ";
      cin >> select;
      cin.ignore();

      switch (select)
      {
      case 1:
        bloodBank.addDonor();
        break;
      case 2:
        bloodBank.saveDataToFile();
        return;
      default:
        cout << "\tInvalid option. Please try again.\n";
        break;
      }
    }
    else
    {
      cout << "\tPress following numbers:\n";
      cout << "\t1) Add new donor\n";
      cout << "\t2) Search by Blood Group\n";
      cout << "\t3) Show All Donors\n";
      cout << "\t4) Delete Donor by Email\n";
      cout << "\t5) Edit Donor by Email\n";
      cout << "\t6) Exit the app\n";
      cout << "\n\tEnter your option: ";
      cin >> select;
      cin.ignore();

      switch (select)
      {
      case 1:
        bloodBank.addDonor();
        break;
      case 2:
        bloodBank.searchByBloodGroup();
        break;
      case 3:
        bloodBank.showAllDonors();
        break;
      case 4:
        bloodBank.deleteDonorByEmail();
        break;
      case 5:
        bloodBank.editDonorByEmail();
        break;
      case 6:
        bloodBank.saveDataToFile();
        return;
      default:
        cout << "\tInvalid option. Please try again.\n";
        break;
      }
    }

    cout << "\n\tPress enter to continue...";
    getchar();
  }
}

// ----------------------------> Starting of the App <---------------------------
int main()
{
  system("color 0C");

  // reading data from the file
  bloodBank.readDataFromFile();

  // startup of the first page of the program from here.
  adminAccess();

  return 0;
}
// ----------------------------> End of the App <----------------------------
