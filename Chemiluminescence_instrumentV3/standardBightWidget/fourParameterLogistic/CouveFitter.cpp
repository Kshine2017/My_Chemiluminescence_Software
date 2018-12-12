#include<ctime>
#include<cmath>
#include<iostream>
#include"CouveFitter.h"
#include <QDebug>
using namespace std;
/** Construct a new CurveFitter. */

CurveFitter::CurveFitter (double x[], double y[],int len)
{
    int i;
    Len = len;
    maxIter=0;
    xData=new double[Len];
    yData=new double[Len];
	for (i=0;i<Len;i++)
	{xData[i] = x[i];
	yData[i] = y[i];}
	numPoints = Len;
	numParams = getNumParams;
	numVertices = numParams + 1;      // need 1 more vertice than parametres,
//		static double **simp = new double*[numVertices];
//	for(int i=0;i<numVertices;i++)
//	simp[i]=new double[numVertices];
//	static double *next = new double[numVertices];

	double firstx = xData[0];
	double firsty = yData[0];
	double lastx = xData[numPoints-1];
	double lasty = yData[numPoints-1];
	double xmean = (firstx+lastx)/2.0;
	double ymean = (firsty+lasty)/2.0;
	double miny=firsty, maxy=firsty;
	double slope;
	if ((lastx - firstx) != 0.0)
		slope = (lasty - firsty)/(lastx - firstx);
	else
		slope = 1.0;
	double yintercept = firsty - slope * firstx;
	if (maxIter==0)
		maxIter = IterFactor * numParams * numParams;  // Where does this estimate come from?
	restarts = defaultRestarts;
	nRestarts = 0;

    simp[0][0] = lasty;
    simp[0][1] = 1.0;
	simp[0][2] = xmean;
    simp[0][3] = firsty;
}
CurveFitter::~CurveFitter()
{
	//delete []xData;
	//delete []yData;
	//for(int k=0;k<numVertices;k++)
	//	delete []simp[k];
	//delete[]simp;
	//delete []next;
}
/**  Perform curve fitting with the simplex method
*          doFit(fitType) just does the fit
*          doFit(fitType, true) pops up a dialog allowing control over simplex parameters
*      alpha is reflection coefficient  (-1)
*      beta is contraction coefficient (0.5)
*      gamma is expansion coefficient (2)
*/


void CurveFitter::doFit() {
//	CurveFitter.initialize();
	//if (initialParams!=NULL) {
	//	for (int i=0; i<numParams; i++)
	//		simp[0][i] = initialParams[i];
		//initialParams = NULL;
	//}
	//long startTime = LocalTime();
	time_t startTime;
		time(&startTime);
	restart(0);

	numIter = 0;
	bool done = false;
	double center[getNumParams]={0};  // mean of simplex vertices
	while (!done) {
		numIter++;
		for (int i = 0; i < numParams; i++) center[i] = 0.0;
		// get mean "center" of vertices, excluding worst
		for (int i = 0; i < numVertices; i++)
			if (i != worst)
				for (int j = 0; j < numParams; j++)
					center[j] =center[j]+ simp[i][j];
		// Reflect worst vertex through centre
		for (int i = 0; i < numParams; i++) {
			center[i] /= numParams;
			next[i] = center[i] + alpha*(simp[worst][i] - center[i]);
		}
		sumResiduals(next);
		// if it's better than the best...
		if (next[numParams] <= simp[best][numParams]) {
			newVertex();
			// try expanding it
			for (int i = 0; i < numParams; i++)
				next[i] = center[i] + gamma * (simp[worst][i] - center[i]);
			sumResiduals(next);
			// if this is even better, keep it
			if (next[numParams] <= simp[worst][numParams])
				newVertex();
		}
		// else if better than the 2nd worst keep it...
		else if (next[numParams] <= simp[nextWorst][numParams]) {
			newVertex();
		}
		// else try to make positive contraction of the worst
		else {
			for (int i = 0; i < numParams; i++)
				next[i] = center[i] + beta*(simp[worst][i] - center[i]);
			sumResiduals(next);
			// if this is better than the second worst, keep it.
			if (next[numParams] <= simp[nextWorst][numParams]) {
				newVertex();
			}
			// if all else fails, contract simplex in on best
			else {
				for (int i = 0; i < numVertices; i++) {
					if (i != best) {
						for (int j = 0; j < numVertices; j++)
							simp[i][j] = beta*(simp[i][j]+simp[best][j]);
						sumResiduals(simp[i]);
					}
				}
			}
		}
		order();

		double rtol = 2 * fabs(simp[best][numParams] - simp[worst][numParams]) /
            (fabs(simp[best][numParams]) + fabs(simp[worst][numParams]) + 0.0000000001);
        /**hzj新添**/

        R = getRSquared();
        all_R[iter] = R;

        for(int i = 0;i<=getNumParams ;i++)
        {
            all_simp[iter][i] = simp[best][i];
        }

        iter++;

        /*hzj新添*/

		if (numIter >= maxIter)
			done = true;
		else if (rtol < maxError) {
			restarts--;
			if (restarts < 0)
				done = true;
			else
				restart(best);
		}
	}
	time_t SedTime;
	time(&SedTime);
	times = SedTime-startTime;
    getR();
    getCoeff();

}



