#pragma once
#include <complexities/complexity_analyzer.h>
#include <random>
#include "libds/amt/implicit_sequence.h"
#include "libds/adt/table.h"
//#include "C:\Users\matej\OneDrive\Desktop\DONE\AaUD1_2023\AUS-VS2022\DataStructures\Zadanie3_Dziaba_Matej_\DuplicitySequenceSortedTable.h"
#include "libds/adt/table.h"

namespace ds::utils
{

    using Table = ds::adt::SortedSequenceTable<size_t, size_t>;

    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    public:
        explicit TableAnalyzer(const std::string& name);
        void beforeOperation(Table& structure) override;
        void afterOperation(Table& structure) override;

    public:
        size_t getRandomIndex_() const;
        std::string getRandomData_() const;
        size_t getRandom_size_t(size_t indexFrom, size_t indexTo) const;
        std::string& getRandom_String(size_t sizeOfString) const;

    protected:
        auto getKey() { return key_; }
        auto getData() { return data_; }

    private:
        void insertNElements(Table& list, size_t n);

    private:
        ds::amt::ImplicitSequence<size_t> IS_data;
        size_t key_;
        size_t data_;
    };


    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };


    template<class Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };


    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer() :
            CompositeAnalyzer("Tables")
        {
            this->addAnalyzer(std::make_unique<TableInsertAnalyzer<Table>>("table-insert"));
            this->addAnalyzer(std::make_unique<TableFindAnalyzer<Table>>("table-find"));
        }
    };

    template<class Table>
    TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name, [this](Table& table, size_t n)
            {
                this->insertNElements(table, n);
            }), 
            key_(0),
            data_(0)
    {
    }


    template<class Table>
    size_t TableAnalyzer<Table>::getRandom_size_t(size_t indexFrom, size_t indexTo) const
    {
        return static_cast<size_t>((rand() % (indexTo - indexFrom)) + indexFrom);
    }
    template<class Table>
    size_t TableAnalyzer<Table>::getRandomIndex_() const
    {
        return getRandom_size_t(0, this->IS_data.size() - 1);
    }

    template<class Table>
    std::string& TableAnalyzer<Table>::getRandom_String(size_t sizeOfString) const
    {
        std::string return_String = "";
        for (int i = 0; i < sizeOfString; i++)
            return_String = return_String + static_cast<char>(std::rand() % ('Z' - 'A' + 1) + 'A');

        return return_String;
    }
    template<class Table>
    std::string TableAnalyzer<Table>::getRandomData_() const
    {
        return this->IS_data.access(getRandomIndex_())->data_;
    }

    template<class Table>
    void TableAnalyzer<Table>::insertNElements(Table& table, size_t n)
    {
        for (size_t i = 0; i < this->getStepSize(); i++)
        {
            this->IS_data.insertLast().data_ = getRandom_size_t(0, n);
        }
    }

    template<class Table>
    void TableAnalyzer<Table>::beforeOperation(Table& structure)
    {
        key_ = this->getRandomIndex_();
        data_ = this->getRandomIndex_();
    }

    template<class Table>
    inline TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) : TableAnalyzer<Table>(name)
    {
    }

    template <class Table>
    void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
        auto key = this->getKey();
        auto data = this->getData();
        structure.insert(key, data);
    }
    template<class Table>
    void TableAnalyzer<Table>::afterOperation(Table& structure)
    {
        for (size_t i = 0; i < this->getStepSize(); i++)
        {
            this->IS_data.clear();
        }
    }

    template<class Table>
    inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) : TableAnalyzer<Table>(name)
    {
    }
    template<class Table>
    inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        auto key = this->getKey();
        structure.findBlockWithKey(key);
    }
}
