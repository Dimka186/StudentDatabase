// ============================================================
// COMP1014 - Lab 06: Student Database System (Enhanced)
// Name: Shamir Dimka
// Student Number: 4406772
// File: Main.cpp
// ============================================================
#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
    Student students[STUDENT_MAX];
    int count = 0;

    loadStudents(students, count);
    calculateAllAverages(students, count);

    int choice;

    do
    {
        cout << "\n===== STUDENT DATABASE =====\n";
        cout << "1. Display\n";
        cout << "2. Search by Course\n";
        cout << "3. Assignment Averages\n";
        cout << "4. Hardest Assignment\n";
        cout << "5. Course Enrollment\n";
        cout << "6. Sort by Averages\n";
        cout << "7. Add Student\n";
        cout << "8. At Risk Students\n";
        cout << "9. Exit\n";
        cout << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
			case 1: 
			{
				displayStudents(students, count); 
				break;
			}
			case 2: 
			{
				searchByCourse(students, count);
				break;
			}		
			case 3: 
			{
				showAssignmentAverage(students, count);
				break;
			}	
			case 4: 
			{
				showHardestAssignment(students, count);
				break;
			}	
			case 5: 
			{
				courseEnrollment(students, count);
				break;
			}	
			case 6: 
			{
				// sort the data, then display it
				sortByAverage(students, count);
				displayStudents(students, count);
				break;
			}	
			case 7: 
			{
				// add student -> save to file -> reload file -> display
				addStudent(students, count);
				saveStudents(students, count);
				loadStudents(students, count);
				calculateAllAverages(students, count);
				displayStudents(students, count);
				break;
			}	
			case 8: 
			{
				atRiskStudents(students, count);
				break;
			}	
			default:
				cout << "\nInvalid choice!" << endl;
        }//end of swithch

    } while (choice != 9);
}//end of main
