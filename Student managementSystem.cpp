#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
using namespace std;

//����ѧ��class
class Student {
private:
	string id;
	string major;
	string student_name;
public:
	//������
	Student() {
		id = "";
		major = "";
		student_name = "";
	}
	//������
	~Student() {
	}
	//����ѧ����Ϣ
	void SetStudent() {
		cout << "Major : ";
		cin >> this->major;
		cout << "Name : ";
		cin >> this->student_name;
	}
	//����ѧ��
	void SetId() {
		cout << "\nStudent number : ";
		cin >> this->id;
	}
	string GetId() {
		return this->id;
	}
	//����ѧ��
	void SetId(string id) {
		this->id = id;
	}
	//���ѧ����Ϣ
	void ShowStudent() {
		cout << "Student number : " << id;
		cout << "\nMajor : " << major;
		cout << "\nName : " << student_name << endl;
	}
	//��ʼ��ѧ����Ϣ
	void CleanStudent() {
		id = "";
		student_name = "";
		major = "";
	}
	bool operator==(string id) {
		if (this->id == id)
			return true;
		else
			return false;
	}
};

//ȫ��ѧ������Class
class StudentManage {
	friend class AllSubjectManage;
	friend class Menu;
protected:
	Student* StuList;
	int student_num;
	string id;
public:
	//������
	StudentManage() {
		student_num = 0;
		StuList = new Student[100];
		id = "";
	}
	//������
	~StudentManage() {
		delete[] StuList;
	}
	//��ѧ��ȷ��ѧ��
	int CheckId() {
		int a = 0;
		cout << "Student number : ";
		cin >> this->id;
		for (int i = 0; i < student_num; i++) {
			if (StuList[i] == id)
				a++;
		}
		return a;
	}
	//���ѧ��
	void StuInsert() {
		StuList[student_num].SetStudent();
		cout << "Added successfully " << endl << endl;
		student_num++;
		cout << "All students : " << student_num;
		cout << "\nPlease press any keys..." << endl;
	}
	//���ѧ��
	virtual void Insert() {
		if (student_num == 0) {
			StuList[student_num].SetId();
			StuInsert();
		}
		else {
			if (CheckId() == 0) {
				StuList[student_num].SetId(this->id);
				StuInsert();
			}
			else
				cout << "Already added student " << endl;
		}
	}
	//��ʾ�ض�ѧ��
	virtual void Show(int num) {
		StuList[num].ShowStudent();
	}
	//ѧ������
	virtual void List() {
		cout << endl << " < Student List > " << endl << endl;
		if (student_num == 0) {
			cout << "There isn't any information" << endl;
		}
		else {
			for (int i = 0; i < student_num; i++) {
				cout << i + 1 << " . ";
				StuList[i].ShowStudent();
				cout << endl;
			}
		}
	}
	//ѡ��ѧ��
	int Find(StudentManage* a) {
		a->List();
		int number = 0;
		while (true) {
			cout << "Enter student's roll number ( Enter 0 = Finish ) : ";
			cin >> number;
			if (number < 0 || number >(a->student_num)) {
				cout << "Please select again" << endl;
				continue;
			}
			else {
				return number;
				break;
			}
		}
	}
	//�޸�ѧ����Ϣ
	virtual void Change(int num) {
		int check = 0;
		do {
			check = CheckId();
			if (check == 0) {
				StuList[num - 1].SetId(id);
				StuList[num - 1].SetStudent();
				cout << "Modify Clear!";
			}
			else
				cout << "Already added student" << endl;
		} while (check != 0);

	}
	//ɾ����Ϣ
	virtual void Delete(int num) {
		StuList[num - 1].CleanStudent();
		cout << "Deleted successfully";
		student_num--;
	}
};

