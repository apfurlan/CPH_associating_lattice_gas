#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

//====== MERSENNE TWISTER generator ===================
#define NN 624
#define MM 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[NN]; /* the array for the state vector  */
static int mti=NN+1; /* mti==N+1 means mt[N] is not initialized */

void init_genrand(unsigned long s) ;
unsigned long genrand_int32(void)  ;
double genrand_real2(void)         ; 
//=====================================================

#define _USE_MATH_DEFINES

void nnlist  (int L, int N  , int ndim,  int ncoord , int nn[]) ; 
void readDOS (int L, float rho, int rep, int count, double lnf , double lng[]) ; 
void evalsubL(int L, int N  , int NsubL, int NspsubL, int subL[]);

using namespace std; 

int main(int argc, char* argv[]){
  
  double temp = 0.70 ; //atoi(argv[1]) ;
  
  int rep = atoi(argv[1]) ;  
  unsigned long int seed = atoi(argv[2]) ; 
 
  const int L           = 64;      // system-size
  
  const int ndim        = 2    ;   // number of dimensions
  const int N           = L*L  ;   // number of sites
  const int ncoord      = 6    ;   // coordination number
  const int Q           = 3    ;   // number of states Q = 0 = empty !
  const int NsubL       = 4    ;   // number of sublattices
  const int NspsubL     = N/NsubL; // number of sites per sublattice
  
  const int mcterm      = 1000000 ;  
  const int mcsteps     = 500000  ;
  const int measure     = 1       ;  

  const int Nmeas       = mcsteps/measure ; 
  const int mctotal     = mcterm + mcsteps ; 

  const double mu0      = -1.680   ;
  const double muf      = -1.560   ;
  const double dmu      = .001     ;
  
  static int s[N]              ;  // site state
  static int nn[ncoord*N]      ;  // nearest-neighbor list
  static int tau[(Q+1)*ncoord] ;  // arm variables
  static int jtau[ncoord]      ;  // nearest-neighbor arm list

  int i1,i2    ;   // sites to be changed 
  int onnEn, nnnEn   ;  // old,new NN energy at site i
  int newstate, oldstate ; 
  int tauitauj ;
  int nnsum,iEn    ;
  int iso,isn,js   ;
  int np,count ; 

  int npoints = int((muf-mu0)/dmu) + 1 ;

  //cout << npoints << endl ; 
  //return 0 ;

  //int Nparts[npoints][Nmeas] ;
  //long int ProbNp[npoints][N] ;
  //int Nparts[npoints][mcsteps] ;
  //int **Nparts ;
  
  int **Nparts  = new int *[npoints];
  int **Energy  = new int *[npoints];
  int **Spheat  = new int *[npoints];
  //int **Optheta = new int *[npoints];
  //int **Opphi   = new int *[npoints];
  for (int i = 0; i < npoints; i++){
    Nparts[i] = new int [mcsteps];
    Energy[i] = new int [mcsteps] ; 
  }
  
  //int **ProbNp = new int *[npoints];
  // for (int i = 0; i < npoints; i++)
  //  Nparts[i] = new int [Nmeas];
  
  long int ProbNp[npoints][N] ;

  double imu[npoints] ; 
  
  //ofstream outfile1,outfile2 ;
  
      
  // ======= DEFINING STATES - SETING ARM VALUES  =======================
  // vaccum 
  tau[0]=tau[1]=tau[2]=tau[3]=tau[4]=tau[5]=0;

  // state 1 
  tau[6]=0  ;
  tau[7]=1  ;
  tau[8]=1  ;
  tau[9]=0  ;
  tau[10]=1 ;
  tau[11]=1 ; 

  // state 2 
  tau[12]=1 ; 
  tau[13]=0 ;
  tau[14]=1 ;
  tau[15]=1 ;
  tau[16]=0 ; 
  tau[17]=1 ; 

  // state 3 
  tau[18]=1 ;
  tau[19]=1 ;
  tau[20]=0 ;
  tau[21]=1 ;
  tau[22]=1 ;
  tau[23]=0 ;
  //=================================================================
  //lista dos bracos do vizinho j com os quais cada braco do i interage
  int nc2 = ncoord/2 ; 
  for(int i=0; i<ncoord; i++)
    jtau[i] = i+nc2*pow(-1.,(int)((float)(i))/nc2);


  nnlist(L,N,ndim,ncoord,nn) ; 

  cout << "#   count     mu         temp " << endl ; 
  cout << "#--------------------------------" << endl ; 
  
  
  //unsigned long seed = (rep+1)*time(NULL) ;
  init_genrand(seed) ; 

  //count = 0 ;
  double mu = mu0 ;
  for(count=0; count < npoints; count++){

  //while(mu < muf){
  //cout << count <<  "  " << npoints << endl ; 
    for(int i = 0; i < N; i++) s[i] = int((Q+1)*genrand_real2()) ;
    
    np = 0 ;
    for(int i=0; i<N; i++) if(s[i] > 0) np++ ; 
    
    for(int mc=0; mc<mctotal; mc++){

      iEn = 0 ; 
      for(int k=0; k<N; k++){

	i1 = int(N*genrand_real2()) ;
	
	iso=ceil(float(s[i1])/Q) ;
	  
	onnEn = 0 ;
	if(s[i1] > 0){
	  
	  nnsum = 0 ;
	  	  
	  for(int j=0; j<ncoord; j++){
	    int index = i1*ncoord+j ;
	    
	    tauitauj = tau[ s[i1]*ncoord + j ] *
	      tau[ s[nn[index]]*ncoord + jtau[j] ] ;
	    
	    js=ceil(float(s[nn[index]])/Q);
	    nnsum+=js*(1-2*tauitauj);
	  }
	  onnEn=iso*nnsum;
	}
			
	int oldstate = s[i1] ; newstate = oldstate ;
	while(oldstate == newstate){
	  newstate = int((Q+1)*genrand_real2()) ;
	}
	
	nnnEn = 0 ;
	isn = int(ceil(float(newstate)/Q)) ;

	if(newstate  > 0){

	  nnsum = 0 ;
	  
	  for(int j=0; j<ncoord; j++){
	    tauitauj = tau[ newstate*ncoord + j ] *
	      tau[ s[nn[i1*ncoord+j]]*ncoord + jtau[j]] ;
	  
	    js=ceil(float(s[nn[i1*ncoord+j]])/Q);
	    nnsum+=js*(1-2*tauitauj);	     
	  }
	  nnnEn = isn*nnsum ; 
	}


	//iEn += min(nnnEn,onnEn) ; 
	
	double dE = nnnEn - onnEn -(isn - iso)*mu ; 
	double Bf = exp(-abs(dE)/(1.*temp)) ; 
	
	if(dE < 0 || Bf > genrand_real2()) {
	  
	  s[i1] = newstate ;
	  np += isn-iso ; 
	  //iEn += nnnEn 
	  //if(isn==1 && iso==0) np++ ; 
	  //else if(isn==0 && iso==1) np-- ; 
	}
      }

      //if(mc >= mcterm && (mc % measure) == 0) {
      if(mc >= mcterm && count < npoints) {
	int index  = mc-mcterm ;
	//cout << count << "  " << index << endl ; 
	//Nparts[count][int((mc-mcterm)/measure)] =  np ;
	Nparts[count][index] =  np ;
	Energy[count][index] =  iEn ; 
	ProbNp[count][np]++ ; 
      }

    }

    cout << fixed ; 
    cout << "    " << setw(3) << count
	 << "    " <<  setprecision(5) << setw(8) << mu
	 << "    " <<  setprecision(6) << temp << endl ; 
    
    //imu[count] = mu ;
    
    mu = mu0+ count*dmu ; 
    //count++ ; 
    //if(count < npoints) count++ ; 
    
  }
  
  stringstream stream ; 
  stream << "" ; 
  stream << fixed << setprecision(2) << temp ; 

  stringstream filename ;
  filename << "" ; 
  filename << "gasldl_L" << L << "_temp" << stream.str() << "_rep" << rep << ".dat" ; 
  
  ofstream outfile1(filename.str().c_str()) ; 

  outfile1  << "#count   mu           <En>        fluEn       <rho>     flurho       <En2>          fluEn2           <EnN>         fluEnN          <N2>           fluN2" << endl ;

  outfile1 << "#" ;
  for(int i=0;i<160 ;i++) outfile1 << "-" ; 
  outfile1  << endl ; 
  
  double avgrho = 0 ;
  double avgEn  = 0 ;
  double avgEn2 = 0 ;
  double avgEnN = 0 ;
  double avgN2  = 0 ;
  double stdrho = 0 ;
  double stdEn  = 0 ;
  double stdEn2 = 0 ;
  double stdEnN = 0 ;
  double stdN2  = 0 ; 
  for(int i=0; i<npoints; i++){
    avgrho=0 ;
    avgEn =0 ;
    avgEn2=0 ;
    avgEnN=0 ;
    avgN2 =0 ;
    for(int j=0; j<Nmeas; j++){
      avgrho += Nparts[i][j]/(1.*N) ;
      avgEn  += Energy[i][j] ;
      avgEn2 += Energy[i][j]*Energy[i][j] ;
      avgEnN += Nparts[i][j]*Energy[i][j] ;
      avgN2  += Nparts[i][j]*Nparts[i][j] ;
    }
    avgrho /= Nmeas ; 
    avgEn  /= Nmeas ; 
    avgEn2 /= Nmeas ; 
    avgEnN /= Nmeas ; 
    avgN2  /= Nmeas ; 
    
    stdrho = 0 ;
    stdEn  = 0 ;
    stdEn2 = 0 ;
    stdEnN = 0 ;
    stdN2  = 0 ; 

    for(int j=0; j<Nmeas; j++){
      stdrho += (Nparts[i][j]/(1.*N)-avgrho)*(Nparts[i][j]/(1.*N)-avgrho) ;
      stdEn  += (Energy[i][j] - avgEn)*(Energy[i][j] - avgEn) ; 
      stdEn2 += (Energy[i][j]*Energy[i][j] - avgEn2)*
	(Energy[i][j]*Energy[i][j] - avgEn2) ;

      stdEnN += (Nparts[i][j]*Energy[i][j] - avgEnN)*
	(Nparts[i][j]*Energy[i][j] - avgEnN) ; 

      
      stdN2 += (Nparts[i][j]*Nparts[i][j] - avgN2)*
	(Nparts[i][j]*Nparts[i][j] - avgN2) ;


    }
    stdrho = sqrt((stdrho/(1.*Nmeas)));
    stdEn  = sqrt((stdEn /(1.*Nmeas)));
    stdEn2 = sqrt((stdEn2/(1.*Nmeas)));
    stdEnN = sqrt((stdEnN/(1.*Nmeas))) ;
    stdN2  = sqrt((stdN2 /(1.*Nmeas))) ;
    
    outfile1 << "  " << i << fixed << setprecision(10) << "   " << mu0+i*dmu << "   "
	     << avgEn  << "   " << stdEn  << "   " 
    	     << avgrho << "   " << stdrho << "   "
	     << avgEn2 << "   " << stdEn2 << "   "
	     << avgEnN << "   " << stdEnN << "   "
	     << avgN2  << "   " << stdEn2 << endl ; 
  }
  
  outfile1.close();


  for(int i=0; i<npoints; i++){

    stringstream stream2 ; 
    stream2 << fixed << setprecision(4) << mu0 + i*dmu ; 

    cout << stream.str() << "  " << stream2.str() << endl ; 
    
    stringstream filename2 ; 
    filename2 << "histnp_L" << L  << "_temp" << stream.str() << 
      "_mu" << stream2.str() << ".dat" ;


    ofstream outfile2(filename2.str().c_str()) ;
   
    //cout << outname << endl ; 
    
    //avgrho = 0. ;
    //for(int j=0; j<Nmeas; j++) avgrho += Nparts[i][j] ;  
    
    
    //outfile2.open(outname) ;

    for(int j=0; j<N; j++){
      outfile2 << j << "  " << j/(1.*N)
	       << "  " << double(ProbNp[i][j]) << endl ;
    }
  
    outfile2.close() ;
  }
  
  
  return 0 ; 
}

