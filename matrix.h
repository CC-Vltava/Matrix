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
	Complex()
	{
		real = image = 0;
	}
	Complex(db a, db b)
	{
		real = a;
		image = b;
	}

	db GetReal() const
	{
		return real;
	}
	db GetImage() const
	{
		return image;
	}
	void SetReal(db value)
	{
		real = value;
	}
	void SetImage(db value)
	{
		image = value;
	}
};
// Complex的各种加减法
Complex operator+(const Complex &a, const Complex &b)
{
	return {a.GetReal() + b.GetReal(), a.GetImage() + b.GetImage()};
}
Complex operator-(const Complex &a, const Complex &b)
{
	return {a.GetReal() - b.GetReal(), a.GetImage() - b.GetImage()};
}
Complex operator*(const Complex &a, const Complex &b)
{
	return {a.GetReal() * b.GetReal() - a.GetImage() * b.GetImage(), a.GetImage() * b.GetReal() + a.GetReal() * b.GetImage()};
}

class ValueType
{
private:
	int type; // type 从1开始，分别对应下面4种类型（我现在只有处理到3的情况过）
	ll LongLongValue;
	db DoubleValue;
	Complex ComplexValue;
	CustomType CustomValue;

public:
	ValueType()
	{
		type = 1;
		LongLongValue = 0;
		DoubleValue = 0;
		ComplexValue = {0, 0};
	}

	//获得valuetype里面的值
	int GetType() const
	{
		return type;
	}
	ll GetLongLongValue() const
	{
		return LongLongValue;
	}
	db GetDoubleValue() const
	{
		return DoubleValue;
	}
	Complex GetComplexValue()
	{
		return ComplexValue;
	}
	CustomType GetCustomValue()
	{
		return CustomValue;
	}
	//设置valuetype里面的值
	void SetType(int value)
	{
		type = value;
	}
	void SetLongLongValue(ll value)
	{
		LongLongValue = value;
	}
	void SetDoubleValue(db value)
	{
		DoubleValue = value;
	}
	void SetComplexValue(Complex value)
	{
		ComplexValue = value;
	}
	void SetCustomValue(CustomType value)
	{
		CustomValue = value;
	}
	//这个是把当前的类型向上升级一个等级，最高升到3级
	void UpGrade()
	{
		if (type == 1)
		{
			DoubleValue = (db)LongLongValue;
			++type;
		}
		else if (type == 2)
		{
			ComplexValue.SetReal(DoubleValue);
			ComplexValue.SetImage(0);
			++type;
		}
	}
};

bool operator<(const Complex &a, const Complex &b) //这个是解决Complex无法比较大小的问题
{
	return a.GetReal() < b.GetReal();
}

//下面两个是ll和db与Complex相乘的重载运算符
Complex operator*(const ll &a, const Complex &b)
{
	return {b.GetReal() * (db)a, b.GetImage() * (db)a};
}
Complex operator*(const db &a, const Complex &b)
{
	return {b.GetReal() * a, b.GetImage() * a};
}

