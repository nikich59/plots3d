#ifndef QPTRVECTOR
#define QPTRVECTOR

#include <QVector>

namespace
{

template <class T>
class QPtrVector
{
public:
    QPtrVector();
    ~QPtrVector();
    void push_back(T *member) {m_vector.push_back(member); }
    const T *operator[](int num) const {return m_vector[num]; }

private:
    QVector <T *> m_vector;
};

template <class T>
QPtrVector<T>::QPtrVector()
{
}

template <class T>
QPtrVector<T>::~QPtrVector()
{
    for (int i = 0; i < m_vector.length(); i++)
        delete m_vector[i];
    m_vector.clear();
}

void byteCopy(const void *from, void *to, int sizeInBytes)
{
    for (uint8_t *_from = (uint8_t *)from, *_to = (uint8_t *)to; _from < (uint8_t *)from + sizeInBytes;
         _from++, _to++)
        *_to = *_from;
}

}
#endif // QPTRVECTOR

