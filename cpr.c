//
//
//  MMP""MM""YMM              `7MM"""Mq.                        `7MM"""Mq.
//  P'   MM   `7                MM   `MM.                         MM   `MM.
//       MM  .gP"Ya   ,6"Yb.    MM   ,M9  .gP"Ya `7M'   `MF'      MM   ,M9 `7Mb,od8 ,pW"Wq.   .P"Ybmmm `7Mb,od8 ,6"Yb.  `7MMpMMMb.pMMMb.  ,pP"Ybd
//       MM ,M'   Yb 8)   MM    MMmmdM9  ,M'   Yb  `VA ,V'        MMmmdM9    MM' "'6W'   `Wb :MI  I8     MM' "'8)   MM    MM    MM    MM  8I   `"
//       MM 8M""""""  ,pm9MM    MM  YM.  8M""""""    XMX          MM         MM    8M     M8  WmmmP"     MM     ,pm9MM    MM    MM    MM  `YMMMa.
//       MM YM.    , 8M   MM    MM   `Mb.YM.    ,  ,V' VA.        MM         MM    YA.   ,A9 8M          MM    8M   MM    MM    MM    MM  L.   I8
//     .JMML.`Mbmmd' `Moo9^Yo..JMML. .JMM.`Mbmmd'.AM.   .MA.    .JMML.     .JMML.   `Ybmd9'   YMMMMMb  .JMML.  `Moo9^Yo..JMML  JMML  JMML.M9mmmP'
//                                                                                           6'     dP
//                                                                                           Ybmmmd'
//
//
// Created by: Trey Adams


#include <stdio.h>
#include <string.h>
#include <raylib.h>
// init game screens
typedef enum GameScreen
{
    SplashScreen = 0,
    StartScreen,
    PlayScreen
} GameScreen;


int main(void)
{
    // init game screen 
    const int screenWidth = 1800;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "CPR SIMULATOR");    
    SetTargetFPS(60);
    // init current screen
    GameScreen currentScreen = SplashScreen;
    
    // init audio devices 
    InitAudioDevice();

    //------Splash Screen---------------
    // TREX init
    Image TREX_image = LoadImage("images/TREX.png");
    Texture2D TREX_texture = LoadTextureFromImage(TREX_image);
    UnloadImage(TREX_image);
    // alpha levels
    float imageTREX_alpha = 0.0f;
    float spaceText_alpha = 0.0f;
    float top_botText_alpha = 1.0f;
    // init state
    int state = 0;
    // init top and bottom text
    int topText_yaxis = -50;
    int bottomText_yaxis = screenHeight;
    int splahScreenFontSize = 50;
    // load tokyo-cafe.wav
    Music tokyocafe_wav = LoadMusicStream("sounds/tokyo-cafe.wav");
    PlayMusicStream(tokyocafe_wav);


    //--------Start Screen---------------

    //-------Play Screen-----------------


    while (!WindowShouldClose())
    {
        

        // update music stream
        
        
        // splashscreen

        if (currentScreen == SplashScreen && IsKeyDown(KEY_SPACE))
        {
            // Transition to PlayScreen
            currentScreen = StartScreen;
            // Reset flags for the new screen
            
        }

        switch(currentScreen)
        {
        case SplashScreen:
        {
            // play music
            UpdateMusicStream(tokyocafe_wav);

            printf("State: %d, Alpha: %.2f\n", state, imageTREX_alpha);

            // init states
            if (state == 0)
            {
                topText_yaxis += 0.6f*GetFrameTime()*60.0f;
                bottomText_yaxis -= 0.6f*GetFrameTime()*60.0f;
                
                if(topText_yaxis >= 3 || bottomText_yaxis <= screenHeight-splahScreenFontSize)
                {
                    topText_yaxis = 3;
                    bottomText_yaxis = (screenHeight-splahScreenFontSize);
                    state = 1;     
                }
            }
            else if (state == 1)
            {
                
                imageTREX_alpha += 0.007f*GetFrameTime()*60.0f;                
                if(imageTREX_alpha >= 1.0f)
                {
                    imageTREX_alpha = 1.0f;
                    state = 2;
                }
                
            }
            else if (state == 2)
            {
                spaceText_alpha += 0.007f;
                if (spaceText_alpha >= 1.0f)
                {
                    spaceText_alpha = 1.0f;
                }
            }
                       
            break;
        }
        case StartScreen:
        {
            UpdateMusicStream(tokyocafe_wav);
            break;
        }
        case PlayScreen:
        {
            
        }
        }

        BeginDrawing();

        ClearBackground(WHITE);

        switch(currentScreen)
        {
        case SplashScreen:
        {
            // Top Text render
            DrawText("TREX Programs presents.....", 5, topText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            // TREX texture render
            DrawTexture(TREX_texture, (screenWidth/2)-(TREX_texture.width/2), (screenHeight/2) - (TREX_texture.height/2), ColorAlpha(WHITE, imageTREX_alpha));
            DrawText("Press SPACE to continue", 5, (screenHeight/2), 30, ColorAlpha(BLACK, spaceText_alpha));
            // bottom text render
            int productionLength = MeasureText(".....A TREX Programs production", 50);                
            DrawText(".....A TREX Programs production", screenWidth-(productionLength+5), bottomText_yaxis, 50, ColorAlpha(BLACK, top_botText_alpha));
            
            break;
        }
        case StartScreen:
        {

        }
        case PlayScreen:
        {

        }
        }
        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;    

    
}