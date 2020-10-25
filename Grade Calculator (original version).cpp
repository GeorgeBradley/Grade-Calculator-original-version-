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
//std::size_t LowestGradeIndex(std::vector<Student>& objStudents)
//{
//	std::size_t stIndex = 0;
//	int iLowestGrade = INT_MAX;
//	for (std::size_t st = 0; st < objStudents.size(); st++) {
//		if (objStudents.at(st).GetGrade() < iLowestGrade)
//		{
//			iLowestGrade = objStudents.at(st).GetGrade();
//			stIndex = st;
//		}
//	}
//	return stIndex;
//}

//Through its parameters the average value is passed in to subsequently check its value with the if / else logic
/*std::string CalculateGradeLetter(double dAverage)
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
*/
//Code self explanatory
/*void WhoGotTheHighest(std::vector<Student>& objStudents) {

	int iHighestGrade = objStudents.at(HighestGradeIndex(objStudents)).GetGrade();
	int iLowestGrade = objStudents.at(LowestGradeIndex(objStudents)).GetGrade();
	std::cout << "The person with the highest score is " << objStudents.at(HighestGradeIndex(objStudents)).GetName() << " who got " << iHighestGrade << std::endl;
	std::cout << "The person with the lowest score is " << objStudents.at(LowestGradeIndex(objStudents)).GetName() << " who got " << iLowestGrade << std::endl;
}
*/

//Code self explanatory
/*int AddGrade(std::vector<Student>& objStudents) {

	int AddedGrade = 0;
	for (Student& objStudent : objStudents) {
		AddedGrade += objStudent.GetGrade();
	}
	return AddedGrade;
}*/

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
	for (const auto grade : objGrades) {
		if (iGrade <= grade.m_iGradeBoundary) {
			return grade.m_sGradeLetter;
		}
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