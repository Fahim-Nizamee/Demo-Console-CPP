#include <iostream>
#include <fstream>
#include <vector>

#define NL endl

using namespace std;

//--------------------------> Class declaration <-------------------------------------
struct Appointment
{
  string patientName;
  string patientPhoneNumber;
  string doctorName;
  string appointmentDate;
  string appointmentTime;
};

class AppointmentManagement
{
private:
  vector<Appointment> appointments;

public:
  bool isAppointmentExists(const string &patientName, const string &appointmentDate, const string &appointmentTime)
  {
    for (const Appointment &appointment : appointments)
    {
      if (appointment.patientName == patientName &&
          appointment.appointmentDate == appointmentDate &&
          appointment.appointmentTime == appointmentTime)
      {
        return true;
      }
    }
    return false;
  }

  void scheduleAppointment()
  {
    Appointment newAppointment;
    cout << "\n\tEnter Patient's Name: ";
    getline(cin, newAppointment.patientName);

    cout << "\tEnter Patient's Phone Number: ";
    getline(cin, newAppointment.patientPhoneNumber);

    cout << "\tEnter Doctor's Name: ";
    getline(cin, newAppointment.doctorName);

    cout << "\tEnter Appointment Date (YYYY-MM-DD): ";
    getline(cin, newAppointment.appointmentDate);

    cout << "\tEnter Appointment Time: ";
    getline(cin, newAppointment.appointmentTime);

    if (isAppointmentExists(newAppointment.patientName, newAppointment.appointmentDate, newAppointment.appointmentTime))
    {
      cout << "\tAppointment already exists for the given details. Please choose a different time or date.\n";
      return;
    }

    appointments.push_back(newAppointment);
    cout << "\n\tAppointment scheduled successfully!\n";
  }

  void viewAllAppointments()
  {
    cout << "\n\tAll Appointments:\n";
    for (const Appointment &appointment : appointments)
    {
      cout << "\tPatient: " << appointment.patientName << " | Phone: " << appointment.patientPhoneNumber << " | Doctor: " << appointment.doctorName << " | Date: " << appointment.appointmentDate << " | Time: " << appointment.appointmentTime << NL;
    }
  }

  void cancelAppointmentByDetails()
  {
    string patientName, appointmentDate, appointmentTime;
    cout << "\n\tEnter Patient's Name: ";
    getline(cin, patientName);

    cout << "\tEnter Appointment Date (YYYY-MM-DD): ";
    getline(cin, appointmentDate);

    cout << "\tEnter Appointment Time: ";
    getline(cin, appointmentTime);

    for (auto it = appointments.begin(); it != appointments.end(); ++it)
    {
      if (it->patientName == patientName &&
          it->appointmentDate == appointmentDate &&
          it->appointmentTime == appointmentTime)
      {
        appointments.erase(it);
        cout << "\n\tAppointment for " << patientName << " on " << appointmentDate << " at " << appointmentTime << " canceled successfully!\n";
        return;
      }
    }

    cout << "\n\tNo appointment found for " << patientName << " on " << appointmentDate << " at " << appointmentTime << NL;
  }

  void editAppointmentByDetails()
  {
    string patientName, appointmentDate, appointmentTime;
    cout << "\n\tEnter Patient's Name: ";
    getline(cin, patientName);

    cout << "\tEnter Appointment Date (YYYY-MM-DD): ";
    getline(cin, appointmentDate);

    cout << "\tEnter Appointment Time: ";
    getline(cin, appointmentTime);

    for (Appointment &appointment : appointments)
    {
      if (appointment.patientName == patientName &&
          appointment.appointmentDate == appointmentDate &&
          appointment.appointmentTime == appointmentTime)
      {
        cout << "\n\tEditing appointment for " << patientName << " on " << appointmentDate << " at " << appointmentTime << ":\n";
        cout << "\tEnter New Patient's Name: ";
        getline(cin, appointment.patientName);

        cout << "\tEnter New Patient's Phone Number: ";
        getline(cin, appointment.patientPhoneNumber);

        cout << "\tEnter New Doctor's Name: ";
        getline(cin, appointment.doctorName);

        cout << "\tEnter New Appointment Date (YYYY-MM-DD): ";
        getline(cin, appointment.appointmentDate);

        cout << "\tEnter New Appointment Time: ";
        getline(cin, appointment.appointmentTime);

        cout << "\n\tAppointment for " << patientName << " on " << appointmentDate << " at " << appointmentTime << " edited successfully!\n";
        return;
      }
    }

    cout << "\n\tNo appointment found for " << patientName << " on " << appointmentDate << " at " << appointmentTime << NL;
  }

  void saveDataToFile()
  {
    ofstream file("appointmentData.txt");
    for (const Appointment &appointment : appointments)
    {
      file << appointment.patientName << NL;
      file << appointment.patientPhoneNumber << NL;
      file << appointment.doctorName << NL;
      file << appointment.appointmentDate << NL;
      file << appointment.appointmentTime << NL;
    }

    file.close();
  }

  void readDataFromFile()
  {
    ifstream file("appointmentData.txt");
    if (file.fail())
    {
      return;
    }

    Appointment tempAppointment;
    while (getline(file, tempAppointment.patientName))
    {
      getline(file, tempAppointment.patientPhoneNumber);
      getline(file, tempAppointment.doctorName);
      getline(file, tempAppointment.appointmentDate);
      getline(file, tempAppointment.appointmentTime);
      appointments.push_back(tempAppointment);
    }

    file.close();
  }

  bool isEmpty()
  {
    return appointments.empty();
  }
};

AppointmentManagement appointmentManagement;

//----------------------> User Profile & Admin interface functions <--------------------------
void receptionistAccess()
{
  int select;
  while (1)
  {
    system("cls");
    cout << "\n\t=============== Welcome to Appointment Management System ===============\n\n";
      cout << "\tPress following numbers:\n";
      cout << "\t1) Schedule new appointment\n";
      cout << "\t2) View All Appointments\n";
      cout << "\t3) Cancel Appointment by Details\n";
      cout << "\t4) Edit Appointment by Details\n";
      cout << "\t5) Exit the app\n";
      cout << "\n\tEnter your option: ";
      cin >> select;
      cin.ignore();

      switch (select)
      {
      case 1:
        appointmentManagement.scheduleAppointment();
        break;
      case 2:
        appointmentManagement.viewAllAppointments();
        break;
      case 3:
        appointmentManagement.cancelAppointmentByDetails();
        break;
      case 4:
        appointmentManagement.editAppointmentByDetails();
        break;
      case 5:
        appointmentManagement.saveDataToFile();
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
  appointmentManagement.readDataFromFile();

  // startup of the first page of the program from here.
  receptionistAccess();

  return 0;
}
// ----------------------------> End of the App <----------------------------
