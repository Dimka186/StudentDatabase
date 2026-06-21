// ============================================================
// COMP1014 - Lab 06: Student Database System (Enhanced)
// Name: Shamir Dimka
// Student Number: 4406772
// File: Student.h
// ============================================================
#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

// ================= CONSTANTS =================
const int STUDENT_MAX = 100;
const int NUM_ASSIGNMENTS = 5;
const int NUM_COURSES = 3;

// ================= STRUCT =================
struct Student
{
    string firstName;
    string lastName;
    int id;

    double assignments[NUM_ASSIGNMENTS];
    double average;

    string courses[NUM_COURSES];
};

// ================= FUNCTION PROTOTYPES =================
void loadStudents(Student students[], int& count);
void displayStudents(Student students[], int count);

void calculateAverage(Student* s);
void calculateAllAverages(Student students[], int count);

void searchByCourse(Student students[], int count);
void showAssignmentAverage(Student students[], int count);
void showHardestAssignment(Student students[], int count);
void courseEnrollment(Student students[], int count);

void sortByAverage(Student students[], int count);

void addStudent(Student students[], int& count);
void atRiskStudents(Student students[], int count);
void saveStudents(Student students[], int count);

#endif
