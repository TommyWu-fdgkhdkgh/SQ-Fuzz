//https://passer20130912.pixnet.net/blog/post/237400478-%E7%B5%82%E7%AB%AF%E6%A9%9F%E7%9A%84%E6%96%87%E5%AD%97%E5%8B%95%E7%95%AB
//https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
//ANSI Escape Sequence(VT100控制碼)

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define TERM_HOME     "\x1b[H"
#define TERM_CLEAR    TERM_HOME "\x1b[2J"
#define CLEAR_1_line  "\x1b[2K"
#define GG(x)         printf("%d\n", (x))

#  define cBLK "\x1b[0;30m"
#  define cRED "\x1b[0;31m"
#  define cGRN "\x1b[0;32m"
#  define cBRN "\x1b[0;33m"
#  define cBLU "\x1b[0;34m"
#  define cMGN "\x1b[0;35m"
#  define cCYA "\x1b[0;36m"
#  define cLGR "\x1b[0;37m"
#  define cGRA "\x1b[1;90m"
#  define cLRD "\x1b[1;91m"
#  define cLGN "\x1b[1;92m"
#  define cYEL "\x1b[1;93m"
#  define cLBL "\x1b[1;94m"
#  define cPIN "\x1b[1;95m"
#  define cLCY "\x1b[1;96m"
#  define cBRI "\x1b[1;97m"
#  define cRST "\x1b[0m"


/*
  TERM HOME 會讓指標移回第一個
  TERM_CLEAR 會往下移一個頁面，所以雖然可以完美的清空一個頁面，但也會不斷往下捲畫面
  \r 可以讓指標回到第一個，並且會清除該行的內容（但有時候又不會清，好怪，例如"aa\r\n"就不會清）
     試了幾次後，可以確定\r在例如printf("aaaa" "\r" "g")這樣沒換行的情況下，是會清空的，但是變成printf("aaaaa" "\rg\n" "gg")這樣有換行的情況下，aaaaa就只有第一個char被換成g，其他則不會變

  \033[K 清除從光標到行尾的內容
   
  \033[nA 光標上移n行
  \033[nB 光標下移n行
  \033[nC 光標右移n行
  \033[nD 光標左移n行
  \033[y;xH設置光標位置

  \033[s 保存光標位置
  \033[u 恢復光標位置
  \033[?25l 隱藏光標
  \033[?25h 顯示光標


 */

int main(){
  /*
  printf("hi\n");
  printf("ggg\n");
  printf("\033[2J");
  printf(TERM_CLEAR);


  for(int i = 0;i < 1000000;i++){
    printf("\r");
    printf(cPIN "%d", i);
  }
  printf("\n");
  printf("\ra");
*/

  printf("aaaaaaaaaaa" "\rg\n" "g");
  //printf("aa" CLEAR_1_line);

  printf("1\n2\n3\n4\n5\n6\n7\n8\n");

  printf("\033[2A" "\033[10C");
  printf("gg\n");

  GG(100);
  AA(1);

  fflush(0);

  return 0;
}




