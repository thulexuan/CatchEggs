#include "CommonFunction.h"
#include "BaseObject.h"
#include "Player.h"
#include "Eggs.h"
#include "Bomb.h"
#include "HealthObject.h"
#include "TextObject.h"


TTF_Font* font_score;

bool Init()
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    ret = SDL_Init(SDL_INIT_AUDIO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("--------------------------------------------------CATCH EGG--------------------------------------------", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
            {
                success = false;
            }
        }

        g_sound = Mix_LoadMUS("sound//ChocoboRacingCidsTestCourse-HoaTau-3316605.mp3");
        if (g_sound == NULL)
        {
            success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_score = TTF_OpenFont("font//Starcraft Normal.ttf", 15);
        if (font_score == NULL)
        {
            success = false;
        }
    }

    return success;
}

BaseObject g_background;
bool LoadBackGround()
{
    bool ret = g_background.LoadImg("img//background.png", g_screen);
    if (ret == false) return false;
    return true;
}

BaseObject g_menu_end;
bool Gameover()
{
    bool ret2 = g_menu_end.LoadImg("img//gameover-0.png", g_screen);
    if (ret2 == false) return false;
    const int num_item_menu_end = 2;
    SDL_Rect pos_arr_end[num_item_menu_end];

    pos_arr_end[0].x = 200;
    pos_arr_end[0].y = 300;

    pos_arr_end[1].x = 200;
    pos_arr_end[1].y = 350;

    TextObject text_menu_end[num_item_menu_end];

    text_menu_end[0].setText("Play Again");
    text_menu_end[0].setColor(TextObject::BLACK_TEXT);
    text_menu_end[0].LoadFromRenderText(font_score, g_screen);


    text_menu_end[1].setText("Exit");
    text_menu_end[1].setColor(TextObject::BLACK_TEXT);
    text_menu_end[1].LoadFromRenderText(font_score, g_screen);
    return true;
}

