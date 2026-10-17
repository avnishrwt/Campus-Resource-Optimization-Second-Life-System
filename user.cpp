
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class User
{
private:
    int userId;
    string name;
    string department;
    int year;

public:
    User(int id, string n, string dept, int y)
    {
        userId = id;
        name = n;
        department = dept;
        year = y;
    }
    int getUserId()
    {
        return userId;
    }
    string getName()
    {
        return name;
    }
    string getDepartment()
    {
        return department;
    }
    int getYear()
    {
        return year;
    }
    void display()
    {
        cout << "User ID: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Year: " << year << endl;
    }
};

class BorrowRecord
{
private:
    int userId;
    int resourceId;
    string type;
    string startTime;
    string endTime;
    bool active;
public:
    BorrowRecord(int uId, int rId, string t, string start = "", string end = "")
    {
        userId = uId;
        resourceId = rId;
        type = t;
        startTime = start;
        endTime = end;
        active = true;
    }
    int getUserId()
    {
        return userId;
    }
    int getResourceId()
    {
        return resourceId;
    }
    string getType()
    {
        return type;
    }
    string getStartTime()
    {
        return startTime;
    }
    string getEndTime()
    {
        return endTime;
    }
    bool getActive()
    {
        return active;
    }
    void completeRecord()
    {
        active = false;
    }
    void display()
    {
        cout << "User ID: " << userId << endl;
        cout << "Resource ID: " << resourceId << endl;
        cout << "Type: " << type << endl;
        cout << "Time: " << startTime << " - " << endTime << endl;
        cout << "Status: ";

        if(active)
            cout << "Active" << endl;
        else
            cout << "Completed" << endl;
    }
};

class UserManager
{
private:
    vector<User> users;
    vector<BorrowRecord> records;
    int nextUserId = 101;

public:
    void addUser(string name, string department, int year)
    {
        User newUser(nextUserId, name, department, year);
        users.push_back(newUser);

        cout << "User added. ID: " << nextUserId << endl;

        nextUserId++;
    }

    void showUsers()
    {
        if(users.empty())
        {
            cout << "No users available." << endl;
            return;
        }

        for(int i = 0; i < users.size(); i++)
        {
            users[i].display();
            cout << endl;
        }
    }

    int searchUserById(int id)
    {
        for(int i = 0; i < users.size(); i++)
        {
            if(users[i].getUserId() == id)
            {
                return i;
            }
        }

        return -1;
    }

    void searchUserByName(string name)
    {
        bool found = false;

        for(int i = 0; i < users.size(); i++)
        {
            if(users[i].getName() == name)
            {
                users[i].display();
                cout << endl;
                found = true;
            }
        }

        if(!found)
        {
            cout << "User not found." << endl;
        }
    }

    void searchUserByDepartment(string department)
    {
        bool found = false;

        for(int i = 0; i < users.size(); i++)
        {
            if(users[i].getDepartment() == department)
            {
                users[i].display();
                cout << endl;
                found = true;
            }
        }

        if(!found)
        {
            cout << "No users found in department." << endl;
        }
    }

    void findUserById(int id)
    {
        int index = searchUserById(id);

        if(index != -1)
        {
            users[index].display();
        }
        else
        {
            cout << "User not found." << endl;
        }
    }

    void searchUser(int id)
    {
        findUserById(id);
    }

    void searchUser(string name)
    {
        searchUserByName(name);
    }

    bool userExists(int userId)
    {
        return searchUserById(userId) != -1;
    }

    bool alreadyBorrowed(int userId, int resourceId, string start, string end)
    {
        for(int i = 0; i < records.size(); i++)
        {
            if(records[i].getUserId() == userId &&
               records[i].getResourceId() == resourceId &&
               records[i].getType() == "Borrow" &&
               records[i].getStartTime() == start &&
               records[i].getEndTime() == end &&
               records[i].getActive())
            {
                return true;
            }
        }

        return false;
    }

    void borrowResource(int userId, int resourceId, string start = "", string end = "")
    {
        if(!userExists(userId))
        {
            cout << "User does not exist." << endl;
            return;
        }

        if(alreadyBorrowed(userId, resourceId, start, end))
        {
            cout << "Already booked for this time." << endl;
            return;
        }

        BorrowRecord newRecord(userId, resourceId, "Borrow", start, end);
        records.push_back(newRecord);

        cout << "Resource booked." << endl;
    }

    void lendResource(int userId, int resourceId, string start = "", string end = "")
    {
        if(!userExists(userId))
        {
            cout << "User does not exist." << endl;
            return;
        }

        BorrowRecord newRecord(userId, resourceId, "Lend", start, end);
        records.push_back(newRecord);

        cout << "Resource listed for lending." << endl;
    }

    void returnResource(int userId, int resourceId, string start = "", string end = "")
    {
        for(int i = 0; i < records.size(); i++)
        {
            if(records[i].getUserId() == userId &&
               records[i].getResourceId() == resourceId &&
               records[i].getType() == "Borrow" &&
               records[i].getStartTime() == start &&
               records[i].getEndTime() == end &&
               records[i].getActive())
            {
                records[i].completeRecord();

                cout << "Resource returned." << endl;
                return;
            }
        }

        cout << "Active borrow record not found." << endl;
    }

    void showRecords()
    {
        if(records.empty())
        {
            cout << "No records available." << endl;
            return;
        }

        for(int i = 0; i < records.size(); i++)
        {
            records[i].display();
            cout << endl;
        }
    }
};