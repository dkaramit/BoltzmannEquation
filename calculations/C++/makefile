-include Definitions.mk 


#c++ std
STD=c++17

#you can inlude more things here
PATH_INCLUDE= -I./

FLG= -$(OPT) -std=$(STD) -lstdc++ -lm $(PATH_INCLUDE) -Wall

Ros_Headers= $(wildcard $(rootDir)src/Rosenbrock/*.hpp) $(wildcard $(rootDir)src/Rosenbrock/LU/*.hpp) $(wildcard $(rootDir)src/Rosenbrock/Jacobian/*.hpp) 
RKF_Headers= $(wildcard $(rootDir)src/RKF/*.hpp)  
SPLINE_Headers=$(wildcard $(rootDir)src/Interpolation/*.hpp)

PathHead=$(rootDir)src/misc_dir/path.hpp
PathTypePy=$(rootDir)src/misc_dir/type.py


Cosmo_Headers= $(wildcard $(rootDir)src/Cosmo/Cosmo.hpp)
Cosmo_Cpp= $(wildcard $(rootDir)src/Cosmo/Cosmo.cpp) 

Static_Funcs= $(wildcard $(rootDir)src/static.hpp) 

all: lib exec examples

lib: lib/libCosmo.so 
	
exec: check

#shared libraries that can be used from python
lib/libCosmo.so: $(Cosmo_Headers) $(Cosmo_Cpp) $(SPLINE_Headers) $(Static_Funcs)
	$(CC) -o lib/libCosmo.so $(rootDir)src/Cosmo/Cosmo.cpp -fPIC -shared $(FLG) -DLONG=$(LONGpy)


# make the examples in Examples/Cpp
examples:
	cd Examples/Cpp && $(MAKE)


#cleans whatever make all created
clean:
	rm -rf $(wildcard lib/*)
	rm -rf $(wildcard exec/*)
	rm -rf $(wildcard Examples/Python/*_examplePlot.pdf)
	rm -rf $(PathTypePy)
	cd Examples/Cpp && $(MAKE) clean


#deletes directories that configure.sh made
deepClean: clean
	rm -rf lib
	rm -rf exec
	rm -rf $(rootDir)src/misc_dir



##--------------------------------make checks----------------------------------------##
check: exec/Cosmo_check.run

Cosmo_check_cpp=$(wildcard $(rootDir)src/Cosmo/checks/Cosmo_check.cpp)
# check anharmonic factor interpolation
exec/Cosmo_check.run: $(Cosmo_check_cpp) $(Cosmo_Headers) $(DataFiles) $(SPLINE_Headers)
	$(CC) -o exec/Cosmo_check.run $(rootDir)src/Cosmo/checks/Cosmo_check.cpp $(FLG) -DLONG=$(LONG)
