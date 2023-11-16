#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


int main() {
    ifstream infile;
    //This is a priority queue with a min heap implementation
    priority_queue<int, vector<int>, greater<int>> pq;


    //While loops runs twice, once for each input
    int i = 1;
    while(i <= 2){
        string filename = "inputs/input" + to_string(i);
        infile.open(filename);

    
        string line;
        int n, m, m_count;
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
                while(iss >> m_count) {
                    times.push_back(m_count);
                }
                //For loop just comfirms that the values are in the vector
                for(int j = 0; j < m; j++) {
                    cout << times[j] << " ";
                }
            }
            
            lineNum++;
        }







        i++;
        }

    infile.close();
}