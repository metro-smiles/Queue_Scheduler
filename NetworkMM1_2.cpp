// EE 465, USC


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <queue>

using namespace std;

#define INFIN  			999999999
double global_av_customers = 0.0, global_av_sys_wait_time = 0.0, p, dist[21], dist1[21], dist2[21], dist3[21], dist4[21], dist5[21], inter_arrivaltime[10000];
long int tot_arrivals = 0; 
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
	
  //cout << " -log(1-u) :" << -log(1-u) << endl;
	return -log(1-u)/lambda;
	
}

// Function Name:	print_stats
// Description: 	Saves and prints system statistics 
// Input:           stats_file (ostream object): ostream object for the stats file
//					avg_customers (double): average customers in the system
//					avg_service_time (double): average service time 
// Output: 			void (output stored to file and printed in the screen)
//
void print_stats(ostream &stats_file, double avg_customers, double avg_wait_time_sys) //, double avg_service_time
{
	cout << "Average No. of Customers: " << avg_customers << endl;
  cout << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
  for(int i = 0; i<=20; i++)
          cout << i <<" - " << dist[i] << "% ";
	cout << endl;
  //cout << "Average Service Time: " << avg_service_time << endl;
	
	stats_file << "Average No. of Customers: " << avg_customers << endl;
  stats_file << "Average Waiting time in the system: " << avg_wait_time_sys << endl;
  for(int i = 0; i<=20; i++)
          stats_file << i <<" - " << dist[i] << "% ";
  stats_file << "Inter Arrival Times :-" << endl;
  for(int i = 0; i < 10000; i++)
          stats_file << inter_arrivaltime[i] <<endl;
	//stats_file << "Average Service Time: " << avg_service_time << endl;
}

