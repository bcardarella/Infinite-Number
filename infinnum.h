/*
	 Infinite Number Header File

	 Programmers: Chhean Saur. Jason Hepp & Brian Cardarella

	 02/17/00
	 ******
	 Brian
	 ******
			Reprogrammed the original header file
			Reorganized the Linked LIST logic

	 02/23/00
	 ******
	 Brian
	 ******
			Fixed minor errors
			Completed the ostream (<<) overload
			Completed the assign (=) overload

		 02/24/00
	 ******
	 Brian
	 ******
			Fixed the list initialization
			Modefied code for Visual C++ 6.0
			Completed the Conditional overaloads
			Sketched rough outline for the addition (+) operator
	
		 03/01/00
	 ******
	 Brian
	 ******
			Added a Purge function to correct the assign (=) operator

		03/08/00
	 ******
	 Brian
	 ******
			Split up the infinum.h file into function-specific .h files

		 03/10/00
	 ******
	 Chhean
	 ******
			removed Conditional types and replaced them with bool
			changed conditional functions to either return true or false
				rather than True or False
			fixed Compare function to allow comparisons of negative numbers
	
		 03/13/00
	 ******
	 Chhean
	 ******
			fixed copy constructor -- copied the List flag into the "this" list

		03/16/00
	 ******
	 Brian & Chhean
	 ******
		    Completed the Addtion function to also do subtration
			Started Division Function

     ******
	 Brian
	 ******
			Went through the program and created continuity between the variables
		
		 03/16/00
	 ******
	 Brian & Chhean
	 ******
			Finished Addition, Subtration, Multiplication, Division, MOD

	 ******
	 Chhean
	 ******
			Added and overloaded the not equals operator (!=)
*/

#ifndef _InfiniteNum
#define _InfiniteNum
#include <fstream.h>

enum Sign{Positive = 1, Negative = -1};
enum Evaluate{Less = -1, Equal = 0, Greater = 1};

class NODE
{
	public:
		int Digit;

		NODE *prev;
		NODE *next;
};

class LIST
{
	public:
		NODE *head;
		NODE *tail;
		
		LIST *prev;
		LIST *next;

		Sign Flag;

		LIST(); //Constructor
		~LIST(); //Destructor
		LIST(LIST const &ThatList); //Copy Constructor
		LIST(char []);
		LIST(int Number);

		void LIST::Purge(void); //Empty the list
		LIST& LIST::operator = (LIST const &ThatList); //Assignment
		LIST& LIST::operator = (int Number);
		void LIST::InsertAtFront(NODE *ThisNode);
		void LIST::InsertAtFront(int Number);
		void LIST::RemoveFromFront(void);
		void LIST::InsertAtEnd(NODE *ThisNode);
		void LIST::InsertAtEnd(int Number);
		void LIST::RemoveFromEnd(void);
		void LIST::RemoveDigit(int Target);
		void LIST::CleanList(void); //Removes any zeros at the front
		void LIST::Combine (LIST const &ThatList); //Combines two lists

		//Conditionals -- condit.h
		bool LIST::operator < (LIST const &ThatList); //Less than
		bool LIST::operator < (int const &Number);	// Less than with integers

		bool LIST::operator > (LIST const &ThatList); //Greater than
		bool LIST::operator > (int const &Number);	// Greater than with integers

		bool LIST::operator <= (LIST const &ThatList);//Less/Equal
		bool LIST::operator <= (int const &Number);	// Less/Equal with integers

		bool LIST::operator >= (LIST const &ThatList);//Greater/Equal
		bool LIST::operator >= (int const &Number);	// Greater/Equal with integers

		bool LIST::operator == (LIST const &ThatList);//Equal to
		bool LIST::operator == (int const &Number);	// Equal with integers

		bool LIST::operator != (LIST const &ThatList);// Not Equal to
		bool LIST::operator != (int const &Number);	// Not Equal with integers

		Evaluate LIST::Compare(LIST const &ThatList);

		//Arithmetic -- arith.h
		LIST LIST::Divide(LIST const &ThatList, int ReturnVal);
		
