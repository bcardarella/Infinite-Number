/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
	Infinite Number Driver Test
*/
#include <iostream.h>
#include <conio.h>
#include "inflist.h"
//#include "infinnum.h"

void UserInterface(void);

// returns true or false on whether or not the SearchKey was found within Options
bool Find(char SearchKey, char Options[], int OptionSize);

void Operator(LIST &A, LIST &B, LIST &Ans, char Operation);	// Operators
bool Compare(LIST &A, LIST &B, char Compare);	// Compare
void ComputeFunction(LIST &A, LIST &B, LIST &Ans, char Function);	// Functions
// for file stream, Output = true for output to a file, Output = False for input from a file
void FileInput(LIST &A, fstream& FileName, bool Output);
void EquateList(LIST &A, LIST &B);

void main()
{	
	LIST A = 0, B = 0, Ans;
	fstream File;
	const int NumOfOperator = 6, NumOfCompare = 4, NumOfFunc = 14, NumOfSet = 10;
	char Operators[] = "+-/*%^", Compares[] = "<>=!", Functions[] = "DKSPQTVdkspqtv",
		 SetEquals[] = "WRCELwrcel", choice;

	while(choice != 'X' && choice != 'x')
	{
		cout << "(+)Addition	(<)Compare if Less		(D)Sum of Digits" << endl
			 << "(-)Subtraction	(>)Compare if Greater		(K)Sum of Digits to Kth Power" << endl
			 <<	"(/)Divide	(=)Compare if Equal		(S)One Digit Sum" << endl
			 <<	"(%)Modulous	(!)Compare Not Equal		(P)One Digit Product" << endl
			 << "(*)Multiply					(Q)Digital Sum Sequence" << endl
			 << "(^)Exponent					(T)Number Ten" << endl
			 << "						(V)Number Eleven" << endl
			 << "(A)Input A	(O)utput A to File" << endl
			 << "(B)Input B	(I)nput A from File" << endl
			 << "(W)Set A=Answer" << endl
			 << "(R)Set B=Answer" << endl
			 << "(C)Set B=A" << endl
			 << "(E)Set A=B" << endl
			 << "(L)Clear Answer" << endl
			 << "(X)Exit" << endl << endl

			 << "All operations are done in terms of A & B: A Function B. " << endl
			 << "A = " << A << endl << "B = " << B << endl << "Answer = " << Ans << endl
			 << "Please choose an option: ";
		cin >> choice;

	//	cout << endl;
		
		if(choice == 'A' || choice == 'a')
		{
		//	cout <<  "Enter a value for A: ";
			cin >> A;			
		}
		else if(choice == 'B' || choice == 'b')
		{
		//	cout << endl << "Enter a value for B: ";
			cin >> B;			
		}
		else if(Find(choice,Operators,NumOfOperator))
			Operator(A,B,Ans,choice);
		else if(Find(choice,Compares,NumOfCompare))
		{
			if(Compare(A,B,choice))
			{
				cout << "True" << endl;				
			}
			else
			{
				cout << "False" << endl;
			}
			cout << "Press any key to continue. ";
			getch();
		}
		else if(Find(choice,Functions,NumOfFunc))
			ComputeFunction(A,B,Ans,choice);
		else if(choice == 'O' || choice == 'o')
		{
			FileInput(A,File,true);
		}
		else if(choice == 'I' || choice == 'i')
		{
			FileInput(A,File,false);
		}
		else if(Find(choice,SetEquals,NumOfSet))
		{
			if(choice == 'W' || choice == 'w')	// A = Ans
				EquateList(A,Ans);
			else if(choice == 'R' || choice == 'r')	// B = Ans
				EquateList(B,Ans);
			else if(choice == 'C' || choice == 'c')	// B = A
				EquateList(B,A);
			else if(choice == 'E' || choice == 'e')	// A = B
				EquateList(A,B);
			else if(choice == 'L' || choice == 'l')	// Ans = Empty List
				Ans.Purge();

		}
		else if(choice != 'X' && choice !='x')
			cout << "Error. Incorrect option choice." << endl;
		
		cout << "Answer = " << Ans << endl;
		cout << "Press any key to continue. " << endl;
		getch();
		
	}
}
void EquateList(LIST &A, LIST &B)
{
	A=B;
}
void FileInput(LIST &A, fstream& FileName, bool Output)
{
	if(Output)
	{
		cout << "Note that A's value will be outputted." << endl;
		FileName << A;
	}
	else
	{
		cout << "Note that A will assume the value from the input." << endl;
		FileName >> A;
	}


}
bool Find(char SearchKey, char Options[], int OptionSize)
{
	for(int i=0; i < OptionSize; i++)
		if(SearchKey == Options[i])
			return true;

	return false;

}

void ComputeFunction(LIST &A, LIST &B, LIST &Ans, char Function)
{
	int Delim;
	char PrintAll = 'N';
	if(Function == 'D' || Function == 'd')
		Ans = A.Sum();
	else if(Function == 'K' || Function == 'k')
		Ans = A.SumKPower(B);
	else if(Function == 'S' || Function == 's')
		Ans = A.OneDigitSum();
	else if(Function == 'P' || Function == 'p')
		Ans = A.OneDigitProduct();
	else if(Function == 'Q' || Function == 'q')
		Ans = A.DigitSumSeq(B);
	// for Number Ten
	else if(Function == 'T' || Function == 't')
	{	
		cout << "Enter the Nth number to stop: ";
		cin >> Delim;
		cout << "Do you wish to print out all the numbers in the sequence? (Y/N): ";
		cin >> PrintAll;
		
		if(PrintAll == 'Y' || PrintAll == 'y')
			Ans = NumberTen(A,B,Delim,true);
		else
			Ans = NumberTen(A,B,Delim,false);		
	}

		else if(Function == 'V' || Function == 'v')
	{	
		cout << "Enter the Nth number to stop: ";
		cin >> Delim;
		cout << "Do you wish to print out all the numbers in the sequence? (Y/N): ";
		cin >> PrintAll;
		
		if(PrintAll == 'Y' || PrintAll == 'y')
			Ans = NumberEleven(A,B,Delim,true);
		else
			Ans = NumberEleven(A,B,Delim,false);		
	}
}

bool Compare(LIST &A, LIST &B, char Compare)
{
	if(Compare == '>')
		if(A > B) return true;
		else return false;
	else if(Compare == '<')
		if(A < B) return true;
		else return false;
	else if(Compare == '=')
		if(A == B) return true;
		else return false;
	else
	{
		if(A != B) return true;
		else return false;
	}
}

void Operator(LIST &A, LIST &B, LIST &Ans, char Operation)
{
	if(Operation == '+')
		Ans = A + B;
	else if(Operation == '-')
		Ans = A - B;
	else if(Operation == '*')
		Ans = A * B;
	else if(Operation == '/')
		Ans = A / B;
	else if(Operation == '%')
		Ans = A % B;
	else
		Ans = A ^ B;

}