void case2(void)
{
  long int tot_arrivals, cur_arrivals = 0;
	double lambda, mu, u;
	double event1 = 0.0, event2 = INFIN, event3 = INFIN, event4 = INFIN, event5 = INFIN, event6 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0, customers1 = 0.0, customers2 = 0.0, customers3 = 0.0, customers4 = 0.0, customers5 = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0, avg_wait_time_sys = 0.0; //used for calculating statistics
	ofstream stats_file; //file handler for saving the statistics in a file
  queue<double> myqueue1, myqueue2, myqueue3, myqueue4, myqueue5;
	
	//get input from the user
	cout << "Basic M/M/1 Simulator with Multiple Queues" << endl;
	cout << "Enter the total number of arrivals: ";
	cin >> tot_arrivals;
	cout << "Enter lambda: ";
	cin >> lambda;
	cout << "Enter mu: ";
	cin >> mu;
			
	stats_file.open ("stats_5_MM1.txt"); //it creates the file, if it does not exist
 
  for(int i = 0; i<= 20; i++)
  {
      dist[i] = 0.0;
  }
  for(int i = 0; i<= 20; i++)
  {
      dist1[i] = 0.0;
  }
  for(int i = 0; i<= 20; i++)
  {
      dist2[i] = 0.0;
  }
  for(int i = 0; i<= 20; i++)
  {
      dist3[i] = 0.0;
  }
  for(int i = 0; i<= 20; i++)
  {
      dist4[i] = 0.0;
  }
  for(int i = 0; i<= 20; i++)
  {
      dist5[i] = 0.0;
  }
	
	// discrete event simulator 
	while (cur_arrivals < tot_arrivals)
	{
		if (event1 < event2 && event1 < event3 && event1 < event4 && event1 < event5 && event1 < event6)	//arrival
		{             
			cur_arrivals++;
      u = drand48();
      if(u>=0 && u<=0.2)
      {        
               for(int i = 0; i<= 20; i++)
               {
                       if(customers1 == i)
                                        dist1[i]+= 1;
               }
			         avg_customers+=(customers1 + customers2 + customers3 + customers4 + customers5);
			         customers1++;
			         cur_time = event1;
               myqueue1.push(cur_time);
			         if (customers1 == 1)	//if there is only 1 customer, he/she goes directly to service
			         {
				                     service_time = expon(mu);
				                     event2 = cur_time + service_time;
				                     avg_service_time += service_time;
               }
      }
      else if(u>0.2 && u<=0.4)
      {        
               for(int i = 0; i<= 20; i++)
               {
                       if(customers2 == i)
                                        dist2[i]+= 1;
               }
			         avg_customers+=(customers1 + customers2 + customers3 + customers4 + customers5);
			         customers2 ++;
			         cur_time = event1;
               myqueue2.push(cur_time);
			         if (customers2 == 1)	//if there is only 1 customer, he/she goes directly to service
			         {
				                     service_time = expon(mu);
				                     event3 = cur_time + service_time;
				                     avg_service_time += service_time;
               }
      }
      else if(u>0.4 && u<=0.6)
      {        
               for(int i = 0; i<= 20; i++)
               {
                       if(customers3 == i)
                                        dist3[i]+= 1;
               }
			         avg_customers+=(customers1 + customers2 + customers3 + customers4 + customers5);
			         customers3 ++;
			         cur_time = event1;
               myqueue3.push(cur_time);
			         if (customers3 == 1)	//if there is only 1 customer, he/she goes directly to service
			         {
				                     service_time = expon(mu);
				                     event4 = cur_time + service_time;
				                     avg_service_time += service_time;
               }
      }
      else if(u>0.6 && u<=0.8)
      {        
               for(int i = 0; i<= 20; i++)
               {
                       if(customers4 == i)
                                        dist4[i]+= 1;
               }
			         avg_customers+=(customers1 + customers2 + customers3 + customers4 + customers5);
			         customers4 ++;
			         cur_time = event1;
               myqueue4.push(cur_time);
			         if (customers4 == 1)	//if there is only 1 customer, he/she goes directly to service
			         {
				                     service_time = expon(mu);
				                     event5 = cur_time + service_time;
				                     avg_service_time += service_time;
               }
      }
      else if(u>0.8 && u<=1.0)
      {        
               for(int i = 0; i<= 20; i++)
               {
                       if(customers5 == i)
                                        dist5[i]+= 1;
               }
			         avg_customers+=(customers1 + customers2 + customers3 + customers4 + customers5);
			         customers5 ++;
			         cur_time = event1;
               myqueue5.push(cur_time);
			         if (customers5 == 1)	//if there is only 1 customer, he/she goes directly to service
			         {
				                     service_time = expon(mu);
				                     event6 = cur_time + service_time;
				                     avg_service_time += service_time;
               }
      }
      event1 = cur_time + expon(5*lambda);
    }
		else	if (event2 < event1 && event2 < event3 && event2 < event4 && event2 < event5 && event2 < event6)				//departure
		{
			customers1--;
			cur_time = event2;
      avg_wait_time_sys += (cur_time - myqueue1.front());
      myqueue1.pop();
      if (customers1 > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure scheduled
			}
		}
    else	if (event3 < event2 && event3 < event1 && event3 < event4 && event3 < event5 && event3 < event6)				//departure
		{
			customers2--;
			cur_time = event3;
      avg_wait_time_sys += (cur_time - myqueue2.front());
      myqueue2.pop();
      if (customers2 > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event3 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event3 = INFIN; //no departure scheduled
			}
		}
    else	if (event4 < event2 && event4 < event3 && event4 < event1 && event4 < event5 && event4 < event6)				//departure
		{
			customers3--;
			cur_time = event4;
      avg_wait_time_sys += (cur_time - myqueue3.front());
      myqueue3.pop();
      if (customers3 > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event4 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event4 = INFIN; //no departure scheduled
			}
		}
    else	if (event5 < event2 && event5 < event3 && event5 < event4 && event5 < event1 && event5 < event6)				//departure
		{
			customers4--;
			cur_time = event5;
      avg_wait_time_sys += (cur_time - myqueue4.front());
      myqueue4.pop();
      if (customers4 > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event5 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event5 = INFIN; //no departure scheduled
			}
		}
    else	if (event6 < event2 && event6 < event3 && event6 < event4 && event6 < event5 && event6 < event1)				//departure
		{
			customers5--;
			cur_time = event6;
      avg_wait_time_sys += (cur_time - myqueue5.front());
      myqueue5.pop();
      if (customers5 > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event6 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event6 = INFIN; //no departure scheduled
			}
		}
	}	
	avg_customers /=cur_arrivals; 
	//avg_service_time /=(cur_arrivals-customers);
  avg_wait_time_sys /= (cur_arrivals-(customers1 + customers2 + customers3 + customers4 + customers5)) ;
  for(int i = 0; i<= 20; i++)
  {
          dist[i] = dist1[i] + dist2[i] + dist3[i] + dist4[i] + dist5[i];
          dist[i]/= cur_arrivals;
          dist[i]*= 100;
  }
	print_stats(stats_file, avg_customers, avg_wait_time_sys);
	stats_file.close();
}


