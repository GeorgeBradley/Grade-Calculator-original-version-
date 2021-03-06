// Grade Calculator (original version).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
struct Grade {
	std::string m_sGradeLetter;
	int m_iGradeBoundary;
	Grade(std::string sGradeLetter, int iGradeBoundary)
		: m_iGradeBoundary(iGradeBoundary),m_sGradeLetter(sGradeLetter)
	{
	}
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
};

//Implementations for the "Student" class
Student::Student(std::string sName, int iGrade) :m_sName(sName), m_iGrade(iGrade) {}
std::string Student::GetName() const {
	return m_sName;
}

int Student::GetGrade() const {
	return m_iGrade;
}
std::string DidStudentPass(int iGrade) {
	return (iGrade > 70) ? "Yes" : "No";
}
//Code self explanatory
double AverageGrade(const std::vector<Student>& objStudents)
{
	//return (double)AddGrade(objStudents) / objStudents.size();
	auto sum = std::transform_reduce(objStudents.begin(), objStudents.end(), 0.0, std::plus<>(), 
		[](auto& student) { return student.GetGrade(); });
	return sum / objStudents.size();
}
std::string CalculateGradeLetter(const double iGrade, const std::vector<Grade>& objGrades)
{
	auto it = std::find_if(objGrades.begin(), objGrades.end(), [&](auto& objGrade) {return iGrade <= objGrade.m_iGradeBoundary; });
	if (it != objGrades.end()) {
		return it->m_sGradeLetter;
	}
	return "Unknown";
}
//Code self explanatory
void DisplayGradeResult(const std::vector<Student>& objStudents, const std::vector<Grade>& objGrades) {
	for (const Student& Student : objStudents)
	{
		std::cout << "****\n";
		std::cout << "Student: " << Student.GetName() << "\n";
		std::cout << "Grade: " << CalculateGradeLetter(Student.GetGrade(),objGrades) << "\n";
		std::cout << "Did student pass?: " << DidStudentPass(Student.GetGrade()) << "\n";
	}
	std::cout << std::endl;
}

void DisplayAverage(const std::vector<Student>& objStudents, const std::vector<Grade>& objGrades)
{
	double dAverageGrade = AverageGrade(objStudents);
	std::cout << "Overall average grade is " 
		<< AverageGrade(objStudents) 
		<< " which is grade " <<  CalculateGradeLetter(dAverageGrade, objGrades) << "\n";
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
	objStudents.emplace_back(Student("George", 1 ));
	objStudents.emplace_back(Student("Jack", 10));
	objStudents.emplace_back(Student("Josh", 40));
	objStudents.emplace_back(Student("Oli", 60));
	objStudents.emplace_back(Student("Josh", 80));
	objStudents.emplace_back(Student("Stephen", 100));
}
//Student findHighestScoringStudent( std::vector<Student>& students)
//{
//	int highestGrade = 0;
//	Student HighestGradedStudent("", 0);
//	for (const Student& s : students)
//	{
//		if (s.GetGrade() > highestGrade)
//		{
//			highestGrade = s.GetGrade();
//			HighestGradedStudent = s;
//		}
//	}
//	return HighestGradedStudent;
//}

void DisplayLowestHighestScoringStudent( std::vector<Student>& objStudents)
{
	/*int iLowestGrade = INT_MAX;
	Student objLowestGradedStudent("", 0);*/
	/*for (const Student& objStudent : students)
	{
		if (objStudent.GetGrade() < iLowestGrade)
		{
			iLowestGrade = objStudent.GetGrade();
			objLowestGradedStudent = objStudent;
		}
	}
	return objLowestGradedStudent;
	*/
	auto [lowest, highest] = std::minmax_element(objStudents.begin(), objStudents.end(), 
		[](auto& a, auto& b) {
		return a.GetGrade() < b.GetGrade();
		});
	std::cout << "Highest scorer is " << highest->GetName() << " who got " << highest->GetGrade() << "\n";
	std::cout << "Lowest scorer is " << lowest->GetName() << " who got " << lowest->GetGrade() << "\n";
}

//void DisplayHighestScorer(std::vector<Student>& objStudents) 
//{
//	Student HighestScoringStudent = findHighestScoringStudent(objStudents);
//	std::cout << "The highest scorer is " << HighestScoringStudent.GetName() << " and got " << HighestScoringStudent.GetGrade() << std::endl;
//}

//void DisplayLowestScorer(std::vector<Student>& objStudents) 
//{
//	Student objLowestScoringStudent = findLowestScoringStudent(objStudents);
//	std::cout << "The lowest scorer is " << objLowestScoringStudent.GetName() << " and got " << objLowestScoringStudent.GetGrade() << std::endl;
//}

void DisplayOverallResult(std::vector<Student>& objStudents, const std::vector<Grade>& objGrades) 
{
	DisplayAverage(objStudents, objGrades);
	DisplayLowestHighestScoringStudent(objStudents);
	//DisplayLowestScorer(objStudents);
}

void SetGradeBoundaries(std::vector<Grade>& objGrades)
{
	objGrades.emplace_back(Grade("F", 10));
	objGrades.emplace_back(Grade("E", 30));
	objGrades.emplace_back(Grade("D", 50));
	objGrades.emplace_back(Grade("C", 70));
	objGrades.emplace_back(Grade("B", 80));
	objGrades.emplace_back(Grade("A", 90));
	objGrades.emplace_back(Grade("A*", 100));
}

int main()
{
	std::vector<Student>objStudents;
	std::vector<Grade>objGrades;
	SetGradeBoundaries(objGrades);
	//AddStudent(objStudents); //Manually add users here 
	TestData(objStudents); //Load test users without manually writing them
	DisplayGradeResult(objStudents, objGrades);
	DisplayOverallResult(objStudents, objGrades);
}