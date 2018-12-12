#include<iostream>
#include<ctime>
using namespace std;
const double alpha = -1.0;     // reflection coefficient
const  double beta = 0.5;   // contraction coefficient
const  double gamma = 2.0;      // expansion coefficient
const double root2 = 1.414214; // square root of 2
const  double maxError = 1e-10; 

class CurveFitter {      

    double temp_R = 0;        //相关系数中转
    double R = 0;          //相关系数

    const static int IterFactor = 500;
    int Len;

	const static int defaultRestarts = 2; 
	const static int getNumParams=4; // paremeter number
    double *xData, *yData;  // x,y data to fit
	int numPoints;          // number of data points
	int numParams;          // number of parametres
	int numVertices;        // numParams+1 (includes sumLocalResiduaalsSqrd)
	int worst;          // worst current parametre estimates
	int nextWorst;      // 2nd worst current parametre estimates
	int best;           // best current parametre estimates
	double simp[getNumParams+1][getNumParams+1];        // the simplex (the last element of the array at each vertice is the sum of the square of the residuals)
	double next[getNumParams+1];      // new vertex to be tested
    /**
     * @brief all_R     //迭代过程中所有的相关系数
     * @brief all_simp  //迭代过程中所有的参数
     * @brief best_R_Index      //最优相关系数R在 all_R中的下标
     * @author hzj
     */
    double all_R[IterFactor*getNumParams*getNumParams];
    double all_simp[IterFactor*getNumParams*getNumParams][getNumParams+1];
    int iter = 0;
    int best_R_Index;

	int numIter;        // number of iterations so far
    int maxIter;    // maximum number of iterations per restart
	int restarts;   // number of times to restart simplex after first soln.
	// default number of restarts
	int nRestarts;  // the number of restarts that occurred
	// maximum error tolerance
//	double initialParams[Len];  // user specified initial parameters
	time_t times;  //elapsed time in ms

public:
    CurveFitter (double x[], double y[],int len);
	~CurveFitter();
	void doFit() ;
//	void initialize();
	void restart(int n);
	double f( double p[], double x);
	double *getParams();
	double *getResiduals();
	double getSumResidualsSqr();
	double  getSD();
	double  getRSquared() ;

    /**
     * @brief getR()       //获取最优相关系数
     * @brief getCoeff()  //获取最优参数
     */

    double getR();
    double *getCoeff();
	void print();
	double sqr(double d);
	void  sumResiduals (double x[]) ;
	void newVertex();
	void order();
	int  getIterations() ;
	int getMaxIterations();
};
