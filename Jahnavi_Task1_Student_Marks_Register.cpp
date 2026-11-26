#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Student {
private:
    string name;
    string usn;
    int* marks;
    static int studentCount;

public:
    Student(string n, string id, int a, int b, int c)
        : name(n), usn(id), marks(new int[3]) {
        setMarks(a, b, c);
        ++studentCount;
    }

    void setMarks(int a, int b, int c) {
        marks[0] = a;
        marks[1] = b;
        marks[2] = c;
    }

    void setMarks(const int values[]) {
        for (int i = 0; i < 3; ++i)
            marks[i] = values[i];
    }

    double average() const {
        return (marks[0] + marks[1] + marks[2]) / 3.0;
    }

    void display() const {
        cout << left << setw(16) << name << setw(14) << usn
             << marks[0] << " " << marks[1] << " " << marks[2]
             << " Average: " << fixed << setprecision(2) << average() << '\n';
    }

    void display(bool showAverage) const {
        cout << "Student: " << name << ", USN: " << usn;
        if (showAverage)
            cout << ", Average: " << fixed << setprecision(2) << average();
        cout << '\n';
    }

    static int getStudentCount() {
        return studentCount;
    }

    bool operator>(const Student& other) const {
        return average() > other.average();
    }

    friend void compareByMarks(const Student&, const Student&);

    ~Student() {
        delete[] marks;
        --studentCount;
    }

    Student(const Student& other)
        : name(other.name), usn(other.usn), marks(new int[3]) {
        for (int i = 0; i < 3; ++i)
            marks[i] = other.marks[i];
        ++studentCount;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            usn = other.usn;
            for (int i = 0; i < 3; ++i)
                marks[i] = other.marks[i];
        }
        return *this;
    }
};

int Student::studentCount = 0;

void compareByMarks(const Student& first, const Student& second) {
    cout << "Friend function: ";
    if (first.average() > second.average())
        cout << "First student has the higher average.\n";
    else if (second.average() > first.average())
        cout << "Second student has the higher average.\n";
    else
        cout << "Both students have equal averages.\n";
}

int main() {
    Student s1("Nisha Rao", "NB25ECE077", 88, 91, 84);
    Student s2("Arjun Dev", "NB25ECE081", 76, 89, 82);
    Student s3("Megha S", "NB25ECE094", 93, 95, 90);

    cout << "===== STUDENT MARKS REGISTER =====\n";
    cout << "Name            USN           Marks and Average\n";
    s1.display();
    s2.display();
    s3.display(true);

    cout << "\nNumber of Student objects: "
         << Student::getStudentCount() << '\n';

    cout << "\nOperator overloading (>): ";
    cout << (s3 > s1 ? "Megha S scored a higher average than Nisha Rao.\n"
                      : "Nisha Rao scored a higher average than Megha S.\n");

    compareByMarks(s1, s2);
    cout << "Program executed successfully.\n";
    return 0;
}