/** Initialise the simplex */
/*void CurveFitter::initialize() {
	// Calculate some things that might be useful for predicting parametres
	numParams = getNumParams;
	numVertices = numParams + 1;      // need 1 more vertice than parametres,
		double **simp = new double*[numVertices];
	for(int i=0;i<numVertices;i++)
	simp[i]=new double[numVertices];
	double *next = new double[numVertices];

	double firstx = xData[0];
	double firsty = yData[0];
	double lastx = xData[numPoints-1];
	double lasty = yData[numPoints-1];
	double xmean = (firstx+lastx)/2.0;
	double ymean = (firsty+lasty)/2.0;
	double miny=firsty, maxy=firsty;
	double slope;
	if ((lastx - firstx) != 0.0)
		slope = (lasty - firsty)/(lastx - firstx);
	else
		slope = 1.0;
	double yintercept = firsty - slope * firstx;//
	if (maxIter==0)
		maxIter = IterFactor * numParams * numParams;  // Where does this estimate come from?
	restarts = defaultRestarts;
	nRestarts = 0;

	simp[0][0] = firsty;
	simp[0][1] = 1.0;
	simp[0][2] = xmean;
	simp[0][3] = lasty;
}*/

/** Restart the simplex at the nth vertex */
void CurveFitter::restart(int n) {
	// Copy nth vertice of simplex to first vertice
	for (int i = 0; i < numParams; i++) {
		simp[0][i] = simp[n][i];
	}
	sumResiduals(simp[0]);          // Get sum of residuals^2 for first vertex
	double *step = new double[numParams];
	for (int i = 0; i < numParams; i++) {
		step[i] = simp[0][i] / 2.0;     // Step half the parametre value
		if (step[i] == 0.0)             // We can't have them all the same or we're going nowhere
			step[i] = 0.01;
	}
	// Some kind of factor for generating new vertices
	double *p = new double[numParams];
	double *q = new double[numParams];
	for (int i = 0; i < numParams; i++) {
		p[i] = step[i] * (sqrt(double(numVertices)) + numParams - 1.0)/(numParams * root2);
		q[i] = step[i] * (sqrt(double(numVertices)) - 1.0)/(numParams * root2);
	}
	// Create the other simplex vertices by modifing previous one.
	for (int i = 1; i < numVertices; i++) {
		for (int j = 0; j < numParams; j++) {
			simp[i][j] = simp[i-1][j] + q[j];
		}
		simp[i][i-1] = simp[i][i-1] + p[i-1];
		sumResiduals(simp[i]);
	}
	// Initialise current lowest/highest parametre estimates to simplex 1
	best = 0;
	worst = 0;
	nextWorst = 0;
	order();
	nRestarts++;
}

// Display simplex [Iteration: s0(p1, p2....), s1(),....] in Log window


/** Get number of parameters for current fit formula */


/** Returns formula value for parameters 'p' at 'x' */


/** Returns 'fit' formula value for parameters "p" at "x" */
double CurveFitter::f( double p[], double x) {
	double y;
	double ex;
	if (x == 0.0)
		ex = 0.0;
	else
		ex = exp(log(x/p[2])*p[1]);
	y = p[0]-p[3];
	y = y/(1.0+ex);
	return (y+p[3]);
}

/** Get the set of parameter values from the best corner of the simplex */
double * CurveFitter:: getParams() {
	order();

    return simp[best];
}

/** Returns residuals array ie. differences between data and curve. */
double * CurveFitter::getResiduals() {
	double *params = getParams();
	double *residuals = new double[numPoints];
	for (int i=0; i<numPoints; i++)
		residuals[i] = yData[i] - f(params, xData[i]);
	return residuals;
}

/* Last "parametre" at each vertex of simplex is sum of residuals
* for the curve described by that vertex
*/
double CurveFitter:: getSumResidualsSqr() {
	double sumResidualsSqr = (getParams())[getNumParams];
	return sumResidualsSqr;
}

/**  Returns the standard deviation of the residuals. */
double CurveFitter:: getSD() {
	double *residuals = getResiduals();
	int n = Len; // n=residuals.length;
	double sum=0.0, sum2=0.0;
	for (int i=0; i<n; i++) {
		sum += residuals[i];
		sum2 += residuals[i]*residuals[i];
	}
	double stdDev = (n*sum2-sum*sum)/n;
	return sqrt(stdDev/(n-1.0));
}

