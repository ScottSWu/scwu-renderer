#include <stdlib.h>
#include <stdio.h>
#include <Pineapple/Pineapple.h>

int main() {
    Pineapple p;

    printf("Width: %d, Height: %d", p.getWidth(), p.getHeight());

    return 0;
}
