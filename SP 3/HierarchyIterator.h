#pragma once
#include "TerritorialUnit.h"


const int MIN_LEVEL_ = 0;
const int MAX_LEVEL_ = 3;
using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;

class HierarchyIterator
{
private:
    Block* actualBlock_;
    MuT* hierarchy;
    size_t level_;

public:

    HierarchyIterator(MuT* hierarchy) {
        this->hierarchy = hierarchy;
        actualBlock_ = this->hierarchy->accessRoot();
        level_ = 0;
    }

    ~HierarchyIterator() {

    }

    void goPrevious() {
        if (level_ > MIN_LEVEL_)
        {
            if (level_ == 1) { // osetrujem pretoze ze accessParent je static_cast ak by som ho zavolal nad rootom tak to vrati blbost
                actualBlock_ = hierarchy->accessRoot();
                --level_;
            }
            else {
                actualBlock_ = hierarchy->accessParent(*actualBlock_);
                --level_;
            }

        }
        else
        {
            std::cout << "You are on the first depth level you can not go higher !!!!" << std::endl;
        }
    }


    void goNext(int& index) {
        if (level_ < MAX_LEVEL_)
        {
            actualBlock_ = actualBlock_->sons_->access(index)->data_;
            ++level_;
        }
        else
        {
            std::cout << "You are on the last depth level you can not go lower !!!!" << std::endl;
        }
    }

    void setActualBlock(Block* block, size_t l) {
        actualBlock_ = block;
        level_ = l;
    }

    Block& getReferenceBlock() {
        return *actualBlock_;
    }

    Block* getPointerBlock() {
        return actualBlock_;
    }

    size_t getLevel() {
        return level_;
    }


};
