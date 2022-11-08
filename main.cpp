#include <iostream>


using namespace std;

#define LIMIT 10000000
int phi[LIMIT+1];

void init()
{
    phi[1] = 1;
    int n, p, f, i;
    for(i = 2; i*i <= LIMIT; i++){
        p = phi[i];
        if(!p){//prime
            phi[i] = i-1;
            for(int j = i*i; j <= LIMIT; j+= i){
                phi[j] = i;
            }
        }else{//p is a prime factor
            n = i/p;            
            f = p;
            while(n%f == 0){
                f*=p;
            }
            n = i/f;
            f = (f/p)*(p-1);
            phi[i] = f*phi[n];
        }
    }
    
    //every prime is marked
    for(; i <= LIMIT; i++){
        p = phi[i];
        if(!p){//prime
            phi[i] = i-1;
        }else{//p is a prime factor
            n = i/p;            
            f = p;
            while(n%f == 0){
                f*=p;
            }
            n = i/f;
            f = (f/p)*(p-1);
            phi[i] = f*phi[n];
        }
    }
}

int digcount[10];
int digitsignature(int n){
    int signature = 0;
    while(n>9){
        digcount[n%10]++;
        n/=10;
    }
    digcount[n]++;
    for(int i = 9; i >= 0; i--){
        int c = digcount[i];
        if(c){
            while (c--){
                signature = 10*signature + i;
            }            
            digcount[i] = 0; //reset for reuse
        }
    }

    return signature;
}

int main()
{
    init();
    int nmin = 1;
    double ratiomin = 1e100, r;
    int sig1, sig2, phint;
    for(int i = 2; i < LIMIT; i++){
        phint = phi[i];
        sig1 = digitsignature(i);
        sig2 = digitsignature(phint);
        if(sig1 == sig2){
            r = i; //cast
            r/=phint; //double division
            if(r < ratiomin){
                nmin = i;
                ratiomin = r;
            }
        }
    }

    cout << nmin << endl;

}