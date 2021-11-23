#include <stdio.h>	
#include <math.h>
#include <stdlib.h>

void main(){
	int i,j;
	int t;
	int X = 200;
	int Y = X/2;
	double dt=0.1;
	double u[200][200];
	double utemp[200][200];

	double a =4.0; 
	double b =0.01;
	double d = 0.5;	
	double thr =0.255973849;
	
	int end =300;
	int div = end / 10;
	
	int ARange = 0;
	int Arange[100];

	FILE *fp1;
		fp1=fopen("Range.csv","w");
	FILE *fp2;
		fp2=fopen("Distribution.csv","w");

	//Initial condition
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			u[i][j]=  (exp(-((i-Y)*(i-Y)+(j-Y)*(j-Y))/1500));//single_InitialCondition
			
			//u[i][j]= exp(-((i-70)*(i-70)+(j-60)*(j-60))/750)+exp(-((i-150)*(i-150)+(j-80)*(j-80))/450)+exp(-((i-100)*(i-100)+(j-150)*(j-150))/450);	//multi_InitialCondition
			if(u[i][j] > thr)
				ARange++;
		}
	}
	//Initial condition range
	Arange[t / div] = ARange;
		fprintf(fp1, "%d\n" , Arange[t / div]);
	ARange = 0;

	//Initial condition output			
	for(i=0;i<X;i++){
		for(j=0;j<X;j++){
			fprintf(fp2,"%.4f",u[i][j]);
			if(j!=X-1){
				fprintf(fp2," ,");
			}
		}
		fprintf(fp2,"\n");
	}

	for(t=1;t<= end; t++){
		//Boundary condition	
		//i=0,j=0
		i=0;
		j=0;
			utemp[i][j]=u[i][j]+dt*(d*(u[X-1][j]+u[i+1][j]+u[i][X-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);

		//i=0,j=99
		i=0;
		j=X-1;
			utemp[i][j]=u[i][j]+dt*(d*(u[X-1][j] +u[i+1][j]+u[i][j-1]+u[i][0]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);

		// i=99,j=0
		i=X-1;
		j=0;
			utemp[i][j]=u[i][j]+dt*(d*(u[i-1][j] +u[0][j]+u[i][X-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);

		//i=99,j=99
		i=X-1;
		j=X-1;
			utemp[i][j]=u[i][j]+dt*(d*(u[i-1][j] +u[0][j]+u[i][j-1]+u[i][0]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);

		//i=0
		i=0;
		for(j=1;j<X-1;j++){
			utemp[i][j]=u[i][j]+dt*(d*(u[X-1][j]+u[i+1][j]+u[i][j-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);
		}

		//i=99
		i=X-1;
		for(j=1;j<X-1;j++){
			utemp[i][j]=u[i][j]+dt*(d*(u[i-1][j]+u[0][j]+u[i][j-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);
		}	

		//j=0	
		j=0;
		for(i=1;i<X-1;i++){
			utemp[i][j]=u[i][j]+dt*(d*(u[i-1][j]+u[i+1][j]+u[i][X-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);
		}

		//j=99
		j=X-1;
		for(i=1;i<X-1;i++){
			utemp[i][j]=u[i][j]+dt*(d*(u[i-1] [j]+u[i+1][j]+u[i][j-1]+u[i][0]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);
		}

		//Others
		for(i=1;i<X-1;i++){
			for(j=1;j<X-1;j++){
				utemp[i][j]=u[i][j]+dt*(d*(u[i-1][j] +u[i+1][j]+u[i][j-1]+u[i][j+1]-4*u[i][j])+a*u[i][j]*u[i][j]/(u[i][j]*u[i][j]+1)+b-u[i][j]);
			}
		}
			
		//Update
		for(i=0;i<X;i++){
			for(j=0;j<X;j++){
				u[i][j]=utemp[i][j];
			}
		}
		
	//}
	//output
		if(t % div == 0){
			for(i=0; i< X; i++){
				for(j=0;j<X;j++){	
						if(u[i][j] > thr)
						ARange++;
				}
			}
			Arange[t / div] = ARange;
			fprintf(fp1, "%d\n" , Arange[t / div]);
			ARange = 0;
		
			for(i=0;i<X;i++){
				for(j=0;j<X;j++){
					fprintf(fp2,"%.4f",u[i][j]);
					if(j!=X-1){
						fprintf(fp2," ,");
					}
				}
				fprintf(fp2,"\n");
			}
		}
	}
	//fclose(fp1);
	//fclose(fp2);
}