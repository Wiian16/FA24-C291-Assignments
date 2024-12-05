#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

// Enums
enum Race { Terran, Martian, Venusian, Saturian };

enum Post { Crew, Cap, Com, Nav, Eng, Sec };

enum Rank { Spcr, Ens, Lt, Comm };

// Structs
struct Skills {
    short navigation;
    short engineering;
    short tacticts;
    short leadership;
    short diplomacy;
};

struct Abilities {
    unsigned short charisma;
    unsigned short intelligence;
    unsigned short strength;
    unsigned short psionics;
    unsigned short agility;
};

struct Crewman {
    char * name;
    enum Race race;
    struct Abilities abilities;
    struct Skills skills;
    enum Post post;
    struct Crewman * captain;
    enum Rank rank;
    int serviceNumber;
};

// Constants
#define CREW_MEMBERS 10

// Method definitions
struct Crewman * generateCrew();
enum Rank generateRank();
enum Race generateRace();
struct Abilities generateAbilities(enum Race race);
int rollDice(int numDice);
struct Skills generateSkills(struct Abilities abilities);
int calculateSkill(int naturalRoll, int ability1, int ability2);
void printCrew(struct Crewman * crew, FILE * out);
void printCrewman(struct Crewman crewman, FILE * out);
char getRaceChar(enum Race race);
char * getRankStr(enum Rank rank);
char * getPostStr(enum Post post);
void parseInput(struct Crewman * crew);
void renameCrewMember(struct Crewman * crew, int serviceNumber, char * name);
int indexOfCrewMember(struct Crewman * crew, int serviceNumber);
void setCaptain(struct Crewman * crew, int serviceNumber);
void setPost(struct Crewman * crew, int serviceNumber, char post);
struct Crewman generateCrewman(int serviceNumber);
int valueOfCrewman(struct Crewman crewman);
int compareCrewmen(const void * a, const void * b);

int main(int argc, char ** argv) {
    if (argc == 2) {
        srand(atoi(argv[1]));
    }
    else {
        // Initialize random number with time as seed
        srand(time(NULL));
    }

    struct Crewman * crew = generateCrew();

    printCrew(crew, stdout);

    fprintf(stderr, "Generated default crew\n");

    parseInput(crew);

    free(crew);
}

void parseInput(struct Crewman * crew) {
    int loop = 1;
    while (loop) {
        printf("\n--- Crew Management Menu ---\n");
        printf("Select an option:\n");
        printf("D: Display the table of crew members\n");
        printf("N srv_num name: Rename a crew member (e.g., N 123456 John)\n");
        printf("C srv_num: Assign a captain (e.g., C 123456)\n");
        printf("B srv_num: Assign a bridge post (e.g., B 123456 Nav)\n");
        printf("   Posts:\n");
        printf("     N - Navigation\n");
        printf("     C - Communications\n");
        printf("     S - Security\n");
        printf("     E - Engineering\n");
        printf("S: Save the crew list to 'crewmember_list.txt'\n");
        printf("R srv_num: Regenerate a crew member (e.g., R 123456)\n");
        printf("P: Exit the program and start the game\n");
        printf("\nEnter your choice: ");

        char buffer[100];

        if (!fgets(buffer, 100, stdin)) {
            printf("Empty fgets, exiting\n");
            exit(1);
        }

        printf("Buffer: %s\n", buffer);

        char choice = buffer[0];
        char * input = buffer + 1;
        int serviceNumber;

        switch (choice) {
            case 'D':
                printf("\n");
                printCrew(crew, stdout);
                break;
            case 'N':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax: %s\n", buffer);
                    break;
                }

                char name[100];

                sscanf(input, "%d %[^\n]", &serviceNumber, name);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                fprintf(stderr, "Renaming crew member %06d to %s\n", serviceNumber, name);
                renameCrewMember(crew, serviceNumber, name);

                break;
            case 'C':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax: %s\n", buffer);
                    break;
                }

                serviceNumber = atoi(input);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                fprintf(stderr, "Assigning crew member %06d to captain\n", serviceNumber);
                setCaptain(crew, serviceNumber);

                break;
            case 'B':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax: %s\n", buffer);
                    break;
                }

                char post;

                sscanf(input, "%d %c", &serviceNumber, &post);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                fprintf(stderr, "Assigning crew member %06d to post %c\n", serviceNumber, post);
                setPost(crew, serviceNumber, post);

                break;
            case 'S':
                printf("\nSaving crew list to 'crewmember_list.txt'\n");

                FILE * file = fopen("crewmember_list.txt", "w");

                printCrew(crew, file);

                fclose(file);
                file = NULL;
                break;
            case 'R':  // todo
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax: %s\n", buffer);
                    break;
                }

                serviceNumber = atoi(input);

                int index = indexOfCrewMember(crew, serviceNumber);

                if (index == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                fprintf(stderr, "Regenerating crew member %06d\n", serviceNumber);
                crew[index] = generateCrewman(serviceNumber);

                break;
            case 'P':
                printf("\nExiting Program, have a good game!\n");
                loop = 0;
                break;
        }
    }
}

