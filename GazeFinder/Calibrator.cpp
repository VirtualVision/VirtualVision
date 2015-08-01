
#include "Calibrator.h"
#include "Mapper.h"
#include "Logger.h"

#define SIZE 9
#define RES1 1180
#define RES2 564
#define CALIBRATIONPOINTS    9
#define SIGN(u, v)     ( (v)>=0.0 ? fabs(u) : -fabs(u) )
#define MAX(x, y)     ( (x) >= (y) ? (x) : (y) )

using namespace std;

double map_matrix[3][3];
int counter = 0;

double xtargets[SIZE] = { 0,590,1180,0,590,1180,0,590,1180 };
double ytargets[SIZE] = { 0,0,0,282,282,282,564,564,564 };

double xpupil[SIZE];
double ypupil[SIZE];

Mapper m;


Calibrator::Calibrator()
{

	m.dataLog = dataLog;
	m.pub = pub;

}

Calibrator::~Calibrator()
{

}

/*
*  Add x value to the pupil point array.
*/
void Calibrator::setX(double x)
{
	//Add up to 9 points
	if (counter < 9)
	{
		xpupil[counter] = x;
		printf("Added x: %f\n", xpupil[counter]);
		dataLog.log("Added x: " + to_string(xpupil[counter]) + "\n");
	}
	else
	{
		printf("Error: Tried to add too many pupil points");
		dataLog.log("Error: Tried to add too many pupil points");
	
	}
	
}

/*
*  Add y value to the pupil point array.
*/
void Calibrator::setY(double y)
{
	//Add up to 9 points
	if (counter < 9)
	{
		ypupil[counter] = y;
		printf("Added y: %f\n", ypupil[counter]);
		dataLog.log("Added y: " + to_string(ypupil[counter]) + "\n");
	    counter++;
	}
	else
	{
		printf("Error: Tried to add too many pupil points");
		dataLog.log("Error: Tried to add too many pupil points");
	}
	
}

/*
*  Once all 9 points are received, calculate the matrix.
*/
void Calibrator::calibrate()
{
	if (counter >= 9)
	{
		printf("CPoints: \n");
		dataLog.log("CPoints: \n");
		for (int i = 0; i < SIZE; i++)
		{
			printf("%f, %f \n", xtargets[i],ytargets[i]);
			dataLog.log(to_string(xtargets[i]) + ", " + to_string(ytargets[i]) + "\n");
		}

		printf("PPoints: \n");
		dataLog.log("PPoints: \n");
		for (int i = 0; i < SIZE; i++)
		{
			printf("%f, %f \n", xpupil[i], ypupil[i]);
			dataLog.log(to_string(xpupil[i]) + ", " + to_string(ypupil[i]) + "\n");
		}

		//calculates the matrix
		cal_calibration_homography(xtargets, ytargets, xpupil, ypupil);

	}
	else
	{
		printf("Error: Tried to calibrate with too few pupil points");
		dataLog.log("Error: Tried to calibrate with too few pupil points");
	}
	
}

void Calibrator::recalibrate()
{
	counter = 0;

}


