#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/sha.h> // Include the SHA header file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHA256_DIGEST_LENGTH 32

struct block {
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    int blockData;
    struct block *link;
};

struct block *head = NULL;

void addBlock(int);
void verifyChain();
void alterNthBlock(int, int);
void hackChain();
void hashPrinter(unsigned char[], int);
int hashCompare(unsigned char *, unsigned char *);
unsigned char *toString(struct block);
void printBlock(struct block *);
void printAllBlocks();

void addBlock(int data) {
    if (head == NULL) {
        head = malloc(sizeof(struct block));
        SHA256("", sizeof(""), head->prevHash); // Corrected usage of SHA256
        head->blockData = data;
        return;
    }
    struct block *currentBlock = head;
    while (currentBlock->link)
        currentBlock = currentBlock->link;
    struct block *newBlock = malloc(sizeof(struct block));
    currentBlock->link = newBlock;
    newBlock->blockData = data;
    SHA256((unsigned char *)toString(*currentBlock), sizeof(*currentBlock), newBlock->prevHash); // Corrected usage of SHA256
}

void verifyChain() {
    if (head == NULL) {
        printf("Block chain is empty! Try again by adding some blocks.\n");
        return;
    }
    struct block *curr = head->link, *prev = head;
    int count = 1;
    while (curr) {
        printf("%d \t %d \t \n", count++, curr->blockData);
        hashPrinter(SHA256((unsigned char *)toString(*prev), sizeof(*prev), NULL), SHA256_DIGEST_LENGTH); // Corrected usage of SHA256
        printf("-");
        hashPrinter(curr->prevHash, SHA256_DIGEST_LENGTH);
        if (hashCompare(SHA256((unsigned char *)toString(*prev), sizeof(*prev), NULL), curr->prevHash)) { // Corrected usage of SHA256
            printf(" verified\n");
        } else {
            printf(" Not verified\n");
        }
        prev = curr;
        curr = curr->link;
    }
}

void alterNthBlock(int n, int newData) {
    struct block *curr = head;
    int count = 1;
    while (curr) {
        if (count == n) {
            curr->blockData = newData;
            printf("Block %d altered successfully!\n", n);
            return;
        }
        curr = curr->link;
        count++;
    }
    printf("Nth block does not exist!\n");
}

void hackChain() {
    struct block *curr = head, *prev;
    if (curr == NULL) {
        printf("Block chain is empty\n");
        return;
    }
    while (1) {
        prev = curr;
        curr = curr->link;
        if (curr == NULL)
            return;
        if (!hashCompare(SHA256((unsigned char *)toString(*prev), sizeof(*prev), NULL), curr->prevHash)) { // Corrected usage of SHA256
            hashPrinter(SHA256((unsigned char *)toString(*prev), sizeof(*prev), NULL), SHA256_DIGEST_LENGTH); // Corrected usage of SHA256
            printf("\n");
        }
    }
}

unsigned char *toString(struct block b) {
    unsigned char *str = malloc(sizeof(unsigned char) * sizeof(b));
    memcpy(str, &b, sizeof(b));
    return str;
}

void hashPrinter(unsigned char hash[], int length) {
    for (int i = 0; i < length; i++)
        printf("%02x", hash[i]);
}

int hashCompare(unsigned char *str1, unsigned char *str2) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        if (str1[i] != str2[i])
            return 1;
    return 0;
}

void printBlock(struct block *b) {
    printf("%p\t", b);
    hashPrinter(b->prevHash, sizeof(b->prevHash));
    printf("\t [%d]\t", b->blockData);
    printf("%p\n", b->link);
}

void printAllBlocks() {
    struct block *curr = head;
    int count = 0;
    while (curr) {
        printBlock(curr);
        curr = curr->link;
    }
}

int main() {
    int c, n, r;
    printf("1) Add Block\n2) Add n random blocks\n3) Alter Nth block\n4) Print all blocks\n5) Verify Chain\n6) Hack Chain\n");
    while (1) {
        printf("Choice: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &n);
                addBlock(n);
                break;
            case 2:
                printf("How many blocks to enter: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    r = rand() % (n * 10);
                    printf("Entering %d\n", r);
                    addBlock(r);
                }
                break;
            case 3:
                printf("Which block to alter? ");
                scanf("%d", &n);
                printf("Enter a value: ");
                scanf("%d", &r);
                alterNthBlock(n, r);
                break;
            case 4:
                printAllBlocks();
                break;
            case 5:
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
    return 0;
}
