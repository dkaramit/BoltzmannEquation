// g++  -fPIC Hubble-py.cpp -shared -o libH.so  -lm -lgsl -lgslcblas
//This is how you can use Hubble.hpp in python


#include "Hubble.hpp"

//define a function pointer type.
//I will use this to basically copy the h,h,rho,Hubble function inside python. 
typedef double(*FuncType)(double);
typedef double(*FuncType_den)(double,double);



extern "C"{
    //this functions return h,g,rho,Hubble, etc. So in python I will a copy of this (see Hubble.py)
    FuncType hsub(  ){
        return heff;
    }
    FuncType gsub(  ){
        return geff;
    }
    FuncType dhsub(  ){
        return dh;
    }
    FuncType rsub(  ){
        return rhoR;
    }
    FuncType Hsub(  ){
        return Hubble;
    }
    
    FuncType Ssub(  ){
        return s;
    }

    FuncType_den nbsub(  ){
        return n_bose;
    }
    FuncType_den nfsub(  ){
        return n_fermi;
    }
    FuncType_den rbsub(  ){
        return rho_bose;
    }
    FuncType_den rfsub(  ){
        return rho_fermi;
    }
    FuncType_den n1bsub(  ){
        return n1_bose;
    }
    FuncType_den n1fsub(  ){
        return n1_fermi;
    }
    

}
