#pragma once

#include <libds/amt/abstract_memory_type.h>
#include <libds/amt/sequence.h>


namespace ds::amt {

	template<typename DataType>
	class ImplicitSequence :
		public Sequence<MemoryBlock<DataType>>,
		public ImplicitAMS<DataType>
	{
	public:
		using BlockType = MemoryBlock<DataType>;

		ImplicitSequence();
		ImplicitSequence(size_t capacity, bool initBlocks);
		ImplicitSequence(const ImplicitSequence<DataType>& other);
		~ImplicitSequence() override;

		size_t calculateIndex(MemoryBlock<DataType>& block) override;

		BlockType* accessFirst() const override;
		BlockType* accessLast() const override;
		BlockType* access(size_t index) const override;
		BlockType* accessNext(const BlockType& block) const override;
		BlockType* accessPrevious(const BlockType& block) const override;

		BlockType& insertFirst() override;
		BlockType& insertLast() override;
		BlockType& insert(size_t index) override;
		BlockType& insertAfter(BlockType& block) override;
		BlockType& insertBefore(BlockType& block) override;

		DataType& operator[](size_t index)
		{
			return this->access(index)->data_;
		};

		void push_back(DataType&& type) 
		{
			this->insertLast();
			this->access(this->size() - 1)->data_ = type;
		};

		void removeFirst() override;
		void removeLast() override;
		void remove(size_t index) override;
		void removeNext(const MemoryBlock<DataType>& block) override;
		void removePrevious(const MemoryBlock<DataType>& block) override;

		void reserveCapacity(size_t capacity);

		virtual size_t indexOfNext(size_t currentIndex) const;
		virtual size_t indexOfPrevious(size_t currentIndex) const;


	public:
		class ImplicitSequenceIterator {
		public:
			ImplicitSequenceIterator(ImplicitSequence<DataType>* sequence, size_t index);
			ImplicitSequenceIterator(const ImplicitSequenceIterator& other);
			ImplicitSequenceIterator& operator++();
			ImplicitSequenceIterator operator++(int);
			bool operator==(const ImplicitSequenceIterator& other) const;
			bool operator!=(const ImplicitSequenceIterator& other) const;
			DataType& operator*();

		private:
			ImplicitSequence<DataType>* sequence_;
			size_t position_;
		};

		ImplicitSequenceIterator begin();
		ImplicitSequenceIterator end();

		using IteratorType = ImplicitSequenceIterator;
	};

	template<typename DataType>
	using IS = ImplicitSequence<DataType>;

	//----------

	template<typename DataType>
	class CyclicImplicitSequence : public IS<DataType>
	{
	public:
		CyclicImplicitSequence();
		CyclicImplicitSequence(size_t initSize, bool initBlocks);

		size_t indexOfNext(size_t currentIndex) const override;
		size_t indexOfPrevious(size_t currentIndex) const override;
	};

	template<typename DataType>
	using CIS = CyclicImplicitSequence<DataType>;

