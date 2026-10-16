
#include <bits/stdc++.h>
using namespace std;

// 1. TimeSlot Class
class TimeSlot {
public:
    int day, startTime, endTime;
    string subject;

    TimeSlot(int d, int start, int end, string sub) {
        day = d;
        startTime = start;
        endTime = end;
        subject = sub;
    }

    bool overlaps(int d, int start, int end) {
        return day == d && start < endTime && end > startTime;
    }
};

// 2. Teacher Class
class Teacher {
public:
    int teacherID;
    string name;
    vector<TimeSlot> timetable;

    Teacher(int id, string n) {
        teacherID = id;
        name = n;
    }

    bool addTimeSlot(TimeSlot slot) {
        for (TimeSlot &t : timetable) {
            if (t.overlaps(slot.day, slot.startTime, slot.endTime))
                return false;
        }

        timetable.push_back(slot);
        return true;
    }

    bool isFree(int day, int start, int end) {
        for (TimeSlot &t : timetable) {
            if (t.overlaps(day, start, end))
                return false;
        }

        return true;
    }
};

// 3. PhysicalResource Class
class PhysicalResource {
public:
    string resourceID, name, ownerID, contact;
    bool available;

    PhysicalResource(string id, string n, string owner, string phone) {
        resourceID = id;
        name = n;
        ownerID = owner;
        contact = phone;
        available = true;
    }
};

// 4. SpaceMentorManager Class
class SpaceMentorManager {
private:
    unordered_map<int, Teacher> teachers;
    unordered_map<string, PhysicalResource> resources;

public:

    // Add teacher
    bool addTeacher(int id, string name) {
        if (teachers.find(id) != teachers.end())
            return false;

        teachers.emplace(id, Teacher(id, name));
        return true;
    }

    // Add a class to teacher's timetable
    bool addTeacherSchedule(int id, int day, int start, int end,
                            string subject) {
        if (teachers.find(id) == teachers.end())
            return false;

        if (day < 1 || day > 6 || start < 0 ||
            end > 1440 || start >= end)
            return false;

        TimeSlot slot(day, start, end, subject);
        return teachers.at(id).addTimeSlot(slot);
    }

    // Check teacher's timetable availability
    string checkTeacherAvailability(int id, int day, int start, int end) {
        if (teachers.find(id) == teachers.end())
            return "Teacher not found.";

        if (day < 1 || day > 6 || start < 0 ||
            end > 1440 || start >= end)
            return "Invalid day or time.";

        if (teachers.at(id).isFree(day, start, end))
            return "No class scheduled during this time.";

        return "Teacher has a scheduled class.";
    }

    // Add student-owned resource
    bool addResource(string id, string name, string owner, string contact) {
        if (resources.find(id) != resources.end())
            return false;

        resources.emplace(
            piecewise_construct,
            forward_as_tuple(id),
            forward_as_tuple(id, name, owner, contact)
        );

        return true;
    }

    // Search available resources by name
    void searchResource(string name) {
        bool found = false;

        for (auto &entry : resources) {
            PhysicalResource &r = entry.second;

            if (r.name == name && r.available) {
                cout << "Resource ID: " << r.resourceID << endl;
                cout << "Name: " << r.name << endl;
                cout << "Owner: " << r.ownerID << endl;
                cout << "Contact: " << r.contact << endl;
                cout << "------------------\n";
                found = true;
            }
        }

        if (!found)
            cout << "No available resource found.\n";
    }

    // Update resource status: false = borrowed, true = returned
    bool updateResourceAvailability(string id, bool status) {
        auto it = resources.find(id);

        if (it == resources.end())
            return false;

        it->second.available = status;
        return true;
    }
};