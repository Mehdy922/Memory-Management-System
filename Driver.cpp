#include<iostream>
#include"1784.cpp"
using namespace std;

int main()
{
	bool strategy = false;
	bool run = true;
	int RAM = 0;
	int input = 0;

	cout << "Enter True (1) for First Come Strategy && False (0) for Best Fit Strategy" << endl;
	cin >> strategy;
	cout << endl;

	cout << "Enter RAM size" << endl;
	cin >> RAM;

	memoryManagementSystem object(RAM, strategy);
	object.addBlockToPool(0, RAM);

	while (run == true)
	{
		cout << endl;
		cout << "Press 1 to enter a program" << endl;
		cout << "Press 2 to delete a program" << endl;
		cout << "Press 3 to view the Pool (Memory of free blocks)" << endl;
		cout << "Press 4 to view the Programs in Memory" << endl;
		cout << "Press 5 to exit the program" << endl;
		cout << endl;

		cin >> input;

		if (input == 1)
		{
			char* programId = new char[8];
			int memoryRequired = 0;
			cout << "Enter Program ID" << endl;
			cin >> programId;
			cout << "Enter memory required for the program" << endl;
			cin >> memoryRequired;
			if (object.GetMem(programId, memoryRequired))
			{
				cout << "Memory succesfully allocated" << endl;
			}
			else
			{
				cout << "Memory not available" << endl;
			}
		}
		else if (input == 2)
		{
			char* programId = new char[8];
			cout << "Enter Program ID which you wish to delete for eg P1" << endl;
			cin >> programId;
			if (object.deleteProgram(programId))
			{
				cout << "Memory succesfully deallocated" << endl;
			}
			else
			{
				cout << "Memory can't be deallocated. Program does not exist" << endl;
			}
		}
		else if (input == 3)
		{
			object.printMemoryPool();
		}
		else if (input == 4)
		{
			object.printProgs();
		}
		else if (input == 5)
		{
			run = false;
			cout << "Program exited." << endl;
		}
		else
		{
			cout << "Invalid Input. Enter again" << endl;
		}
	}
}