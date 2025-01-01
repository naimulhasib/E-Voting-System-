#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_NAME_LENGTH 50
#define NID_LENGTH 13
#define ADMIN_PASSWORD "admin123"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidateCount = 5; 
const char *CANDIDATES_FILE = "candidates.txt";
const char *VOTERS_FILE = "voters.txt";

void initializeCandidates();
void loadCandidates();
void saveCandidates();
int hasVoted(const char *nid);
void recordVoter(const char *nid, const char *voterName, const char *candidateName);
void adminMenu();
void voterMenu();
void viewCredits();
void addCandidate();
void viewResults();
void castVote();
void readString(char *buffer, size_t bufferSize);

int main() {
    initializeCandidates(); 
    loadCandidates();       

    while (1) {
        printf("\n=== Voting System ===\n");
        printf("1. Admin Menu\n");
        printf("2. Voter Menu\n");
        printf("3. View Project Credits\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar();  // To consume the newline character from previous input
        
        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                voterMenu();
                break;
            case 3:
                viewCredits();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void initializeCandidates() {
    strcpy(candidates[0].name, "Obaidul Kader");
    candidates[0].votes = 0;

    strcpy(candidates[1].name, "Shamim Osman");
    candidates[1].votes = 0;

    strcpy(candidates[2].name, "Sheikh Hasina");
    candidates[2].votes = 0;

    strcpy(candidates[3].name, "Khaleda Zia");
    candidates[3].votes = 0;

    strcpy(candidates[4].name, "Hero Alam");
    candidates[4].votes = 0;
}

void loadCandidates() {
    FILE *file = fopen(CANDIDATES_FILE, "r");
    if (file == NULL) {
        printf("No additional candidates found. Using fixed candidates only.\n");
        return;
    }
    while (fscanf(file, "%49[^,],%d\n", candidates[candidateCount].name, &candidates[candidateCount].votes) == 2) {
        candidateCount++;
    }
    fclose(file);
}

void saveCandidates() {
    FILE *file = fopen(CANDIDATES_FILE, "w");
    if (file == NULL) {
        printf("Error saving candidates to file.\n");
        return;
    }
    for (int i = 0; i < candidateCount; i++) {
        fprintf(file, "%s,%d\n", candidates[i].name, candidates[i].votes);
    }
    fclose(file);
}

int hasVoted(const char *nid) {
    FILE *file = fopen(VOTERS_FILE, "r");
    if (file == NULL) {
        return 0;  // No voters file found, no one has voted yet
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, nid)) {
            fclose(file);
            return 1;  // Found the NID in the voters list, meaning they have voted
        }
    }
    fclose(file);
    return 0;  // NID not found in the voters file
}

void recordVoter(const char *nid, const char *voterName, const char *candidateName) {
    FILE *file = fopen(VOTERS_FILE, "a"); // Append mode to add voter info at the end
    if (file == NULL) {
        printf("Error recording voter information.\n");
        return;
    }
    fprintf(file, "NID: %s, Name: %s, Voted For: %s\n", nid, voterName, candidateName);
    fclose(file);
}

void adminMenu() {
    char password[20];
    printf("Enter Admin Password: ");
    scanf("%19s", password);
    getchar();  // Consume the newline character

    if (strcmp(password, ADMIN_PASSWORD) != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }

    while (1) {
        printf("\n=== Admin Menu ===\n");
        printf("1. Add Candidate\n");
        printf("2. View Results\n");
        printf("3. Return to Main Menu\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                addCandidate();
                break;
            case 2:
                viewResults();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

void voterMenu() {
    char nid[NID_LENGTH + 1];
    char voterName[MAX_NAME_LENGTH];

    printf("Enter your 13-digit NID number: ");
    scanf("%13s", nid);
    getchar();  // Consume the newline character

    if (strlen(nid) != 13) {
        printf("Invalid NID! Must be exactly 13 digits.\n");
        return;
    }

    if (hasVoted(nid)) {
        printf("You have already voted! Voting denied.\n");
        return;
    }

    printf("Enter your name: ");
    readString(voterName, sizeof(voterName));  // Using fgets-like function for name input

    castVote();
    recordVoter(nid, voterName, candidates[candidateCount - 1].name);
}

void viewCredits() {
    printf("\n=== Project Credits ===\n");
    printf("This project was developed by:\n");
    printf("1. Naimul Hasib Ratul (ID: 2422069642)\n");
    printf("2. Md Aowlad Hussain  (ID: 2422785642)\n");
    printf("3. Mohammad Rizwanul Hasan  (ID: 2422930042)\n");
    printf("=========================\n");
}

void addCandidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("Cannot add more candidates. Maximum limit reached.\n");
        return;
    }
    printf("Enter the name of the new candidate: ");
    readString(candidates[candidateCount].name, sizeof(candidates[candidateCount].name));  // Using fgets-like function
    candidates[candidateCount].votes = 0;
    candidateCount++;
    saveCandidates();
    printf("Candidate added successfully.\n");
}

void viewResults() {
    printf("\n=== Voting Results ===\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
    printf("======================\n");
}

void castVote() {
    printf("\n=== Candidates ===\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
    printf("Enter the number of your chosen candidate: ");
    
    int choice;
    scanf("%d", &choice);
    getchar(); // Consume newline

    if (choice < 1 || choice > candidateCount) {
        printf("Invalid choice! Vote not recorded.\n");
        return;
    }

    candidates[choice - 1].votes++;
    saveCandidates();
    printf("Your vote for %s has been recorded. Thank you!\n", candidates[choice - 1].name);
}

void readString(char *buffer, size_t bufferSize) {
    fgets(buffer, bufferSize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove the newline character
}