//下面两个是ll和db和Complex与valuetype的重载运算符，返回的valuetype是较高类型的type Complex > double > long long
ValueType operator*(const ll &a, const ValueType &b)
{
	ValueType c = b;
	if (c.GetType() == 1)
		c.SetLongLongValue(a * c.GetLongLongValue());
	else if (c.GetType() == 2)
		c.SetDoubleValue((db)a * c.GetDoubleValue());
	else
		c.SetComplexValue(a * c.GetComplexValue());
	return c;
}
ValueType operator*(const db &a, const ValueType &b)
{
	ValueType c = b;
	if (c.GetType() == 1)
		c.UpGrade();
	if (c.GetType() == 2)
		c.SetDoubleValue(a * c.GetDoubleValue());
	else
		c.SetComplexValue(a * c.GetComplexValue());
	return c;
}
ValueType operator*(const Complex &a, const ValueType &b)
{
	ValueType c = b;
	if (c.GetType() == 1)
		c.UpGrade();
	if (c.GetType() == 2)
		c.UpGrade();
	c.SetComplexValue(a * c.GetComplexValue());
	return c;
}
//下面是valuetype之间的运算，不要求两者type相同，返回较高的type
ValueType operator+(ValueType a, ValueType b)
{
	while (a.GetType() < b.GetType())
		a.UpGrade();
	while (a.GetType() > b.GetType())
		b.UpGrade();
	if (a.GetType() == 1)
		a.SetLongLongValue(a.GetLongLongValue() + b.GetLongLongValue());
	else if (a.GetType() == 2)
		a.SetDoubleValue(a.GetDoubleValue() + b.GetDoubleValue());
	else
		a.SetComplexValue(a.GetComplexValue() + b.GetComplexValue());
	return a;
}
ValueType operator-(ValueType a, ValueType b)
{
	while (a.GetType() < b.GetType())
		a.UpGrade();
	while (a.GetType() > b.GetType())
		b.UpGrade();
	if (a.GetType() == 1)
		a.SetLongLongValue(a.GetLongLongValue() - b.GetLongLongValue());
	else if (a.GetType() == 2)
		a.SetDoubleValue(a.GetDoubleValue() - b.GetDoubleValue());
	else
		a.SetComplexValue(a.GetComplexValue() - b.GetComplexValue());
	return a;
}
ValueType operator*(ValueType a, ValueType b)
{
	while (a.GetType() < b.GetType())
		a.UpGrade();
	while (a.GetType() > b.GetType())
		b.UpGrade();
	if (a.GetType() == 1)
		a.SetLongLongValue(a.GetLongLongValue() * b.GetLongLongValue());
	else if (a.GetType() == 2)
		a.SetDoubleValue(a.GetDoubleValue() * b.GetDoubleValue());
	else
		a.SetComplexValue(a.GetComplexValue() * b.GetComplexValue());
	return a;
}

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
	Matrix() //矩阵初始化，默认为long long 0*0的普通矩阵
	{
		type = 1;
		isSparseMatrix = 0;
		MatrixValue.clear();
		SparseMatrix.clear();
		row = 0;
		col = 0;
	}
	Matrix(int row, int col, int type) //创造一个给定大小和type的全零矩阵
	{
		this->row = row;
		this->col = col;
		this->type = type;
		ValueType input;
		input.SetType(type);
		for (int i = 1; i <= row * col; i++)
			MatrixValue.push_back(input);
		this->isSparseMatrix = 0;
	}
	Matrix(int row, int col, int type, vector<ValueType> &value) //通过一个vec来更新普通矩阵
	{
		if (value.size() % row != 0)
		{
			throw("Size not Divide Error!");
		}
		this->row = row;
		this->col = col;
		this->type = type;
		this->MatrixValue = value;
		this->isSparseMatrix = 0;
	}
	Matrix(int row, int col, int type, const vector<ValueType> &value, const vector<PII> &position) //初始化一个稀疏矩阵
	{
		if (value.size() != position.size())
		{
			throw("Size not Same Error!");
		}
		this->type = type;
		this->isSparseMatrix = 1;
		this->MatrixValue = value;
		this->SparseMatrix = position;
		this->row = row;
		this->col = col;
	}
	// matrix中的get函数
	int GetRow() const
	{
		return row;
	}
	int GetCol() const
	{
		return col;
	}
	int GetType() const
	{
		return type;
	}
	int GetisSparseMatrix() const
	{
		return isSparseMatrix;
	}
	int GetTotalSize() const //这个是获得总的大小
	{
		return row * col;
	}
	ValueType GetValue(int position) const //这个是获得指定位置的值
	{
		return MatrixValue[position];
	}
	ValueType GetValue(int x, int y) const //获得当前位置的值
	{
		if (x > row || y > col || (x - 1) * col + y > this->GetTotalSize())
		{
			throw("Not in the matrix!");
		}
		return MatrixValue[(x - 1) * col + y - 1];
	}
	// matrix中的set函数
	void SetValue(int x, int y, ValueType value)
	{
		if (x > row || y > col || (x - 1) * col + y > this->GetTotalSize())
		{
			throw("Not in the matrix!");
		}
		MatrixValue[(x - 1) * col + y - 1] = value;
	}
	void SetType(int value)
	{
		type = value;
	}
	void SetValue(int position, ValueType value)
	{
		MatrixValue[position] = value;
	}
	//对row和col的设置在reshape中写就行了

	//给当前矩阵的类型升级
	void UpGrade()
	{
		if (type == 3)
			return;
		for (int i = 0; i < MatrixValue.size(); i++)
			MatrixValue[i].UpGrade();
		type++;
	}

	bool CheckSquare() const //检查矩阵是否是方阵
	{
		return row == col;
	}
	PII GetSize() const //获得当前矩阵大小，返回一个pair
	{
		return make_pair(row, col);
	}

	ValueType GetMax(int axis = 0); //这里需要重载<，而且需要自己定义虚数比较大小的方式
	ValueType GetMin(int axis = 0);
	ValueType GetAverage(int axis = 0);
	ValueType GetSum(int axis = 0);

	void reshape(int row = -1, int col = -1);
	void slicing();
};
//有了各种get和set之后，就可以不使用friend类型了~

