typedef struct _pixelRGB {
  unsigned char R ;
  unsigned char G ;
  unsigned char B ; 
} pixelRGB ;

pixelRGB * get_pixel( unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y ){
    if (x >= width) {
        return 0;
    }
    else if (y >= height) {
        return 0;
    }

    else if (data == 0) {
        return 0;

    }
    else {
        return (pixelRGB *) &data[(y*width+x)*n] ;
    }

}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int read_image_data(const char *filename, unsigned char **data, int *width, int *height, int *channel_count) {
    int channels;
    *data = stbi_load(filename, width, height, &channels, 0);
    if (*data == NULL) {
        fprintf(stderr, "Error: Could not load image %s\n", filename);
        return 0;
    }
    *channel_count = channels;
    return 1;
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int write_image_data(const char *filename, unsigned char *data, int width, int height) {
    int result = stbi_write_png(filename, width, height, 3, data, width * 3);
    if (!result) {
        fprintf(stderr, "Error: Could not write image %s\n", filename);
        return 0;
    }
    return 1;
}

void dimension (char* source_path) {
    int width;
    int height;
    unsigned char* data;
    int channel_count;
    read_image_data(source_path, &data, &width, &height, &channel_count);
    //read_image_data(source_path, &data, &width, &height, &channel_count);
    printf("dimension : %d, %d  \n", width, height);
}

void first_pixel (char* source_path) {
    int width;
    int height;
    unsigned char* data;
    int channel_count;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    read_image_data(source_path, &data, &width, &height, &channel_count);
    //read_image_data(source_path, &data, &width, &height, &channel_count);
    red = data[0];
    green = data[1];
    blue = data[2];

    printf("first_pixel : %d, %d, %d  \n", red, green, blue);
}

void tenth_pixel (char* source_path) {
    int width;
    int height;
    unsigned char* data;
    int channel_count;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    read_image_data(source_path, &data, &width, &height, &channel_count);
    //read_image_data(source_path, &data, &width, &height, &channel_count);
    red = data[27];
    green = data[28];
    blue = data[29];

    printf("tenth_pixel : %d, %d, %d  \n", red, green, blue);
}

void second_line (char* source_path) {
    int width;
    int height;
    unsigned char* data;
    int channel_count;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    read_image_data(source_path, &data, &width, &height, &channel_count);
    //read_image_data(source_path, &data, &width, &height, &channel_count);
    red = data[3*width];
    green = data[3*width+1];
    blue = data[3*width+2];

    printf("second_line : %d, %d, %d  \n", red, green, blue);
}


void print_pixel (char *source_path, char* a, char* b){
    int width;
    int height;
    unsigned char* data;
    int channel_count;
    
    read_image_data(source_path, &data, &width, &height, &channel_count);
    

    int x = atoi(a);
    int y = atoi(b);
    
    pixelRGB* pix = get_pixel( data, width, height, channel_count, x, y);

    printf("print_pixel (%d, %d) : %d, %d, %d  \n", x, y, pix->R, pix->G, pix->B);
}

void max_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int x = 0, y = 0;
    int max = 0;
    int j = 0;

    while (j < height) {
        int i = 0;
        while (i < width) {
            pixelRGB *pix = get_pixel(data, width, height, channel_count, i, j);
            int sum = pix->R + pix->G + pix->B;

            if (sum > max) {
                max = sum;
                x = i;
                y = j;
            }
            i++;
        }
        j++;
    }
    pixelRGB *max_pix = get_pixel(data, width, height, channel_count, x, y);
    printf("max_pixel (%d, %d): %d, %d, %d\n", x, y, max_pix->R, max_pix->G, max_pix->B);
}