void Calibrator::cal_calibration_homography(double xtargets[], double ytargets[], double xpupil[], double ypupil[])
{
	int i, j;
	stuDPoint cal_scene[9], cal_eye[9];
	stuDPoint scene_center, eye_center, *eye_nor, *scene_nor;
	double dis_scale_scene, dis_scale_eye;

	for (i = 0; i < 9; i++) {
		cal_scene[i].x = xtargets[i];
		cal_scene[i].y = ytargets[i];
		cal_eye[i].x = xpupil[i];
		cal_eye[i].y = ypupil[i];
	}

	scene_nor = normalize_point_set(cal_scene, dis_scale_scene, scene_center, CALIBRATIONPOINTS);
	eye_nor = normalize_point_set(cal_eye, dis_scale_eye, eye_center, CALIBRATIONPOINTS);

	printf("normalize_point_set end\n");
	printf("scene scale:%lf  center (%lf, %lf)\n", dis_scale_scene, scene_center.x, scene_center.y);
	printf("eye scale:%lf  center (%lf, %lf)\n", dis_scale_eye, eye_center.x, eye_center.y);

	const int homo_row = 18, homo_col = 9;
	double A[homo_row][homo_col];
	int M = homo_row, N = homo_col; //M is row; N is column
	double **ppa = (double**)malloc(sizeof(double*)*M);
	double **ppu = (double**)malloc(sizeof(double*)*M);
	double **ppv = (double**)malloc(sizeof(double*)*N);
	double pd[homo_col];
	for (i = 0; i < M; i++) {
		ppa[i] = A[i];
		ppu[i] = (double*)malloc(sizeof(double)*N);
	}
	for (i = 0; i < N; i++) {
		ppv[i] = (double*)malloc(sizeof(double)*N);
	}

	for (j = 0; j< M; j++) {
		if (j % 2 == 0) {
			A[j][0] = A[j][1] = A[j][2] = 0;
			A[j][3] = -eye_nor[j / 2].x;
			A[j][4] = -eye_nor[j / 2].y;
			A[j][5] = -1;
			A[j][6] = scene_nor[j / 2].y * eye_nor[j / 2].x;
			A[j][7] = scene_nor[j / 2].y * eye_nor[j / 2].y;
			A[j][8] = scene_nor[j / 2].y;
		}
		else {
			A[j][0] = eye_nor[j / 2].x;
			A[j][1] = eye_nor[j / 2].y;
			A[j][2] = 1;
			A[j][3] = A[j][4] = A[j][5] = 0;
			A[j][6] = -scene_nor[j / 2].x * eye_nor[j / 2].x;
			A[j][7] = -scene_nor[j / 2].x * eye_nor[j / 2].y;
			A[j][8] = -scene_nor[j / 2].x;
		}
	}

	printf("normalize_point_set end\n");

	svd(M, N, ppa, ppu, pd, ppv);
	int min_d_index = 0;
	for (i = 1; i < N; i++) {
		if (pd[i] < pd[min_d_index])
			min_d_index = i;
	}

	for (i = 0; i < N; i++) {
		map_matrix[i / 3][i % 3] = ppv[i][min_d_index];  //the column of v that corresponds to the smallest singular value,
														 //which is the solution of the equations
	}

	double T[3][3] = { 0 }, T1[3][3] = { 0 };
	printf("\nT1: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", T1[j][i]);
		}
		printf("\n");
	}

	T[0][0] = T[1][1] = dis_scale_eye;
	T[0][2] = -dis_scale_eye*eye_center.x;
	T[1][2] = -dis_scale_eye*eye_center.y;
	T[2][2] = 1;

	printf("\nmap_matrix: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", map_matrix[j][i]);
		}
		printf("\n");
	}
	printf("\nT: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", T[j][i]);
		}
		printf("\n");
	}

	matrix_multiply33(map_matrix, T, map_matrix);

	T[0][0] = T[1][1] = dis_scale_scene;
	T[0][2] = -dis_scale_scene*scene_center.x;
	T[1][2] = -dis_scale_scene*scene_center.y;
	T[2][2] = 1;

	printf("\nmap_matrix: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", map_matrix[j][i]);
		}
		printf("\n");
	}
	printf("\nT: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", T[j][i]);
		}
		printf("\n");
	}

	affine_matrix_inverse(T, T1);
	matrix_multiply33(T1, map_matrix, map_matrix);

	printf("\nmap_matrix: \n");
	dataLog.log("\nmap_matrix: \n");
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			printf("%8lf ", map_matrix[j][i]);
			dataLog.log(to_string(map_matrix[j][i]));
		}
		printf("\n");
		dataLog.log("\n");
	}

	for (i = 0; i < M; i++) {
		free(ppu[i]);
	}
	for (i = 0; i < N; i++) {
		free(ppv[i]);
	}
	free(ppu);
	free(ppv);
	free(ppa);

	free(eye_nor);
	free(scene_nor);
	printf("\nfinish calculate calibration\n");
	dataLog.log("\nfinish calculate calibration\n\n");
}

Calibrator::stuDPoint* Calibrator::normalize_point_set(stuDPoint* point_set, double &dis_scale, stuDPoint &nor_center, int num)
{
	double sumx = 0, sumy = 0;
	double sumdis = 0;
	stuDPoint *edge = point_set;
	int i;
	for (i = 0; i < num; i++) {
		sumx += edge->x;
		sumy += edge->y;
		sumdis += sqrt((double)(edge->x*edge->x + edge->y*edge->y));
		edge++;
	}

	dis_scale = sqrt((double)2)*num / sumdis;
	nor_center.x = sumx*1.0 / num;
	nor_center.y = sumy*1.0 / num;
	stuDPoint *edge_point_nor = (stuDPoint*)malloc(sizeof(stuDPoint)*num);
	edge = point_set;
	for (i = 0; i < num; i++) {
		edge_point_nor[i].x = (edge->x - nor_center.x)*dis_scale;
		edge_point_nor[i].y = (edge->y - nor_center.y)*dis_scale;
		edge++;
	}

	return edge_point_nor;
}