void case1()
{
  long int tot_arrivals, cur_arrivals = 0, repeat = 0, index = 0;
	double lambda, mu;
	double event1 = 0.0, event2 = INFIN; //event1: time of next arrival, event2: time of next departure
	double service_time, cur_time = 0.0, customers = 0.0;
	double avg_customers = 0.0, avg_service_time = 0.0, avg_wait_time_sys = 0.0; //used for calculating statistics
	ofstream stats_file; //file handler for saving the statistics in a file
  queue<double> myqueue;
	
	//get input from the user
	cout << "Basic M/M/1 Simulator with feedback" << endl;
	cout << "Enter the total number of arrivals: ";
	cin >> tot_arrivals;
	cout << "Enter lambda: ";
	cin >> lambda;
	cout << "Enter mu: ";
	cin >> mu;
  cout << "Enter the probability of repeating a call: ";
	cin >> p;
			
	stats_file.open ("stats_Network_MM1.txt"); //it creates the file, if it does not exist
 
  for(int i = 0; i<= 20; i++)
  {
      dist[i] = 0.0;
  }
	
  for(int i = 0; i < 10000; i++)
          inter_arrivaltime[i] = 0.0;
	// discrete event simulator 
	while (cur_arrivals < tot_arrivals)
	{
		if (event1 < event2)	//arrival
		{
      for(int i = 0; i<= 20; i++)
      {
              if(customers == i)
                           dist[i]+= 1;
      }             
			cur_arrivals++;
			avg_customers+=customers;
			customers ++;
			cur_time = event1;
      myqueue.push(cur_time);
      if(index<10000)
      {
                     if(index == 0)
                     {
                              inter_arrivaltime[index] = cur_time;
                              index++;
                     }
                     else
                     {
                              inter_arrivaltime[index] = cur_time;//(cur_time - inter_arrivaltime[index-1]);
                              index++;
                     }
      }
			event1 = cur_time + expon(lambda);
			if (customers == 1)	//if there is only 1 customer, he/she goes directly to service
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
		}
		else					//departure
		{
			customers--;
			cur_time = event2;
      avg_wait_time_sys += (cur_time - myqueue.front());
      myqueue.pop();
      if (customers > 0) // the departure left a non-empty queue behind
			{
				service_time = expon(mu);
				event2 = cur_time + service_time;
				avg_service_time += service_time;
			}
			else 				//the departure left the queue empty
			{
				event2 = INFIN; //no departure scheduled
			}
      if(drand48()<=p) // Repeat by feedback
      {
                      customers++;
                      myqueue.push(cur_time);
                      if(index < 10000)
                      {
                               if(index == 0)
                               {
                                        inter_arrivaltime[index] = cur_time;
                                        index++;
                               }
                               else
                               {
                                        inter_arrivaltime[index] = cur_time;//(cur_time - inter_arrivaltime[index-1]);
                                        index++;
                               }
                      }
                      repeat++;
                      if (customers == 1)	//if there is only 1 customer, he/she goes directly to service
			                {
				                 service_time = expon(mu);
				                 avg_service_time += service_time;        
                         event2 = cur_time + service_time;
	                    }
      }
		}
	}	
	avg_customers /=cur_arrivals; 
	//avg_service_time /=(cur_arrivals-customers);
  avg_wait_time_sys /= ( (cur_arrivals-customers) + repeat);
  for(int i = 0; i<= 20; i++)
  {
          dist[i]/= cur_arrivals;
          dist[i]*= 100;
  }
	print_stats(stats_file, avg_customers, avg_wait_time_sys);
	stats_file.close();
}

// The main function of the program that is called at the beginning.
int main(int argc, char *argv[]) {
	//system variables
 int choice;
 
 srand48(10); // Random Number Generation
 if ( argc != 2 )
    cout << "Enter only the Case Number as a parameter." << endl;
 else
    choice = atoi(argv[1]); 
 /*
 cout << "Enter your choice between Case 1 and Case 2. For Case 1 enter 1, for Case 2 enter 2" << endl;
 cin>> choice;*/
 
 switch(choice)
 {
               case 1 : case1();
                        break;
               case 2 : case2();
                        break;
               default : cout << "Invalid Input";
                         break;
 }
	return 0;
}
