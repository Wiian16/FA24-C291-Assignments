#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

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
void printCrew(struct Crewman * crew);
void printCrewman(struct Crewman crewman);
char getRaceChar(enum Race race);
char * getRankStr(enum Rank rank);
char * getPostStr(enum Post post);
void parseInput(struct Crewman * crew);
void renameCrewMember(struct Crewman * crew, int serviceNumber, char * name);
int indexOfCrewMember(struct Crewman * crew, int serviceNumber);
void setCaptain(struct Crewman * crew, int serviceNumber);
void setPost(struct Crewman * crew, int serviceNumber, char post);

int main(int argc, char ** argv) {
    if (argc == 2) {
        printf("using given seed\n");
        srand(atoi(argv[1]));
    } else {
        // Initialize random number with time as seed
        srand(time(NULL));
    }

    struct Crewman * crew = generateCrew();

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
        printf("B srv_num: Assign a bridge post (e.g., B 123456)\n");
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

        char choice = buffer[0];
        char * input = buffer + 1;
        int serviceNumber;

        switch (choice) {
            case 'D':
                printCrew(crew);
                break;
            case 'N':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax\n");
                    break;
                }

                serviceNumber = atoi(input);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                printf("\nEnter new name for crew member %06d: ", serviceNumber);

                char name[100];

                if (!fgets(name, 100, stdin)) {
                    printf("Empty fgets, exiting\n");
                    exit(1);
                }

                name[strlen(name) - 1] = '\0';

                renameCrewMember(crew, serviceNumber, name);

                break;
            case 'C':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax\n");
                    break;
                }

                serviceNumber = atoi(input);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                setCaptain(crew, serviceNumber);

                break;
            case 'B':
                if (strlen(input) < 3) {
                    printf("\nInvalid Syntax\n");
                    break;
                }

                serviceNumber = atoi(input);

                if (indexOfCrewMember(crew, serviceNumber) == -1) {
                    printf("\nService Number %06d does not belong to a crew member\n", serviceNumber);
                    break;
                }

                printf("Enter a post to assign to crew member %06d: ", serviceNumber);

                char buffer2[3];

                if (!fgets(buffer2, 3, stdin)) {
                    printf("Empty fgets, exiting\n");
                    exit(1);
                }

                if (strlen(buffer2) != 2) {
                    printf("\nInvalid input, post must be one character\n");
                    break;
                }

                char post = buffer2[0];
                break;
            case 'S':
                printf("\nSaving crew list to 'crewmember_list.txt'\n");
                // todo
                break;
            case 'R':  // todo
                serviceNumber = atoi(input);
                printf("\nRegenerating Crewman %06d\n", serviceNumber);
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
        // Default 6-digit service number ( serviceNumber < 1000000)
        crew[i].serviceNumber = i + 1;

        // Default post (Crew)
        crew[i].post = Crew;

        // Generate Rank
        crew[i].rank = generateRank();

        // Generate Race
        crew[i].race = generateRace();

        // Generate Abilities
        crew[i].abilities = generateAbilities(crew[i].race);

        // Generate Skills
        crew[i].skills = generateSkills(crew[i].abilities);

        // Gernerate Name
        crew[i].name = (char *)malloc(sizeof(char) * 10);
        sprintf(crew[i].name, "CREWMAN%d", crew[i].serviceNumber);
    }

    return crew;
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
    } else {
        printf("Abilities outside of normal range, exiting program\n");
        exit(1);
    }
}

void printCrew(struct Crewman * crew) {
    // output captain, if selected
    if (crew[0].captain) {
        printf("Captain : %s\n", crew[0].captain->name);
    } else {
        printf("Captain : NONE\n");
    }

    // print table headers
    printf("                       Skills           Abilities\n");
    printf("Ser#   Post Rank | N  E  T  L  D  | C  I  S  P  A  | Race Name\n");

    // print all crewmen
    for (int i = 0; i < CREW_MEMBERS; i++) {
        printCrewman(crew[i]);
    }
}

void printCrewman(struct Crewman crewman) {
    char * post = getPostStr(crewman.post);
    char * rank = getRankStr(crewman.rank);
    char race = getRaceChar(crewman.race);

    printf("%06d %-4s %-4s | ", crewman.serviceNumber, post, rank);
    struct Skills skills = crewman.skills;
    printf("%-2d %-2d %-2d %-2d %-2d | ", skills.navigation, skills.engineering, skills.tacticts, skills.leadership,
           skills.diplomacy);
    ;
    struct Abilities abilities = crewman.abilities;
    printf("%-2d %-2d %-2d %-2d %-2d | ", abilities.charisma, abilities.intelligence, abilities.strength,
           abilities.psionics, abilities.agility);
    printf("%c    %s\n", race, crewman.name);
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

    crew[index].name = name;
}

int indexOfCrewMember(struct Crewman * crew, int serviceNumber) {
    for (int i = 0; i < CREW_MEMBERS; i++) {
        if (crew[i].serviceNumber == serviceNumber) {
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
