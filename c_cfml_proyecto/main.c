#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics.h>



char * fonts_array[] = {

        "..\\fonts\\arial.ttf",
        "..\\fonts\\comic.ttf",
        "..\\fonts\\Inkfree.ttf",
        "..\\fonts\\calibri.ttf",
        "..\\fonts\\LHANDW.ttf"
};

int font_sizes[] = {
        20, 25, 35, 40, 45, 50, 60, 70, 80
};


sfImage *  resizeImage (  sfImage * actual_image ){

    puts("Resizing...");

    sfImage * auxiliar_image = NULL;
    auxiliar_image = sfImage_createFromFile("..\\auxiliar\\1280x720.png");

    if ( auxiliar_image != NULL ){

        sfVector2u *original_size = malloc( sizeof( sfVector2u * ) );
        sfVector2u *auxiliar_size = malloc( sizeof( sfVector2u * ) );

        original_size->x = sfImage_getSize( actual_image ).x;
        original_size->y = sfImage_getSize( actual_image ).y;
        auxiliar_size->x = sfImage_getSize( auxiliar_image ).x;
        auxiliar_size->y = sfImage_getSize( auxiliar_image ).y;

        for (unsigned int y = 0; y < auxiliar_size->y; y++) {
            for (unsigned int x = 0; x < auxiliar_size->x; x++) {

                unsigned int x_position = (unsigned int) ( (double)  x /  ( double ) auxiliar_size->x
                                                                                        *
                                                                          ( double ) original_size->x);


                unsigned int y_position = (unsigned int) ( (double)  y /  ( double ) auxiliar_size->y
                                                                                         *
                                                                              ( double ) original_size->y);

                sfImage_setPixel( auxiliar_image, x, y, sfImage_getPixel( actual_image, x_position, y_position ) );
            }
        }
        return auxiliar_image; //Returning the resized image...

    }

    puts("Failed opening the auxiliar image, check the file...");
    exit(-1);
}







sfImage * loadImagePath ( char * route ) {

    sfImage *image = NULL;
    image = sfImage_createFromFile( route  );

    if ( image == NULL ) {

        puts("Error loading the image, verify the path");
        exit( -1 );

    }else {

        sfVector2u *img_size = malloc( sizeof( sfVector2u * ) ); //Setting memory to vector struct
        img_size->x = sfImage_getSize( image ).x;
        img_size->y = sfImage_getSize( image ).y;

        if ( img_size->x < 700 || img_size->y < 700 ) { //Contemplar cambiar
            puts("Image pixels are to small, please change the picture");
            exit( -1 );

        }else {

            sfImage *resized_image= NULL;
            resized_image = resizeImage( image );

            return resized_image; //Returning....
        }
    }
}



void imageSavePath (  sfRenderTexture *render, char *filename ) {

    puts( "Saving the image..." );


    __auto_type renderTexture = sfRenderTexture_getTexture( render );
    __auto_type image = sfTexture_copyToImage( renderTexture );

    sfImage_saveToFile( image, filename);
    puts( "Image saved!!!" );
    exit(1);

}




void textures ( sfImage *image, sfText *text_one,  sfText *text_two, char * filename  ) {

    puts("Texturing...");

    sfVector2u       *img_size = malloc( sizeof( sfVector2u ) );
    sfVector2f       text_location;
    sfTexture        *img_texture;
    sfRenderTexture  *renderTexture;
    sfSprite         *sprite;
    sprite =         sfSprite_create(); //Giving memory to sprite



    img_size->x = sfImage_getSize( image ).x;
    img_size->y = sfImage_getSize( image ).y;


    text_location.x =  ( float ) img_size->x / ( float ) 3;
    text_location.y = 15;
    sfText_setPosition( text_one, text_location ); //Setting the text location


    img_texture   = sfTexture_createFromImage( image, NULL );
    renderTexture = sfRenderTexture_create( img_size->x, img_size->y, 1 );

    sfSprite_setTexture( sprite, img_texture, 0 );
    sfRenderTexture_drawSprite( renderTexture, sprite, 0 );
    sfRenderTexture_drawText( renderTexture, text_one, 0 );

    if ( text_two != NULL ) {

        text_location.x = ( float ) img_size->x / ( float )  3;
        text_location.y = ( float ) img_size->y / ( float ) 1.2;

        sfText_setPosition( text_two, text_location );
        sfRenderTexture_drawText( renderTexture, text_two, 0 );

    }

    sfRenderTexture_display( renderTexture );

    imageSavePath( renderTexture, filename ); //This method save the image





}


sfFont * fontLoad ( int font_type ) {

    if ( font_type > ( sizeof fonts_array / sizeof *fonts_array ) - 1 ) {
        puts("Font type index out of range, verify and try again");
        exit( -1 );
    }else {
        sfFont *font;
        font = sfFont_createFromFile( fonts_array[ font_type ] );
        return font;
    }
}

int fontSizeLoad ( int font_size ){

    if ( font_size > ( sizeof font_sizes / sizeof *font_sizes ) - 1 ) {
        puts("Font size out of index, verify and try again");
        exit( -1 );
    }else{

        return font_sizes[ font_size ];
    }
}




void textSettings ( sfImage *image, char *text1, char *text2, char *filename, int font_type, int font_size ) {

    puts( "Setting the text..." );

    sfText * text_one = NULL;
    sfText * text_two = NULL;

    sfFont * font = fontLoad( font_type );
    int fontSize = fontSizeLoad( font_size );

    text_one = sfText_create(); //Giving memory to pointer
    sfText_setFont( text_one, font );
    sfText_setCharacterSize( text_one, fontSize );
    sfText_setString( text_one, text1 );

    if ( strlen( text2 ) > 0 ) {


         text_two = sfText_create();
         sfText_setFont( text_two, font );
         sfText_setCharacterSize( text_two, fontSize );
         sfText_setString( text_two, text2 );

     }

     textures( image, text_one, text_two, filename );



}




int main() {



    sfImage *image = NULL;
    image = loadImagePath( "..\\process\\arenal.jpg" );
    textSettings(  image,
                  "",
                  "COSTA RIC",
                  "..\\saved\\prueba_final.bmp",
                  2,
                  5);


    return 0;

}