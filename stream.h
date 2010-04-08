/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
	Stream functions for Infinite Numbers

	03/08/00
	**********
	Brian
	**********
		Moved the ostream function into its own header file

	03/20/00
	**********
	Brian & Chhean
	**********
		Completed the istream and fstream overloaded functions

	**********
	Brian
	**********
		Updated the istream overload, more robust algorithm
*/

#ifndef _Stream
#define _Stream

ostream& operator << (ostream &out, LIST const &ThatList)
{
	 NODE *ThatNode;
	 ThatNode = new NODE;

	 ThatNode  = ThatList.head->next;

	 // if an empty list
	if(ThatNode == ThatList.tail)
	{
			out << "Empty List";
	}

	else
	{
		if(ThatList.Flag == Negative)
		{
			 out << '-';
		}

		for(; // ThatList.head->next;
			 ThatNode != ThatList.tail;
			 ThatNode  = ThatNode->next)
		{
			out << ThatNode->Digit;
		}
	}

	 return out;
}

void operator >> (istream &in, LIST &ThatList)
{
	char InputChar;

	ThatList.Purge();
		
	InputChar = _getche();
	if(InputChar == '-')
	{
		ThatList.Flag = Negative;
		InputChar = _getche();
	}
		
	while(InputChar != (char)13) // while not new line
	{
		if(InputChar == (char)8) //If backspace is used this will remove the
		{                        //the node, echo a space and move the cursor back
			ThatList.RemoveFromEnd();
			putch(' ');
			putch((char)8);
		}

		//ignore non-integer characters
		else if((InputChar - '0') < 10 && (InputChar - '0') >= 0)
		{
			ThatList.InsertAtEnd((InputChar - '0'));
		}

		InputChar = _getche();
	}
	cout << endl;
}

fstream& operator << (fstream &out, LIST const &ThatList)
{
	 NODE *ThatNode;
	 ThatNode = new NODE;

	 char filename[255];

	 cout << "Enter the filename: ";
	 cin  >> filename;
	 
	 ofstream newfile(filename, ios::out);
	 
	 if(ThatList.Flag == Negative)
	 {
		 newfile << '-';
	 }

	 for(ThatNode  = ThatList.head->next;
			 ThatNode != ThatList.tail;
			 ThatNode  = ThatNode->next)
	 {
			newfile << ThatNode->Digit;
	 }

	 newfile << ' '; //The deliminiator is a space

	 return out; 
}

void operator >> (fstream &in, LIST &ThatList)
{
	 ThatList.Purge();	// destroy the list
	 char filename[255], InputChar;

	 cout << "Enter the filename: ";
	 cin  >> filename;
	 
	 ifstream newfile(filename, ios::in);
	 
	 newfile.get(InputChar);
	 while(InputChar != ' ' && InputChar != '\n' && !newfile.eof())
	 {

		 if(InputChar == '-')
		 {
			 ThatList.Flag = Negative;
			 newfile.get(InputChar);		 
		 }

		 ThatList.InsertAtEnd((InputChar - '0'));
		 newfile.get(InputChar);
	 }	 
}

#endif