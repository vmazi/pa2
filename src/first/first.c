#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "first.h"

struct trienode 
{
  char key;
  int occurances;
  int superword;
  struct trienode* next;
  struct trienode* children;
};

struct trienode* root = NULL;

struct CLL 
{
  int count;
  struct listnode* tail;
};
struct listnode
 {
   char data;
   struct listnode* next;
 };
struct ans
{
  char* word;
  int occurances;
  int superword;
  struct ans* next;
};
char* strlwr(char* s)
{
  char *t = s;
 
  if (!s)
    {
      return 0;
    }
 
  
  while ( *t != '\0' )
    {
      if (*t >= 'A' && *t <= 'Z' )
	{
	  *t = *t + ('a' - 'A');
	}
      t++;
    }
 
  return s;
}

void  addEnd (char val,struct CLL* list)
{
  struct listnode* tmp = NULL;
  struct listnode* new = NULL;
  new = (struct listnode*)malloc(1*sizeof(struct listnode));
  new -> data = val;
  new -> next = NULL;
  if (list->tail == NULL)
    {
      
      list->tail = new;
      list-> tail->next = NULL;
      list->count++;
      return;
    }
  else if (list->tail->next == NULL)
    {
      tmp =list->tail;
      list-> tail = new;
      list-> tail->next = tmp;
      tmp->next =list-> tail;
      list->count++;
      return;
    }
  else
    {
      tmp = list ->tail;
      list-> tail = new;
      list-> tail->next = tmp ->next;
      tmp->next = list->tail;
      list->count++;
      return;
    }
}
char* CLLtoStr(struct CLL* list)
{
  struct listnode* point;
  int count = list->count;
  char* str = NULL; 
  str = (char *) calloc(count,sizeof(char));
  int ptr;
  if(list->tail == NULL)
    {
      free(str);
      str = NULL;
      return NULL;
    }
  else if(list->tail->next == NULL)
    {
      point = list->tail;
    }
  else
    {
      point = list->tail->next;
    }
 
  for(ptr = 0; ptr<count;ptr++)
    {
      str[ptr] = point->data;
      point = point->next;
    }
  return str;
}
void printCLL(struct CLL* list)
  {
    if(list->tail == NULL)
      {
	return;
      }
    struct  listnode* ptr = list->tail->next;;
    int count = list->count;
    if(ptr == NULL)
      {
	printf("%c",list->tail->data);
	return;  
      }
    while (count!=0)
      {
	printf("%c",ptr->data);
	ptr = ptr->next;
	count--;	
      }
    printf("\n");
    return;
  }
void deleteCLL (struct CLL* list)
{
  if(list->tail == NULL)
    {
      return;
    }
  struct  listnode* ptr = list->tail->next;;
  struct listnode* tmp;
  tmp = ptr;
  int count = list->count;
  if(ptr == NULL)
    {
      free(list->tail);
      list->tail = NULL;
      list->count = 0;
      return;
    }
  while (count!=1)
    {
  
      ptr = ptr->next;
      free(tmp);
      tmp = ptr;
      count--;
    }
  free(ptr);
  ptr = NULL;
  tmp = NULL;
  list->tail = NULL;
  list->count = 0;
  return;
}

struct trienode* TrieCreateNode(char key)
{
  struct trienode* node=NULL;
  node = (struct trienode*)malloc(1*sizeof(struct trienode));
  node->key = key;  
  node->occurances = 0;
  node->superword = 0;
  node->next = NULL;
  node->children = NULL;
  return node;

}
struct trienode* TrieSearch(struct trienode* start, char* key)
{
  char* ptr = key;
  struct trienode* level = start;
  
  
  while(1)
    {
      struct trienode *found = NULL;
      struct trienode *curr;
      
      for (curr = level; curr != NULL; curr = curr->next)
	{
	  if (curr->key == *ptr)
	    {
	      found = curr;
	      
	      break;
	    }
	}
      if(curr == NULL)
	{
	  return NULL;
	}
      ptr++;
      if (*ptr=='\0')
	{
	  
	  return found;
	   
	}
      if (found->children == NULL)
	{
	  return NULL;
	}
      level = found->children;
      
    }
}

