/*
	*COMPUTER SCIENCE - C++ PROJECT
	*CLASS - XII (SESSION 2019-2020)
	*HOSPITAL MANAGEMENT SYSTEM
	*PROJECT DONE BY:
		1. CALVIA ELIZA SHAJI
		2. SAJAL SAHU
		3. VINAYAK MAHADEVAN
	*PROJECT DESCRIPTION:
		THE PROJECT "HOSPITAL MANAGEMENT SYSTEM" IS A PROJECT FOR MANAGING THE PATIENT AND DOCTOR RECORDS IN A HOSPITAL
*/

/*Includes all the headerfiles required for the project*/
using namespace std;

#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <windows.h>

/*Declaring the file pointers*/
ofstream a1, a2, a3;
ifstream b1, b2, b3;

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.dwCursorPosition.Y;
}

/*Class HOSPITAL is a class containing the data members and member functions associated with the system*/
class HOSPITAL
{
	/*Private data members and member functions*/
	int n_lt;
	int age;
	int stay_days;
	int med_qty[10];
	float cons_charge;
	float pt_stay_price;
	float tpc_labtest;
	float amount_med;
	float total_med;
	float total_bill;
	float disc_amt;
	float final_bill;
	float pc_labtest[10];
	float individual_price[10];
	char md_pmt;
	char gender;
	char phone[10];
	char pt_room[10];
	char dept[20];
	char name[20];
	char dname[30];
	char address[50];
	char nm_labtest[10][20];
	char med[10][20];
	void total_bill_calc();
	void md_payment();

public:
	/*Constructor for class HOSPITAL*/
	HOSPITAL()
	{
		n_lt = 0;
		age = 0;
		stay_days = 1;
		cons_charge = 0;
		pt_stay_price = 0;
		tpc_labtest = 0;
		amount_med = 0;
		total_med = 0;
		total_bill = 0;
		disc_amt = 0;
		final_bill = 0;
		md_pmt = '\0';
		gender = '\0';
		for (int i = 0; i < 10; i++)
		{
			med_qty[i] = 0;
			pc_labtest[i] = 0;
			individual_price[i] = 0;
			phone[i] = '\0';
			pt_room[i] = '\0';

			for (int j = 0; j < 20; j++)
			{
				nm_labtest[i][j] = '\0';
				med[i][j] = '\0';
			}
		}

		for (int i = 0; i < 50; i++)
		{
			if (i < 20)
			{
				dept[i] = '\0';
				name[i] = '\0';
			}

			if (i < 30)
			{
				dname[i] = '\0';
			}

			address[i] = '\0';
		}
	}
	/*public member functions*/
	void pt_info();
	void room();
	void print_bill(char ch_lab, char ch_med, char ch_ptm, char ch_cc);
	void MEDICINE();
	void LABTEST();
	void ip(int records, int choice);
	void doc_details(int records);
	void dept_list(int records, char(&dep)[60][20], int& departments);
	void find_doc(char dep[60][20], int choice, int records);
	void add_doc(int& records);
	void del_doc(int& records, int choice);
	void op();
};

/*Member function to calculate total price*/
void HOSPITAL::total_bill_calc()
{
	total_bill = tpc_labtest + (cons_charge * stay_days) + total_med + pt_stay_price + (pt_stay_price / 10);
}

/*Member function to calculate price after discount*/
void HOSPITAL::md_payment()
{
	while (1)
	{
		cout << "\n Enter Payment Mode ";
		cout << "\n Press 'c' for Cash payment | Press 'd' for card payment";
		cout << "\n Input :";
		cin >> md_pmt;
		if (md_pmt == 'c' || md_pmt == 'C')
		{
			disc_amt = 7.5 * total_bill / 100;
			final_bill = total_bill - disc_amt;
			break;
		}
		if (md_pmt == 'd' || md_pmt == 'D')
		{
			disc_amt = 0.0;
			final_bill = total_bill - disc_amt;
			break;
		}
		else
		{
			cout << "\n Invalid input please enter again.";
			continue;
		}
	}
}

