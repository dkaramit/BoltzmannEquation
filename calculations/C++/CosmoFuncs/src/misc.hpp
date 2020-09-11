#ifndef include_Misc
#define include_Misc


namespace misc
{
    //-- Get a number (length) of log_10-spaced points from 10^min to 10^max. --//
    template<class LD>
    void logspace(LD min, LD max, int length, LD* X ){
        for(int i = 0; i<length ; ++i){
            X[i]= std::pow( 10, min + i*(max-min)/( length-1 ));
        }
    }

    //-- Get a number (length) of log_n-spaced points from n^min to n^max. --//
    template<class LD>
    void logspace(LD n ,LD min, LD max, int length, LD* X ){
        for(int i = 0; i<length ; ++i){
            X[i]= std::pow( n , min + i*(max-min)/( length-1 ));
        }
    }

    //-- Get a number (length) of linearly spaced points from min to max. --//
    template<class LD>
    void linspace(LD min, LD max, int length, LD* X ){
        for(int i = 0; i<length ; ++i){
            X[i]=  min + i*(max-min)/( length-1 ) ;
        }
    }

    template<class LD>
    void map(LD* X , LD(* func)(LD), int N_points, LD* Y ){
        for(int i = 0; i < N_points ; ++i){
            Y[i]=  func(X[i]) ;
        }
    }



}


#endif
