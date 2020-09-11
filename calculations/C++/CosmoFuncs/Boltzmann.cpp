/*=============== Solve only the radiation Phi System =================*/
/*C++ stuff*/
#include <iostream>

#include <fstream>
#include <string>
#include <functional>
#include <vector>

using std::cout;
using std::endl;



/*CosmoFuncs stuff*/
#include "src/Hubble.hpp"
#include "src/misc.hpp"



#ifndef LONG
    #define LONG 
#endif

#define LD LONG double

int main(int argc, char **argv){ 
    std::fstream eos("src/data/eos2020.dat", std::ios_base::in);
    
    std::vector<LD> Ttab;
    std::vector<LD> stab;
    std::vector<LD> rhotab;
    std::vector<LD> sint;    
    std::vector<LD> rhoint;    

    LD a[3];
    int len=0;
    while (eos >> a[0] >>a[1] >>a[2])
    {
        Ttab.push_back(a[0]);
        stab.push_back(2*M_PI*M_PI/45.*a[1]*std::pow(a[0],3)  );
        rhotab.push_back(M_PI*M_PI/30.*a[1]*std::pow(a[0],4)  );
        sint.push_back( s(a[0]) );
        rhoint.push_back( rhoR(a[0]) );
        len++;
    }


    for(int i=0; i<len;++i ){
        cout<<Ttab[i]<<"\t"<<sint[i]<<"\t"<<stab[i]<<"|||"<<rhoint[i]<<"\t"<<rhotab[i]<<":::"<<dh(Ttab[i])<<endl;
    }


    return 0;
}