/*Member function to select the type of room and calculate the accommodation fee based of number of days stayed*/
void HOSPITAL::room()
{
	char rooms[4][20] = {
				{"General Ward"},
				{"Semi Private"},
				{"Private"},
				{"Delux"}
	};
	int price_rooms[4] = { 500,1000,2000,5000 };
	int ch = 0;
	while (1)
	{
		cout << "\n* PATIENT ADMISSION *";
		cout << "\n Available Rooms ";
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << "." << rooms[i] << endl;
		}
		cin >> ch;
		if (ch >= 1 && ch <= 4)
		{
			break;
		}
		else
		{
			cout << endl << "Invalid input. Enter Again.";
			continue;
		}
	}
	cout << "\n Enter No of days stayed : ";
	cin >> stay_days;
	ch -= 1;
	strcpy_s(pt_room, rooms[ch]);
	pt_stay_price = price_rooms[ch];
	pt_stay_price *= stay_days;
}

/*Member function to enter details of the patient*/
void HOSPITAL::pt_info()
{
	cout << "\n Enter details of patient.";
	cout << "\n 1. Name : ";
	fflush(stdout);
	getchar();
	cin.getline(name, 20);
	while (1)
	{
		cout << "\n 2. Age : ";
		cin >> age;
		if (age > 0 && age <= 200) break;
		else { cout << "\n Enter a Valid age.";  continue; }
	}
	while (1)
	{
		cout << "\n 3. Gender : 'F' Female ";
		cout << "\n \t: 'M' FOR Male";
		cout << "\n \t: 'O' FOR Others";
		cout << "\n Input  : ";
		cin >> gender;
		if (gender == 'O' || gender == 'o' || gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f')
		{
			break;
		}
		else
		{
			cout << "\n Invalid Gender.";
			cout << "\n Enter Again." << endl;
		}
	}
	cout << "\n 4. Address : ";
	fflush(stdout);
	getchar();
	cin.getline(address, 50);
	while (1)
	{
		cout << "\n 5. Contact : ";
		cin >> phone;
		_getch();
		int x;
		for (x = 0; strlen(phone) < 10; x++)
		{
			if (isdigit(phone[x])) continue;
			else { x = -1; break; }
		}

		if (x == -1)
		{
			cout << "\n Please Enter valid digits.";
			continue;
		}
		else break;
	}
}

/*Member function to select the required labtests and calculate the labtest fee*/
void HOSPITAL::LABTEST()
{

	int sl_lt = 0;
	int pc_avail_labtest[5] = { {100},
					{200},
					{150},
					{250},
					{300}
	};
	int i = 0;
	char avail_labtest[5][15] = {
					{"Blood Test"},
					{"Endoscopy"},
					{"MRI"},
					{"ECG"},
					{"X-Ray"}
	};
	int choice = 0;
	cout << "\n Enter No.of test(s) to be done : ";
	cin >> n_lt;
	while (i < n_lt)
	{
		while (1)
		{
			system("cls");
			cout << "\n\t\t*----- Available test's -----*";
			cout << "\n\t\t------------------------------";
			cout << "\n\t\t|Srn.|      Name     | Price |";
			cout << "\n\t\t------------------------------";
			for (int a = 0; a < 5; a++)
			{
				int s = strlen(avail_labtest[a]);
				s = 17 - s;
				cout << "\n\t\t| " << a + 1 << ". | " << avail_labtest[a] << "  " << setw(s) << "|  " << pc_avail_labtest[a] << "  |";
			}
			cout << "\n\t\t------------------------------";
			cout << "\n\t\t| Enter Code : ";
			cin >> choice;
			if (choice >= 1 && choice <= 5)
			{
				break;
			}
			else
			{
				cout << "\n Invalid code, Enter again.";
				continue;
			}
		}

		sl_lt = choice - 1;
		strcpy_s(nm_labtest[i], avail_labtest[sl_lt]);
		pc_labtest[i] = pc_avail_labtest[sl_lt];
		tpc_labtest += pc_labtest[i];
		i++;

	}
}

/*Member function to print the bill*/
void HOSPITAL::print_bill(char ch_lab, char ch_med, char ch_ptm, char ch_cc)
{
	char date[9];
	_strdate_s(date);
	total_bill_calc();
	md_payment();
	system("cls");
	_getch();
	cout << "\n\t\t\t CVS HOSPITAL ";
	cout << "\n\t\tIS Sohar,Al Hambar,www.cvshospitals.com";
	cout << "\n -------------------------------------------------------";
	int s = strlen(name);
	if (age < 10)
		s = 39 - strlen(name);
	if (age >= 100)
		s = int (37 - strlen(name));
	else if ((age < 100) && (age >= 10))
		s = 38 - strlen(name);
	name[0] = toupper(name[0]);
	if (islower(gender)) gender -= 32;
	cout << "\n | Patient       | " << name << ", " << gender << ", " << age << setw(s) << "| Date : " << date;
	s = 37 - strlen(address);
	cout << "\n | Address	 | " << address << setw(s) << "|";
	cout << "\n ------------------------------------------------------" << endl;
	int sr = 1;
	cout << "----------------------------------------------------------";
	cout << endl << "| Particulars			      | qty | prc | amt |";
	cout << endl << "|-------------------------------------------------------|";
	if (ch_ptm == 'Y')
	{

		cout << "\n|" << sr << ". Accommodation: " << pt_room << setw(20 - strlen(pt_room)) << "|" << stay_days << "   |" << pt_stay_price / stay_days << " |" << pt_stay_price << "|";  sr++;
		cout << "\n|" << sr << ". Hospital Charges                  |     |     |" << pt_stay_price / 10 << " |"; sr++;
	}
	if ((ch_lab == 'Y') || (ch_lab == 'y'))
	{
		cout << "\n|" << sr << ". Labtest:                          |     |     |     |";
		for (int k = 0; k < n_lt; k++)
		{

			cout << "\n|   " << k + 1 << "." << nm_labtest[k] << setw(45 - strlen(nm_labtest[k])) << "|     |     |" << pc_labtest[k] << "  |";
		}
		sr++;
	}
	if ((ch_med == 'Y') || (ch_med == 'y'))
	{
		cout << "\n|" << sr << ". Medicines:                        |     |     |     |";
		for (int k = 0; k < amount_med; k++)
		{
			cout << "\n|   " << k + 1 << "." << med[k] << setw(33 - strlen(med[k])) << "|" << med_qty[k] << "    |" << individual_price[k] << "  |" << med_qty[k] * individual_price[k] << "  |";
		}
		sr++;
	}
	if (ch_cc == 'Y')
	{
		cout << "\n|" << sr << ". Cons Charges: " << dname << setw(21 - strlen(dname)) << "|" << cons_charge << "  |     |" << cons_charge * stay_days << "  |";
		sr++;
	}
	cout << "\n----------------------------------------------------------";
	cout << "\n TOTAL : " << total_bill;
	cout << "\n DISC  : " << disc_amt;
	cout << "\n FINAL : " << final_bill;
	fflush(stdout);
	_getch();
}

/*Member function to enter the required medicines and calculate the medicine fee*/
void HOSPITAL::MEDICINE()
{
	cout << "\n ENTER HOW MANY MEDICINES - ";
	cin >> amount_med;
	for (int q = 0; q < amount_med; q++)
	{
		cout << "\n\n ENTER NAME OF MEDICINE " << q + 1 << ":";
		fflush(stdout);
		getchar();
		cin.getline(med[q], 20);
		cout << "\n  ENTER ITS PRICE - ";
		cin >> individual_price[q];
		cout << "\n ENTER QUANTITY - ";
		cin >> med_qty[q];
		total_med += individual_price[q] * med_qty[q];

	}
}

/*Member function to display the details of all doctors in the hospital*/
void HOSPITAL::doc_details(int records)
{
	system("cls");
	cout << "   DOCTOR";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {34, short(wherey())});
	//gotoxy(34, wherey());
	cout << "DEPARTMENT";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {54, short(wherey())});
	//gotoxy(54, wherey());
	cout << "CHARGE";
	for (int i = 0; i < records; i++)
	{
		b1.getline(dname, 30);
		b2.getline(dept, 20);
		b3 >> cons_charge;
		cout << "\n\n" << i + 1 << ". " << dname;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {34, short(wherey())});
		//gotoxy(34, wherey());
		cout << dept;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {54, short(wherey())});
		//gotoxy(54, wherey());
		cout << cons_charge;
	}
	_getch();
}

