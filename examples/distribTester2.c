//
// Created by cigla on 12. 10. 2024
#include "distribTester2.h"
#include "distribFunction.h"
#include "osqp.h"
#include <stdio.h>
#include <time.h>
int main(void) {

    OSQPSolver *solver = NULL;
    OSQPSettings settings_data;
    OSQPSettings *settings = &settings_data;
    OSQPCscMatrix P_mat, A_mat;
    OSQPCscMatrix *P = &P_mat;
    OSQPCscMatrix *A = &A_mat;

    printf("n1\n");
    OSQPFloat P_x[0] = {};
    OSQPInt P_i[0] = {};
    OSQPInt P_p[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    OSQPInt P_nnz = 0;


    // My definition of problem hahahahahahahaha
    OSQPInt A_nnz = 108; // Number of non-zero elements in matrix A

    OSQPInt m = 40;
    OSQPInt n = 20;
    OSQPFloat A_data[108] = {
        1.000000, -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 100.000000, -100.000000, 1.000000, -1.000000,
        1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 100.000000, -100.000000, 1.000000, -1.000000,
        1.000000, -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 100.000000, -100.000000, 1.000000, -1.000000,
        1.000000, -1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 100.000000, -100.000000, 1.000000, -1.000000,
        1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000,
        -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000,
        -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000,
        1.000000, -1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000,
        -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000,
        1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000,
        -1.000000, -1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, -1.000000
    };
    OSQPInt A_row_indices[108] = {
        0, 1, 28, 29, 30, 31, 36, 37, 38, 39, 2, 3, 28, 29, 30, 31, 36, 37, 38, 39, 4, 5, 28, 29, 30, 31, 36, 37, 38,
        39, 6, 7, 28, 29, 30, 31, 36, 37, 38, 39, 8, 9, 16, 17, 18, 19, 20, 21, 32, 10, 11, 16, 17, 22, 23, 24, 25, 33,
        12, 13, 18, 19, 22, 23, 26, 27, 34, 14, 15, 20, 21, 24, 25, 26, 27, 35, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        26, 27, 0, 1, 8, 9, 2, 3, 10, 11, 4, 5, 12, 13, 6, 7, 14, 15, 28, 29, 30, 31
    };
    OSQPInt A_col_ptrs[21] = {0, 10, 20, 30, 40, 49, 58, 67, 76, 78, 80, 82, 84, 86, 88, 92, 96, 100, 104, 106, 108};
    OSQPFloat q[20] = {
        0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.200000, 1.200000, 1.200000,
        1.200000, 1.200000, 1.200000, 1.000000, 1.000000, 1.000000, 1.000000, 3.000000, 4.000000
    };
    //OSQPFloat l[40] = {-99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999, -99999};
    OSQPFloat u[40] = {
        0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 30.000000, -30.000000,
        30.000000, -30.000000, 30.000000, -30.000000, 30.000000, -30.000000, 0.000000, 0.000000, 0.000000, 0.000000,
        0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, -200.000000, 200.000000,
        0.000000, -0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 8000.000000, 30000.000000, 300.000000, 0.000000
    };


    OSQPFloat l[40] = {
        -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY,
        -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY,
        -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY,
        -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY,
        -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY, -OSQP_INFTY
    };

    /* Populate matrices */
    csc_set_data(A, m, n, A_nnz, A_data, A_row_indices, A_col_ptrs);
    csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);

    /* Set default settings */
    if (settings) {
        osqp_set_default_settings(settings);
        settings->polishing = 0;
        settings->verbose = 0;
        settings->alpha =1;
        settings->adaptive_rho = 0;
        //settings->scaling = 1;
        // settings->warm_starting = 0;
        //settings->sigma =0.00007;
         settings->rho = 0.001;
        //settings->eps_abs =0.00001;
        //settings->eps_rel = 0.00001;
        //settings->linsys_solver = OSQP_DIRECT_SOLVER;
        //settings->max_iter = 100;
        //settings->linsys_solver = OSQP_INDIRECT_SOLVER;
    }
    OSQPInt exitflag;

    exitflag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);
    //osqp_solve(solver);


    //setup struct with matrices and data2update
    static Data2update data2_update;


    data2_update.driveSetpoint = (OSQPFloat)-71;
    data2_update.yawSetpoint = (OSQPFloat) -71;

    data2_update.availableTorques[0] = (OSQPFloat) 40.0;
    data2_update.availableTorques[1] = (OSQPFloat) 25.0;
    data2_update.availableTorques[2] = (OSQPFloat) 7.0;
    data2_update.availableTorques[3] = (OSQPFloat) 15.0;

    data2_update.powerMax = (OSQPFloat) 800;
    data2_update.powerMin = (OSQPFloat) -300;

    data2_update.wheelSpeeds[0] = (OSQPFloat) 100;
    data2_update.wheelSpeeds[1] = (OSQPFloat) 100;
    data2_update.wheelSpeeds[2] = (OSQPFloat) 1000;
    data2_update.wheelSpeeds[3] = (OSQPFloat) 100;
    static PreviousMatrices matrices;

    matrices.A_x_new = A_data;
    matrices.A_p = A_col_ptrs;
    matrices.A_i = A_row_indices;
    matrices.P_x = P_x;
    matrices.P_i = P_i;
    matrices.P_p = P_p;
    matrices.q = q;
    matrices.l = l;
    matrices.u = u;
    matrices.m = m;
    matrices.n = n;
    matrices.solver = solver;

    data2_update.driveSetpoint = -1/2;
    data2_update.yawSetpoint = -0/2;
    if(!exitflag)LPdistribFunction(matrices, data2_update);
    if(exitflag) return -69;
    clock_t start, end;

     start = clock();
    int limit =300;
    for (int driveTorque = -limit; driveTorque < limit; driveTorque++) {
        for (int yawTorque = -limit; yawTorque <= limit; yawTorque++) {


            //printf("yawTorque   %i\n", yawTorque);
            data2_update.driveSetpoint = (OSQPFloat)driveTorque/3;
            data2_update.yawSetpoint = (OSQPFloat)yawTorque/3;
            if(!exitflag) exitflag =LPdistribFunction(matrices, data2_update);
            if(exitflag) return yawTorque;
        }
        //printf("driveTorque %i\n", driveTorque);
    }
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds that is %f Hertz\n", cpu_time_used,((limit*2)*(limit*2))/cpu_time_used);
    //LPdistribFunction(matrices, data2_update);
    float torques[4];
    LPdistribFunction(matrices, data2_update);

    torques[0] = matrices.solver->solution->x[0];
    torques[1] = matrices.solver->solution->x[1];
    torques[2] = matrices.solver->solution->x[2];
    torques[3] = matrices.solver->solution->x[3];

    for (int i = 0; i < 4; i++) {
        printf("torques[%d] = %f\n", i, torques[i]);
    }

    return (int) exitflag;
}
