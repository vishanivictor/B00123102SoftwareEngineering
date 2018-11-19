#include <iostream>
#include<string>

using namespace std;

int x = 0;

class Sensor
{
public:
  virtual string getReading() = 0;
  void setReading(string sensorReading) {
      this->sensorReading = sensorReading;
  }
protected:
    string sensorReading;
};

class HumiditySensor : public Sensor
{
public:
  string getReading() {
      return sensorReading+" %";
  }
};


class TempSensor : public Sensor
{
public:
  string getReading(){
      return sensorReading+" degrees";
  }
};

class Controller
{
  public:
      void getSensorData(string sensorType){

          if(sensorType == "humidity"){
            HumiditySensor sensor;
            sensor.setReading("50");
            cout<<"Humidity is "+sensor.getReading()<<endl;
          } else if(sensorType == "temperature"){
           TempSensor sensor;
           sensor.setReading("25");
            cout<<"Temperature is "+sensor.getReading()<<endl;
          }
          x++;
          if(x==10){
            pushDataToQueue();
            x = 0;
          }

      }
      void pushDataToQueue(){
          cout<<"Pushing data to queue"<<endl;
      }

};




int main()
{
    int count = 5;
    Controller controller;

    while (count > 0){
       controller.getSensorData("humidity");
       controller.getSensorData("temperature");
       count--;
    }

    return 0;
}
