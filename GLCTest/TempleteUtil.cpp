//#ifdef _MSC_VER
#include "StdAfx.h"
//#endif
#include "TempleteUtil.h"
/*
template<int n,class F>
struct Accumlate
{ enum{RET=Accumlate<n-1,F>::RET + F::template Apply<n>::RET};
};
template<class F>
struct Accumlate<0.F>
{ enum {RET=F::template Apply<0>::RET};
};
*/

template <class T>struct LessThan{
    T value;
    LessThan(const T& v):value(v){};
    bool operator()(const T& v) const{return v<value}
};

template<int no> struct TypeNo{};
template<> struct TypeNo<0>{typedef wchar_t Type;};
template<> struct TypeNo<1>{typedef bool Type;};
template<> struct TypeNo<2>{typedef char Type;};

template <class A> struct TypeTraits{};
template<> struct TypeTraits<wchar_t>{enum {no=0}; static char* name(){return "wchar_t";};};
template<> struct TypeTraits<bool>{enum {no=1}; static char* name(){return "bool";};};
template<> struct TypeTraits<char>{enum {no=2}; static char* name(){return "char";};};


template<bool cond,class Then,class Else>
struct IF{
  typedef Then RET;
};
template<class Then,class Else>
struct IF<false,Then,Else>
{  
  typedef Else RET;
};
struct Square{
    template<int n>
    struct Apply
    {
        enum{RET= n*n};
    };
};

#include <iostream>
void U::printAc(){
    using namespace std;
    cout<<Square::Apply<3>::RET << endl;
    cout<< TypeTraits<char>::name() <<endl;
}