
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

// ============================================================
// ENUM
// ============================================================

enum class Status {
    AVAILABLE,
    BORROWED,
    UNDER_REPAIR
};

string statusToString(Status s) {

    if (s == Status::AVAILABLE)
        return "Available";

    if (s == Status::BORROWED)
        return "Borrowed";

    return "Under Repair";
}

// ============================================================
// USER
// ============================================================

class User {

private:

    int id;
    string name;
    string email;

public:

    User(int id, string name, string email)
        : id(id), name(name), email(email) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }
};

// ============================================================
// RESOURCE
// ============================================================

class Resource {

private:

    int id;
    string name;
    string category;

    int ownerId;
    int borrowerId;

    int condition;
    int demand;

    Status status;

public:

    Resource(
        int id,
        string name,
        string category,
        int ownerId,
        int condition,
        int demand
    )
        : id(id),
          name(name),
          category(category),
          ownerId(ownerId),
          borrowerId(-1),
          condition(condition),
          demand(demand),
          status(Status::AVAILABLE) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getCategory() const {
        return category;
    }

    int getOwnerId() const {
        return ownerId;
    }

    int getBorrowerId() const {
        return borrowerId;
    }

    int getCondition() const {
        return condition;
    }

    int getDemand() const {
        return demand;
    }

    Status getStatus() const {
        return status;
    }

    void setStatus(Status s) {
        status = s;
    }

    void setBorrower(int userId) {
        borrowerId = userId;
    }

    void removeBorrower() {
        borrowerId = -1;
    }

    void increaseDemand() {
        demand++;
    }

    void display() const {

        cout << "\n----------------------------------------\n";

        cout << "Resource ID : " << id << endl;
        cout << "Name        : " << name << endl;
        cout << "Category    : " << category << endl;
        cout << "Condition   : " << condition << "%" << endl;
        cout << "Demand      : " << demand << endl;
        cout << "Status      : "
             << statusToString(status)
             << endl;

        if (borrowerId != -1) {
            cout << "Borrowed By : User #" << borrowerId << endl;
        }

        cout << "----------------------------------------\n";
    }
};

// ============================================================
// REQUEST
// ============================================================

class Request {

private:

    int id;
    int userId;

    string description;
    string category;

    int duration;
    int priority;

public:

    Request(
        int id,
        int userId,
        string description,
        string category,
        int duration,
        int priority
    )
        : id(id),
          userId(userId),
          description(description),
          category(category),
          duration(duration),
          priority(priority) {}

    int getId() const {
        return id;
    }

    int getUserId() const {
        return userId;
    }

    string getCategory() const {
        return category;
    }

    int getPriority() const {
        return priority;
    }

    void display() const {

        cout << "\nRequest #" << id << endl;

        cout << "Need       : "
             << description << endl;

        cout << "Category   : "
             << category << endl;

        cout << "Duration   : "
             << duration << " days" << endl;

        cout << "Priority   : "
             << priority << "/10" << endl;
    }
};

// ============================================================
// PRIORITY QUEUE COMPARATOR
// ============================================================

struct RequestComparator {

    bool operator()(
        const Request& a,
        const Request& b
    ) const {

        return a.getPriority()
             < b.getPriority();
    }
};

// ============================================================
// STUDY SPACE
// ============================================================

class StudySpace {

private:

    int id;
    string name;

    int capacity;
    int quietness;
    int availableHours;
    int distance;

public:

    StudySpace(
        int id,
        string name,
        int capacity,
        int quietness,
        int availableHours,
        int distance
    )
        : id(id),
          name(name),
          capacity(capacity),
          quietness(quietness),
          availableHours(availableHours),
          distance(distance) {}

    int getId() const {
        return id;
    }

    int getQuietness() const {
        return quietness;
    }

    int getAvailableHours() const {
        return availableHours;
    }

    int getDistance() const {
        return distance;
    }

    void display(double score) const {

        cout << "\n----------------------------------------\n";

        cout << "Study Space  : "
             << name << endl;

        cout << "Capacity     : "
             << capacity << endl;

        cout << "Quietness    : "
             << quietness << "/5" << endl;

        cout << "Available    : "
             << availableHours
             << " hours" << endl;

        cout << "Distance     : "
             << distance
             << " meters" << endl;

        cout << "MATCH SCORE  : "
             << fixed
             << setprecision(1)
             << score
             << "%" << endl;

        cout << "----------------------------------------\n";
    }
};

// ============================================================
// CAMPUS SYSTEM
// ============================================================

class CampusSystem {

private:

    unordered_map<int, User> users;

    vector<Resource> resources;