void min_pixel(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int x = 0, y = 0;
    int min = 255*3;
    int j = 0;

    while (j < height) {
        int i = 0;
        while (i < width) {
            pixelRGB *pix = get_pixel(data, width, height, channel_count, i, j);
            int sum = pix->R + pix->G + pix->B;
            if (sum < min) {
                min = sum;
                x = i;
                y = j;
            }
            i++;
        }
        j++;
    }
    pixelRGB *min_pix = get_pixel(data, width, height, channel_count, x, y);
    printf("min_pixel (%d, %d): %d, %d, %d\n", x, y, min_pix->R, min_pix->G, min_pix->B);
}



void max_component(char *source_path, char *a) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int x = 0, y = 0;
    unsigned char max_value = 0;
    int j = 0;

    while (j < height) {
        int i = 0;
        while (i < width) {
            pixelRGB *pix = get_pixel(data, width, height, channel_count, i, j);
            unsigned char value;
            switch (a[0]) {
                case 'R':
                    value = pix->R;
                    break;
                case 'G':
                    value = pix->G;
                    break;
                case 'B':
                    value = pix->B;
                    break;
                default:
                    printf("Commande non valide.\n");
            }
            if (value > max_value) {
                max_value = value;
                x = i;
                y = j;
            }
            i++;
        }
        j++;
    }

    printf("max_component %c (%d, %d): %d\n", a[0], x, y, max_value);
}

void min_component(char *source_path, char *component) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    int x = 0, y = 0;
    unsigned char min_value = 255;
    int j = 0;

    while (j < height) {
        int i = 0;
        while (i < width) {
            pixelRGB *pix = get_pixel(data, width, height, channel_count, i, j);
            unsigned char value;
            switch (component[0]) {
                case 'R':
                    value = pix->R;
                    break;
                case 'G':
                    value = pix->G;
                    break;
                case 'B':
                    value = pix->B;
                    break;
                default:
                    printf("Invalid component specified.\n");
            }
            if (value < min_value) {
                min_value = value;
                x = i;
                y = j;
            }
            i++;
        }
        j++;
    }
    printf("min_component %c (%d, %d): %d\n", component[0], x, y, min_value);
}

void color_red(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_red = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_red == NULL) {
        printf("Memory allocation failed. \n");
    }

    int i = 0;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        data_red[i * channel_count] = pixel->R;
        data_red[i * channel_count + 1] = 0;
        data_red[i * channel_count + 2] = 0;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_red, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_red);
}

void color_green(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_green = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_green == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        data_green[i * channel_count] = 0;
        data_green[i * channel_count + 1] = pixel->G;
        data_green[i * channel_count + 2] = 0;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_green, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_green);
}



void color_blue(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_blue = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_blue == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        data_blue[i * channel_count] = 0;
        data_blue[i * channel_count + 1] = 0;
        data_blue[i * channel_count + 2] = pixel->B;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_blue, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_blue);
}


void color_gray(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_gray = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_gray == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i, moyenne;
    for(i=0; i<width*height*3 -2; i+=3){
        moyenne = (data[i]+data[i+1]+data[i+2])/3;
        data_gray[i] = moyenne;
        data_gray[i+1] = moyenne;
        data_gray[i+2] = moyenne;
    }

    int success = write_image_data("image_out.bmp", data_gray, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_gray);
}

void color_invert(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_invert = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_invert == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        data_invert[i * channel_count] = 255 - pixel->R ;
        data_invert[i * channel_count + 1] = 255 - pixel->G ;
        data_invert[i * channel_count + 2] = 255 - pixel->B ;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_invert, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_invert);
}

void color_gray_luminance(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_luminance = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_luminance == NULL) {
        printf("Memory allocation failed. \n");
    }

    int i = 0;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        unsigned char value = 0.21 * pixel->R + 0.72 * pixel->G + 0.07 * pixel->B;

        data_luminance[i * channel_count] = value ;
        data_luminance[i * channel_count + 1] = value ;
        data_luminance[i * channel_count + 2] = value ;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_luminance, width, height);

    if (success) {
        printf("Successful transformation. \n");
    } else {
        printf("Failed.\n");
    }
    free(data_luminance);
}