/*Member function to display all departments available in the hospital*/
void HOSPITAL::dept_list(int records, char(&dep)[60][20], int& departments)
{
	departments = 0;
	for (int i = 0; i < records; i++)
	{
		b2.getline(dept, 20);
		int found = 0;
		for (int j = 0; j < departments; j++)
		{
			if (_strcmpi(dept, dep[j]) == 0)
			{
				found = 1;
			}
		}
		if (found == 0)
		{
			cout << endl << departments + 1 << ". " << dept;
			strcpy_s(dep[departments], dept);
			departments++;
		}
	}
	fflush(stdout);
	_getch();
}

/*Member function to display all doctors in a particular department*/
void HOSPITAL::find_doc(char dep[60][20], int choice, int records)
{
	system("cls");
	char ch[20];
	int n = 1;
	strcpy_s(ch, dep[choice - 1]);
	for (int i = 0; i < records; i++)
	{
		b1.getline(dname, 30);
		b2.getline(dept, 20);
		b3 >> cons_charge;
		if (_strcmpi(dept, ch) == 0)
		{
			if (n == 1)
			{
				cout << "   DOCTOR";
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {34, short(wherey())});
				//gotoxy(34, wherey());
				cout << "CHARGE";
			}
			cout << "\n\n" << n << ". " << dname;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {34, short(wherey())});
			//gotoxy(34, wherey());
			cout << cons_charge;
			n++;
		}
	}
	fflush(stdout);
	_getch();
}

