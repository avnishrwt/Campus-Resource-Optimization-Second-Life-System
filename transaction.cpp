#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


class request 
{
    int requestId;
    int userId;
    string description;
    


    public:
        request(int reqId, int uId , string des)
        {
            requestId = reqId;
            userId = uId;
            description = des;
        }

        int getrequestId()
        {
            return requestId;
        }

        void display()
        {
            cout << "Request ID   : " << requestId << endl;
            cout << "User ID     : " << userId << endl;
            cout << "Description : " << description << endl;
        }
};


class transaction
{
    private:
            int transactionId;
            int requestId;
            int userId;
            int resourceId;

    public:

        transaction(int transId ,int reqId ,int uId ,int resId)
        {
            transactionId = transId;
            requestId = reqId;
            userId = uId;
            resourceId = resId;
        }

        int getTransactionId()
        {
            return transactionId;
        }

        void display()
        {
            cout << "Transaction ID : " << transactionId << endl;
            cout << "Request ID     : " << requestId << endl;
            cout << "User ID        : " << userId << endl;
            cout << "Resource ID    : " << resourceId << endl;
        }
};






class storage
{

    // fulll data 
    vector<request> requests;
    vector<transaction> transactions;

    // fast data look up
    unordered_map< int , request > request_map;
    unordered_map< int , transaction > transaction_map;


    // id generation 
    int next_req_Id = 1001 ;
    int next_trans_Id = 5001 ;


    public:

    void addrequest(int userId , string description)
    {
        request req(next_req_Id , userId , description);       // object creation 


        requests.push_back(req);



        request_map.emplace(next_req_Id , req);


        next_req_Id++;

    }




    void addtransaction(int requestId , int userId , int resourceId)
    {
        transaction trans(next_trans_Id , requestId , userId , resourceId);    // object creation 

        transactions.push_back(trans);

        transaction_map.emplace(next_trans_Id , trans);      //inplace of emplace can also use insert as it map.insert({next_trans_id , trans})


        next_trans_Id++;


    }


    void showrequests()
    {

        cout << "HERE ARE THE REQUESTS : " << '\n';

        for(auto &it : requests)     // & is used bcs of the reason so that no new copy of each and every object not be created 
        {
            it.display();

            cout <<'\n';

        }
    }




    void showtransactions()
    {
        cout << "HERE ARE THE TRANSACTIONS : " << '\n';
        for(auto &it : transactions)
        {
            it.display();
            cout << '\n';
        }
    }

};


