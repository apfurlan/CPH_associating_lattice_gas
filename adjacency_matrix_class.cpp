class adjacency_matrix()





    // Metods
	generate(int L, int N, int ndim, int ncoord, int nn[]){

		if(ndim == 2 ){

    		if(ncoord == 4){

      			for(int i=0; i< N; i++){

					nn[i*ncoord + 0] = (i+1) % L == 0 ? i-L+1 : i+1;
					nn[i*ncoord + 1] = (i < L) ? (N-L)+i : i-L;
					nn[i*ncoord + 2] = ((i % L) == 0 || i == 0) ? i+L-1 : i-1;
					nn[i*ncoord + 3] = (i >= (N-L)) ? i-(N-L) : i+L;
				
				}
				

    		} else if(ncoord == 6) {  
  
      			for(int i=0; i<N; i++){

					nn[i*ncoord + 0] = i+1   ;
					nn[i*ncoord + 1] = i-L+1 ;
					nn[i*ncoord + 2] = i-L   ;
					nn[i*ncoord + 3] = i-1   ;
					nn[i*ncoord + 4] = i+L-1 ;
					nn[i*ncoord + 5] = i+L   ;
	
					if( nn[i*ncoord + 1] <  0   ) nn[i*ncoord + 1] = nn[i*ncoord + 1] + N;
					if( nn[i*ncoord + 2] <  0   ) nn[i*ncoord + 2] = nn[i*ncoord + 2] + N;
					if( nn[i*ncoord + 4] >= N ) nn[i*ncoord + 4] = nn[i*ncoord + 4] - N;
					if( nn[i*ncoord + 5] >= N ) nn[i*ncoord + 5] = nn[i*ncoord + 5] - N;
	
					int imod=(i+1) % L;
					if(imod == 0){
	  					nn[i*ncoord + 0] = nn[i*ncoord + 0]-L;
	  					nn[i*ncoord + 1] = nn[i*ncoord + 1]-L;
	  					if(i == L-1)nn[i*ncoord + 1]=nn[i*ncoord + 1] + N;
					}
					if(i % L == 0){
						nn[i*ncoord + 3] = i+L-1;
						nn[i*ncoord + 4] = nn[i*ncoord + 4]+L;
						if(i >= N -L) nn[i*ncoord + 4]=nn[i*ncoord + 4] - N;
					}
      			}
    		}
 		}

		return nn ; 
	
		get_nn_states // retorna uma lista com os estados




	}

    get_nn_states






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

