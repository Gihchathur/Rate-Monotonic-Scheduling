/*NAME - H.K.A.G.CHATHURANGA
INDEX  - 17/ENG/016
REGISTRATION - EN86135*/

#include <iostream>
#include<vector>
using namespace std;

//structure for creating process
struct job {
	
	int brusttime;
	int period;
	int count = 0;//num of completed processes
	int reminder = 0;//num of completed processes
	int finishedCount = 0;
};


//firstly sort the period and bursttime according to the period time
//bubble sort function
void bubblesort_float(job *var, int size)
{

	for (int i = 0; i < size-1; i++) {
		for (int j = i; j < size; j++) {
			if (var[i].period > var[j].period) {
				float tmp = var[i].period;
				var[i].period = var[j].period;
				var[j].period = tmp;
				float tmp2 = var[i].brusttime;
				var[i].brusttime = var[j].brusttime;
				var[j].brusttime = tmp2;
			}
		}
	}
}
//that gcd and lcm using to calculate the lcm of set of all process periods
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}
int findlcm(vector<int> arr)
{
	int n = arr.size();
	int ans = arr[0];


	for (int i = 1; i < n; i++)
		ans = (((arr[i] * ans)) / (gcd(arr[i], ans)));

	return ans;
}

//this function calculate this can be processed or not
void calculate(job* var, int size,int lcm)
{
	
	//consider second by seconds to lcm
	for (int time = 0; time < lcm ; time++)
	{
		for (int x = 0; x < size; x++)
		{
			if (var[x].period * var[x].count <= time)
			{
				if ((time - var[x].period * var[x].count ) < var[x].brusttime)
				{
					var[x].reminder++;
					//if all the process should process ,increment the reminder of each structure object
				}

			}

		}
		//in this part we select the just proceed process and decrement the reminder value of reminder
		//and also we check reminder value is equal to the burst time and increment the count
		for (int x = 0; x < size; x++)
		{
			if (var[x].reminder > 0)
			{
				
				var[x].finishedCount++;
				var[x].reminder--;
				if (var[x].finishedCount >= var[x].brusttime)
				{
					var[x].finishedCount = 0;
					var[x].count++;
				}

				x = size + 1;
			}
			

		}


		

	}
	int cnt = 0;
	//check all process can proceed
	for (int x = 0; x < size; x++)
	{
		
		if ((lcm / var[x].period) <= var[x].count)
		{
			cnt++;
		}

	

	}
	//print final output
	if (cnt == size)
	{
		cout << "\n-----------------------------------\n";
		cout << "Period\tBurst Time\n";
		for (int x = 0; x < size; x++)
		{
			cout<<var[x].period << "\t  ";
			cout << var[x].brusttime; 
			if ((lcm / var[x].period) <= var[x].count)
			{
				cout << "\t - This process can be completed\n";
			}
			else
			{
				cout << "\t - This process cannot be completed\n";
			}

			

		}
		cout << "\n-----------------------------------\n\n";
		cout << "set of processes can be completed";
		cout << "\n\n-----------------------------------\n\n";

	}
	else
	{
		cout << "\n-----------------------------------\n";
		cout << "Period\tBurst Time\n";
		for (int x = 0; x < size; x++)
		{
			cout<< var[x].period << "\t  ";
			cout << var[x].brusttime;
			if ((lcm / var[x].period) <= var[x].count)
			{
				cout << "\t - This process can be completed\n";
			}
			else
			{
				cout << "\t - This process cannot be completed\n";
			}



		}
		cout << "\n-----------------------------------\n\n";
	
		
		cout << "set of processes cannot be completed\n\n";
		cout << "-----------------------------------\n\n";
	}
}


int main()
{
	//user input how many process
	int numOfProcess;
	cout << "Enter number of process :";
	
	cin >> numOfProcess;

	//create a vector
	vector<int> arr;
	job* var = new job[numOfProcess];

	for (int x = 0; x < numOfProcess; x++)
	{
		cout << "Enter process " << x+1 << " period time :";
		cin >> var[x].period;
		arr.push_back(var[x].period);
		
		cout << "Enter process " << x+1 << " Brust time :";
		cin >> var[x].brusttime;
	}

	////firstly sort the period and bursttime according to the period time
	bubblesort_float(var, numOfProcess);

	

	int lcmValue= findlcm(arr);
	
	//call the calculate function
	calculate(var, numOfProcess, lcmValue);


	return 0;
}