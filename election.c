#include "election.h"

// Global variable definitions
struct currentValidID currentValidID;
CANDIDATE candidateArray[20];
int numberOfCandidates;
char studentVotes[200];

// To extract year from userID -- For example, userID:2018btecs00064 year:2018 
int extractYear(char userID[15]) {
    int year = 0;
    for(int i = 0; i < 4; i++) {
        year = (year * 10) + (userID[i] - '0');
    }
    return year;
}

int extractRollNo(char userID[15]) {
    int rollno = 0;
    for(int i = 9; i < 14; i++) {
        rollno = (rollno * 10) + (userID[i] - '0');
    }
    return rollno;
}

// Will check whether the global branch code and inputted branch code is matching or not
int checkBranchCode(char userID[15]) {
    char branchCode[6];
    for(int i = 4; i < 9; i++) {
        branchCode[i - 4] = userID[i];
    }
    branchCode[5] = '\0';
    return strcmp(branchCode, currentValidID.branch) == 0;
}

int authenticateAdmin() {
    char username[15], password[6];
    printf("\nEnter username: ");
    scanf("%s", username);
    if(strcmp(username, "Admin") != 0) return 0;

    printf("Enter Password: ");
    for(int i = 0; i < 5; i++) {
        password[i] = getchar();
        printf("*");
    }
    password[5] = '\0';

    return strcmp(password, "admiN") == 0;
}

void banID() {
    printf("\nCreating Banned.txt...\n");
    FILE *fp = fopen("Banned.txt", "w");
    if(fp == NULL) {
        printf("Error: Banned.txt not created.\n");
        return;
    }
    printf("Just Enter last roll no to ban\nPress 0 to exit... ");
    int input;
    while(1) {
        printf("\nEnter Number: ");
        scanf("%d", &input);
        if(input == 0) break;
        studentVotes[input - 1] = '$';
        fprintf(fp, "%d\n", input);
    }
    fclose(fp);
    printf("Created Successfully\n");
}

void createCandidateFiles() {
    printf("\nCreating candidate files...\n");
    FILE *fp;
    char filename[25];
    for(int i = 1; i <= numberOfCandidates; i++) {
        sprintf(filename, "candidate%d.txt", i);
        fp = fopen(filename, "w");
        fprintf(fp, "0\n%s", candidateArray[i - 1].cname);
        fclose(fp);
    }
    printf("Created Files successfully\n");
}

void deleteIllegalVote(char userID[15]) {
    FILE *fp, *fcp;
    char filename[20], line[20];

    int location = extractRollNo(userID);
    sprintf(filename, "candidate%d.txt", candidateArray[studentVotes[location - 1] - '1'].cid);
    candidateArray[studentVotes[location - 1] - '1'].votes--;
    studentVotes[location - 1] = '0';

    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("\nFile cannot be opened...Operation Failed");
        return;
    }
    printf("\nDeleting in process...\n");

    fcp = fopen("tmp.txt", "w");
    if(fcp == NULL) {
        printf("\nFile cannot be opened...Operation Failed");
        return;
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
        fprintf(fcp, "%s", line);
    }
    fclose(fp);
    fclose(fcp);

    fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("\nFile cannot be opened...Operation Failed");
        return;
    }
    int numFromFile;
    char cnameFromFile[20];
    fcp = fopen("tmp.txt", "r");
    fscanf(fcp, "%d", &numFromFile);
    fprintf(fp, "%d", numFromFile - 1);
    fscanf(fcp, "%s", cnameFromFile);
    fprintf(fp, "\n%s", cnameFromFile);
    while(fscanf(fcp, "%d", &numFromFile) != EOF) {
        if(numFromFile != location) {
            fprintf(fp, "\n%d", numFromFile);
        }
    }
    fclose(fp);
    fclose(fcp);
    remove("tmp.txt");
    printf("\nVote deleted successfully\nPress any key to continue...");
    getchar(); // Replaces getch() for waiting for input
}

int getWinner() {
    int maxV = -1, winnerCid;
    for(int i = 0; i < numberOfCandidates; i++) {
        if(candidateArray[i].votes > maxV) {
            winnerCid = candidateArray[i].cid;
            maxV = candidateArray[i].votes;
        } else if(candidateArray[i].votes == maxV) {
            return -1;
        }
    }
    return winnerCid;
}

void initiateNewElection() {
    printf("\nNew Election Initiation:\n");

    printf("\nElections for which Year: ");
    scanf("%d", &currentValidID.year);
    printf("Enter branch code: ");
    scanf("%s", currentValidID.branch);
    printf("Enter max roll no.: ");
    scanf("%d", &currentValidID.totalVoters);
    printf("Enter the no. of candidates: ");
    scanf("%d", &numberOfCandidates);

    for(int i = 0; i < currentValidID.totalVoters; i++) {
        studentVotes[i] = '0';
    }

    for(int i = 0; i < numberOfCandidates; i++) {
        candidateArray[i].cid = i + 1;
        printf("Enter name of candidate %d: ", i + 1);
        scanf("%s", candidateArray[i].cname);
        candidateArray[i].votes = 0;
    }
}

void saveElectionInfoInFile() {
    printf("Saving Election Info in File...\n");
    FILE *fp = fopen("ElectionInfo.txt", "w");
    if(fp == NULL) {
        printf("\nError in file creation\n");
        return;
    }
    fprintf(fp, "%d\n%s\n%d\n%d", currentValidID.year, currentValidID.branch, currentValidID.totalVoters, numberOfCandidates);
    fclose(fp);
    printf("Saved Successfully : )");
}