		LIST LIST::operator + (LIST const &ThatList); //Addition
		LIST LIST::operator + (int const &Number); // Addition with integers
		
		LIST LIST::operator - (LIST &ThatList); //Subtration
		LIST LIST::operator - (int const &Number); // Subtraction with integers
		
		LIST LIST::operator * (LIST const &ThatList); //Multiplication
		LIST LIST::operator * (int const &Number); //Multiplication with integers
		
		LIST LIST::operator / (LIST const &ThatList); //Division
		LIST LIST::operator / (int const &Number); //Division with integers

		LIST LIST::operator % (LIST const &ThatList); //Modulous
		LIST LIST::operator % (int const &Number); //Modulous with integers

		LIST LIST::operator ^ (LIST const &ThatList); //Exponent
		LIST LIST::operator ^ (int const &Number);	//Exponent with integers

		//I/O Stream -- stream.h
		friend ostream& operator << (ostream &out, LIST const &ThatList); // for cout
		friend void operator >> (istream &in, LIST &ThatList);			  // for cin
		friend fstream& operator << (fstream &out, LIST const &ThatList); // for file output
		friend void operator >> (fstream &in, LIST &ThatList);			  // for file input
		LIST LIST::BubbleSort(int Arg);
	
		//Problems -- Functions.h
		LIST LIST::Sum(void);
		
		LIST LIST::SumKPower(LIST const& Power);
		LIST LIST::SumKPower(int const&);

		LIST LIST::OneDigitSum(void);
		LIST LIST::OneDigitProduct(void);

		LIST LIST::DigitSumSeq(LIST const &Number);
		LIST LIST::DigitSumSeq(int const &Number);
		LIST NumberTen(LIST const &M, LIST const &N, const unsigned long Delim);
		LIST NumberEleven(LIST M, LIST N, const unsigned long Delim);
};

class INFLIST
{
	public:
		LIST *head;
		LIST *tail;

		INFLIST(); //Constructor
		~INFLIST(); //Destructor
		INFLIST(INFLIST const &ThatList); //Copy Constructor

		void INFLIST::InsertAtEnd(LIST *ThisList);
		void INFLIST::Purge(void);
		void INFLIST::RemoveDigit(LIST Target, int Arg);
		INFLIST INFLIST::BubbleSort(int Arg);
};

#include "arith.h"
#include "condit.h"
#include "stream.h"
#include "function.h"


LIST::LIST():Flag(Positive)
{
	head = new NODE;
	tail = new NODE;

	head->next = tail;
	tail->prev = head;
}

LIST::LIST(int Number):Flag(Positive)
{
	head = new NODE;
	tail = new NODE;

	head->next = tail;
	tail->prev = head;
	
	NODE *NumNode;

	if(Number < 0)
	{
		Flag = Negative;
	}

	else
	{
		Flag = Positive;
	}

	if(Number == 0)
	{
		InsertAtFront(0); //Incase the user wants to initialize the list at zero
	}
	else
	while(Number != 0)
	{
		NumNode = new NODE;
		NumNode->Digit = Number % 10;
		Number = Number / 10;

		InsertAtFront(NumNode);
	}
}

LIST::LIST(char Num[]):Flag(Positive)
{
	 head = new NODE;
	 tail = new NODE;

	 int i = 0;

	 head->next = tail; //empty LIST
	 tail->prev = head; //empty LIST

	 NODE *ThisNode;

	 if(Num[0] == '-')
	 {
		Flag = Negative;
		i++;
	 }

	 else
	 {
		Flag = Positive;
	 }

	 for(; Num[i] != '#'; i++)
	 {
		ThisNode = new NODE;

		ThisNode->Digit = (Num[i] - '0');
		InsertAtEnd(ThisNode);
	 }

	 CleanList();
}

LIST::LIST(LIST const &ThatList)
{
	NODE *ThisNode;
	NODE *ThatNode;

	head = new NODE;
	tail = new NODE;

	head->next = tail;
	tail->prev = head;

	ThisNode = new NODE;

	for(ThatNode  = ThatList.head->next;
		ThatNode != ThatList.tail;
		ThatNode  = ThatNode->next)
	{
		ThisNode = new NODE;

		ThisNode->Digit = ThatNode->Digit;

		InsertAtEnd(ThisNode);
	}

	Flag = ThatList.Flag;		// assign its sign value (positive or negative)
}

