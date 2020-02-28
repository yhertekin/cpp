#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
using namespace std;

template <class type>
class Matrix {
public:
	Matrix(type _rows = 10, type _columns = 10, type _value = 0);
    Matrix<type> *copyMatrix();

    //Matrix-Matrix Operations
    Matrix *operator+(Matrix &m);
    Matrix *operator-(Matrix &m);
    Matrix *operator*(Matrix &m);

    //Matrix-Scalar Operations
	Matrix *operator+(const type& value);
    Matrix *operator-(const type& value);
    Matrix *operator*(const type& value);
    Matrix *operator/(const type& value);
    Matrix *operator%(const type& value);
    Matrix *operator^(const type& value);


    void setRows(type _rows);
	void setColumns(type _columns);
	void setValue(type _value);

	type getRows();
	type getColumns();
	type getValue();
	type** getMatrix();

	void print();
    void print(string filename);
    void resizeMatrix(type _rows, type _columns);
    void transpose();
    void emul(Matrix<type> *m);
    float det();
    void inv();


protected:

	type rows;
	type columns;
	type value;
	type** matrix;



};
template <typename type>
Matrix<type>::Matrix(type _rows, type _columns, type _value) {
	this->rows = _rows;
	this->columns = _columns;
	this->value = _value;

	this->matrix = new type * [int(this->rows)];

	for (int i = 0; i < this->rows; i++) {
		matrix[i] = new type[int(this->columns)];
	}

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _columns; j++) {
			this->matrix[i][j] = _value;
			if (this->value == 101) {
				if (i == j) { this->matrix[i][j] = 1; }
				else { this->matrix[i][j] = 0; }
			}

			else if (_value == 114) {
				this->matrix[i][j] = rand() % 255;
			}
		}

	}

}
struct RGB
{
public:
	int red = 0;
	int green = 0;
	int blue = 0;
};

template <class rgb>
class Image : public Matrix<rgb>
{
public:
	Image<rgb>();
	Image<rgb>(rgb _rows, rgb _columns);
	Image<rgb>(string filename, string format);

	void setColors(rgb _red, rgb _green, rgb _blue);
	void setGray();

    void color2gray();

private:

	RGB _rgb;
	rgb gray;
};

template<class rgb>
Image<rgb>::Image()
{
	this->rows = 255;
	this->columns = 255;
	this->value = 0;
	setColors(0, 0, 0);
	setGray();
}
template<class rgb>
Image<rgb>::Image(rgb _rows, rgb _columns){
    this->rows = _rows;
    this->columns = _columns;
    this->value = 0;

    setColors(0,0,0);
    setGray();
}

template<class rgb>
void Image<rgb>::setColors(rgb _red, rgb _green, rgb _blue){
    _rgb.red = _red;
    _rgb.green = _green;
    _rgb.blue = _blue;
}
template<class rgb>
void Image<rgb>::setGray(){
    this->gray = (_rgb.red + _rgb.blue + _rgb.green) / 3;
}

template <class rgb>
void Image<rgb>::color2gray(){
    
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++)
            this->matrix[i][j] /= 3;
    }
}



template <class type>
void Matrix<type>::setRows(type _rows) {
	this->rows = _rows;
}

template <class type>
void Matrix<type>::setColumns(type _columns) {
	this->columns = _columns;
}

template <class type>
void Matrix<type>::setValue(type _value) {
	this->value = _value;
}

template <class type>
type Matrix<type>::getRows() {
	return this->rows;
}

template <class type>
type Matrix<type>::getColumns() {
	return this->columns;
}

template <class type>
type Matrix<type>::getValue() {
	return this->value;
}

template <class type>
type** Matrix<type>::getMatrix() {
	return this->matrix;
}

template<class type>
Matrix<type>* Matrix<type>::operator+(Matrix &m){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];

	return m1;
}
template<class type>
Matrix<type>* Matrix<type>::operator-(Matrix &m){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];

	return m1;
}

template <typename type>
Matrix<type> *Matrix<type>::operator*(Matrix &m) {
	
    Matrix<type>* m1 = new Matrix<type>(this->rows, m.columns, 0);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < m.columns; ++j){
            for(int k = 0; k < columns; ++k)
                m1->matrix[i][j] += this->matrix[i][k] * m.matrix[k][j];            
        }
    }
	return m1;
}



template <class type>
Matrix<type>* Matrix<type>::operator+(const type& value){

	Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] + value;

	return m1;
}

template<class type>
Matrix<type>* Matrix<type>::operator-(const type& value){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] - value;

	return m1;
}

template<class type>
Matrix<type>* Matrix<type>::operator*(const type& value){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] * value;

	return m1;
}

template<class type>
Matrix<type>* Matrix<type>::operator/(const type& value){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] / value;

	return m1;
}

template<class type>
Matrix<type>* Matrix<type>::operator%(const type& value){

    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->columns; j++)
			m1->matrix[i][j] = this->matrix[i][j] % value;

	return m1;
}

