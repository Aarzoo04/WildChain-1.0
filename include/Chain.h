#ifndef __C_CHAIN_INCLUDED__
#define __C_CHAIN_INCLUDED__
#include "Block.h"
#include <vector>

namespace Blockchain
{
    class Chain{
        private:
            std::vector<block> chain;
            block* CurrentBlock;
            int difficulty;
        public:
            Chain(int difficulty);
            void appendToCurrentBlock();
            void nextBlock();
            block* getCurrentBlock();
    };

}
#endif
