#include<iostream>
#pragma warning (disable:4996)
#include<fstream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<list>
using namespace std;

//classes
template<class T>
class HashTable
{
private:
	list<T>** hashTableHead;
	int tableSize;//70% of (99999-5000) is ~123503 is prime..accroding to thumb rule, your buckets should be 1.3 times of actual enteries
public:
	HashTable();//allocate memory
	int static HashFormula(int);
	HashTable(int _tableSize);//allocate memory
	~HashTable();//deallocation
	int getTableSize() { return tableSize; }

	bool RequestFileAccessHashClass(UserInformation& queueUserInfo, int _fileID, char priority[4])
	{
		int index = HashFunction(_fileID);
		if (hashTableHead[index] == nullptr)
		{
			cout << "ERROR: File Not Exist";
			return false;
		}
		else
		{
			hashTableHead[index][0]::iterator i2 = hashTableHead[index]->begin();
			hashTableHead[index][0]::iterator i3 = hashTableHead[index]->end();
			for (i2; i2 != i3; i2++)
			{
				if (*i2.fileID == _fileID)
				{
					*i2.RequestFileAccessFileClass(queueUserInfo, _fileID, _priority);
				}
			}

		}
	}
	bool RequestFileAccessHashClass(UserInformation& queueUserInfo, int _fileID, int _priority)
	{
		int index = HashFunction(_fileID);
		if (hashTableHead[index] == nullptr)
		{
			cout << "File Not Exist";
			return false;
		}
		else
		{
			hashTableHead[index][0]::iterator i2 = hashTableHead[index]->begin();
			hashTableHead[index][0]::iterator i3 = hashTableHead[index]->end();
			for (i2; i2 != i3; i2++)
			{
				if (*i2 == _fileID)
				{
					*i2.RequestFileAccessFileClass(queueUserInfo, _fileID, _priority);
				}
			}
			
		}
	}

	void Insert(int nmbrtobehashed, T data);//hashfunction
	void Delete(bool allowedOrNot, T _data, int id);//pass template's function , Delete the file only if no one is currently accessing it
	void Print();//only print H_index-> and then cout<<hashTableHead[i][j]->data
	void LoadData();//loads data from file
};

//int HashFormula1(int num,int _tableSize)
//{
//	int a = 3991;
//	int b = 231;
//	int p = 100003;
//	return ((a*num + b) % p) % _tableSize;
//}
class File
{
private:
	MaxHeapQueue<UserInformation> queue;
	int fileID;
public:
	File();
	~File(){}
	File(int _fileID);

	//operators
	friend ostream& operator<<(ostream& out, File _file);
	bool operator==(File& rhs) { return fileID == rhs.fileID; }

	//functionalities
	bool RequestFileAccessFileClass(UserInformation& queueUserInfo, int _fileID, char priority[4])
	{
		if (!queue.isEmpty())
		{
			if (strcmp(priority, "high"))
			{
				int mypriority = (queue.FindMax()).priority;
				UserInformation u1(queueUserInfo.userID, queueUserInfo.operation, mypriority);
				queue.Insert(u1);
				return true;
			}
			else
			{
				int mypriority = (queue.FindMin()).priority;
				UserInformation u1(queueUserInfo.userID, queueUserInfo.operation, mypriority);
				queue.Insert(u1);
				return true;
			}
		}
		else
		{
			queue.Insert(queueUserInfo);
		}
	}
	bool RequestFileAccessFileClass(UserInformation& queueUserInfo, int _fileID, int priority)
	{
		if (!queue.isEmpty())
		{
		
			
				UserInformation u1(queueUserInfo.userID, queueUserInfo.operation, priority);
				queue.Insert(u1);
				return true;
			
		}
		else
		{
			queue.Insert(queueUserInfo);
		}
	}
	void  ReleaseFileFileClass(UserInformation& queueUserInfo, int _fileID)
	{
		if (!queue.isEmpty())
		{
			ofstream fout;
			fout.open("userIDTrack.txt");
			if (queueUserInfo.operation == 'w')
			{
				//exclusive access
				UserInformation u1 = queue.ExtractMax();
				fout <<"writing: "<< u1.userID << endl;

				return;
			}
			else
			{
				UserInformation wasteUser = queue.ExtractMax();
				while (wasteUser.operation != 'w' && !queue.isEmpty())
				{
					wasteUser = queue.ExtractMax();;
					fout << "reading: " << wasteUser.userID << endl;
				}
				return;
			}
		}
	}

};
class UserInformation
{
public:
	int userID;
	char operation;
	int priority;
	UserInformation()
	{
		userID = 0;
		operation = 'u';
		priority = 0;
	}
	UserInformation(int ter, char rt)
	{
		userID =ter;
		operation = rt;
		priority = 0;
	}
	UserInformation(int ter, char rt, int iy)
	{
		userID = ter;
		operation = rt;
		priority = iy;
	}
	bool operator>(UserInformation rhs);
	bool operator<(UserInformation rhs);
	bool operator==(UserInformation rhs);
	friend ostream& operator<<(ostream&, UserInformation rhs);
};