void color_desaturate(char *source_path) {

    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_desaturate = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_desaturate == NULL) {
        printf("Allocation a la mémoire echoue.\n");
    }

    int i = 0;

    int max; 
    int min;

    int new_val ;

    while (i < width * height) {

        pixelRGB *pixel = (pixelRGB *)(data + i * channel_count);

        max = pixel->R;
        min = pixel->R;

        if (pixel->G > max) {
            max = pixel->G;
        }

        if (pixel->B > max) {
            max = pixel->B;
        }

        if (pixel->G < min) {
            min = pixel->G;
        }

        if (pixel->B < min) {
            min = pixel->B;
        }

        new_val = (min + max) / 2;

        data_desaturate[i * channel_count] = new_val;
        data_desaturate[i * channel_count + 1] = new_val;
        data_desaturate[i * channel_count + 2] = new_val;

        i++;
    }

    int success = write_image_data("image_out.bmp", data_desaturate, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_desaturate);
}

void rotate_cw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_rotate_cw = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_rotate_cw == NULL) {
        printf("Memory allocation failed.\n");
    }

    int new_width = height;
    int new_height = width;
    int i, j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            int src_index = (j * width + i) * channel_count;
            int dest_index = (i * new_width + (height - j - 1)) * channel_count;
            data_rotate_cw[dest_index] = data[src_index];
            data_rotate_cw[dest_index + 1] = data[src_index + 1];
            data_rotate_cw[dest_index + 2] = data[src_index + 2];
        }
    }

    int success = write_image_data("image_out.bmp", data_rotate_cw, new_width, new_height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed\n");
    }
    free(data_rotate_cw);
}

void rotate_acw(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_rotate_acw = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_rotate_acw == NULL) {
        printf("Memory allocation failed.\n");
    }

    int new_width = height;
    int new_height = width;
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            int src_index = (j * width + i) * channel_count;
            int dest_index = ((width - i - 1) * new_width + j) * channel_count;
            data_rotate_acw[dest_index] = data[src_index];
            data_rotate_acw[dest_index + 1] = data[src_index + 1];
            data_rotate_acw[dest_index + 2] = data[src_index + 2];
        }
    }
    int success = write_image_data("image_out.bmp", data_rotate_acw, new_width, new_height);
    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_rotate_acw);
}


void mirror_horizontal(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_mirror_horizontal = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_mirror_horizontal == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;
    int row_length = width * channel_count;

    while (i < height) {

        int row_start = i * row_length;
        int mirrored_row_start = row_start + row_length - channel_count;
        int j = 0;

        while (j < row_length) {

            int pixel_index = row_start + j;
            int mirrored_pixel_index = mirrored_row_start - j;
            int k = 0;

            while (k < channel_count) {
                data_mirror_horizontal[mirrored_pixel_index + k] = data[pixel_index + k];
                k++;
            }
            j += channel_count;
        }
        i++;
    }

    int success = write_image_data("image_out.bmp", data_mirror_horizontal, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_mirror_horizontal);
}

void mirror_vertical(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_mirror_vertical = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_mirror_vertical == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;
    int row_length = width * channel_count;

    while (i < height) {
        int row_start = i * row_length;
        int mirrored_row_start = (height - i - 1) * row_length;
        int j = 0;

        while (j < row_length) {
            int pixel_index = row_start + j;
            int mirrored_pixel_index = mirrored_row_start + j;
            int k = 0;

            while (k < channel_count) {
                data_mirror_vertical[mirrored_pixel_index + k] = data[pixel_index + k];
                k++;
            }
            j += channel_count;
        }
        i++;
    }

    int success = write_image_data("image_out.bmp", data_mirror_vertical, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_mirror_vertical);
}

