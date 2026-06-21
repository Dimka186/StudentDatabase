// ============================================================
// COMP1014 - Lab 06: Student Database System (Enhanced)
// Name: Shamir Dimka
// Student Number: 4406772
// File: Student.cpp
// ============================================================
#include <iostream>
#include <fstream>
#include "Student.h"
using namespace std;

// ================= LOAD =================
void loadStudents(Student students[], int& count)
{
    ifstream inFile("Students90.txt");

    if (!inFile)
    {
        cout << "Error: Could not open Students90.txt" << endl;
        return;
    }

    count = 0;

    while (inFile >> students[count].firstName
                 >> students[count].lastName
                 >> students[count].id)
    {
        // read the 5 assignment marks into the assignments array
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            inFile >> students[count].assignments[j];

        // read the average
        inFile >> students[count].average;

        // read the 3 courses into the courses array
        for (int j = 0; j < NUM_COURSES; j++)
            inFile >> students[count].courses[j];

        count++;

        if (count >= STUDENT_MAX)
            break;
    }

    inFile.close();
}

// ================= DISPLAY =================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

// ================= AVERAGE (POINTER REQUIREMENT) =================
// Uses pass-by-pointer and the -> operator to modify the struct.
void calculateAverage(Student* s)
{
    double sum = 0;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        sum += s->assignments[j];

    s->average = sum / NUM_ASSIGNMENTS;
}

void calculateAllAverages(Student students[], int count)
{
    for (int i = 0; i < count; i++)
        calculateAverage(&students[i]);
}

// ================= SEARCH BY COURSE =================
void searchByCourse(Student students[], int count)
{
    string course;
    cout << "Enter Course: ";
    cin >> course;

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << " "
                     << students[i].firstName << " "
                     << students[i].lastName << endl;
                break;
            }
        }
    }
}

// ================= ASSIGNMENT AVERAGES (A1 - A5) =================
void showAssignmentAverage(Student students[], int count)
{
    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        double sum = 0;

        for (int i = 0; i < count; i++)
            sum += students[i].assignments[j];

        cout << "A" << j + 1 << ": " << sum / count << endl;
    }
}

// ================= HARDEST ASSIGNMENT (LOWEST AVERAGE) =================
void showHardestAssignment(Student students[], int count)
{
    int hardest = 0;
    double lowestAvg = 0;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        double sum = 0;

        for (int i = 0; i < count; i++)
            sum += students[i].assignments[j];

        double avg = sum / count;

        if (j == 0 || avg < lowestAvg)
        {
            lowestAvg = avg;
            hardest = j;
        }
    }

    cout << "Hardest: A" << hardest + 1 << " (" << lowestAvg << ")" << endl;
}

// ================= COURSE ENROLLMENT =================
void courseEnrollment(Student students[], int count)
{
    string courseNames[STUDENT_MAX * NUM_COURSES];
    int courseCounts[STUDENT_MAX * NUM_COURSES];
    int numCourses = 0;

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            string c = students[i].courses[j];
            int found = -1;

            for (int k = 0; k < numCourses; k++)
            {
                if (courseNames[k] == c)
                {
                    found = k;
                    break;
                }
            }

            if (found == -1)
            {
                courseNames[numCourses] = c;
                courseCounts[numCourses] = 1;
                numCourses++;
            }
            else
            {
                courseCounts[found]++;
            }
        }
    }

    for (int k = 0; k < numCourses; k++)
        cout << courseNames[k] << ": " << courseCounts[k] << endl;
}

// ================= SORT BY AVERAGE (HIGH -> LOW) =================
void sortByAverage(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - 1 - i; j++)
        {
            if (students[j].average < students[j + 1].average)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// ================= ADD STUDENT =================
void addStudent(Student students[], int& count)
{
    cout << "Enter FName LName ID: ";
    cin >> students[count].firstName
        >> students[count].lastName
        >> students[count].id;

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
    {
        cout << "Enter A" << j + 1 << " mark: ";
        cin >> students[count].assignments[j];
    }

    for (int j = 0; j < NUM_COURSES; j++)
    {
        cout << "Enter Course" << j + 1 << ": ";
        cin >> students[count].courses[j];
    }

    // calculate the new student's average using the pointer function
    calculateAverage(&students[count]);

    count++;
}

// ================= AT RISK STUDENTS =================
// At least one assignment below 50 AND average between 50 and 59.
void atRiskStudents(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        bool hasLowAssignment = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (students[i].assignments[j] < 50)
            {
                hasLowAssignment = true;
                break;
            }
        }

        if (hasLowAssignment &&
            students[i].average >= 50 &&
            students[i].average <= 59)
        {
            cout << students[i].id << " "
                 << students[i].firstName << " "
                 << students[i].lastName << endl;
        }
    }
}

// ================= SAVE STUDENTS =================
// Writes every field back to the file in the exact same format.
void saveStudents(Student students[], int count)
{
    ofstream outFile("Students90.txt");

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].firstName << " "
                << students[i].lastName << " "
                << students[i].id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            outFile << students[i].assignments[j] << " ";

        outFile << students[i].average << " ";

        for (int j = 0; j < NUM_COURSES; j++)
        {
            outFile << students[i].courses[j];
            if (j < NUM_COURSES - 1)
                outFile << " ";
        }

        outFile << endl;
    }

    outFile.close();
}
