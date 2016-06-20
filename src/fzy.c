#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "match.h"
#include "tty.h"
#include "choices.h"
#include "options.h"
#include "tty_interface.h"

#include "../config.h"

options_t options;

int main(int argc, char *argv[]) {
	options_parse(&options, argc, argv);

	choices_t choices;
	choices_init(&choices);
	choices_fread(&choices, stdin);

	if (options.benchmark) {
		if (!options.filter) {
			fprintf(stderr, "Must specify -e/--show-matches with --benchmark\n");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < options.benchmark; i++)
			choices_search(&choices, options.filter);
	} else if (options.filter) {
		choices_search(&choices, options.filter);
		for (size_t i = 0; i < choices_available(&choices); i++) {
			if (options.show_scores)
				printf("%f\t", choices_getscore(&choices, i));
			printf("%s\n", choices_get(&choices, i));
		}
	} else {
		/* interactive */
		tty_t tty;
		tty_init(&tty, options.tty_filename);

		if (options.num_lines > choices.size)
			options.num_lines = choices.size;

		if (options.num_lines + 1 > tty_getheight(&tty))
			options.num_lines = tty_getheight(&tty) - 1;

		tty_interface_t tty_interface;
		tty_interface_init(&tty_interface, &tty, &choices, &options);
		tty_interface_run(&tty_interface);
	}

	choices_destroy(&choices);

	return 0;
}