//���˳ɼ�Class
class Subject {
private:
	string subject_name; //�γ�����
	double sub_number; //�γ�ѧ��
	int score; //�ɼ�
	double num_grade; //�γ�GPA�ɼ�
	string subject_grade; //�ɼ�(A,B,C,D,F)
	double grade_sum; //ȫ�γ�GPA�ɼ���
public:
	//������
	Subject() {
		subject_name = "";
		sub_number = 0;
		score = 0;
		num_grade = 0;
		grade_sum = 0;
		subject_grade = "";
	}
	//������
	~Subject() {
	}
	void SetSubjectName(string subject_name) {
		this->subject_name = subject_name;
	}
	//����γ� 
	void SetSubject() {
		while (1) {
			cout << "Grade point(Max 5) : ";
			cin >> this->sub_number;
			if (sub_number > 0 && sub_number <= 5)
				break;
			else {
				cout << "The maximum grade point per subject is 5." << endl;
				continue;
			}
		}
	}
	//����ɼ�
	void SetScore() {
		do {
			cout << "Score : ";
			cin >> this->score;
			if (score >= 0 && score <= 100)
				break;
			else {
				cout << "The score between 0 and 100 points." << endl;
				continue;
			}
		} while (score < 0 || score > 100);
	}
	//��ȡÿ�ſγ�ѧ��
	double GetSubNumber() {
		return this->sub_number;
	}
	//����ɼ�
	void ShowScore() {
		cout << " Subject : " << setw(7) << this->subject_name;
		cout << " ( " << this->sub_number << " )" << endl;
		cout << "     Score : " << setw(4) << this->score << " | " << setw(4) << this->GetSubGrade() << endl;
	}
	//��ʼ��
	void CleanScore() {
		subject_name = "";
		sub_number = 0;
		score = 0;
		grade_sum = 0;
		num_grade = 0;
		subject_grade = "";
	}
	//GPA��ABCD��ʽ�ɼ�
	void CalcGrade() {
		if (score >= 95 && score <= 100) {
			subject_grade = "A+";
			num_grade = 4.5;
		}
		else if (score >= 90) {
			subject_grade = "A";
			num_grade = 4.0;
		}
		else if (score >= 85) {
			subject_grade = "B+";
			num_grade = 3.5;
		}
		else if (score >= 80) {
			subject_grade = "B";
			num_grade = 3.0;
		}
		else if (score >= 75) {
			subject_grade = "C+";
			num_grade = 2.5;
		}
		else if (score >= 70) {
			subject_grade = "C";
			num_grade = 2.0;
		}
		else if (score >= 65) {
			subject_grade = "D+";
			num_grade = 1.5;
		}
		else if (score >= 60) {
			subject_grade = "D";
			num_grade = 1.0;
		}
		else {
			subject_grade = "F";
			num_grade = 0.0;
		}
	}
	//��ȡ�ɼ�
	string GetSubGrade() {
		return subject_grade;
	}
	//ƽ�ɼ��ĺ�
	double SumGrade() {
		this->grade_sum = (double)this->sub_number * this->num_grade;
		return grade_sum;
	}
	bool operator==(string name) {
		if (this->subject_name == name)
			return true;
		else
			return false;
	}
};

