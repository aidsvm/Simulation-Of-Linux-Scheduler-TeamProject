#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


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

        int lineNum = 0;
        while(getline(infile, line)) {
            istringstream iss(line);
            if(lineNum == 0){
                iss >> n >> m;
                cout << "Read numbers: " << n << " " << m << endl;
            }
    
            else{
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
        }

        string outfilename = "output" + to_string(i) + ".a";
        outfile.open(outfilename);

        /* 
            Need to come up with a way to take the first thread and
            allow it to run the first process. Then the second, and on.
            We need to think of a function that pops a thread out of the
            queue and keeps it out for t time and pushes that thread back
            into the queue when done
        */

        i++;
        infile.close();
    }
}