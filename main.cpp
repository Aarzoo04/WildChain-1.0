#include <iostream>
#include <cstring>
#include "include/Chain.h"
#include "include/Block.h"
using namespace std;
using namespace Blockchain;

int main(){
    Chain chain(1);
    cout<< "Chain initialized....\n";
    block* genesis = chain.getCurrentBlock();
    chain.appendToCurrentBlock();
    chain.getCurrentBlock()->readDataHashFromFile();

    cout<< "Details added to Blockchain...\n";
    chain.nextBlock();
    cout<<"Next Block Mined....\n";
    cout<<"Previous Hash: "<< chain.getCurrentBlock()->getpreviousblock()->getHashstr();
    cout<<endl;

    chain.appendToCurrentBlock();
    cout<< "Details added to Blockchain...\n";
    chain.nextBlock();
    cout<<"Next Block Mined....\n";
    cout<<"Previous Hash: "<< chain.getCurrentBlock()->getpreviousblock()->getHashstr();

    return 0;
}
