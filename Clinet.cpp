
//#include<iostream>
#include"Server.h"

//using std::cout;
//using std::endl;
//using std::cin;

template<class T>
void PrintList(List<T> & l1, List<T>& l2)
{
	cout<< endl <<"List1: \t";
	
	for(typename List<T>::iterator iter = l1.begin(); iter != l1.end(); iter++)
		cout <<"<-|" << *iter  << "|->";

	cout<< endl <<"List2:\t";
	
	for(typename List<T>::iterator iter = l2.begin(); iter != l2.end(); iter++)
		cout <<"<-|" << *iter  << "|->";

	cout << endl << endl;
}

template<class T>
void MyMain(T);

int main(void)
{
	
	int iBool = 1;
	int iChoice;

	while(iBool)
	{
		cout << "\n1-:int\n2-:char\n3-:sing Precision floating Point(flolat)\n4-:Double Precision floating Point(double)\n5-:exit" <<endl;
		cout << "\nwhich type of linked list do you want-:\t";
		cin >> iChoice;

		if(iChoice <= 0 || iChoice >= 6)
		{
			cout << "\nInvalid Choice Enter Valid Choice " << endl;
			iChoice = 0;
		}


		switch(iChoice)
		{

		case 1 :
			MyMain(10);
			break;

		case 2 :
			MyMain('S');
			break;

		case 3 :
			MyMain(65.00f);
			break;

		case 4 :
			MyMain(60.00);
			break;

		case 5 :
			iBool = 0;
			break;
		}

	}
	return 0;
}


template<class T>
void MyMain(T)
{
	List<T> list1, list2;	// Creatr two Empty List

	for(T tNo = 0; tNo < 6; tNo++)
	{
		list1.push_back((T)tNo + 65);   // Fill Both List
		list2.push_front((T)tNo + 65);
	}

	PrintList(list1, list2);

	//insert all elements of list1 before the first element with value E of list2
	// - find() returns an iterator to the first element with value E

		// Destination			  // Source List 
	list2.Splice(find(list2.begin(), list2.end(),(T) 'E'), list1);
	PrintList(list1, list2);
		
	//move first element of list2 to the end
	list2.Splice(list2.end(), list2, list2.begin());
	PrintList(list1, list2);

	//sort second list,assign to list1 and remove duplicates
	list2.Sort();
	list1 = list2;
	list2.Unique();
	PrintList(list1, list2);

	//merge both sorted lists into the first list
	list1.Merge(list2);
	PrintList(list1, list2);
	
}