void evalsubL(int L,int N, int NsubL, int NspsubL, int subL[]){
  ofstream file1;  
  int i,j,line,site,s1,s2,s3,s4;
    
  s1=0; s2=0; s3=0; s4=0;
  //for(j=0;j<NsubL;j++){
  for(i=0; i<N; i++){
    
    line=i/L;
    site=i%L;
    
    if((line % 2) == 0){
      if((site % 2) == 0){
	subL[s1]=i;
	s1++;
      }else{
	subL[1*NspsubL+s2]=i;
	s2++;
      }
    }else{
      if((site % 2) == 0){
	subL[2*NspsubL+s3]=i;
	s3++;
      }else{
	subL[3*NspsubL+s4]=i;
	s4++;
      }
    }
  }


  
  return ;
}
  

void nnlist(int L, int N, int ndim, int ncoord, int nn[]){

  
 if(ndim == 2 ){

    if(ncoord == 4){

      for(int i=0; i< N; i++){

        nn[i*ncoord + 0] = (i+1) % L == 0 ? i-L+1 : i+1;
        nn[i*ncoord + 1] = (i < L) ? (N-L)+i : i-L;
	nn[i*ncoord + 2] = ((i % L) == 0 || i == 0) ? i+L-1 : i-1;
	nn[i*ncoord + 3] = (i >= (N-L)) ? i-(N-L) : i+L;

      }	
    }else if(ncoord == 6) {  
  
      for(int i=0; i<N; i++){

	nn[i*ncoord+0] = i+1 ;
	nn[i*ncoord+1] = i-L+1;
	nn[i*ncoord+2] = i-L;
	nn[i*ncoord+3] = i-1;
	nn[i*ncoord+4] = i+L-1;
	nn[i*ncoord+5] = i+L ;
	
	if( nn[i*ncoord+1] <  0   ) nn[i*ncoord+1]=nn[i*ncoord+1] + N;
	if( nn[i*ncoord+2] <  0   ) nn[i*ncoord+2]=nn[i*ncoord+2] + N;
	if( nn[i*ncoord+4] >= N ) nn[i*ncoord+4]=nn[i*ncoord+4] - N;
	if( nn[i*ncoord+5] >= N ) nn[i*ncoord+5]=nn[i*ncoord+5] - N;
	
	int imod=(i+1) % L;
	if(imod == 0){
	  nn[i*ncoord+0]=nn[i*ncoord+0]-L;
	  nn[i*ncoord+1]=nn[i*ncoord+1]-L;
	  if(i == L-1)nn[i*ncoord+1]=nn[i*ncoord+1] + N;
	}
	if(i % L == 0){
	  nn[i*ncoord+3] = i+L-1;
	  nn[i*ncoord+4] = nn[i*ncoord+4]+L;
	  if(i >= N -L) nn[i*ncoord+4]=nn[i*ncoord+4] - N;
	}
      }
    }
 }

 return ; 
}


/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<NN; mti++) {
        mt[mti] =
      (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}


/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
 {
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= NN) { /* generate N words at one time */
        int kk;

        if (mti == NN+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<NN-MM;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+MM] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<NN-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(MM-NN)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[NN-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[NN-1] = mt[MM-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0);
    /* divided by 2^32 */
}