void TrieAdd(struct trienode **root, char *key)
{
  struct trienode* pTrav = NULL;
  
  if(NULL == *root)
    {
      printf("NULL tree\n");
      return;
    }
  if(key == NULL)
    {
      return;
    }  
  pTrav = (*root)->children;
  
  
  
  if(pTrav == NULL)
    {
      
      for(pTrav = *root; *key; pTrav = pTrav->children)
	{
	  pTrav->children = TrieCreateNode(*key);
	  key++;
	}
 
      return;
    }
 
  if(TrieSearch(pTrav, key))
    {
      return;
    }
 
  while(*key != '\0')
    {
      if(*key == pTrav->key)
	{
	  key++;
	  if(pTrav->children == NULL)
	    {
	      struct trienode* ptr1;
	      for(ptr1 =pTrav;*key;key++)
		{
		  ptr1->children = TrieCreateNode(*key);
		  ptr1 = ptr1->children;
		}
	      return;
	    }
	  pTrav = pTrav->children;
	}
      else
	break;
    }
 
  while(pTrav->next)
    {
      if(*key == pTrav->next->key)
	{
	  key++;
	  TrieAdd(&(pTrav->next), key);
	  return;
	}
      pTrav = pTrav->next;
    }
 
  if(*key)
    {
      pTrav->next = TrieCreateNode(*key);
    }
  else
    {    
      return;
    }
  key++;
 
  for(pTrav = pTrav->next; *key; pTrav = pTrav->children)
    {
      pTrav->children = TrieCreateNode(*key);
      key++;
    }
 
  return;
}


void  TrieIncr(struct trienode **root, char *key)
{

  char* ptr = key;
  struct trienode* level = (*root)->children;;
  

  while(1)
    {
      struct trienode *found = NULL;
      struct trienode *curr;

      for (curr = level; curr != NULL; curr = curr->next)
        {
          if (curr->key == *ptr)
            {
	      curr->superword++;
              found = curr;

              break;
            }
        }
      if(curr == NULL)
        {
          return;
        }
      ptr++;
      if (*ptr=='\0')
        {
	  found->superword--;
	  found->occurances++;
          return;

        }
      if (found->children == NULL)
        {
          return;
        }
      level = found->children;

    }


}
void matchStr(char* str)
{
  if(!(str))
    {
      return;
    }
  TrieIncr(&root,str);
}
void useData(FILE* data_file)
{

  char* str;
  char c;

  struct CLL* word = NULL;
  word = (struct CLL*) malloc(1*sizeof(struct CLL));
  word->count = 0;
  word->tail = NULL;


  FILE* file = data_file;
  while(!feof(file))
    {
      c = fgetc(file);
      if(isalpha(c)!=0)
        {
          addEnd(c,word);

        }
      else
        {

          str = CLLtoStr(word);
          deleteCLL(word);
	  str =  strlwr(str);
	  matchStr(str);
          free(str);
          str = NULL;
        }
    }
  

}
void readDict(FILE* dict_file)
{
  
  char* str;
  char c;

  struct CLL* word = NULL;
  word = (struct CLL*) malloc(1*sizeof(struct CLL));
  word->count = 0;
  word->tail = NULL;

  FILE* file = dict_file;
  while(!feof(file))
    {
      c = fgetc(file);
      if(isalpha(c)!=0)
        {
          addEnd(c,word);


        }
      else
        {
          
          str = CLLtoStr(word);
          deleteCLL(word);
	  str = strlwr(str);
          TrieAdd(&root,str);
          free(str);
          str = NULL;
        }
    }
  

} 


struct ans* answer = NULL;

struct trienode*  TrieSearchBuild(struct trienode **root, char *key)
{

  char* ptr = key;
  if(!ptr)
    {
      return NULL;
    }
  struct trienode* level = (*root)->children;;


  while(1)
    {
      struct trienode *found = NULL;
      struct trienode *curr;

      for (curr = level; curr != NULL; curr = curr->next)
        {
          if (curr->key == *ptr)
            {
              
              found = curr;

              break;
            }
        }
      if(curr == NULL)
        {
          return NULL;
        }
      ptr++;
      if (*ptr=='\0')
        {
          
          return found;

        }
      if (found->children == NULL)
        {
          return NULL;
        }
      level = found->children;

    }


}


struct ans*  buildAnswer(char*  dict,struct trienode** root)
{
  char* str;
  char c;
  struct CLL* word = NULL;
  word = (struct CLL*) malloc(1*sizeof(struct CLL));
  word->count = 0;
  word->tail = NULL;


  
  struct trienode* ptr = NULL;
  struct ans* head = NULL;
  struct ans* result = NULL;
  
  FILE* file = fopen(dict,"r");
  while(!feof(file))
    {
      c = fgetc(file);
      if(isalpha(c)!=0)
        {
          addEnd(c,word);


        }
      else
        {

          str = CLLtoStr(word);
	  if(!str)
	    {
	      continue;
	    }
	  str = strlwr(str);
          deleteCLL(word);
	  if(head == NULL)
	    {
	      head = (struct ans*)malloc(1*sizeof(struct ans));
	      head->word = str;
	      ptr = TrieSearchBuild(root,str);
	      if (ptr == NULL)
		{
		  head->occurances = 0;	
		  head->superword = 0;
		}
	      else
		{
		head->occurances = ptr->occurances;
		head->superword = ptr->superword;
		}
	      head->next = NULL;
	      str = NULL;
	    }
	  else
	    {
	      for(result = head;result->next!=NULL;result = result->next)
		{
		  
		}
	      result->next = (struct ans*)malloc(1*sizeof(struct ans));
	      result->next->word = str;
	      ptr = TrieSearchBuild(root,str);
	      if (ptr == NULL)
                {
                  result->next->occurances = 0;
                  result->next->superword = 0;
                }
              else
                {
		  result->next->occurances = ptr->occurances;

                  result->next->superword =  ptr->superword;

		   
		 
                }

	      result->next->next = NULL;
	      
	      str = NULL;
	    }
        }
    }
  fclose(file);
  return head;



}


