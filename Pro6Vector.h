/*
Aaron Shackelford
CISP 400
Project 6
6:00 PM class
*/

#ifndef AARON_ECTOR_H_DEF_
#define AARON_ECTOR_H_DEF_
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Vector
{
  T* _array;
  unsigned _size;
  unsigned _length;
  int _zero; //the offset number


public:
  Vector (int Vindex = 0);
  Vector (const T*, unsigned s, int Vindex = 0);
  Vector (const Vector&);
  ~Vector ();

  Vector<T>& operator= (const Vector<T>&);

  template <class OS>
  friend ostream& operator<< (ostream&, const Vector<OS>&);

  template <class OS>
  friend ostream& operator<< (ostream&, const Vector<OS>*);

  T& operator[] (int Vindex);
  const T& operator[] (int Vindex) const;

  Vector operator() (int Vfirst, int Vlast) const;

  unsigned Length() const{return _length;};

  Vector& operator+= (const T&);
  Vector& operator+= (const Vector&);

  void Remove (const int Vindex);
  void Remove (int Vfirst, int Vlast);
  void Remove ();

  void Insert (const T&, int Vindex);
  void Insert (const T&);

};

#endif

template <class T>
Vector<T>::Vector(int Vindex)
{
  _array  = (NULL);
  _size   = (0);
  _length = (0);
  _zero   = Vindex;
}

template <class T>
Vector<T>::Vector (const T* a, unsigned s, int Vindex)
{
  _array  = (NULL);
  _size   = (0);
  _length = (0);
  _zero   = Vindex;
  for(unsigned i=0; i<s; i++)
  {
    operator+= (a[i]);
  }
}

template <class T>
Vector<T>::Vector (const Vector& v)
{
  _array  = (NULL);
  _size   = (0);
  _length = (0);
  _zero   = v._zero;
  for(unsigned i=0; i<v._length; i++)
  {
    operator+= (v._array[i]);
  }
}

template <class T>
Vector<T>::~Vector ()
{
  delete [] _array;
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T>& v)
{
  if(this != &v)
  {
    unsigned stop = v._length;
    delete [] _array;
    _array = NULL;
    _size = 0;
    _length = 0;
    _zero = v._zero;
    for(unsigned i = 0; i < stop; i++)
    {
      operator+= (v._array[i]);
    }
  }
  return *this;
}

template <class OT>
ostream& operator<< (ostream& os, const Vector<OT>& v)
{
  if(v._length != 0)
  {
    os << v._array[0];
    for(unsigned i=1; i<v._length; i++)
    {
      os << ", " << (v._array[i]);
    }
  }
  return os;
}

template <class OT>
ostream& operator<< (ostream& os, const Vector<OT>* v)
{
  os << *v;
  return os;
}


template <class T>
T& Vector<T>::operator[] (int Vindex)
{
  int Aindex = Vindex - _zero;
  if(Aindex < 0 || Aindex >= _length)
  {
    cout << "operator[] index out of range\n";
    exit(200);
  }
  return _array[Aindex];
}

template <class T>
Vector<T> Vector<T>::operator() (int Vfirst, int Vlast) const
{
  int Afirst = Vfirst - _zero;
  int Alast = Vlast - _zero;
  if((Afirst < 0) || (Afirst >= Alast) || (Alast >= _length))
  {
    cout << "operator() index out of range\n";
    exit(200);
  }
  Vector<T> ret (_zero);
  for(unsigned i=Afirst; i<= Alast; i++)
  {
    ret += _array[i];
  }
  return ret;
}

template <class T>
void Vector<T>::Remove(const int Vindex)
{
  int Aindex = Vindex - _zero;
  if((Aindex<0) || (Aindex >= _length))
  {
    cout << "Remove index out of range\n";
    exit(200);
  }
  Vector<T> temp(_zero);
  for(unsigned i=0; i<_length; i++)
  {
    if(i != Aindex)
    {
      temp += _array[i];
    }
  }
  *this = temp;
}

template <class T>
void Vector<T>::Remove(int Vfirst, int Vlast)
{
  if(Vfirst >= Vlast)
  {
    cout << "Remove index(s) out of range\n";
    exit(200);
  }
  for(unsigned i = Vfirst; i < Vlast; i++)
  {
    Remove(Vfirst);
  }
}

template <class T>
void Vector<T>::Remove()
{
  Remove(_zero);
}

template <class T>
void Vector<T>::Insert(const T& newt, int Vindex)
{
  int Aindex = Vindex - _zero;
  if((Aindex<0) || (Aindex >= _length))
  {
    cout << "Insert index out of range\n";
    exit(200);
  }
  unsigned stop = _length +1;
  Vector<T> temp(_zero);
  for(unsigned i=0; i< stop; i++)
  {
    if(i==Aindex)
    {
      temp+=( newt );
    }
    temp+=(_array[i]);
  }
  *this = temp;
}

template <class T>
void Vector<T>::Insert(const T& newt)
{
  Insert(newt, _zero);
}

template <class T>
Vector<T>& Vector<T>::operator+=(const T& newt)
{
  if((_length+1)>_size)
  {
    _size = ((_size == 0) ? 1 : (_size*2));
    T* temp = new T[_size];
    if(_length != 0)
    {
      for(unsigned i=0; i<_length; i++)
      {
        temp[i] = _array[i];
      }
    }
    delete [] _array;
    _array = temp;
  }
  _array[_length++] = newt;
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator+= (const Vector& v)
{
  unsigned stop = v._length;
  if(stop != 0)
  {
    for(unsigned i=0; i < stop; i++)
    {
      operator+=(v._array[i]);
    }
  }
  return *this;
}
