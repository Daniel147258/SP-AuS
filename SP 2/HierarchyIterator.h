#pragma once
#include "TerritorialUnit.h"
#include <libds/amt/explicit_hierarchy.h>

const int MIN_LEVEL_ = 0;
const int MAX_LEVEL_ = 3;
using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;

class HierarchyIterator
{
private:
    Block* actualBlock_;
    size_t level_;

public:

    HierarchyIterator(Block& root_Block){
        actualBlock_ = &root_Block;
        level_ = 0;
    }

    ~HierarchyIterator(){}

    void goPrevious() {
        if (level_ > MIN_LEVEL_)
        {
            actualBlock_ = static_cast<Block*>(actualBlock_->parent_);
            --level_;
            std::cout << "Your actual node is:";
            std::cout << actualBlock_->data_->getName() << "\n";
        }
        else
        {
            std::cout << "You are on the first depth level you can not go higher !!!!" << std::endl;
        }
    }
    

    void goNext(int&& index) {
        if (level_ < MAX_LEVEL_)
        {
            actualBlock_ = static_cast<Block*>(actualBlock_->sons_->access(index)->data_);
            ++level_;
            std::cout << "Your actual node is:";
            std::cout << actualBlock_->data_->getName() << "\n";
        }
        else
        {
            std::cout << "You are on the last depth level you can not go lower !!!!" << std::endl;
        }
    }

    void setActualBlock(Block* block, size_t l){
        actualBlock_ = block;
        level_ = l;
    }

    Block& getReferenceBlock(){ 
        return *actualBlock_; 
    }

    Block* getPointerBlock(){ 
        return actualBlock_; 
    }

    size_t getLevel(){ 
        return level_; 
    }


};