void loadElectionInfoFromFile() {
    FILE *f1 = fopen("ElectionInfo.txt", "r");
    if(f1 == NULL) {
        printf("Not Exist");
        return;
    }
    fscanf(f1, "%d", &currentValidID.year);
    fseek(f1, 2, SEEK_CUR);
    fscanf(f1, "%s", currentValidID.branch);
    fseek(f1, 2, SEEK_CUR);
    fscanf(f1, "%d", &currentValidID.totalVoters);
    fseek(f1, 2, SEEK_CUR);
    fscanf(f1, "%d", &numberOfCandidates);
    fclose(f1);

    for(int i = 0; i < currentValidID.totalVoters; i++) {
        studentVotes[i] = '0';
    }

    for(int i = 1; i <= numberOfCandidates; i++) {
        int location;
        char filename[20];
        sprintf(filename, "candidate%d.txt", i);
        FILE *f2 = fopen(filename, "r+");
        candidateArray[i - 1].cid = i;
        fscanf(f2, "%d", &candidateArray[i - 1].votes);
        fscanf(f2, "%s", candidateArray[i - 1].cname);
        while(fscanf(f2, "%d", &location) != EOF) {
            studentVotes[location - 1] = i + '0';
        }
        fclose(f2);
    }

    int location;
    FILE *f3 = fopen("banned.txt", "r+");
    while(fscanf(f3, "%d", &location) != EOF) {
        studentVotes[location - 1] = '$';
    }
    fclose(f3);
}

void adminPanel() {
    while(1) {
        if(authenticateAdmin() != 1) {
            printf("\n Wrong Username or Password \n");
            break;
        }

        printf("\n\nLOGGED IN SUCCESSFULLY (Press Enter)");
        getchar();

        while(1) {
            char inputID[15], input, banInp;
            int WinnerCid, totalVotedNow = 0;
            printf("\n1.New Election\n2.Continue Previous Election\n3.Delete Illegal Vote\n4.Ban User IDs\n5.Result\n6.Logout\nOption:");
            scanf(" %c", &input);

            switch(input) {
                case '1':
                    initiateNewElection();
                    saveElectionInfoInFile();
                    createCandidateFiles();
                    break;
                case '2':
                    loadElectionInfoFromFile();
                    break;
                case '3':
                    printf("\nEnter user ID to delete its vote: ");
                    scanf("%s", inputID);
                    deleteIllegalVote(inputID);
                    break;
                case '4':
                    printf("Do you want to ban particular ID's?\nPress 1 if yes or any other key to continue...");
                    scanf(" %c", &banInp);
                    if(banInp == '1') {
                        banID();
                    }
                    break;
                case '5':
                    WinnerCid = getWinner();
                    if(WinnerCid != -1) {
                        printf("\nWinner is %s with %d votes\n", candidateArray[WinnerCid - 1].cname, candidateArray[WinnerCid - 1].votes);
                    } else {
                        printf("\nIts A TIE");
                    }
                    printf("\nFull Result\n");
                    for(int i = 0; i < numberOfCandidates; i++) {
                        totalVotedNow += candidateArray[i].votes;
                        printf("%d. %s -> %d votes\n", candidateArray[i].cid, candidateArray[i].cname, candidateArray[i].votes);
                    }
                    printf("\nVoting Percentage: %d %%\n\n", (totalVotedNow * 100) / currentValidID.totalVoters);
                    break;
                case '6':
                    return;
                default:
                    printf("Invalid Option");
                    getchar();
            }
        }
    }
}

int isValid(char userID[15]) {
    if(strlen(userID) != 14) return 0;

    int inputedYear = extractYear(userID);
    int inputedRollNo = extractRollNo(userID);

    return inputedYear == currentValidID.year && checkBranchCode(userID) == 1 && inputedRollNo <= currentValidID.totalVoters;
}

int isVoted(char userID[15]) {
    int location = extractRollNo(userID);
    return studentVotes[location - 1] != '0';
}

int isBanned(char userID[15]) {
    int location = extractRollNo(userID);
    return studentVotes[location - 1] == '$';
}

void saveVote(char userID[15], char voteInput) {
    char filename[20];
    sprintf(filename, "candidate%d.txt", voteInput - '0');
    FILE *fp = fopen(filename, "r+");
    int location = extractRollNo(userID);
    studentVotes[location - 1] = voteInput;
    candidateArray[voteInput - '1'].votes++;
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", candidateArray[voteInput - '1'].votes);
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "\n%d", location);
    fclose(fp);
}

void studentPanel() {
    char userID[15], voteInput;
    while(1) {
        printf("\n\n  To exit press 0");
        printf("\n  Enter user ID:");
        scanf("%s", userID);
        if(strcmp(userID, "0") == 0) return;
        if(isValid(userID) != 1) {
            printf("\n  Invalid User ID(Press Enter)");
            getchar();
            continue;
        }
        if(isBanned(userID) != 0) {
            printf("\nThis User ID is currently banned...\nContact Admin for the reason...(Press Enter to continue)");
            getchar();
            continue;
        }
        if(isVoted(userID) != 0) {
            printf("\n  Your PRN entered is already voted\n  Contact Admin for further query");
            getchar();
            continue;
        }
        printf("\n\n  Candidates for election:");
        for(int i = 0; i < numberOfCandidates; i++) {
            printf("\n  %d. %s", i + 1, candidateArray[i].cname);
        }
        printf("\n\n  Your Vote(Enter Number):");
        voteInput = getchar();
        printf("*");
        if(voteInput < '1' || voteInput > '0' + numberOfCandidates) {
            printf("\nInvalid Vote\nTry Again...");
            getchar();
            continue;
        }
        saveVote(userID, voteInput);
        printf("\n\nThanks for your precious vote(Press Enter)");
        getchar();
    }
}