/*Member function to add a doctor to the list of doctors in the hospital*/
void HOSPITAL::add_doc(int& records)
{
	char name[30], dep[20];
	int choice, found = 0;
	getchar();
	cout << "\nEnter Doctor's Name: ";
	fflush(stdin);
	cin.getline(dname, 30);
	cout << "Enter Department: ";
	fflush(stdout);
	cin.getline(dept, 20);
	cout << "Enter Consultation Charge: ";
	cin >> cons_charge;
	b1.seekg(0);
	b2.seekg(0);
	for (int j = 0; j < records; j++)
	{
		b1.getline(name, 30);
		b2.getline(dep, 20);
		if ((_strcmpi(dname, name) == 0) && (_strcmpi(dept, dep) == 0))
		{
			found = 1;
		}
	}
	if (found == 1)
	{
		cout << "\nDoctor with same name already exists in the department.\nDo you still want to addnew record?\n(Enter 1 if yes and 2 if no): ";
		for (;;)
		{
			cin >> choice;
			if ((choice == 1) || (choice == 2))
				break;
			else
				cout << "\nInvalid choice. Enter input again: ";
		}
	}
	if ((found == 0) || ((found == 1) && (choice == 1)))
	{
		a1 << dname << endl;
		a2 << dept << endl;
		a3 << cons_charge << endl;
		records++;
		cout << "\nThe record has been added";
	}
	fflush(stdout);
	_getch();
}

/*Member function to delete a doctor from the list of doctors in the hospital*/
void HOSPITAL::del_doc(int& records, int choice)
{
	for (int i = 0; i < records; i++)
	{
		b1.getline(dname, 30);
		b2.getline(dept, 20);
		b3 >> cons_charge;
		if ((i + 1) != choice)
		{
			a1 << dname << endl;
			a2 << dept << endl;
			a3 << cons_charge << endl;
		}
	}
	records--;
}

/*Member function the select the required doctor*/
void HOSPITAL::ip(int records, int choice)
{
	for (int i = 0; i < records; i++)
	{
		b1.getline(dname, 30);
		b2.getline(dept, 20);
		b3 >> cons_charge;
		if ((i + 1) == choice)
		{
			break;
		}
	}
}

/*Member function to display the dtails of the selected doctor*/
void HOSPITAL::op()
{
	cout << "\nDoctor: " << dname;
	cout << "\nDepartment: " << dept;
	cout << "\nConsultation Charge: " << cons_charge;
}

/*Fucntion to confirm if any labtest is required*/
char labtest_required(char ch)
{
	while (1)
	{
		cout << "\n Labtest Required?";
		cout << "\n Enter 'Y' - Yes, 'N' -No.";
		cout << "\n Choice : ";
		cin >> ch;

		if (ch == 'Y' || ch == 'N' || ch == 'y' || ch == 'n') break;
		else
		{
			cout << "\n Invalid Input.";
			continue;
		}
	}
	return ch;
}

/*Function to confirm if any medicine is required*/
char med_required(char ch)
{
	while (1)
	{
		cout << "\n Medicines Required?";
		cout << "\n Enter 'Y' - Yes, 'N' -No.";
		cout << "\n Choice : ";
		cin >> ch;
		if (ch == 'Y' || ch == 'N' || ch == 'y' || ch == 'n') break;
		else
		{
			cout << "\n Invalid Input.";
			continue;
		}
	}
	return ch;
}

/*Function to display program loading*/
void line_prt()
{
	int dlay = 25;

	//delay(dlay);
	cout << "\n\t\t\t|------------------------------|";
	//delay(dlay);
}

