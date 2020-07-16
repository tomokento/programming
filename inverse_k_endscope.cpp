///////////////////////////////////////////////////////////
//DH parameters //
//    twist | length |offset | angle
//  i  | a | d | A | theta
//  1  | PI | 0 | 0 | theta1
//  2  | 0 | l1(0.03) | 0 | theta2
//  3  | 0 | l2(0.03) | 0 | theta3
//  4  | 0 | l3(0.03) | 0 | theta4
//  5  | 0 | l4(0.03) | 0 | 0
//////////////////////////////////////////////////////////////


//すべてのリンクでの座標を表示
//    link1   link2  link3  link4
//x
//y
//z

#include <iostream>
#include <cmath>
#include "Eigen/Dense"

//std::もしくはEigen::を先頭に書く手間を省いている。
using namespace std;
using namespace Eigen;

//各々のリンクの長さ
const double L1=1.0;
const double L2=1.0;
const double L3=1.0;
const double L4=1.0;

int main()
{
	//std::Vector3d 三次元ベクトルの
	Vector3d  p_frist(0,0,0); //三次元ベクトルの初期値
	Vector3d	pg(0.0, 0, 1); //  Goal hand position　三次元ベクトル
	//4次元ベクトルについて
	Vector4d	qi(0.0,0.0,0.0,0.0); //  Initial joint angle: {q1, q2, q3,q4} [rad]
	Vector4d	qf;//  Final joint angle: {q1, q2, q3,q4} [rad]
	//結果的に得られる各角度
	//Vector3d	pf;//  Final hand position: {x, y, z} [m]

	MatrixXd	pf(3,5);//  Final hand position: {x, y, z} [m]　
	//3*5行列の初期化
  //p_firstの(0,0)(0,1)(0,2)の値をpfのpf(0,0)(1,0)(2,0)に代入
	//　0 - - - -
	//　0 - - - -
	//　0 - - - - の状態。
  for(int i=0; i< 3 ;i++){
 	pf(i,0)= p_frist(i);
	}

	qf = inverse_kinematics(pg, qi);

	pf.col(4) = forward_kinematics(qf);

	pf.col(1)= forward_kinematics1link(qf(0));
	Vector2d p_link2(qf(0),qf(1));
  pf.col(2)= forward_kinematics2link(p_link2);
	Vector3d p_link3(qf(0),qf(1),qf(2));
	pf.col(3)= forward_kinematics3link(p_link3);

	cout << "Initial joint angles" << endl << qi << endl;
	cout << "Goal hand position" << endl << pg << endl;
	cout << "Final joint angles" << endl << qf << endl;
	cout << "Final hand position(all position)" << endl << pf << endl;

	return(0);
}


Matrix4d	DH(double twist, double length, double angle, double offset)
{
	Matrix4d	t;

	t(0, 0) =  cos(angle);
	t(0, 1) = -sin(angle);
	t(0, 2) =  0.0;
	t(0, 3) =  length;

	t(1, 0) =  sin(angle) * cos(twist);
	t(1, 1) =  cos(angle) * cos(twist);
	t(1, 2) = -sin(twist);
	t(1, 3) = -offset * sin(twist);

	t(2, 0) =  sin(angle) * sin(twist);
	t(2, 1) =  cos(angle) * sin(twist);
	t(2, 2) =  cos(twist);
	t(2, 3) =  offset * cos(twist);

	t(3, 0) =  0.0;
	t(3, 1) =  0.0;
	t(3, 2) =  0.0;
	t(3, 3) =  1.0;
	return(t);
}
Vector3d forward_kinematics3link(const Vector3d& q)
{
	Matrix4d	t01, t12, t23, t34, t45, t05;
  //      twist | length | angle | offset
	t01 = DH( 0.0,     0, q(0),  0.0 );
	t12 = DH( M_PI_2, L1, q(1), 0.0 );
	t23 = DH( 0.0,    L2, q(2), 0.0 );
	t34 = DH( 0.0,    L3, 0,  0.0 );
	t05 = t01 * t12 * t23 * t34 ;


	Vector4d	o(0.0, 0.0, 0.0, 1.0);
	Vector4d	p;
	p = t05 * o;
	return(p.head(3));
}

