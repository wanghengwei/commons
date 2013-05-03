#include <string>
#include <iostream>
#include <cassert>

using namespace std;



int find_first(string const &s, string const &pattern)
{

  int const N = pattern.length();
  int const M = 'z' - 'a' + 1;

  auto sm = new int[N][M];

  for (int i = 0; i < N; ++i) {

    for (int j = 0; j < M; ++j) {

      string w = pattern.substr(0, i).append(1, char('a' + j));

      for (int k = i + 1; k >= 0; --k) {

	string pp = pattern.substr(0, k);

	if (w.rfind(pp) + pp.length() == w.length()) {
	  sm[i][j] = k;
	  cout << "sm[" << i << "][" << j << "]=" << k << endl;
	  break;
	}

      }

    }

  }

  int q = 0;

  for (int i = 0; i < s.length(); ++i) {

    if ((q = sm[q][s[i] - 'a']) == pattern.length()) {
      return i - pattern.length() + 1;
    }
    cout << s[i] - 'a' << ":" << q << endl;
  }

  return -1;

}

int main(int, char *[])
{
  int i = find_first("ababaca", "bac");
  cout << i << endl;
  assert(i == 3);

  return 0;
}
