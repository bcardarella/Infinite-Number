/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
	
	Condit.h
	Contains all conditional member functions for infinite numbers

	03/08/00
	******
	Brian
	******
		Removed these member functions from the infinum.h file and put them
		their own specific .h file

	03/10/00
	******
	Chhean
	******
		Fixed conditionals to account for negative values
		Replaced the Conditional type with bool and had each
			function return ether true or false
	
	03/17/00
	******
	Chhean
	******
		Added and overloaded the not equals operator (!=)

	03/21/00
	******
	Brian
	******
		Overloaded the functions to work for taking in
			an integer as well as a LIST
*/

#ifndef _Condit
#define _Condit

bool LIST::operator < (LIST const &ThatList)
{
	if(Compare(ThatList) == Less)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator < (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Less)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator > (LIST const &ThatList)
{
	if(Compare(ThatList) == Greater)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator > (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Greater)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator <= (LIST const &ThatList)
{
	if(Compare(ThatList) == Less || Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator <= (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Less || Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator >= (LIST const &ThatList)
{
	if(Compare(ThatList) == Greater || Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator >= (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Greater || Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator == (LIST const &ThatList)
{
	if(Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator == (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Equal)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator != (LIST const &ThatList)
{
	if(Compare(ThatList) == Greater || Compare(ThatList) == Less)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool LIST::operator != (int const &Number)
{
	LIST ThatList;
	ThatList = Number;

	if(Compare(ThatList) == Greater || Compare(ThatList) == Less)
	{
		return true;
	}

	else
	{
		return false;
	}
}

Evaluate LIST::Compare(LIST const &ThatList)
{
	NODE *ThatListNode; //Wrapper Nodes
	NODE *ThisNode;  //Wrapper Nodes

	ThatListNode = new NODE;
	ThisNode  = new NODE;

	// Compare the signs first
	// (note that zero (0) will be positive) --Chhean Saur
	if(Flag == Positive && ThatList.Flag == Negative)
	{
		return Greater;		// this > that
	}

	else if(Flag == Negative && ThatList.Flag == Positive)
	{
		return Less;		// this < that
	}

	// else the signs must be the same, therefore,
	// compare their lengths --Chhean Saur

	//Comapre the list sizes... if one is longer than
	//the other then comparison is easy	  --Brian Cardarella

	ThatListNode = ThatList.head;
	ThisNode  = head;

	while(ThisNode != tail || ThatListNode != ThatList.tail)
	{
		if(ThatListNode == ThatList.tail)
		{
			// if they're positive, then the longer number is greater
			if(Flag == Positive && ThatList.Flag == Positive)
			{
				return Greater;		// this > that
			}

			// else if they're both negative,
			// then the longer number is smaller
			else
			{
				return Less;		// this < that
			}
		}

		if(ThisNode == tail)
		{
			// if they're positive, then the longer number is greater
			if(Flag == Positive && ThatList.Flag == Positive)
			{
				return Less;		// this < that
			}

			// else if they're both negative,
			// then the longer number is smaller
			else
			{
				return Greater;		// this > that
			}
		}

		ThatListNode = ThatListNode->next;
		ThisNode  = ThisNode->next;
	}

	//If the program makes it to this point then a
	//digit-by-digit comparison must be done

	ThatListNode = ThatList.head->next;
	ThisNode  = head->next;


	while(ThatListNode != ThatList.tail || ThisNode != tail)
	{
		if( ((ThisNode->Digit)*Flag) >
			((ThatListNode->Digit)*ThatList.Flag) )	// test for sign
		{		
			return Greater;
		}

		if( ((ThisNode->Digit)*Flag) <
			((ThatListNode->Digit)*ThatList.Flag) )
		{
			return Less;
		}

		ThatListNode = ThatListNode->next;
		ThisNode  = ThisNode->next;
	}

	//If the program has made it to this point
	//then the two lists must be equal
	return Equal;
}

#endif