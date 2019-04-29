#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[]) {
  struct winsize ws;

	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}

  FILE* fd = fopen("text_file.txt", "r");   //set terminal window size to 80 * 12 for this txt file
  fseek(fd, 0, SEEK_SET);

  bool is_at_end = false;
  bool is_at_start;
  char user_input;
  int count;
  do
  {
    is_at_start = false;
    if (ftell(fd) == 0 || ftell(fd) == ws.ws_col * (ws.ws_row - 2)) {
      is_at_start = true;
    }

    if (!is_at_start) {
      printf("type b for last page, ");
    }
    if (!is_at_end) {
      printf("press ENTER for next page, ");
    }
    printf("type s to stop program:  ");
    user_input = getchar();
    printf("\n");
    if (user_input == 'b' || user_input == 10) {  // 10 = ENTER
      if (user_input == 'b')
      {
        fseek(fd, count - ws.ws_col * (ws.ws_row - 2), SEEK_CUR);
        getchar();   //bugfix
        is_at_end = false;
      }
      if (!is_at_end) {
        count = 0;
        for(int o = 0; o < ws.ws_row - 2; o++)
        {
          for(int i = 0; i < ws.ws_col; i++)
          {
            int output = fgetc(fd);
            if(output != -1)
            {
              printf("%c", output);
              count--;
            }
            else
            {
                is_at_end = true;
            }
          }
        }
        printf("\n");
      }
    }
  } while(user_input != 's');

  fclose(fd);
  return 0;
}
