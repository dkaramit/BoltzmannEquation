In heff.dat, you can find the relativistic degrees of freedom as a function of the temperature.
The format is:
$$T ~[{\rm GeV}]  \; h_{eff} \; g_{eff}$$

Note that for T>1000 GeV both g and h are constant. They are also constant for T<10^-5 GeV
 

In densities.dat you find diferent densities for bosons (denoted with b) and fermions (denoted by f ),
at some x (denied as $m/T$) and $m=1~{\rm GeV}$. Their relation with m is usually simle, so we can do that! The format is:
$$
x  \;  n_{b} \; n_{f} \; \rho_{b} \; \rho_{f} \; n_{b}^{(-1)} \;  n_{f}^{(-1)} 
$$


Actually, you can checkout Hubble.hpp, which is simple to understand. Once you run make, you can see check the jupyter-notebook in tests/Cosmo-plots (or run the Hubble.py as a script), and see that everything is Ok.