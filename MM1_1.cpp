// EE 465, USC


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <queue>

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

double min(double a, double b)
{
     if(a<=b)
             return a;
     else
             return b;
}

double max(double a, double b)
{
     if(a<=b)
             return b;
     else
             return a;
}

// Function Name:	print_stats
// Description: 	Saves and prints system statistics 
// Input:           stats_file (ostream object): ostream object for the stats file
//					avg_customers (double): average customers in the system
//					avg_service_time (double): average service time 
// Output: 			void (output stored to file and printed in the screen)
//
void print_stats(ostream &stats_file, double utilization, double avg_customers, double avg_wait_time_sys, double block_prob, double sys_idle_time, double avg_service_time, double second_moment_st, double avg_waiting_time_queue)
{
	cout << "Utilization: " << utilization << endl;
	cout << "Average No. of Customers: " << avg_customers << endl;
	cout << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
	cout << "Blocking Probability: " << block_prob << endl;
	cout << "Idle Period of the server: " << sys_idle_time << endl;
  cout << "Average Service Time of the server: " << avg_service_time << endl;
  cout << "Second Moment of Service Time: " << second_moment_st << endl; 
  cout << "Average Waiting Time in Queue: " << avg_waiting_time_queue << endl;
	
	stats_file << "Utilization: " << utilization << endl;
	stats_file << "Average No. of Customers: " << avg_customers << endl;
	stats_file << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
	stats_file << "Blocking Probability: " << block_prob << endl;
	stats_file << "Idle Period of the server: " << sys_idle_time << endl;
  stats_file << "Average Service Time of the server: " << avg_service_time << endl;
  stats_file << "Second Moment of Service Time: " << second_moment_st << endl; 
  stats_file << "Average Waiting Time in Queue: " << avg_waiting_time_queue << endl;
}

void case3(void)
{
	
	long int tot_arrivals, cc = 0, cur_arrivals = 0, cur_departures = 0, flag1 = 0, flag2 = 0;
	double lambda, mu;
	double event1 = 0.0, event2 = INFIN, event3 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0, customers = 0.0, sys_idle_time = 0.0, avg_wait_time_sys = 0.0, max_customer, idle_period = 0.0, second_moment_st = 0.0, avg_waiting_time_queue;
	double block_time =0.0, block_prob = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0, avg_service_time_cust1 = 0.0, server1_entry, server2_entry; //used for calculating statistics
	double utilization; // used for computing the Utilization of the Queue
  queue<double> myqueue;
	ofstream stats_file; //file handler for saving the statistics in a file
	
  tot_arrivals = 10000;
  lambda = .7;
  mu = 1;
  max_customer = 5;
	//get input from the user
 
	cout << "Basic M/M/2/5 Simulator" << endl;
	/*cout << "Enter the total number of arrivals: ";
	cin >> tot_arrivals;
	cout << "Enter lambda: ";
	cin >> lambda;
	cout << "Enter mu: ";
	cin >> mu;
	cout << "Enter maximum number of customers: ";
	cin >> max_customer;*/
	
	//static double **at_dt;			
	stats_file.open ("stats_MM25_case3.txt"); //it creates the file, if it does not exist
	
		
  while (cur_arrivals < tot_arrivals)
	{
		if (event1 < event2 && event1 < event3)	//arrival
		{ 
      if(customers == 0)
                   idle_period++;
      if(customers == max_customer)
                   block_prob++;            
			cur_arrivals++;
      cur_time = event1;
      avg_customers+=customers;
      if(customers < max_customer)
      {
			 customers ++;
       myqueue.push(cur_time);
       if (customers == 1)	//if there is only 1 customer, he/she goes directly to service
		   {
			   	service_time = expon(mu);
			  	event2 = cur_time + service_time;
				  avg_service_time += service_time;
          avg_service_time_cust1 += service_time;
          second_moment_st += pow((service_time), 2);
          flag1 = 1;
          server1_entry = myqueue.front();
          myqueue.pop();
			 }
       if (customers == 2 )	//if there is only 2 customer, he/she goes directly to service in the corresponding server, which is free
		   {
			   	service_time = expon(mu);
          avg_service_time += service_time;
          second_moment_st += pow((service_time), 2);
          if(flag1 == 1)
          {
			  	         event3 = cur_time + service_time;
                   flag2 = 1;
                   server2_entry = myqueue.front();
                   myqueue.pop();
          }
          else
          {
                  event2 = cur_time + service_time;
                  flag1 = 1;
                  server1_entry = myqueue.front();
                  myqueue.pop();
          }        
			 }
      }
      event1 = cur_time + expon(lambda);
		}
		else					//departure
		{
			customers--;
      if(event2 < event3)
      {
			  cur_time = event2;
        avg_wait_time_sys += (cur_time - server1_entry);
        if (customers > 1) // the departure left a non-empty queue behind
			  {
				        service_time = expon(mu);
                event2 = cur_time + service_time;
                avg_service_time += service_time;
                second_moment_st += pow((service_time), 2);
                server1_entry = myqueue.front();
                myqueue.pop();
			  }
			  else 				//the departure left the queue empty
		  	{
			         	event2 = INFIN; //no departure scheduled
                flag1 = 0;
			  }
      }
      else
      {
			  cur_time = event3;
        avg_wait_time_sys += (cur_time - server2_entry);
        if (customers > 1) // the departure left a non-empty queue behind
			  {
				        service_time = expon(mu);
                event3 = cur_time + service_time;
                avg_service_time += service_time;
                second_moment_st += pow((service_time), 2);
                server2_entry = myqueue.front();
                myqueue.pop();
			  }
			  else 				//the departure left the queue empty
		  	{
			         	event3 = INFIN; //no departure scheduled
                flag2 = 0;
			  }
      }
		}
	}	
	avg_customers /=cur_arrivals; 
	utilization = 0.5*((avg_service_time + avg_service_time_cust1)/ cur_time);
  sys_idle_time = idle_period / cur_arrivals;
  block_prob = block_prob / cur_arrivals;
	avg_wait_time_sys /= (cur_arrivals-customers);
	avg_service_time /=(cur_arrivals-customers);
  second_moment_st /= (cur_arrivals-customers);
  avg_waiting_time_queue = avg_wait_time_sys - avg_service_time; 
	print_stats(stats_file, utilization, avg_customers, avg_wait_time_sys, block_prob, sys_idle_time, avg_service_time, second_moment_st, avg_waiting_time_queue);
	stats_file.close();
}

