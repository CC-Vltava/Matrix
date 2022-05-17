#include <iostream>
#include <vector>
#include <complex>
using namespace std;

#define PII pair<int, int>
#define fir first
#define sec second
#define ma(a, b) make_pair(a, b)

#define ll long long
#define db double

class CustomType
{
};

//因为我没找到c++里面的Complex怎么用，所以就自己写了一个
class Complex
{
private:
	db real, image;

public:
	Complex();			 //普通构造函数，建立一个real和image都为0的complex
	Complex(db a, db b); //通过给定值构造complex

	db GetReal() const;		 //获得实部
	db GetImage() const;	 //获得虚部
	void SetReal(db value);	 //设置实部
	void SetImage(db value); //设置虚部
};
// Complex和Complex的四则运算
Complex operator+(const Complex &a, const Complex &b);
Complex operator-(const Complex &a, const Complex &b);
Complex operator*(const Complex &a, const Complex &b);
Complex operator/(const Complex &c1, const Complex &c2);

class ValueType
{
private:
	int type; // type 从1开始，分别对应下面4种类型（我现在只有处理到3的情况过）
	ll LongLongValue;
	db DoubleValue;
	Complex ComplexValue;
	CustomType CustomValue;

public:
	//初始化
	ValueType();
	explicit ValueType(int a);

	//各种get函数，获得valuetype里面的值
	int GetType() const;
	ll GetLongLongValue() const;
	db GetDoubleValue() const;
	Complex GetComplexValue() const;
	CustomType GetCustomValue() const;

	//各种set函数，设置valuetype里面的值
	void SetType(int value);
	void SetLongLongValue(ll value);
	void SetDoubleValue(db value);
	void SetComplexValue(Complex value);
	void SetCustomValue(CustomType value);

	//这个是把当前的类型向上升级一个等级，最高升到3级
	void UpGrade();
};

//这个是解决Complex无法比较大小的问题
bool operator<(const Complex &a, const Complex &b);

//下面两个是ll和db与Complex乘除法的重载运算符
Complex operator*(const ll &a, const Complex &b);
Complex operator*(const db &a, const Complex &b);
Complex operator/(const Complex &a, const ll &b);
Complex operator/(const Complex &a, const double &b);

//下面两个是ll和db和Complex与valuetype的重载运算符，返回的valuetype是较高类型的type Complex > double > long long
ValueType operator*(const ll &a, const ValueType &b);
ValueType operator*(const db &a, const ValueType &b);
ValueType operator*(const Complex &a, const ValueType &b);
ValueType operator/(const ValueType &b, const ll &a);
ValueType operator/(const ValueType &b, const db &a);
ValueType operator/(const ValueType &b, const Complex &a);

//下面是valuetype之间的运算，不要求两者type相同，返回较高的type
ValueType operator+(ValueType a, ValueType b);
ValueType operator-(ValueType a, ValueType b);
ValueType operator*(ValueType a, ValueType b);
ValueType operator/(ValueType a, ValueType b);

//矩阵部分
class Matrix
{
private:
	int row, col, type, isSparseMatrix; // ty指的是这个矩阵是普通矩阵还是稀疏矩阵,0对应普通矩阵
	vector<ValueType> MatrixValue;
	vector<PII> SparseMatrix; //稀疏矩阵只需要储存对应的位置
							  //注意，这里把向量看成一个行或者列为1的矩阵
public:
	//初始化
	Matrix();																						 //矩阵初始化，默认为long long 0*0的普通矩阵
	Matrix(int row, int col, int type);																 //创造一个给定大小和type的全零矩阵
	Matrix(int row, int col, int type, vector<ValueType> &value);									 //通过一个vec来更新普通矩阵
	Matrix(int row, int col, int type, const vector<ValueType> &value, const vector<PII> &position); //初始化一个稀疏矩阵

	// matrix中的get函数
	int GetElementNum() const;
	int GetRow() const;
	int GetCol() const;
	int GetType() const;
	int GetisSparseMatrix() const;
	int GetTotalSize() const;				//这个是获得的大小(注意！这里获得的是vector中含有的元素的个数，在稀疏矩阵中药注意！！！
	ValueType GetValue(int position) const; //这个是获得指定位置的值
	ValueType GetValue(int x, int y) const; //获得当前位置的值
	vector<ValueType> GetMatrixValue() const;
	vector<PII> GetSparseMatrix() const;

	// matrix中的set函数
	void SetCol(int a);
	void Setrow(int a);
	void SetType(int value);
	void SetValue(int x, int y, ValueType value);
	void SetValue(int position, ValueType value);
	void SetisSparseMatrix(bool judge);

	//给当前矩阵的类型升级
	void UpGrade();

	bool CheckSquare() const; //检查矩阵是否是方阵
	PII GetSize() const;	  //获得当前矩阵大小，返回一个pair

	ValueType GetMax(int axis = 0); //这里需要重载<，而且需要自己定义虚数比较大小的方式
	ValueType GetMin(int axis = 0);
	ValueType GetAverage(int axis = 0);
	ValueType GetSum(int axis = 0);
};
//有了各种get和set之后，就可以不使用friend类型了~

Matrix Reshape(const Matrix &a, int x, int y);

//数乘，注意返回的矩阵的类型是两者中较高的那个类型！Complex > double > long long
Matrix operator*(const ll Mul, const Matrix &matrix);
Matrix operator*(const Matrix &matrix, const ll Mul);
Matrix operator*(const db Mul, const Matrix &matrix);
Matrix operator*(const Matrix &matrix, const db Mul);
Matrix operator*(const Complex Mul, const Matrix &matrix);
Matrix operator*(const Matrix &matrix, const Complex Mul);

Matrix operator/(const Matrix &matrix, const ll Mul);
Matrix operator/(const Matrix &matrix, const db Mul);
Matrix operator/(const Matrix &matrix, const Complex Mul);

//这个是自定义类型的，不管他
Matrix operator*(const CustomType Mul, const Matrix &matrix);
Matrix operator*(const Matrix &matrix, const CustomType Mul);
Matrix operator/(const Matrix &matrix, const CustomType Mul);
//矩阵基本运算
Matrix operator+(const Matrix &a, const Matrix &b);
Matrix operator-(const Matrix &a, const Matrix &b);
Matrix operator*(const Matrix &a, const Matrix &b);

bool CheckSame(const Matrix &a, const Matrix &b);	  //检查两个矩阵大小是否相同
bool CheckMultiply(const Matrix &a, const Matrix &b); //检查两个矩阵是否可以相乘

Matrix Transposition(const Matrix &a); //矩阵转置
Matrix conjugation(const Matrix &a);   //求共轭矩阵
ValueType DotProduct(const Matrix &a, const Matrix &b);
Matrix CrossProduct(const Matrix &a, const Matrix &b); //向量✖️乘

Matrix Inverse(const Matrix &a);		//矩阵求逆
ValueType Eigenvalue(const Matrix &a);	//矩阵求特征值
Matrix Eigenvector(const Matrix &a);	//矩阵求特征向量
ValueType Trace(const Matrix &a);		//矩阵求trace
ValueType Determinant(const Matrix &a); //矩阵求行列式

Matrix Convolution(const Matrix &a, const Matrix &b); //两个矩阵卷积