template<class T>
class QueueNode
{
public:
	int key;
	T data;
	QueueNode();
	QueueNode(int, T);
	~QueueNode();
	bool operator<(QueueNode);
	bool operator>(QueueNode);
	bool operator==(QueueNode);
	QueueNode& operator=(QueueNode);

};

template<class T>
class MaxHeapQueue
{
private:
	QueueNode<T> ** head;
	int currentSize;
	int maxSize;
	T minElement;
public:
	MaxHeapQueue();
	MaxHeapQueue(int);
	~MaxHeapQueue();
	void BuildQueue(T* arr, int caapacity );//takes unsorted array and convert into queue
	T ExtractMax();//removes and return max element
	T FindMax();
	T FindSecondMax();
	int getCurrentSize() { return getSize(); }
	T FindMin();
	void BubbleUp(int index);
	void BubbleDown(int index);
	bool Insert(T);
	int getSize();
	bool isEmpty();
	void PrintQueue();
};
int main()
{
//	vector<int> v1(5);
//	vector<int>:: iterator i1 = v1.begin();
//	for (int i = 0; i < 5; i++)
//	{
//		v1.insert(i1, i);
//	}
//	v1.resize(6);
//	//i1++;
//	v1.insert(i1, 990);
//	for (int i = 0; i < 6; i++)
//	{
//		cout << v1[i] << " ";
//	}
//	cout << endl;
	//list<int> l1;
	//list<int>::iterator i1 = l1.begin();
	//for (int i = 0; i < 10; i++)
	//{
	//	l1.insert(i1, i);
	//}
	////printing
	//for (i1 = l1.begin(); i1 != l1.end(); i1++)
	//{
	//	cout << *i1 << " ";
	//}
	//cout << endl;
	//cout << "inserting -99 at the end of list\n";
	//l1.push_back(-99);
	////printing
	//for (i1 = l1.begin(); i1 != l1.end(); i1++)
	//{
	//	cout << *i1 << " ";
	//}
	//cout << endl;
	//
	//cout << "deleting 5\n";
	//i1 = find(l1.begin(), l1.end(), 5);
	//i1++;
	//l1.erase(--i1);
	//cout << *i1<<" ";
	////printing
	//for (i1 = l1.begin(); i1 != l1.end(); i1++)
	//{
	//	cout << *i1 << " ";
	//}
	//cout << endl;
	//// i1++;
	//cout << "replacing it with 100";
	//l1.insert(i1, 100);
	////pritning
	//for (i1 = l1.begin(); i1 != l1.end(); i1++)
	//{
	//	cout << *i1 << " ";
	//}
	//cout << endl;
	system("pause");
}

template<class T>
QueueNode<T>::QueueNode()
{
	key = -1;
}

template<class T>
QueueNode<T>::QueueNode(int _key, T _data)
{
	key = _key;
	data = _data;
}

template<class T>
QueueNode<T>::~QueueNode()
{
	//do nothing
}

template<class T>
bool QueueNode<T>::operator<(QueueNode temp)
{
	return key<temp.key;
}

template<class T>
bool QueueNode<T>::operator>(QueueNode temp)
{
	return key>temp.key;
}

template<class T>
bool QueueNode<T>::operator==(QueueNode temp)
{
	return key==temp.key;
}

