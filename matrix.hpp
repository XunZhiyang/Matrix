#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>
#define ASSERT(expr, message) if(!(expr)); //throw std::invalid_argument(message);
using std::size_t;

namespace sjtu {
	template <class T>
	class Matrix {

	template <class V, class U>
	friend auto operator*(const Matrix<V> &mat, const U &x);

	template <class V, class U>
	friend auto operator*(const U &x, const Matrix<V> &mat);

	template <class U, class V>
	friend auto operator*(const Matrix<U> &a, const Matrix<V> &b);

	template <class U, class V>
	friend auto operator+(const Matrix<U> &a, const Matrix<V> &b);

	template <class U, class V>
	friend auto operator-(const Matrix<U> &a, const Matrix<V> &b);
	public:
		size_t rowNum, colNum;
		T *mat;
			// your private member variables here.
		template <class U>
		bool homomorphic(const Matrix<U> &o) const {
			return rowNum == o.rowNum && colNum == o.colNum;
		}

	public:
		Matrix() : rowNum(0), colNum(0), mat(NULL) {};
		Matrix(size_t n, size_t m, T _init = T()) {
			// ASSERT(n > 0 && m > 0, "invalid n m");
			mat = new T[n * m + 1];
			rowNum = n;
			colNum = m;
			for(size_t i = 0; i < rowNum * colNum; ++i) mat[i] = _init;
		}
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
			:Matrix(sz.first, sz.second, T()) {}

		Matrix(const Matrix &o) {
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = new T[rowNum * colNum + 1];
			for (size_t i = 0; i < rowNum * colNum; ++i) {
				mat[i] = o.mat[i];
			}
		}

		template <class U>
		Matrix(const Matrix<U> &o) {
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = new T[rowNum * colNum + 1];
			for (size_t i = 0; i < rowNum * colNum; ++i) {
				mat[i] = T(o.mat[i]);
			}
		}		//U must be able to comvert to T

		Matrix &operator=(const Matrix &o) {
			if(this == &o) return *this;
			delete []mat;
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = new T[rowNum * colNum + 1];
			for (size_t i = 0; i < rowNum * colNum; ++i) {
				mat[i] = T(o.mat[i]);
			}
			return *this;
		}
		template <class U>
		Matrix &operator=(const Matrix<U> &o) {
			delete []mat;
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = new T[rowNum * colNum + 1];
			for (size_t i = 0; i < rowNum * colNum; ++i) {
				mat[i] = T(o.mat[i]);		//Ctrl + C   Ctrl + V
			}
			return *this;
		}

		Matrix(Matrix &&o) noexcept {
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = o.mat;
			o.mat = NULL;
		}

		Matrix &operator=(Matrix &&o) noexcept {
			delete []mat;
			rowNum = o.rowNum;
			colNum = o.colNum;
			mat = o.mat;
			o.mat = NULL;
			return *this;
		}

		~Matrix() {
			delete []mat;
		}

		Matrix(std::initializer_list< std::initializer_list<T> > o) {
			rowNum = o.size();
			colNum = o.begin() -> size();
			mat = new T[rowNum * colNum + 1];
			size_t cnt = 0;
			for(auto i : o) {
				ASSERT(i.size() == colNum, "invalid initializer_list");
				for(T j : i) {
					mat[cnt++] = j;
				}
			}
		}

	public:
		size_t rowLength() const {
			return rowNum;
		}

		size_t columnLength() const {
			return colNum;
		}

		void resize(size_t _n, size_t _m, T _init = T()) {
			ASSERT(_n > 0 && _m > 0, "invalid resize n m");;
			if(_n * _m == rowNum * colNum) {
				rowNum = _n;
				colNum = _m;
				return;
			}
			T *p = new T[_n * _m + 1];
			for(size_t i = 0; i < _n * _m; ++i) {
				p[i] = i < rowNum * colNum ? mat[i] : _init;
			}
			delete []mat;
			rowNum = _n;
			colNum = _m;
		}

		void resize(std::pair<size_t, size_t> sz, T _init = T()) {
			resize(sz.first, sz.second, _init);
		}

		std::pair<size_t, size_t> size() const {
			return std::make_pair(rowNum, colNum);
		};

		void clear() {
			rowNum = colNum = 0;
			delete []mat;
			mat = NULL;
		}

	public:
		const T &operator()(size_t i, size_t j) const {
			ASSERT(i >= 0 && i < rowNum && j >= 0 && j <colNum, "invalid const element visit");
			return mat[i * colNum + j];
		}

		T &operator()(size_t i, size_t j) {
			ASSERT(i >= 0 && i < rowNum && j >= 0 && j <colNum, "invalid element visit");
			return mat[i * colNum + j];
		}

		Matrix<T> row(size_t i) const {
			ASSERT(i >= 0 && i < rowNum, "Invalid row visit");
			Matrix tmp = Matrix(1, colNum);
			for(size_t j = 0; j < colNum; ++j) {
				tmp(0, j) = (*this)(i, j);
			}
			return tmp;
		}

		Matrix<T> column(size_t i) const {
			ASSERT(i >= 0 && i < colNum, "Invalid column visit");
			Matrix tmp = Matrix(rowNum, 1);
			for(size_t j = 0; j < rowNum; ++j) {
				tmp(j, 0) = (*this)(j, i);
			}
			return tmp;
		}


	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const {
			if(!homomorphic(o)) return false;
			for(size_t i = 0; i < rowNum * colNum; ++i) {
				if(mat[i] != o.mat[i]) return false;
			}
			return true;
		}

		template <class U>
		bool operator!=(const Matrix<U> &o) const {
			return !((*this) == o);
		}

		Matrix operator-() const {
			Matrix newMat = (*this);
			for(size_t i = 0; i < rowNum * colNum; ++i) newMat.mat[i] = -mat[i];
			return newMat;
		}

