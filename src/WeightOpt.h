///////////////////////////////////////////////////////////////////////////////////////
//Copyright (C) Yang Zhang Lab, University of Michigan - All Rights Reserved
//Unauthorized copying of this file, via any medium is strictly prohibited
//Written by Xiaoqiang Huang <xiaoqiah@umich.edu>
//////////////////////////////////////////////////////////////////////////////////////

#ifndef WEIGHT_OPT_H
#define WEIGHT_OPT_H

#define  NUM_ENERGY_TERM 72
#define  NUM_REFERENCE   20
#define  NUM_ENERGY_MON  46 //20 ref + 8 intra + 3 statistics + 15 interS
#define  NUM_ENERGY_PPI  15 //5terms + 1 ssbond + 9 HB terms
#define  NUM_ENERGY_LIG  11 //5terms + 6 HB terms

#define  DELTA_X        1e-4
#define  EPSILON        1e-3
#define  WOLFE_C1       1e-4
#define  WOLFE_C2       0.1
#define  MAX_STEP       500


int isNumber(double x);
int isFiniteNumber(double d);


typedef struct _EnergyTermRot{
  //only two types: the first type is NAT rotamer
  //the second is ROT rotamer
  int rotCount[2];
  double **energy[2];
}EnergyTermRot;

int EnergyTermRotCreate(EnergyTermRot* pTerm);
int EnergyTermRotDestroy(EnergyTermRot* pTerm);


typedef struct _EnergyTermsRot{
  int posCount;
  EnergyTermRot* terms;
}EnergyTermsRot;

int EnergyTermsRotCreate(EnergyTermsRot * pTerms);
int EnergyTermsRotDestroy(EnergyTermsRot * pTerms);
int EnergyTermsRotRead(EnergyTermsRot* terms, char* pdblist);

int GradientUnit(double *grad,int xcount);
double GradientNorm(double *grad,int xcount);
double GradientMax(double *grad,int xcount);
int Xupdate(double *x,double *grad,int xcount,double alpha);
int Xshow(double *x,int xcount);

int PNATROT_BacktrackLineSearch(EnergyTermsRot *pTerms,double lossk,double *xk,double * gradk,double scalar,int xcnt);
int PNATROT_LossFunction(EnergyTermsRot* pTerms,double *x,int xcount,double *loss);
int PNATROT_CalcGradientTwoSide(EnergyTermsRot* pTerms,double loss,double *x,double *grad,int xcount);
int PNATROT_CalcGradientForward(EnergyTermsRot* pTerms,double loss,double *x,double *grad,int xcount);
int PNATROT_CalcGradientBackword(EnergyTermsRot* pTerms,double loss,double *x,double *grad,int xcount);
int PNATROT_WeightOptByGradientDescent(char* pdblistfile);


#define TYPE_TWENTYTWO 22


typedef struct _EnergyTermAA{
  //21 types: ACD...Y and NAT rotamer
  //index 0-19 are A,C,D,...,Y and index 21 is NAT
  int rotCount[TYPE_TWENTYTWO];
  double **energy[TYPE_TWENTYTWO];
}EnergyTermAA;

int EnergyTermAllCreate(EnergyTermAA* pTerm);
int EnergyTermAllDestroy(EnergyTermAA* pTerm);

typedef struct _EnergyTermsAA{
  int posCount;
  EnergyTermAA* terms;
}EnergyTermsAA;

int EnergyTermsAACreate(EnergyTermsAA* pTerms);
int EnergyTermsAADestroy(EnergyTermsAA* pTerms);
int EnergyTermsAARead(EnergyTermsAA* pTerms,char* pdblist);
int PNATAA_BacktrackLineSearch(EnergyTermsAA *pTerms,double lossk,double *xk,double * gradk,double scalar,int xcnt);
int PNATAA_LossFunction(EnergyTermsAA* pTerms,double *x,int xcount,double *loss);
int PNATAA_CalcGradientForward(EnergyTermsAA* pTerms,double loss,double *x,double *grad,int xcount);
int PNATAA_WeightOptByGradientDescent(char* pdblistfile);

#endif