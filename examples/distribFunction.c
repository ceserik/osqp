//
// Created by cigla on 12. 10. 2024.
//
#include "osqp.h"
#include "distribTester2.h"
#include "distribFunction.h"

#include <stdio.h>

int LPdistribFunction(PreviousMatrices matrices, Data2update data2_update) {
    static float torques[4];
    //update avail
    matrices.u[8] = data2_update.availableTorques[0];
    matrices.u[9] = -data2_update.availableTorques[0];

    matrices.u[10] = data2_update.availableTorques[1];
    matrices.u[11] = -data2_update.availableTorques[1];

    matrices.u[12] = data2_update.availableTorques[2];
    matrices.u[13] = -data2_update.availableTorques[2];

    matrices.u[14] = data2_update.availableTorques[3];
    matrices.u[15] = -data2_update.availableTorques[3];

    matrices.u[28] = -data2_update.driveSetpoint;
    matrices.u[29] = data2_update.driveSetpoint;

    matrices.u[30] = -data2_update.yawSetpoint;
    matrices.u[31] = data2_update.yawSetpoint;

    //update speeds
    matrices.A_x_new[0] = data2_update.wheelSpeeds[0];
    matrices.A_x_new[1] = -data2_update.wheelSpeeds[0];

    matrices.A_x_new[2] = data2_update.wheelSpeeds[1];
    matrices.A_x_new[3] = -data2_update.wheelSpeeds[1];

    matrices.A_x_new[4] = data2_update.wheelSpeeds[2];
    matrices.A_x_new[5] = -data2_update.wheelSpeeds[2];

    matrices.A_x_new[6] = data2_update.wheelSpeeds[3];
    matrices.A_x_new[7] = -data2_update.wheelSpeeds[3];

    matrices.u[36] = data2_update.powerMax;
    matrices.u[37] = -data2_update.powerMin;
    //SQPFloat b[40] = matrices.u;

    //allow drive force to be only between zero and setpoint, so no negative force is created when setpoint is positive

    if (data2_update.driveSetpoint >= 0) {
        matrices.A_x_new[8] = 1;
        matrices.A_x_new[9] = 1;
        matrices.A_x_new[10] = 1;
        matrices.A_x_new[11] = 1;
        matrices.u[38] = data2_update.driveSetpoint;

        matrices.A_x_new[12] = -1;
        matrices.A_x_new[13] = -1;
        matrices.A_x_new[14] = -1;
        matrices.A_x_new[15] = -1;
        matrices.u[39] = 0;
    } else {
        matrices.A_x_new[8] = -1;
        matrices.A_x_new[9] = -1;
        matrices.A_x_new[10] = -1;
        matrices.A_x_new[11] = -1;
        matrices.u[38] = -data2_update.driveSetpoint;

        matrices.A_x_new[12] = 1;
        matrices.A_x_new[13] = 1;
        matrices.A_x_new[14] = 1;
        matrices.A_x_new[15] = 1;
        matrices.u[39] = 0;
    }

    OSQPInt exitflag = 0;
    if (!exitflag) exitflag = osqp_update_data_vec(matrices.solver,OSQP_NULL,OSQP_NULL, matrices.u);

    OSQPInt A_i_new[16] = {6,7,16,17,26,27,36,37,8,18,28,38,9,19,29,39};
    if (!exitflag) exitflag = osqp_update_data_mat(matrices.solver,OSQP_NULL,OSQP_NULL,OSQP_NULL, matrices.A_x_new, A_i_new,16);

    if (!exitflag) exitflag = osqp_solve(matrices.solver);

    torques[0] = (float) matrices.solver->solution->x[0];
    torques[1] = (float) matrices.solver->solution->x[1];
    torques[2] = (float) matrices.solver->solution->x[2];
    torques[3] = (float) matrices.solver->solution->x[3];


    return (int)exitflag;
}
