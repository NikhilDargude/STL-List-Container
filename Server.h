#include<iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::cin;

template<class T>
class List;

template<class T>
class Node
{
	Node<T> * pPrev;
	T tData;
	Node<T> * pNext;

public:

	Node();
	~Node();

	friend class List<T>;

	template<class T1>
	friend ostream& operator << (ostream &out, List<T1> &refObj);
};

template<class T>
class List
{
	Node<T> * pDemo;

	void DeleteAllNode();

public:
	List();
	~List();

	void Display();
	int CountNode();
	T DeleteLast();
	T DeleteFirst();
	bool IfListEmpty();
	void InsertLast(T);
	void InsertFirst(T);
	T DeleteAtPosition(int);
	int SearchAllOccurrence(T);
	int SearchLastOccurrence(T);
	int SearchFirstOccurrence(T);
	void InsertAtPosition(T, int);


	void Sort();
	void Unique();
	void Merge(List&);
	void push_back(T);
	void push_front(T);
	void operator=(List&);
	
	template<class T>
	friend ostream& operator << (ostream &out, List<T> &refObj);

	class iterator
	{
		Node<T> * pCurrent;
		
	public:
		iterator();
		~iterator();

		bool operator ==(iterator &);
		bool operator !=(iterator&);
		iterator operator ++(int);
		iterator operator --(int);
		iterator& operator ++();
		iterator& operator--();
		T operator*();

		 void SetCurrentNode(Node<T> *);
		 Node<T> * GetCurrentNode();
	};

private:
	iterator Start;
	iterator Last;

public:
	iterator& begin();
	iterator& end();

	void Splice(iterator&, List&, iterator&);
	void Splice(iterator&, List&);
};



template<class T>
Node<T>::Node()
{
	pPrev = NULL;
	tData = (T)0;
	pNext = NULL;

}

template<class T>
Node<T>::~Node()
{
	if(pNext != NULL)
	{
		delete pNext;

		pPrev = NULL;
		pNext = NULL;
	}
}

template<class T>
List<T>::List()
{
	pDemo = NULL;

	pDemo = new Node<T>;
		if(NULL == pDemo)
		{
			cout << "Node creation Faild";
			return ;
		}

		pDemo->pPrev = pDemo;
		pDemo->tData = 0;
		pDemo->pNext = pDemo;
}

template<class T>
List<T>::~List()
{
	if(pDemo == pDemo->pNext)
	{
		DeleteAllNode();
	}

	pDemo->pPrev = NULL;
	pDemo->pNext = NULL;

	delete pDemo;
	pDemo = NULL;
}

template<class T>
List<T>::iterator::iterator()
{
	pCurrent = NULL;
}

template<class T>
List<T>::iterator::~iterator()
{
	pCurrent = NULL;
}

template<class T>
typename List<T>::iterator& List<T>::begin()
{
	Start.SetCurrentNode(pDemo->pNext);
	return Start;
}

template<class T>
typename List<T>::iterator& List<T>::end()
{
	Last.SetCurrentNode(pDemo);
	return Last;
}

template<class T>
void List<T>::iterator::SetCurrentNode(Node<T> * pSet)
{
	pCurrent = pSet;
}

template<class T>
Node<T>* List<T>::iterator::GetCurrentNode()
{
	return pCurrent;
}

template<class T>
bool List<T>::iterator::operator!=(iterator& refObj)
{
	if(pCurrent != refObj.pCurrent)
		return true;
	else
		return false;
}

