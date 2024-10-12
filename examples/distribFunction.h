//
// Created by cigla on 12. 10. 2024.
//
#include "osqp.h"
#ifndef DISTRIBTESTER2_H
#define DISTRIBTESTER2_H

#endif //DISTRIBTESTER2_H

int LPdistribFunction();

typedef struct {
    OSQPSolver* solver;     //test
    OSQPCscMatrix* P;       //test
    OSQPFloat* q;           //test
    OSQPCscMatrix* A;       //test
    OSQPFloat* l;           //test
    OSQPFloat* u;           //test
    OSQPInt m;              //test
    OSQPInt n;              //test
} OSQPProblem;

typedef struct {
    OSQPSolver* solver;
    OSQPFloat* P_x;
    OSQPInt* P_i;
    OSQPInt* P_p;
    OSQPFloat* A_x_new;
    OSQPInt* A_i;
    OSQPInt* A_p;
    OSQPFloat* q;
    OSQPFloat* u;
    OSQPFloat* l;
    OSQPInt n;
    OSQPInt m;
} PreviousMatrices;


typedef struct {
    OSQPFloat driveSetpoint;
    OSQPFloat yawSetpoint;
    OSQPFloat availableTorques[4];
    OSQPFloat powerMax;
    OSQPFloat powerMin;
    OSQPFloat wheelSpeeds[4];

}Data2update;

