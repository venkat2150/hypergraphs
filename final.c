#include<stdio.h>
#define max 10
#define dmax 20
#define pwr 1024
void proc_bronk(int pg[][max], int p[], int r[], int x[]);
void un(int a[], int b[], int uni[]);
void minus(int a[], int b[], int m[]);
void neigh(int pg[][max], int a, int nei[]);
void inter(int a[], int b[], int inte[]);
int main()
{
	int n, c, nc, t[pwr][max], pg[max][max]={0};
	int p[max], r[max], x[max];
	
	for(int i=0; i<max; i++)
	{
		p[i]=99;
		r[i]=99;
		x[i]=99;
	}

	for(int i=0; i<pwr; i++)
	{
		for(int j=0; j<max; j++)
		{
			t[i][j]=99;
		}
	}

	printf("enter total no of nodes");
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		p[i]=i;
	}
	printf("enter no of hyperedges");
	scanf("%d",&c);
	for(int i=0; i<c; i++)
	{
		printf("enter no of nodes in the hyperedge %d\t", i+1);
		scanf("%d",&nc);
		for(int j=0; j<nc; j++)
		{
			printf("enter the node %d in the hyperedge %d\t", j+1, i+1);
			scanf("%d",&t[i][j]);/* the first row of t contains 1st clique, 2nd row contains 2nd clique and so on.*/
		}
	}
	/*for(int i=0; i<c; i++)
	{
		printf("\n");
		for(int j=0; j<max; j++)
		{
			printf("%d\t",t[i][j]);//printing the clique matrix
		}
	}
	printf("\n*********************************************************\n");*/
	for(int i=0; i<c; i++)
	{
		for(int j=0; j<max; j++)
		{
			for(int k=0; k<(max-j); k++)
			{
				if(t[i][j+k]!=99)
				{
					pg[t[i][j]][t[i][j+k]]=1;//creating the triangle which is on the top-right of the diagnol of the matrix
					pg[t[i][j+k]][t[i][j]]=1;//creating the triangle which is on the bottom-left of the diagnol of the matrix
				}
			}
		}
	}
	for(int i=0; i<n; i++)
	{
		pg[i][i]=0;
	}
	printf("\n");
	for(int i=0; i<n; i++)
	{
		printf("\t%d", i);
	}
	for(int i=0; i<n; i++)
	{
		printf("\n%d\t", i);
		for(int j=0; j<n; j++)
		{
			printf("%d\t", pg[i][j]);//printing the primal graph
		}
	}
	printf("\n***********************************************\n");	
	
	proc_bronk(pg, p, r, x);
	return 0;
}
//algorithm function
void proc_bronk(int pg[][max], int p[], int r[], int x[])
{
	
	int pux[max], non[max], nou[max], nov[max], pmnou[max], ruv[max], pinov[max], pmv[max], xinov[max], xuv[max];
	int temp, count=0, a, b, v, u, lar, vmat[max];
	for(int i=0; i<max; i++)
	{
		pux[i]=99;
		non[i]=-1;
		nou[i]=99;
		pmnou[i]=99;
		nov[i]=99;
		vmat[i]=99;
		ruv[i]=99;
		pinov[i]=99;
		pmv[i]=99;
		xinov[i]=99;
		xuv[i]=99;
	}
	// creating pux(p union x)
	un(p, x, pux);

	//checking weather pux(p union x) is empty or not
	for(int i=0; i<max; i++)
	{
		if(pux[i]!=99)
		{
			count++;
		}
	}
	//printf("%d", count);

	// printing r[i] if pux is empty
	if(count==0)
	{
		for(int i=0; i<max; i++)
		{
			if(r[i]!=99)
			{
				printf("%d", r[i]);
			}
		}
		printf("\n");
	}
	

	//creating non(no of neighbours) for nodes in pux
	count=0;
	for(int i=0; i<max; i++)
	{
		if(pux[i]!=99)
		{
			for(int j=0; j<max; j++)
			{
				if(pg[pux[i]][j]==1)
				{
					count++;
				}
			}
			non[pux[i]]=count;
			count=0;
		}
	}

	//selecting u from pux with largest no of elements
	lar=non[0];
	for(int i=1; i<max; i++)
	{
		if(non[i]>lar)
		{
			lar=non[i];
			u=i;
		}
	}
	//creating nou(neighbours of u)
	neigh(pg, u, nou);
	
	//creating pmnou(p minus neighbours of u)
	minus(p, nou, pmnou);
	
	//main for loop for reccurcive calling
	for(int i=0; i<max; i++)
	{
		if(pmnou[i]!=99)
		{
			v=pmnou[i];//creating vertex v

			neigh(pg, v, nov);//creating nov(neighbours of v)
			
			vmat[0]=v;//creating vmat with vetex v at the 0th place

			un(r, vmat, ruv);//creating ruv(r union v)
			
			inter(p, nov, pinov);//creating pinov(p intersect nov)
			
			inter(x, nov, xinov);//creating xinov(x intersect nov)
			
			proc_bronk(pg, pinov, ruv, xinov);//recurcive call

			minus(p, vmat, pmv);//creating pmv (p minus v)
			
			for(int j=0; j<max; j++)
			{
				p[j]=pmv[j];// p = pmv
			}

			un(x, vmat, xuv);//creating xuv(x union v)
			
			for(int j=0; j<max; j++)
			{
				x[j]=xuv[j];//x=xuv
			}

		}
	}

}
//union function
void un(int a[], int b[], int uni[])
{
	int u[dmax];
	int c;
	for(int i=0; i<dmax; i++)
	{
		u[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		u[i]=a[i];
		u[max+i]=b[i];
		uni[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		for(int j=0; j<max; j++)
		{	
			if(i!=j)
			{
				if(u[i]==u[j])
				{
					u[j]=99;
				}
				if(u[max+i]==u[max+j])
				{
					u[max+j]=99;
				}
			}
			if(u[i]==u[max+j])
			{
				u[max+j]=99;
			}
		}
	}
	c=0;
	for(int i=0; i<dmax; i++)
	{
		if(u[i]!=99)
		{
			uni[c]=u[i];
			c++;
		}
	}
}
//minus function
void minus(int a[], int b[], int m[])
{
	int u[dmax];
	for(int i=0; i<dmax; i++)
	{
		u[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		u[i]=a[i];
		u[max+i]=b[i];
		m[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		for(int j=0; j<max; j++)
		{	
			if(i!=j)
			{
				if(u[i]==u[j])
				{
					u[j]=99;
				}
				if(u[max+i]==u[max+j])
				{
					u[max+j]=99;
				}
			}
			if(u[i]==u[max+j])
			{
				u[i]=99;
			}
		}
		m[i]=u[i];
	}
}
// neighbour function
void neigh(int pg[][max], int a, int nei[])
{
	int b=0;
	
	for(int i=0; i<max; i++)
	{
		nei[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		if(pg[a][i]==1)
		{
			nei[b]=i;
			b++;
		}
	}
}
// intersection function
void inter(int a[], int b[], int inte[])
{
	int u[dmax], t[max];
	int c;
	for(int i=0; i<dmax; i++)
	{
		u[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		u[i]=a[i];
		u[max+i]=b[i];
		inte[i]=99;
		t[i]=99;
	}
	for(int i=0; i<max; i++)
	{
		for(int j=0; j<max; j++)
		{
			if(u[i]==u[max+j])
			{
				inte[i]=u[i];
			}
		}
	}
	for(int i=0; i<max; i++)
	{
		for(int j=1; j<(max-i); j++)
		{
			if(inte[i]!=99)
			{			
				if(inte[i]==inte[i+j])
				{
					inte[i+j]=99;
				}
			}
		}
	}
}


