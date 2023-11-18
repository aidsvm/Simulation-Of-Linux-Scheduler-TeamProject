#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Struct to represent a process
struct Process {
    int thread;
    long int time_needed, time_elapsed, time_left, time_started;

    Process(int thread) {
        this->thread = thread;
        time_needed = -1;
        time_elapsed = -1;
        time_left = -1;
        time_started = 0;
    }

    // Method to assign time to a process
    void assignTime(long int t) {
        time_needed = t;
        time_elapsed = -1;
    }

    // Method to reset time-related attributes of a process
    void resetTime() {
        time_needed = -1;
        time_left = -1;
        time_elapsed = -1;
    }

    // Method to update time_left for a process
    void updateTimeLeft() {
        time_elapsed++;
        time_left = time_needed - time_elapsed;
    }

    // Method to update the start time for a process
    void newStartTime(long int new_time) {
        time_started += new_time;
    }
};

// Struct for comparing processes based on their remaining time
struct CompareProcessByTime {
    bool operator()(const Process* process_one, const Process* process_two) const {
        if (process_one->time_needed == process_two->time_needed) {
            return process_one->thread > process_two->thread;
        }

        return process_one->time_left > process_two->time_left;
    }
};

// Struct for comparing processes based on their thread number
struct CompareProcessByThread {
    bool operator()(const Process* process_one, const Process* process_two) const {
        return process_one->thread > process_two->thread;
    }
};

int main() {
    ifstream infile;
    ofstream outfile;

    // Priority queues for unused and used threads with custom comparators
    priority_queue<Process*, vector<Process*>, CompareProcessByThread> unused_threads;
    priority_queue<Process*, vector<Process*>, CompareProcessByTime> used_threads;

    // Loop for reading two input files
    int i = 1;
    while (i <= 2) {
        string filename = "input" + to_string(i);
        infile.open(filename);

        string line;
        int n, m, t;
        queue<long int> times;
        vector<Process*> processes;

        int lineNum = 0;
        // Read input file line by line
        while (getline(infile, line)) {
            istringstream iss(line);
            if (lineNum == 0) {
                // Read the number of threads (n) and the number of times (m)
                iss >> n >> m;
                cout << n << " " << m << endl;
            } else {
                // Add all the times into the vector
                while (iss >> t) {
                    times.push(t);
                }
            }

            lineNum++;
        }

        // Push n threads into the priority queue
        for (int j = 0; j < n; j++) {
            Process* process = new Process(j);
            unused_threads.push(process);
            processes.push_back(process);
        }

        string outfilename = "output" + to_string(i) + ".a";
        outfile.open(outfilename);

        int j = 0;
        // Simulation loop for processing threads
        while (j < m) {
            // Process threads that are being used
            if (!used_threads.empty()) {
                for (int currentThread = 0; currentThread < n; currentThread++) {
                    if (used_threads.top()->time_left == 0) {
                        if (currentThread == used_threads.top()->thread) {
                            // Push completed thread to unused thread queue
                            unused_threads.push(used_threads.top());
                            used_threads.pop();
                            // Reset time for the current thread
                            processes[currentThread]->resetTime();
                        }
                    }
                }
            }

            // Process unused threads
            if (!unused_threads.empty()) {
                for (int currentThread = 0; currentThread < n; currentThread++) {
                    // If the first thread of unused_threads is equal to currentThread and not empty
                    if (unused_threads.top()->thread == currentThread && !times.empty()) {
                        // Print currentThread to the outfile
                        outfile << currentThread << " ";
                        // Set the time of the processes vector with index currentThread to the first time in the times queue
                        processes[currentThread]->assignTime(times.front());

                        if (j != 0) {
                            // Update start time for the process
                            processes[currentThread]->newStartTime(times.front());
                            // Remove the first element in times queue
                            times.pop();
                        }

                        // Push the processes object into used_threads
                        used_threads.push(processes[currentThread]);

                        // Remove it from unused_threads
                        unused_threads.pop();

                        // Print j/the time to the outfile
                        outfile << processes[currentThread]->time_started << endl;
                    }
                }
            }

            // Update time_left for all processes
            for (int currentThread = 0; currentThread < n; currentThread++) {
                processes[currentThread]->updateTimeLeft();
            }

            j++;
        }

        // Clean up allocated memory for processes
        for (Process* process : processes) {
            delete process;
        }
        
        // Empties both priority queues
        while(!used_threads.empty()){
            used_threads.pop();
        }
        while(!unused_threads.empty()){
            unused_threads.pop();
        }
        
        i++;
        outfile.close();
        infile.close();
    }
}
