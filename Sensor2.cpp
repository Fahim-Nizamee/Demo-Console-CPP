#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

struct Measurement {
    double value;
};

class DataRecorder {
    vector<Measurement> storage;

public:
    void recordData(double value) {
        Measurement measurement;
        measurement.value = value;
        storage.push_back(measurement);
    }

    const vector<Measurement>& getData() const {
        return storage;
    }
};

vector<DataRecorder> sensors(3);  // Temperature, Humidity, AirQuality

void readDataFromFile(string sensorType, string fileName) {
    double value = 0.0;
    ifstream file(fileName);

    while (file >> value) {
        if (sensorType == "Temperature") {
            sensors[0].recordData(value);
        } else if (sensorType == "Humidity") {
            sensors[1].recordData(value);
        } else if (sensorType == "AirQuality") {
            sensors[2].recordData(value);
        }
    }

    file.close();
}

void clearConsole() {
    system("cls");
}

void acquireSensorData() {
    string sensor1 = "Temperature";
    string fileName1 = "temperature.txt";
    string sensor2 = "Humidity";
    string fileName2 = "humidity.txt";
    string sensor3 = "AirQuality";
    string fileName3 = "air_quality.txt";

    readDataFromFile(sensor1, fileName1);
    readDataFromFile(sensor2, fileName2);
    readDataFromFile(sensor3, fileName3);
}

void displaySensorData(const vector<Measurement>& sensorData, string sensorType) {
    clearConsole();
    cout << "\tViewing " << sensorType << " Sensor data" << endl;

    if (sensorData.empty()) {
        cout << "\tNo " << sensorType << " data available." << endl;
    } else {
        for (const auto& data : sensorData) {
            cout << "\t" << data.value << endl;
        }
    }

    cout << "\n\tPress enter to continue...";
    getchar();
    getchar();
}

void displayAnalysisData(const vector<Measurement>& sensorData, string sensorType) {
    clearConsole();
    cout << "\tViewing " << sensorType << " Analysis" << endl;

    if (sensorData.empty()) {
        cout << "\tNo " << sensorType << " data available for analysis." << endl;
    } else {
        double sum = 0.0, mean, variance = 0.0, stdev;
        double minVal = sensorData[0].value;
        double maxVal = sensorData[0].value;

        // Calculate sum, min, max
        for (const auto& data : sensorData) {
            sum += data.value;
            minVal = min(minVal, data.value);
            maxVal = max(maxVal, data.value);
        }

        // Calculate mean
        mean = sum / sensorData.size();

        // Calculate variance
        for (const auto& data : sensorData) {
            variance += pow(data.value - mean, 2);
        }
        variance /= sensorData.size();

        // Calculate standard deviation
        stdev = sqrt(variance);

        // Display results
        cout << "\tMinimum " << sensorType << ": " << minVal << endl;
        cout << "\tMaximum " << sensorType << ": " << maxVal << endl;
        cout << "\tMean " << sensorType << ": " << mean << endl;
        cout << "\tStandard Deviation " << sensorType << ": " << stdev << endl;
    }

    cout << "\n\tpress enter to continue...";
    getchar();
    getchar();
}

int main() {
    acquireSensorData();
    while (1) {
        int option;
        clearConsole();
        cout << "\tEnvironmental monitoring system" << endl;
        cout << "\t1. View Sensor Data" << endl;
        cout << "\t2. View Data Analysis" << endl;
        cout << "\t3. Quit" << endl;
        cout << endl << "\tEnter Your Option: ";
        cin >> option;

        switch (option) {
            case 1:
                while (1) {
                    int subOption;
                    clearConsole();
                    cout << "\t1. View Temperature Sensor data" << endl;
                    cout << "\t2. View Humidity Sensor data" << endl;
                    cout << "\t3. View AirQuality Sensor data" << endl;
                    cout << "\t4. Previous page" << endl;
                    cout << endl << "\tEnter Your Option: ";
                    cin >> subOption;

                    switch (subOption) {
                        case 1:
                            displaySensorData(sensors[0].getData(), "Temperature");
                            break;

                        case 2:
                            displaySensorData(sensors[1].getData(), "Humidity");
                            break;

                        case 3:
                            displaySensorData(sensors[2].getData(), "AirQuality");
                            break;

                        default:
                            break;
                    }
                    if (subOption == 4)
                        break;
                }
                break;

            case 2:
                while (1) {
                    int analysisOption;
                    clearConsole();
                    cout << "\t1. View Temperature Analysis" << endl;
                    cout << "\t2. View Humidity Analysis" << endl;
                    cout << "\t3. View AirQuality Analysis" << endl;
                    cout << "\t4. Previous page" << endl;
                    cout << endl << "\tEnter Your Option: ";
                    cin >> analysisOption;

                    switch (analysisOption) {
                        case 1:
                            displayAnalysisData(sensors[0].getData(), "Temperature");
                            break;

                        case 2:
                            displayAnalysisData(sensors[1].getData(), "Humidity");
                            break;

                        case 3:
                            displayAnalysisData(sensors[2].getData(), "AirQuality");
                            break;

                        default:
                            break;
                    }
                    if (analysisOption == 4)
                        break;
                }
                break;

            default:
                return 0;
        }
    }
}
