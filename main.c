#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "Lab4_IO.h"
#include "timer.h"

int page_rank();

int page_rank() {
  struct node *nodehead;
    int nodecount;
    double *r, *r_pre, *contribution;
    int i, j;
    double damp_const;
    int iterationcount = 0;
    int collected_nodecount;
    double *collected_r;
    double cst_addapted_threshold;
    double error;
    FILE *fp, *ip;

    // Load the data and simple verification
    if ((ip = fopen("data_input_meta","r")) == NULL) {
        printf("Error opening the data_input_meta file.\n");
        return 254;
    }
    fscanf(ip, "%d\n", &nodecount);
    if (nodecount != collected_nodecount){
        printf("Problem size does not match!\n");
        return 2;
    }
    fclose(ip);
    collected_r = malloc(collected_nodecount * sizeof(double));
    for ( i = 0; i < collected_nodecount; ++i)
        fscanf(fp, "%lf\n", &collected_r[i]);
    fclose(fp);

    // Adjust the threshold according to the problem size
    cst_addapted_threshold = THRESHOLD;

    if (node_init(&nodehead, 0, nodecount)) return 254;
    // initialize variables
    r = malloc(nodecount * sizeof(double));
    r_pre = malloc(nodecount * sizeof(double));
    for ( i = 0; i < nodecount; ++i)
        r[i] = 1.0 / nodecount;
    contribution = malloc(nodecount * sizeof(double));
    for ( i = 0; i < nodecount; ++i)
        contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
    damp_const = (1.0 - DAMPING_FACTOR) / nodecount;

    // CORE CALCULATION
    GET_TIME(start);
    do{
        ++iterationcount;
        vec_cp(r, r_pre, nodecount);
        // update the value
        for ( i = 0; i < nodecount; ++i){
            r[i] = 0;
            for ( j = 0; j < nodehead[i].num_in_links; ++j)
                r[i] += contribution[nodehead[i].inlinks[j]];
            r[i] += damp_const;
        }
        // update and broadcast the contribution
        for ( i=0; i<nodecount; ++i){
            contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
        }
    }while(rel_error(r, r_pre, nodecount) >= EPSILON);
    GET_TIME(end);
    printf("Program converged at %d th iteration.\nElapsed time %f.\n", iterationcount, end-start);

    Lab4_saveoutput(r), nodecout, end-start);

    // post processing
    node_destroy(nodehead, nodecount);
    free(contribution);

    free(r); free(r_pre); free(collected_r);
}



/*
Main function

*/
int main(int argc, char* argv[])
{
  int num_threads;

  if (argc != 1) {
    printf("Usage: main <number_of_threads>\n");
    return(1);
  }

  page_rank();


  return(0);
}
