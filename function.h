/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
*/

#ifndef _functions
#define _functions


LIST LIST::Sum(void)
{
	LIST SumList;
	
	NODE *SumPtr;

	SumPtr = new NODE;

	for(SumPtr = head->next; SumPtr != tail; SumPtr = SumPtr->next)
	{
		SumList = SumList + SumPtr->Digit;
	}

	return SumList;
}

LIST LIST::SumKPower(LIST const& Power)
{
	LIST SumList = 0;
	
	NODE *SumPtr;
	LIST Temp;

	SumPtr = new NODE;

	for(SumPtr = head->next; SumPtr != tail; SumPtr = SumPtr->next)
	{
		Temp = SumPtr->Digit;
		SumList = SumList + (Temp ^ Power);
	}

	return SumList;
}
LIST LIST::SumKPower(int const& Power)
{
	LIST Temp;
	Temp = Power;
	return (SumKPower(Temp));	
}

LIST LIST::OneDigitSum(void)
{
	LIST SumList;
	LIST NineList = 9;

	SumList = *this;
	SumList.Flag = Positive;	// make sure the digit is positive for
	                            // the compare against 9

	while(SumList > NineList)
	{
		SumList = SumList.Sum();
	}

	return SumList;
}

LIST LIST::OneDigitProduct(void)
{
	LIST ProdList;
	LIST ProdDigit = 1;
	LIST NineList = 9;
	LIST ZeroList = 0;

	ProdList = *this;
	ProdList.Flag = Positive;	// make sure the digit is positive for
	                            // the compare against 9

	while(ProdList > NineList)
	{
		while(ProdList > ZeroList)
		{
			ProdDigit = ProdDigit * (ProdList % 10);
			ProdList = ProdList / 10;
		}
		ProdList = ProdDigit;
		ProdDigit = 1;	//reset the product digit
	}

	return ProdList;
}

LIST NumberTen(LIST const &M, LIST const &N, const unsigned long Delim, bool Sequence)
{	
	INFLIST TempList;
	INFLIST ThisList;

	LIST *NodeA;
	LIST *NodeB;
	LIST *TempListNode;

	NodeA = new LIST;
	NodeB = new LIST;
	TempListNode = new LIST;

	*NodeA = M;
	*NodeB = N;

	ThisList.InsertAtEnd(NodeA);
	ThisList.InsertAtEnd(NodeB);

	if(Sequence)	// the first two terms
	{
		cout << M << endl << N << endl;
	}

	for(unsigned long i = 2; i < Delim; i++)
	{
		NodeA = ThisList.tail->prev;

		for(NodeB = ThisList.head->next;
		    NodeB != NodeA;
			NodeB = NodeB->next)

		{
			*TempListNode = (*NodeA + *NodeB);
				
			//Insert TempListNode into TempList
			TempList.InsertAtEnd(TempListNode);
			TempListNode = new LIST;
		}

		NodeA = new LIST;
		
		TempList.BubbleSort(1);

		for(TempListNode = TempList.head->next;
		    TempListNode != TempList.tail;
			TempListNode = TempListNode->next)
		{
			if(*ThisList.tail->prev < *TempListNode)
			{
				ThisList.InsertAtEnd(TempListNode);
				
				if(Sequence)
				{					
					cout << *TempListNode << endl;
				}

				break;
			}
		}
		TempListNode = new LIST;
	}

	return (*ThisList.tail->prev);
}