	//----------

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence()
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence(size_t initialSize, bool initBlocks):
		ImplicitAMS<DataType>(initialSize, initBlocks)
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence(const ImplicitSequence<DataType>& other):
		ImplicitAMS<DataType>::ImplicitAbstractMemoryStructure(other)
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::~ImplicitSequence()
	{
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::calculateIndex(BlockType& block)
	{
		return ImplicitAMS<DataType>::getMemoryManager()->calculateIndex(block);
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessFirst() const
	{
		return AbstractMemoryStructure<BlockType>::size() > 0 ? &ImplicitAMS<DataType>::getMemoryManager()->getBlockAt(0) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessLast() const
	{
		const size_t size = this->size();
		return size > 0 ? &this->getMemoryManager()->getBlockAt(size - 1) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::access(size_t index) const
	{
		return index < this->size() ? &this->getMemoryManager()->getBlockAt(index) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessNext(const MemoryBlock<DataType>& block) const
	{
		typename ImplicitAMS<DataType>::MemoryManagerType& memManager = *ImplicitAMS<DataType>::getMemoryManager();
		const size_t index = indexOfNext(memManager.calculateIndex(block));
		return index < this->size() ? &memManager.getBlockAt(index) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessPrevious(const MemoryBlock<DataType>& block) const
	{
		typename ImplicitAMS<DataType>::MemoryManagerType& memManager = *ImplicitAMS<DataType>::getMemoryManager();
		const size_t index = indexOfPrevious(memManager.calculateIndex(block));
		return index != INVALID_INDEX ? &memManager.getBlockAt(index) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertFirst()
	{
		return *(ImplicitAMS<DataType>::getMemoryManager()->allocateMemoryAt(0));
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertLast()
	{
		return *(ImplicitAMS<DataType>::getMemoryManager()->allocateMemory());
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insert(size_t index)
	{
		return *static_cast<MemoryBlock<DataType>*>(ImplicitAMS<DataType>::getMemoryManager()->allocateMemoryAt(index));
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertAfter(MemoryBlock<DataType>& block)
	{
		typename ImplicitAMS<DataType>::MemoryManagerType& CMM = *ImplicitAMS<DataType>::getMemoryManager();
		return *static_cast<MemoryBlock<DataType>*>(CMM.allocateMemoryAt(CMM.calculateIndex(block) + 1));
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertBefore(MemoryBlock<DataType>& block)
	{
		typename ImplicitAMS<DataType>::MemoryManagerType* memManager = this->getMemoryManager();
		return *memManager->allocateMemoryAt(memManager->calculateIndex(block));
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeFirst()
	{
		ImplicitAMS<DataType>::getMemoryManager()->releaseMemoryAt(0);
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeLast()
	{
		ImplicitAMS<DataType>::getMemoryManager()->releaseMemory();
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::remove(size_t index)
	{
		ImplicitAMS<DataType>::getMemoryManager()->releaseMemoryAt(index);
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeNext(const MemoryBlock<DataType>& block)
	{
		ds::mm::CompactMemoryManager<BlockType>& CMP = *ImplicitAMS<DataType>::getMemoryManager();
		CMP.releaseMemoryAt(this->indexOfNext(CMP.calculateIndex(block)));
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removePrevious(const MemoryBlock<DataType>& block)
	{
		typename ImplicitAMS<DataType>::MemoryManagerType& CMP = *ImplicitAMS<DataType>::getMemoryManager();
		CMP.releaseMemoryAt(this->indexOfPrevious(CMP.calculateIndex(block)));
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::reserveCapacity(size_t capacity)
	{
		ImplicitAMS<DataType>::getMemoryManager()->changeCapacity(capacity);
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::indexOfNext(size_t currentIndex) const
	{
		return currentIndex >= this->size() - 1 ? INVALID_INDEX : currentIndex + 1;
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::indexOfPrevious(size_t currentIndex) const
	{
		return currentIndex <= 0 ? INVALID_INDEX : currentIndex - 1;
	}

    template <typename DataType>
    ImplicitSequence<DataType>::ImplicitSequenceIterator::ImplicitSequenceIterator
        (ImplicitSequence<DataType>* sequence, size_t index) :
		    sequence_(sequence),
            position_(index)
    {
    }

    template <typename DataType>
    ImplicitSequence<DataType>::ImplicitSequenceIterator::ImplicitSequenceIterator
        (const ImplicitSequenceIterator& other) :
		    sequence_(other.sequence_),
            position_(other.position_)
    {
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::ImplicitSequenceIterator::operator++() -> ImplicitSequenceIterator&
    {
		position_++;
		return *this;
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::ImplicitSequenceIterator::operator++(int) -> ImplicitSequenceIterator
    {
		ImplicitSequenceIterator tmp(*this);
	    operator++();
	    return tmp;
    }

    template <typename DataType>
    bool ImplicitSequence<DataType>::ImplicitSequenceIterator::operator==(const ImplicitSequenceIterator& other) const
    {
		return sequence_ == other.sequence_ && position_ == other.position_;
    }

    template <typename DataType>
    bool ImplicitSequence<DataType>::ImplicitSequenceIterator::operator!=(const ImplicitSequenceIterator& other) const
    {
		return !(*this == other);
    }

    template <typename DataType>
    DataType& ImplicitSequence<DataType>::ImplicitSequenceIterator::operator*()
    {
		return sequence_->access(position_)->data_;
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::begin() -> ImplicitSequenceIterator
    {
		return ImplicitSequenceIterator(this, 0);
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::end() -> ImplicitSequenceIterator
    {
		return ImplicitSequenceIterator(this, ImplicitAbstractMemoryStructure<DataType>::size());
    }

    template<typename DataType>
    CyclicImplicitSequence<DataType>::CyclicImplicitSequence():
		IS<DataType>()
	{
	}

	template<typename DataType>
    CyclicImplicitSequence<DataType>::CyclicImplicitSequence(size_t initCapacity, bool initBlocks):
		IS<DataType>(initCapacity, initBlocks)
	{
	}

	template<typename DataType>
    size_t CyclicImplicitSequence<DataType>::indexOfNext(size_t currentIndex) const
	{
		const size_t size = this->size();
		return size != 0 ? currentIndex >= size - 1 ? 0 : currentIndex + 1 : INVALID_INDEX;
	}

	template<typename DataType>
    size_t CyclicImplicitSequence<DataType>::indexOfPrevious(size_t currentIndex) const
	{
		const size_t size = this->size();
		return size != 0 ? currentIndex <= 0 ? size - 1 : currentIndex - 1 : INVALID_INDEX;
	}
}