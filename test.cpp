#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

#define NUM_WRITE_BYTE 512
#define NUM_ITER 51200
#define BUF_SIZE 409600
#define COMPUTE_COMPLEXITY 1e3

int main()
{
	for(int bufsize = 2; bufsize <= 4194304; bufsize *= 2)
	{
		ofstream fout("dummyout.txt");
		std::vector<char> buf(bufsize);
		fout.rdbuf()->pubsetbuf(&buf.front(), buf.size());

		char buffer[bufsize];
		int ptr = 0;

		high_resolution_clock::time_point t1, t2, outt1, outt2;
		long long duration = 0, time_taken;

		outt1 = high_resolution_clock::now();

		for(int i = 0; i < NUM_ITER; ++i)
		{
			int ans = 1;
			for(int i = 1; i <= COMPUTE_COMPLEXITY; ++i)
				ans *= i;

			// string str(NUM_WRITE_BYTE, to_string(ans)[0]);
			char ch = to_string(ans)[0];

			t1 = high_resolution_clock::now();

			for(int j = 0; j < NUM_WRITE_BYTE; ++j)
			{
				buffer[ptr] = (ch+j);
				ptr += 1;

				if(ptr == bufsize)
				{
					fout << buffer;
					ptr = 0;
				}
			}

			t2 = high_resolution_clock::now();
			time_taken = duration_cast<nanoseconds>( t2 - t1 ).count();
			duration += time_taken;

			// string str(NUM_WRITE_BYTE, ch);

			// t1 = high_resolution_clock::now();
			// fout << str;
			// t2 = high_resolution_clock::now();
			// time_taken = duration_cast<nanoseconds>( t2 - t1 ).count();
			// duration += time_taken;

			// cout << "time_taken in " << i << "th write : " << time_taken << endl;
		}

		t1 = high_resolution_clock::now();
		fout << buffer;
		t2 = high_resolution_clock::now();
		time_taken = duration_cast<nanoseconds>( t2 - t1 ).count();
		duration += time_taken;


		outt2 = high_resolution_clock::now();

		cout 	<< "total writing time for bufsize : " << bufsize << " is " << duration 
				<< " and overall time is " << duration_cast<nanoseconds>( outt2 - outt1 ).count() << endl;
	}
}