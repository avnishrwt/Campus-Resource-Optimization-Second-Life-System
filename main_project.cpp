#include <iostream>
#include "transaction.cpp"


using namespace std;

int main() {
    storage store;

    // Test requests
    store.addrequest(101, "Need DSA Book for 3 days");
    store.addrequest(102, "Need Scientific Calculator");

    // Test transactions
    store.addtransaction(1001, 101, 501);

    // Output check
    store.showrequests();
    store.showtransactions();

    return 0;
}