void case1case2(double lambda)
{
	long int tot_arrivals, cur_arrivals = 0, cur_departures = 0;
	double mu;
	double event1 = 0.0, event2 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0, customers = 0.0, sys_idle_time = 0.0, avg_wait_time_sys = 0.0, second_moment_st = 0.0, avg_waiting_time_queue;
	double avg_customers = 0.0, avg_service_time = 0.0; //used for calculating statistics
	double utilization; // used for computing the Utilization of the Queue
  double **at_dt;
	ofstream stats_file; //file handler for saving the statistics in a file
	
  tot_arrivals = 5000;
  mu = 1;
	//get input from the user
	cout << "Basic M/M/1 Simulator" << endl;
	/*cout << "Enter the total number of arrivals: ";
	cin >> tot_arrivals;
	cout << "Enter lambda: ";
	cin >> lambda;
	cout << "Enter mu: ";
	cin >> mu;*/
				
	stats_file.open ("stats_MM1_case1case2.txt"); //it creates the file, if it does not exist
	
	at_dt=new double*[tot_arrivals]; //creates a new array of pointers to double objects
	for(int i=0; i<tot_arrivals; ++i)
		at_dt[i]=new double[2];
   
  for(int i=0;i<tot_arrivals;i++)
          for(int j=0;j<2;j++)
                  at_dt[i][j] = 0.0;

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
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
        second_moment_st += (service_time*service_time);
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
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
        second_moment_st += (service_time*service_time);
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
  second_moment_st /=(cur_arrivals-customers);
  avg_waiting_time_queue = avg_wait_time_sys - avg_service_time;
	print_stats(stats_file, utilization, avg_customers, avg_wait_time_sys, 0.0, (sys_idle_time/cur_time), avg_service_time, second_moment_st, avg_waiting_time_queue);
	stats_file.close();
}

// The main function of the program that is called at the beginning.
int main(int argc, char *argv[]) {
	//system variables
 int choice;
 
 srand48(10); // Random number generation
 if ( argc != 2 )
    cout << "Enter only the Case Number as a parameter." << endl;
 else
    choice = atoi(argv[1]); 
 /*cout << "Enter your choice between Case 1, Case 2 and Case 3. For Case 1 enter 1, for Case 2 enter 2, for Case 3 enter 3" << endl;
 cin>> choice;*/
 
 switch(choice)
 {
               case 1 : case1case2(0.3);
                        break;
               case 2 : case1case2(0.97);
                        break;
               case 3 : case3();
                        break;
               default : cout << "Invalid Input";
                         break;
 }
 return 0;
}