/** Returns R^2, where 1.0 is best.
<pre>
r^2 = 1 - SSE/SSD

where:  SSE = sum of the squares of the errors
SSD = sum of the squares of the deviations about the mean.
</pre>
*/
double CurveFitter:: getRSquared() {
    double sumY = 0.0;
    for (int i=0; i<numPoints; i++) sumY += yData[i];
    double mean = sumY/numPoints;
//    double sumMeanDiffSqr = 0.0;
//    for (int i=0; i<numPoints; i++)
//        sumMeanDiffSqr += sqr(yData[i]-mean);
    double rSquared = 0.0;
//    if (sumMeanDiffSqr>0.0)
//        rSquared = 1.0 - getSumResidualsSqr()/sumMeanDiffSqr;
    double fenzi = 0;
    double fenmu = 0;
    double *pVal = getParams();

    for(int i=0;i<Len;i++)
    {
        fenzi+=pow((pVal[0]-pVal[3])/(1+pow(xData[i]/pVal[2],pVal[1]))+pVal[3]-mean,2);
        fenmu+=pow(yData[i]-mean,2);
    }

    rSquared = fenzi/fenmu;
	return rSquared;
}

/**  Get a measure of "goodness of fit" where 1.0 is best. */


/** Get a string description of the curve fitting results
* for easy output.
*/
void CurveFitter:: print() {
	cout<< "\nFormula: y = d+(a-d)/(1+(x/c)^b)" ;
	cout<<"\nTimes: "<<times<<"ms" ;
	cout<<"\nNumber of iterations: " <<getIterations() << " (" << getMaxIterations() << ")" ;
	cout<<"\nNumber of restarts: " <<(nRestarts-1) << " (" << defaultRestarts << ")" ;
	cout<< "\nSum of residuals squared: " <<getSumResidualsSqr() ;
	cout<<"\nStandard deviation: " <<getSD();
    cout<<"\nR^2: " <<getRSquared(),Len;
	cout<<"\nParameters:";
	char pChar = 'a';
	double *pVal = getParams();
	for (int i = 0; i < numParams; i++) {
		cout<<"\n  " << pChar <<" = " <<pVal[i];
		pChar++;
	}

    qDebug()<<pVal[3];

}

double CurveFitter::sqr(double d) { return d * d; }

/** Adds sum of square of residuals to end of array of parameters */
void CurveFitter:: sumResiduals (double x[]) {
	x[numParams] = 0.0;
	for (int i=0; i<numPoints; i++)
		x[numParams] = x[numParams] + pow((f(x,xData[i])-yData[i]),2);

}

/** Keep the "next" vertex */
void CurveFitter:: newVertex() {
	for (int i = 0; i < numVertices; i++)
		simp[worst][i] = next[i];
}

/** Find the worst, nextWorst and best current set of parameter estimates */
void CurveFitter:: order() {
	for (int i = 0; i < numVertices; i++) {
		if (simp[i][numParams] < simp[best][numParams]) best = i;
		if (simp[i][numParams] > simp[worst][numParams]) worst = i;
	}
	nextWorst = best;
	for (int i = 0; i < numVertices; i++) {
		if (i != worst) {
			if (simp[i][numParams] > simp[nextWorst][numParams]) nextWorst = i;
		}
	}
	//        IJ.log("B: " + simp[best][numParams] + " 2ndW: " + simp[nextWorst][numParams] + " W: " + simp[worst][numParams]);
}

/** Get number of iterations performed */
int CurveFitter:: getIterations() {
	return numIter;
}

/** Get maximum number of iterations allowed */
int CurveFitter:: getMaxIterations() {
	return maxIter;
}

/**
 * @brief CurveFitter::getR
 * @return  返回所有系数中 最接近1（小于1）的系数。
 */
double CurveFitter::getR()
{
    double temp = 0;
    for(int i = 0;i < maxIter;i++){
        if(all_R[i]>temp&&all_R[i]<1)
        {
            temp=all_R[i];
        }
    }

    for(int i = 0;i < maxIter;i++){
        if(all_R[i] == temp)
        {
            best_R_Index = i;
        }
    }
    qDebug()<<"temp---"<<temp;
    return temp;
}
double * CurveFitter::getCoeff()
{
    getR();

    qDebug()<<"best_simp"<<best_R_Index;
    qDebug()<<"best_simp"<<all_simp[best_R_Index][0];
    qDebug()<<"best_simp"<<all_simp[best_R_Index][1];
    qDebug()<<"best_simp"<<all_simp[best_R_Index][2];
    qDebug()<<"best_simp"<<all_simp[best_R_Index][3];
    qDebug()<<"best_simp"<<all_simp[best_R_Index][4];

    return all_simp[best_R_Index];

}



