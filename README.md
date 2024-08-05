# Election Management System

## Overview
This project is a simple election management system designed for use in a school or college environment. It allows students to vote for candidates and provides administrators with tools to manage the election process.

## Features
- **Student Panel**: Allows students to cast their votes for candidates.
- **Admin Panel**: Enables administrators to:
  - Start a new election.
  - Continue a previous election.
  - Delete illegal votes.
  - Ban specific user IDs.
  - View election results.

## Structure
The project consists of three main files:
1. **main.c**: The entry point of the program.
2. **election.h**: The header file containing structure definitions, global variables, and function prototypes.
3. **election.c**: The implementation of all functions declared in `election.h`.

## How to Use
1. **Compile the Program**:
   ```sh
   gcc main.c election.c -o election
   ```

2. **Run the Program**:
   ```sh
   ./election
   ```

3. **Follow the Menu**:
   - **Student Panel**: Enter user ID and cast your vote.
   - **Admin Panel**: Authenticate as admin and manage the election.

## Functions

### Main Functions
- **main()**: Displays the main menu and directs to the student or admin panel based on user input.

### Utility Functions
- **extractYear(char userID[15])**: Extracts the year from the user ID.
- **extractRollNo(char userID[15])**: Extracts the roll number from the user ID.
- **checkBranchCode(char userID[15])**: Checks if the branch code in the user ID matches the current valid branch.

### Admin Functions
- **authenticateAdmin()**: Authenticates the admin using a username and password.
- **banID()**: Bans user IDs and stores them in `Banned.txt`.
- **createCandidateFiles()**: Creates files for each candidate to store their votes and names.
- **deleteIllegalVote(char userID[15])**: Deletes an illegal vote.
- **getWinner()**: Determines the winner of the election.
- **initiateNewElection()**: Initiates a new election.
- **saveElectionInfoInFile()**: Saves the current election information to `ElectionInfo.txt`.
- **loadElectionInfoFromFile()**: Loads election information from `ElectionInfo.txt`.

### Vote Management Functions
- **isValid(char userID[15])**: Checks if a user ID is valid for the current election.
- **isVoted(char userID[15])**: Checks if a user ID has already voted.
- **isBanned(char userID[15])**: Checks if a user ID is banned.
- **saveVote(char userID[15], char voteInput)**: Saves a vote to the appropriate candidate's file.

### Panel Functions
- **adminPanel()**: Handles admin actions such as starting a new election, continuing a previous election, deleting illegal votes, banning user IDs, and viewing results.
- **studentPanel()**: Handles the student voting process, including checking user ID validity, displaying candidates, and saving votes.

## Files
- **main.c**: Contains the main function and the program loop.
- **election.h**: Header file with structure definitions, global variables, and function prototypes.
- **election.c**: Implementation of all the functions declared in `election.h`.
- **ElectionInfo.txt**: Stores the current election information.
- **Banned.txt**: Stores the banned user IDs.
- **candidateX.txt**: Stores the vote count and name for each candidate, where X is the candidate ID.

## Notes
- Ensure that `ElectionInfo.txt` and `Banned.txt` are present in the working directory when running the program to avoid errors.
- The admin username is `Admin` and the password is `admiN`.

## License
This project is open-source and free to use under the MIT License.