template<class T>
QueueNode<T> & QueueNode<T>::operator=(QueueNode rhs)
{
	if (this != &rhs)
	{
		key = rhs.key;
		data = rhs.data;
	}
	return *this;
	// TODO: insert return statement here
}

template<class T>
MaxHeapQueue<T>::MaxHeapQueue()
{
	head  = new QueueNode<T>[100];
	currentSize = 0;
	maxSize = 100;
}

template<class T>
MaxHeapQueue<T>::MaxHeapQueue(int sz)
{
	head = new QueueNode<T>*[sz];
	currentSize = 0;
	maxSize = sz;
}

template<class T>
MaxHeapQueue<T>::~MaxHeapQueue()
{
	if (currentSize == 1)
	{
		delete head[0];
		head[0] = nullptr;
		delete head;
		head = nullptr;
	}
	else if(currentSize>1)
	{
		for (int i = 0; i < currentSize; i++)
		{
			delete head[i];
			head[i] = nullptr;
		}
		delete[] head;
		head = nullptr;
	}
}

template<class T>
void MaxHeapQueue<T>::BuildQueue(T * arr, int capacity)
{
	if (capacity <= 100)
	{
		for (int i = 0; i < capacity; i++)
		{
			Insert(arr[i]);
		}
		int temp = currentSize / 2;
		for (temp; temp >= 0; temp--)
		{
			BubbleDown(temp);
		}
	}
}

template<class T>
T MaxHeapQueue<T>::ExtractMax()
{
	if (currentSize > 0)
	{
		T retData;
		retData = head[0][0].data;
		head[0] = head[currentSize - 1];
		currentSize--;
		BubbleDown(0);
		return retData;
	}
}

template<class T>
T MaxHeapQueue<T>::FindMax()
{
	if (currentSize > 0)
	{
		return head[0][0].data;
	}
}

template<class T>
T MaxHeapQueue<T>::FindSecondMax()
{
	if (currentSize >=3)
	{
		if (head[1][0] >= head[2][0])
		{
			return head[1][0].data;
		}
		else
		{
			return head[2][0].data;
		}
		
	}
	else
	{
		return 0;
	}
}

template<class T>
T MaxHeapQueue<T>::FindMin()
{
	if (currentSize > 0)
	{
		return minElement;
	}
}

template<class T>
void MaxHeapQueue<T>::BubbleUp(int index)
{
	if (index <= 0)
		return;
	int parent = (index - 1) / 2;
	QueueNode<T>* temp = nullptr;
	while (parent >= 0 && head[parent][0] < head[index][0])
	{
		//swapping of parent and child
		temp = head[parent];
		head[parent] = head[index];
		head[index] = temp;
		index = parent;
		parent = (index - 1) / 2;
	}
}

template<class T>
void MaxHeapQueue<T>::BubbleDown(int index)
{
	if (index >= currentSize-1)
		return;
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	QueueNode<T>* temp = nullptr;
	while (rightChild < currentSize && (head[leftChild][0] > head[index][0] || head[rightChild][0] > head[index][0]))
	{
		//swapping of parent and left child
		if (leftChild<currentSize && head[leftChild][0] > head[rightChild][0])
		{
			temp = head[leftChild];
			head[leftChild] = head[index];
			head[index] = temp;

			index = 2 * index + 1;
		}
		else if(rightChild<currentSize &&  head[rightChild][0] > head[leftChild][0])
		{
			//swapping of parent and right child
			temp = head[rightChild];
			head[rightChild] = head[index];
			head[index] = temp;

			index = 2 * index + 2;
		}
		leftChild = 2 * index + 1;
		rightChild = 2 * index + 2;
	}
}

template<class T>
bool MaxHeapQueue<T>::Insert(T _data)
{
	currentSize++;
	if (currentSize > maxSize)
		return false;
	QueueNode<T>* temp = new QueueNode<T>(currentSize - 1, _data);
	if (currentSize == 1)
	{
		head[currentSize - 1] = temp;
		minElement = temp->data;
	}
	else
	{
		head[currentSize - 1] = temp;
		if (minElement > temp->data)
		{
			minElement = temp->data;
		}
		BubbleUp(currentSize - 1);
		return true;
	}
}

template<class T>
int MaxHeapQueue<T>::getSize()
{
	return currentSize;
}

