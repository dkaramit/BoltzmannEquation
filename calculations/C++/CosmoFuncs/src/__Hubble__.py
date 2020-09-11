import ctypes
import os



cdouble=ctypes.c_double
cint=ctypes.c_int

#load the library
func = ctypes.CDLL(_PATH_+'/libH.so')

# define a function that takes no arguments and returns a function pointer (a list of function in CppFunc[i]) of the form:
# typedef double(*FuncType)(int)
CppFunc=func.hsub,func.gsub,func.dhsub,func.rsub,func.Hsub,func.Ssub  
CppFunc_den=func.nbsub,func.nfsub,func.rbsub,func.rfsub,func.n1bsub,func.n1fsub

#specify the argument types
for i,f in enumerate (CppFunc): 
    f.argtypes = None
    #specify the return type
    f.restype = ctypes.CFUNCTYPE(cdouble, cdouble) 
################################################
#specify the argument types for the densities
for i,f in enumerate (CppFunc_den): 
    f.argtypes = None
    #specify the return type
    f.restype = ctypes.CFUNCTYPE(cdouble, cdouble, cdouble) 
################################################

####---since ff returns a function pointer, FuncPY is now what ff retured.---###
heff=func.hsub()
geff=func.gsub()
dh=func.dhsub()
rhoR=func.rsub()
Hubble=func.Hsub()
s=func.Ssub()
n_bose=func.nbsub()
n_fermi=func.nfsub()
rho_bose=func.rbsub()
rho_fermi=func.rfsub()
n1_bose=func.n1bsub()
n1_fermi=func.n1fsub()

#####################
# Run some tests:
if __name__=="__main__":
    from numpy import logspace
    for i in range(-10,10):
        print( heff(i) , geff(i) , rhoR(i) , Hubble(i) )
    for i in logspace(-2,2,10):
        print( n_bose(i,1) , n_fermi(i,1) , rho_bose(i,1) , rho_fermi(i,1), 
        n1_bose(i,1) , n1_fermi(i,1) )