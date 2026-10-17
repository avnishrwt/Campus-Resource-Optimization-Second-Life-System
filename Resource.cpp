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

        //Checks if the slot makes sense before using it
    bool isValid()
    {
        //A day must be given
        if (day == "")
        {
            return false;
        }

        //Hours must be between 0 and 24
        if (startHour < 0 || endHour > 24)
        {
            return false;
        }

        //Start must be before end (14 to 12 is not a real slot)
        if (startHour >= endHour)
        {
            return false;
        }

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
        //An invalid slot can never be available
        if (!s.isValid())
        {
            return false;
        }
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
    virtual void displayDetails() const 
    {
        cout << "\nResource Details:\n";
        cout << "ID: " << resourceId
            << " | Name: " << name
            << " | Capacity: " << capacity
            << " | Location: " << location
            << " | Booked slots: " << bookedSlots.size()
            << endl;
    }

    virtual ~Resource() {}
};

class Classroom : public Resource
{
    private:

    string department;

    public:

    //Constructor: calls the Resource constructor first, then sets its own field
    Classroom(int id, string n, int cap, string loc, string dept): Resource(id, n, cap, loc)
    {
        department = dept;
    }

    string getDepartment()
    {
        return department;
    }

    //Overrides the base version to also show the department
    void displayDetails() const override
    {
        Resource::displayDetails();
        cout << "Type: Classroom | Department: " << department << endl;
    }
};

int main()
{
    Resource lab(2, "Lab-1", 40, "Block A");

    TimeSlot s1 = {"Mon", 10, 12};   //first booking
    TimeSlot s2 = {"Mon", 11, 13};   //overlaps s1
    TimeSlot s3 = {"Mon", 12, 14};   //starts right after s1
    TimeSlot s4 = {"Tue", 10, 12};   //different day

    if (lab.book(s1))
        cout << "Mon 10-12: Booked" << endl;
    else
        cout << "Mon 10-12: Clash" << endl;

    if (lab.book(s2))
        cout << "Mon 11-13: Booked" << endl;
    else
        cout << "Mon 11-13: Clash" << endl;

    if (lab.book(s3))
        cout << "Mon 12-14: Booked" << endl;
    else
        cout << "Mon 12-14: Clash" << endl;

    if (lab.book(s4))
        cout << "Tue 10-12: Booked" << endl;
    else
        cout << "Tue 10-12: Clash" << endl;

    lab.displayDetails();

    return 0;
}


