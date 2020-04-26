#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 最後的結果是 unix time(從0開始)，以及coverage(次數)
 * 假如有定義hr的話，就輸出還不到hr的所有資料（ex : hr = 1, 則輸出一小時內的所有資料）
 *
 */

int main (int argc, char *argv[]) {

  if (argc < 2) {
    cout << "trans plot data : [plot data] [hr]" << endl;
    exit(-1);
  }

  vector<vector<string>> totalst;
  vector<string> temp;
  int hr = -1;

  if(argc > 2) {
    hr = atoi(argv[2]);
  }

  FILE *fp;
  char buffer[10000];

  fp = fopen(argv[1], "r");
 
  if (fp == NULL) {
    printf("open sq-fuzz plot-data failed\n");
    return -1;
  }

  int i = 0, j = 0;
   
  while (fscanf(fp, "%s\n", buffer) == 1) {

    if (i > 11) {
      j++;

      temp.push_back(string(buffer));
      
      if (j == 11) {
        totalst.push_back(temp);
        temp.clear();	
        j = 0;
      }
    }
      
    i++;
  }

  fclose(fp);
 
  unsigned long event_s = strtoul(totalst[0][0].c_str(), NULL, 10);

  for (int i = 0;i < totalst.size();i++) {
    unsigned long cur_s = strtoul(totalst[i][0].c_str(), NULL, 10);

    if (((cur_s-event_s) / 60 / 60) >= hr && hr != -1) {
      //printf("break! hr = %d, cur_s = %lu\n", hr, cur_s);
      break;
    }

    printf("%lf, ", (double)(cur_s-event_s)/60/60);

    double cov_per = strtod(totalst[i][6].c_str(), NULL);
    cov_per /= 100;
    cov_per *= 65536;

    printf("%d\n", (int)cov_per);
  }
  



  return 0;
}
