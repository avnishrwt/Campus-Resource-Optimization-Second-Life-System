#include <iostream>
#include "resource.cpp"
#include "transaction.cpp"

using namespace std;

int main()
{

    Resource r1(1, "Lab-1", 40, "Block A");
    Resource r2(2, "Seminar Hall", 100, "Block B");
    Resource r3(3, "Sports Ground", 50, "Block C");

    cout << "========== RESOURCES ==========\n\n";

    cout << "Resource 1: " << r1.getName()
         << " | Capacity: " << r1.getCapacity()
         << " | Location: " << r1.getLocation() << endl;

    cout << "Resource 2: " << r2.getName()
         << " | Capacity: " << r2.getCapacity()
         << " | Location: " << r2.getLocation() << endl;

    cout << "Resource 3: " << r3.getName()
         << " | Capacity: " << r3.getCapacity()
         << " | Location: " << r3.getLocation() << endl;


  

    storage store;


    

    cout << "\n========== ADDING REQUESTS ==========\n\n";

    store.addrequest(101, "Need Lab-1 for project work");
    store.addrequest(102, "Need Seminar Hall for presentation");
    store.addrequest(103, "Need Sports Ground for practice");



    cout << "\n========== ALL REQUESTS ==========\n\n";

    store.showrequests();




    cout << "\n========== BOOKING RESOURCES ==========\n\n";

    // User 101 requests Resource 1
    if (r1.book())
    {
        cout << "Lab-1 booked successfully for User 101.\n";

        // Create transaction after successful booking
        store.addtransaction(1001, 101, r1.getId());
    }
    else
    {
        cout << "Lab-1 is already booked.\n";
    }


    // User 102 requests Resource 2
    if (r2.book())
    {
        cout << "Seminar Hall booked successfully for User 102.\n";

        store.addtransaction(1002, 102, r2.getId());
    }
    else
    {
        cout << "Seminar Hall is already booked.\n";
    }


    // User 103 requests Resource 3
    if (r3.book())
    {
        cout << "Sports Ground booked successfully for User 103.\n";

        store.addtransaction(1003, 103, r3.getId());
    }
    else
    {
        cout << "Sports Ground is already booked.\n";
    }



    cout << "\n========== ALL TRANSACTIONS ==========\n\n";

    store.showtransactions();


  
    cout << "\n========== SECOND BOOKING ATTEMPT ==========\n\n";

    if (r1.book())
    {
        cout << "Lab-1 booked successfully.\n";
    }
    else
    {
        cout << "Lab-1 is already booked. Booking failed.\n";
    }



    cout << "\n========== RELEASING RESOURCE ==========\n\n";

    r1.release();

    cout << "Lab-1 has been released.\n";




    cout << "\n========== BOOKING AFTER RELEASE ==========\n\n";

    if (r1.book())
    {
        cout << "Lab-1 booked successfully again.\n";

        store.addtransaction(1004, 104, r1.getId());
    }
    else
    {
        cout << "Lab-1 booking failed.\n";
    }




    cout << "\n========== FINAL TRANSACTIONS ==========\n\n";

    store.showtransactions();


    return 0;
}