    vector<StudySpace> spaces;

    vector<Request> requests;

    priority_queue<
        Request,
        vector<Request>,
        RequestComparator
    > requestQueue;

    int nextUserId = 4;
    int nextResourceId = 106;
    int nextRequestId = 1;

public:

    // ========================================================
    // LOAD SAMPLE DATA
    // ========================================================

    void loadData() {

        users.emplace(
            1,
            User(
                1,
                "Avnish",
                "avnish@college.edu"
            )
        );

        users.emplace(
            2,
            User(
                2,
                "Rahul",
                "rahul@college.edu"
            )
        );

        users.emplace(
            3,
            User(
                3,
                "Ananya",
                "ananya@college.edu"
            )
        );

        resources.emplace_back(
            101,
            "DSA Complete Guide",
            "Book",
            2,
            95,
            8
        );

        resources.emplace_back(
            102,
            "Casio FX-991ES",
            "Calculator",
            2,
            90,
            10
        );

        resources.emplace_back(
            103,
            "USB-C Charger",
            "Charger",
            3,
            85,
            7
        );

        resources.emplace_back(
            104,
            "Data Structures Book",
            "Book",
            3,
            80,
            6
        );

        resources.emplace_back(
            105,
            "Arduino Kit",
            "Equipment",
            2,
            75,
            4
        );

        spaces.emplace_back(
            1,
            "Classroom 101",
            30,
            5,
            3,
            100
        );

        spaces.emplace_back(
            2,
            "Classroom 102",
            25,
            4,
            2,
            50
        );

        spaces.emplace_back(
            3,
            "Seminar Hall",
            100,
            5,
            4,
            300
        );
    }

    // ========================================================
    // LOGIN
    // ========================================================

    int login() {

        cout << "\n====================================\n";
        cout << "       CAMPUS RESOURCE HUB\n";
        cout << "====================================\n";

        cout << "\nDemo Users:\n";

        cout << "1. Avnish\n";
        cout << "2. Rahul\n";
        cout << "3. Ananya\n";

        int id;

        cout << "\nEnter User ID: ";
        cin >> id;

        auto it = users.find(id);

        if (it == users.end()) {

            cout << "\nUser not found.\n";

            return -1;
        }

        cout << "\nLogin successful!\n";

        cout << "Welcome, "
             << it->second.getName()
             << "!\n";

        return id;
    }

    // ========================================================
    // I NEED SOMETHING
    // ========================================================

    void needSomething(int userId) {

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        string description;
        string category;

        int duration;
        int priority;

        cout << "\n====================================\n";
        cout << "          I NEED SOMETHING\n";
        cout << "====================================\n";

        cout << "\nWhat do you need?\n";
        getline(cin, description);

        cout << "Category: ";
        getline(cin, category);

        cout << "For how many days? ";
        cin >> duration;

        cout << "Priority (1-10): ";
        cin >> priority;

        priority =
            max(1, min(10, priority));

        Request request(
            nextRequestId++,
            userId,
            description,
            category,
            duration,
            priority
        );

        requests.push_back(request);

        requestQueue.push(request);

        cout << "\nRequest created successfully!\n";

        // ----------------------------------------------------
        // FIND MATCHES
        // ----------------------------------------------------

        vector<pair<double, Resource*>>
            matches;

        for (auto& resource : resources) {

            if (
                resource.getStatus()
                != Status::AVAILABLE
            )
                continue;

            string resourceCategory =
                resource.getCategory();

            string search =
                category;

            transform(
                resourceCategory.begin(),
                resourceCategory.end(),
                resourceCategory.begin(),
                [](unsigned char c) {
                    return tolower(c);
                }
            );

            transform(
                search.begin(),
                search.end(),
                search.begin(),
                [](unsigned char c) {
                    return tolower(c);
                }
            );

            if (
                resourceCategory.find(search)
                != string::npos
            ) {

                double conditionScore =
                    resource.getCondition();

                double demandScore =
                    min(
                        resource.getDemand()
                        * 10.0,
                        100.0
                    );

                double availabilityScore = 100;

                double score =
                    0.50 * conditionScore
                    +
                    0.30 * demandScore
                    +
                    0.20 * availabilityScore;

                matches.push_back(
                    {
                        score,
                        &resource
                    }
                );
            }
        }

        // ----------------------------------------------------
        // SORT MATCHES
        // ----------------------------------------------------

        sort(
            matches.begin(),
            matches.end(),
            [](const auto& a,
               const auto& b) {

                return a.first > b.first;
            }
        );

        cout << "\n====================================\n";
        cout << "          BEST MATCHES\n";
        cout << "====================================\n";

        if (matches.empty()) {

            cout << "\nNo matching resources available.\n";

            cout << "Your request has been added "
                 << "to the priority queue.\n";

            return;
        }

        for (
            int i = 0;
            i < min(3, (int)matches.size());
            i++
        ) {

            cout << "\nRecommendation #"
                 << i + 1 << endl;

            cout << "Match Score: "
                 << fixed
                 << setprecision(1)
                 << matches[i].first
                 << "%\n";

            matches[i].second->display();
        }
    }

