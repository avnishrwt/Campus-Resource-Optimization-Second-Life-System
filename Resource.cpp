#include<iostream>
#include<vector>
#include<string>
using namespace std;


struct TimeSlot
{
    string day;
    int startHour;
    int endHour;

    //Two slots clash if same day and each starts before the other ends
    bool overlaps(TimeSlot other)
    {
        //Different days can never clash
        if (day != other.day)
        {
            return false;
        }

        //This slot finishes before (or exactly when) the other one starts
        if (endHour <= other.startHour)
        {
            return false;
        }

        //The other slot finishes before (or exactly when) this one starts
        if (other.endHour <= startHour)
        {
            return false;
        }

        //None of the safe cases matched, so the slots overlap
        return true;
    }
};


class Resource 
{
    protected:
    
    int resourceId;
    string name;
    int capacity;
    string location;
    vector<TimeSlot> bookedSlots;

    public:
    
    //Contructor
    Resource(int id, string n, int cap, string loc)
    {
        resourceId = id;
        name = n;
        capacity = cap;
        location = loc;
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

    bool isAvailable(TimeSlot s)
    {
        for (int i = 0; i < bookedSlots.size(); i++)
        {
            if (bookedSlots[i].overlaps(s))
            {
                return false;
            }
        }
        return true;
    }

    bool book(TimeSlot s)
    {
        if (!isAvailable(s))
        {
            return false;
        }
        bookedSlots.push_back(s);
        return true;
    }

    //This function displays the details of the resource.
    void displayDetails() const 
    {
        cout << "\nResource Details:\n";
        cout << "ID: " << resourceId
            << " | Name: " << name
            << " | Capacity: " << capacity
            << " | Location: " << location
            << " | Booked slots: " << bookedSlots.size()
            << endl;
    }
};

int main()
{
    Resource lab(2, "Lab-1", 40, "Block A");

    TimeSlot s1 = {"Mon", 10, 12};
    TimeSlot s2 = {"Mon", 11, 13};
    TimeSlot s3 = {"Mon", 12, 13};
    TimeSlot s4 = {"Tue", 10, 12};

    cout << "Mon 10-12 (expected BOOKED): " << (lab.book(s1) ? "BOOKED" : "CLASH") << endl;
    cout << "Mon 11-13 (expected CLASH):  " << (lab.book(s2) ? "BOOKED" : "CLASH") << endl;
    cout << "Mon 12-13 (expected BOOKED): " << (lab.book(s3) ? "BOOKED" : "CLASH") << endl;
    cout << "Tue 10-12 (expected BOOKED): " << (lab.book(s4) ? "BOOKED" : "CLASH") << endl;

    lab.displayDetails();

    return 0;
}


