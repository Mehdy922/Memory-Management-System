#include <iostream>
using namespace std;

template<class T>
class List
{
public:
	List()
	{
		tail = NULL;
		head = NULL;
	}
	//=============================================================================
	//Helper Functions
	bool checkPool()
	{
		return (head == tail == NULL);
	}
	bool search(char i[])
	{
		string check = i;
		bool flag = false;
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data->returnID() == check)
			{
				flag = true;
				break;
			}
		}
		return flag;
	}
	void setID(string i)
	{
		Node* tmp = head;
		tmp->data->placeID(i);
	}
	int NoofProgBlocks(char i[])
	{
		string check = i;
		bool flag = false;
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data->returnID() == check)
			{
				if (tmp->data->isEmpty() == true)
				{
					return 0;
				}
				else
				{
					return (tmp->data->countallBLocks());
				}
				break;
			}

		}
	}
	//=============================================================================
	//Main Functions
	int getMemoryFromPool(int size, bool stratagy)
	{
		int Start_Byte = -1;

		if (stratagy)
		{
			Node* ite;
			for (ite = head; ite != NULL; ite = ite->next)
			{
				if (ite->data->total_bytes >= size)
				{
					Start_Byte = ite->data->start_byte_ID;
					ite->data->start_byte_ID = ite->data->start_byte_ID + size;
					ite->data->total_bytes = ite->data->total_bytes - size;

					if (ite->data->total_bytes == 0)
					{
						DeletePool(ite->data->start_byte_ID);
					}

					break;
				}
			}
		}

		else
		{
			Node* ite;
			Node* temp = NULL;
			int min;

			for (ite = head; ite != NULL; ite = ite->next)
			{
				if (ite->data->total_bytes >= size)
				{
					min = ite->data->total_bytes;
					temp = ite;
					break;
				}
			}


			for (ite = head; ite != NULL; ite = ite->next)
			{
				if (ite->data->total_bytes >= size && ite->data->total_bytes <= min)
				{
					min = ite->data->total_bytes;
					temp = ite;
				}
			}

			if (temp != NULL)
			{
				Start_Byte = temp->data->start_byte_ID;
				temp->data->start_byte_ID += size;
				temp->data->total_bytes = temp->data->total_bytes - size;

				if (temp->data->total_bytes == 0)
				{
					DeletePool(temp->data->start_byte_ID);
				}
			}

		}

		return Start_Byte;


	}

	//=============================================================================
	
	//Functions called for nodes arrangment
	void Sort()
	{
		Node* tmp;
		Node* tmp2;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			for (tmp2 = head; tmp2 != NULL; tmp2 = tmp2->next)
			{
				if (tmp2->data->start_byte_ID > tmp->data->start_byte_ID)
				{
					int temp = tmp2->data->start_byte_ID;
					tmp2->data->start_byte_ID = tmp->data->start_byte_ID;
					tmp->data->start_byte_ID = temp;

					temp = tmp2->data->total_bytes;
					tmp2->data->total_bytes = tmp->data->total_bytes;
					tmp->data->total_bytes = temp;
				}
			}
		}

	}
	void merge()
	{
		Node* temp;
		for (temp = head; temp != NULL; temp = temp->next)
		{
			if (temp->next != NULL)
			{
				if (temp->data->start_byte_ID + temp->data->total_bytes == temp->next->data->start_byte_ID)
				{
					int tmp = temp->data->total_bytes;
					temp->data->total_bytes = tmp + temp->next->data->total_bytes;
					if (temp->next->next != NULL)
					{
						temp->next = temp->next->next;
					}
					else
					{
						temp->next = NULL;
					}
				}
			}
		}
	}
	
	//=============================================================================

	//Printing and adding functions

	void addToPool(int start, int tB)
	{
		if (head != NULL) {
			Node* n = new Node(start, tB, head);
			head = n;
		}
		else
			head = tail = new Node(start, tB);
	}
	void addToProg(char id[], int start, int tB)
	{
		if (search(id) != true)
		{
			if (head != NULL)
			{
				Node* n = new Node(start, tB, head);
				head = n;
			}
			else
				head = tail = new Node(start, tB);
		}
		else if (search(id) == true)
		{
			string check = id;
			Node* tmp;
			for (tmp = head; tmp != NULL; tmp = tmp->next)
			{
				if (tmp->data->returnID() == check)
				{
					tmp->data->addTohead(start, tB);
					break;
				}
			}
		}
	}
	void PrintPool()
	{
		cout << endl;
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			tmp->data->Print();
		}
		cout << endl;
	}
	void PrintProg()
	{
		cout << endl;
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			cout << "Program : " << tmp->data->returnID() << endl;
			tmp->data->printProgram();
		}
		cout << endl;
	}
	

	//=============================================================================
	void DeletePool(int startByte)
	{
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (head->data->start_byte_ID == startByte)
			{
				if (head->next != NULL)
				{
					head = head->next;
				}
				else
				{
					head = tail = NULL;
				}
				break;
			}
			if (tmp->next->data->start_byte_ID == startByte)
			{
				if (tmp->next->next != NULL)
				{
					tmp->next = tmp->next->next;
				}
				else
				{
					tmp->next = NULL;
					tmp = tail;
				}
				break;
			}
		}
	}
	void deleteBlocks(char i[], int& x, int& y)
	{
		string check = i;
		Node* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data->returnID() == check)
			{
				if (tmp->data->isEmpty() != true)
				{
					tmp->data->DeleteProg(x, y);
				}
				else
				{
					break;
				}
			}
		}
	}
	void deleteprogs(char i[])
	{
		string check = i;
		int flag = 0;

		if (head->data->returnID() == check)
		{
			if (head->next == NULL)
			{
				head = NULL;
			}
			else
			{
				head = head->next;
			}
			flag = 1;
		}

		if (flag == 0)
		{
			Node* tmp;
			for (tmp = head; tmp != NULL; tmp = tmp->next)
			{
				if (tmp->next->data->returnID() == check)
				{
					if (tmp->next->next == NULL)
					{
						tmp->next = NULL;
						tail = tmp;
					}
					else
					{
						tmp->next = tmp->next->next;
					}
					break;
				}
			}
		}
	}
	//=============================================================================

	~List()
	{
		Node* p = head;
		while (head!=NULL) {
			p = head->next;
			delete head;
			head = p;
		}
		tail = NULL;
	}
