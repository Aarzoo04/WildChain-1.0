#include <iostream>
#include <fstream>
#include <string>
using namespace std;
    int main(){
    fstream newFile;string detail_hash;
    newFile.open("hash.txt",ios::in);
    if(newFile.is_open()){
        
        while(getline(newFile,detail_hash)){
            cout<<detail_hash<<"\n";
        }
        newFile.close();
    }
    return 0;
}