/*Function to display homepage after program loads*/
void print()
{
	int i = 0, j = 0;
	int p = 1;  int z = 0;
	char bar[50] = { "|||||||||||||||||||||||||" };
	for (i; i < 25; i++, p += 4.5)
	{
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl << endl;
		cout << "\n\t\t\t\t CVS  HOSPITAL ";
		cout << "\n\t\t\t\t  LOADING " << p << "%";
		cout << "\n\t\t\t |------------------------|" << endl;
		cout << "\t\t\t |";
		for (j = 0; j < i; j++)
		{
			cout << bar[j];
			//delay(5);
		}
		cout << endl;
	}
	cout << "|";
	system("cls");
	cout << endl << endl;
	cout << "\n\n\n\t\t\t           CVS HOSPITAL	\t";
	//delay(25);
	cout << "\n\t\t\t*------------------------------*";
	//delay(25);
	cout << endl << "\t\t\t|\t     MENU    	       |";
	cout << "\n\t\t\t|1.|	OPD		       |";
	line_prt();
	cout << "\n\t\t\t|2.|	PATIENT ADMISSION      |";
	line_prt();
	cout << "\n\t\t\t|3.|	LAB-TEST	       |";
	line_prt();
	cout << "\n\t\t\t|4.|	MEDICINE	       |";
	line_prt();
	cout << "\n\t\t\t|5.|	DOCTOR MANAGEMENT      |";
	line_prt();
	cout << "\n\t\t\t|6.|	EXIT.		       |";
	line_prt();
	cout << "\n\t\t\t|SELECT = ";
}

