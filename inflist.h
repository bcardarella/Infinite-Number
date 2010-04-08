/*
	Programmers: Chhean Saur, Jason Hepp, & Brian Cardarella
	INFLIST.H
*/

#ifndef _INFLIST
#define _INFLIST

#include "infinnum.h"

INFLIST::INFLIST()
{
	head = new LIST;
	tail = new LIST;

	head->next = tail;
	tail->prev = head;
}

INFLIST::INFLIST(INFLIST const &ThatList)
{
	LIST *ThisNode;
	LIST *ThatNode;

	head = new LIST;
	tail = new LIST;

	head->next = tail;
	tail->prev = head;

	ThisNode = new LIST;

	for(ThatNode  = ThatList.head->next;
		ThatNode != ThatList.tail;
		ThatNode  = ThatNode->next)
	{
		ThisNode = new LIST;

		*ThisNode = *ThatNode;

		InsertAtEnd(ThisNode);
		
		ThisNode->Flag = ThatNode->Flag;		// assign its sign value (positive or negative)
	}
}

INFLIST::~INFLIST() //Deconstructor
{ 
	 Purge(); //Empty the list
}

void INFLIST::Purge(void)
{
	LIST *Temp;

	while(head->next != tail)
	{
		Temp = new LIST;
		Temp = head->next;
		head->next = Temp->next;
		head->next->prev = head;

		Temp->Purge();
	}
}

void INFLIST::InsertAtEnd(LIST *ThisList)
{
	LIST *NewNode;
	NewNode = new LIST;

	*NewNode = *ThisList;
	
	NewNode->next = tail;
	NewNode->prev = tail->prev;
	tail->prev->next = NewNode;
	tail->prev = NewNode;
}

void INFLIST::RemoveDigit(LIST Target, int Arg)
{
	LIST *NewNode;
	NewNode = new LIST;

	LIST *TempNode;
	TempNode = new LIST;

	for(NewNode = head->next;
	    NewNode != tail;
		NewNode = NewNode->next)
	{
		if(*NewNode == Target && Arg == 0)
		{
			TempNode = NewNode->prev;
			NewNode->prev->next = NewNode->next;
			NewNode->next->prev = NewNode->prev;
			delete NewNode;
			NewNode = new LIST;
			NewNode = TempNode;
		}

		else if(*NewNode == Target && Arg != 0)
		{
			Arg = 0;
		}
	}
}

#endif