#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Student {
protected:
    string name;
    int rollNo;

public:
    Student(const string& n, int r) : name(n), rollNo(r) {}

    virtual void show() const {
        cout << name << " (" << rollNo << ")";
    }

    virtual ~Student() = default;
};

class Result : public Student {
private:
    int internalMarks;
    int externalMarks;

public:
    Result(const string& n, int r, int in, int ex)
        : Student(n, r), internalMarks(in), externalMarks(ex) {
        if (in < 0 || in > 40 || ex < 0 || ex > 60)
            throw invalid_argument(
                "Internal marks must be 0-40 and external marks 0-60.");
    }

    int total() const {
        return internalMarks + externalMarks;
    }

    void show() const override {
        cout << left << setw(16) << name
             << setw(10) << rollNo
             << setw(10) << internalMarks
             << setw(10) << externalMarks
             << setw(10) << total()
             << (total() >= 40 ? "PASS" : "FAIL") << '\n';
    }

    string fileRecord() const {
        return name + "," + to_string(rollNo) + "," +
               to_string(internalMarks) + "," + to_string(externalMarks);
    }
};

int main() {
    vector<Result> records;
    int count;

    cout << "===== STUDENT RESULT MANAGEMENT =====\n";
    cout << "Enter number of students: ";

    if (!(cin >> count) || count <= 0) {
        cerr << "Invalid student count. Enter a positive integer.\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        string name;
        int roll, internal, external;

        cout << "\nStudent " << i + 1 << " name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Roll number: ";
        cin >> roll;

        cout << "Internal marks (0-40): ";
        cin >> internal;

        cout << "External marks (0-60): ";
        cin >> external;

        try {
            records.emplace_back(name, roll, internal, external);
        } catch (const invalid_argument& e) {
            cout << "Invalid marks: " << e.what() << '\n';
            cout << "This record was not added.\n";
            --i;
        }
    }

    ofstream fout("jahnavi_results.txt");
    if (!fout) {
        cerr << "Unable to create result file.\n";
        return 1;
    }

    for (const Result& r : records)
        fout << r.fileRecord() << '\n';

    fout.close();

    ifstream fin("jahnavi_results.txt");
    if (!fin) {
        cerr << "Unable to open result file.\n";
        return 1;
    }

    vector<Result> retrieved;
    string line;

    while (getline(fin, line)) {
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
            continue;

        string savedName = line.substr(0, p1);
        int savedRoll = stoi(line.substr(p1 + 1, p2 - p1 - 1));
        int savedInternal = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        int savedExternal = stoi(line.substr(p3 + 1));

        retrieved.emplace_back(
            savedName, savedRoll, savedInternal, savedExternal);
    }

    fin.close();

    cout << "\nRecords retrieved from file:\n";
    cout << left << setw(16) << "Name"
         << setw(10) << "Roll"
         << setw(10) << "Internal"
         << setw(10) << "External"
         << setw(10) << "Total"
         << "Status\n";

    for (const Result& r : retrieved) {
        const Student* basePtr = &r;
        basePtr->show();
    }

    int cutoff;
    cout << "\nShow students scoring above total marks: ";
    cin >> cutoff;

    cout << "\nStudents above " << cutoff << ":\n";

    int found = 0;
    for_each(retrieved.begin(), retrieved.end(),
             [cutoff, &found](const Result& r) {
                 if (r.total() > cutoff) {
                     r.show();
                     ++found;
                 }
             });

    if (found == 0)
        cout << "No student scored above the given cutoff.\n";

    cout << "\nTotal records processed: " << retrieved.size() << '\n';
    cout << "Program executed successfully.\n";

    return 0;
}
