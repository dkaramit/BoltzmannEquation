These files are the different densities we need. See also $\tt Mathematica$ file to see how it works.

All densities are functions of $x=m/T$ ($m$ is the mass of the particle) and are evaluated at $m=1$ and   $g=1$ (internal degrees of freedom).

n_boson.dat and n_fermion.dat contain points for the number densities of fermions and bosons, respectively. It is defined as

$$ 
n_{f,b}= \int \dfrac{d^3 \vec p}{ (2\pi)^3} \dfrac{1}{e^{E(p)/T } \pm 1} = \dfrac{4\pi}{(2\pi)^3} m^3 \int_{1}^{\infty} dt \dfrac{t \sqrt{t^2-1} }{e^{x \, t}  \pm 1} \;.
$$

To evaluate it at different mass, multiply it by $m^3$.

rho_boson.dat and rho_fermion.dat contain points for the energy densities of fermions and bosons, respectively. It is defined as

$$ 
\rho_{f,b}= \int \dfrac{d^3 \vec p}{ (2\pi)^3 } \dfrac{E(p)}{e^{E(p)/T } \pm 1} = \dfrac{4\pi}{(2\pi)^3} m^4 \int_{1}^{\infty} dt \dfrac{t^2 \sqrt{t^2-1} }{e^{x \, t}  \pm 1} 
$$

To evaluate it at different mass, multiply it by $m^4$.


n-1_boson.dat and n-1_fermion.dat contain points for the densities defined by 
$$ 
n^{(-1)}_{f,b}= \int \dfrac{d^3 \vec p}{ (2\pi)^3 E(p)} \dfrac{1}{e^{E(p)/T } \pm 1} = \dfrac{4\pi}{(2\pi)^3} m^2 \int_{1}^{\infty} dt \dfrac{\sqrt{t^2-1} }{e^{x \, t}  \pm 1} \;.
$$

To evaluate it at different mass, multiply it by $m^2$.


All the densities are concentrated in the densities.dat file. The first column is the x, the second n_b, third n_f, etc.  