//���˳ɼ�����Class
class SubjectManage {
private:
	int subject_num; //���ο�Ŀ��
	Subject* ScoList;
	string subject_name;
	double sub_sum; //��ѧ��
	double ave_grade; //GPA�ɼ�
public:
	//������
	SubjectManage() {
		subject_num = 0;
		ScoList = new Subject[subject_num + 1];
		sub_sum = 0;
		ave_grade = 0;
	}
	//������
	~SubjectManage() {
		delete[] ScoList;
	}
	//�����Ŀ��
	void SetSubjectNum() {
		while (1) {
			cout << "Enter the total courses you taken (Max 8): ";
			cin >> this->subject_num;
			if (subject_num >= 1 && subject_num <= 8)
				break;
			else {
				cout << "Exceed the number." << endl;
				continue;
			}
		}
	}
	//��ȡ��Ŀ��
	int GetSubjectNum() {
		return subject_num;
	}
	int CheckName() {
		cout << "Subject : ";
		cin >> this->subject_name;
		int a = 0;
		for (int i = 0; i < this->subject_num; i++) {
			if (ScoList[i] == subject_name)
				a++;
		}
		return a;
	}
	//����ɼ�
	void ScoreInsert(int sub) {
		sub = GetSubjectNum();
		ScoList = new Subject[sub + 1];
		for (int j = 0; j < sub;) {
			if (CheckName() == 0) {
				ScoList[j].SetSubjectName(this->subject_name);
				ScoList[j].SetSubject();
				ScoList[j].SetScore();
				ScoList[j].CalcGrade();
				cout << "Added successfully" << endl << endl;
				j++;
			}
			else
				cout << "Already added" << endl;
		}
		cout << "Completed your entry. " << endl;
	}
	//�޸ĳɼ���Ϣ
	void ScoreChange() {
		int num = 0;
		ScoreList();
		cout << "Enter subject number to modify : ";
		cin >> num;
		if (num >= 1 && num <= subject_num)
		{
			ScoList[num - 1].SetScore();
			ScoList[num - 1].CalcGrade();
			cout << "Modification completed" << endl;
		}
		else
			cout << "There are no information about that subjects. " << endl;
	}
	//ɾ����Ŀ
	void ScoreDelete() {
		int num = 0;
		ScoreList();
		cout << "Enter subject number to delete: ";
		cin >> num;
		if (num >= 1 && num <= subject_num)
		{
			ScoList[num - 1].CleanScore();
			cout << "Delete Completely" << endl;
			subject_num--;
			cout << "Total subject you taken : " << subject_num;
		}
		else
			cout << "There are no information about that subjects. " << endl;
	}
	//ɾ��ȫ���ɼ�
	void AllScoreDelete() {
		for (int i = 0; i < subject_num; i++) {
			ScoList[i].CleanScore();
		}
		subject_num = 0;
	}
	//�ɼ���
	void ScoreList() {
		CalcAveGrade();
		cout << endl << " < Score List > " << endl << endl;
		if (subject_num > 0) {
			for (int i = 0; i < subject_num; i++) {
				cout << i + 1 << " . ";
				ScoList[i].ShowScore();
				cout << endl;
			}
			cout << "----------------------------------------------" << endl;
			cout << " Total units :" << setw(3) << sub_sum;
			cout << " l GPA Score:" << fixed << setw(3) << setprecision(2) << ave_grade << endl << endl;
		}
		else
			cout << "There are no registered grades." << endl;
	}
	//ƽ��GPA�ɼ�
	void CalcAveGrade() {
		double sub = 0;
		for (int i = 0; i < subject_num; i++)
			sub += ScoList[i].GetSubNumber();
		sub_sum = sub;

		double sumgrade = 0;
		if (sub_sum > 0) {
			for (int i = 0; i < subject_num; i++)
				sumgrade += ScoList[i].SumGrade();

			ave_grade = sumgrade / sub_sum;
		}
		else
			ave_grade = 0.0;
	}
	//���ƽ��GPA�ɼ�
	double GetAveGrade() {
		return ave_grade;
	}
};
//ȫ�����Class
class AllSubjectManage : public StudentManage {
private:
	double* Sco_grade;
	SubjectManage* Sco;
public:
	//������
	AllSubjectManage() {
		Sco = new SubjectManage[100];
		Sco_grade = new double[100];
	}
	//������
	~AllSubjectManage() {
		delete[] Sco;
		delete[] Sco_grade;
	}
	//����ɼ�
	void Insert(int num) {
		if (num == 0)
			cout << "Go out";
		else if (Sco[num - 1].GetSubjectNum() == 0) {
			Sco[num - 1].SetSubjectNum();
			Sco[num - 1].ScoreInsert(Sco[num - 1].GetSubjectNum());
			Sco[num - 1].CalcAveGrade();
		}
		else
			cout << "There is already a grade entered. " << endl;
	}
	//���˳ɼ���ѯ
	void Show(int num) {
		Sco[num].ScoreList();
	}
	//�޸ĳɼ�
	void Change(int num) {
		if (num == 0)
			cout << "Go out";
		else if (Sco[num - 1].GetSubjectNum() != 0) {
			Sco[num - 1].ScoreChange();
			Sco[num - 1].CalcAveGrade();
		}
		else
			cout << "There are no registered grades." << endl;
	}
	//ɾ���ɼ�
	void Delete(int num) {
		if (num == 0)
			cout << "Go out";
		else if (Sco[num - 1].GetSubjectNum() != 0) {
			Sco[num - 1].ScoreDelete();
			Sco[num - 1].CalcAveGrade();
		}
		else
			cout << "There are no registered grades." << endl;
	}
	//ɾ��ȫ���ɼ�
	void AllDelete(int num) {
		Sco[num - 1].AllScoreDelete();
	}
	void swap(double* a, double* b) {
		double temp;
		temp = *a;
		*a = *b;
		*b = temp;
	}
	void swap(Student* a, Student* b) {
		Student temp;
		temp = *a;
		*a = *b;
		*b = temp;
	}
	//����
	void bubble_sort(bool tf, double grade[], Student Stu[], int n) {
		for (int i = 0; i < n; i++) {
			tf = false;
			for (int j = i; j < n; j++) {
				if (grade[i] < grade[j]) {
					swap(&grade[i], &grade[j]);
					swap(&Stu[i], &Stu[j]);
					tf = true;
				}
			}
			if (!tf)
				break;
		}
	}
	//����
	void Rank(StudentManage* a) {
		for (int i = 0; i < (a->student_num); i++) {
			this->Sco_grade[i] = this->Sco[i].GetAveGrade();
		}
		cout << " < Rank List > " << endl;
		Student* Stu = new Student[100];
		for (int i = 0; i < 100; i++) {
			Stu[i] = (a->StuList[i]);
		}
		bubble_sort(false, Sco_grade, Stu, 100);
		for (int i = 0; i < (a->student_num); i++)
			cout << i + 1 << "." << " Student number:" << Stu[i].GetId()
			<< "l Score:" << this->Sco_grade[i] << endl;
	}
};

