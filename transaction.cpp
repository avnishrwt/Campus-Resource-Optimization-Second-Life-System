#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
 
using namespace std;
 
 
 
class request     // for request created by a user 
{
private:
    int requestId;
    int userId;
    int resourceId;       // which resource the user wants
    string description;
    int priority;         // 3 = urgent, 2 = medium, 1 = low
    string status;        // Pending Approved Rejected Completed 

 
public:
    request(int reqId, int uId, int resId, string des, int prio)
    {
        requestId = reqId;
        userId = uId;
        resourceId = resId;
        description = des;
        priority = prio;
        status = "Pending";    // Initially any status would be pending only 

    }
    

    // Getter Functions 

    int getRequestId()   { return requestId; }
    int getUserId()      { return userId; }
    int getResourceId()  { return resourceId; }
    int getPriority()    { return priority; }


    string getStatus()   { return status; }
 
    // Setter Function 
    
    void setStatus(string s) { status = s; }
 
    void display()
    {
        cout << "Request ID  : " << requestId << endl;
        cout << "User ID     : " << userId << endl;
        cout << "Resource ID : " << resourceId << endl;
        cout << "Description : " << description << endl;
        cout << "Priority    : " << priority << endl;
        cout << "Status      : " << status << endl;
    }
};
 
 
// Transaction Class 

class transaction
{
private:
    int transactionId;
    int requestId;
    int userId;
    int resourceId;
    bool returned;
 
public:
    transaction(int transId, int reqId, int uId, int resId)
    {
        transactionId = transId;
        requestId = reqId;
        userId = uId;
        resourceId = resId;
        returned = false;          // borrowed right now
    }
 
    // Getter Functions
    int getTransactionId() { return transactionId; }
    int getRequestId()     { return requestId; }
    int getResourceId()    { return resourceId; }
    bool isReturned()      { return returned; }
 
    void markReturned() { returned = true; }
 
    void display()
    {
        cout << "Transaction ID : " << transactionId << endl;
        cout << "Request ID     : " << requestId << endl;
        cout << "User ID        : " << userId << endl;
        cout << "Resource ID    : " << resourceId << endl;
        cout << "Status         : " << (returned ? "Returned" : "Borrowed") << endl;

    }

};
 
 
// Storage Class

class storage
{
private:
    // the only copy of every object
    vector<request> requests;
    vector<transaction> transactions;
 
    // searching the index in vector with the help of indexes 
    unordered_map<int, int> requestIndex;
    unordered_map<int, int> transactionIndex;
 
    // history: userId -> list of transaction ids
    unordered_map<int, vector<int>> userHistory;
 
    // urgent requests first: stores priority, -requestId 
    priority_queue<pair<int, int>> pendingQueue;

    // - is here because of the reason if same priority comes for two requests 
    // for example 5001 and 5002 then out priority queue will have given class to 1002 
    // who came late , so we used the - sign here which will make -1001 bigger than -1002 
    // so 1001 will get the class
 
    int next_req_Id = 1001;
    int next_trans_Id = 5001;
 
    // priority assignment rule
    int assignPriority(string purpose)
    {
        if (purpose == "exam")  return 3;
        if (purpose == "event") return 2; 
        return 1;                          // project, practice, others
    }
 
public:
 // for request creation 

    int addrequest(int userId, int resourceId, string purpose, string description)
    {
        int id = next_req_Id++;
        int prio = assignPriority(purpose);
 
        requests.push_back(request(id, userId, resourceId, description, prio));
        requestIndex[id] = requests.size() - 1;     // adds id key with request made... it will be at the last of the request vector index
 
        pendingQueue.push({prio, -id});    // -id: older request wins a tie
        return id;
    }
 

    request* findRequest(int requestId)
    {
        if (requestIndex.count(requestId) == 0) return nullptr;
        return &requests[requestIndex[requestId]];  // jo bi iss function ko call krega usse ye address mil jatyega requests me jo bi request pdi h uska 
    }
 
    transaction* findTransaction(int transactionId)
    {
        if (transactionIndex.count(transactionId) == 0) return nullptr;
        return &transactions[transactionIndex[transactionId]];
    }
 

    int getNextRequest()
    {
        while (!pendingQueue.empty())
        {
            int id = -pendingQueue.top().second;
            pendingQueue.pop();
            

            request* r = findRequest(id);     // Done for safe check so that if there was no request for this id then find request will give the nullptr

            if (r != nullptr && r->getStatus() == "Pending")
                return id;                 // skip ones already handled
        }
        return -1;
    }
 
    
    int borrow(int requestId)
    {
        request* r = findRequest(requestId);
        if (r == nullptr || r->getStatus() != "Pending") return -1;
 
        int transId = next_trans_Id++;
        
        transactions.push_back(transaction(transId, requestId, r->getUserId(), r->getResourceId()));

        transactionIndex[transId] = transactions.size() - 1;
        userHistory[r->getUserId()].push_back(transId);
 
        r->setStatus("Approved");
        return transId;
    }
 
   
 

    int returnResource(int transactionId)
    {
        transaction* t = findTransaction(transactionId);
        if (t == nullptr || t->isReturned()) return -1;

        t->markReturned();
        request* r = findRequest(t->getRequestId());
        if (r != nullptr)
        {
            r->setStatus("Completed");
        }
        return t->getResourceId();
    }

    
};