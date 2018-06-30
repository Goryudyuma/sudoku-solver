#include<bits/stdc++.h>
/**/

using namespace std;

void show(vector<vector<set<long long int>>>D){
	cout << endl;
	for( size_t i = 0; i < 9; i++ ){
		for( size_t j = 0; j < 9; j++ ){
			if( D[i][j].size() == 1 ){
				cout << *( D[i][j].begin() );
			} else{
				cout << " ";
			}
			//cout << D[i][j].size();
			cout << " ";
		}
		cout << endl;
	}
}

vector<vector<set<long long int>>>change(vector<vector<set<long long int>>>D){
	auto D_ = D;
	for( size_t i = 0; i < 9; i++ ){
		for( size_t j = 0; j < 9; j++ ){
			if( D[i][j].size() == 1 ){
				long long int now = *( D[i][j].begin() );
				for( size_t k = 0; k < 9; k++ ){
					if( k != j ){
						D[i][k].erase(now);
					}
					if( i != k ){
						D[k][j].erase(now);
					}
					if( i != i / 3 * 3 + k % 3 || j != j / 3 * 3 + k / 3 ){
						D[i / 3 * 3 + k % 3][j / 3 * 3 + k / 3].erase(now);
					}
				}
			}
		}
	}

	for( size_t i = 0; i < 9; i++ ){
		map<long long int, long long int>m1, m2, m3;
		for( size_t j = 0; j < 9; j++ ){
			for( auto x : D[i][j] ){
				m1[x]++;
			}
			for( auto x : D[j][i] ){
				m2[x]++;
			}
			for( auto x : D[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] ){
				m3[x]++;
			}
		}
		for( auto y : m1 ){
			if( y.second == 1 ){
				for( size_t j = 0; j < 9; j++ ){
					if( D[i][j].count(y.first) ){
						D[i][j] = set<long long int>{ y.first };
					}
				}
			}
		}
		for( auto y : m2 ){
			if( y.second == 1 ){
				for( size_t j = 0; j < 9; j++ ){
					if( D[j][i].count(y.first) ){
						D[j][i] = set<long long int>{ y.first };
					}
				}
			}
		}
		for( auto y : m3 ){
			if( y.second == 1 ){
				for( size_t j = 0; j < 9; j++ ){
					if( D[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].count(y.first) ){
						D[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = set<long long int>{ y.first };
					}
				}
			}
		}
	}

	if( D_ == D ){
		return D;
	} else{
		return change(D);
	}
}

pair<vector<vector<set<long long int>>>, long long int>find(vector<vector<set<long long int>>> D){
	D = change(D);
	long long int sum = 0;
	auto memo = D;
	for( size_t i = 0; i < 9; i++ ){
		for( size_t j = 0; j < 9; j++ ){
			if( D[i][j].size() != 1 ){
				for( auto x : D[i][j] ){
					auto Dx = D;
					Dx[i][j] = set<long long int>{ x };
					auto ret = find(Dx);
					sum += ret.second;
					if( sum > 1 )break;
					if( ret.second ){
						memo = ret.first;
					}
				}
				return make_pair(memo, sum);
			}
		}
	}
	return make_pair(D, 1);
}

int main(){
	vector<vector<set<long long int>>>D(9, vector<set<long long int>>(9, set<long long int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
	while( true ){
		show(D);
		long long int a, b, c;
		cin >> a >> b >> c;
		if( a == -1 ){
			auto ret = find(D);
			if( ret.second == 1 ){
				D = ret.first;
				break;
			}
		} else{
			D[a][b] = set<long long int>{ c };
			D = change(D);
		}
	}
	show(D);
}