int main()
{
	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;
	system("cls");
	char line[30], dept_list[60][20];
	b1.open("doc.txt", ios::in);
	int records = 0, departments;
	/*Loop to calculate the number of doctors available in the hospital*/
	while (!b1.eof())
	{
		b1.getline(line, 30);
		records++;
	}
	records--;
	b1.close();
	for (;;)
	{
		HOSPITAL h;
		int select = 0;
		char ch_lab = 'N';
		char ch_ptm = 'N';
		char ch_med = 'N';
		char ch_cc = 'N';
		int ch_doc = 0;
		/*Loop to display the available management choices and select the required one*/
		while (1)
		{
			print();
			cin >> select;
			if (select >= 1 && select <= 6)
				break;
			else
			{
				cout << "\n Invalid Input.";
				continue;
			}
		}
		int ch1;
		switch (select)
		{

			/*Case for printing an OPD bill*/
			case 1:
				cout << "\n\t\t* OPD DEPARTMENT * ";
				system("cls");
				b1.open("doc.txt", ios::in);
				b2.open("dept.txt", ios::in);
				b3.open("charge.txt", ios::in);
				h.pt_info();

				while (1)
				{
					h.doc_details(records);
					b1.seekg(0);
					b2.seekg(0);
					b3.seekg(0);
					cout << "\nEnter your choice: ";
					cin >> ch1;
					_getch();
					if (ch1 >= 1 && ch1 <= records)
						break;
					else
					{
						cout << "\n Invalid Input Enter Again";
						continue;
					}
				}
				h.ip(records, ch1);
				b1.close();
				b2.close();
				b3.close();
				system("cls");
				ch_lab = labtest_required(ch_lab);
				if (ch_lab == 'Y' || ch_lab == 'y')
				{
					h.LABTEST();
				}
				ch_med = med_required(ch_med);
				if (ch_med == 'Y' || ch_med == 'y')
				{
					h.MEDICINE();
				}
				//delay(100);
				ch_cc = 'Y';
				h.print_bill(ch_lab, ch_med, ch_ptm, ch_cc);
				break;

				/*Case for printing bill in case the patient is admiited in the hospital*/
			case 2:
				system("cls");
				cout << "\n*\t\t PATIENT ADMISSION \t\t*";
				h.pt_info();
				system("cls");
				cout << "\n Please select the type of room . ";
				h.room();
				system("cls");
				int choice;
				b1.open("doc.txt", ios::in);
				b2.open("dept.txt", ios::in);
				b3.open("charge.txt", ios::in);
				system("cls");
				h.doc_details(records);
				b1.seekg(0);
				b2.seekg(0);
				b3.seekg(0);
				cout << "\nEnter your choice: ";
				cin >> choice;
				h.ip(records, choice);
				b1.close();
				b2.close();
				b3.close();
				system("cls");
				ch_lab = labtest_required(ch_lab);
				if ((ch_lab == 'Y') || (ch_lab == 'y'))
				{
					h.LABTEST();
				}

				system("cls");

				ch_med = med_required(ch_med);

				if ((ch_med == 'Y') || (ch_med == 'y'))
				{
					h.MEDICINE();
				}

				system("cls");

				ch_ptm = 'Y';
				ch_cc = 'Y';
				h.print_bill(ch_lab, ch_med, ch_ptm, ch_cc);
				_getch();
				break;

				/*Case for printing lab test bill*/
			case 3:
				system("cls");
				h.pt_info();
				ch_lab = 'Y';
				ch_med = 'N';
				ch_ptm = 'N';
				ch_cc = 'N';
				h.LABTEST();
				h.print_bill(ch_lab, ch_med, ch_ptm, ch_cc);
				break;

				/*Case for printing medicine bill*/
			case 4:
				system("cls");
				h.pt_info();
				ch_med = 'Y';
				ch_lab = 'N';
				ch_ptm = 'N';
				ch_cc = 'N';
				h.MEDICINE();
				h.print_bill(ch_lab, ch_med, ch_ptm, ch_cc);
				break;

				/*Case for docto management*/
			case 5:

				while (1)
				{
					system("cls");

					cout << "\n\t DOCTORs MANAGEMENT ";
					cout << "\n \t\tMENU ";
					cout << "\n1. Display details of doctors in a particular department";
					cout << "\n2. Display list of departments";
					cout << "\n3. Add a doctor to the list";
					cout << "\n4. Delete a doctor from the list";
					cout << "\n5. Main Menu.";
					cout << "\n Choice : ";
					cin >> ch_doc;

					if (ch_doc >= 1 && ch_doc <= 5)
					{
						break;
					}
					else
					{
						cout << "\n Invalid Input. ";
						cout << "\n Enter again. ";
						continue;
					}
				}

				switch (ch_doc)
				{
					/*Case for displaying doctors in a particular department*/
					case 1:
						system("cls");
						int choice;

						b2.open("dept.txt", ios::in);
						b2.seekg(0);

						h.dept_list(records, dept_list, departments);

						for (;;)
						{
							cout << "\nEnter your choice: ";
							cin >> choice;

							if (choice >= 1 && choice <= departments) break;
							else
							{
								cout << "\nInvalid choice";
								continue;
							}
						}
						system("cls");

						b1.open("doc.txt", ios::in);
						b2.seekg(0);
						b3.open("charge.txt", ios::in);

						h.find_doc(dept_list, choice, records);

						b1.close();
						b2.close();
						b3.close();

						break;
						/*Case for displaying available departments*/
					case 2:
						system("cls");

						b2.open("dept.txt", ios::in);
						b2.seekg(0);

						h.dept_list(records, dept_list, departments);

						b2.close();
						break;
						/*Case for adding a doctor to the list of doctors in the hospital*/
					case 3:
						system("cls");

						a1.open("doc.txt", ios::app);
						a2.open("dept.txt", ios::app);
						a3.open("charge.txt", ios::app);

						b1.open("doc.txt", ios::in);
						b2.open("dept.txt", ios::in);

						h.add_doc(records);

						b1.close();
						b2.close();

						a1.close();
						a2.close();
						a3.close();

						break;
						/*Case for deleting a doctor from the list of doctors in the hospital*/
					case 4:
						system("cls");

						choice = 0;

						b1.open("doc.txt", ios::in);
						b2.open("dept.txt", ios::in);
						b3.open("charge.txt", ios::in);

						h.doc_details(records);

						b1.seekg(0);;
						b2.seekg(0);
						b3.seekg(0);

						a1.open("temp1.txt", ios::out);
						a2.open("temp2.txt", ios::out);
						a3.open("temp3.txt", ios::out);

						for (;;)
						{
							cout << "\nEnter the record number to be deleted: ";
							cin >> choice;

							if (choice >= 1 && choice <= records) break;
							else
								cout << "\nInvalid choice";
						}

						b2.seekg(0);

						h.del_doc(records, choice);

						cout << "\nThe record has been deleted";

						a1.close();
						a2.close();
						a3.close();

						b1.close();
						b2.close();
						b3.close();

						remove("doc.txt");
						remove("dept.txt");
						remove("charge.txt");
						rename("temp1.txt", "doc.txt");
						rename("temp2.txt", "dept.txt");
						rename("temp3.txt", "charge.txt");

						fflush(stdout);
						_getch();
						break;
						/*Case to exit doctor management*/
					case 5:
						break;
				}
				break;

				/*Case to exit the program*/
			case 6:
				exit(0);
		}
	}
	_getch();
	return 0;
}