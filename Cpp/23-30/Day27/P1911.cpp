#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	int ans = 0;
	
	ans = (n / 10)+(n % 10);
	cout << ans << endl;
	return 0;
}
