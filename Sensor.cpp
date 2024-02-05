#include <bits/stdc++.h>
using namespace std;
int Tindex = 0;
int Hindex = 0;
int Aindex = 0;

class SensorDataStorage
{
    double data;

public:
    void getData(double data)
    {
        this->data = data;
    }
    double viewData()
    {
        return data;
    }
};

SensorDataStorage Temperature[100];
SensorDataStorage Humidity[100];
SensorDataStorage AirQuality[100];

void read_file(string sensor, string sensorfile)
{
    double data = 0.0;
    ifstream file(sensorfile);

    while (file >> data)
    {
        if (sensor == "Temperature")
        {
            Temperature[Tindex].getData(data);
            Tindex++;
        }
        else if (sensor == "Humidity")
        {
            Humidity[Hindex].getData(data);
            Hindex++;
        }
        else if (sensor == "AirQuality")
        {
            AirQuality[Aindex].getData(data);
            Aindex++;
        }
    }

    file.close();
}

void clearScreen()
{
    system("cls");
}

void getSensorData()
{
    while (1)
    {
        int i;
        clearScreen();
        cout << "\t1. Temperature Sensor" << endl;
        cout << "\t2. Humidity Sensor" << endl;
        cout << "\t3. AirQuality Sensor" << endl;
        cout << "\t0. Back to the previous page" << endl;
        cout << endl
             << "\tEnter Your Option: ";
        cin >> i;

        string fileName = "";
        string sensor = "";

        switch (i)
        {
        case 1:
            cout << "\n\tEnter Your Data file name (.txt): ";
            cin >> fileName;
            sensor = "Temperature";
            read_file(sensor, fileName);
            cout << endl
                 << "\tReading Temperature data file..." << endl;
            cout << "\n\tpress enter to continue...";
            getchar();
            getchar();
            break;

        case 2:
            cout << "\n\tEnter Your Data file name (.txt): ";
            cin >> fileName;
            sensor = "Humidity";
            read_file(sensor, fileName);
            cout << endl
                 << "\tReading Humidity data file..." << endl;
            cout << "\n\tpress enter to continue...";
            getchar();
            getchar();
            break;

        case 3:
            cout << "\n\tEnter Your Data file name (.txt): ";
            cin >> fileName;
            sensor = "AirQuality";
            read_file(sensor, fileName);
            cout << endl
                 << "\tReading AirQuality data file..." << endl;
            cout << "\n\tpress enter to continue...";
            getchar();
            getchar();
            break;

        default:
            return;
        }
    }
}

void viewSensorData(SensorDataStorage sensorArray[], int index, string sensorName)
{
    clearScreen();
    cout << "\tViewing " << sensorName << " Sensor data" << endl;

    if (index == 0)
    {
        cout << "\tNo " << sensorName << " data available." << endl;
    }
    else
    {
        for (int l = 0; l < index; l++)
        {
            cout << "\t" << sensorArray[l].viewData() << endl;
        }
    }

    cout << "\n\tpress enter to continue...";
    getchar();
    getchar();
}

void viewAnalysisData(SensorDataStorage sensorArray[], int index, string sensorName)
{
    clearScreen();
    cout << "\tViewing " << sensorName << " Analysis" << endl;

    if (index == 0)
    {
        cout << "\tNo " << sensorName << " data available for analysis." << endl;
    }
    else
    {
        double sum = 0.0, mean, variance = 0.0, stdev;
        double minVal = sensorArray[0].viewData();
        double maxVal = sensorArray[0].viewData();

        // Calculate sum, min, max
        for (int i = 0; i < index; i++)
        {
            double value = sensorArray[i].viewData();
            sum += value;
            minVal = min(minVal, value);
            maxVal = max(maxVal, value);
        }

        // Calculate mean
        mean = sum / index;

        // Calculate variance
        for (int i = 0; i < index; i++)
        {
            double value = sensorArray[i].viewData();
            variance += pow(value - mean, 2);
        }
        variance /= index;

        // Calculate standard deviation
        stdev = sqrt(variance);

        // Display results
        cout << "\tMean " << sensorName << ": " << mean << endl;
        cout << "\tStandard Deviation " << sensorName << ": " << stdev << endl;
        cout << "\tMinimum " << sensorName << ": " << minVal << endl;
        cout << "\tMaximum " << sensorName << ": " << maxVal << endl;
    }

    cout << "\n\tpress enter to continue...";
    getchar();
    getchar();
}

int main()
{
    system("color 0B");
    while (1)
    {
        int i;
        clearScreen();
        cout << "\t===========Environmental monitoring system===========" << endl;
        cout << "\t1. Read Data File" << endl;
        cout << "\t2. View Data File" << endl;
        cout << "\t3. View Analysis" << endl;
        cout << "\t0. EXIT" << endl;
        cout << endl
             << "\tEnter Your Option: ";
        cin >> i;

        switch (i)
        {
        case 1:
            getSensorData();
            break;

        case 2:
            while (1)
            {
                int j;
                clearScreen();
                cout << "\t1. View Temperature Sensor data" << endl;
                cout << "\t2. View Humidity Sensor data" << endl;
                cout << "\t3. View AirQuality Sensor data" << endl;
                cout << "\t0. Back to the previous page" << endl;
                cout << endl
                     << "\tEnter Your Option: ";
                cin >> j;

                switch (j)
                {
                case 1:
                    viewSensorData(Temperature, Tindex, "Temperature");
                    break;

                case 2:
                    viewSensorData(Humidity, Hindex, "Humidity");
                    break;

                case 3:
                    viewSensorData(AirQuality, Aindex, "AirQuality");
                    break;

                default:
                    break;
                }
                if (j == 0)
                    break;
            }
            break;

        case 3:
            while (1)
            {
                int k;
                clearScreen();
                cout << "\t1. View Temperature Analysis" << endl;
                cout << "\t2. View Humidity Analysis" << endl;
                cout << "\t3. View AirQuality Analysis" << endl;
                cout << "\t0. Back to the previous page" << endl;
                cout << endl
                     << "\tEnter Your Option: ";
                cin >> k;

                switch (k)
                {
                case 1:
                    viewAnalysisData(Temperature, Tindex, "Temperature");
                    break;

                case 2:
                    viewAnalysisData(Humidity, Hindex, "Humidity");
                    break;

                case 3:
                    viewAnalysisData(AirQuality, Aindex, "AirQuality");
                    break;

                default:
                    break;
                }
                if (k == 0)
                    break;
            }
            break;

        case 0:
            return 0;
        }
    }
}