struct Crewman * generateCrew() {
    struct Crewman * crew = (struct Crewman *)calloc(CREW_MEMBERS, sizeof(struct Crewman));

    if (!crew) {
        printf("Memory allocation for crew failed, exiting program\n");
        exit(1);
    }

    for (int i = 0; i < CREW_MEMBERS; i++) {
        fprintf(stderr, "Generating crew member %d\n", i);
        crew[i] = generateCrewman(i);
    }

    return crew;
}

struct Crewman generateCrewman(int serviceNumber) {
    struct Crewman crewman;
    // Default 6-digit service number ( serviceNumber < 1000000)
    crewman.serviceNumber = serviceNumber;

    // Default post (Crew)
    crewman.post = Crew;

    // Generate Rank
    crewman.rank = generateRank();

    // Generate Race
    crewman.race = generateRace();

    // Generate Abilities
    crewman.abilities = generateAbilities(crewman.race);

    // Generate Skills
    crewman.skills = generateSkills(crewman.abilities);

    // Gernerate Name
    crewman.name = (char *)malloc(sizeof(char) * 10);
    sprintf(crewman.name, "CREWMAN%d", crewman.serviceNumber);

    crewman.captain = NULL;

    return crewman;
}

enum Rank generateRank() {
    // Roll 2 6-sided dice
    int rank = rollDice(2);

    if (rank < 8) {
        return Spcr;
    }
    if (rank < 10) {
        return Ens;
    }
    if (rank < 12) {
        return Lt;
    }
    return Comm;
}

enum Race generateRace() {
    int race = rand() % 4;

    switch (race) {
        case 0:
            return Terran;
        case 1:
            return Martian;
        case 2:
            return Venusian;

        case 3:
            return Saturian;
        default:
            printf("Error in generateRace()\n");
            exit(1);
    }
}

struct Abilities generateAbilities(enum Race race) {
    struct Abilities abilities;

    // Generate natural rolls
    abilities.agility = rollDice(3);
    abilities.intelligence = rollDice(3);
    abilities.strength = rollDice(3);
    abilities.psionics = rollDice(3);
    abilities.charisma = rollDice(3);

    // Race modifiers

    switch (race) {
        case Martian:
            abilities.strength -= 2;
            abilities.psionics += 2;
            abilities.agility++;
            break;
        case Venusian:
            abilities.charisma++;
            abilities.intelligence--;
            abilities.strength++;
            abilities.psionics++;
            abilities.agility--;
            break;
        case Saturian:
            abilities.charisma--;
            abilities.intelligence += 2;
            abilities.strength--;
            abilities.psionics++;
            break;
        default:
            break;
    }

    return abilities;
}

int rollDice(int numDice) {
    int result = 0;

    for (int i = 0; i < numDice; i++) {
        result += rand() % 6;
        result++;
    }

    return result;
}

struct Skills generateSkills(struct Abilities abilities) {
    struct Skills skills;

    skills.navigation = calculateSkill(0, abilities.intelligence, abilities.psionics);
    skills.engineering = calculateSkill(0, abilities.intelligence, abilities.agility);
    skills.tacticts = calculateSkill(0, abilities.strength, abilities.agility);
    skills.leadership = calculateSkill(0, abilities.charisma, abilities.intelligence);
    skills.diplomacy = calculateSkill(0, abilities.charisma, abilities.psionics);

    return skills;
}

int calculateSkill(int naturalRoll, int ability1, int ability2) {
    float avgAbility = (ability1 + ability2) / 2.0;

    if (avgAbility < 4) {
        return naturalRoll - 2;
    }
    if (avgAbility < 7) {
        return naturalRoll - 1;
    }
    if (avgAbility < 15) {
        return naturalRoll;
    }
    if (avgAbility < 18) {
        return naturalRoll + 1;
    }
    if (avgAbility == 18) {
        return naturalRoll + 2;
    }
    else {
        printf("Abilities outside of normal range, exiting program\n");
        exit(1);
    }
}

