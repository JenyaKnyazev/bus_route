#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct bus_stop {
    int x;
    int y;
}BusStop;
typedef struct bus_route* RoutPtr;
typedef struct bus_route{
    BusStop* currentStop;
    RoutPtr next;
}BusRout;
int* max_x_y(RoutPtr run) {
    int max_x = 0;
    int max_y = 0;
    while (run != NULL) {
        if (run->currentStop->x > max_x)
            max_x = run->currentStop->x;
        if (run->currentStop->y > max_y)
            max_y = run->currentStop->y;
        run = run->next;
    }
    int* result = (int*)malloc(sizeof(int) * 2);
    result[0] = max_x;
    result[1] = max_y;
    return result;
}
int** makeMap(RoutPtr n) {
    int* len = max_x_y(n);
    int** map = (int**)malloc(sizeof(int*) * (len[1]+1));
    int i,r;
    for (i = 0; i < len[1]+1; i++)
        map[i] = (int*)malloc(sizeof(int) * (len[0]+1));
    for (i = 0; i < len[1]+1; i++)
        for (r = 0; r < len[0]+1; r++)
            map[i][r] = 0;
    i = 1;
    while (n != NULL) {
        map[n->currentStop->y][n->currentStop->x] = i;
        i++;
        n = n->next;
    }
    return map;
}
int count_elements(RoutPtr n) {
    int count = 0;
    while (n != NULL) {
        count++;
        n = n->next;
    }
    return count;
}
int** makeDistanceMap(RoutPtr n) {
    int len = count_elements(n);
    int** map=(int**)malloc(sizeof(int*)*(len+1));
    int i,r;
    for (i = 0; i < len + 1; i++)
        map[i] = (int*)malloc(sizeof(int) * (len + 1));
    for (i = 0; i < len + 1; i++) {
        map[i][i] = 0;
        map[0][i] = i;
        map[i][0] = i;
    }
    i = 1;
    while (n->next != NULL) {
        RoutPtr run = n->next;
        r = i + 1;
        while (run != NULL) {
            map[i][r] = abs(run->currentStop->x - n->currentStop->x) + abs(run->currentStop->y - n->currentStop->y);
            map[r][i] = abs(run->currentStop->x - n->currentStop->x) + abs(run->currentStop->y - n->currentStop->y);
            r++;
            run = run->next;
        }
        i++;
        n = n->next;
    }
    return map;
}
RoutPtr generate_stop(int x, int y) {
    RoutPtr n = (RoutPtr)malloc(sizeof(RoutPtr));
    n->currentStop = (BusStop*)malloc(sizeof(BusStop));
    n->currentStop->x = x;
    n->currentStop->y = y;
    n->next = NULL;
    return n;
}
int max_(int** map,int len){
    int i,r,max=0;
    for (i = 1, r = 2; r < len; i++, r++)
        max += map[i][r];
    return max;
}
void print(int** map, int len1, int len2) {
    int i, r;
    for (i = 0; i < len1; i++) {
        for (r = 0; r < len2; r++)
            printf("%d ", map[i][r]);
        putchar('\n');
    }
}
void Game() {
    RoutPtr n=NULL;
    int number_or_stops,x,y,i,r;
    puts("Enter the number of stops in the route");
    scanf("%d", &number_or_stops);
    if (number_or_stops < 1) {
        puts("Wrong Input");
        return;
    }
    puts("Enter the coordinates x and y for the bus stop");
    scanf("%d %d", &x, &y);
    if (x < 0 || y < 0) {
        puts("Wrong Input");
        return;
    }
    n = generate_stop(x, y);
    RoutPtr run = n;
    number_or_stops--;
    while (number_or_stops > 0) {
        puts("Enter the coordinates x and y for the bus stop");
        scanf("%d %d", &x, &y);
        if (x < 0 || y < 0) {
            puts("Wrong Input");
            return;
        }
        run->next = generate_stop(x, y);
        run = run->next;
        number_or_stops--;
    }
    int* len_map1=max_x_y(n);
    int len_map2 = count_elements(n);
    int** map1 = makeMap(n);
    int** map2 = makeDistanceMap(n);
    printf("The total amount of distance in the rout is %d\n", max_(map2, len_map2 + 1));
    puts("The Map");
    print(map1, len_map1[1]+1, len_map1[0]+1);
    puts("Distance Matrix");
    print(map2, (len_map2 + 1), (len_map2 + 1) );
}
void main() {
    Game();
    system("pause");
}