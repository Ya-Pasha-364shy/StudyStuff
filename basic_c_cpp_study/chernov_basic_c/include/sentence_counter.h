#ifndef _SENTENCE_COUNTER_H_
#define _SENTENCE_COUNTER_H_

int count_words(const char sentence[256]);
int longest_sentence_in_file(const char* filename, char longest_sentence[256]);

#endif // _SENTENCE_COUNTER_H_