Vector3d forward_kinematics2link(const Vector2d& q)
{
	Matrix4d	t01, t12, t23, t34,t45, t05;
  //      twist | length | angle | offset
	t01 = DH( 0.0,     0, q(0),  0.0 );
	t12 = DH( M_PI_2, L1, q(1), 0.0 );
	t23 = DH( 0.0,    L2, 0, 0.0 );

	t05 = t01 * t12 * t23 ;


	Vector4d	o(0.0, 0.0, 0.0, 1.0);
	Vector4d	p;
	p = t05 * o;
	return(p.head(3));
}
Vector3d forward_kinematics1link(const double  &q)
{
	Matrix4d	t01, t12, t23, t34,t45, t05;
  //      twist | length | angle | offset
	t01 = DH( 0.0,     0, q,  0.0 );
	t12 = DH( M_PI_2, L1, 0, 0.0 );
	t05 = t01 * t12 ;
	Vector4d	o(0.0, 0.0, 0.0, 1.0);
	Vector4d	p;
	p = t05 * o;
	return(p.head(3));
}
Vector3d forward_kinematics(const VectorXd& q)
{
	Matrix4d	t01, t12, t23, t34,t45, t05;
  //      twist | length | angle | offset
	t01 = DH( 0.0,     0, q(0),  0.0 );
	t12 = DH( M_PI_2, L1, q(1), 0.0 );
	t23 = DH( 0.0,    L2, q(2), 0.0 );
	t34 = DH( 0.0,    L3, q(3),  0.0 );
  t45 = DH(0.0 ,    L4, 0.0 ,  0.0);
	t05 = t01 * t12 * t23 * t34 * t45;


	Vector4d	o(0.0, 0.0, 0.0, 1.0);
	Vector4d	p;
	p = t05 * o;
	return(p.head(3));
}
MatrixXd jacobian(const Vector4d& q)
{

	const double dq = 1E-9;
	MatrixXd	j(3,4);
	Vector4d dq1(dq, 0.0, 0.0,0.0), dq2(0.0, dq, 0.0 , 0.0), dq3(0.0, 0.0, dq , 0.0),dq4(0.0, 0.0,0.0,dq);
	Vector3d p, pdp1, pdp2, pdp3,pdp4;

	p = forward_kinematics(q); 	//	元のqによる手先の位置ベクトル
	pdp1 = forward_kinematics(q + dq1); 	//	q+dq1 (q1がごく少量増加)による手先の位置ベクトル
	pdp2 = forward_kinematics(q + dq2);
	pdp3 = forward_kinematics(q + dq3);
  pdp4 = forward_kinematics(q + dq4);
	//	dx/dt = ((x+dx)-x)/((q+dq1) - q1)
	//	dy/dt = ((y+dy)-y)/((q+dq1) - q1)
	//	dz/dt = ((z+dz)-z)/((q+dq1) - q1)
	j.col(0) = (pdp1 - p) / dq;
	j.col(1) = (pdp2 - p) / dq;
	j.col(2) = (pdp3 - p) / dq;
	j.col(3) = (pdp4 - p) / dq;
	return(j);
}
MatrixXd pseudo_inverse(const MatrixXd& j)
{
int m= j.rows();
int n= j.cols();

MatrixXd j_pinv(n,m);
MatrixXd m_sigma_plus(n,m);
MatrixXd Zero(n,m);
VectorXd sigma(m);
VectorXd sigma_inverse(m);	//特異値行列と逆特異値行列のの対角成
JacobiSVD< MatrixXd >	svd(j, ComputeFullU | ComputeFullV); 	//	与えられた行列の特異値分解


m_sigma_plus = Zero ;
sigma = svd.singularValues();
	//	特異値行列の逆数から逆特異値行列を作る
 for(int i=0;i<m;i++){
   for(int j=0;j<m;j++){
     if(i==j){
       m_sigma_plus(i,j) = sigma(i) ;
     }
   }
 }

	for (int i = 0; i < 3; ++i) {
		//	対角成分の値が小さかったら，０を与える
		if (1E-9 > fabs(sigma(i))) {
			sigma_inverse(i) = 0.0;
		}

		//	対角成分の値が十分大きかったら，特異値の逆数を与える
		else
		{
			sigma_inverse(i) = 1.0 / sigma(i);
		}
	}

	j_pinv = svd.matrixV() * m_sigma_plus * svd.matrixU().transpose();

	return(j_pinv);
}
Vector4d inverse_kinematics(const Vector3d& pg, const Vector4d& qi)
{
	const int T = 100;
	double	a = 0.1;  //逆運動学計算のための係数
	Vector3d	p;	//現在の手先の位置ベクトル
	Vector4d	q;	//現在の関節角度ベクトル
	Vector4d	qd; //関節角度更新量ベクトル
	MatrixXd	j(4,3);   //ヤコビアン
	q = qi;  //	初期関節角度を現在の関節角度ベクトルに与える


	for (int t = 0; t < T; ++t) {	//	逆運動学のための繰り返し計算
		p = forward_kinematics(q);	//	順運動学
		j = jacobian(q);	//ヤコビアン
		//	関節角度の更新
		//	単純な逆行列だと特異姿勢のときに逆行列が定まらない
    q += a * pseudo_inverse(j) * (pg - p);
  }
  //	最終的に得られた関節角度
  return(q);
}
