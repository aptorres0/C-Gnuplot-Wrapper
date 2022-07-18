#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double *X_array;
  double *Y_array;
  char *TITLE;
  char *xlabel;
  char *ylabel;
  char **gnuplot_commands;
} gnu_plot;

void show_gnu_2D_plot(gnu_plot plot) {
  /* Opens an interface that one can use to send commands to gnuplot
   *    as if they were typed into the gnuplot command line. The
   *    "-persistent" flag keeps the plot open even after the C
   *    program terminates.
   */
  FILE *gnuplot = popen("gnuplot -persistent", "w");
  if (!gnuplot) {
    perror("popen");
    exit(EXIT_FAILURE);
  }

  // setting titles and axis labels
  fprintf(gnuplot, "set title \'%s\'\n", plot.TITLE);
  fprintf(gnuplot, "set xlabel \'%s\'\n", plot.xlabel);
  fprintf(gnuplot, "set ylabel \'%s\'\n", plot.ylabel);
  fprintf(gnuplot, "set autoscale\n");
  fprintf(gnuplot, "set xtic auto\n");
  fprintf(gnuplot, "set ytic auto\n");

  // Passing additional gnuplot commands
  size_t NUM_COMMANDS =
      sizeof(plot.gnuplot_commands) / sizeof(plot.gnuplot_commands[0]);

  // enter data into gnuplot
  fprintf(gnuplot, "plot '-' using 1:2 with linespoints\n");
  for (int i = 0; i < 6; ++i) {
    fprintf(gnuplot, "%f %f\n", plot.X_array[i], plot.Y_array[i]);
  }
  fprintf(gnuplot, "e\n");

  fprintf(stdout, "Click Ctrl+d to quit...\n");
  fflush(gnuplot);
  getchar();

  pclose(gnuplot);
}

void add_gnuplot_command(gnu_plot plot, char *cmd) {
  // See how many commands are already present
  size_t NUM_COMMANDS =
      sizeof(plot.gnuplot_commands) / sizeof(plot.gnuplot_commands[0]);
  plot.gnuplot_commands[NUM_COMMANDS + 1] = cmd;
}
