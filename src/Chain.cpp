#include <iostream>
#include "Chain.h"
#include "Block.h"
#include <openssl/sha.h>
using namespace Blockchain;

Chain::Chain(int difficulty){
    this->difficulty = difficulty;
    chain.push_back(block(nullptr));  // Genesis block
    CurrentBlock = &chain[0];
}

void Chain::appendToCurrentBlock(){
    std::string details_hash = CurrentBlock->readDataHashFromFile();
    CurrentBlock->appendData(details_hash);
}

void Chain::nextBlock(){
    block newBlock(CurrentBlock);
    newBlock.mine(difficulty);
    chain.push_back(newBlock);
    CurrentBlock = &chain.back();
}

block* Chain::getCurrentBlock(){
    return CurrentBlock;
}
