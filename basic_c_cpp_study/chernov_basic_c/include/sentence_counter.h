#ifndef _SENTENCE_COUNTER_H_
#define _SENTENCE_COUNTER_H_

#define MAX_STR_LENGTH 256

int count_words(const char sentence[MAX_STR_LENGTH]);
int longest_sentence_in_file(const char* filename, char longest_sentence[MAX_STR_LENGTH]);

#endif // _SENTENCE_COUNTER_H_