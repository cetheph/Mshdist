#ifndef _DIST_H
#define _DIST_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#include "chrono.h"
#include "libmesh5.h"
#include "lplib3.h"
#include "memory.h"

#define D_VER   "1.1b"
#define D_REL   "June 21, 2010"
#define D_CPY   "Copyright (c) LJLL, 2010"
#define D_STR   "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"

#define D_MAX(a,b) (((a) > (b)) ? (a) : (b))
#define D_MIN(a,b) (((a) < (b)) ? (a) : (b))

#define LONMAX   8192
#define EPS      1.e-6
#define EPS1     1.e-20
#define EPS2     1.e-10
#define PRECI    1.0    // size for scaling
#define SIZE     0.95   // size of mesh2 in mesh1

#define REFINT        3
#define REFDIR        1
#define REFDIRSWP     3
#define REFSYM        4
#define MAXGRD        5.0
#define ATHIRD        0.333333333

#define INIVAL_2d     1 //0.25
#define INIVAL_3d     3.0

typedef struct {
  double         c[3],h;
  int            s,flag;
  unsigned char  b,tag;
} Point;
typedef Point * pPoint;

typedef struct {
	int     v[2],flag,ref;
} Edge;
typedef Edge * pEdge;

typedef struct {
  int            v[3],mark,flag,ref;
  double         h;
  unsigned char  tag;
} Tria;
typedef Tria * pTria;

typedef struct {
  int            v[4],mark,flag,ref;
  double         h;
  unsigned char  tag;
} Tetra;
typedef Tetra * pTetra;

typedef struct {
  double   delta1[3],delta2[3],min1[3],max1[3],min2[3],max2[3],cen1[3],cen2[3];
  double   dt,ray,res;
  int      ncpu,libpid,typ[2];          /* for // purposes */
  int      maxit,ref,nsref,*sref;
  int      nintel,*intel,nst,*st,nsa,*sa,nsp,*sp; /* for -dom option */
  char     imprim,ddebug,option,bbbc,hausdorff,specdist,startref,noscale;
  mytime   ctim[TIMEMAX];
} Info;

typedef struct {
  int      np,na,nt,ne,ver,dim;
  int     *adja,mark,base,flag;
  char    *name,bin;

  pPoint   point;
  pEdge    edge;
  pTria    tria;
  pTetra   tetra;
} Mesh;
typedef Mesh * pMesh;

typedef struct {
  int         np,nt,ne,dim,ver,bin;
  int         type[2],size,typtab[2][GmfMaxTyp];
  double     *val;
  float       time;
  int        *ref;
  char       *name;
} Sol;
typedef Sol * pSol;

typedef struct {
	pMesh    mesh;
	pSol     sol;
	double  *grad,*dtmp,*res,dt,dtfin;
} Param;

typedef struct {
  int     size;
  int    *head;
  int    *link;
} Bucket;
typedef Bucket * pBucket;

typedef struct {
  int           mins,maxs,s,k,nxt;
} hTria;

typedef struct {
  hTria         *ttab;
  int           thsiz,thmax;
} hash;

/* prototypes */
int  loadMesh(pMesh mesh1,pMesh mesh2);
int  loadSol(pSol );
int  saveSol(pSol sol);
int  mshdis1(pMesh mesh1,pMesh mesh2,pSol sol1);
int  scaleMesh(pMesh mesh1,pMesh mesh2,pSol sol1);
int  unscaleSol(pSol sol);
int  locateTetra(pMesh mesh,int nsdep,int base,double *p,double *cb);
int  locateTria(pMesh mesh,int nsdep,int base,double *p,double *cb);
int boulep (pMesh mesh, int start, int ip, int * list);
void freeBucket(pBucket );

int intersec_2d(pPoint,pPoint,pPoint,pPoint);
double distpt_2d(pPoint,pPoint,pPoint,int*);
double distnv0_2d(pMesh,pSol,int,pPoint,int*);
int buildcircum_3d(pMesh,double *);
int circumcoords(pPoint,pPoint,pPoint,double *);
double distptplan(pPoint,pPoint,pPoint,pPoint);
double distpt_3d(pPoint p0,pPoint p1,pPoint p2,pPoint pq,char *proj);
double distnv0_3d(pMesh,pSol,int,pPoint,char*);
double distnv0approx_3d(pMesh,pSol,int,pPoint);
int buildcircumredis_3d(pMesh,pSol,int*,int,double*);

