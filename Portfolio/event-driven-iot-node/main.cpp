#include <iostream>
#include <windows.h>

using namespace std;

class Machine
{
    class State *current;
public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
public:
    virtual void idle(Machine *m)
    {
        cout << "Already in idle state"<<endl;
    }
    virtual void sensing(Machine *m)
    {
        cout << "Already sensing"<<endl;
    }
    virtual void processing(Machine *m)
    {
        cout << "Already processing"<<endl;
    }

};

void Machine::idle()
{
    current->idle(this);
}

void Machine::sensing()
{
    current->sensing(this);
}

void Machine::processing()
{
    current->processing(this);
}

class Idle: public State
{
public:
    Idle()
    {
        cout << "Idle-ctor "<<endl;
    };
    ~Idle()
    {
        cout << "dtor-Idle"<<endl;
    };
    void sensing(Machine *m);

};

class Sensing: public State
{
public:
    Sensing()
    {
        cout << "Sensing-ctor "<<endl;
    };
    ~Sensing()
    {
        cout << "dtor-Sensing"<<endl;
    };
    void processing(Machine *m);

};

class Processing: public State
{
public:
    Processing()
    {
        cout << "Processing-ctor "<<endl;
    };
    ~Processing()
    {
        cout << "dtor-Processing"<<endl;
    };

    void idle(Machine *m);

};

void Idle::sensing(Machine *m)
{
    cout << "***Going from Idle to Sensing***"<<endl;
    m->setCurrent(new Sensing());
    delete this;
    cout<<"Starting to read sensor values..."<<endl;
    Sleep(1000);
    cout<<"Getting the humidity reading..."<<endl;
    Sleep(1000);
    cout<<"Getting the temperature reading..."<<endl;
    Sleep(1000);
    cout<<"Reading sensor values completed!"<<endl;
    Sleep(1000);
    cout<<"Sensor values ready for processing."<<endl;
    m->processing();
}

void Sensing::processing(Machine *m)
{
    cout << "***Going from Sensing to Processing***"<<endl;
    m->setCurrent(new Processing());
    delete this;
    cout<<"Processing the sensor values..."<<endl;
    Sleep(1000);
    cout<<"Processing the humidity reading..."<<endl;
    Sleep(1000);
    cout<<"Processing the temperature reading..."<<endl;
    Sleep(1000);
    cout<<"Processing sensor values completed!"<<endl;
    Sleep(1000);
    cout<<"Releasing the resources before going to Idle state."<<endl;
    Sleep(1000);
    m->idle();
}

void Processing::idle(Machine *m)
{
    cout << "***Going from Processing to Idle***"<<endl;
    m->setCurrent(new Idle());
    delete this;
}

Machine::Machine()
{
    current = new Idle();
    cout << '\n';
}

int main()
{
    Machine fsm;
    char startSensing;
    while (1)
    {
        cout << "System is idle. Do you want to start sensing (y/n): ";
        cin >> startSensing;
        if(startSensing == 'y' || startSensing == 'Y')
        {
            fsm.sensing();
            Sleep(1000);
        }
        else if (startSensing == 'n' || startSensing == 'N')
        {
            continue;
        }
        else
        {
            cout <<"Invalid character detected"<<endl;
        }
    }
}
