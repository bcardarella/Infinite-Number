/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
	Arith.h
	Arithmetic Member Functions for the Infinite Number Program

	03/08/00
	******
	Brian
	******
		Removed these member functions from the infinum.h file and put them
		their own specific .h file
*/

#ifndef _Arith
#define _Arith

LIST& LIST::operator = (LIST const &ThatList)
{
   	 NODE *ThisNode;
	 NODE *ThatListNode;
	 ThatListNode = new NODE;

	 Purge(); //Empty the THIS list

	 for(ThatListNode  = ThatList.head->next; //Cycle through List2
		 ThatListNode != ThatList.tail;       //until List2.tail is reached
		 ThatListNode  = ThatListNode->next) //
	 {
		ThisNode = new NODE;

		ThisNode->Digit = ThatListNode->Digit; //Assign the value

		InsertAtEnd(ThisNode);
	 }

	 Flag = ThatList.Flag;                 //Assign flag value

	 return *this;  
}

LIST& LIST::operator = (int Number)
{
	NODE *NumNode;
		
	Purge();

	if(Number < 0)
	{
		Flag = Negative;
	}

	else
	{
		Flag = Positive;
	}
	
	if(Number == 0)
		InsertAtFront(0);
	else
	{
		while(Number != 0)
		{
			NumNode = new NODE;
			NumNode->Digit = Number % 10;
			Number = Number / 10;

			InsertAtFront(NumNode);
		}
	}
	

	return *this;
}

LIST LIST::operator + (LIST const &ThatList)
{
   	 LIST TempList; //Create a temp list for return

	 int CarryDigit = 0; //If a carry is needed

	 NODE *TempNode; //Wrapper Node
	 NODE *ThisNode; //Wrapper Node
	 NODE *ThatListNode; //Wrapper Node

	 ThatListNode = new NODE;
	 ThisNode  = new NODE;

	 ThatListNode = ThatList.tail->prev; //Start at the end of the nubmer
	 ThisNode  = tail->prev; //Start at the end of the number

	 while(ThatListNode != ThatList.head || ThisNode != head)
	 {
			TempNode = new NODE;

			TempNode->Digit = CarryDigit;

			CarryDigit = 0; //Empty the carry

			if(ThatListNode == ThatList.head) //if one list is longer than the other			
			{
				TempNode->Digit += (ThisNode->Digit * Flag);
			}

			else if(ThisNode == head) //if one list is longer than the other
			{
				TempNode->Digit += (ThatListNode->Digit * ThatList.Flag);
			}

			else
			{
				TempNode->Digit  += (ThatListNode->Digit * ThatList.Flag) +
					                (ThisNode->Digit * Flag);
			}

			if(Flag == ThatList.Flag)
			{
				if (TempNode->Digit > 9 || TempNode->Digit < -9)
				{
					TempNode->Digit -= 10 * Flag;
					CarryDigit = 1 * Flag;
				}

				if(Flag == Negative)	// set the sign accordingly
				{
					TempList.Flag = Negative;
				}
			}
				
			else 
			{
				// store the old *this flag for comparison
				Sign OldFlag = Flag;
				Flag = ThatList.Flag;

				if(*this > ThatList)
				{
					TempList.Flag = Negative;
					if(TempNode->Digit > 0)
					{
						TempNode->Digit -= 10;
						CarryDigit = 1;
					}
				}
				
				else if(*this < ThatList)
				{
					if(TempNode->Digit < 0)
					{
						TempNode->Digit += 10;
						CarryDigit = -1;
					}
				}
				
				// change *this flag back
				Flag = OldFlag;
			}
			if(ThatListNode != ThatList.head) //So that the wrapper doesn't
			{                           //leave the list
				 ThatListNode = ThatListNode->prev;
			}

			if(ThisNode  != head) //So that the wrapper doesn't leave the list
			{
				 ThisNode = ThisNode->prev;
			}

			TempNode->Digit *= TempList.Flag;

			TempList.InsertAtFront(TempNode);	
	 }


	 if(CarryDigit != 0)
	 {
			TempNode = new NODE;

			TempNode->Digit = CarryDigit;
			TempNode->Digit *= TempList.Flag;

			TempList.InsertAtFront(TempNode);
	 }

	 TempList.CleanList();
	 return TempList;
}

LIST LIST::operator + (int const &Number)
{
	LIST TempList;
	TempList = Number;
	return (TempList + (*this));
}
	

LIST LIST::operator - (LIST &ThatList)
{
	LIST TempList;
	
	if(ThatList.Flag == Positive)
	{
		ThatList.Flag = Negative;
	}

	else
	{
		ThatList.Flag = Positive;
	}

	
	TempList = (ThatList + (*this));
	
	if(ThatList.Flag == Positive)
	{
		ThatList.Flag = Negative;
	}

	else
	{
		ThatList.Flag = Positive;
	}

	return TempList;

}

LIST LIST::operator - (int const &Number)
{
	LIST TempList;
	
	TempList = Number;
	TempList.Flag = Negative;
	return (TempList + (*this));
}

