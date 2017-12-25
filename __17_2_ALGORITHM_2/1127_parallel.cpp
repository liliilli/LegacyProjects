#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <cmath>
#include <algorithm>
using namespace std;

/**
 * 프로세스를 n^2 개 만들어야 한다는 것?
 * 타임 * 프로세스의 갯수가 n^2lgn 이 되면 가장 이상적이지만,
 * 현재 짜고자 하는 알고리즘은 n^3lgn 이다. (nlgn * n^2)
 * 
 * 병렬 프로그래밍이 왜 그렇게 되는가? <- Knuth 가 증명함.
 * 0/1 Principle 으로 Sorting 이 증명이 되면, 모든 값에 대해서도 소팅이 된다.
 * 
 * Dirty row, Clean row.
 * 진행이 되면 될 수록 Dirty row 의 수는 반으로 줄어든다.
 * log n 개 하게 되면 0/1 에서 Dirty 항은 1개 (0 - 1) 만 남게 된다.
 */

void merge_sort(vector<int>& array, int buf[], int s, int e, bool r_sort_flag) {
  if (s == e) return;

  // Devide
  int sep = (s + e) >> 1;
  merge_sort(array, buf, s, sep, r_sort_flag);
  merge_sort(array, buf, sep + 1, e, r_sort_flag);

  // Conquer
  int i = 0;
  int l = s, r = sep + 1, l_lim = sep + 1, r_lim = e + 1;
  while ((l ^ l_lim) && (r ^ r_lim)) {
    if (!r_sort_flag) {
        if (array[l] > array[r]) { buf[i++] = array[r++]; }
        else { buf[i++] = array[l++]; }
    }
    else {
        if (array[l] < array[r]) { buf[i++] = array[r++]; }
        else { buf[i++] = array[l++]; }
    }

  }

  while (l ^ l_lim) { buf[i] = array[l++]; ++i; }
  while (r ^ r_lim) { buf[i] = array[r++]; ++i; }

  i = s;
  while (i <= e) { array[i] = buf[i - s]; ++i; }
}

void mergesort(vector<int>& A, bool r_sort_flag) {
    int* buf = new int[A.size()];
    merge_sort(A, buf, 0, A.size() - 1, r_sort_flag); 
    delete[] buf;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen("input_parallel.txt", "r", stdin);

    int N; cin >> N;
    vector<vector<int>> value_array(N);
    for (auto& row : value_array)
        row = vector<int>(N);

    for (auto& row : value_array) {
        for (auto& col : row) {
            int value; cin >> value;
            col = value;
        }
    }

    auto count_limit = static_cast<int>(log2(N));
    for (auto cnt = 0; cnt < count_limit; ++cnt) {
        for (auto& row : value_array) { for (auto& col : row) { cout << col << ' '; } cout << '\n'; }
        cout << '\n';

        // Each Row
        auto r_sort_flag = false;
        for (auto& row : value_array) {
            mergesort(row, r_sort_flag);
            r_sort_flag = !r_sort_flag;
        }

        for (auto& row : value_array) { for (auto& col : row) { cout << col << ' '; } cout << '\n'; }
        cout << '\n';
        
        // Each Column
        for (auto col = 0; col < N; ++col) {
            vector<int> temp_col; temp_col.reserve(N);
            for (auto i = 0; i < N; ++i)
                temp_col.push_back(value_array[i][col]);

            sort(temp_col.begin(), temp_col.end());
            for (auto i = 0; i < N; ++i)
                value_array[i][col] = temp_col[i];
        }
    }

    // Each Row
    for (auto& row : value_array) { mergesort(row, false); }
    for (auto& row : value_array) { for (auto& col : row) { cout << col << ' '; } cout << '\n'; }
}