#include <iostream>
#include <string>
#include <queue>
#include <windows.h>
#include <ctime>
#include <sstream>
using namespace std;

class Sensor
{
public:
    virtual string getReading() = 0;
    void setReading(string sensorReading)
    {
        this->sensorReading = sensorReading;
    }
protected:
    string sensorReading;
};

class HumiditySensor : public Sensor
{
public:
    HumiditySensor()
    {
        int randomHumidity = rand() % (20 - 10) + 10;
        ostringstream oStr;
        oStr << randomHumidity;
        setReading(oStr.str());
    }
    string getReading()
    {
        return sensorReading+" %";
    }
};


class TempSensor : public Sensor
{
public:
    TempSensor()
    {
        int randomTemp = rand() % (20 - 10) + 10;
        ostringstream oStr;
        oStr << randomTemp;
        setReading(oStr.str());
    }
    string getReading()
    {
        return sensorReading+" degrees";
    }
};


class DataQueue
{
private:
    queue<string> dataQueue;
public:
    void writeDataToQueue(string data)
    {
        dataQueue.push(data);
        if(dataQueue.size() == 10)
        {
            outputDataQueue();
        }
    }
    void outputDataQueue()
    {
        cout<<"Queue limit reached!!!!Displaying the data!!!!"<<endl;
        while (!dataQueue.empty())
        {
            cout<<dataQueue.front()<<endl;
            dataQueue.pop();
        }
    }
};


class SensorService
{
private:
    DataQueue dataQueue;

public:
    void getSensorData(string sensorType)
    {
        time_t now = time(0);
        string sensorData;
        if(sensorType == "humidity")
        {
            HumiditySensor sensor;
            cout<<"Retrieving data from Humidity sensor"<<endl;
            sensorData = "Humidity is "+sensor.getReading()+" at "+ctime(&now);
        }
        else if(sensorType == "temperature")
        {
            TempSensor sensor;
            cout<<"Retrieving data from Temperature sensor"<<endl;
            sensorData = "Temperature is "+sensor.getReading()+" at "+ctime(&now);
        }
        if(!sensorData.empty())
        {
            dataQueue.writeDataToQueue(sensorData);

        }
    }

};




int main()
{
    SensorService service;

    while (true)
    {
        service.getSensorData("humidity");
        service.getSensorData("temperature");
        Sleep(5000);
    }

    return 0;
}
