#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

struct SensorReading
{
    double measurementValue;
};

class EnvironmentalSensor
{
private:
    vector<SensorReading> readings;

public:
    void addReading(double value)
    {
        SensorReading reading;
        reading.measurementValue = value;
        readings.push_back(reading);
    }

    const vector<SensorReading> &getReadings() const
    {
        return readings;
    }

    double getMinimumValue() const
    {
        if (readings.empty())
            return 0.0;

        double minValue = readings[0].measurementValue;
        for (int i = 1; i < readings.size(); ++i)
        {
            minValue = min(minValue, readings[i].measurementValue);
        }
        return minValue;
    }

    double getMaximumValue() const
    {
        if (readings.empty())
            return 0.0;

        double maxValue = readings[0].measurementValue;
        for (int i = 1; i < readings.size(); ++i)
        {
            maxValue = max(maxValue, readings[i].measurementValue);
        }
        return maxValue;
    }

    double getMean() const
    {
        if (readings.empty())
            return 0.0;

        double sum = 0.0;
        for (int i = 0; i < readings.size(); ++i)
        {
            sum += readings[i].measurementValue;
        }
        return sum / readings.size();
    }

    double getStandardDeviation() const
    {
        if (readings.empty())
            return 0.0;

        double mean = getMean();
        double variance = 0.0;

        for (int i = 0; i < readings.size(); ++i)
        {
            variance += pow(readings[i].measurementValue - mean, 2);
        }
        variance /= readings.size();

        return sqrt(variance);
    }
};

class DataRecorder
{
private:
    vector<EnvironmentalSensor> sensors;

public:
    DataRecorder() : sensors(3) {}

    void readDataFromFile(const string &sensorType, const string &fileName)
    {
        ifstream file(fileName);
        double value;

        while (file >> value)
        {
            recordMeasurement(sensorType, value);
        }

        file.close();
    }

    void recordMeasurement(const string &sensorType, double value)
    {
        if (sensorType == "Temperature")
        {
            sensors[0].addReading(value);
        }
        else if (sensorType == "Humidity")
        {
            sensors[1].addReading(value);
        }
        else if (sensorType == "AirQuality")
        {
            sensors[2].addReading(value);
        }
    }

    const EnvironmentalSensor &getSensor(int index) const
    {
        return sensors[index];
    }
};

void clearConsoleScreen()
{
    system("cls");
}

void displaySensorReadings(const vector<SensorReading> &sensorReadings, const string &sensorType)
{
    clearConsoleScreen();
    cout << "\tDisplaying " << sensorType << " Sensor Readings" << endl;

    if (sensorReadings.empty())
    {
        cout << "\tNo " << sensorType << " readings available." << endl;
    }
    else
    {
        for (int i = 0; i < sensorReadings.size(); ++i)
        {
            cout << "\tReading " << i + 1 << ": " << sensorReadings[i].measurementValue << endl;
        }
    }

    cout << "\n\tPress enter to continue...";
    getchar();
    getchar();
}

void displayAnalysisResults(const vector<SensorReading> &sensorReadings, const string &sensorType)
{
    clearConsoleScreen();
    cout << "\tDisplaying " << sensorType << " Analysis Results" << endl;

    if (sensorReadings.empty())
    {
        cout << "\tNo " << sensorType << " readings available for analysis." << endl;
    }
    else
    {
        double sum = 0.0, mean, variance = 0.0, stdev;
        double minVal = sensorReadings[0].measurementValue;
        double maxVal = sensorReadings[0].measurementValue;

        // Calculate sum, min, max
        for (int i = 0; i < sensorReadings.size(); ++i)
        {
            sum += sensorReadings[i].measurementValue;
            minVal = min(minVal, sensorReadings[i].measurementValue);
            maxVal = max(maxVal, sensorReadings[i].measurementValue);
        }

        // Calculate mean
        mean = sum / sensorReadings.size();

        // Calculate variance
        for (int i = 0; i < sensorReadings.size(); ++i)
        {
            variance += pow(sensorReadings[i].measurementValue - mean, 2);
        }
        variance /= sensorReadings.size();

        // Calculate standard deviation
        stdev = sqrt(variance);

        // Display results
        cout << "\tMinimum Value in " << sensorType << ": " << minVal << endl;
        cout << "\tMaximum Value in " << sensorType << ": " << maxVal << endl;
        cout << "\tMean Value in " << sensorType << ": " << mean << endl;
        cout << "\tStandard Deviation in " << sensorType << ": " << stdev << endl;
    }

    cout << "\n\tPress enter to continue...";
    getchar();
    getchar();
}

int main()
{
    DataRecorder dataRecorder;
    dataRecorder.readDataFromFile("Temperature", "temperature.txt");
    dataRecorder.readDataFromFile("Humidity", "humidity.txt");
    dataRecorder.readDataFromFile("AirQuality", "air_quality.txt");

    while (1)
    {
        int option;
        clearConsoleScreen();
        cout << "\tEnvironmental Monitoring System" << endl;
        cout << "\t1. View Temperature Sensor Readings" << endl;
        cout << "\t2. View Humidity Sensor Readings" << endl;
        cout << "\t3. View AirQuality Sensor Readings" << endl;
        cout << "\t4. View Temperature Analysis Results" << endl;
        cout << "\t5. View Humidity Analysis Results" << endl;
        cout << "\t6. View AirQuality Analysis Results" << endl;
        cout << "\t7. Close" << endl;
        cout << endl
             << "\tEnter Your Choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            displaySensorReadings(dataRecorder.getSensor(0).getReadings(), "Temperature");
            break;

        case 2:
            displaySensorReadings(dataRecorder.getSensor(1).getReadings(), "Humidity");
            break;

        case 3:
            displaySensorReadings(dataRecorder.getSensor(2).getReadings(), "AirQuality");
            break;

        case 4:
            displayAnalysisResults(dataRecorder.getSensor(0).getReadings(), "Temperature");
            break;

        case 5:
            displayAnalysisResults(dataRecorder.getSensor(1).getReadings(), "Humidity");
            break;

        case 6:
            displayAnalysisResults(dataRecorder.getSensor(2).getReadings(), "AirQuality");
            break;

        case 7:
            return 0;

        default:
            cout << "\tInvalid choice. Please try again." << endl;
            break;
        }
    }
}
