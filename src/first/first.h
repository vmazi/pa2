#ifndef FIRST_H_
#define FIRST_H_

#include <stdio.h>

struct trienode;
struct CLL;
struct listnode;
struct ans;
void  addEnd (char val,struct CLL* list);
char* CLLtoStr(struct CLL* list);
void printCLL(struct CLL* list);
void deleteCLL (struct CLL* list);
struct trienode* TrieCreateNode(char key);
struct trienode* TrieSearch(struct trienode* start, char* key);
void TrieAdd(struct trienode **root, char *key);
void TrieIncr(struct trienode **root, char *key);
void matchStr(char* str);
void useData (FILE* data_file);
void readDict(FILE* dict_file);
struct trienode*  TrieSearchBuild(struct trienode **root, char *key);
struct ans*  buildAnswer(char*  dict,struct trienode** root);
int ListLength (struct ans *list);
struct ans *SelectPivot(struct ans *list);
struct ans *Quicksort(struct ans *list);
void printResult();

#endif //FIRST_H_
