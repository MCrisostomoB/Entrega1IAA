  #include <fstream>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

bool areDistinct(vector<int> arr)
{
    int n = arr.size();
    unordered_set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(arr[i]);
    }
    return (s.size() == arr.size());
}
vector<string> split(const std::string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);

   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
class Charlas{
  public:
    int cruce;
    vector<int> charlas;
    int considerado;
	vector<int> otrascharlas;
	int lcharlas;
	int n;
};

int main(int argc, char** argv){
	string instances[] = {"MAPSP2015_Instance.txt","MAPSP2017_Instance.txt","MathSport2013_Instance.txt","ORBEL2017_Instance.txt"};
	int sessions,people,talks,i,place;
	vector<string> values;
	string line,valor;
	ifstream file;
	vector<vector<int>> preferences;
	vector<vector<int>> horario;
	vector<Charlas> charlas;
	file.open(argv[1]);
	getline(file,line);
	getline(file,line);
	values = split(line,' ');
	sessions =stoi(values[0]);
	horario.resize(sessions);
	if(sessions == 4){
		getline(file,line);
		getline(file,line);
		getline(file,line);
	}
	getline(file,line);
	getline(file,line);

	getline(file,line);
	values = split(line,'\t');
	talks = stoi(values[values.size() -1]);
	charlas.resize(talks);

	while(getline(file,line)){
		values = split(line,'\t');
		place = stoi(values[0]);
		preferences.resize(place);

		values.erase(values.begin());
		for(int i = 0; (unsigned)i<values.size() ; i++){
			preferences[place-1].push_back(stoi(values[i]));
		}
	}
	people = place;
	for(i = 0; i<talks;i++){
		charlas[i].cruce = 9999999;
		charlas[i].charlas.resize(sessions);
		charlas[i].considerado = 0;
		charlas[i].n = 0;

	}

	for(int i=0;i<talks;i++){
	  for(int j= 0;j<talks;j++){
		  for(int k = 0;k<people;k++){
			  if(preferences[k][i]== 1 && preferences[k][j]==1 && i!=j){
				  charlas[i].otrascharlas.push_back(j);
				  charlas[i].lcharlas++;
				  break;
			  }
		  }
	  }
	}


	// for(i=0;i<talks;i++){
	//   std::cerr << "Charla:"<<i+1 << '\n';
	//   for(int j=0;j<charlas[i].lcharlas;j++){
	// 	  std::cout << charlas[i].otrascharlas[j] +1<< '\t';
	//   }
	//   std::cout << "\n" << '\n';
	// }

	int n;
	for(i=0;i<talks;i++){
		n=0;
		int actualval = 0;
		if(charlas[i].considerado == 0){
			for(int j=0;j<charlas[i].lcharlas;j++){
				if(n==sessions){
					break;
				}
				if(charlas[i].otrascharlas[j]!= actualval){
					if(charlas[actualval].considerado==0){

						int posible = 1;
						if(n>1){
							for(int r = 0; r<n;r++){
								for(int f =0; f < charlas[charlas[i].charlas[r]].lcharlas; f++){
									if(charlas[charlas[i].charlas[r]].otrascharlas[f] == actualval){
										posible = 0;
										break;
									}
								}
							}
						}
						if(posible == 1){
							int found = 0;

							for(int t = 0; t<n;t++){
								if(charlas[i].charlas[t] == i){
									found = 1;
								}
							}
							if(found == 0 && n==sessions-1){
								charlas[i].charlas[n]=i;
								charlas[i].cruce = 0;
								charlas[i].considerado = 1;
							}else{
								charlas[i].charlas[n]=actualval;
								charlas[i].cruce = 0;
								charlas[actualval].considerado = 1;
							}

							n++;

							for(int t = 0; t<n;t++){
								charlas[charlas[i].charlas[t]].n= n;
							}

						}
					}
					if(actualval<charlas[i].otrascharlas[j]){
						j--;
					}
				}

				actualval++;
			}

		}
		if(sessions!= 2){
			if(charlas[i].n < sessions-1){
				charlas[i].cruce = 9999999;
				charlas[i].n = 0;
				charlas[i].considerado=0;
				for(int s= 0; s<n; s++){
					charlas[charlas[i].charlas[s]].considerado = 0;
					charlas[i].charlas[s] = 0;
				}
			}
		}else{
			if(charlas[i].n <= sessions-1){
				charlas[i].cruce = 9999999;
				charlas[i].n = 0;
				charlas[i].considerado=0;
				for(int s= 0; s<n; s++){
					charlas[charlas[i].charlas[s]].considerado = 0;
					charlas[i].charlas[s] = 0;
				}
			}
		}
	}
	// std::cout << "resultado 1" << '\n';
	// for(i=0;i<talks;i++){
	// 	if(charlas[i].cruce == 0){
	//     	cout << charlas[i].cruce <<"\t"<<charlas[i].charlas[0]+1<<"\t"<<charlas[i].charlas[1]+1<<"\t"<<charlas[i].charlas[2]+1<<'\n';
	// 	}
	// }
	vector<int> charlasrestantes;
	int lrestantes=0;
	for(i=0;i<talks+1;i++){
		if(charlas[i].considerado == 0){
			charlasrestantes.push_back(i);
			lrestantes++;
			// cout <<"charla: "<<i+1<<'\n';
		}
	}
	for(i = 0 ; i<talks; i++){
		if(charlas[i].n<sessions && charlas[i].cruce == 0){
			charlas[i].cruce = 5000;
			for(int k = 0 ; k<lrestantes; k++){
				int newsum = 0;
				for(int h = 0 ; h < people; h++){
					int tempsum = 0;
					for(int g = 0 ; g< charlas[i].n-1;g++){
						tempsum = tempsum + preferences[h][charlas[i].charlas[g]];
					}
					tempsum = tempsum + preferences[h][charlasrestantes[k]];
					if(tempsum != 0){
						newsum= newsum + tempsum-1;
					}
				}
				if(charlas[i].cruce>newsum){
					if(charlas[charlasrestantes[k]].considerado==0){
						charlas[i].cruce = newsum;
						if(charlas[i].charlas[sessions-1] == 0){
							charlas[charlasrestantes[k]].considerado = 1;
							charlas[i].charlas[sessions-1] = charlasrestantes[k];
						}else{
							charlas[charlasrestantes[k]].considerado = 1;
							charlas[charlas[i].charlas[sessions-1]].considerado = 0;
							charlas[i].charlas[sessions-1] = charlasrestantes[k];
						}
					}
				}
			}
		}
	}
	// std::cout << "resultado 2" << '\n';
	// for(i=0;i<talks;i++){
	// 	if(charlas[i].cruce != 9999999){
	// 		cout << charlas[i].cruce <<"\t"<<charlas[i].charlas[0]+1<<"\t"<<charlas[i].charlas[1]+1<<"\t"<<charlas[i].charlas[2]+1<<'\n';
	// 	}
	// }
	charlasrestantes.clear();
	lrestantes = 0;
	// std::cout << "segunda tanda" << '\n';
	for(int h = 0; h<talks; h++){
		if(charlas[h].considerado == 0){
			charlasrestantes.push_back(h);
			lrestantes++;
			// cout <<"charla: "<<h+1<<'\n';
		}
	}
	for(int h = 0 ; h<lrestantes;h++){
		if(charlas[charlasrestantes[h]].considerado == 0){
			charlas[charlasrestantes[h]].considerado = 1;
			charlas[charlasrestantes[h]].charlas[0] = charlasrestantes[h];
			charlas[charlasrestantes[h]].n=1;

		}
		int changed = 0;
		for(int j = 0 ; j <lrestantes;j++){
			if(h!=j&& charlas[charlasrestantes[j]].considerado!=1){
				int newsum = 0;
				for(int p = 0 ; p<people;p++){
					int tempsum = 0;
					for(int g = 0 ; g< charlas[charlasrestantes[h]].n;g++){
						tempsum = tempsum + preferences[p][charlas[charlasrestantes[h]].charlas[g]];
					}
					// if(j == 71){
					// 	std::cout << "h: "<<h <<"j: "<<j<<"Charla restante:"<<charlasrestantes[j] <<"Preferencia"<<preferences[h][charlasrestantes[j]]<<'\n';
					//
					// }
					tempsum = tempsum + preferences[p][charlasrestantes[j]];
					if(tempsum != 0){
						newsum= newsum + tempsum-1;
					}
				}
				// std::cout<<"Charla " <<charlasrestantes[h]<<"\t" <<"Charla2: "<<charlasrestantes[j]<<"\t"<< "Cruce: " <<charlas[charlasrestantes[h]].cruce <<"\t"<<"Suma: "<<newsum<<"\t"<<"N: "<<charlas[charlasrestantes[h]].n<<'\n';
				if(charlas[charlasrestantes[h]].cruce>newsum&&charlas[charlasrestantes[h]].n != sessions){
					changed = 1;
					charlas[charlasrestantes[h]].charlas[charlas[charlasrestantes[h]].n] =charlasrestantes[j];
					charlas[charlasrestantes[h]].cruce = newsum;
				}
			}
		}
		if(changed == 1){
			charlas[charlas[charlasrestantes[h]].charlas[charlas[charlasrestantes[h]].n]].considerado = 1;
			charlas[charlasrestantes[h]].n++;
			for(int p = 1 ; p<charlas[charlasrestantes[h]].n;p++){
				charlas[charlas[charlasrestantes[h]].charlas[p]].n = charlas[charlasrestantes[h]].n;
			}
		}
		if(charlas[charlasrestantes[h]].n != sessions){
			charlas[charlasrestantes[h]].cruce = 9999999;
			h--;
		}

	}
	int conflicto = 0;
	string nfile="Resultados_"+(string)argv[1];
	ofstream out(nfile);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
	cout <<"Conflictos"<<"\t";
	for(i = 0;i<sessions; i++){
		cout <<"Ch"<<i+1<< "\t";
	}
	std::cout <<'\n';
	for(i=0;i<talks;i++){
		if(charlas[i].cruce != 9999999){
			cout << charlas[i].cruce <<"\t\t\t";
			for(int j=0; j<sessions; j++){
				horario[j].push_back((int)charlas[i].charlas[j]);
				cout <<charlas[i].charlas[j]+1<<"\t";
			}
			std::cout  << '\n';
			// charlas[i].charlas[0]+1<<"\t"<<charlas[i].charlas[1]+1<<"\t"<<charlas[i].charlas[2]+1<<"\t"<<'\n';
			conflicto = conflicto+ charlas[i].cruce;
		}
	}
	std::cout <<"\n"<< "Conflicto total: "<< conflicto<< '\n';
	cout.rdbuf(coutbuf);

  return 0;
}
