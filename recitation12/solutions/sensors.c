#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sensor {
    char *name; // dynamically allocated string
    char type; // ’I’ or ’F’
    union {
        int i;
        float f;
    } reading;
};

void setSensor(struct Sensor *s, const char *name, char type, void *valuePtr) {
    // allocate memory for name
    s->name = (char *)malloc(20);
    strcpy(s->name, name);

    // set type
    s->type = type;

    // store reading based on type
    if (type == 'I') {
        s->reading.i = *(int *)valuePtr;
    } 
    else if (type == 'F') {
        s->reading.f = *(float *)valuePtr;
    }
}

int main() {
    struct Sensor sensors[3];
    float tempVal = 23.7;
    int countVal = 120;
    float rateVal = 5.25;

    setSensor(&sensors[0], "Temp", 'F', &tempVal);
    setSensor(&sensors[1], "Count", 'I', &countVal);
    setSensor(&sensors[2], "Rate", 'F', &rateVal);
    
    // print all sensors
    for (int i = 0; i < 3; i++) {
        printf("Sensor %d:\n", i+1);
        printf(" Name: %s\n", sensors[i].name);
        printf(" Type: %c\n", sensors[i].type);
        if (sensors[i].type == 'I') 
            printf(" Reading: %d\n", sensors[i].reading.i);
        else
            printf(" Reading: %.2f\n", sensors[i].reading.f);
        printf("\n");
    }
    // free memory
    for (int i = 0; i < 3; i++) {
        free(sensors[i].name);
    }
    return 0;
}