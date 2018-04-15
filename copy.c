//end of /9
//this is a double link list, add and delete node in the specific position. Also I will reprsent the struct as a pointer function. it is useful to allocate the memory.
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
    void  *value;
    struct Node *next;
    struct Node *prev;
} Node;
 //I make a double link list and design a pointer struct which is similar with lab03
typedef struct IteratorGRep {
    ElmCompareFp  compareFuncP;
    ElmNewFp      newFuncP;
    ElmFreeFp     freeFuncP;
    //the function pointer which lecture give us
    Node *curr_prev;//I use two node because it will help me to find previous and next node
    Node *curr_next;
    Node *first;
    Node *last;

    //use the curr for the last time;
    int use_curr_prev;
    int use_curr_next;
} IteratorGRep;

   31  //set the pointer function
   32  IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp){
   33      IteratorG new;
   34          if ((new = malloc(sizeof(struct IteratorGRep))) == NULL) {
   35            fprintf(stderr, "Error!!  .... \n");
            ^
            + ================== +
            + indentation errors +
            + ================== +
   36          }
   37
   38          new->first = new->last = new->curr_next = new->curr_prev = NULL;
   39          new->use_curr_prev = new->use_curr_next = 0;
   40          new->compareFuncP = cmpFp;
   41          new->newFuncP = newFp;
   42          new->freeFuncP = freeFp;
   43
   44      return new;
   45
   46  }
   47  //add the node in to appropriate position
   48  //if succeed return 1
   49  //else return 0
   50  int  add(IteratorG it, void *vp){
   51
   52      it->use_curr_prev = 0;
   53      it->use_curr_next = 0;
   54
   55      assert(it != NULL);
   56
   57      Node *new;
   58
   59      if ((new = malloc(sizeof(Node))) == NULL) {
   60                  return 0;
   61          }
   62          new->value = it->newFuncP(vp);
   63          new->next = new->prev = NULL;
   64          //the first condition is the first time to add the node
   65          if(it->first == NULL){
   66
   67              it->first = new;
   68              it->last = new;
   69              it->curr_prev = new;
   70              it->curr_next = NULL;
   71
   72              return 1;
   73        } else{
   76          //the second condition is add the node in the last of list
   77          if(it->curr_next == NULL){
   78              it->last->next = new;
   79              new->prev = it->last;
   80              it ->last = new;
   81              it->curr_prev = it->last;
   82              it->curr_next = NULL;
   83
   84              return 1;
   85
   86          } else if(it->curr_prev ==NULL){
   89              it->first->prev = new;
   90              new->next = it->first;
   91              it ->first = new;
   92
   93              it->curr_prev = NULL;
   94              it->curr_next = it->first;
   95              return 1;
   96
   97          } else{
  100              it->curr_prev->next = new;
  101              new->prev = it->curr_prev;
  102              new->next = it->curr_next;
  103              it->curr_next->prev = new;
  104              it->curr_prev = new;
  105              return 1;
  106
  107          }
  108      }
  109      return 0;
  110  }
  111
  112  //check the the curr has next node
  113  //if has return 1
  114  //if not return 0
  1   int  hasNext(IteratorG it){
  116      assert (it!=NULL);
  117      it->use_curr_prev = 0;
  118      it->use_curr_next = 0;
  119      if(it->curr_next!=NULL){
  120          return 1;
  121      }
  122
  123      return 0;
  124  }
  125  //check the the curr has previous node
  126  //if has return 1
  127  //if not return 0
  128  int  hasPrevious(IteratorG it){
  129      assert (it!=NULL);
  130      it->use_curr_prev = 0;
  131      it->use_curr_next = 0;
  132      if(it->curr_prev!=NULL){
  133          return 1;
  134      }
  135
  136
  137      return 0;
  138  }
  139
  140  //return the last time recall the value of next node
  141  //if can not find the node return NULL;
  142  void *next(IteratorG it){
  143      assert (it!=NULL);
  144      if(hasNext(it)){
  145          it->curr_prev = it->curr_next;
  146          it->curr_next = it->curr_next->next;
  147          it->use_curr_prev = 1;
  148          it->use_curr_next = 0;
  149
  150          return it->curr_prev->value;
  151
  152      }
  153      it->use_curr_prev = 0;
  154      it->use_curr_next = 0;
  155
  156      return NULL;
  157  }
  158
  159  //return the last time recall the value of previous node
  160  //if can not find the node return NULL;
  161  void *previous(IteratorG it){
  162      assert (it!=NULL);
  163      if(hasPrevious(it)){
  164          it->curr_next = it->curr_prev;
  165          it->curr_prev = it->curr_prev->prev;
  166          it->use_curr_prev = 0;
  167          it->use_curr_next = 1;
  168
  169          return it->curr_next->value;
  170      }
  171
  172      it->use_curr_prev = 0;
  173      it->use_curr_next = 0;
  174
  175      return NULL;
  176
  177  }
  178
  179  //reset the curr in front of the lsit
  180  void reset(IteratorG it){
  181      assert (it!=NULL);
  182      it->curr_next = it->first;
  183      it->curr_prev = NULL;
  184      it->use_curr_prev = 0;
  185      it->use_curr_next = 0;
  186
  187  }
  188
  189  //delete the curr after recall prev and next
  190  int  delete(IteratorG it){
  191      assert (it!=NULL);
  192      //the first condition is the list is empty
  193      if(it->first == NULL){
  194          it->use_curr_prev = 0;
  195          it->use_curr_next = 0;
  196              return 0;
  197
  198      }
  199      //the second condition is recall by *next and *findnext in the last time
  200      if(it->use_curr_next){
  201
  202          Node *delete = it->curr_next;
  203
  204          if(it->curr_next == it->first){
  205              if(it->first->next == NULL){
  206                  it->first = NULL;
  207                  it->last = NULL;
  208                  it->curr_prev = NULL;
  209                  it->curr_next = NULL;
  210
  211              } else{
  213                  it->curr_next = it->curr_next->next;
  214                  it->curr_prev = NULL;
  215                  it->first = it->curr_next;
  216                  it->first->prev = NULL;
  217
  218              }
  219          } else if(it->curr_next == it->last){
  221              it->last = it->last->prev;
  222              it->curr_next = NULL;
  223              it->last->next = NULL;
  224
  225
  226          } else{
  229              it->curr_next= it->curr_next->next;
  230              it->curr_next->prev = it->curr_prev;
  231              it->curr_prev->next = it->curr_next;
  232
  233          }
  234
  235          it->freeFuncP(delete);
  236
  237          it->use_curr_prev = 0;
  238          it->use_curr_next = 0;
  239          return 1;
  240
  241      }
  242      //the third condition is recall by *prev and *findprev in the last time
  243      if(it->use_curr_prev){
  244          Node *delete = it->curr_prev;
  245          if(it->curr_prev == it->first){
  246              if(it->first->next == NULL){
  247                  it->curr_prev = NULL;
  248                  it->last = NULL;
  249                  it->first = NULL;
  250                  it->curr_next = NULL;
  251
  252              } else{
  254                  it->first = it->first->next;
  255                  it->curr_prev = NULL;
  256                  it->curr_next = it->first;
  257                  it->first->prev = NULL;
  258
  259              }
  260
  261          } else if(it->curr_prev == it->last){
  263              it->last = it->last->prev;
  264              it->curr_prev = it->last;
  265              it->curr_next = NULL;
  266              it->last->next = NULL;
  267
  268
  269          }else{
  271              it->curr_prev=it->curr_prev->prev;
  272              it->curr_prev->next = it->curr_next;
  273              it->curr_next->prev = it->curr_prev;
  274
  275          }
  276          it->freeFuncP(delete);
  277          it->use_curr_prev = 0;
  278          it->use_curr_next = 0;
  279          return 1;
  281      }
  282
  283
  284
  285
  286      return 0;
  287  }
  288
  289  //set the vp after recall prev and next
  290  int  set(IteratorG it, void *vp){
  291      assert (it!=NULL);
  292      //recall by prev
  293      if(it->use_curr_prev){
  294          Node *d = it->newFuncP(it->curr_prev->value);
  295          it->curr_prev->value = vp;
  296          it->freeFuncP(d);
  297          it->use_curr_prev = 0;
  298          it->use_curr_next = 0;
  299
  300          return 1;
  301
  302      }
  303      //recall by next
  304      if(it->use_curr_next){
  305          Node *d = it->newFuncP(it->curr_next->value);
  306          it->curr_next->value = vp;
  307          it->freeFuncP(d);
  308          it->use_curr_prev = 0;
  309          it->use_curr_next = 0;
  310          return 1;
  311      }
  312
  313      return 0;
  314  }
  315  //free the list
  316  void freeIt(IteratorG it){
  317      assert (it!=NULL);
  318      Node *F = it->first;
  319      while(F != NULL){
  320          Node *d = F->next;
  321          Node *q = it->newFuncP(F->value);
  322          it->freeFuncP(q);
  323          it->freeFuncP(F);
  324          F = d;
  325      }
  326      it->freeFuncP(it);
  327      it->use_curr_prev = 0;
  328      it->use_curr_next = 0;
  329
  330  }
  331  //find the value in next position same as vp
  332  void *findNext(IteratorG it, void *vp){
  333      assert (it!=NULL);
  334      Node *find = it->curr_next;
  335
  336      while(find !=NULL){
  337          if(it->compareFuncP(vp,find->value)==0){
  338              it->curr_next = find->next;
  339              it->curr_prev = find;
  340              it->use_curr_prev = 1;
  341              it->use_curr_next = 0;
  342              return find->value;
  343          }
  344
  345          find = find->next;
  346      }
  347      it->use_curr_prev = 0;
  348      it->use_curr_next = 0;
  349      return NULL;
  350
  351  }
  352  //find the value in prev position same as vp
  353  void *findPrevious(IteratorG it, void *vp){
  354
  355      assert (it!=NULL);
  356      Node *find = it->curr_prev;
  357
  358
  359      while(find!= NULL){
  360
  361          if(it->compareFuncP(vp,find->value)==0){
  362              it->curr_prev = find->prev;
  363              it->curr_next = find;
  364              it->use_curr_prev = 0;
  365              it->use_curr_next = 1;
  366              return find->value;
  367          }
  368          find = find->prev;
  369      }
  370      it->use_curr_prev = 0;
  37       it->use_curr_next = 0;
  372
  373      return NULL;
  374
  375  }
  376
