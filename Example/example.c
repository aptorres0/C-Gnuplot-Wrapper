#include "../gnuplot_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  clock_t begin = clock();
  double x[] = {2015, 2016, 2017, 2018, 2019, 2020};
  double y[] = {344, 543, 433, 232, 212, 343};

  gnu_plot myPlot = {.TITLE = "My Example Plot",
                     .xlabel = "My x-axis",
                     .ylabel = "My y-axis",
                     .X_array = x,
                     .Y_array = y};

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  fprintf(stdout, "\nTime spent: %f seconds\n", time_spent);

  show_gnu_2D_plot(myPlot);

  exit(EXIT_SUCCESS);
}
