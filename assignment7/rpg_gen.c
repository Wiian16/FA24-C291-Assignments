#include <stdlib.h>
#include <stdio.h>

enum Race {
    Terran,
    Martian,
    Venusian,
    Saturian
};

enum Post {
    Crew,
    Cap,
    Com,
    Nav,
    Eng,
    Sec
};

enum Rank{
    Spcr,
    Ens,
    Lt,
    Comm
};


struct Skills {
    unsigned short navigation;
    unsigned short engineering;
    unsigned short tacticts;
    unsigned short leadership;
    unsigned short diplomacy;
};

struct Abilities {
    unsigned short charisma;
    unsigned short intelligence;
    unsigned short strenght;
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


#define CREW_MEMBERS 10


struct Crewman * generateCrew();


int main(void){


}


struct Crewman * generateCrew(){
    struct Crewman * crew = (struct Crewman *) calloc(CREW_MEMBERS, sizeof(struct Crewman));

    if(!crew){
        printf("Memory allocation for crew failed, exiting program\n");
        exit(1);
    }

    for(int i = 0; i < CREW_MEMBERS; i++){
        //Default 6-digit service number ( serviceNumber < 1000000)
        crew[i].serviceNumber = i;


    }
}
