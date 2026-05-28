#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRID_SIZE 8
#define CUBE_SIZE 1.0f
#define STREET_WIDTH 0.8f

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    int heights[GRID_SIZE][GRID_SIZE];
    int total_cubes = 0;

    // Step 1: Calculate the layout and count total cubes
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            
            // Calculate distance from the center of the grid to create a "downtown"
            float cx = (float)GRID_SIZE / 2.0f - 0.5f;
            float cy = (float)GRID_SIZE / 2.0f - 0.5f;
            float dist = sqrt(pow(i - cx, 2) + pow(j - cy, 2));

            // Base height decreases as you move away from the center
            int max_height = 7 - (int)(dist * 1.5f);
            if (max_height < 1) max_height = 1;

            // Add a little randomness to make the skyline look organic
            int floors = max_height + (rand() % 3); 
            heights[i][j] = floors;
            total_cubes += floors;
        }
    }

    const char* filename = "gemini.tvw";
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Failed to create file!\n");
        return 1;
    }

    // Step 2: Write the exact total count for the engine to read
    fprintf(f, "%d\n", total_cubes);

    // Offset to center the city around (0,0,0)
    float offset = (GRID_SIZE * (CUBE_SIZE + STREET_WIDTH)) / 2.0f;

    // Step 3: Generate the individual flats (cubes)
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            
            // X and Z coordinates remain constant for the entire building
            float x = (i * (CUBE_SIZE + STREET_WIDTH)) - offset;
            float z = (j * (CUBE_SIZE + STREET_WIDTH)) - offset;
            
            int floors = heights[i][j];
            
            // Stack the cubes vertically
            for (int f_lvl = 0; f_lvl < floors; f_lvl++) {
                // Your engine's grid is at y = -1.0f
                // We add CUBE_SIZE/2 so the bottom of the cube rests exactly on the grid
                float y = -1.0f + (CUBE_SIZE / 2.0f) + (f_lvl * CUBE_SIZE);
                
                fprintf(f, "%.4f %.4f %.4f %.4f\n", x, y, z, CUBE_SIZE);
            }
        }
    }

    fclose(f);
    printf("City generated successfully!\n");
    printf("Total blocks used: %d\n", total_cubes);
    printf("Load %s in Teravox to explore your city.\n", filename);
    
    return 0;
}