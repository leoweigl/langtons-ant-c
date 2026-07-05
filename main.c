#include <stdio.h>
#include <string.h>
#define size 250

int grid[size][size];

typedef enum {
    UP, RIGHT, DOWN, LEFT
} Direction;

typedef struct {
    int x, y;
    Direction direction;
} Ant;

void move(Ant *ant) {
    switch (ant->direction) {
        case UP:
            ant->y--;
            break;
        case RIGHT:
            ant->x++;
            break;
        case DOWN:
            ant->y++;
            break;
        case LEFT:
            ant->x--;
            break;
        default:
            break;
    }
}

void step(Ant *ant) {
    if (grid[ant->y][ant->x] == 0) {
        grid[ant->y][ant->x] = 1;
        ant->direction = (ant->direction + 1) % 4 ;
    } else {
        grid[ant->y][ant->x] = 0;
        ant->direction = (ant->direction +3 ) % 4 ;
    }

    const int OLD_X = ant->x;
    const int OLD_Y = ant->y;

    move(ant);

    if (ant->x < 0 || ant->x >= size || ant->y < 0 || ant->y >= size) {
        if (ant->x < 0) { ant->x = OLD_X; }
        if (ant->x >= size) { ant->x = OLD_X; }
        if (ant->y < 0) { ant->y = OLD_Y; }
        if (ant->y >= size) { ant->y = OLD_Y; }

        ant->direction = (ant->direction + 2) % 4;

        move(ant);
    }
}

void save_ppm(char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("No file found.");
        return;
    }
    fprintf(f, "P3\n%d %d\n255\n", size, size);
    char line[6000];

    for (int i = 0; i < size; i++) {
        line[0] = '\0';
        for (int j = 0; j < size; j++) {
            strcat(line, grid[i][j] == 0 ? "255 255 255 " : "0 0 0 ");
        }
        fprintf(f, "%s\n", line);
    }
    fclose(f);
}

int main() {
    printf("Langton's Ant is starting...\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }

    Ant ant = {125, 125, LEFT};
    Ant ant2 = {50, 200, RIGHT};
    Ant ant3 = {200, 50, DOWN};
    int frame_count = 0;

    for (int i = 0; i < 50000; i++) {
        step(&ant);
        step(&ant2);
        step(&ant3);
        if (i % 50 == 0) {
            frame_count++;
            char filename[50];
            sprintf(filename, "./frames/frame_%04d.ppm", frame_count);
            save_ppm(filename);
        }
    }
    return 0;
}
