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
