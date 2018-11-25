#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu {

	template <class T>
	class Matrix {
	private:
		// your private member variables here.

	public:
		Matrix() = default;

		Matrix(size_t n, size_t m, T _init = T()) {

		}

		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()) {

		}

		Matrix(const Matrix &o) {

		}

		template <class U>
		Matrix(const Matrix<U> &o) {

		}

		Matrix &operator=(const Matrix &o) {

		}

		template <class U>
		Matrix &operator=(const Matrix<U> &o) {

		}

		Matrix(Matrix &&o) noexcept {

		}

		Matrix &operator=(Matrix &&o) noexcept {

		}

		~Matrix() { }

		Matrix(std::initializer_list<std::initializer_list<T>> il) {

		}

	public:
		size_t rowLength() const { }

		size_t columnLength() const { }

		void resize(size_t _n, size_t _m, T _init = T()) {

		}

		void resize(std::pair<size_t, size_t> sz, T _init = T()) {

		}

		std::pair<size_t, size_t> size() const {

		};

		void clear() {

		}

	public:
		const T &operator()(size_t i, size_t j) const {

		}

		T &operator()(size_t i, size_t j) {

		}

		Matrix<T> row(size_t i) const {

		}

		Matrix<T> column(size_t i) const {

		}


	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const {

		}

		template <class U>
		bool operator!=(const Matrix<U> &o) const {

		}

		Matrix operator-() const {

		}

		template <class U>
		Matrix &operator+=(const Matrix<U> &o) {

		}

		template <class U>
		Matrix &operator-=(const Matrix<U> &o) {

		}

		template <class U>
		Matrix &operator*=(const U &x) {

		}

		Matrix tran() const {

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

		private:


		public:
			difference_type operator-(const iterator &o) {

			}

			iterator &operator+=(difference_type offset) {

			}

			iterator operator+(difference_type offset) const {

			}

			iterator &operator-=(difference_type offset) {

			}

			iterator operator-(difference_type offset) const {

			}

			iterator &operator++() {

			}

			iterator operator++(int) {

			}

			iterator &operator--() {

			}

			iterator operator--(int) {

			}

			reference operator*() const {

			}

			pointer operator->() const {

			}

			bool operator==(const iterator &o) const {

			}

			bool operator!=(const iterator &o) const {

			}
		};

		iterator begin() {

		}

		iterator end() {

		}

		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {

        }
	};

}

//
namespace sjtu {
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x) {

	}

	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat) {

	}

	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b) {

	}

	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b) {

	}

	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b) {

	}

}

#endif //SJTU_MATRIX_HPP
