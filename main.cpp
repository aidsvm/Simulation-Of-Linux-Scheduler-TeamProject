#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


struct Process{
    int thread;
    long int time;

    Process();

    Process(int thread){
        this->thread = thread;
        time = 0;
    }

    void assignTime(long int t){
        time = t;
    }

    int nextAvailableThread(priority_queue<int, vector<int>, greater<int>> pq, vector<Process> processes){
        
    }
};

int main() {
    ifstream infile;
    ofstream outfile;
    //This is a priority queue with a min heap implementation
    priority_queue<int, vector<int>, greater<int>> pq;


    //While loops runs twice, once for each input
    int i = 1;
    while(i <= 2){
        string filename = "inputs/input" + to_string(i);
        infile.open(filename);

        string line;
        int n, m, t;
        vector<long int> times;
        vector<Process> processes;

        int lineNum = 0;
        while(getline(infile, line)) {
            istringstream iss(line);
            if(lineNum == 0){
                iss >> n >> m;
                cout << "Read numbers: " << n << " " << m << endl;
            }
    
            else{

                times.clear();
                //Adds all the times into the vector
                while(iss >> t) {
                    times.push_back(t);
                }
                //For loop just comfirms that the values are in the vector
                for(int j = 0; j < m; j++) {
                    cout << times[j] << " ";
                }
            }

            lineNum++;
        }

        
        //Pushes n threads into the priority queue
        for(int i = 0; i < n; i++){
            pq.push(i);
            Process process(i);
            processes.push_back(process);
        }


        string outfilename = "output" + to_string(i) + ".a";
        outfile.open(outfilename);

        //Calculate next aviable thread
        //Function(pq, proccesses)
        //  return procecesses.thread;

        for (int j = 0; j < m; j++) {
            // retrieves next available thread from priority queue, top() returns smallest element since its min-heap.
            int nextThread = pq.top();
            // removes the index of this thread from priority queue since it has been assigned to a job.
            pq.pop();
            // determines start time for next job, calculates max between 0 or start time of next available thread.
            processes[j]
            
        }



        i++;
        infile.close();
    }
}