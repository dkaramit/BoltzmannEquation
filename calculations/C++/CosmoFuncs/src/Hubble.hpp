#ifndef HEAD_HUBBLE
#define HEAD_HUBBLE
#include <cmath>
#include <fstream>
#include<string>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_errno.h>

#include "path.hpp"





#define Mp 1.22e19


//this file is found in https://member.ipmu.jp/satoshi.shirai/DM2020/
// the data are : T  h  g
// arXiv: 2005.03544 
#define N_h_tab 529


#define N_den_tab 1000

static void get_data(double *T,double *g,double *h,
 double *x, double *nb, double *nf, double *rb, double *rf, double *n1b, double *n1f){
        
        std::ifstream input_h(h_PATH); 
        std::ifstream input_den(den_PATH);

        //Store the data for increasig T (gls wants it like that)
        int i=0;
        while (true)
        {
            input_h>>T[i];
            input_h>>h[i];
            input_h>>g[i];

    
            if (input_h.eof())
            {
                break;
            }
            i++;
        }




        i=0;//These files have increasing x, so I read them normally
        while (true)
        {   //std::cout<<i<<std::endl;

            input_den>>x[i];
            input_den>>nb[i];
            input_den>>nf[i];
            input_den>>rb[i];
            input_den>>rf[i];
            input_den>>n1b[i];
            input_den>>n1f[i];

    
            if (input_den.eof())
            {
                break;
            }
            i++;
        }
}




class Cosmo{
    private:

