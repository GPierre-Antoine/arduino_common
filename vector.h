//
// Created by Pierre-Antoine GUILLAUME.
//

#ifndef PAG_VECTOR_H
#define PAG_VECTOR_H

namespace pag
{
    template <typename T>
    class vector
    {
    public:

        //current array size
        unsigned long long int size() const;

        //ref accessor
        T & operator[](const unsigned long long int index);
        //const ref accessor
        const T &  operator[](const unsigned long long int index) const;

        //constructor, with size
        vector(const unsigned long long int size = 0);
        //destructor
        ~vector();

        //changes the size of the vector
        //returns : true if the operation succedes
        //returns : false if the operation fails. No information lost.
        bool resize(const unsigned long long int new_size);

        T * begin();
        const T * begin() const;
        T * end();
        const T * end() const;

    private:
        T * array;//actual container
        unsigned long long int size_of_array;//size keeper.
    };
}

template <typename T>
unsigned long long int pag::vector<T>::size() const
{
    return size_of_array;
}

template <typename T>
T & pag::vector<T>::operator[](const unsigned long long int index)
{
    return array[index];
}

template <typename T>
const T & pag::vector<T>::operator[](const unsigned long long int index) const
{
    return array[index];
}

template <typename T>
pag::vector<T>::vector(const unsigned long long int size) : size_of_array (size)
{
    if (size_of_array)
        array = malloc(size_of_array * sizeof(T));
}

template <typename T>
pag::vector<T>::~vector()
{
    free(array);
}

template <typename T>
bool pag::vector<T>::resize(const unsigned long long int new_size)
{

    T * temp = (T *)
            realloc(array, sizeof(T) * new_size);
    if (temp)
    {
        array = temp;
        size_of_array = new_size;
    }
    return array != NULL;
}

template <typename T>
T * pag::vector<T>::begin()
{
    return array;
}

template <typename T>
const T * pag::vector<T>::begin() const
{
    return array;
}

template <typename T>
T * pag::vector<T>::end()
{
    return array + size_of_array;
}

template <typename T>
const T * pag::vector<T>::end() const
{
    return array + size_of_array;
}

#endif //PAG_VECTOR_H