pBucket newBucket_2d(pMesh ,int );
pBucket newBucket_3d(pMesh ,int );
int     buckin_2d(pMesh ,pBucket ,double *);
int     buckin_3d(pMesh ,pBucket ,double *);
int     inTetra(pMesh ,int ,double *,double *);
int     inTria(pMesh ,int ,double *,double *);
int     locelt_2d(pMesh ,int ,double *,double *);
int     locelt_3d(pMesh ,int ,double *,double *);
int     nxtelt_2d(pMesh ,int ,double *,double *);
int     nxtelt_3d(pMesh ,int ,double *,double *);
int     closept_2d(pMesh ,double *);
int     closept_3d(pMesh ,double *);
int     hashelt_3d(pMesh );
int     hashelt_2d(pMesh );
int     inidist_2d(pMesh ,pMesh ,pSol ,pBucket );
int     inidist_3d(pMesh ,pMesh ,pSol ,pBucket );
int     iniredist_2d(pMesh ,pSol );
int     iniredist_3d(pMesh ,pSol );
int     sgndist_2d(pMesh ,pMesh ,pSol ,pBucket );
int     sgndist_3d(pMesh ,pMesh ,pSol ,pBucket );
int     ppgdist_2d(pMesh mesh, pSol sol);
int     ppgdist_3d(pMesh mesh, pSol sol);
int     iniencdomain_2d(pMesh mesh, pSol sol);
int     iniencdomain_3d(pMesh mesh, pSol sol);
int     inireftrias_2d(pMesh mesh, pSol sol);
int     inireftrias_3d(pMesh mesh, pSol sol);
int     hashEdge_2d(pMesh mesh);
int     getEdge(pMesh mesh, int ia, int ib);
double  hausdorff(pMesh, pMesh);
int     errdist(pMesh mesh,pMesh mesh2,pSol sol);
int     hashTriaRef(pMesh);
int     getTria(pMesh,int,int,int);
double  volume(double *,double *,double *,double *);
void    delhash(pMesh);
int     corrGrad_3d(pMesh,pSol);
int     isIntDom(int );
int     isStartTri(int );
int     isStartEdg(int );
int     isStartVer(int );

/* Analytical distance functions */
int     genHolesPCB_2d(pMesh mesh,pSol sol);
int     gen2Holes_2d(pMesh mesh,pSol sol);
int     genHolesRadia_2d(pMesh ,pSol );
int     holeClMast_3d(pMesh mesh, pSol sol);
int     genHolesMast_3d(pMesh mesh, pSol sol);
int     holeClBridge_3d(pMesh mesh, pSol sol);
int     holeClBridge2_3d(pMesh mesh, pSol sol);
int     genHolesBridge_3d(pMesh,pSol);
int     genHolesCantia_3d(pMesh mesh,pSol sol);
int     holeClStarfish_3d(pMesh mesh, pSol sol);
int     genHolesStarfish_3d(pMesh,pSol);
int     holeClCrane(pMesh,pSol);
int     holeCraneIni(pMesh,pSol);
int     anafunc(pMesh,pSol);
int     anafuncbuddha(pMesh,pSol);
int     anafuncsaddle(pMesh,pSol);
int     anafunctorus(pMesh,pSol);
int     anafuncspherelag(pMesh,pSol);
int     anafunchelix(pMesh,pSol);
int     holeClGrip(pMesh,pSol);
int     holeGripIni(pMesh,pSol);
int     holeLBeamIni(pMesh,pSol);
int     holeCl_LBBBeam(pMesh,pSol);
int     holeLBBBeamIni(pMesh,pSol);
int     genHolesCanti_2d(pMesh,pSol);
int     genHolesMast_2d(pMesh,pSol);
int     genHolesSCantia_3d(pMesh,pSol);
int     holeCl_Chair(pMesh,pSol);
int     holeChairIni(pMesh,pSol);
int     gen1Hole_2d(pMesh mesh,pSol sol);

/* Function pointers */
pBucket (*newBucket)(pMesh ,int );
int     (*buckin)(pMesh ,pBucket ,double *);
int     (*locelt)(pMesh ,int ,double *,double *);
int     (*nxtelt)(pMesh ,int ,double *,double *);
int     (*closept)(pMesh ,double *);
int     (*hashelt)(pMesh );
int     (*inidist)(pMesh ,pMesh ,pSol ,pBucket );
int     (*iniredist)(pMesh ,pSol );
int     (*iniencdomain)(pMesh ,pSol );
int     (*inireftrias)(pMesh, pSol);
int     (*sgndist)(pMesh ,pMesh ,pSol ,pBucket );
int     (*ppgdist)(pMesh mesh, pSol sol);

#endif