		template <class U>
		Matrix &operator+=(const Matrix<U> &o) {
			return (*this) = (*this) + o;
		}

		template <class U>
		Matrix &operator-=(const Matrix<U> &o) {
			return (*this) = (*this) - o;
		}

		template <class U>
		Matrix &operator*=(const U &x) {
			return (*this) = (*this) * x;
		}

		Matrix tran() const {
			Matrix tmp = Matrix(colNum, rowNum);
			for(size_t i = 0; i < rowNum; ++i) {
				for(size_t j = 0; j < colNum; ++j) {
					tmp(j, i) = (*this)(i, j);
				}
			}
			return tmp;
		}

	public: // iterator
		class iterator {
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;

			iterator() = default;

			iterator(const iterator &) = default;

			iterator &operator=(const iterator &) = default;

		public:
			pointer p;
			size_type nowRow, nowCol, beginRow, beginCol, endRow, endCol, colNum;

		public:
			iterator(pointer x, size_t a, size_t b, size_t c, size_t d, size_t e, size_t f, size_t g) : p(x), nowRow(a), nowCol(b), beginRow(c), beginCol(d), endRow(e), endCol(f), colNum(g) {}
			difference_type operator-(const iterator &o) {
				return -(endCol - beginCol + 1) * (o.nowRow - nowRow) - o.nowCol + nowCol;
			}

			iterator operator+(difference_type offset) const {
				iterator np = (*this);
				if(offset > 0 && offset >= endCol - np.nowCol + 1) {
					ASSERT(np.nowRow <= endRow, "index overflow");
					np.p += beginCol - np.nowCol + colNum;
					offset -= endCol - np.nowCol + 1;
					np.nowCol = beginCol;
					np.nowRow++;
				}
				if(offset < 0 && offset <= (int)beginCol - (int)np.nowCol - 1) {
					ASSERT(np.nowRow > beginRow, "index overflow");
					np.p -= np.nowCol - endCol + colNum;
					offset += beginCol - np.nowCol - 1;
					np.nowCol = endCol;
					np.nowRow--;
				}
				// std::cerr<<"offset: "<<offset<<std::endl;
				int t = offset / (endCol - beginCol + 1);
				np.nowRow += t;
				ASSERT(np.nowRow >= beginRow && np.nowRow <= endRow + 1, "index overflow");
				np.p += t * colNum;
				offset -= t * (endCol - beginCol + 1);
				np.nowCol += offset;
				ASSERT(np.nowRow != endRow + 1 || np.nowCol == beginCol, "index overflow");
				np.p += offset;
				return np;
			}

			iterator operator-(difference_type offset) const {
				return (*this) + (-offset);
			}

			iterator &operator+=(difference_type offset) {
				return (*this) = (*this) + offset;
			}

			iterator &operator-=(difference_type offset) {
				return (*this) = (*this) - offset;
			}

			iterator &operator++() {
				return (*this) += 1;
			}

			iterator operator++(int) {
				iterator np = (*this);
				++(*this);
				return np;
			}
			iterator &operator--() {
				return (*this) -= 1;
			}

			iterator operator--(int) {
				iterator np = (*this);
				--(*this);
				return np;
			}

			reference operator*() const {
				return *p;
			}

			pointer operator->() const {
				return p;
			}

			bool operator==(const iterator &o) const {
				return p == o.p;
			}

			bool operator!=(const iterator &o) const {
				return p != o.p;
			}
		};

		iterator begin() {
			iterator np;
			return np = {mat, 0, 0, 0, 0, rowNum - 1, colNum - 1, colNum};
		}

		iterator end() {
			return {mat + colNum * rowNum, rowNum, 0, 0, 0, rowNum - 1, colNum - 1, colNum};
		}

		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {
			iterator Begin = {mat + l.first * colNum + l.second, l.first, l.second, l.first, l.second, r.first, r.second, colNum};
			iterator End = {mat + r.first * colNum + r.second, r.first, r.second, l.first, l.second, r.first, r.second, colNum};
			return std::make_pair(Begin, End + 1);
        }
	};

}

//
namespace sjtu {
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x) {
		Matrix<decltype(T() * U())> tmp = Matrix<decltype(T() * U())>(mat);
		for(size_t i = 0; i < mat.rowNum * mat.colNum; ++i) {
			tmp.mat[i] = mat.mat[i] * x;
		}
		return tmp;
	}

	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat) {
		Matrix<decltype(T() * U())> tmp = Matrix<decltype(T() * U())>(mat);
		for(size_t i = 0; i < mat.rowNum * mat.colNum; ++i) {
			tmp.mat[i] = mat.mat[i] * x;
		}
		return tmp;
	}

	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b) {
		ASSERT(a.colNum == b.rowNum, "invalid matrix multiplication");
		Matrix<decltype(U() * V())> tmp = Matrix<decltype(U() * V())>(a.rowNum, b.colNum, 0);
		for(size_t i = 0; i < tmp.rowNum; ++i) {
			for(size_t j = 0; j < tmp.colNum; ++j) {
				for(size_t k = 0; k < a.colNum; ++k) {
					tmp(i, j) += a(i, k) * b(k, j);
				}
			}
		}
		return tmp;
	}
	
	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b) {
		ASSERT(a.homomorphic(b), "invalid plus");
		Matrix<decltype(U() + V())> tmp = Matrix<decltype(U() + V())>(a.rowNum, a.colNum);
		for(size_t i = 0; i < a.rowNum * a.colNum; ++i) {
			tmp.mat[i] = a.mat[i] + b.mat[i];
		}
		return tmp;
	}

	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b) {
		return a + -b;
	}

}

#endif //SJTU_MATRIX_HPP
