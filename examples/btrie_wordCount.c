#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../btrie.h"

#define MAX_WORD 50

struct BTrie t;

struct word {
	char text[MAX_WORD];
	int num;
};

char *tolowerstr(char *str) {
	int i, len = strlen(str);
	for (i = 0; i < len; ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void update_count(char *buf, int len) {
	if (!len) return;
	printf("looking up '%s'... ", buf);
	if (!strcmp(buf, "s")) printf("*******************************************s!\n");
	struct word *word = (struct word *)btrie_lookup(&t, buf, len);
	if (word) {
		printf("found it, count is now %d.\n", word->num + 1);
		word->num++;
	} else {
		printf("not found, creating\n");
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
	t.dir = 1;
	FILE *fp = fopen(filename, "r");
	if (!fp) { printf("Error opening file.\n"); return 0; }
	while ((c = fgetc(fp)) != EOF) {
		if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
			buf[i++] = c;
		else {
			buf[i] = '\0';
			update_count(tolowerstr(buf), i);
			i = 0;
		}
	}
	fclose(fp);

	t.prnt = word_print;
	btrie_print(&t);

	return 0;
}