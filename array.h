//
// Created by Pierre-Antoine GUILLAUME.
//

#ifndef PAG_ARRAY_H
#define PAG_ARRAY_H

namespace pag
{
    template <typename T, unsigned long int D>
    class array
    {
    public:

        //current array size
        unsigned long int size() const;

        //ref accessor
        T & operator[](const unsigned long int index);
        //const ref accessor
        const T &  operator[](const unsigned long int index) const;

        T& reverse(const unsigned long int index);
        const T &  reverse(const unsigned long int index) const;

        //constructor, with c style array or nothing
        array(T * underlaying);
        array();
        //destructor
        ~array();

        T * begin();
        const T * begin() const;
        T * end();
        const T * end() const;

    private:
        T  p[D] = {T()};//actual container
    };
}

template <typename T, unsigned long int D>
unsigned long int pag::array<T,D>::size() const
{
    return D;
}



template <typename T, unsigned long int D>
const T & pag::array<T,D>::operator[](const unsigned long int index) const
{
    return p[index];
}

template <typename T, unsigned long int D>
T & pag::array<T,D>::operator[](const unsigned long int index)
{
    return p[index];
}

template <typename T, unsigned long int D>
const T & pag::array<T,D>::reverse(const unsigned long int index) const
{
    return p[size()-index];
}

template <typename T, unsigned long int D>
T & pag::array<T,D>::reverse(const unsigned long int index)
{
    return p[size()-index];
}



template <typename T, unsigned long int D>
pag::array<T,D>::array()
{

}

template <typename T, unsigned long int D>
pag::array<T,D>::array(T * array)
{
    for (unsigned i =0;i<D;++i)
    {
        p[i] = *(array+i);
    }
}

template <typename T, unsigned long int D>
pag::array<T,D>::~array()
{
}


template <typename T, unsigned long int D>
const T * pag::array<T,D>::begin() const
{
    return p;
}

template <typename T, unsigned long int D>
const T * pag::array<T,D>::end() const
{
    return p+size();
}

template <typename T, unsigned long int D>
T * pag::array<T,D>::begin()
{
    return p;
}

template <typename T, unsigned long int D>
T * pag::array<T,D>::end()
{
    return p+size();
}

#endif //PAG_ARRAY_H
