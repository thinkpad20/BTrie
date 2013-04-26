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

struct word **words;

char *tolowerstr(char *str) {
	int i, len = (int)strlen(str);
	for (i = 0; i < len; ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void update_count(char *buf, int len) {
	if (!len) return;
    
	struct word *word = (struct word *)btrie_lookup(&t, buf, len);
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

struct word_copyToArrayArgs{
	struct word **array;
	int index;
	struct word *word;
};

void word_copyToArray(void *w) {
	static int i = 0;
	words[i++] = (struct word *)w;
}

int word_compare(const void *w1, const void *w2) {
	struct word **word1 = (struct word **)w1,
    **word2 = (struct word **)w2;
	return strcmp((*word1)->text, (*word2)->text);
}

void word_printAlpha() {
	int i;
	words = (struct word **)malloc(t.size * sizeof(struct word *));
	btrie_map(&t, word_copyToArray);

	qsort(words, t.size, sizeof(struct word *), word_compare);
	for (i=0; i<t.size; ++i) {
		word_print(words[i]);
	}
}

int main(int argc, char **argv) {
	const char *filename = (argc >= 2) ? argv[1] : "default.txt";
	char c, buf[MAX_WORD];
	
	int i = 0, nWords = 0;
	btrie_init(&t);
	t.dir = 1;
	FILE *fp = fopen(filename, "r");
	if (!fp) { printf("Error opening file.\n"); return 0; }
	while ((c = fgetc(fp)) != EOF) {
		if ((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
			buf[i++] = c;
		else if (c == '\'')
			continue;
		else {
			buf[i] = '\0';
			update_count(tolowerstr(buf), i);
			i = 0;
			nWords++;
		}
	}
	fclose(fp);
    
	t.prnt = word_print;
	btrie_print(&t);
	// word_printAlpha();
	printf("Total %d words, %lu distinct.\n", nWords, t.size);
	btrie_delete(&t);
    
	return 0;
}