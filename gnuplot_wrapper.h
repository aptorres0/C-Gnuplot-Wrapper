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

int NUMBER_GNUPOLT_ARGS = 0;

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
  for (int i = 0; i < NUMBER_GNUPOLT_ARGS; i++) {
    fprintf(gnuplot, "%s\n", plot.gnuplot_commands[i]);
  }

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

void add_gnuplot_command(gnu_plot *plot, char *cmd) {
  if (NUMBER_GNUPOLT_ARGS == 0) {
    plot->gnuplot_commands = malloc(sizeof(cmd));
    plot->gnuplot_commands[NUMBER_GNUPOLT_ARGS] = cmd;
    NUMBER_GNUPOLT_ARGS++;
    return;
  } else {
    // Add to array of commands
    char **tmp = realloc(plot->gnuplot_commands,
                         sizeof(plot->gnuplot_commands) + sizeof(cmd));
    if (tmp == NULL) {
      free(plot->gnuplot_commands);
      exit(EXIT_FAILURE);
    } else {
      plot->gnuplot_commands = tmp;
    }
    plot->gnuplot_commands[NUMBER_GNUPOLT_ARGS] = cmd;
    NUMBER_GNUPOLT_ARGS++;
  }
}
