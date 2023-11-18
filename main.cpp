#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Process
{
    int thread;
    long int time;

    //Constructor to make a Process object with passed in thread value/
    Process(int thread)
    {
        this->thread = thread;
        time = 0;
    }

    //>Operator for this class, if both times are equal, return thread > other.thread
    bool operator>(const Process& other) const {
        if (time == other.time) {
            return thread > other.thread;
        }
        //Else, return time > other.time
        return time > other.time;
    }
};

int main()
{
    ifstream infile;
    ofstream outfile;
    
    // While loops runs twice, once for each input
    int i = 1;
    while (i <= 2)
    {
        string filename = "inputs/input" + to_string(i);
        infile.open(filename);

        string line;
        int n, m;

        // Read the first line of the input file to get n and m
        getline(infile, line);
        istringstream iss1(line);
        iss1 >> n >> m;
        
        //Priority Queue, min-heap, takes in Process Objects
        priority_queue<Process, vector<Process>, greater<Process>> threads;
        //Stores times, size m.
        vector<long long int> times(m);

        // Pushes n threads into the priority queue
        for (int i = 0; i < n; i++)
        {
           threads.push(Process(i));
        }

        // Read the second line of the input file to get processing times
        getline(infile, line);
        istringstream iss2(line);

        // Reads the input file into the vector times, from index 0 to m-1.
        for(int i = 0; i < m; i++) {
            iss2 >> times[i];
        }

        // Construct the filename for the output file
        string outfilename = "output" + to_string(i) + ".a";
        outfile.open(outfilename);

        //From 0 to m-1 processes, this will create a new Process object with 
        // the first thread available, it will then pop it out of the threads PQ.
        for(int i = 0; i < m; i++) {
            Process currentProcess = threads.top();
            threads.pop();

            // Write thread index and processing time to the output file
            outfile << currentProcess.thread << " " << currentProcess.time << endl;

            // Update the processing time for the current process
            currentProcess.time += times[i];
            threads.push(currentProcess);

        }
        
        i++;
        outfile.close();
        infile.close();
    }

}