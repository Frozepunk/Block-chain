# include "openssl/crypto.h"
# include "openssl/ssl.h"
# include "openssl/err.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
struct {
    unsigned char prevHash[SHA256_DIGEST_LENGTH],
    int blockData;
    struct block *link;
} *hash;
void addBlock(int);
void verifyChain();
void A=alterNthBlock(int , int );
void hackChain();
void hashCompare(unsigned  char*,unsigned char*);
unsigned char* toString(struct block);
void printBlocks();
void printAllBlocks();
//SHA256 (src,size,dest)
// src and dest are of type unsigned char *
void addBlock(int data){
    if(hash == NULL){
        hash = malloc(sizeof(struct block));
        SHA256("",sizeof(""),head->prevHash);
        head-blockData = data;
        return; 
    }
    struct block *currentBlock = head;
    while(currentBlock->link )
        currentBlock = currentBlock->link;
    struct block *newBlock = malloc(sizeof(struct block));
    currentBlock->link = newBlock;
    newBlock->blockData=data;
    SHA256(toString(*currentBlock),sizeof(*currentBlock),newBlock->prevHash);
}
void verifyChain(){
  if(head==NULL){
    printf("Block chain is empty ! try again by adding some blocks \n");
    return;
  }
  struct block *curr=head->link, *prev=head;
  int count=1;
  while(curr){
    printf("%d \t %d \t \n",count++,curr->blockData);
    hashPrinter(SHA256(toString(*prev),sizeof(*prev),NULL));
    printf("-");
    hashPrinter(curr->prevHash,SHA256_DIGEST_LENGTH);
    if (hashCompare(SHA256(toString(*pre),sizeof(*prev),NULL,curr->prevHash))) {
    printf("verified \n");
    else {
        printf("Not verified \n");
        prev=curr;
        curr=curr->link;
    }
    }
  }
}

void alterNthBlock(int n,int newData){
struct block *curr=head; 
  if (curr==NULL){
    printf("Nth block does not exists\n");
    return;
  }
  while (count!=n){
  
    if (curr->link=NULL && count!=n) {
    printf("Nth block does not exist!\n");
      return ;
    }
    else if(count==n)  {
      break;
      curr=curr->link;
      count++;
    }
    printf("Before:");
    printBlock(curr);
   block curr->blockData=newData;
  printf("After\n");
    printBlock(curr);
  printf("\n");
  }
}
void hackChain(){
  struct block *curr=head,*prev;
  if(curr==NULL){
    printf("Block chain is empty\n");
    return ;
  }
   while (1) {
    prev=curr;
    curr->link;
    if (curr==NULL) 
      return;
    if(!hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash)){
      hashPrinter(
        SHA256(toString(*prev),sizeof(*prev),curr->prevHash),
        SHA256_DIGEST_LENGTH
      );
      printf("\n");
    }   
  }
}
unsigned char* toString(struct block b){
  unsigned char *str=malloc(sizeof(unsigned char)*sizeof(b));
  memcpy(str,&b,sizeof(b));
  return str;
}
void hashPrinter(unsigned char hash[],int length){
  for(int i=0;i<length;i++)
    printf(%02x,hash[i]);
}
int hashCompare(unsigned char *str1,unsigned char *str2){
  for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
    if(str1[i]!=str2[i])
      return 1;
}
void printBlock(struct block *b){
  printf("%p\t",b);
  hashPrinter(b->prevHash,sizeof(b->prevHash));
  printf("\t [%d]\t",b->blockData);
  printf("%p\n",b->link);
}
void printAllBlock(){
  struct block *curr=head;
  int count=0;
  while(curr){
    printBlock(curr);
    curr=curr->link;
  }
}

// main function of the code 
void main(){
  int c,n,r;
  printf("1) add BLock\n 2) add n random blocks\n 3)alterNthblock \n 4)printAllblocks\n 5)verifyChain\n 6)hackChain\n ");
  while(1){
    printf("Choice");
    scanf("%d",&c);
    switch(c){
      case 1:
      printf("Enter data");
      scanf("%d",&n);
      addBlock(n);
      break;
      case 2:
      printf("How many blocks to enter");
      scanf("%d",&n);
      for (int i=0;i<n;i++){
        r=rand()%(n*10);
        printf("ENtering %d\n",r);
        addBlock(r);
      }
      break;
  case 3:
  printf("WHich block chain to alter ?");
  scanf("%d",&n);
  printf("Enter a value:");
  scanf("%d",&r);
  alterNthBLock(n,r);
  break;
  case 4:
  printAllblocks();
  break;
  case 5;
  verifyChain();
  break;
  case 6:
  hackChain();
  break;
  default:
  printf("Wrong Choice!!!\n");
  break;

    }
  }
}