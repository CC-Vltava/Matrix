#include "matrix.h"
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

Complex::Complex()
{
    real = image = 0;
}
Complex::Complex(db a, db b)
{
    real = a;
    image = b;
}

db Complex::GetReal() const
{
    return real;
}
db Complex::GetImage() const
{
    return image;
}
void Complex::SetReal(db value)
{
    real = value;
}
void Complex::SetImage(db value)
{
    image = value;
}
// Complex的四则运算
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
Complex operator/(const Complex &c1, const Complex &c2)
{
    double a = c1.GetReal();
    double b = c1.GetImage();
    double c = c2.GetReal();
    double d = c2.GetImage();
    return {(a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d)};
}

ValueType::ValueType()
{
    type = 1;
    LongLongValue = 0;
    DoubleValue = 0;
    ComplexValue = {0, 0};
}
ValueType::ValueType(int a)
{
    type = a;
    LongLongValue = 0;
    DoubleValue = 0;
    ComplexValue = {0, 0};
}

//获得valuetype里面的值
int ValueType::GetType() const
{
    return type;
}
ll ValueType::GetLongLongValue() const
{
    return LongLongValue;
}
db ValueType::GetDoubleValue() const
{
    return DoubleValue;
}
Complex ValueType::GetComplexValue() const
{
    return ComplexValue;
}
CustomType ValueType::GetCustomValue() const
{
    return CustomValue;
}
//设置valuetype里面的值
void ValueType::SetType(int value)
{
    type = value;
}
void ValueType::SetLongLongValue(ll value)
{
    LongLongValue = value;
}
void ValueType::SetDoubleValue(db value)
{
    DoubleValue = value;
}
void ValueType::SetComplexValue(Complex value)
{
    ComplexValue = value;
}
void ValueType::SetCustomValue(CustomType value)
{
    CustomValue = value;
}
//这个是把当前的类型向上升级一个等级，最高升到3级
void ValueType::UpGrade()
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

bool operator<(const Complex &a, const Complex &b) //这个是解决Complex无法比较大小的问题
{
    return a.GetReal() < b.GetReal();
}

//下面两个是ll和db与Complex乘除法的重载运算符
Complex operator*(const ll &a, const Complex &b)
{
    return {b.GetReal() * (db)a, b.GetImage() * (db)a};
}
Complex operator*(const db &a, const Complex &b)
{
    return {b.GetReal() * a, b.GetImage() * a};
}
Complex operator/(const Complex &a, const ll &b)
{
    return {a.GetReal() / (db)b, a.GetImage() / (db)b};
}