//Menu Class
class Menu {
private:
	StudentManage* stu_manager;
	AllSubjectManage* sco_manager;
public:
	//������
	Menu() {
		stu_manager = new StudentManage;
		sco_manager = new AllSubjectManage;
	}
	//������
	~Menu() {
		delete stu_manager;
		delete sco_manager;
	}
	//��menu����
	void MainMenu()
	{
		system("cls");
		cout << " < MAIN MENU > " << endl;
		cout << "\n1. Student management" << endl;
		cout << "2. Score management" << endl;
		cout << "3. Finish this program" << endl;

	}
	//ѧ������menu
	int StudentMenu() {
		int num = 0;

		system("cls");
		cout << "1. Add student" << endl;
		cout << "2. Modify information" << endl;
		cout << "3. Delete student" << endl;
		cout << "4. All student record" << endl;
		cout << "5. Back to main menu" << endl;
		cout << endl;
		cout << "Please select your choice(1-5) : ";
		cin >> num;

		return num;
	}
	//ѡ��ѧ��menu
	void StudentSelect() {
		int num = 0;
		int del = 0;
		int cha = 0;
		while ((num = StudentMenu()) != 5) {
			switch (num) {
			case 1:
				stu_manager->Insert();  //����ѧ�����⺯��
				break;
			case 2:
				cha = stu_manager->Find(stu_manager);
				if (cha == 0) {
					cout << "Go out";
					break;
				}
				else {
					stu_manager->Change(cha);   //����ѧ���޸ĺ���
					break;
				}
			case 3:
				del = stu_manager->Find(stu_manager);
				if (del == 0) {
					cout << "Go out";
					break;
				}
				else {
					stu_manager->Delete(del); //����ѧ��ɾ������
					sco_manager->AllDelete(del);
					break;
				}
			case 4:
				stu_manager->List();  //����ѧ���б���
				break;
			default:
				cout << "Please select again ";
			}
			_getch();
		}
	}
	//�ɼ�����menu
	int SubjectMenu() {
		int num = 0;

		system("cls");
		cout << "1. Enter score" << endl;
		cout << "2. Modifying and deleting grades" << endl;
		cout << "3. Score Report" << endl;
		cout << "4. Rank List" << endl;
		cout << "5. Back to main menu" << endl;
		cout << endl;
		cout << "Please select your choice(1-5): ";
		cin >> num;

		return num;
	}
	//ѡ��ɼ�menu
	void SubjectSelect() {
		int a, b, c, d;
		a = b = c = d = 0;
		int num1, num2, num3;
		num1 = num2 = num3 = 0;
		while ((num1 = SubjectMenu()) != 5) {
			if ((stu_manager->student_num) > 0) {
				switch (num1) {
				case 1: //����ɼ�
					a = sco_manager->Find(stu_manager);
					sco_manager->Insert(a);  //���óɼ���Ӻ���
					break;
				case 2: //ɾ���ɼ��޸�
					SelectSecond();
					break;
				case 3: //�ɼ���ѯ
					SelectThird();
					break;
				case 4:
					sco_manager->Rank(stu_manager);//�������б���
					break;
				default:
					cout << "Please select again ";
				}
			}
			else {
				cout << "There are no enrolled students.";
			}
			_getch();
		}
	}
	//2.�ɼ��޸ļ�ɾ��
	int SubSecond() {
		int num = 0;
		system("cls");
		cout << "1. Score modify " << endl;
		cout << "2. Score delete " << endl;
		cout << "3. Back to main menu " << endl;
		cout << "Please select your choice(1-3) : ";
		cin >> num;
		return num;
	}
	//ѡ��ڶ�
	void SelectSecond() {
		int sel = 0;
		int num = 0;
		while ((num = SubSecond()) != 3) {
			switch (num) {
			case 1:
				sel = sco_manager->Find(stu_manager);
				sco_manager->Change(sel); //���óɼ�У������
				break;
			case 2:
				sel = sco_manager->Find(stu_manager);
				sco_manager->Delete(sel); //���óɼ�ɾ������
				break;
			default:
				cout << "Please select again ";
			}
			_getch();
		}
	}
	//3.�ɼ���ѯ
	int SubThird() {
		int num = 0;
		system("cls");
		cout << "1. All student's score " << endl;
		cout << "2. Student's score (one by one) " << endl;
		cout << "3. Back to main menu " << endl;
		cout << "Please select your choice(1 - 3) : ";
		cin >> num;
		return num;
	}
	//ѡ�����
	void SelectThird() {
		int sel = 0;
		int num = 0;
		while ((num = SubThird()) != 3) {
			switch (num) {
			case 1:
				cout << endl;
				for (int i = 0; i < (stu_manager->student_num); i++) {
					cout << i + 1 << " . ";
					stu_manager->Show(i);
					sco_manager->Show(i);
					cout << endl;
				}
				break;
			case 2:
				sel = sco_manager->Find(stu_manager);
				cout << endl;
				if (sel == 0) {
					cout << "Go out";
					break;
				}
				else {
					stu_manager->Show(sel - 1);
					cout << endl;
					sco_manager->Show(sel - 1); //���óɼ�������
					break;
				}
			default:
				cout << "Please select again " << endl;
			}
			_getch();
		}
	}
};

//main����
int main() {
	int choice = 0;
	Menu a;

	while (true) {
		a.MainMenu();
		cout << endl << "Please select choice: ";
		cin >> choice;

		if (choice == 1)
			a.StudentSelect();
		else if (choice == 2)
			a.SubjectSelect();
		else if (choice == 3) {
			cout << "Finish this program" << endl;
			break;
		}
		else {
			cout << "Please select again " << endl;
			_getch();
		}
	}
	return 0;
}
