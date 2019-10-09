#include <iostream>
#include <clocale>
#include <vector>

using namespace std;
const int inf = 99999;

/*берем максимальную из функций штрафа, берем индекс*/
int max_D(vector<pair<pair<int, int>, int>> D) {
	int max_D_ind = 0;
	int max_De = 0;
	for (size_t i = 0; i < D.size(); i++) {
		if (D[i].second > max_De) {
			max_De = D[i].second;
			max_D_ind = i;
		}
	}
	cout << endl << endl << max_D_ind << "	" << max_De << endl << endl;
	return max_D_ind;
}
void disp(vector<vector<int>> start_matrix1) {

	for (size_t i = 0; i < start_matrix1.size(); i++) {
		cout << endl;
		for (size_t j = 0; j < start_matrix1.size(); j++) {
			cout << start_matrix1[i][j] << "	";
		}
	}
}

vector<vector<int>> Privedenie(vector<vector<int>> start_matrix1,int &R) {
	vector<int> hi, hj;
	for (size_t i = 0; i < start_matrix1.size(); i++) {
		int flag = inf;
		for (size_t j = 0; j < start_matrix1.size(); j++) {
			if (flag > start_matrix1[i][j])
				flag = start_matrix1[i][j];
		}
		if (flag > 1000)
			hi.push_back(0);
		else
			hi.push_back(flag);
	}

	for (size_t i = 0; i < start_matrix1.size(); i++) {
		for (size_t j = 0; j < start_matrix1.size(); j++) {
			start_matrix1[i][j] -= hi[i];
		}
	}

	for (size_t j = 0; j < start_matrix1.size(); j++) {
		int flag = inf;
		for (size_t i = 0; i < start_matrix1.size(); i++) {
			if (flag > start_matrix1[i][j])
				flag = start_matrix1[i][j];
		}
		if (flag > 1000)
			hj.push_back(0);
		else
			hj.push_back(flag);
	}

	for (size_t j = 0; j < start_matrix1.size(); j++) {
		for (size_t i = 0; i < start_matrix1.size(); i++) {
			start_matrix1[i][j] -= hj[j];
		}
	}
	cout << endl;
	cout << endl;
	for (size_t i = 0; i < start_matrix1.size(); i++)
		cout << hi[i] << "	";

	cout << endl;

	for (size_t i = 0; i < start_matrix1.size(); i++)
		cout << hj[i] << "	";

	for (size_t i = 0; i < start_matrix1.size(); i++)
		R += hi[i];

	for (size_t i = 0; i < start_matrix1.size(); i++)
		R += hj[i];

	
	return start_matrix1;

}

void TSM(vector<vector<int>> start_matrix) {
	vector<vector<int>> start_matrix1 = start_matrix;
	int R = 0,del,del_str,del_stlb;
	vector<int> travel;

	/*начало кода отвечающего за первый этап*/
	
	start_matrix1 = Privedenie(start_matrix1, R);

	cout << endl;

	for (size_t i = 0; i < start_matrix1.size(); i++) {
		cout << endl;
		for (size_t j = 0; j < start_matrix1.size(); j++) {
			cout << start_matrix1[i][j] << "	";
		}
	}
	/*конец кода отвечающего за первый этап*/


	/*Начало второго этапа*/

	int l = 0;
	int s = 4;
	/*подсчет функций штрафа D если будет не лень попробую оптимизировать*/
	while (s > 3) {
		s = 0;
		vector<pair<pair<int, int>, int>> D(256);
		cout << endl << "Почему  " << R;
		for (size_t i = 0; i < start_matrix1.size(); i++) {
			for (size_t j = 0; j < start_matrix1.size(); j++) {

				if (start_matrix1[i][j] == 0) {
					int flag = 9999;
					int flag1 = 0;
					for (size_t k = 0; k < start_matrix1.size(); k++) {
						if (start_matrix1[i][k]<flag && start_matrix1[i][k] < 1000)
							flag = start_matrix1[i][k];
					}
					flag1 = flag;
					for (size_t k = 0; k < start_matrix1.size(); k++) {
						if (start_matrix1[k][j]<flag && start_matrix1[k][j] < 1000)
							flag = start_matrix1[k][j];
					}
					flag1 += flag;
					D[l].second = flag;
					D[l].first.first = i;
					D[l].first.second = j;
					l++;
				}
			}
		}
		del = max_D(D);
		del_str = D[del].first.first;
		del_stlb = D[del].first.second;
		start_matrix1[del_stlb][del_str] = inf;

		for (size_t i = 0; i < start_matrix1.size(); i++) {
			start_matrix1[del_str][i] = inf;
		}
		for (size_t i = 0; i < start_matrix1.size(); i++) {
			start_matrix1[i][del_stlb] = inf;
		}
		disp(start_matrix1);
		start_matrix1 = Privedenie(start_matrix1, R);

		for (size_t i = 0; i < start_matrix1.size(); i++) {
			for (size_t j = 0; j < start_matrix1.size(); j++) {
				if (start_matrix1[i][j] == 0)
					s++;
			}
		}
		travel.push_back(del_str);
		travel.push_back(del_stlb);
		D.clear();
	}
	cout << endl << "путь: ";
	for (size_t i = 0; i < travel.size(); i++) {
		cout << travel[i] << "--";
	}

}

void new_fun()
{
	cout << "Are you algoritmist, aren't you?"<<endl;
	cout << "It's my fun!" << endl;
}

int main()
{
	setlocale(0, "RUS");
	int k = 0;
	int n = 5;
	vector<vector<int>> start_matrix(5); 
	int exodus[] = { inf,20,18,12,8,
					5,inf,14,7,11,
					12,18,inf,6,11,
					11,17,11,inf,12,
					5,5,5,5,inf };

	for (int i = 0; i < n; i++)
		start_matrix[i].resize(5);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++, k++) {
			start_matrix[i][j] = exodus[k];
		}
	}
	TSM(start_matrix);
}