int ListLength (struct ans *list)
{
  struct ans *temp = list;
     
  int i=0;
  while(temp!=NULL)
    {
      i++;
      temp=temp->next;
 
 
    }
  return i;
}

struct ans *SelectPivot(struct ans *list)
{
  
  int k, n, i = 0;
  n = ListLength(list);
  
  
  struct ans *pivot=list;
  
  
  k=rand()%n;
  for (; i < k; ++i)
    {
      pivot=pivot->next;
    }
  
  return pivot;
}

struct ans *Quicksort(struct ans *list)
{
  // Return NULL list
  if (ListLength(list) <= 1) return list;
  struct ans *less=NULL, *more=NULL, *next, *end, *temp=NULL;

  // Select a random pivot point
  struct ans *pivot = SelectPivot(list);

  // Remove pivot from list
  while(list !=NULL)
    {
      next = list->next;

      if(strcmp(list->word,pivot->word)!=0)
        {
	  list->next=temp;
	  temp = list;
        }
      list = next;
    }

  // Divide & Conq
  while(temp != NULL)
    {
      next = temp->next;
      if(strcmp(temp->word,pivot->word)<0)
        {
	  temp->next = less;
	  less = temp;
        }
      else 
        {
	  temp->next = more;
	  more = temp;    
        }
      temp = next;
    }

  // Recursive Calls
  less = Quicksort(less);
  more = Quicksort(more);

  // Merge
  if(less != NULL)
    {
      end = less;
      while(end->next != NULL){
	end=end->next;
      }
      pivot->next=more;
      end->next = pivot;
      return less;        
    }
  else{
    pivot->next = more;
    return pivot;   
  }

}

int outnumber;

void printResult()
{
  int length;
  struct ans* res = answer;
  char* outnum2str  = NULL;
  length = snprintf(NULL,0,"%d",outnumber);
  outnum2str =(char*) malloc(length+1);
  snprintf(outnum2str,length+1,"%d",outnumber);
  char* outfile = (char*)malloc(length+1+sizeof("out")+sizeof(".txt"));
  strcpy(outfile,"out");
  strcat(outfile,outnum2str);
  strcat(outfile,".txt");
  FILE* write = fopen(outfile,"w");
  while(res!=NULL)
    {
      fputs(res->word,write);
      fputc(' ',write);
      fprintf(write,"%d",res->occurances);
      fputc(' ',write);
      fprintf(write,"%d",res->superword);
      fputc('\n',write);
      res = res->next;
    }
  fclose(write);
}
int main(int argc, char** argv)
{
  
  root = TrieCreateNode('\0');
  outnumber = 0;  
  char* dict=NULL;
  char* data=NULL;   
  FILE* dict_file = NULL;
  FILE* data_file = NULL;
  if (argc != 2)
    {
      return 0;
    }
  FILE* file;
  file = fopen(argv[1],"r");

  char* str;
  char c;

  while(1)
    {

      struct CLL* word = NULL;
      word = (struct CLL*) malloc(1*sizeof(struct CLL));
      word->count = 0;
      word->tail = NULL;
      
      c = fgetc(file);
      if(c == EOF)
	{
	  fclose(file); 
	  return 0;
	}
      while(!isspace(c))
	{
	  addEnd(c,word);
	  c = fgetc(file);
	  
	}
      str = CLLtoStr(word);
      deleteCLL(word);
      dict = str;    
      
      str = NULL;
      while(isspace(c))
	{
	  c = fgetc(file);
	  if (c == EOF)
	    {
	      fclose(file);
	      return 0;
	    }
	}

      while(!isspace(c))
        {
	  addEnd(c,word);
	  c = fgetc(file);
	  if (c==EOF)
	    {
	      fclose(file);
              return 0;

	    }
        }
      str = CLLtoStr(word);
      deleteCLL(word);
      data = str;
      str = NULL;
      
      dict_file = fopen(dict,"r");
      data_file = fopen(data,"r");
      outnumber++;
      readDict(dict_file);
      useData(data_file);
      answer = buildAnswer(dict,&root);
      answer = Quicksort(answer);
      printResult();
      root = NULL;
      root = TrieCreateNode('\0');
      fclose(dict_file);
      dict_file = NULL;
      fclose(data_file);
      data_file = NULL;
      
      dict=NULL;
      
      data=NULL;
     
    };
  fclose(file);
  return 0;
}
	 	 
	 
