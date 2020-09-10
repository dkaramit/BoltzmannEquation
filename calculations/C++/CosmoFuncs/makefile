# ---example of other path--- #
#Path = "/home/USR/calculations/python-C++/CosmoFuncs"

#set PATH variable to working directory
Path=$(PWD)

CC=g++ #compiler. I use g++, and haven't tested anything else. 

LONG= long #use long doubles. Slower (marginally), but more accurate. 
#Keep in mind that Hubble.hpp uses doubles, which can cause problems (n_bose for x>750 returns 0).


#---optimization options---#
# OPT=O0
# OPT=O1
# OPT=O2 
# OPT=O3 
# OPT=Os

#3 times faster. May result to low accuracy (that's what the internet says. I haven't seen anything bad happening!).
OPT=Ofast #may cause problems with VEGAS



# STD=gnu++17 
STD=c++17

# GSL directory
# GSL_DIR=-L"/usr/include/gsl"
#leave it empty if you don't care
GSL_DIR=


FLG= -$(OPT)  -std=$(STD) -lm  $(GSL_DIR) -lgsl -lgslcblas -DLONG=$(LONG) -I "$(Path)" -I "$(Path)/src"




# "make all" will look for libH.so, so it will go to execute "make libH.so"
all: libH.so 
	


# "make paths" makes a header file that defines macros with the paths of heff.dat and T_s.dat.
# Then it makes a python script where at the top a global variable _PATH_ is defined (the path of libH.so that will be created),
# followed by the definitios of ctypes etc. as in _Hubble.py.
paths: 
	@echo "$(Path)"
	echo "#define h_PATH \"$(Path)/src/data/eos2020.dat\" "> "$(Path)/src/path.hpp"
	echo "#define Ts_PATH \"$(Path)/src/data/T_s.dat\" ">> "$(Path)/src/path.hpp"
	echo "#define den_PATH \"$(Path)/src/data/densities.dat\" ">> "$(Path)/src/path.hpp"


	echo "_PATH_=\"$(Path)\" "> "$(Path)/Hubble.py"

	cat "src/__Hubble__.py" >> "$(Path)/Hubble.py"


# "make libH.so" will look for paths, so it will execute "make paths"
# then it will compile Hubble-py.cpp to created libH.so in the current directory.
libH.so:  paths
	$(CC)  -fPIC "$(Path)/src/Hubble-py.cpp" -shared -o "$(Path)/libH.so"  $(FLG)


	

#cleans whatever make all created
clean: 
	@[ -f "$(Path)/libH.so" ] &&  rm "$(Path)/libH.so" || true
	@[ -f "$(Path)/src/path.hpp" ] && rm "$(Path)/src/path.hpp" || true
	@[ -f "$(Path)/Hubble.py" ] && rm  "$(Path)/Hubble.py" || true


# remove ignored files
git_clean:	 
	@git clean -fX
