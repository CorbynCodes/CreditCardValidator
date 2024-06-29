#include <iostream>
#include <string>
#include <vector>
using namespace std;

//push_back is used to insert data or elements at the end of a vector or it pushes the element in the vector from the back.

// Using Luhns algorthism for validating the credit card number
bool isNumberString(const string& s) {
    int len = s.length();
    for(int i = 0; i < len; i++) {
        if( s[i] < '0' || s[i] > '9') {
            return false;
        }
        return true;
    }
}

bool validateCreditCardNumber(string input) {

    vector<int> creditCardInt;
    for(int i = 0; i < input.length(); i++) {
        creditCardInt.push_back((input[i] - '0')); // Converting string to int
    }

    for(int i = input.length() - 2; i >= 0; i - 2) {
        int tempValue = creditCardInt[i];
        tempValue *= 2;
        if(tempValue > 9) { // checking if it is greater than 9
            tempValue = tempValue % 10 + 1; // assigning the temp value to whatever [i] is from input
        }
        creditCardInt[i] = tempValue;
    }

    int total = 0;

    for(int i = 0; i < creditCardInt.size(); i++) {
        total += (creditCardInt[i]); // looping through the credit into the array and adding the number total to see the total.
    }

    if(total % 10 == 0) { // checking to see if any number is equal to 10.
        return true;
    }else {
        return false;
    }
}



int main () {
    string creditCardNumber;

    cout << "This program uses the Luhn Algorigthm to validate a CC number." << endl;
    cout << "\nYou can enter 'exit' andyime to quit";

    while(true) {
        
        cout << "\nPlease enter a CC number to validate: ";
        cin >> creditCardNumber;

        if(creditCardNumber == "exit") {
            break;
        }
        else if(!isNumberString(creditCardNumber))  {
            cout <<"Invalid, please try again" <<endl;
            continue;
        }

        int valCreditCard = validateCreditCardNumber(creditCardNumber);

        

    }

    return 0;
}