#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Resource 
{
    protected:
    int resourceId;
    string name;
    int capacity;
    string location;
    bool isBooked;

    public:
    
    //Contructor
    Resource(int id, string n, int cap, string loc)
    {
        resourceId = id;
        name = n;
        capacity = cap;
        location = loc;
        isBooked = false;
    }
    
    //Getter functions
    int getId()  
    {
    return resourceId;
    }

    string getName()  
    {
        return name;
    }

    int getCapacity()  
    {
        return capacity;
    }

    string getLocation()  
    {
        return location;
    }

    bool getIsBooked()  
    {
        return isBooked;
    }
};