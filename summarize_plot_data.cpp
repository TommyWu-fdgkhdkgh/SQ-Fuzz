#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 統合三個plot data在hours內的edge coverage
 * 最後的結果會是 ： 秒數（從0開始）, SQ-Fuzz's edge coverage(int), afl-fast's edge cov, afl's edge cov
 *
 */

int main (int argc, char *argv[]) {

  if (argc < 4) {
    cout << "summarize plot data : [SQ-Fuzz's plot data] [afl-fast's plot data] [afl's plot data] [hours]" << endl;
    exit(-1);
  }

  vector<string> all_token; 
  vector<vector<string>> sqfuzz_plot_data;
  vector<vector<string>> afl_fast_plot_data;
  vector<vector<string>> afl_plot_data;
  vector<string> temp;
  int hr;

  FILE *fp;
  char buffer[10000];

  /* open sq-fuzz plot-data */

  fp = fopen(argv[1], "r");
 
  if (fp == NULL) {
    printf("open sq-fuzz plot-data failed\n");
    return -1;
  }

  int i = 0, j = 0;
   
  while (fscanf(fp, "%s\n", buffer) == 1) {

    if (i > 11) {
      j++;

      //printf("%s\n", buffer);
      //all_token.push_back(string(buffer));
      temp.push_back(string(buffer));
      
      if (j == 11) {
        //printf("temp size : %d\n", temp.size());
        sqfuzz_plot_data.push_back(temp);
        temp.clear();	
        j = 0;
      }
    }
      
    i++;
  }

  fclose(fp);

  /* open afl-fast plot-data */
  i = 0, j = 0;

  fp = fopen(argv[2], "r");

  if (fp == NULL) {
    printf("open afl-fast plot-data failed\n");
    return -1;
  }

  while (fscanf(fp, "%s\n", buffer) == 1) {
    if (i > 11) {
      j++;
      temp.push_back(string(buffer));

      if(j == 11) {
        afl_fast_plot_data.push_back(temp);
        temp.clear();
        j = 0;	
      } 
    }
    i++; 
  }

  fclose(fp);

  /* open afl plot-data */
  i = 0, j = 0;

  fp = fopen(argv[3], "r");

  if (fp == NULL) {
    printf("open afl-fast plot-data failed\n");
    return -1;
  }

  while (fscanf(fp, "%s\n", buffer) == 1) {
    if (i > 11) {
      j++;
      temp.push_back(string(buffer));

      if(j == 11) {
        afl_plot_data.push_back(temp);
        temp.clear();
        j = 0;	
      } 
    }
    i++; 
  }
  fclose(fp);

  printf("sqfuzz_plot_data.size() : %lu\n", sqfuzz_plot_data.size());
  printf("afl_fast_plot_data.size() : %lu\n", afl_fast_plot_data.size());
  printf("afl_plot_data.size() : %lu\n", afl_plot_data.size());




  return 0;
}
