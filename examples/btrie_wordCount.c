#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../btrie.h"

#define MAX_WORD 50

struct BTrie t;

struct word {
	char text[MAX_WORD];
	int num;
};

void update_count(char *buf, int len) {
	struct word *word = (struct word *)btrie_lookup(&t, buf, len);
	if (!len) return;
	if (word) {
		word->num++;
	} else {
		word = (struct word *)calloc(1, sizeof(struct word));
		strncpy(word->text, buf, MAX_WORD);
		word->num = 1;
		btrie_insert(&t, word->text, len, word);
	}
}

void word_print(void *w) {
	struct word *word = (struct word *)w;
	printf("%s (%d instances)\n", word->text, word->num);
}

int main(int argc, char **argv) {
	const char *filename = (argc == 2) ? argv[1] : "default.txt";
	char c, buf[MAX_WORD];
	
	int i = 0;
	btrie_init(&t);
	FILE *fp = fopen(filename, "r");
	if (!fp) { printf("Error opening file.\n"); return 0; }
	while ((c = fgetc(fp)) != EOF) {
		if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
			buf[i++] = c;
		else {
			buf[i] = '\0';
			update_count(buf, i);
			i = 0;
		}
	}
	fclose(fp);

	t.prnt = word_print;
	btrie_print(&t);

	return 0;
}