private:

	struct Node
	{
	public:
		Node()
		{
			next = NULL;
		}
		Node(int val1, int val2, Node* nptr = 0)
		{
			data = new T(val1, val2);
			next = nptr;
		}

		T* data;
		Node* next;
	};
	Node* head;
	Node* tail;

};

class Blocks
{
public:
	Blocks()
	{
		start_byte_ID = 0;
		total_bytes = 0;
		next = NULL;
	}
	Blocks(int st, int tb, Blocks* n = NULL)
	{
		start_byte_ID = st;
		total_bytes = tb;
		next = n;
	}
	void Print()
	{
		cout << " Starting byte : " << start_byte_ID << "\t\tSize : " << total_bytes << endl;
	}

	int start_byte_ID;
	int total_bytes;
	Blocks* next;
};

class Programs
{
public:
	//=============================================================================
	Programs(int st, int tb, Blocks* n = NULL)
	{
		sb = st;
		size = tb;
		addTohead(st, size);
		nxt = NULL;
	}
	~Programs()
	{
		Blocks* p = head;
		while (head != NULL) {
			p = head->next;
			delete head;
			head = p;
		}
		tail = NULL;
	}
	//=============================================================================
	//Helper functions getters and setters
	int countallBLocks()
	{
		Blocks* tmp;
		int count = 0;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			count++;
		}
		return count;
	}
	string returnID()
	{
		return id;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
	void placeID(string i)
	{
		id = i;
	}
	//=============================================================================
	//Other printing and adding functions
	void addTohead(int start, int tB)
	{
		if (head != NULL) {
			Blocks* n = new Blocks(start, tB, head);
			head = n;
		}
		else
			head = tail = new Blocks(start, tB);
	}
	void DeleteProg(int& x, int& y)
	{
		Blocks* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (head->next != NULL)
			{
				x = head->start_byte_ID;
				y = head->total_bytes;
				head = head->next;
				break;
				
			}
			else
			{
				x = head->start_byte_ID;
				y = head->total_bytes;
				head = tail = NULL;
				break;
			}
		}
	}
	void printProgram()
	{
		Blocks* tmp;
		for (tmp = head; tmp != NULL; tmp = tmp->next)
		{
			tmp->Print();
		}
		cout << endl;
	}
	
private:
	List<Blocks> obj;
	int sb;
	int size;
	string id;
	Blocks* head;
	Blocks* tail;
	Blocks* nxt;

};

class memoryManagementSystem
{
private:
	List<Blocks> Pool;
	List<Programs> Prog;
	int sizeOfMemory;
	bool strategy;

public:
	//Main functions used in this assignment
	memoryManagementSystem()
	{
		strategy = 0;
		sizeOfMemory = NULL;

	}
	memoryManagementSystem(int smem, bool strat)
	{
		strategy = strat;
		sizeOfMemory = smem;

	}
	void addBlockToPool(int start, int end)
	{
		Pool.addToPool(start, end);
	}
	bool GetMem(char id[], int size)
	{
		int startByte = Pool.getMemoryFromPool(size, strategy);
		if (startByte == -1) {
			return false;
		}
		else {
			Prog.addToProg(id, startByte, size);
			string name = id;
			if (!Prog.search(id))
			{
				Prog.setID(name);
			}
			return true;
		}
	}
	void printMemoryPool()
	{	
		Pool.PrintPool();
	}
	void printProgs()
	{
		Prog.PrintProg();
	}
	bool deleteProgram(char id[])
	{
		if (!Prog.search(id))
		{
			return false;
		}

		else
		{
			int size;
			int start;
			int TotalBlocks = Prog.NoofProgBlocks(id);
			for (int i = 0; i < TotalBlocks; i++)
			{
				size = 0;
				start = 0;
				Prog.deleteBlocks(id, start, size);
				Pool.addToPool(start, size);
			}
			Prog.deleteprogs(id);
			Pool.Sort();
			for (int j = 0; j < 5; j++)
			{
				Pool.merge();
			}
			return true;
		}
	}
};
