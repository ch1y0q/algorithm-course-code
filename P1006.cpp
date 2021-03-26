#include <algorithm>
#include <iostream>
#include <string>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define per(a, b, c) for (int a = b; a >= c; a--)

typedef long long ll;
using namespace std;

size_t n;
int arr[1005];

template <class T>
class MinHeap {
   public:
    MinHeap(T data[], size_t sz) {
        n = 0;
        heap = new T[sz + 1];  // 下标从1开始
                               /*
                               for (size_t i = 1; i <= sz; ++i) {
                                   Insert(data[i]);
                               }
                               */
        for (size_t i = 1; i <= sz; ++i) {
            heap[i] = data[i];
        }
        n = sz;
        per(i, n / 2, 1) shiftDown(i);
    }

    ~MinHeap() { delete[] heap; }

    void Insert(const T& data) {
        heap[++n] = data;
        shiftUp(n);
    }

    void Delete(T& data) {
        data = heap[1];
        heap[1] = heap[n];
        n--;
        shiftDown(1);
    }

    void shiftUp(size_t p) {
        size_t q = p / 2;
        T a = heap[p];
        while (q >= 1) {
            if (a < heap[q]) {
                heap[p] = heap[q];
            } else {
                break;
            }
            p = q;
            q = p / 2;
        }
        heap[p] = a;
    }

    void shiftDown(size_t p) {
        size_t q = p * 2;
        T a = heap[p];
        while (q <= n) {
            if (q + 1 <= n) {
                q = heap[q] <= heap[q + 1] ? q : q + 1;
            }
            if (heap[q] < a) {
                heap[p] = heap[q];
            } else
                break;
            p = q;
            q = p * 2;
        }
        heap[p] = a;
    }

    void print() const {
        /** LINEAR OUTPUT **/
        for (size_t i = 1; i < n; ++i) {
            std::cout << heap[i] << " ";
        }
        std::cout << heap[n] << std::endl;
    }

   private:
    size_t n;  // current number of elements
    T* heap;
};

int main() {
    int m;
    cin >> m;
    while (m--) {
        cin >> n;
        rep(i, 1, n) { cin >> arr[i]; }
        auto theHeap = new MinHeap<int>(arr, n);
        theHeap->print();
        delete theHeap;
    }
    return 0;
}