void printCrew(struct Crewman * crew, FILE * out) {
    fprintf(stderr, "Sorting crew list\n");

    if (crew[0].captain) {
        int captainServNum = crew[0].captain->serviceNumber;
        qsort(crew, CREW_MEMBERS, sizeof(struct Crewman), compareCrewmen);
        setCaptain(crew, captainServNum);
    }
    else {
        qsort(crew, CREW_MEMBERS, sizeof(struct Crewman), compareCrewmen);
    }
    // output captain, if selected
    if (crew[0].captain) {
        fprintf(out, "Captain : %s\n", crew[0].captain->name);
    }
    else {
        fprintf(out, "Captain : NONE\n");
    }

    // print table headers
    fprintf(out, "                       Skills           Abilities\n");
    fprintf(out, "Ser#   Post Rank | N  E  T  L  D  | C  I  S  P  A  | Race Name\n");

    // print all crewmen
    for (int i = 0; i < CREW_MEMBERS; i++) {
        printCrewman(crew[i], out);
    }
}

void printCrewman(struct Crewman crewman, FILE * out) {
    char * post = getPostStr(crewman.post);
    char * rank = getRankStr(crewman.rank);
    char race = getRaceChar(crewman.race);

    fprintf(out, "%06d %-4s %-4s | ", crewman.serviceNumber, post, rank);
    struct Skills skills = crewman.skills;
    fprintf(out, "%-2d %-2d %-2d %-2d %-2d | ", skills.navigation, skills.engineering, skills.tacticts,
            skills.leadership, skills.diplomacy);
    ;
    struct Abilities abilities = crewman.abilities;
    fprintf(out, "%-2d %-2d %-2d %-2d %-2d | ", abilities.charisma, abilities.intelligence, abilities.strength,
            abilities.psionics, abilities.agility);
    fprintf(out, "%c    %s\n", race, crewman.name);
}

char * getRankStr(enum Rank rank) {
    switch (rank) {
        case Spcr:
            return "Spcr";
        case Lt:
            return "Lt";
        case Ens:
            return "Ens";
        case Comm:
            return "Comm";
    }
}

char getRaceChar(enum Race race) {
    switch (race) {
        case Saturian:
            return 'S';
        case Terran:
            return 'T';
        case Martian:
            return 'M';
        case Venusian:
            return 'V';
    }
}

char * getPostStr(enum Post post) {
    switch (post) {
        case Crew:
            return "Crew";
        case Cap:
            return "Cap";
        case Com:
            return "Com";
        case Nav:
            return "Nav";
        case Eng:
            return "Eng";
        case Sec:
            return "Sec";
    }
}

void renameCrewMember(struct Crewman * crew, int serviceNumber, char * name) {
    int index = indexOfCrewMember(crew, serviceNumber);

    if (index == -1) {
        printf("Crewman %06d not found\n", serviceNumber);
        return;
    }

    free(crew[index].name);
    crew[index].name = strdup(name);
}

int indexOfCrewMember(struct Crewman * crew, int serviceNumber) {
    for (int i = 0; i < CREW_MEMBERS; i++) {
        if (crew[i].serviceNumber == serviceNumber) {
            fprintf(stderr, "Found crew member %06d at index %d\n", serviceNumber, i);
            return i;
        }
    }

    return -1;
}

void setCaptain(struct Crewman * crew, int serviceNumber) {
    int index = indexOfCrewMember(crew, serviceNumber);

    if (index == -1) {
        printf("Crewman %06d not found", serviceNumber);
        return;
    }

    if (crew[0].captain) {
        crew[0].captain->post = Crew;
    }

    for (int i = 0; i < CREW_MEMBERS; i++) {
        crew[i].captain = &crew[index];
    }

    crew[index].post = Cap;
}

void setPost(struct Crewman * crew, int serviceNumber, char post) {
    int index = indexOfCrewMember(crew, serviceNumber);

    if (index == -1) {
        printf("Crewman %06d not found\n", serviceNumber);
    }

    enum Post postEnum;

    if (post == 'C') {
        postEnum = Com;
    }
    else if (post == 'N') {
        postEnum = Nav;
    }
    else if (post == 'E') {
        postEnum = Eng;
    }
    else if (post == 'S') {
        postEnum = Sec;
    }
    else {
        printf("Ivalid post, aborting\n");
        return;
    }

    crew[index].post = postEnum;
}

int valueOfCrewman(struct Crewman crewman) {
    switch (crewman.post) {
        case Cap:
            return 0;
        case Nav:
        case Com:
        case Eng:
        case Sec:
            return 1;
        case Crew:
            return 2;
    }
}

int compareCrewmen(const void * a, const void * b) {
    return valueOfCrewman(*(struct Crewman *)a) - valueOfCrewman(*(struct Crewman *)b);
}
