// Grade Calculator (original version).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
struct grade {
	int cutoff;
	std::string letter;
};

grade grades[]{
	{ 10, "F" },
	{ 30, "E" },
	{ 50, "D" },
	{ 70, "C" },
	{ 80, "B" },
	{ 90, "A" },
	{ 100, "A*" },
};
//My own user-defined datatype "Student"
class Student
{
private: //Everything under "private" is only accessible from the class itself and not outside e.g. in the int main()
	std::string m_sName; 
	int m_iGrade;
public:
	Student(std::string sName, int iGrade); //Constructor to initialize member variables (in the private)
	std::string GetName() const; //Allows for external access to the private member variable "m_sName"
	int GetGrade() const; //Allows for external access to the private member variable "m_sName"
	std::string CalculateGradeLetter() const; //returns the "letter" of the grade
	std::string HasUserPassed(); //Determines whether the user has passed by checking if the grade returned is "F"
};

//Implementations for the "Student" class
Student::Student(std::string sName, int iGrade) :m_sName(sName), m_iGrade(iGrade) {}
std::string Student::GetName() const {
	return m_sName;
}

int Student::GetGrade() const {
	return m_iGrade;
}


std::string Student::CalculateGradeLetter() const
{
	for (auto grade : grades) {
		if (m_iGrade <= grade.cutoff) {
			return grade.letter;
		}
	}
	return "Unknown";
}

std::string Student::HasUserPassed()
{
	std::string Grade = CalculateGradeLetter();
	if (Grade == "F")
	{
		return "Fail";
	}
	return "Passed";
}
//End of interface link 

//Stand alone functions (nothing to do with the Student class itself)
//returns the index of the vector of the student who got the highest grade
//std::size_t HighestGradeIndex(std::vector<Student>& objStudents) {
//	std::size_t stIndex = 0;
//	int iHighestGrade = 0;
//	for (std::size_t st = 0; st < objStudents.size(); st++)
//	{
//		if (objStudents.at(st).GetGrade() > iHighestGrade)
//		{
//			iHighestGrade = objStudents.at(st).GetGrade();
//			stIndex = st;
//		}
//	}
//	return stIndex;
//}
//returns the index of the vector of the student who got the lowest grade
std::size_t LowestGradeIndex(std::vector<Student>& objStudents)
{
	std::size_t stIndex = 0;
	int iLowestGrade = INT_MAX;
	for (std::size_t st = 0; st < objStudents.size(); st++) {
		if (objStudents.at(st).GetGrade() < iLowestGrade)
		{
			iLowestGrade = objStudents.at(st).GetGrade();
			stIndex = st;
		}
	}
	return stIndex;
}

//Through its parameters the average value is passed in to subsequently check its value with the if / else logic
std::string CalculateGradeLetter(double dAverage)
{
	if (dAverage <= 10) {
		return "F";
	}
	else if (dAverage <= 30) {
		return "E";
	}
	else if (dAverage <= 50) {
		return "D";
	}
	else if (dAverage <= 70) {

		return "C";
	}
	else if (dAverage <= 80) {
		return "B";
	}
	else if (dAverage <= 90) {
		return "A";
	}
	else if (dAverage <= 100)
	{
		return "A*";
	}
	else
	{
		return "Invalid";
	}
}

//Code self explanatory
//void WhoGotTheHighest(std::vector<Student>& objStudents) {
//
//	int iHighestGrade = objStudents.at(HighestGradeIndex(objStudents)).GetGrade();
//	int iLowestGrade = objStudents.at(LowestGradeIndex(objStudents)).GetGrade();
//	std::cout << "The person with the highest score is " << objStudents.at(HighestGradeIndex(objStudents)).GetName() << " who got " << iHighestGrade << std::endl;
//	std::cout << "The person with the lowest score is " << objStudents.at(LowestGradeIndex(objStudents)).GetName() << " who got " << iLowestGrade << std::endl;
//}

//Code self explanatory
int AddGrade(std::vector<Student>& objStudents) {

	int AddedGrade = 0;
	for (Student& objStudent : objStudents) {
		AddedGrade += objStudent.GetGrade();
	}
	return AddedGrade;
}
//Code self explanatory
double AverageGrade(std::vector<Student>& objStudents)
{
	return (double)AddGrade(objStudents) / objStudents.size();
}
//Code self explanatory
void DisplayGradeResult(std::vector<Student>& objStudents) {
	for (Student& Student : objStudents)
	{
		std::cout << "****" << std::endl;
		std::cout << "Student: " << Student.GetName() << std::endl;
		std::cout << "Has Student passed?: " << Student.HasUserPassed() << std::endl;
		std::cout << "Grade: " << Student.CalculateGradeLetter() << std::endl;
	}
	std::cout << std::endl;
}

void DisplayAverage(std::vector<Student>& objStudents)
{
	double dAverageGrade = AverageGrade(objStudents);
	std::cout << "Overall average grade is " << AverageGrade(objStudents) << " which is grade " << CalculateGradeLetter(dAverageGrade) << std::endl;
}

void AddStudent(std::vector<Student>& objStudents)
{
	std::string sName = "";
	int iGrade = 0;
	std::cout << "Enter student's name: ";
	std::cin >> sName;
	std::cout << "Enter student's grade: ";
	std::cin >> iGrade;
	objStudents.push_back({ sName, iGrade });
}

void TestData(std::vector<Student>& objStudents) {
	objStudents.push_back(Student("George", 1));
	objStudents.push_back(Student("Jack", 10));
	objStudents.push_back(Student("Josh", 40));
	objStudents.push_back(Student("Oli", 60));
	objStudents.push_back(Student("Josh", 80));
	objStudents.push_back(Student("Stephen", 100));
}
Student findHighestScoringStudent(const std::vector<Student>& students)
{
	int highestGrade = 0;
	Student HighestGradedStudent("", 0);
	for (const Student& s : students)
	{
		if (s.GetGrade() > highestGrade)
		{
			highestGrade = s.GetGrade();
			HighestGradedStudent = s;
		}
	}
	return HighestGradedStudent;
}
void DisplayHighestScorer(std::vector<Student>& objStudents) {
	Student HighestScoringStudent = findHighestScoringStudent(objStudents);
	std::cout << "The highest scorer is " << HighestScoringStudent.GetName() << " and got " << HighestScoringStudent.GetGrade();
}

void DisplayOverallResult(std::vector<Student>& objStudents) {
	DisplayAverage(objStudents);
	DisplayHighestScorer(objStudents);
}
int main()
{
	std::vector<Student>objStudents;
	//AddStudent(objStudents); //Manually add users here 
	TestData(objStudents); //Load test users without manually writing them
	DisplayGradeResult(objStudents);
	DisplayOverallResult(objStudents);
	
}