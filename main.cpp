#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


int main() {
    ifstream infile;
    //This is a priority queue with a mean heap implementation
    priority_queue<int, vector<int>, greater<int>> pq;


    int i = 1;
    while(i <= 2){
        string filename = "inputs/input" + to_string(i);
        infile.open(filename);

    
        string line;
        int n, m, m_count;
        vector<long int> arr;

        int lineNum = 0;
        while(getline(infile, line)) {
            istringstream iss(line);
            if(lineNum == 0){
                iss >> n >> m;
                cout << "Read numbers: " << n << " " << m << endl;
            }
    
            else{
                while(iss >> m_count) {
                    arr.push_back(m_count);
                }

                for(int j = 0; j < m; j++) {
                    cout << arr[j] << " ";
                }
            }
            lineNum++;
        }







        i++;
        }

    infile.close();
}