#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


struct Process{
    int thread;
    long int time, time_elapsed, time_left;

    Process(int thread){
        this->thread = thread;
        time = -1;
        time_elapsed = -1;
        time_left = -1;
    }

    void assignTime(long int t){
        time = t;
        time_elapsed = 0;
    }

    void resetTime(){
        time = -1;
        time_left = -1;
        time_elapsed = -1;
    }

    void updateTimeLeft(){
        time_elapsed++;
        time_left = time - time_elapsed;
    }
};

struct CompareProcessByTime{
    bool operator()(const Process& process_one, const Process& process_two) const {
        return process_one.time_left > process_two.time_left;
    }
};

struct CompareProcessByThread{
    bool operator()(const Process& process_one, const Process& process_two) const {
        return process_one.thread > process_two.thread;
    }
};

int main() {
    ifstream infile;
    ofstream outfile;
    //This is a priority queue with a min heap implementation
    priority_queue<Process, vector<Process>, CompareProcessByThread> unused_threads;
    priority_queue<Process, vector<Process>, CompareProcessByTime> used_threads;

    //While loops runs twice, once for each input
    int i = 1;
    //while(i <= 2){
        string filename = "inputs/input" + to_string(i);
        infile.open(filename);

        string line;
        int n, m, t;
        queue<long int> times;
        vector<Process> processes;

        int lineNum = 0;
        while(getline(infile, line)) {
            istringstream iss(line);
            if(lineNum == 0){
                iss >> n >> m;
            }
    
            else{
                //Adds all the times into the vector
                while(iss >> t) {
                    times.push(t);
                }
            }

            lineNum++;
        }

        
        //Pushes n threads into the priority queue
        for(int j = 0; j < n; j++){
            Process process(j);
            unused_threads.push(process);
            processes.push_back(process);
        }

        string outfilename = "output" + to_string(i) + ".a";
        outfile.open(outfilename);

        

        int j = 0;
        while(1){
            
            //For threads that are being used
            if(!used_threads.empty()){
                cout << used_threads.top().thread << endl;
                //Iterates through all threads
                for(int currentThread = 0; currentThread < n; currentThread++){
                    //If the thread at the front of the PQ has 0 time left the if is executed
                    if(used_threads.top().time_left == 0)
                    {
                        //If the current thread is equal to the thread at the front of the PQ
                        if(currentThread == used_threads.top().thread){    
                            //Resets the time for the current thread
                            processes[currentThread].resetTime();
                            
                            //Pushes the thread to unused thread PQ
                            unused_threads.push(used_threads.top());
                            
                            //Pops the thread from the used queue
                            used_threads.pop();
                        }
                    }
                }
            }
            
            //For unused_threads that are in use
            if(!unused_threads.empty()){
                //Iterates through these threads
                for(int currentThread = 0; currentThread < n; currentThread++){
                    
                    //If the first thread of unused_threads is equal to currentThread and not empty
                    if(unused_threads.top().thread == currentThread && !times.empty()){

                        //Print currentThread to the outfile
                        outfile << currentThread << " ";

                        //Sets the time of the processes vector with index currentThreat to the first time in 
                        // the times queue
                        processes[currentThread].assignTime(times.front());

                        //Removes the first element in times queue
                        times.pop();

                        //Pushes the proccesses object into used_threads
                        used_threads.push(processes[currentThread]);

                        //Removes it from unused_threads
                        cout << unused_threads.empty() << endl;
                        //Prints j/the time to the outfile
                        outfile << j << endl;
                    }
                }
            }

            for(int currentThread = 0; currentThread < n; currentThread++){
                processes[currentThread].updateTimeLeft();
            }
            
            j++;

            if(j == 100)
                break;
        
        }

        i++;
        outfile.close();
        infile.close();

        cout << "Yippie!" << endl;
    //}
}