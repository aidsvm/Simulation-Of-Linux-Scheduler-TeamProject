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
        time_elapsed = -1;
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

int main() {
    ifstream infile;
    ofstream outfile;
    //This is a priority queue with a min heap implementation
    priority_queue<Process, vector<Process>, CompareProcessByTime> unused_threads;
    priority_queue<Process, vector<Process>, CompareProcessByTime> used_threads;

    //While loops runs twice, once for each input
    int i = 1;
    while(i <= 2){
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
            
            if(!used_threads.empty()){
                for(int currentThread = 0; currentThread < n; currentThread++){
                    if(used_threads.top().time_left == 0){
                        unused_threads.push(used_threads.top());
                        used_threads.pop();
                        processes[currentThread].resetTime();
                    }
                }
            }
            

            if(!unused_threads.empty()){
                for(int currentThread = 0; currentThread < n; currentThread++){
                    if(unused_threads.top().thread == currentThread && !times.empty()){
                        outfile << currentThread << " ";

                        processes[currentThread].assignTime(times.front());
                        times.pop();

                        used_threads.push(processes[currentThread]);
                        unused_threads.pop();
                        
                        outfile << j << endl;
                    }
                }
            }

            for(int currentThread = 0; currentThread < used_threads.size(); currentThread++){
                processes[currentThread].updateTimeLeft();
            }
            
            j++;

            if(unused_threads.empty())
                break;
        
        }

        i++;
        outfile.close();
        infile.close();
    }
}