//CONVOLUTION
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
class conv
{
public:
    int y[10];
    void calculate(int m, int n, int *x, int *h);
    void display();
    conv()
    {
        for (int i = 0; i < 9; i++)
            y[i] = 0;
    }
};
void conv::calculate(int m, int n, int x[5], int h[5])
{
    int i, j;
    for (i = 0; i < m + n - 1; i++)
    {
        y[i] = 0;
        for (j = 0; j <= i; j++)
        {
            y[i] = y[i] + (x[j] * h[i - j]);
            //printf("\n%d",y[i]);
        }
    }
    //for(int k=0;k<9;k++)
    // printf("\n%d",y[k]);
    //for(int k=0;k<5;k++)
    // printf("\n%d",h[k]);
}
void conv::display()
{
    for (int i = 0; i < 9; i++)
printf("\n The Value of output y[%d]=
%d",i,y[i]);
}
int main()
{
    int input, rank, key = 0, rightSize = 5, leftSize = 5, found = 0;
    int right[10] = {1, 2, 3, 4, 5};
    int left[10] = {1, 2, 3, 4, 5};
    int flag = 0;
    char check;
    MPI::Status status;
    conv c;
    MPI::Init();
    rank = MPI::COMM_WORLD.Get_rank();
    if (rank == 0)
    {
        //MPI::COMM_WORLD.Recv(&rightSize, 1, MPI_INT, 1, 100,
status);
printf("receving from 1");
MPI::COMM_WORLD.Recv(&right, rightSize, MPI_INT, 1, 101,
                     status);
//MPI::COMM_WORLD.Recv(&leftSize, 1, MPI_INT,2, 200,
status);
printf("receving from 2");
MPI::COMM_WORLD.Recv(&left, leftSize, MPI_INT, 2, 201,
                     status);
c.calculate(5, 5, right, left);
for (int i = 0; i < 9; i++)
    printf("\n The Value of output y[%d]=%d", i, c.y[i]);
    }
    //MPI::COMM_WORLD.Barrier();
    //Right Side of the tree
    if (rank == 1)
    {
        printf("sending from 1");
        //MPI::COMM_WORLD.Recv(&rightSize, 1, MPI_INT, 0, 100,
status);
//MPI::COMM_WORLD.Recv(&right, rightSize, MPI_INT, 0, 101,
status);
//right[]={1,2,3,4,5};
//for(int i=0;i<10;i++)
//{
// right[i]=i*2;
//}
//MPI::COMM_WORLD.Send(&rightSize,1,MPI::INT,0,100);
MPI::COMM_WORLD.Send(&right, rightSize, MPI::INT, 0, 101);
/*std::cout<<"\n\nRight Side (Processor "<<rank<<")\n";
for(int i=0;i<rightSize;i++)
{
std::cout<<right[i]<<"\n";
}*/
    }
    //Left Side of the tree
    if (rank == 2)
    {
        printf("sending from 2");
        //for(int i=0;i<10;i++)
        //{
        // left[i]=i*4;
        //}
        //left[5]={1,2,3,4,5};
        //MPI::COMM_WORLD.Send(&leftSize,1,MPI::INT,0,200);
        MPI::COMM_WORLD.Send(&left, leftSize, MPI::INT, 0, 201);
        /*std::cout<<"\n\nRight Side (Processor "<<rank<<")\n";
for(int i=0;i<rightSize;i++)
{
std::cout<<right[i]<<"\n";
}*/
    }
    MPI::Finalize();
    return 0;
}