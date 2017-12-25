#include <iostream>
#include <string>
#include <random>

using namespace std;

auto pibo_recur(const int nu, const int fl, const int fr) -> int;
auto pibo_iter(const int num) -> int;
auto pibo(const int num) -> int;

void permutation(string&, int, int);

auto get_separation(string&, const int, const int) -> int;
void quick_sort(string&, const int, const int);

auto insertion_sort(string&, const int, const int) -> void;
auto selection_sort(string&, const int, const int) -> void;
auto merge_sort(string&, const int, const int) -> void;

/*
 * Main ÇÔ¼ö.
 */
int main() {
	string input = ""; std::cin >> input;
	string input_2 = input;

	//permutation(input, 0, input.length());
	quick_sort(input, 0, input.length() - 1);
	cout << input << '\n';

	merge_sort(input_2, 0, input.length() - 1);
	cout << input_2 << '\n';
}

auto pibo_recur(const int num, const int fl, const int fr) -> int {
	if (num > 2)
		return pibo_recur(num - 1, fr, fl + fr);
	else if (num >= 1)
		return fl + fr;
	else
		return fl;
}

auto pibo_iter(const int num) -> int {
	auto back_2 = 0;
	auto back_1 = 1;

	auto res = (num == 1) ? 1 : 0;

	if (num > 1) {
		for (int i = 1; i < num; ++i) {
			res		= back_1 + back_2;
			back_2	= back_1;
			back_1	= res;
		}
	}

	return res;
}

auto pibo(const int num) -> int {
	return pibo_recur(num, 0, 1);
}

void permutation(string& input, int index, int length) {
	if (index >= length) return;

	selection_sort(input, index, length);
	permutation(input, index + 1, length);
	selection_sort(input, index + 1, length);

	for (int m = 0; m < length; ++m) {
		if (m > index && input[m] > input[index]) {
			swap(input[m], input[index]);
			printf("%s\n", input.c_str());

			permutation(input, index + 1, length);
			selection_sort(input, index + 1, length);
		}
	}
}

auto get_separation(string& input, const int start, const int end) -> int {
	static int count = 0;

	auto target = input[end];
	auto prefix = start - 1;

	for (auto src = start; src <= end - 1; ++src) {
		if (input[src] <= target) {
			++prefix;

			swap(input[prefix], input[src]);
		}
	}

	++prefix;
	swap(input[prefix], input[end]);

	return prefix;
}

void quick_sort(string& input, const int start, const int end) {
	static auto i = 0;
	static auto random_partition = 
		[](string& input, const int start, const int end) {

		static random_device seed_gen;
		static std::mt19937 engine(seed_gen());

		auto len = end - start + 1;
		auto sel = (static_cast<int>(engine() % len) + start);

		swap(input[end], input[sel]);
	};

	if (start < end) {
		random_partition(input, start, end);
		auto sep = get_separation(input, start, end);
		cout << i++ << " : " << input << '\n';

		quick_sort(input, start, sep - 1);
		quick_sort(input, sep + 1, end);
	}
}

auto insertion_sort(string &, const int, const int) -> void {
}

auto selection_sort(string& input, const int index, const int length) -> void {
	for (int i = index; i < length; ++i) {
		char src = input[i];
		int max_index = i;
		
		for (int j = i + 1; j < length; ++j) {
			char dst = input[j];
			
			if (src > dst) max_index = j;
		}

		if (max_index != i) {
			char temp = src;
			input[i] = input[max_index];
			input[max_index] = temp;
		}
	}
}

auto merge_sort(string& input, const int start, const int end) -> void {
	if (end <= start) return;

	auto sep = static_cast<int>((start + end) / 2) + 1;

	merge_sort(input, start, sep - 1);
	merge_sort(input, sep, end);

	auto left	= start;
	auto right	= sep;

	std::string res;
	while (left < sep && right <= end) {
		if (input[left] >= input[right])
			res += input[right++];
		else
			res += input[left++];
	}

	while (left < sep) res += input[left++];
	while (right <= end) res += input[right++];

	auto replace_length = end - start + 1;
	input.replace(start, replace_length, res);
}
