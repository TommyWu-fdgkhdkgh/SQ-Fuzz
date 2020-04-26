#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
 * input  -> a plot file
 * output -> time < - > plot file 
 *
 */


/* Describe time delta. Returns one static buffer, 34 chars of less. */

char* DTD(unsigned long cur_s, unsigned long event_s) {

  static char tmp[64];
  unsigned long delta;
  int t_d, t_h, t_m, t_s;

  if (!event_s) return (char* )"none seen yet";

  delta = cur_s - event_s;

  //t_d = delta / 1000 / 60 / 60 / 24;
  //t_h = (delta / 1000 / 60 / 60); //% 24;
  t_h = (delta  / 60 / 60); //% 24;
  //t_m = (delta / 1000 / 60) % 60;
  t_m = (delta  / 60) % 60;
  //t_s = (delta / 1000) % 60;
  t_s = (delta ) % 60;

  sprintf((char *)tmp, "%u hrs| %u min| %u sec", t_h, t_m, t_s);

  //想要在某個小時停下來，可以在這邊插一個if
  /*
  if (t_h == 12) {
    FATAL("Times up!\n");
  }
  */

  return tmp;

}


int main(int argc, char *argv[]) {


  if (argc < 2) {
    printf("usage : ./time_and_data [plot_data]\n");
    return -1;
  }



  printf("unix time, cycles_done, cur_path, paths_total, pending_total, pending_favs, map_size, unique_crashes, unique_hangs, max_depth, execs_per_sec\n");

  vector<string> temp;
  vector<vector<string>> totalst;


  FILE *fp;
  char buffer[10000];

  fp = fopen(argv[1], "r"); 
 
  if (fp == NULL) {
    printf("open failed\n");
    return -1;
  }

  int i = 0, j = 0;

  while (fscanf(fp, "%s\n", buffer) == 1) {

    if (i > 11) {
      j++;

      //printf("%s\n", buffer);
      temp.push_back(string(buffer));

      if (j == 11) {
        //printf("temp size : %d\n", temp.size());
        totalst.push_back(temp);
        temp.clear();
        j = 0;
      }
    }

    i++;
  }

  unsigned long event_s = strtoul(totalst[0][0].c_str(), NULL, 10);

  for(int i = 0;i < totalst.size();i++) {
   
    unsigned long cur_s = strtoul(totalst[i][0].c_str(), NULL, 10);

    printf("%s, ", DTD(cur_s, event_s));

    for(int j = 1;j < totalst[i].size();j++) {

      if (j == 6) {
        double coverage_percent = strtod(totalst[i][6].c_str(), NULL);
	coverage_percent/= 100;
        coverage_percent*= 65536;
        printf("branch cov : %d| coverage percent : %s", (int)coverage_percent, totalst[i][6].c_str());

      } else {
        printf("%s ", totalst[i][j].c_str()); 

      }
    }
    printf("\n");
  }



  fclose(fp);  



}