static double   radius(double u, double v)
{
	double          w;
	u = fabs(u);
	v = fabs(v);
	if (u > v) {
		w = v / u;
		return (u * sqrt(1. + w * w));
	}
	else {
		if (v) {
			w = u / v;
			return (v * sqrt(1. + w * w));
		}
		else
			return 0.0;
	}
}

/*
Given matrix a[m][n], m>=n, using svd decomposition a = p d q' to get
p[m][n], diag d[n] and q[n][n].
*/
void Calibrator::svd(int m, int n, double **a, double **p, double *d, double **q)
{
	int             flag, i, its, j, jj, k, l, nm, nm1 = n - 1, mm1 = m - 1;
	double          c, f, h, s, x, y, z;
	double          anorm = 0, g = 0, scale = 0;
	//double         *r = tvector_alloc(0, n, double);
	double			*r = (double*)malloc(sizeof(double)*n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		p[i][j] = a[i][j];
	//for (i = m; i < n; i++)
	//                p[i][j] = 0;

	/* Householder reduction to bidigonal form */
	for (i = 0; i < n; i++)
	{
		l = i + 1;
		r[i] = scale * g;
		g = s = scale = 0.0;
		if (i < m)
		{
			for (k = i; k < m; k++)
				scale += fabs(p[k][i]);
			if (scale)
			{
				for (k = i; k < m; k++)
				{
					p[k][i] /= scale;
					s += p[k][i] * p[k][i];
				}
				f = p[i][i];
				g = -SIGN(sqrt(s), f);
				h = f * g - s;
				p[i][i] = f - g;
				if (i != nm1)
				{
					for (j = l; j < n; j++)
					{
						for (s = 0.0, k = i; k < m; k++)
							s += p[k][i] * p[k][j];
						f = s / h;
						for (k = i; k < m; k++)
							p[k][j] += f * p[k][i];
					}
				}
				for (k = i; k < m; k++)
					p[k][i] *= scale;
			}
		}
		d[i] = scale * g;
		g = s = scale = 0.0;
		if (i < m && i != nm1)
		{
			for (k = l; k < n; k++)
				scale += fabs(p[i][k]);
			if (scale)
			{
				for (k = l; k < n; k++)
				{
					p[i][k] /= scale;
					s += p[i][k] * p[i][k];
				}
				f = p[i][l];
				g = -SIGN(sqrt(s), f);
				h = f * g - s;
				p[i][l] = f - g;
				for (k = l; k < n; k++)
					r[k] = p[i][k] / h;
				if (i != mm1)
				{
					for (j = l; j < m; j++)
					{
						for (s = 0.0, k = l; k < n; k++)
							s += p[j][k] * p[i][k];
						for (k = l; k < n; k++)
							p[j][k] += s * r[k];
					}
				}
				for (k = l; k < n; k++)
					p[i][k] *= scale;
			}
		}
		anorm = MAX(anorm, fabs(d[i]) + fabs(r[i]));
	}

	/* Accumulation of right-hand transformations */
	for (i = n - 1; i >= 0; i--)
	{
		if (i < nm1)
		{
			if (g)
			{
				for (j = l; j < n; j++)
					q[j][i] = (p[i][j] / p[i][l]) / g;
				for (j = l; j < n; j++)
				{
					for (s = 0.0, k = l; k < n; k++)
						s += p[i][k] * q[k][j];
					for (k = l; k < n; k++)
						q[k][j] += s * q[k][i];
				}
			}
			for (j = l; j < n; j++)
				q[i][j] = q[j][i] = 0.0;
		}
		q[i][i] = 1.0;
		g = r[i];
		l = i;
	}
	/* Accumulation of left-hand transformations */
	for (i = n - 1; i >= 0; i--)
	{
		l = i + 1;
		g = d[i];
		if (i < nm1)
			for (j = l; j < n; j++)
			p[i][j] = 0.0;
		if (g)
		{
			g = 1.0 / g;
			if (i != nm1)
			{
				for (j = l; j < n; j++)
				{
					for (s = 0.0, k = l; k < m; k++)
						s += p[k][i] * p[k][j];
					f = (s / p[i][i]) * g;
					for (k = i; k < m; k++)
						p[k][j] += f * p[k][i];
				}
			}
			for (j = i; j < m; j++)
				p[j][i] *= g;
		}
		else
			for (j = i; j < m; j++)
			p[j][i] = 0.0;
		++p[i][i];
	}
	/* diagonalization of the bidigonal form */
	for (k = n - 1; k >= 0; k--)
	{                       /* loop over singlar values */
		for (its = 0; its < 30; its++)
		{               /* loop over allowed iterations */
			flag = 1;
			for (l = k; l >= 0; l--)
			{       /* test for splitting */
				nm = l - 1;     /* note that r[l] is always
								* zero */
				if (fabs(r[l]) + anorm == anorm)
				{
					flag = 0;
					break;
				}
				if (fabs(d[nm]) + anorm == anorm)
					break;
			}
			if (flag)
			{
				c = 0.0;        /* cancellation of r[l], if
								* l>1 */
				s = 1.0;
				for (i = l; i <= k; i++)
				{
					f = s * r[i];
					if (fabs(f) + anorm != anorm)
					{
						g = d[i];
						h = radius(f, g);
						d[i] = h;
						h = 1.0 / h;
						c = g * h;
						s = (-f * h);
						for (j = 0; j < m; j++)
						{
							y = p[j][nm];
							z = p[j][i];
							p[j][nm] = y * c + z * s;
							p[j][i] = z * c - y * s;
						}
					}
				}
			}
			z = d[k];
			if (l == k)
			{       /* convergence */
				if (z < 0.0)
				{
					d[k] = -z;
					for (j = 0; j < n; j++)
						q[j][k] = (-q[j][k]);
				}
				break;
			}
			if (its == 30)
			{
				//error("svd: No convergence in 30 svd iterations", non_fatal);
				return;
			}
			x = d[l];       /* shift from bottom 2-by-2 minor */
			nm = k - 1;
			y = d[nm];
			g = r[nm];
			h = r[k];
			f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
			g = radius(f, 1.0);
			/* next QR transformation */
			f = ((x - z) * (x + z) + h * ((y / (f + SIGN(g, f))) - h)) / x;
			c = s = 1.0;
			for (j = l; j <= nm; j++)
			{
				i = j + 1;
				g = r[i];
				y = d[i];
				h = s * g;
				g = c * g;
				z = radius(f, h);
				r[j] = z;
				c = f / z;
				s = h / z;
				f = x * c + g * s;
				g = g * c - x * s;
				h = y * s;
				y = y * c;
				for (jj = 0; jj < n; jj++)
				{
					x = q[jj][j];
					z = q[jj][i];
					q[jj][j] = x * c + z * s;
					q[jj][i] = z * c - x * s;
				}
				z = radius(f, h);
				d[j] = z;       /* rotation can be arbitrary
								* id z=0 */
				if (z)
				{
					z = 1.0 / z;
					c = f * z;
					s = h * z;
				}
				f = (c * g) + (s * y);
				x = (c * y) - (s * g);
				for (jj = 0; jj < m; jj++)
				{
					y = p[jj][j];
					z = p[jj][i];
					p[jj][j] = y * c + z * s;
					p[jj][i] = z * c - y * s;
				}
			}
			r[l] = 0.0;
			r[k] = f;
			d[k] = x;
		}
	}
	free(r);

	// dhli add: the original code does not sort the eigen value
	// should do that and change the eigen vector accordingly

}

// r is result matrix
void Calibrator::matrix_multiply33(double a[][3], double b[][3], double r[][3])
{
	int i, j;
	double result[9];
	double v = 0;
	for (j = 0; j < 3; j++) {
		for (i = 0; i < 3; i++) {
			v = a[j][0] * b[0][i];
			v += a[j][1] * b[1][i];
			v += a[j][2] * b[2][i];
			result[j * 3 + i] = v;
		}
	}
	for (i = 0; i < 3; i++) {
		r[i][0] = result[i * 3];
		r[i][1] = result[i * 3 + 1];
		r[i][2] = result[i * 3 + 2];
	}
}

// r is result matrix
void Calibrator::affine_matrix_inverse(double a[][3], double r[][3])
{
	double det22 = a[0][0] * a[1][1] - a[0][1] * a[1][0];
	r[0][0] = a[1][1] / det22;
	r[0][1] = -a[0][1] / det22;
	r[1][0] = -a[1][0] / det22;
	r[1][1] = a[0][0] / det22;

	r[2][0] = r[2][1] = 0;
	r[2][2] = 1 / a[2][2];

	r[0][2] = -r[2][2] * (r[0][0] * a[0][2] + r[0][1] * a[1][2]);
	r[1][2] = -r[2][2] * (r[1][0] * a[0][2] + r[1][1] * a[1][2]);
}

/*
* Send point to mapper.
*/

void Calibrator::homography_map_point(double x, double y)
{
	CvPoint p;
	p.x = x;
	p.y = y;
	
	m.homography_map_point(map_matrix, p);
}
