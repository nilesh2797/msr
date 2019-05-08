#include <bits/stdc++.h>

using namespace std;

void process(string datafilename, string out_prefix)
{
	ifstream input(datafilename);
	ofstream outx(out_prefix + "_X_Xf.txt"), outy(out_prefix + "_X_Y.txt");
	int num_sample, num_xf, num_yf;

	input >> num_sample >> num_xf >> num_yf;
	outx << num_sample << " " << num_xf << "\n";
	outy << num_sample << " " << num_yf << "\n";

	string line;
	char ch;

	while(getline(input, line))
	{
		if(line.size() > 1)
		{
			stringstream ss(line);

			int y_f;
			ss >> y_f >> ch;
			while(ch == ',')
			{
				outy << y_f << ":1 ";
				ss >> y_f >> ch;
			}
			outy << y_f << ":1" << "\n";

			outx << ss.rdbuf() << "\n";
		}
	}

	input.close();
	outx.close();
	outy.close();
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cerr << "expected two arguments" << endl;
		exit(1);
	}

	// process("../Sandbox/Data/Wiki10/wiki10_train.txt", "../Sandbox/Data/Wiki10/trn");
	process(argv[1], argv[2]);
}