package life_game;

import java.util.Random;

public class Process_Cell{
	
	void init_1(boolean flag[][],int size) {
		for(int i=1;i<=size;i++) {
	    	Random r=new Random();
	    	int x=r.nextInt(19);
	    	int y=r.nextInt(19);
	    	flag[x][y]=true;
    	
	    }
	}
	
	void init_2(boolean flag[][],int size) {
		for(int i=0;i<size;i++) {
	    	flag[size/2][i]=true;
    	
	    }
		for(int i=0;i<size;i++) {
	    	flag[i][size/2]=true;
    	
	    }
		
	}
	
	void init_3(boolean flag[][],int size) {
		for(int i=0;i<2;i++) {
			for(int j=0;j<2;j++) {
				flag[i][j]=true;
				flag[size-2+i][j]=true;
				flag[i][size-2+j]=true;
				flag[size-2+i][size-2+j]=true;			
			}    	    	
	    }	
	}
	public void Process(boolean a[][],int size) {
		int x[]= {-1,0,1};
		int y[]= {-1,0,1};
		boolean copy[][]=new boolean[size][size];
		for(int i=0;i<size;i++) {
			for(int j=0;j<size;j++) {
				copy[i][j]=a[i][j];
			}
		}
		for(int i=0;i<20;i++) {
			for(int j=0;j<20;j++) {
				int countn=0;
				for(int k=0;k<3;k++) {
					for(int l=0;l<3;l++) {
						if(x[k]==0&&y[l]==0) continue;
						if(i+x[k]>=0&&i+x[k]<20&&j+y[k]>=0&&j+y[k]<20) {
							if(copy[i+x[k]][j+y[k]]) countn++;
						}
					}
				}
				if(copy[i][j]) {
					if(countn<2||countn>3) a[i][j]=false;
				}
				else {
					if(countn==3) a[i][j]=true;
				}
				
			}
		}
	}
	
	 
}