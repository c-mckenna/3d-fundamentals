#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"
#include "mesh.h"

mesh_t mesh = {
        .vertices = NULL,
        .faces = NULL,
        .rotation = {0, 0, 0}
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
{ .x = -1, .y = -1, .z = -1 }, // 1
{ .x = -1, .y =  1, .z = -1 }, // 2
{ .x =  1, .y =  1, .z = -1 }, // 3
{ .x =  1, .y = -1, .z = -1 }, // 4
{ .x =  1, .y =  1, .z =  1 }, // 5
{ .x =  1, .y = -1, .z =  1 }, // 6
{ .x = -1, .y =  1, .z =  1 }, // 7
{ .x = -1, .y = -1, .z =  1 }  // 8
};

face_t cube_faces[N_CUBE_FACES] = {
// front
{ .a = 1, .b = 2, .c = 3 },
{ .a = 1, .b = 3, .c = 4 },
// right
{ .a = 4, .b = 3, .c = 5 },
{ .a = 4, .b = 5, .c = 6 },
// back
{ .a = 6, .b = 5, .c = 7 },
{ .a = 6, .b = 7, .c = 8 },
// left
{ .a = 8, .b = 7, .c = 2 },
{ .a = 8, .b = 2, .c = 1 },
// top
{ .a = 2, .b = 7, .c = 5 },
{ .a = 2, .b = 5, .c = 3 },
// bottom
{ .a = 6, .b = 8, .c = 1 },
{ .a = 6, .b = 1, .c = 4 }
};

void load_cube_mesh_data(void) {
    for (int i = 0; i < N_CUBE_VERTICES; i++) {
        array_push(mesh.vertices, cube_vertices[i]);
    }

    for (int i = 0; i < N_CUBE_FACES; i++) {
        array_push(mesh.faces, cube_faces[i]);
    }
}

void load_obj_file_data(char* filename) {
    FILE* file = fopen(filename, "r");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[1] == ' ') {
            switch (line[0]) {
                case 'v': {
                    char* token = strtok(line, " ");
                    int i = 0;
                    float values[3];

                    while (token) {
                        if ((strcmp(token, "v") != 0)) {
                            values[i++] = atof(token);
                        }

                        token = strtok(NULL, " ");
                    }

                    vec3_t vertex = {
                            .x = values[0],
                            .y = values[1],
                            .z = values[2]
                    };

                    printf("Vertex\n");
                    printf("%f, %f, %f\n", vertex.x, vertex.y, vertex.z);

                    array_push(mesh.vertices, vertex);

                    break;
                }
                case 'f': {
                    char* token = strtok(line, " ");
                    int i = 0;
                    int values[3];

                    while (token) {
                        if ((strcmp(token, "f") != 0)) {
                            if (strlen(token) > 0) {
                                int length = strcspn(token, "/");
                                char* index = malloc(length + 1);
                                memcpy(index, token, length);
                                index[length] = '\0';

                                values[i++] = atoi(index);
                                free(index);
                            }
                        }

                        token = strtok(NULL, " ");
                    }

                    face_t face = {
                            .a = values[0],
                            .b = values[1],
                            .c = values[2]
                    };

                    printf("Face\n");
                    printf("%i, %i, %i\n", face.a, face.b, face.c);

                    array_push(mesh.faces, face);

                    break;
                }
            }
        }
    }

    fclose(file);
}