//
// Created by Pierre-Antoine on 26/12/2016.
//

#ifndef PAG_QUEUE_H
#define PAG_QUEUE_H

namespace pag
{

    template <typename T,unsigned long reserved_size>
    class queue
    {
    public:
        typedef T value_type;
        typedef T& ref_type;
        typedef T* ptr_type;
        typedef unsigned long size_type;
    private:
        value_type p[reserved_size];
        value_type * head;
        value_type * tail;

        void shift();
    public:
        queue();

        bool empty() const;
        size_type size() const;
        ref_type front();
        ref_type back();
        void push(const ref_type item);
        void pop();

        //inherent to embedded system
        //to avoid using extra vtable to iterate over list etc.
        size_type max_size() const;
        bool full() const;

        T* begin();
        T* end();
    };

    template <typename T,unsigned long reserved_size>
    unsigned long pag::queue<T,reserved_size>::max_size() const
    {
        return reserved_size;
    }

    template <typename T,unsigned long reserved_size>
    pag::queue<T,reserved_size>::queue()
    {
        head = tail = p;
    }

    template <typename T,unsigned long reserved_size>
    bool pag::queue<T,reserved_size>::empty() const
    {
        return !size();
    }

    template <typename T,unsigned long reserved_size>
    unsigned long pag::queue<T,reserved_size>::size() const
    {
        return tail - head;
    }

    template <typename T,unsigned long reserved_size>
    T& pag::queue<T,reserved_size>::front()
    {
        return *head;
    }

    template <typename T,unsigned long reserved_size>
    T& pag::queue<T,reserved_size>::back()
    {
        return *tail;
    }

    template <typename T,unsigned long reserved_size>
    void pag::queue<T,reserved_size>::pop()
    {
        if (!empty())
            head+=1;
    }

    template <typename T,unsigned long reserved_size>
    void pag::queue<T,reserved_size>::push(const ref_type item)
    {
        if (full()) pop();
        shift();
        *(tail) = item;
        tail +=1;

    }

    template <typename T,unsigned long reserved_size>
    bool pag::queue<T,reserved_size>::full() const
    {
        return size() == max_size();
    }

    template <typename T,unsigned long reserved_size>
    void pag::queue<T,reserved_size>::shift()
    {
        const size_type step = head - p;
        if (step)
        {
            for (T * i = p;i<tail-step;++i)
            {
                *i = *(i+step);
            }
            head = p;
            tail -=step;
        }
    }
    template <typename T,unsigned long reserved_size>
    T* pag::queue<T,reserved_size>::begin()
    {
        return head;
    }

    template <typename T,unsigned long reserved_size>
    T* pag::queue<T,reserved_size>::end()
    {
        return tail;
    }
}


#endif //PAG_QUEUE_H
