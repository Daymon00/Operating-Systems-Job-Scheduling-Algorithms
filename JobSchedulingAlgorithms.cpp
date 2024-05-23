/*
CSCI 340 Project 1
Name: Daymon Wu
Class: MW 10:45 - 12:00

Documentation:
For the FIFO algorithm I used the static array data structure because when the array
holds all the jobs I can use a simple sort based on the arrival time and that will
order them in the way it should be processed.
Complexity: O(n log n)
Appropriate usage of FIFO algorithm: when the jobs have similar times or when the
order they finish in matters

For the SJF algorithm I used a static array to sort jobs by the CPU burst so that I
can make sure the job with the shortest duration gets processed next in the array.
Because in preemptive scheduling the jobs have to be completed before switching.
Complexity: O(n log n)
Appropriate usage of SJF algorithm: when most of the jobs are short and you know
how long they take. It will reduce how long jobs will take to wait

For the SRTF algorithm I used a static array because if I set it up so it manually
checks the shortest remaining time at each step I can arrange it so the job with
the shortest remaining time is put next at each step. At each step the jobs can switch
from one to another.
Complexity: O(n log n)
Appropriate usage of SRTF algorithm: when most of the jobs are short and you know
how long they take. It will reduce how long jobs will take to wait

For the highest priority algorithm I also used a static array, I sorted the jobs
by highest priority first. I did this because static array are good for fast access
and sorting.
Complexity: O(n log n)
Appropriate usage of the highest priority algorithm: when some jobs are more
important than others and have to jump the queue. Like a fire truck on the road

For the round robin algorithm I used the static array like a queue data structure
because in round robin each job needs to be processed by the CPU and needs to be an
element in the queue. Jobs in round robin are processed for a fixed amount of time
and after that amount of time is over it is moved to the back of the queue. So with
the queue data structure the jobs can get the same amount of cpu time so no job is
skipped. It keeps going on until all the jobs are complete. It is easy to dequeue
and enqueue each job. Aka putting jobs in the front and in the back.
Complexity: O(n)
Appropriate usage of round robin algorithm: when you want to be fair to all jobs
so that all can get a chance to run.

Summary:
From what I gathered, jobs are processed according to what they are used for.
Different algorithms are used for different scenarios because they affect wait
times, turn around times and system throughput. I think SJF and Highest priority
queue give shorter average turn around times because they tend to favor shorter
tasks. And for FIFO it's really simple but it can lead to problems like the convoy
effect, which we talked about in class. SRTP is really good but it switches too
much between jobs so I feel like that can cause problems. In my opinion round
robin is the best because every job get the same amount of time and they all get
a chance to run no matter how long or short the task is. So that means shorter
tasks can still be completed faster than longer tasks.




Source Code:
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iomanip>
using namespace std;
const int JOBZ = 100; //the number of jobs
class Job {
public:
   int arrTime; //arrival time
   int cpuBurst; //cpu burst time
   int priority; //priority of job
   int remainingTime; // remining time for job for preemptive
   int exitTime; //time when the joob finishes
   int turnAroundTime; //turn around time
   bool started; //bool to check if the job started for srtf
   //job contructor that initialized the jobs with random numbers
   Job() : arrTime(rand() % 250 + 1), //1-250
           cpuBurst(rand() % 14 + 2), //2-15
           priority(rand() % 5 + 1),//1-5
           remainingTime(cpuBurst),
           exitTime(0),
           turnAroundTime(0),
           started(false){}
   //method to print the jobs
   void print() const {
       cout << "Arrival time: " << arrTime
            << " | CPU burst: " << cpuBurst
            << " | Priority: " << priority
            << " | Exit time: " << exitTime
            << " | Turnaround time: " << turnAroundTime << endl;
   }
};
//funtion to make the jobs accoring to how many which is 25
void createJobs(Job jobs[], int count){
   for (int i = 0; i < count; ++i){
       jobs[i] = Job();
   }
}
//function to evaluate and print the average turnaround time for a set of jobs
void evaluatePerformance(Job jobs[], int count){
   double totalTurnaroundTime = 0;
   for (int i = 0; i < count; ++i) {
       totalTurnaroundTime += jobs[i].turnAroundTime;
   }
   double averageTurnaroundTime = totalTurnaroundTime / count;
   cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}
//FIFO
void scheduleFIFO(Job jobs[], int count) {
   sort(jobs, jobs + count, [](const Job& a, const Job& b){
       return a.arrTime < b.arrTime;
       });
   int currentTime = 0;
   for (int i = 0; i < count; ++i) {
       if (currentTime < jobs[i].arrTime) {
           currentTime = jobs[i].arrTime;
       }
       currentTime += jobs[i].cpuBurst;
       jobs[i].exitTime = currentTime;
       jobs[i].turnAroundTime = currentTime - jobs[i].arrTime;
   }
}
//sjf non-preemptive
void scheduleSJF(Job jobs[], int count) {
   sort(jobs, jobs + count, [](const Job& a, const Job& b) { return a.cpuBurst < b.cpuBurst; });
   int currentTime = 0;
   for (int i = 0; i < count; ++i) {
       if (currentTime < jobs[i].arrTime) {
           currentTime = jobs[i].arrTime;
       }
       currentTime += jobs[i].cpuBurst;
       jobs[i].exitTime = currentTime;
       jobs[i].turnAroundTime = currentTime - jobs[i].arrTime;
   }
}
//highest priority
void schedulePriority(Job jobs[], int count) {
   sort(jobs, jobs + count, [](const Job& a, const Job& b) { return a.priority > b.priority; });
   int currentTime = 0;
   for (int i = 0; i < count; ++i) {
       if (currentTime < jobs[i].arrTime) {
           currentTime = jobs[i].arrTime;
       }
       currentTime += jobs[i].cpuBurst;
       jobs[i].exitTime = currentTime;
       jobs[i].turnAroundTime = currentTime - jobs[i].arrTime;
   }
}
//srtf preemptive
void scheduleSRTF(Job jobs[], int count) {
   int currentTime = 0;
   bool jobInProgress = true;
   while (jobInProgress) {
       int id = -1;
       int minTime = INT_MAX;
       for (int i = 0; i < count; ++i) {
           if (jobs[i].arrTime <= currentTime && jobs[i].remainingTime > 0 && jobs[i].remainingTime < minTime) {
               minTime = jobs[i].remainingTime;
               id = i;
           }
       }
       if (id != -1) {
           jobs[id].remainingTime--;
           if (!jobs[id].started) {
               jobs[id].started = true;
           }
           if (jobs[id].remainingTime == 0) {
               jobs[id].exitTime = ++currentTime;
               jobs[id].turnAroundTime = jobs[id].exitTime - jobs[id].arrTime;
           } else {
               currentTime++;
           }
       } else {
           currentTime++;  //increment the time and if no job is ready to be executed
       }
       jobInProgress = false;
       for (int i = 0; i < count; i++) {
           if (jobs[i].remainingTime > 0) {
               jobInProgress = true;
               break;
           }
       }
   }
}
// Round Robin
void scheduleRoundRobin(Job jobs[], int count, int quantum, bool withContextSwitch, int contextSwitchTime = 0) {
   int indexes[JOBZ], front = 0, back = 0, currentTime = 0;
   for (int i = 0; i < count; ++i) indexes[back++] = i; // load all jobs into the queue
   while (front != back) {
       int id = indexes[front];
       front = (front + 1) % JOBZ; //circular queue
       Job& job = jobs[id];
       if (withContextSwitch && front != back) currentTime += contextSwitchTime;

       int slice = min(job.remainingTime, quantum);
       job.remainingTime -= slice;
       currentTime += slice;

       if (job.remainingTime > 0) {
           indexes[back] = id;
           back = (back + 1) % JOBZ; //enqueue
       } else {
           job.exitTime = currentTime;
           job.turnAroundTime = currentTime - job.arrTime;
       }
   }
}

int main() {
   srand(time(nullptr)); //random number generator
   Job jobs[JOBZ];
   createJobs(jobs, 25); // create 25 jobs
   cout << "Original Jobs:\n";
   for (int i = 0; i < 25; ++i) {
       jobs[i].print();
   }
   //FIFO
   Job fifoJobs[JOBZ];
   copy(jobs, jobs + 25, fifoJobs);
   scheduleFIFO(fifoJobs, 25);
   cout << "\nFIFO Scheduling:\n";
   for (int i = 0; i < 25; ++i) {
       fifoJobs[i].print();
   }
   evaluatePerformance(fifoJobs, 25);
   //SJF
   Job sjfJobs[JOBZ];
   copy(jobs, jobs + 25, sjfJobs);
   scheduleSJF(sjfJobs, 25);
   cout << "\nSJF Scheduling:\n";
   for (int i = 0; i < 25; ++i) {
       sjfJobs[i].print();
   }
   evaluatePerformance(sjfJobs, 25);
   //Highest priority
   Job priorityJobs[JOBZ];
   copy(jobs, jobs + 25, priorityJobs);
   schedulePriority(priorityJobs, 25);
   cout << "\nPriority Scheduling:\n";
   for (int i = 0; i < 25; ++i) {
       priorityJobs[i].print();
   }
   evaluatePerformance(priorityJobs, 25);
   //SRTF
   Job srtfJobs[JOBZ];
   copy(jobs, jobs + 25, srtfJobs);
   scheduleSRTF(srtfJobs, 25);
   cout << "\nSRTF Scheduling:\n";
   for (int i = 0; i < 25; ++i) {
       srtfJobs[i].print();
   }
   evaluatePerformance(srtfJobs, 25);
   //Round Robin random context switch and random quantum
   int quantum = rand() % 3 + 1; //quantum between 1 and 3
   int contextSwitchTime = rand() % 2 + 1; //context switch time of 1 or 2
   Job rrJobs[JOBZ];
   copy(jobs, jobs + 25, rrJobs);
   cout << "\nUsing Quantum: " << quantum << " and Context Switch Time: " << contextSwitchTime << "\n";
   scheduleRoundRobin(rrJobs, 25, quantum, true, contextSwitchTime);
   cout << "Round Robin with Random Context Switch:\n";
   for (int i = 0; i < 25; ++i) {
       rrJobs[i].print();
   }
   evaluatePerformance(rrJobs, 25);
   //Round Robin without context switch
   Job rrJobsNoContext[JOBZ];
   copy(jobs, jobs + 25, rrJobsNoContext);
   scheduleRoundRobin(rrJobsNoContext, 25, quantum, false);
   cout << "\nRound Robin without Context Switch:\n";
   for (int i = 0; i < 25; ++i) {
       rrJobsNoContext[i].print();
   }
   evaluatePerformance(rrJobsNoContext, 25);
   return 0;
}