    // ========================================================
    // BROWSE RESOURCES
    // ========================================================

    void browseResources() {

        cout << "\n====================================\n";
        cout << "         AVAILABLE RESOURCES\n";
        cout << "====================================\n";

        bool found = false;

        for (auto& resource : resources) {

            if (
                resource.getStatus()
                == Status::AVAILABLE
            ) {

                resource.display();

                found = true;
            }
        }

        if (!found)
            cout << "\nNo resources available.\n";
    }

    // ========================================================
    // BORROW RESOURCE
    // ========================================================

    void borrowResource(int userId) {

        int id;

        cout << "\nEnter Resource ID: ";
        cin >> id;

        for (auto& resource : resources) {

            if (resource.getId() == id) {

                if (
                    resource.getStatus()
                    != Status::AVAILABLE
                ) {

                    cout << "\nResource is not available.\n";

                    return;
                }

                resource.setStatus(
                    Status::BORROWED
                );

                resource.setBorrower(userId);

                resource.increaseDemand();

                cout << "\nResource borrowed successfully!\n";

                resource.display();

                return;
            }
        }

        cout << "\nResource not found.\n";
    }

    // ========================================================
    // RETURN RESOURCE
    // ========================================================

    void returnResource(int userId) {

        int id;

        cout << "\nEnter Resource ID: ";
        cin >> id;

        for (auto& resource : resources) {

            if (resource.getId() == id) {

                if (
                    resource.getStatus()
                    != Status::BORROWED
                ) {

                    cout << "\nThis resource is "
                         << "not currently borrowed.\n";

                    return;
                }

                if (
                    resource.getBorrowerId()
                    != userId
                ) {

                    cout << "\nYou did not borrow "
                         << "this resource.\n";

                    return;
                }

                resource.setStatus(
                    Status::AVAILABLE
                );

                resource.removeBorrower();

                cout << "\nResource returned successfully!\n";

                return;
            }
        }

        cout << "\nResource not found.\n";
    }

    // ========================================================
    // FIND STUDY SPACE
    // ========================================================

    void findStudySpace() {

        int hours;

        cout << "\nHow many hours do you need? ";
        cin >> hours;

        vector<pair<double, StudySpace*>>
            recommendations;

        for (auto& space : spaces) {

            if (
                space.getAvailableHours()
                < hours
            )
                continue;

            double quietnessScore =
                space.getQuietness()
                * 20.0;

            double availabilityScore =
                min(
                    100.0,
                    (
                        space.getAvailableHours()
                        /
                        (double)hours
                    ) * 50.0
                );

            double distanceScore =
                max(
                    0.0,
                    100.0
                    -
                    space.getDistance() / 5.0
                );

            double score =
                0.40 * quietnessScore
                +
                0.35 * availabilityScore
                +
                0.25 * distanceScore;

            recommendations.push_back(
                {
                    score,
                    &space
                }
            );
        }

        sort(
            recommendations.begin(),
            recommendations.end(),
            [](const auto& a,
               const auto& b) {

                return a.first > b.first;
            }
        );

        cout << "\n====================================\n";
        cout << "          BEST STUDY SPACES\n";
        cout << "====================================\n";

        if (recommendations.empty()) {

            cout << "\nNo suitable study space found.\n";

            return;
        }

        for (
            int i = 0;
            i < min(
                3,
                (int)recommendations.size()
            );
            i++
        ) {

            recommendations[i]
                .second
                ->display(
                    recommendations[i].first
                );
        }
    }

    // ========================================================
    // MY BORROWED RESOURCES
    // ========================================================

    void myBorrowedResources(int userId) {

        cout << "\n====================================\n";
        cout << "        MY BORROWED RESOURCES\n";
        cout << "====================================\n";

        bool found = false;

        for (auto& resource : resources) {

            if (
                resource.getBorrowerId()
                == userId
            ) {

                resource.display();

                found = true;
            }
        }

        if (!found) {

            cout << "\nYou have no borrowed resources.\n";
        }
    }

    // ========================================================
    // MY REQUESTS
    // ========================================================