void close()
{
    g_background.Free();


    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_FreeMusic(g_sound);
    g_sound = NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    if (Init() == false) return -1;

    Mix_PlayMusic(g_sound, -1);

    // Menu start
    BaseObject g_menu_;
    bool ret1 = g_menu_.LoadImg("img//menu.png", g_screen);
    if (ret1 == false) return -1;

    const int num_item_menu = 2;
    SDL_Rect pos_arr[num_item_menu];

    pos_arr[0].x = 200;
    pos_arr[0].y = 300;

    pos_arr[1].x = 200;
    pos_arr[1].y = 350;

    TextObject text_menu[num_item_menu];

    text_menu[0].setText("Play");
    text_menu[0].setColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font_score, g_screen);


    text_menu[1].setText("Exit");
    text_menu[1].setColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font_score, g_screen);

    SDL_Event m_event;

    // Menu game over
    BaseObject g_menu_end;
    bool ret2 = g_menu_end.LoadImg("img//gameover-0.png", g_screen);
    if (ret2 == false) return -1;



    while (true)
    {
        g_menu_.Render(g_screen);
        text_menu[0].RenderText(g_screen, pos_arr[0].x, pos_arr[0].y);
        text_menu[1].RenderText(g_screen,  pos_arr[1].x, pos_arr[1].y);
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                return 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                int xm = m_event.button.x;
                int ym = m_event.button.y;

                if (xm >=200 && xm <= 250 && ym >=350 && ym <= 400)
                {
                    close();
                }

                if (xm >= 200 && xm <= 250 && ym >= 300 && ym <=350)
                {
                    if (LoadBackGround() == false) return -1;
                    //g_sound = Mix_LoadMUS("sound//beat.wav");
                    //if (g_sound == NULL) return -1;

                    Player basket;
                    basket.SetRect(400, 450);
                    bool ret = basket.LoadImg("img//basket2.png", g_screen);
                    if (ret == false) return false;

                    HealthObject health_object;
                    health_object.Init(g_screen);

                    Eggs* eggs = new Eggs[NUM_OBSTACLE];
                    for (int t = 0; t < NUM_OBSTACLE; t++)
                    {
                        Eggs* egg =  (eggs + t);
                        ret = egg->LoadImg("img//egg2.png", g_screen);
                        if (ret == false)
                        {
                            return 0;
                        }
                        int rand_x = SDLCommonFunc::getRandomNumber(0,1000) ;
                        egg->SetRect(rand_x, -t*100);
                        egg->set_y_val(2);
                    }

                    Bomb* bombs = new Bomb[NUM_BOMB];
                    for (int i = 0; i< NUM_BOMB; i++)
                    {
                        Bomb* bomb = (bombs + i);
                        ret = bomb->LoadImg("img//bomb2 (2).png", g_screen);
                        if (ret == false) return 0;
                        int rand_x = SDLCommonFunc::getRandomNumber(0,1000);
                        bomb->SetRect(rand_x, -i*200);
                        bomb->set_y_val(2);

                    }

                    TextObject score_text;
                    score_text.setColor(TextObject::RED_TEXT);
                    UINT score = 0;
                    unsigned int num_die_ = 0;

                    bool is_quit = false;
                    while (!is_quit)
                    {
                        while (SDL_PollEvent(&g_event) != 0)
                        {
                            if (g_event.type == SDL_QUIT)
                            {
                                is_quit = true;
                                break;
                            }


                            basket.HandleInputAction(g_event);
                        }

                        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
                        SDL_RenderClear(g_screen);

                        g_background.Render(g_screen);
                        //Mix_PlayMusic(g_sound, -1);
                        health_object.Render(g_screen);
                        basket.HandleMove();
                        basket.Render(g_screen);

                        health_object.Show(g_screen);

                        for (int tt=0; tt < NUM_OBSTACLE; tt++)
                        {
                            Eggs* egg = (eggs + tt);
                            if (egg)
                            {
                                egg->HandleMove();
                                egg->Render(g_screen);
                            }
                            SDL_Delay(1);

                            bool is_col_1 = SDLCommonFunc::CheckCollision(basket.GetRect(), egg->GetRect());
                            if (is_col_1)
                            {
                                egg->SetRect(SDLCommonFunc::getRandomNumber(0,1000), 0);
                                score++ ;
                            }
                        }

                        for (int ii = 0; ii < NUM_BOMB; ii++)
                        {
                            Bomb* bomb = (bombs+ii);
                            if (bomb)
                            {
                                bomb->HandleMove();
                                bomb->Render(g_screen);
                            }
                            SDL_Delay(1);
                            bool is_col_2 = SDLCommonFunc::CheckCollision(basket.GetRect(), bomb->GetRect());
                            if (is_col_2)
                            {
                                bomb->SetRect(SDLCommonFunc::getRandomNumber(0,1000), 0);
                                num_die_ ++;
                                if (num_die_ < 3)
                                {
                                    health_object.Decrease();
                                    health_object.Render(g_screen);
                                    //continue;
                                }
                                 if (num_die_ == 3)
                                {

                                    SDL_Delay(1000);
                                    g_menu_end.Render(g_screen);
                                    SDL_RenderPresent(g_screen);
                                    SDL_Delay(3000);
                                    return 0;

                                    //close();
                                    //SDL_Quit();
                                    //return 0;
                                }
                            }
                        }




                        std::string score_val = std::to_string(score);
                        std::string str_score("Score: ");
                        str_score += score_val;
                        score_text.setText(str_score);
                        score_text.LoadFromRenderText(font_score, g_screen);
                        score_text.RenderText(g_screen, SCREEN_WIDTH / 2 - 30, 10);

                        SDL_RenderPresent(g_screen);

                    }

                }

                break;
            }
            default:
                break;
            }
        }
        SDL_RenderPresent(g_screen);
    }



    close();
    return 0;

}


