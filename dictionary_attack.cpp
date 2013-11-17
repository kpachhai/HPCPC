#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

int main(int argc, char ** argv) {
    ifstream file; 
    string line;
    map<string,string> dictionary;
    map<string,string>::iterator it;
    string md5 = argv[1];
    string match;
    bool found = false;

    file.open("passlist/wordsforsimpletest.txt");
    
    for(int i = 0; i < 17; i++) {
        while(getline(file, line)) {
            string key,value;
            istringstream liness(line);
            getline(liness, key, ',');
            getline(liness, value, ',');
            dictionary[key] = value;
        }
    }
    file.close();

    for(map<string,string>::iterator it=dictionary.begin(); it!=dictionary.end();++it) {
        if(md5.compare(it->second) == 0) {
            match = it->first;
            found = true;
            cout << "Hash matched!!" << endl;
            cout << "The password is " << match << endl;
            break;
        }
    }

    if(!found)
        cout << "You suck. Couldn't match the password in the dictionary" << endl;

    return 0;

}