template<class T>
bool MaxHeapQueue<T>::isEmpty()
{
	return currentSize == 0;
}

template<class T>
void MaxHeapQueue<T>::PrintQueue()
{
	for (int i = 0; i < currentSize; i++)
	{
		cout << head[i]->data<<endl;
	}
}

ostream & operator<<(ostream & out, File _file)
{
	out << "File "<<_file.fileID<<"...Access granted to ";
	if (_file.queue.isEmpty() == 0)
	{
		out << "none\n\t\tNext none\n\t\tWaiting none\n";
	}
	else
	{
		out << _file.queue.FindMax() << endl << "\t\tNext ";
		if (_file.queue.FindSecondMax())
		{
			out << _file.queue.FindSecondMax() << endl << "\t\tWaiting "<< _file.queue.getCurrentSize()-2<<" users";
		}
		else
		{
			out << "none\n\t\tWaiting none";
		}
	}
	return out;
	// TODO: insert return statement here
}

ostream & operator<<(ostream & out, UserInformation rhs)
{
	out << rhs.userID << " ";
	if (rhs.operation=='w')
	{
		out << "write";
	}
	else
	{
		out << "read";
	}
	return out;
	// TODO: insert return statement here
}

bool UserInformation::operator>(UserInformation rhs)
{
	if (priority != 0)
	{
		return priority>rhs.priority;
	}
	return userID>rhs.userID;
}

bool UserInformation::operator<(UserInformation rhs)
{
	if (priority != 0)
	{
		return priority<rhs.priority;
	}
	return userID<rhs.userID;
}

bool UserInformation::operator==(UserInformation rhs)
{
	if (priority != 0)
	{
		return priority==rhs.priority;
	}
	return userID==rhs.userID;
}

template<class T>
HashTable<T>::HashTable()
{
	tableSize = 101;
	hashTableHead = new list<T>*[tableSize];
	for (int i = 0; i < tableSize; i++)
	{
		
			hashTableHead[i] = nullptr;
		
	}
}

template<class T>
int HashTable<T>::HashFormula(int num)
{
	int a = 3991;
	int b = 231;
	int p = 100003;
	return ((a*num + b) % p) % tableSize;
}

template<class T>
HashTable<T>::HashTable(int _tableSize)
{
	tableSize = _tableSize;
	hashTableHead = new list<T>*[tableSize];
	for (int i = 0; i < tableSize; i++)
	{

		hashTableHead[i] = nullptr;

	}
}

template<class T>
HashTable<T>::~HashTable()
{
	if (hashTableHead)
	{
		for (int i = 0; i < tableSize; i++)
		{
			if (hashTableHead)
			{
				delete hashTableHead[i];
				hashTableHead[i] = nullptr;
			}
		}
		delete[] hashTableHead;
		hashTableHead = nullptr;
	}
}

template<class T>
void HashTable<T>::Insert(int nmbrtobehashed, T data)
{
	int index = HashFormula(nmbrtobehashed);
	if (hashTableHead[index]==nullptr)
	{
		hashTableHead[index] = new list<T>;
	}
	hashTableHead[index]->push_back(data);
	
}

template<class T>
void HashTable<T>::Delete(bool allowedOrNot, T _data, int id)
{
	if (allowedOrNot)
	{
		int index = HashFormula(id);
		if (hashTableHead[index])
		{
			hashTableHead[index][0]::iterator i1 = hashTableHead[index]->begin();
			i1 = find(hashTableHead[index]->begin(), hashTableHead[index]->end(), _data);
			if (i1)
			{
				hashTableHead[index]->remove(i1);
			}
			else
			{
				cout << "Error: " << _data << " with ID: " << id << " not found\n";
			}
		}
	}
}

template<class T>
void HashTable<T>::Print()
{
	for (int i = 0; i < tableSize; i++)
	{
		if (hashTableHead[i])
		{
			hashTableHead[i][0]::iterator i1 = hashTableHead[i]->begin();
			for (i1; i1 != hashTableHead[i]->end(); i1++)
			{
				cout << "H" << i << "->";
				cout << *i1 << endl;
			}
		}
	}
}

File::File()
{
	fileID = -1;
}

File::File(int _fileID)
{
	fileID = _fileID;
}


