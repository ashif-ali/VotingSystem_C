#ifndef ELECTION_H
#define ELECTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct Definitions
struct currentValidID {
    int year;
    char branch[4]; // Adjusted to 4 to accommodate "mcs" + null terminator
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
int extractYear(char userID[9]);
int extractRollNo(char userID[9]);
int checkBranchCode(char userID[9]);
int authenticateAdmin();
void banID();
void createCandidateFiles();
void deleteIllegalVote(char userID[9]);
int getWinner();
void initiateNewElection();
void saveElectionInfoInFile();
void loadElectionInfoFromFile();
void adminPanel();
int isValid(char userID[9]);
int isVoted(char userID[9]);
int isBanned(char userID[9]);
void saveVote(char userID[9], char voteInput);
void studentPanel();

#endif // ELECTION_H