    void myRequests(int userId) {

        cout << "\n====================================\n";
        cout << "             MY REQUESTS\n";
        cout << "====================================\n";

        bool found = false;

        for (auto& request : requests) {

            if (
                request.getUserId()
                == userId
            ) {

                request.display();

                found = true;
            }
        }

        if (!found) {

            cout << "\nYou have no requests.\n";
        }
    }

    // ========================================================
    // LEND RESOURCE
    // ========================================================

    void lendResource(int userId) {

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        string name;
        string category;

        int condition;

        cout << "\n====================================\n";
        cout << "           LEND RESOURCE\n";
        cout << "====================================\n";

        cout << "\nResource name: ";
        getline(cin, name);

        cout << "Category: ";
        getline(cin, category);

        cout << "Condition (0-100): ";
        cin >> condition;

        condition =
            max(0, min(100, condition));

        resources.emplace_back(
            nextResourceId++,
            name,
            category,
            userId,
            condition,
            0
        );

        cout << "\nYour resource is now available "
             << "for other students!\n";
    }

    // ========================================================
    // DONATE RESOURCE
    // ========================================================

    void donateResource(int userId) {

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        string name;
        string category;

        int condition;

        cout << "\n====================================\n";
        cout << "           DONATE RESOURCE\n";
        cout << "====================================\n";

        cout << "\nResource name: ";
        getline(cin, name);

        cout << "Category: ";
        getline(cin, category);

        cout << "Condition (0-100): ";
        cin >> condition;

        condition =
            max(0, min(100, condition));

        resources.emplace_back(
            nextResourceId++,
            name,
            category,
            0,
            condition,
            1
        );

        cout << "\nThank you for your donation!\n";
        cout << "The resource has been added "
             << "to the campus pool.\n";
    }

    // ========================================================
    // REPORT DAMAGE
    // ========================================================

    void reportDamage(int userId) {

        int id;

        cout << "\nEnter Resource ID: ";
        cin >> id;

        for (auto& resource : resources) {

            if (resource.getId() == id) {

                if (
                    resource.getBorrowerId()
                    != userId
                    &&
                    resource.getOwnerId()
                    != userId
                ) {

                    cout << "\nYou cannot report damage "
                         << "for this resource.\n";

                    return;
                }

                resource.setStatus(
                    Status::UNDER_REPAIR
                );

                cout << "\nResource reported "
                     << "for repair.\n";

                return;
            }
        }

        cout << "\nResource not found.\n";
    }

    // ========================================================
    // USER MENU
    // ========================================================

    void userMenu(int userId) {

        int choice;

        do {

            cout << "\n\n====================================\n";
            cout << "        CAMPUS RESOURCE HUB\n";
            cout << "====================================\n";

            cout << "Logged in as: "
                 << users.at(userId).getName()
                 << "\n";

            cout << "\n1.  I Need Something\n";
            cout << "2.  Browse Resources\n";
            cout << "3.  Borrow Resource\n";
            cout << "4.  Return Resource\n";
            cout << "5.  Find Study Space\n";
            cout << "6.  Lend My Resource\n";
            cout << "7.  Donate Resource\n";
            cout << "8.  My Requests\n";
            cout << "9.  My Borrowed Resources\n";
            cout << "10. Report Damaged Resource\n";
            cout << "0.  Logout\n";

            cout << "\nChoose an option: ";
            cin >> choice;

            switch (choice) {

                case 1:
                    needSomething(userId);
                    break;

                case 2:
                    browseResources();
                    break;

                case 3:
                    borrowResource(userId);
                    break;

                case 4:
                    returnResource(userId);
                    break;

                case 5:
                    findStudySpace();
                    break;

                case 6:
                    lendResource(userId);
                    break;

                case 7:
                    donateResource(userId);
                    break;

                case 8:
                    myRequests(userId);
                    break;

                case 9:
                    myBorrowedResources(userId);
                    break;

                case 10:
                    reportDamage(userId);
                    break;

                case 0:
                    cout << "\nLogging out...\n";
                    break;

                default:
                    cout << "\nInvalid option.\n";
            }

        } while (choice != 0);
    }
};

// ============================================================
// MAIN
// ============================================================

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CampusSystem system;

    system.loadData();

    while (true) {

        int userId = system.login();

        if (userId == -1)
            continue;

        system.userMenu(userId);

        char again;

        cout << "\nLogin again? (y/n): ";
        cin >> again;

        if (
            again != 'y'
            &&
            again != 'Y'
        ) {
            break;
        }
    }

    cout << "\nThank you for using "
         << "Campus Resource Hub!\n";

    return 0;
}

