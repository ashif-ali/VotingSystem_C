#ifndef ELECTION_H
#define ELECTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct Definitions
struct currentValidID {
    int year;
    char branch[6];
    int totalVoters;
};

typedef struct candidate {
    int cid;
    char cname[20];
    int votes;
} CANDIDATE;

// Global variable declarations
extern struct currentValidID currentValidID;
extern CANDIDATE candidateArray[20];
extern int numberOfCandidates;
extern char studentVotes[200];

// Function Prototypes
int extractYear(char userID[15]);
int extractRollNo(char userID[15]);
int checkBranchCode(char userID[15]);
int authenticateAdmin();
void banID();
void createCandidateFiles();
void deleteIllegalVote(char userID[15]);
int getWinner();
void initiateNewElection();
void saveElectionInfoInFile();
void loadElectionInfoFromFile();
void adminPanel();
int isValid(char userID[15]);
int isVoted(char userID[15]);
int isBanned(char userID[15]);
void saveVote(char userID[15], char voteInput);
void studentPanel();

#endif // ELECTION_H
