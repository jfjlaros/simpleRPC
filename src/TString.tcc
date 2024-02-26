#pragma once

#include <defs.h>
#include <PString.h>

template<size_t S>
class TString : public PString
{
public:
    TString() : PString(_buffer, S)
    {
        
    }

    template<class T> TString(T arg) : PString(_buffer, S, arg)
    {

    }

    template<class T> TString(T arg, int modifier) : PString(_buffer, S, arg, modifier)
    {
        
    }

    // This function allows assignment to an arbitrary scalar value like 
    //    str = myfloat;
    template<class T> inline TString<S> &operator =(T arg) 
    {
        begin();
        print(arg);
        return *this;
    }

    // Concatenation of any type data
    //    str += myfloat;
    template<class T> inline TString<S> &operator +=(T arg) 
    {
        print(arg);
        return *this;
    }

private:
    char _buffer[S];
};