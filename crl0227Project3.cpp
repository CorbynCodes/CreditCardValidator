///failed attempt on project, really annoyed by this project espeically since the exam was last week for the class as well. 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

const int NUM_TESTS = 5;

enum MenuChoice 
{
    Add = 1,
    Remove = 2,
    Display = 3,
    Search = 4,
    Results = 5,
    Quit = 6
};

struct Student {
    string name;
    int studentID;
    int testTaken;
    int* test_Scores;
    float average;
};


    int getNumber() {

    ifstream fin;
    fin.open("student.dat");
    if (fin.fail()) {
        cout<<"File error."<<endl;
        exit(1);
    }

    int count=0;
    string line;
    while(!fin.eof()) {

        getline(fin, line);
        ++count;
    }

    fin.close();
    return(count);

}



void add_Student() {
    
    Student s;
    cout << "Enter the students name: ";
    getline(cin >> ws, s.name); // using getline for the string also including the structure ".";
    cout << "Enter student ID: ";
    cin >> s.studentID;
    cout << "Enter number of test taken: ";
    cin >> s.testTaken;

    s.test_Scores = new int[s.testTaken]; // using dynamic array for testtaken.

    double sum = 0;
    for(int i = 0; i < s.testTaken; i++) {
        cout << "Enter the score for test #" << i + 1 << ": ";
        cin >> s.test_Scores[i];
        sum += s.test_Scores[i];
    }

    s.average = sum / s.testTaken;

    ofstream outFile("student.dat", ios::app);
    outFile << s.name << " " << s.studentID << " " << s.testTaken << " ";
    for(int i = 0; i < s.testTaken; i++) {
        outFile << s.test_Scores[i] << " ";
    }
    outFile << s.average << endl;
    outFile.close();

    delete [] s.test_Scores;

    cout << "Student record added.\n";

}

void remove_Student(int id) {

    int count = getNumber();
    if (count == 0) {
        cout << "No records found." << endl;
        return;
    }

    // Open the input and output files
    ifstream infile("student.dat");
    ofstream outfile("temp.dat");
    if (!infile.is_open() || !outfile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    bool found = false;
    while (!infile.eof()) {
        getline(infile, line);
        if (line.empty()) {
            continue;
        }
        int cur_id = stoi(line.substr(31, 15));
        if (cur_id == id) {
            found = true;
            // Skip over the current student record
            for (int i = 0; i < NUM_TESTS + 2; i++) {
                getline(infile, line);
            }
            continue;
        }
        // Write the current student record to the output file
        outfile << line << endl;
        for (int i = 0; i < NUM_TESTS + 2; i++) {
            getline(infile, line);
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();

    // Remove the original file and rename the temp file
    if (found) {
        remove("student.dat");
        rename("temp.dat", "student.dat");
        cout << "Student record deleted successfully!" << endl;
    } else {
        remove("temp.dat");
        cout << "Student record not found." << endl;
    }

}

void display(string &filename) {

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }
    string line;
    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        string first_name = line.substr(0, 15);
        string last_name = line.substr(16, 15);
        int id = stoi(line.substr(31, 15));
        int num_tests = stoi(line.substr(46, 2));
        float test_scores[NUM_TESTS];
        for (int i = 0; i < num_tests; i++) {
            getline(infile, line);
            test_scores[i] = stof(line);
        }
        getline(infile, line);
        float average = stof(line);
        cout << "Name: " << first_name << " " << last_name << endl;
        cout << "ID: " << id << endl;
        cout << "Number of tests: " << num_tests << endl;
        cout << "Test scores: ";
        for (int i = 0; i < num_tests; i++) {
            cout << test_scores[i] << " ";
        }
        cout << endl;
        cout << "Average: " << average << endl;
        cout << endl;
    }

    infile.close();

}   

void search(int id) {

    ifstream infile("student.dat");
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }
    string line;
    bool found = false;
    while (!infile.eof()) {
        getline(infile, line);
        if (line.empty()) {
            continue;
        }
        int cur_id = stoi(line.substr(31, 15));
        if (cur_id == id) {
            found = true;
            cout << line << endl;
            for (int i = 0; i < NUM_TESTS + 1; i++) {
                getline(infile, line);
                cout << line << endl;
            }
            break;
        }
        for (int i = 0; i < NUM_TESTS + 1; i++) {
            getline(infile, line);
        }
    }
    infile.close();
    if (!found) {
        cout << "Record not found." << endl;
    }

}

void exportResults() {

    int count = getNumber();
    if (count == 0) {
        cout << "No records found." << endl;
        return;
    }
    string filename;
    cout << "Enter filename to export results: ";
    getline(cin, filename);
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }
    ifstream infile("student.dat");
    string line;
    while (!infile.eof()) {
        getline(infile, line);
        if (line.empty()) {
            continue;
        }
        string name = line.substr(0, 30);
        int id = stoi(line.substr(31, 15));
        int num_tests = stoi(line.substr(47, 2));
        double average = stod(line.substr(50, 5));
        outfile << "Name: " << name << endl;
        outfile << "ID: " << id << endl;
        outfile << "Number of Tests: " << num_tests << endl;
        outfile << "Average: " << average << endl;
        for (int i = 0; i < num_tests; i++) {
            getline(infile, line);
            double score = stod(line.substr(0, 5));
            outfile << "Test " << i+1 << ": " << score << endl;
        }
        getline(infile, line); // skip average line
        outfile << endl;
    }
    cout << "Results exported successfully!" << endl;
}

int findMinimum(int arr[], int size) { // need to figure out how to put exportresults inside this function.

    if(size < 5) {
        return 0;
    }

    int min = arr[0];
    for(int i = 0; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return min;

}


int main() {
    
    
   string filename;
   int id;
   MenuChoice choice;
   bool done = false;

   while(!done) {
        cout << "Menu:\n:";
        cout << "1. Add a new student record\n";
        cout << "2. Remove an existing student record\n";
        cout << "3. Display all records";
        cout << "4. Search for a particular student record using student ID\n";
        cout << "5. Export the results to a disk file\n";
        cout << "6. Quit the program";

        int choiceInt;
        cout << "Enter choice: " << endl;;
        cin >> choiceInt;
        choice = static_cast<MenuChoice>(choiceInt);

        switch(choice) {
            case Add:
                add_Student();
                break;
            case Remove:
                remove_Student(id);
                break;
            case Display:
                display(filename);
                break;
            case Search:
                search(id);
                break;
            case Results:
                exportResults();
                break;
            case Quit:
                cout << "Quitting the program......\n";
                done = true;
                break;
            default:
                cout << "Invaild choice. Please enter a number between 1 and 6\n";
                break;
        }

        return 0;

   }
}