    gsl_interp_accel *g_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *g_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_h_tab);

    gsl_interp_accel *h_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *h_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_h_tab);
    
    // 
    gsl_interp_accel *nb_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *nb_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    
    gsl_interp_accel *nf_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *nf_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    // 
    
    gsl_interp_accel *rb_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *rb_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    
    gsl_interp_accel *rf_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *rf_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    // 
    
    gsl_interp_accel *n1b_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *n1b_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    
    gsl_interp_accel *n1f_accel_ptr= gsl_interp_accel_alloc ();;
    gsl_spline *n1f_spline_ptr = gsl_spline_alloc (gsl_interp_cspline, N_den_tab);
    
    
    
    public:
    double T[N_h_tab], g[N_h_tab], h[N_h_tab], x[N_den_tab],
    nb[N_den_tab], nf[N_den_tab], rb[N_den_tab], rf[N_den_tab], n1b[N_den_tab], n1f[N_den_tab];
    double Tmin, Tmax, xmin, xmax,n1b_min,n1f_min;
    


    Cosmo(){    
        get_data(this->T,this->g,this->h,
        this->x,this->nb,this->nf,this->rb,this->rf,this->n1b,this->n1f);
        gsl_spline_init (h_spline_ptr, T, h, N_h_tab);
        gsl_spline_init (g_spline_ptr, T, g, N_h_tab);


        gsl_spline_init (nb_spline_ptr, x, nb, N_den_tab);
        gsl_spline_init (nf_spline_ptr, x, nf, N_den_tab);
        gsl_spline_init (rb_spline_ptr, x, rb, N_den_tab);
        gsl_spline_init (rf_spline_ptr, x, rf, N_den_tab);
        gsl_spline_init (n1b_spline_ptr, x, n1b, N_den_tab);
        gsl_spline_init (n1f_spline_ptr, x, n1f, N_den_tab);
        
        this->Tmin=this->T[0];
        this->Tmax=this->T[N_h_tab-1];    
        this->xmin=this->x[0];
        this->xmax=this->x[N_den_tab-1];   
        this->n1b_min=this->n1b[0];
        this->n1f_min=this->n1f[0];

    };
    ~Cosmo(){};

    double heff(double T){
        double tmpT=T;

        if (T>this->Tmax)
        {
            tmpT=this->Tmax;
            
        }
        if (T<this->Tmin)
        {
            tmpT=this->Tmin;
        }
        return gsl_spline_eval(this->h_spline_ptr, tmpT, this->h_accel_ptr);
    }

    double geff(double T){
        double tmpT=T;

        if (T>this->Tmax)
        {
            tmpT=this->Tmax;
            
        }
        if (T<this->Tmin)
        {
            tmpT=this->Tmin;
        }
        return gsl_spline_eval(this->g_spline_ptr, tmpT, this->g_accel_ptr);
    }
    
    double dh(double T)
    {
        double tmpT=T;

        if (T>this->Tmax)
        {
            tmpT=this->Tmax;
            
        }
        if (T<this->Tmin)
        {
            tmpT=this->Tmin;
        }

        return 1+ 1/3. * tmpT/ this->heff(T) *gsl_spline_eval_deriv(h_spline_ptr, tmpT, h_accel_ptr);
    }
    // Densities start here
    double n_bose(double x, double m)
    {

        if (x>this->xmax)
        {
            return pow(m*m/(2*x*M_PI) ,1.5 )  * exp(-x);
            
        }
        if (x<this->xmin)
        {
            return 1.20206/(M_PI*M_PI)*pow( m/x,3.);
        }

        return gsl_spline_eval(this->nb_spline_ptr, x, this->nb_accel_ptr)*m*m*m;
    }

    double n_fermi(double x, double m)
    {

        if (x>this->xmax)
        {
            return pow(m*m/(2*x*M_PI) ,1.5 )  * exp(-x);
            
        }
        if (x<this->xmin)
        {
            return 3/4.*1.20206/(M_PI*M_PI)*pow( m/x,3.);
        }

        return gsl_spline_eval(this->nf_spline_ptr, x, this->nf_accel_ptr)*m*m*m;
    }

    double rho_bose(double x, double m)
    {

        if (x>this->xmax)
        {
            return m*this->n_bose(x,m);
            
        }
        if (x<this->xmin)
        {
            return (M_PI*M_PI)/30*pow( m/x,4.);
        }

        return gsl_spline_eval(this->rb_spline_ptr, x, this->rb_accel_ptr)*m*m*m*m;
    }

    double rho_fermi(double x, double m)
    {

        if (x>this->xmax)
        {
            return m*this->n_fermi(x,m);
            
        }
        if (x<this->xmin)
        {
            return 7/8.*(M_PI*M_PI)/30*pow( m/x,4.);
        }

        return gsl_spline_eval(this->rf_spline_ptr, x, this->rf_accel_ptr)*m*m*m*m;
    }

    double n1_bose(double x, double m)
    {

        if (x>this->xmax)
        {
            return this->n_bose(x,m)/m*m*m;
            
        }
        if (x<this->xmin)
        {
            return (xmin/x)*(xmin/x)*n1b_min*m*m;
        }

        return gsl_spline_eval(this->n1b_spline_ptr, x, this->n1b_accel_ptr)*m*m;
    }

    double n1_fermi(double x, double m)
    {

        if (x>this->xmax)
        {
            return this->n_fermi(x,m)/m*m*m;
            
        }
        if (x<this->xmin)
        {
            return (xmin/x)*(xmin/x)*n1f_min*m*m;
        }

        return gsl_spline_eval(this->n1f_spline_ptr, x, this->n1f_accel_ptr)*m*m;
    }

};



static Cosmo _cosmo;

double heff(double T){
    return _cosmo.heff(T);
}

double geff(double T){
    return _cosmo.geff(T);
}

double dh(double T){
    return _cosmo.dh(T);
}

double s(double T){
    //s=\dfrac{2\pi^2}{45} h_{eff} T^3.
    return (2*M_PI*M_PI)/(45.)*heff(T)*pow(T,3.);
}

double rhoR(double T){
    //\rho_R=\dfrac{\pi^2}{30} g_{eff} T^4
    return M_PI*M_PI/30.*geff(T)*pow(T,4) ;
}


double Hubble(double T){
    //H=\sqrt{ \dfrac{8\pi}{3 M_p^2} \rho_R(T) }
    return pow(8*M_PI/3. *rhoR(T) ,0.5 )/Mp ;
}


double n_bose(double x, double m){
    return _cosmo.n_bose(x,m);
}
double n_fermi(double x, double m){
    return _cosmo.n_fermi(x,m);
}
double rho_bose(double x, double m){
    return _cosmo.rho_bose(x,m);
}
double rho_fermi(double x, double m){
    return _cosmo.rho_fermi(x,m);
}
double n1_bose(double x, double m){
    return _cosmo.n1_bose(x,m);
}
double n1_fermi(double x, double m){
    return _cosmo.n1_fermi(x,m);
}





#endif