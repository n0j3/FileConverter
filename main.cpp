#include "converter.h"
#include <cstdio> // For printf

int main() {
    Converter converter;

    if (!converter.inputs()) {
        printf("inputs() failed\n");
        return 1;
    } else {
        printf("inputs() succeeded\n");
    }

    if (!converter.readFile()) {
        printf("readFile() failed\n");
        return 1;
    } else {
        printf("readFile() succeeded\n");
    }

    if (!converter.showFile()) {
        printf("showFile() failed\n");
        return 1;
    } else {
        printf("showFile() succeeded\n");
    }

    if (!converter.writeFile()) {
        printf("writeFile() failed\n");
        return 1;
    } else {
        printf("writeFile() succeeded\n");
    }

    return 0;
}