LIST::~LIST() //Deconstructor
{ 
	 Purge(); //Empty the list
}

void LIST::Purge(void)
{
	NODE *Temp;

	Flag = Positive;

	while(head->next != tail)
	{
		Temp = new NODE;
		Temp = head->next;
		head->next = Temp->next;
		head->next->prev = head;

		delete Temp;		
	}
}

void LIST::InsertAtFront(NODE *ThisNode)
{
	NODE *NewNode;
	NewNode = new NODE;

	NewNode->Digit = ThisNode->Digit;

	NewNode->next = head->next;
	NewNode->prev = head;
	head->next->prev = NewNode;
	head->next = NewNode;
}

void LIST::InsertAtFront(int Number)
{
	NODE *ThisNode;
	ThisNode = new NODE;

	ThisNode->Digit = Number;
	
	ThisNode->next = head->next;
	ThisNode->prev = head;
	head->next->prev = ThisNode;
	head->next = ThisNode;
}

void LIST::RemoveFromFront(void)
{
	NODE *NewNode;
	NewNode = new NODE;

	NewNode = head->next;

	if(NewNode == tail)
	{
		return; //So that the program does not access empty memory
	}

	NewNode->next->prev = head;
	head->next = NewNode->next;
	delete NewNode;
}

void LIST::InsertAtEnd(NODE *ThisNode)
{
	NODE *NewNode;
	NewNode = new NODE;

	NewNode->Digit = ThisNode->Digit;
	
	NewNode->next = tail;
	NewNode->prev = tail->prev;
	tail->prev->next = NewNode;
	tail->prev = NewNode;
}

void LIST::InsertAtEnd(int Number)
{
	NODE *ThisNode;
	ThisNode = new NODE;

	ThisNode->Digit = Number;
	
	ThisNode->next = tail;
	ThisNode->prev = tail->prev;
	tail->prev->next = ThisNode;
	tail->prev = ThisNode;
}

void LIST::RemoveFromEnd(void)
{
	NODE *NewNode;
	NewNode = new NODE;

	NewNode = tail->prev;

	if(NewNode == head)
	{
		return; //So that the program does not access empty memory
	}

	NewNode->prev->next = tail;
	tail->prev = NewNode->prev;
	delete NewNode;
}

void LIST::RemoveDigit(int Target)
{
	NODE *NewNode;
	NewNode = new NODE;

	for(NewNode = head->next;
	    NewNode != tail;
		NewNode = NewNode->next)
	{
		if(NewNode->Digit == Target)
		{
			NewNode->prev->next = NewNode->next;
			NewNode->next->prev = NewNode->prev;
			delete NewNode;
			NewNode = new NODE;
			NewNode = head;
		}
	}
}

void LIST::CleanList(void)
{
	NODE *ThisNode;
	ThisNode = new NODE;

	ThisNode = head->next;

	while(ThisNode->Digit == 0 && ThisNode->next != tail)
	{		
		head->next = ThisNode->next;
		ThisNode->next->prev = ThisNode->prev;
		
		delete ThisNode;

		ThisNode = head->next;
	}

	if(head->next->Digit == 0)
	{
		Flag = Positive;
	}
}

void LIST::Combine (LIST const &ThatList) //Combines two lists
{
   	 NODE *ThisNode;
	 NODE *ThatListNode;
	 ThatListNode = new NODE;

	 for(ThatListNode  = ThatList.head->next; //Cycle through List2
		 ThatListNode != ThatList.tail;       //until List2.tail is reached
		 ThatListNode  = ThatListNode->next) //
	 {
		ThisNode = new NODE;

		ThisNode->Digit = ThatListNode->Digit; //Assign the value

		InsertAtEnd(ThisNode);
	 }

	 Flag = ThatList.Flag;                 //Assign flag value
}

#endif