void mirror_total(char *source_path) {
    int width, height, channel_count;
    unsigned char *data;

    read_image_data(source_path, &data, &width, &height, &channel_count);

    unsigned char *data_premiere_transfo = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));
    unsigned char *data_mirror_total = (unsigned char *)malloc(width * height * channel_count * sizeof(unsigned char));

    if (data_premiere_transfo == NULL) {
        printf("Memory allocation failed.\n");
    }

    if (data_mirror_total == NULL) {
        printf("Memory allocation failed.\n");
    }

    int i = 0;
    int row_length = width * channel_count;
    // Vertical Transformation 
    while (i < height) {
        int row_start = i * row_length;
        int mirrored_row_start = (height - i - 1) * row_length;
        int j = 0;

        while (j < row_length) {
            int pixel_index = row_start + j;
            int mirrored_pixel_index = mirrored_row_start + j;
            int k = 0;

            while (k < channel_count) {
                data_premiere_transfo[mirrored_pixel_index + k] = data[pixel_index + k];
                k++;
            }
            j += channel_count;
        }
        i++;
    }

    // Horizontal Transformation 
    int l = 0;

    while (l < height) {

        int row_start = l * row_length;
        int mirrored_row_start = row_start + row_length - channel_count;
        int j = 0;

        while (j < row_length) {

            int pixel_index = row_start + j;
            int mirrored_pixel_index = mirrored_row_start - j;
            int k = 0;

            while (k < channel_count) {
                data_mirror_total[mirrored_pixel_index + k] = data_premiere_transfo[pixel_index + k];
                k++;
            }
            j += channel_count;
        }
        l++;
    }

    int success = write_image_data("image_out.bmp", data_mirror_total, width, height);

    if (success) {
        printf("Successful transformation.\n");
    } else {
        printf("Failed.\n");
    }
    free(data_premiere_transfo);
    free(data_mirror_total);
}

int main()
{
    printf("Hello \n");
    printf("Results for images on the same level as this : \n");
    char img[20];

    // Ask the user to type a image
    printf("Write the name of the file that is looked into: \n");

    // Get and save the image the user types
    scanf("%s", &img);

    // Output the number the user image..
    printf("Your file is: %s \n", img);

    dimension(img);
    first_pixel(img);
    tenth_pixel(img);
    second_line(img);

    /*
    char answer[20];

    // Ask the user if they want a pixel
    printf("Do you want a pixel in particular ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        char x,y;
        //char* a,b;
        printf("Which pixel do you want for x? \n");
        scanf("%s",&x);
        printf("Which pixel do you want for y? \n");
        scanf("%s",&y);
        char *a = &x;
        char *b = &y;
        print_pixel(img, a, b);
    } else if(!strcmp(answer,"no")) {
        printf("\n");
    } else {
        printf("That's not an option. Please try again.\n");}
    */

    max_pixel(img);
    min_pixel(img);


    char answer[20];

    // Ask the user if they want the picture red
    printf("Do you want the picture with a red filter ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_red(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture green
    printf("Do you want the picture with a green filter ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_green(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture blue
    printf("Do you want the picture with a blue filter ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_blue(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture gray
    printf("Do you want the picture with a gray filter ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_gray(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }


    // Ask the user if they want the picture inverted color
    printf("Do you want the picture with inverted color ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_invert(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture with gray luminance
    printf("Do you want the picture with gray luminance ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_gray_luminance(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture with desaturated colors
    printf("Do you want the picture with desaturated colors ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        color_desaturate(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture rotated clockwise
    printf("Do you want the picture rotated clockwide ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        rotate_cw(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture rotated anti clockwise
    printf("Do you want the picture rotated anti clockwide ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        rotate_acw(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture horizontal mirror 
    printf("Do you want the picture horizontal mirror ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        mirror_horizontal(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture vertical mirror 
    printf("Do you want the picture vertical mirror ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        mirror_vertical(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }

    // Ask the user if they want the picture total mirror 
    printf("Do you want the picture total mirror ? (yes or no) ");

    // Get the answer
    scanf("%s", &answer);

    // Act accordingly
    if  (!strcmp(answer,"yes")) {
        mirror_total(img);
        printf("Please download before doing other transformation \n");
    } else //(!strcmp(answer,"no")) 
    {
        printf("\n");
    }
}

