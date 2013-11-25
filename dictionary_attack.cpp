#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

struct hashes
{
    char * hash;
    char * pass;
};

int main(int argc, char ** argv) {
    hashes * record = new hashes[3106];        
    int i = 0;
    ifstream file; 
    string line;
    char * md5 = argv[1];
    bool found = false;
    
    file.open("passlist/wordsforsimpletest.txt");

    while(getline(file, line)) {
        string key,value;
        istringstream liness(line);
        getline(liness, key, ',');
        getline(liness, value, ',');
            
        record[i].pass = new char[key.size() + 1];
        copy(key.begin(), key.end(), record[i].pass);
        record[i].pass[key.size()] = '\0';

        record[i].hash = new char[value.size() + 1];
        copy(value.begin(), value.end(), record[i].hash);
        record[i].hash[value.size()] = '\0';          
        i++;
    }
    file.close();
    
    for(i = 0; i < 17; i++) {
        if(strcmp(record[i].hash, md5) == 0) {
            found = true;
            cout << "The password is " << record[i].pass << endl;
            break;
        }
    }
    
    if(!found)
        cout << "Couldn't match the password in the dictionary" << endl;
    
    return 0;
    
}