//数乘，注意返回的矩阵的类型是两者中较高的那个类型！Complex > double > long long
Matrix operator*(const ll Mul, const Matrix &matrix)
{
	Matrix answer = matrix;
	for (int i = 0; i < matrix.GetTotalSize(); i++)
		answer.SetValue(i, Mul * answer.GetValue(i));
	return answer;
}
Matrix operator*(const Matrix &matrix, const ll Mul)
{
	return Mul * matrix;
}

Matrix operator*(const db Mul, const Matrix &matrix)
{
	Matrix answer = matrix;
	if (answer.GetType() == 1)
	{
		answer.UpGrade();
	}
	for (int i = 0; i < answer.GetTotalSize(); i++)
		answer.SetValue(i, Mul * answer.GetValue(i));
	return answer;
}
Matrix operator*(const Matrix &matrix, const db Mul)
{
	return Mul * matrix;
}

Matrix operator*(const Complex Mul, const Matrix &matrix)
{
	Matrix answer = matrix;
	if (answer.GetType() == 1)
	{
		answer.UpGrade();
	}
	if (answer.GetType() == 2)
	{
		answer.SetType(answer.GetType() + 1);
		answer.UpGrade();
	}
	for (int i = 0; i < answer.GetTotalSize(); i++)
		answer.SetValue(i, Mul * answer.GetValue(i));
	return answer;
}
Matrix operator*(const Matrix &matrix, const Complex Mul)
{
	return Mul * matrix;
}
//这个是自定义类型的，不管他
Matrix operator*(const CustomType Mul, const Matrix &matrix);
Matrix operator*(const Matrix &matrix, const Complex Mul);

//矩阵基本运算
Matrix operator+(const Matrix &a, const Matrix &b)
{
	if (a.GetSize() != b.GetSize())
	{
		throw("Size not Same Error!");
	}
	Matrix answer = a;
	while (answer.GetType() < b.GetType())
	{
		answer.UpGrade();
	}
	for (int i = 0; i < answer.GetTotalSize(); i++)
		answer.SetValue(i, b.GetValue(i) + answer.GetValue(i));
	return answer;
}
Matrix operator-(const Matrix &a, const Matrix &b)
{
	if (a.GetSize() != b.GetSize())
	{
		throw("Size not Same Error!");
	}
	Matrix answer = a;
	while (answer.GetType() < b.GetType())
	{
		answer.UpGrade();
	}
	for (int i = 0; i < answer.GetTotalSize(); i++)
		answer.SetValue(i, answer.GetValue(i) - b.GetValue(i));
	return answer;
}
Matrix operator*(const Matrix &a, const Matrix &b)
{
	if (a.GetCol() != b.GetRow())
	{
		throw("Size not Same Error!");
	}
	Matrix answer = Matrix(a.GetRow(), b.GetCol(), max(a.GetType(), b.GetType()));
	for (int i = 1; i <= a.GetRow(); i++)
		for (int j = 1; j <= b.GetCol(); j++)
			for (int k = 1; k <= a.GetCol(); k++)
				answer.SetValue(i, j, answer.GetValue(i, j) + a.GetValue(i, k) * b.GetValue(k, j));
	return answer;
}

bool CheckSame(const Matrix &a, const Matrix &b) //检查两个矩阵大小是否相同
{
	return a.GetSize() == b.GetSize();
}
bool CheckMultiply(const Matrix &a, const Matrix &b) //检查两个矩阵是否可以相乘
{
	return a.GetCol() == b.GetRow();
}

Matrix Transposition(const Matrix &a); //矩阵转置
Matrix conjugation(const Matrix &a);   //求共轭矩阵
ValueType DotProduct(const Matrix &a, const Matrix &b);
Matrix CrossProduct(const Matrix &a, const Matrix &b); //向量✖️乘

Matrix Inverse(const Matrix &a);		//矩阵求逆
ValueType Eigenvalue(const Matrix &a);	//矩阵求特征值
Matrix Eigenvector(const Matrix &a);	//矩阵求特征向量
ValueType Trace(const Matrix &a);		//矩阵求trace
ValueType Determinant(const Matrix &a); //矩阵求行列式

Matrix Convolution(const Matrix &a, const Matrix &b);
