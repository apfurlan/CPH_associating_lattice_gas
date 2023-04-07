class sublattice()

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