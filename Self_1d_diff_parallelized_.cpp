//Program wa written by Swaroop Sampad Pradhan by Following the hands on session of MPI in parallelization of unsteady heat conduction solvers in 1d

#include<iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>   // value of PI is defined as M_PI
#include <mpi.h>   // header for MPI

int main( int argc, char **argv )
{
  int nglobe = 32;             // global number of nodes
  int np = 2;                   // number of processors
  int nloc = nglobe/np + 2;  // +2 are used to store ghost nodes
                                // communication happens on these nodes
  double dt = 0.0001;
  double dx = 1.0/(nglobe-1.0);
  double dxinv2 = 1.0/dx/dx;

  // each processor holds only the local data
  double xx[nloc], uold[nloc], unew[nloc];
  double g[nloc], f[nloc];

  // MPI related stuff
  MPI_Init(&argc, &argv);
  int procsize; // number of processors
  MPI_Comm_size(MPI_COMM_WORLD, &procsize);
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // storing the starting and end points of local indices
  int ibegin = my_rank * (nloc-2);
  int iend = ibegin + nloc - 1;

  // iloc --> local index
  // iglo --> global index
  int iglo = 0;
  for( int iloc=0; iloc < nloc; iloc++ )
  {
    iglo = iloc + ibegin;
    xx[iloc] = (iglo-1)*dx;
    uold[iloc] = 0.0;
    unew[iloc] = 0.0;

    g[iloc] = M_PI*M_PI*sin(M_PI*xx[iloc]);
  }

 

// write convergence history in a outfile
  std::ofstream outconv;
  if( my_rank ==0 )
    outconv.open("convergence-par.txt");

  double norm_loc  = 100.0;
  double norm_glo = 0.0;
  bool converged = false;
  int itercount = 0;
  while( not converged )
  {
    itercount++;

    for( int iloc=1; iloc<nloc-1; iloc++ )
    {
      if( my_rank ==0 and iloc == 1)
      {
        unew[iloc] = 0.0;
        continue;
      }
      if( my_rank == np-1 and iloc == nloc - 2 )
      {
        unew[iloc] = 0.0;
        continue;
      }
      f[iloc] = g[iloc] + dxinv2 * ( uold[iloc+1]-2.0*uold[iloc]+uold[iloc-1] );
      unew[iloc] = uold[iloc] + dt * f[iloc];
    }

    norm_loc  = 0.0;
    for( int iloc=1; iloc<nloc-1; iloc++ )
    {
      if( abs(f[iloc]) > norm_loc )
        norm_loc = abs(f[iloc]);
    }

    // compute max value of norm across all processors
    MPI_Allreduce(&norm_loc, &norm_glo, 1, MPI_DOUBLE, MPI_MAX,
               MPI_COMM_WORLD);



    if( my_rank == 0 )
    {
      outconv << itercount << " " << norm_glo << std::endl;
      std::cout << itercount << " " << norm_glo << std::endl;
    }

    if( norm_glo < 1e-6 )
    {
      converged = true;
    }

    // update the interior nodes
    for( int iloc=1; iloc<nloc-1; iloc++ )
    {
      uold[iloc] = unew[iloc];
    }

    // sending information to the left processor
    if( my_rank != 0)
    {
      MPI_Send(&unew[1], 1, MPI_DOUBLE, my_rank-1, my_rank, MPI_COMM_WORLD);
    }

    // receiving information from the right processor
    if( my_rank != np-1 )
    {
      MPI_Recv(&uold[nloc-1], 1, MPI_DOUBLE, my_rank+1, my_rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // sending information to the right
    if( my_rank != np-1)
    {
      MPI_Send(&unew[nloc-2], 1, MPI_DOUBLE, my_rank+1, my_rank, MPI_COMM_WORLD);
    }

    // receiving information from the left processor
    if( my_rank != 0 )
    {
      MPI_Recv(&uold[0], 1, MPI_DOUBLE, my_rank-1, my_rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }


  // Write output of result in a file
  std::stringstream sstm;
  sstm << "output_" << my_rank << ".txt";
  std::string file_local = sstm.str();
  std::ofstream outfile;
  outfile.open(file_local);
  double uexact;
  for( int iloc=1; iloc<nloc-1; iloc++ )
  {
    uexact = sin(M_PI*xx[iloc]);
    outfile << xx[iloc] << "\t" << unew[iloc] << "\t" << uexact << std::endl;
  }
  outfile.close();

  MPI_Finalize();
}