Complex operator/(const Complex &a, const double &b)
{
    return {a.GetReal() / b, a.GetImage() / b};
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
ValueType operator/(const ValueType &b, const ll &a)
{
    ValueType c = b;
    if (c.GetType() == 1)
        c.SetLongLongValue(c.GetLongLongValue() / a);
    else if (c.GetType() == 2)
        c.SetDoubleValue(c.GetDoubleValue() / (db)a);
    else
        c.SetComplexValue(c.GetComplexValue() / a);
    return c;
}

ValueType operator/(const ValueType &b, const db &a)
{
    ValueType c = b;
    if (c.GetType() == 1)
        c.UpGrade();
    if (c.GetType() == 2)
        c.SetDoubleValue(c.GetDoubleValue() / a);
    else
        c.SetComplexValue(c.GetComplexValue() / a);
    return c;
}

ValueType operator/(const ValueType &b, const Complex &a)
{
    ValueType c = b;
    if (c.GetType() == 1)
        c.UpGrade();
    if (c.GetType() == 2)
        c.UpGrade();
    c.SetComplexValue(c.GetComplexValue() / a);
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
ValueType operator/(ValueType a, ValueType b)
{
    while (a.GetType() < b.GetType())
        a.UpGrade();
    while (a.GetType() > b.GetType())
        b.UpGrade();
    if (a.GetType() == 1)
        a.SetLongLongValue(a.GetLongLongValue() / b.GetLongLongValue());
    else if (a.GetType() == 2)
        a.SetDoubleValue(a.GetDoubleValue() / b.GetDoubleValue());
    else
        a.SetComplexValue(a.GetComplexValue() / b.GetComplexValue());
    return a;
}

//矩阵部分

Matrix::Matrix() //矩阵初始化，默认为long long 0*0的普通矩阵
{
    type = 1;
    isSparseMatrix = 0;
    MatrixValue.clear();
    SparseMatrix.clear();
    row = 0;
    col = 0;
}
Matrix::Matrix(int row, int col, int type) //创造一个给定大小和type的全零矩阵
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
Matrix::Matrix(int row, int col, int type, vector<ValueType> &value) //通过一个vec来更新普通矩阵
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
Matrix::Matrix(int row, int col, int type, const vector<ValueType> &value, const vector<PII> &position) //初始化一个稀疏矩阵
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
int Matrix::GetElementNum() const
{
    return MatrixValue.size();
}

int Matrix::GetRow() const
{
    return row;
}
int Matrix::GetCol() const
{
    return col;
}
int Matrix::GetType() const
{
    return type;
}
int Matrix::GetisSparseMatrix() const
{
    return isSparseMatrix;
}
int Matrix::GetTotalSize() const //这个是获得总的大小
{
    return row * col;
}
ValueType Matrix::GetValue(int position) const //这个是获得指定位置的值
{
    return MatrixValue[position];
}
ValueType Matrix::GetValue(int x, int y) const //获得当前位置的值
{
    if (x > row || y > col || (x - 1) * col + y > this->GetTotalSize())
    {
        throw("Not in the matrix!");
    }
    return MatrixValue[(x - 1) * col + y - 1];
}
vector<ValueType> Matrix::GetMatrixValue() const
{
    return MatrixValue;
}
vector<PII> Matrix::GetSparseMatrix() const
{
    return SparseMatrix;
}
// matrix中的set函数
void Matrix::SetCol(int a)
{
    col = a;
}
void Matrix::Setrow(int a)
{
    row = a;
}
void Matrix::SetType(int value)
{
    type = value;
}
void Matrix::SetValue(int x, int y, ValueType value)
{
    if (x > row || y > col || (x - 1) * col + y > this->GetTotalSize())
    {
        throw("Not in the matrix!");
    }
    MatrixValue[(x - 1) * col + y - 1] = value;
}
void Matrix::SetValue(int position, ValueType value)
{
    MatrixValue[position] = value;
}
void Matrix::SetisSparseMatrix(bool judge)
{
    isSparseMatrix = judge;
}
//对row和col的设置在reshape中写就行了

//给当前矩阵的类型升级
void Matrix::UpGrade()
{
    if (type == 3)
        return;
    for (int i = 0; i < MatrixValue.size(); i++)
        MatrixValue[i].UpGrade();
    type++;
}

bool Matrix::CheckSquare() const //检查矩阵是否是方阵
{
    return row == col;
}
PII Matrix::GetSize() const //获得当前矩阵大小，返回一个pair
{
    return make_pair(row, col);
}

// to do````````````````````````````````````````````````````````````````````````````````````
ValueType Matrix::GetMax(int axis) {} //这里需要重载<，而且需要自己定义虚数比较大小的方式
ValueType Matrix::GetMin(int axis) {}
ValueType Matrix::GetAverage(int axis) {}
ValueType Matrix::GetSum(int axis) {}
// to do````````````````````````````````````````````````````````````````````````````````````

// reshape and slicing
Matrix Reshape(const Matrix &a, int x, int y)
{
    if (a.GetTotalSize() != x * y)
    {
        throw("Size can not match error!");
    }
    Matrix answer = Matrix(a);
    answer.Setrow(x);
    answer.SetCol(y);
    return answer;
}
// to do slicing````````````````````````````````````````````````````````````````````````

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

//矩阵除法
Matrix operator/(const Matrix &matrix, const ll Mul)
{
    Matrix answer = matrix;
    for (int i = 0; i < matrix.GetTotalSize(); i++)
        answer.SetValue(i, answer.GetValue(i) / Mul);
    return answer;
}

Matrix operator/(const Matrix &matrix, const db Mul)
{
    Matrix answer = matrix;
    if (answer.GetType() == 1)
    {
        answer.UpGrade();
    }
    for (int i = 0; i < answer.GetTotalSize(); i++)
        answer.SetValue(i, answer.GetValue(i) / Mul);
    return answer;
}

Matrix operator/(const Matrix &matrix, const Complex Mul)
{
    Matrix answer = matrix;
    if (answer.GetType() == 1)
    {
        answer.UpGrade();
    }
    if (answer.GetType() == 2)
    {
        answer.UpGrade();
    }
    for (int i = 0; i < answer.GetTotalSize(); i++)
        answer.SetValue(i, answer.GetValue(i) / Mul);
    return answer;
}

//这个是自定义类型的，不管他
Matrix operator*(const CustomType Mul, const Matrix &matrix) {}
Matrix operator*(const Matrix &matrix, const CustomType Mul) {}
Matrix operator/(const Matrix &matrix, const CustomType Mul) {}

//矩阵基本运算
Matrix operator+(const Matrix &a, const Matrix &b)
{
    if (CheckSame(a, b))
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
	if (CheckSame(a, b))
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
    if (CheckMultiply(a, b))
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

//填充稀疏矩阵
Matrix FillSparseMatrix(const Matrix &a)
{
    if (a.GetisSparseMatrix())
    {
        int type = a.GetType();
        int col = a.GetCol();
        int row = a.GetRow();
        Matrix answer = Matrix(row, col, type);
        answer.SetisSparseMatrix(false);
        vector<ValueType> value = a.GetMatrixValue();
        vector<PII> SparseMat = a.GetSparseMatrix();
        for (int i = 0; i < SparseMat.size(); ++i)
        {
            PII temp = SparseMat[i];
            ValueType tempValue = value[i];
            answer.SetValue(temp.first, temp.second, tempValue);
        }
        return answer;
    }
    Matrix answer = a;
    return answer;
}

//普通矩阵转换为稀疏矩阵
Matrix Sparse(const Matrix &a)
{
    if (!a.GetisSparseMatrix())
    {
        int type = a.GetType();
        int col = a.GetCol();
        int row = a.GetRow();
        Matrix answer = Matrix(row, col, type);
        vector<ValueType> value = answer.GetMatrixValue();
        vector<PII> SparseMat = answer.GetSparseMatrix();
        value.clear();
        SparseMat.clear();
        answer.SetisSparseMatrix(true);
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if ((type == 1 && a.GetValue(i, j).GetLongLongValue() == 0) ||
                    (type == 2 && a.GetValue(i, j).GetDoubleValue() == 0) ||
                    (type == 3 && a.GetValue(i, j).GetComplexValue().GetImage() == 0 &&
                     a.GetValue(i, j).GetComplexValue().GetReal() == 0))
                {
                    continue;
                }
                SparseMat.push_back(PII(i, j));
                if (type == 1)
                {
                    value.push_back(a.GetValue(i, j));
                }
                else if (type == 2)
                {
                    value.push_back(a.GetValue(i, j));
                }
                else if (type == 3)
                {
                    value.push_back(a.GetValue(i, j));
                }
            }
        }
        return answer;
    }
    Matrix answer = a;
    return answer;
}

//转置
Matrix Transposition(const Matrix &a)
{
    Matrix answer = Matrix(a.GetCol(), a.GetRow(), a.GetType());
    if (!a.GetisSparseMatrix())
    {
        answer.SetisSparseMatrix(false);
        for (int i = 0; i < answer.GetRow(); ++i)
        {
            for (int j = 0; j < answer.GetCol(); ++j)
            {
                answer.SetValue(i, j, a.GetValue(j, i));
            }
        }
    }
    else
    {
        Matrix fillmat = FillSparseMatrix(a);
        Matrix temp = Matrix(a.GetCol(), a.GetRow(), a.GetType());
        temp.SetisSparseMatrix(false);
        for (int i = 0; i < answer.GetRow(); ++i)
        {
            for (int j = 0; j < answer.GetCol(); ++j)
            {
                temp.SetValue(i, j, fillmat.GetValue(j, i));
            }
        }
        answer = Sparse(temp);
    }
    return answer;
}

//共轭
Matrix conjugation(const Matrix &a)
{
    Matrix answer = Matrix(a);
    if (answer.GetType() == 3)
    {
        for (int i = 0; i < answer.GetElementNum(); ++i)
        {
            Complex conjugation = Complex(answer.GetValue(i).GetComplexValue().GetReal(),
                                          -answer.GetValue(i).GetComplexValue().GetImage());
            ValueType value = ValueType(3);
            value.SetComplexValue(conjugation);
            answer.SetValue(i, value);
        }
    }
    if (answer.GetType() == 1)
    {
        answer.UpGrade();
        answer.UpGrade();
    }
    if (answer.GetType() == 2)
    {
        answer.UpGrade();
    }
    return answer;
}

//按元素乘
Matrix ElementWiseProduct(const Matrix &a, const Matrix &b)
{
    if (a.GetSize() != b.GetSize())
        throw("Size not Same Error!");
    Matrix answer = Matrix(a.GetRow(), b.GetCol(), max(a.GetType(), b.GetType()));
    Matrix mat_a = a;
    Matrix mat_b = b;
    if (mat_a.GetisSparseMatrix())
        mat_a = FillSparseMatrix(mat_a);
    if (mat_b.GetisSparseMatrix())
        mat_b = FillSparseMatrix(mat_b);
    for (int i = 0; i < mat_a.GetTotalSize(); ++i)
    {
        answer.SetValue(i, mat_a.GetValue(i) * mat_b.GetValue(i));
    }
    return answer;
}

//点乘
ValueType DotProduct(const Matrix &a, const Matrix &b)
{
    Matrix mat = ElementWiseProduct(a, b);
    ValueType answer = ValueType(mat.GetType());
    for (int i = 0; i < mat.GetTotalSize(); i++)
    {
        answer = answer + mat.GetValue(i);
    }
    return answer;
}

// to do`````````````````````````````````````````````````````````````````````````
Matrix Inverse(const Matrix &a) {}                      //矩阵求逆
ValueType Eigenvalue(const Matrix &a) {}                //矩阵求特征值
Matrix Eigenvector(const Matrix &a) {}                  //矩阵求特征向量
ValueType Trace(const Matrix &a) {}                     //矩阵求trace
ValueType Determinant(const Matrix &a) {}               //矩阵求行列式
Matrix Convolution(const Matrix &a, const Matrix &b) {} //矩阵求卷积