LIST LIST::operator / (int const &Number) //Division with integers
{
	// Algorithm: call the equals (=) function and set a TempList = to that Number
	// then do the regular operation
	LIST TempList;
	TempList = Number;
	return ((*this) / TempList);

}

LIST LIST::operator / (LIST const &ThatList)
{
	//int Arbitrary;
	return Divide(ThatList, 0);
}

LIST LIST::operator % (int const &Number) //Modulous with integers
{
	// Algorithm: call the equals (=) function and set a TempList = to that Number
	// then do the regular operation
	LIST TempList;
	TempList = Number;
	return ((*this) % (TempList));

}

LIST LIST::operator % (LIST const &ThatList)
{
	return Divide(ThatList, 1);
}

LIST LIST::Divide (LIST const &ThatList, int ReturnVal) //ReturnVal = 0 : Division
														//ReturnVal = 1 : Modulous
{
	LIST CountList = 0;	//List to be returned
	LIST Divisor;
	LIST Dividend;
	LIST Remainder = 0;

	NODE *ThatNode;

	ThatNode = new NODE;

	ThatNode = head->next;

	while(ThatNode != tail)
	{
		Divisor = ThatList;

		Dividend = Remainder;
		Dividend.CleanList();

		while(Divisor > Dividend && ThatNode != tail)
		{
			Dividend.InsertAtEnd(ThatNode);
			ThatNode = ThatNode->next;
			CountList.InsertAtEnd(0);
			Dividend.CleanList();
		}

		CountList.CleanList();

		Dividend.CleanList();
		
		Divisor = 0;

		while((Divisor+ThatList) <= Dividend)
		{	
			CountList = CountList + 1;
			Divisor = Divisor + ThatList;
		}

		Remainder = Dividend - Divisor;
		Dividend.Purge();
	}
	
	// set its signs
	if(Flag != ThatList.Flag)
	{
		CountList.Flag = Negative;
		Remainder.Flag = Negative;
	}

	else
	{
		CountList.Flag = ThatList.Flag;
		Remainder.Flag = ThatList.Flag;
	}

	// determine whether or not to return the Quotient or the Remainder
	if(ReturnVal == 0)
	{
		CountList.CleanList();	// clean off the leading zeros
		return CountList;
	}

	else
	{
		Remainder.CleanList();
		return Remainder;
	}
}

LIST LIST::operator * (int const &Number) //Multiplication with integers
{
	// Algorithm: call the equals (=) function and set a TempList = to that Number
	// then do the regular operation
	LIST TempList;
	TempList = Number;
	return (TempList * (*this));

}

LIST LIST::operator * (LIST const &ThatList)
{
	 LIST TempList; //Create a temp list for return
	 LIST ProductList;
	 LIST ZeroList;

	 int TensCarry = 0;

	 NODE *TempNode; //Wrapper Node
	 NODE *ThisNode; //Wrapper Node

	 NODE *ThatListNode; //Wrapper Node

	 ThatListNode = new NODE;
	 ThisNode  = new NODE;

	 while(ThatListNode!= ThatList.head || ThisNode != head)
	 {
			TempNode = new NODE;

			TensCarry = 0; //Empty the carry
			
			for(ThatListNode = ThatList.tail->prev;
			    ThatListNode != ThatList.head;
				ThatListNode = ThatListNode->prev)
			{
				for(ThisNode = tail->prev;
				    ThisNode != head;
					ThisNode = ThisNode->prev)
				{
					TempNode->Digit = TensCarry;	

					TempNode->Digit  += (ThatListNode->Digit * ThisNode->Digit);
			
					if (TempNode->Digit > 9)
					{
						TensCarry = TempNode->Digit / 10;
						TempNode->Digit %= 10;
					}

					else
					{
						TensCarry = 0;
					}

					ProductList.InsertAtFront(TempNode);
				}
				
				
				if(TensCarry != 0)
				{
					TempNode = new NODE;

					TempNode->Digit = TensCarry;

					ProductList.InsertAtFront(TempNode);
				}

				TensCarry = 0;
				TempList = TempList + ProductList;
				ZeroList.InsertAtEnd(0);
				ProductList.Purge();
				ProductList = ZeroList;				
			}
	 }

	 if(TensCarry != 0)
	 {
		TempNode = new NODE;

		TempNode->Digit = TensCarry;

		TempList.InsertAtFront(TempNode);
	 }

	 if(Flag == ThatList.Flag)
	 {
		 TempList.Flag = Positive;
	 }

	 else
	 {
		 TempList.Flag = Negative;
	 }

	 TempList.CleanList();
	 return TempList;
}

LIST LIST::operator ^ (LIST const &ThatList)
{
	LIST ExpList;
	LIST ReturnList = 1;
	LIST Base;
	
	Base = *this;
	ExpList.Flag = ThatList.Flag;	// make sure that ExpList < ThatList
	
	for(ExpList = 0; ExpList < ThatList; ExpList = ExpList + 1)
	{
		ReturnList = ReturnList * Base;
	}
	
	return ReturnList;
}

LIST LIST::operator ^ (int const &Number)
{
	LIST TempList;
	TempList = Number;
	return (*this^TempList);
}

#endif