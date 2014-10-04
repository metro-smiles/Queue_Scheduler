// EE 465, USC


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define INFIN  			999999999

// Function Name:	expon
// Description: 	Generates an exponentially distributed random number 
//					with parameter \lambda. 
// Input: 			lambda (double)
// Output: 			An exponentially distributed random number (double)
//
double expon(double lambda)
{
	double u; // used to store a random number. 
	
	do
	{
		u = drand48(); //uniform number in the interval [0.0, 1.0]
	}
	while ((u == 0) || (u == 1)); //special cases that we want to avoid
	
	return -log(1-u)/lambda;
	
}

// Function Name:	print_stats
// Description: 	Saves and prints system statistics 
// Input:           stats_file (ostream object): ostream object for the stats file
//					avg_customers (double): average customers in the system
//					avg_service_time (double): average service time 
// Output: 			void (output stored to file and printed in the screen)
//
void print_stats(ostream &stats_file, double avg_customers, double avg_wait_time_sys, double avg_service_time, double avg_delay_sys, double sys_idle_time, double block_prob)
{
	cout << "Average Number of customers in the system: " << avg_customers << endl;
	cout << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
	cout << "Average Service time: " << avg_service_time << endl;
  cout << "Average Delay per customer: " << avg_delay_sys << endl;
  cout << "Idle Period of the server: " << sys_idle_time << endl;
	cout << "Blocking Probability: " << block_prob << endl;
	
	stats_file << "Average Number of customers in the system: " << avg_customers << endl;
	stats_file << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
	stats_file << "Average Service time: " << avg_service_time << endl;
  stats_file << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
  stats_file << "Idle Period of the server: " << sys_idle_time << endl;
	stats_file << "Blocking Probability: " << block_prob << endl;
}

// The main function of the program that is called at the beginning.
int main(int argc, char *argv[]) {
	//system variables
	long int tot_arrivals, cur_arrivals = 0, cur_departures = 0;
	double lambda;
	double event1 = 0.0, event2 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0, customers = 0.0, sys_idle_time = 0.0, avg_wait_time_sys = 0.0, seed;
	double avg_customers = 0.0, avg_service_time = 0.0; //used for calculating statistics
	double utilization; // used for computing the Utilization of the Queue
	ofstream stats_file; //file handler for saving the statistics in a file
	
   if ( argc != 3 )
    cout << "Enter only the number of arrivals and the seed value as parameters." << endl;
   else
    tot_arrivals = atoi(argv[1]);
    seed = atoi(argv[2]); 
	//get input from the user
 
	/*cout << "Basic M/G/1 Simulator" << endl;
	cout << "Enter the total number of arrivals: ";
	cin >> tot_arrivals;
  cout << "Enter the seed value: ";
	cin >> seed;*/
	
  srand48(seed); // Random Number generation
  lambda = 0.1;
	
	double **at_dt;			
	stats_file.open ("stats_MG1.txt"); //it creates the file, if it does not exist
	
	at_dt=new double*[tot_arrivals]; //creates a new array of pointers to double objects
	for(int i=0; i<tot_arrivals; ++i)
		at_dt[i]=new double[2];

	// discrete event simulator 
	while (cur_arrivals < tot_arrivals)
	{
		if (event1 < event2)	//arrival
		{
			avg_customers+=customers;
			customers ++;
			cur_time = event1;
			at_dt[cur_arrivals][0] = event1;
      cur_arrivals++;
			if (customers == 1)	//if there is only 1 customer, he/she goes directly to service
			{
				service_time = pow( (1 - (drand48()*(1 - pow(10, -5.2)))), -1/1.3);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
				if (cur_arrivals > 1)
					sys_idle_time += event1;
			}
      event1 = cur_time + expon(lambda);
		}
		else					//departure
		{
			customers--;
			at_dt[cur_departures][1] = event2;
			cur_departures++;
			cur_time = event2;
			if (customers > 0) // the departure left a non-empty queue behind
			{
				service_time = pow( (1 - (drand48()*(1 - pow(10, -5.2)))), -1/1.3);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				sys_idle_time -= event2;
				event2 = INFIN; //no departure scheduled
			}
		}
	}	
	avg_customers /=cur_arrivals; 
	utilization = avg_service_time / cur_time;

	for(int i = 0; i<tot_arrivals; i++)
	{
		if(at_dt[i][1] == 0)
			avg_wait_time_sys += (cur_time-at_dt[i][0]);
		else
			avg_wait_time_sys += (at_dt[i][1]-at_dt[i][0]);
	}
	avg_wait_time_sys /= cur_arrivals;
	avg_service_time /=(cur_arrivals-customers);
	print_stats(stats_file, avg_customers, avg_wait_time_sys, avg_service_time, (avg_wait_time_sys-avg_service_time), (sys_idle_time/cur_time), 0.0);
	stats_file.close();
	return 0;
}
