# DataStructures-TeamProject

Description:
You are in possession of a program that's been parallelized and employs 𝑛 individual threads to tackle a given list of m jobs or tasks. Threads operate on these 
tasks in the sequence they appear in the input. Whenever a thread becomes available, it promptly picks up the next job from the list. Once a thread commences 
processing a job, it proceeds without interruption until the job reaches completion. In cases where multiple threads vie for tasks from the list at the same time, 
the thread with the lower index takes precedence. Each job comes with a precise processing time, which remains constant across all threads. Your task involves 
determining both which threads will be responsible for processing each job and when that processing will commence.

Input:
The initial line in the input comprises two integers, 𝑛 and 𝑚. The subsequent line presents 𝑚 integers denoted as 𝑡𝑖, representing the time in seconds required for 
any thread to complete the 𝑖-th job. These times are listed in the exact sequence as they appear in the job list from which threads draw their tasks. It's important 
to note that thread indexing begins at 0.

•	The first line of the input contains integers 𝑛 and 𝑚.

•	The second line contains 𝑚 integers 𝑡𝑖 — the times in seconds it takes any thread to process 𝑖-th job. The times are given in the same order as they are in the list 
from which threads take jobs.

•	Threads are indexed starting from 0.

Output: 
Generate precisely 𝑚 lines of output. Each 𝑖-th line (using a 0-based index) must consist of two integers separated by a space. These integers represent the 0-based index 
of the thread responsible for executing the 𝑖-th job and the time, in seconds, at which the thread will commence the processing of that particular job.