template <class type>
Matrix<type>* Matrix<type>::operator^(const type& value) {
	
    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);

    for(int i = 0; i < value; i++){
        for(int j = 0; j < this->rows; j++){
            for(int k = 0; k < this->columns; k++){
                m1->matrix[j][k] += this->matrix[j][k] * this->matrix[j][k];
            }
        }
    }
    return m1;
}
template<class type>
void Matrix<type>::resizeMatrix(type _rows, type _columns){
    
    Matrix<type> *m1 = new Matrix<type>(_rows, _columns, 0);
    
    if(_rows < this->rows) {this->rows = _rows;}    
    if(_columns < this->columns) {this->columns = _columns;}

    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++){
            m1->getMatrix()[i][j] += this->matrix[i][j];
        }
    }
    this->rows = _rows;
    this->columns = _columns;
    this->matrix = m1->getMatrix();
}

template <class type>
void Matrix<type>::transpose() {
    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);

	for (int i = 0; i < m1->rows; i++) 
		for (int j = 0; j < m1->columns; j++)
			m1->matrix[i][j] = this->matrix[j][i];
	

    for(int i = 0; i < this->rows; i++)
        delete [] this->matrix[i];
    delete[] this->matrix;
    
    this->matrix = m1->matrix;
}

template <class type>
void Matrix<type>::emul(Matrix<type> *m){

    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++){
            this->matrix[i][j] = this->matrix[i][j] * m->matrix[i][j];
        }
    }
}
template <class type>
void Matrix<type>::inv(){
    Matrix<type>* m1 = copyMatrix();
    
    int det = this->det(); 
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            this->matrix[i][j] = ((m1->matrix[(j+1)%3][(i+1)%3] * m1->matrix[(j+2)%3][(i+2)%3]) -
             (m1->matrix[(j+1)%3][(i+2)%3] * m1->matrix[(j+2)%3][(i+1)%3])) / (float)det;
        
    }
}

template <class type>
Matrix<type>* Matrix<type>::copyMatrix(){
    Matrix<type>* m1 = new Matrix<type>(this->rows, this->columns, 0);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++)
            m1->matrix[i][j] = this->matrix[i][j];
    }
    m1->setRows(this->rows);
    m1->setColumns(this->columns);
    return m1;   
}

template<class type>
float Matrix<type>::det()
{
	if (this->rows + this->columns == 4)	
		return ((this->matrix[0][0] * this->matrix[1][1]) - (this->matrix[0][1] * this->matrix[1][0]));
	
	if (this->rows + this->columns == 6)	
		return ((this->matrix[0][0] * this->matrix[1][1] * this->matrix[2][2])
			   +(this->matrix[1][0] * this->matrix[2][1] * this->matrix[0][2])
			   +(this->matrix[2][0] * this->matrix[0][1] * this->matrix[1][2]))
              -((this->matrix[0][2] * this->matrix[1][1] * this->matrix[2][0])
			   +(this->matrix[1][2] * this->matrix[2][1] * this->matrix[0][0])
			   +(this->matrix[2][2] * this->matrix[0][1] * this->matrix[1][0]));
	
	
}



template <class type>
void Matrix<type>::print(string fileName){
    ofstream file;
    file.open(fileName);
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->columns; j++){
            file << this->matrix[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

template <class type>
void Matrix<type>::print() {
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			cout << this->matrix[i][j] << " ";
		}
		cout << "\n";
	}
}


int main() {
    srand(time(NULL));

	// Matrix<double>* m1 = new Matrix<double>(3, 3, 'r');
	// Matrix<double>* m2 = new Matrix<double>(3, 3, 3);
    // m1 = *m1 * *m2;
    // Image<int> *image = new Image<int>(10,10);
    // image->print();
    // image->resizeMatrix(3,2);
    // image->print();
    // m1->print();
    // cout <<"\n" <<m1->det() << "\n";
    // m1->print();

     int sec=3;
  switch(sec){
    // case 1 :
    //   Matrix<double>* a = new Matrix<double>(2,3,1.);
    //   Matrix<double>* b = new Matrix<double>(2,3,9.);
    //   a->print();
    //   b->print();
    //   a = *b + *(*a*1);
    //   a->print("file.txt"); // içinde 10 olan matris olmalı
    //   break;  
    // case 2 :
    //   Matrix<int>* m1 = new Matrix<int> (5,5,'e');
    //   Matrix<int>* m2 = new Matrix<int>(5,5,'r'); // (5,5) boyutu dene
    //   m1->print();
    //   cout << "\n************************\n";
    //   m2->print();
    //   cout << "\n************************\n";      
    //   m1 = (*m1) * (*m2);
    //   m1->print();
    //   break;
    case 3 :
      // STL vector kullanan buradan puan alamaz
      Matrix<double>* m3 = new Matrix<double>(5,4,1);
      m3->print();
      // aşağıdaki durumları ayrı ayrı dene
      //m3.resize(2,6);
      //m3.resize(10,6);
      m3->resizeMatrix(10,3);
      m3->print();
    }

    //   m3.print();
    //   break;
    // case 4 :
    //   // lineer matris oluştur
    //   Matrix<double> m4(2,2,'L');
    //   Matrix<double> m5 = m4 * m4.inv();
    //   m5.print(); // birim matris olmalı

    //   Matrix<double> m6(3,3,'L');
    //   cout<<m6.det(); // sonuç 0 olmalı
    //   break;

	return 0;
}