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

    //This function tells the user that the resource is already booked or not
    bool book() 
    {
        if (isBooked) 
        {
            return false;
        }
    isBooked = true;
    return true;
    }

    //This function releases the resource when the time is over.
    void release()
    {
        isBooked=false;
    }
};

int main() 
{
    Resource r(1, "Lab-1", 40, "Block A");
    cout << "Name: " << r.getName() << endl;
    cout << "Capacity: " << r.getCapacity() << endl;
    cout << "Location: " << r.getLocation() << endl;
    cout << "Booked: " << r.getIsBooked() << endl;

    //if the resource is not booked

    cout<< "Booking resource..." << endl;
    if(r.book())
    {
        cout<<"Resoursce Booked successfully!"<<endl;
    }
    else
    {
        cout<<"Resource is already booked!"<<endl;
    }

    //if the resource was booked and we are trying to book it again

    cout<< "Trying to book the same resource again..." << endl;
    if(r.book())
    {
        cout<<"Resoursce Booked successfully!"<<endl;
    }
    else
    {
        cout<<"Resource is already booked!"<<endl;
    }

    //Releasing the resource
    cout << "\nReleasing the resource..." << endl;
    r.release();
    cout << "Booked: " << r.getIsBooked() << endl;

    cout << "\nTrying to book it again after release..." << endl;
    if (r.book()) 
    {
        cout << "Booking successful!" << endl;
    }  
    else 
    {
        cout << "Booking failed - already booked." << endl;
    }
    return 0;
}