LIST NumberEleven(LIST const M, LIST const N, const unsigned long Delim, bool Sequence)
{	
	INFLIST TempList;
	INFLIST ThisList;
		
	LIST *NodeA;
	LIST *NodeB;
	LIST *TempListNode;
	LIST *ListAdder;

	NodeA = new LIST;
	NodeB = new LIST;
	TempListNode = new LIST;
	ListAdder = new LIST;

	*NodeA = M;
	*NodeB = N;

	ThisList.InsertAtEnd(NodeA);
	ThisList.InsertAtEnd(NodeB);

	if(Sequence)	// the first two terms
	{
		cout << M << endl << N << endl;
	}


	for(unsigned long i = 2; i < Delim; i++)
	{
		
		NodeA = ThisList.tail->prev;

		for(NodeB = ThisList.head->next;
		    NodeB != NodeA;
			NodeB = NodeB->next)

		{
			*TempListNode = (*NodeA + *NodeB);
				
			//Insert TempListNode into TempList
			TempList.InsertAtEnd(TempListNode);
			TempListNode = new LIST;
		}

		NodeA = new LIST;

		TempList.BubbleSort(2);

		*ListAdder = 1;

		for(TempListNode = TempList.head->next;
		    TempListNode != TempList.tail;
			TempListNode = TempListNode->next)
		{
			if((*ThisList.tail->prev < *TempListNode) &&
			  ((*ThisList.tail->prev + *ListAdder) !=  *TempListNode))
			{
				*NodeA = (*ThisList.tail->prev + *ListAdder);
				ThisList.InsertAtEnd(NodeA);
				if(Sequence)
				{					
					cout << *NodeA << endl;
				}

				break;
			}

			else if(TempListNode->next == TempList.tail)
			{
				*ListAdder = *ListAdder + 1;
				*NodeA = (*ThisList.tail->prev + *ListAdder);
				ThisList.InsertAtEnd(NodeA);

				if(Sequence)
				{					
					cout << *NodeA << endl;
				}

				break;
			}

			if((*ThisList.tail->prev < *TempListNode))
			{
				*ListAdder = *ListAdder + 1;
			}
		}

		TempListNode = new LIST;
	}

	return (*ThisList.tail->prev);
}

LIST LIST::BubbleSort(int Arg) //Arg = 0: Regular sort
							   //Arg = 1: If there is more than one instance of
							   //         the number destory all instances of it
{
	NODE *ThisNode;
	ThisNode = new NODE;

	ThisNode = head->next;

	int TempDigit;

	while(ThisNode != tail)
	{
		if(Arg == 1)
		{
			if(ThisNode->Digit == ThisNode->prev->Digit)
			{
				RemoveDigit(ThisNode->Digit);
				ThisNode = head->next;
			}
		}

		if(ThisNode != tail && (ThisNode->Digit < ThisNode->prev->Digit))
		{
			TempDigit = ThisNode->Digit;
			ThisNode->Digit = ThisNode->prev->Digit;
			ThisNode->prev->Digit = TempDigit;
			ThisNode = ThisNode->prev;
		}

		else if(ThisNode != tail)
		{
			ThisNode = ThisNode->next;
		}
	}
	
	return *this;
}

INFLIST INFLIST::BubbleSort(int Arg) //Arg = 0: Regular sort
							   //Arg = 1: If there is more than one instance of
							   //         the number destory all instances of it
							   //Arg = 2: Remove all but one instance of repeting number
{
	LIST *ThisNode;
	ThisNode = new LIST;

	ThisNode = head->next;

	LIST TempList;

	while(ThisNode != tail)
	{
		if(Arg != 0)
		{
			if(*ThisNode == *ThisNode->prev)
			{
				RemoveDigit(*ThisNode, Arg);
				ThisNode = head->next;
			}
		}

		if(ThisNode != tail && (*ThisNode < *ThisNode->prev))
		{
			TempList = *ThisNode;
			*ThisNode = *ThisNode->prev;
			*ThisNode->prev = TempList;
			ThisNode = ThisNode->prev;
		}

		else if(ThisNode != tail)
		{
			ThisNode = ThisNode->next;
		}
	}
	
	return *this;
}

LIST LIST::DigitSumSeq(LIST const &Number)	// returns -1 if the ThisList only has one digit
{
	LIST ThisList;

	ThisList = *this;

	if(ThisList > 9)
	{
		for(LIST i=1; i < Number; i = i+1)
		{
			ThisList = ThisList.Sum() + ThisList;
		}
	}
	else	// return a -1
	{
		ThisList = 1;
		ThisList.Flag = Negative;
	}

	return ThisList;

}

LIST LIST::DigitSumSeq(int const &Number)
{
	LIST TempList;
	TempList = Number;
	return(DigitSumSeq(TempList));
}


#endif