template<class T>
typename List<T>::iterator& List<T>::iterator::operator ++()
{
	pCurrent = pCurrent -> pNext;
	return *this;
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator ++(int)
{
	iterator iTer;

	iTer.pCurrent = pCurrent;
	pCurrent = pCurrent -> pNext;

	return iTer;
}

template<class T>
typename List<T>::iterator& List<T>::iterator::operator --()
{
	pCurrent = pCurrent -> pPrev;
	return *this;
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator --(int)
{
	iterator iTer; 

	iTer.pCurrent = pCurrent;
	pCurrent = pCurrent -> pPrev;

	return iTer;
}

template<class T>
bool List<T>::iterator::operator==(iterator &list)
{
	if(pCurrent == list.pCurrent)
		return true;
	else
		return false;
}

template<class T>
T List<T>::iterator::operator*()
{
	return pCurrent->tData;
}

template<class T>
void List<T>::push_front(T iNo)
{
	InsertFirst(iNo);
}

template<class T>
void List<T>::push_back(T iNo)
{
	InsertLast(iNo);
}

template <typename T>
typename List<T>::iterator& find(typename List<T>::iterator &Begin,typename List<T>::iterator &End, T tNo)
{
	while(Begin != End)
	{
		if(*Begin == tNo)
			return Begin;

		Begin++;
	}

	return Begin;

}

template<class T>
void List<T>::Splice(iterator& Possi, List& list1)
{
	Node<T> * pTemp = NULL;

	pTemp = Possi.GetCurrentNode();

	pTemp->pPrev->pNext = list1.pDemo->pNext;
	list1.pDemo->pNext->pPrev = pTemp->pPrev;
	pTemp->pPrev = list1.pDemo->pPrev;
	list1.pDemo->pPrev->pNext = pTemp;

	list1.pDemo->pNext = list1.pDemo->pPrev = list1.pDemo;
}

template<class T>
void List<T>::Splice(iterator& Destination, List& list2, iterator& Source)
{
	Node<T> * pHead = NULL;
	Node<T> * pLast = NULL;

	pLast = Destination.GetCurrentNode();
	pHead = Source.GetCurrentNode();

	pHead->pPrev->pNext = pHead->pNext;
	pHead->pNext->pPrev = pHead->pPrev;

	pHead->pNext = pLast;
	pHead->pPrev = pLast->pPrev;
	pLast->pPrev = pHead;
	pHead->pPrev->pNext = pHead;
}

template<class T>
void List<T>::Sort()
{
	Node<T> * pSet = pDemo->pNext;
	Node<T> * pFind = pSet->pNext;

	while(pSet != pDemo)
	{
		if(pSet->tData > pFind->tData )
		{
				pFind->pPrev->pNext = pFind->pNext;
				pFind->pNext->pPrev = pFind->pPrev;

				pSet->pPrev->pNext = pFind;
				pFind->pPrev = pSet->pPrev;
			
				pSet->pPrev = pFind;
				pFind->pNext = pSet;

				pSet = pFind;
				pFind = pSet->pNext;
		}

			pFind = pFind->pNext;

			if(pFind == pDemo)
			{
				pSet = pSet->pNext;
				pFind = pSet;
			}
	}

	pSet = pFind = NULL;
}

template<class T>
void List<T>::operator=(List& refSource)
{
	T tData;

	Node<T> * pIter = refSource.pDemo->pNext;

	if(pDemo->pNext != pDemo)
	{
		cout << "About to DelteNode call " << endl;
		DeleteAllNode();
	}

	while(pIter != refSource.pDemo)
	{
		tData = pIter->tData;

		InsertLast(tData);
		
		pIter = pIter->pNext;
	}
}


template<class T>
void List<T>::Unique()
{
	int iCount = 0;
	
	Node<T> * pSet = pDemo->pNext;
	Node<T> * pFind = NULL;

	while(pSet != pDemo)
	{
		pFind = pSet->pNext;

			while(pFind != pDemo)
			{
				if(pSet->tData == pFind->tData)
				{
					pFind->pPrev->pNext = pFind->pNext;
					pFind->pNext->pPrev = pFind->pPrev;

					pFind->pNext = pFind->pPrev = NULL;

					iCount = 1;
					delete pFind;

					break;
				}

				pFind = pFind->pNext;
			}

			if(iCount != 1)
				pSet = pSet->pNext;

			iCount  = 0;
	}

}


template<class T>
void List<T>::DeleteAllNode()
{
	if(pDemo == pDemo->pNext)
		return;

	while(pDemo != pDemo->pNext)
	{
		pDemo->pPrev = pDemo->pNext->pNext;

		pDemo->pNext->pPrev = NULL;
		pDemo->pNext->pNext = NULL;

		delete pDemo->pNext;

		pDemo->pNext = pDemo->pPrev;
	}
}

template<class T>
ostream& operator << (ostream &out,  List<T> &refObj)
{
	Node<T> * pTemp = NULL;

	if(NULL == refObj.pDemo)
		out << "Linked List Is Empty\n";
	else
	{
		pTemp = refObj.pDemo->pNext;

	do
	{
		out << "<-|" << pTemp->tData << "|->";
		pTemp = pTemp->pNext;
		
	}while(refObj.pDemo != pTemp);

	cout <<endl;
	pTemp =NULL;
	}

	return out;
}

template<class T>
void List<T>::InsertFirst(T iNo)
{
	Node<T> *pNewNode = NULL;

	pNewNode = new Node<T>;
		if(NULL == pNewNode)
			return;

	pNewNode ->tData = iNo;

		if(pDemo == pDemo->pNext)
		{
			pDemo->pPrev = pNewNode;
			pNewNode->pNext = pDemo;
		}
		else
		{
			pNewNode->pNext = pDemo->pNext;
			pNewNode->pNext->pPrev = pNewNode;
		}

	pDemo->pNext = pNewNode;
	pNewNode->pPrev = pDemo;

}

template<class T>
void List<T>::Merge(List& refObj2)
{
	Splice(begin(), refObj2);
	
	Sort();
}

template<class T>
void List<T>::InsertLast(T iNo)
{
	Node<T> * pNewNode = NULL;

	pNewNode = new Node<T>;
		if(NULL == pNewNode)
			return;

	pNewNode->tData = iNo;
		
		if(pDemo == pDemo->pNext)
		{
			pDemo->pNext = pNewNode;
			pNewNode->pPrev = pDemo;
		}
		else
		{
			pNewNode->pPrev = pDemo->pPrev;
			pNewNode->pPrev->pNext = pNewNode;
		}

	pDemo->pPrev = pNewNode;
	pNewNode->pNext = pDemo;

}

template<class T>
void List<T>::InsertAtPosition(T iNo, int iPos)
{
	int iCount; 
	int iCounter;

	 Node<T> *pNewNode = NULL;
	 Node<T> *pTemp = NULL;

	iCount = CountNode();

	if(iPos <= 0 || iPos > (iCount + 1))
	{
		cout << "Invalid Possion" << endl;
		return;
	}

	if(1 == iPos)
	{
		InsertFirst(iNo);
		return;
	}

	if(iPos == (iCount+1) )
	{
		InsertLast(iNo);
		return;
	}

	pNewNode = new Node<T>;
	if(NULL == pNewNode)
	{
		cout << "Memoy Allocation Failed" << endl;
		return;
	}

	pNewNode->tData = iNo;

	pTemp = pDemo->pNext;
	iCounter = 1;

	while(iCounter < (iPos - 1))
	{
		pTemp = pTemp->pNext;
		iCounter++;
	}

	pNewNode->pNext = pTemp->pNext;
	pNewNode->pNext->pPrev = pNewNode;
	pTemp->pNext = pNewNode;
	pNewNode->pPrev = pTemp;
}

template<class T>
T List<T>::DeleteFirst()
{
	T tDel;
	Node<T> *pTemp = NULL;

	if(NULL == pDemo)
	{
		cout << "Linked List is Empty\n";
		return -1;
	}

	pTemp = pDemo->pNext;

	if(pDemo != pTemp)
	{
		pTemp->pNext->pPrev = pDemo;
		pDemo->pNext = pTemp->pNext;

		iDel = pTemp->iData;

		pTemp->pNext = NULL;
		pTemp->pPrev = NULL;
	}

	delete pTemp;
	pTemp = NULL;

	return tDel;
}

template<class T>
T List<T>::DeleteLast()
{
	T tDel;

	Node<T> *pTemp = NULL;
	
	pTemp = pDemo->pPrev;

	if(pDemo != pTemp)
	{
		pTemp->pPrev->pNext = pDemo;
		pDemo->pPrev = pTemp->pPrev;

		iDel = pTemp->iData;

		pTemp->pNext = NULL;
		pTemp->pPrev = NULL;
	}

	delete pTemp;
	pTemp = NULL;

	return tDel;
}

template<class T>
T List<T>::DeleteAtPosition(int iPos)
{
	T tDel;
	int iCount;
	int iCounter;
	Node<T> *pTemp = NULL;

	if(NULL == pDemo)
	{
		cout<< "Linked List Is Empty\n";
		return -1;
	}

	iCount = CountNode();
	
	if(iPos <= 0 || iPos > iCount )
	{
		cout << "Invalid Possion\n";
		return -1;
	}

	if(1 == iPos)
	{
		iDel = DeleteFirst();
		return iDel;
	}

	if(iPos == iCount)
	{
		iDel = DeleteLast();
		return iDel;
	}

	pTemp = pDemo->pNext;
	iCounter = 1;

	while(iCounter != iPos )
	{
		iCounter++;
		pTemp = pTemp->pNext;
	}

	pTemp->pPrev->pNext = pTemp->pNext;
	pTemp->pNext->pPrev = pTemp->pPrev;
	iDel = pTemp->iData;

	pTemp->pNext =NULL;
	pTemp->pPrev = NULL;
	
	delete pTemp;
	pTemp = NULL;

	return tDel;
}

template<class T>
int List<T>::SearchFirstOccurrence(T iNo)
{
	int iPos =  -1;
	int iCounter = 0;
	Node<T> *pTemp = pDemo->pNext;

	if(NULL == pDemo)
		return iPos;

	while(pTemp != pDemo )
	{
		iCounter++;

		if(pTemp->tData == iNo)
		{
			iPos = iCounter;
			break;
		}

		pTemp = pTemp->pNext;
	}
	
	pTemp = NULL;
	return iPos;
}

template<class T>
int List<T>::SearchLastOccurrence(T iNo)
{
	int iPos = -1;
	int iCounter = 0;
	Node<T> *pTemp = pDemo->pNext;

	if(NULL == pDemo)
		return iPos;

	while(pTemp != pDemo)
	{
		iCounter++;

		if(pTemp->tData == iNo)
			iPos = iCounter;

		pTemp = pTemp->pNext;
	}

	pTemp = NULL;
	return iPos;
}


template<class T>
int List<T>::SearchAllOccurrence(T iNo)
{
	int iPos = 0;
	int iCounter = 0;
	Node<T> *pTemp = pDemo->pNext;

	if(NULL == pDemo)
		return iPos;

	while(pTemp != pDemo)
	{
		iCounter++;

		if(pTemp->tData == iNo)
			iPos++;

		pTemp = pTemp->pNext;
	}

	pTemp =  NULL;
	return iPos;
}

template<class T>
int List<T>::CountNode()
{
	Node<T> * pTemp = pDemo->pNext;
	int iCounter = 0;

	if(NULL == pTemp)
		return iCounter;

	while( pDemo != pTemp)
	{
		iCounter++;
		pTemp = pTemp->pNext;
	}

	pTemp =  NULL;
	return iCounter;
}

template<class T>
void List<T>::Display()
{
	Node<T> * pTemp = NULL;

	cout << endl << " pDemo id -:" <<pDemo << endl;
	cout << endl << "pDemo -> pNext" << pDemo->pNext;
	cout << endl << " pDemo -> pPrev" << pDemo->pPrev << endl;

	if(NULL == pDemo)
	{
		cout << "Linked List Is Empty\n";
		return;
	}
	
	pTemp = pDemo->pNext;

	while(pDemo != pTemp)
	{
		cout << "<-|" << pTemp->tData << "|->";
		pTemp = pTemp->pNext;
	}
	

	cout <<endl;
	pTemp =NULL;
}

template<class T>
bool List<T>::IfListEmpty()
{
	if(pDemo->pNext->pPrev == pDemo->pPrev)
		return false;
	else
		return true;
}

