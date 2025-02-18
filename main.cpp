#include "runCheDoVatPham.h"
#include "manHinhKhoiDong.h"
#include "endGame.h"
// std::string Name;//tên người chơi
long diemdadat=0;//điểm đạt được
int chedo=0;//chọn chế độ chơi
std::string inputString;
bool checkLoa=true;
Mix_Music* music=NULL;
bool initMain(){
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
        std::cout<<"Khong khoi tao duoc SDL: \n"<<SDL_GetError();
        return false;
    }
    if (TTF_Init()<0)
    {
        std::cout<<"Khong khoi tao duoc TTF: \n";
        return false;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout<<"Khong khoi tao duoc SDL: \n"<< IMG_GetError();
        return false;
    }
    
    return true;
}

int main( int argc, char* args[] )
{
    if (initMain())
    {
        //màn đăng nhập
        tieptuc:
        chedo=manHinhKhoiDong();
        std::cout<<inputString;
        // if (checkLoa==true)
        // {
        //     music = Mix_LoadMUS("data/nhacnendotoc.mp3");
        //     Mix_PlayMusic(music, -1);
        // }
        
        //inputString!="        " //ấn nút thoát ngay trong màn hình đăng nhập
        if (inputString!="        ")
        {
            if (chedo==1)
            {
                //chế độ vât phẩm
                diemdadat=runCheDoVatPham(inputString);
                close();
                chedo=0;
            }else if (chedo==2)
            {
                //che độ text
                chedo=0;
                return 0;
            }
            //khi ấn thoát ở trong game
            if (diemdadat==-1000)
            {
                SDL_Quit();
                return 0;
            }
            bool luaChonKetThuc=false;
            luaChonKetThuc=endGame(level,diemdadat,inputString);
            //tiep tuc choi
            if (luaChonKetThuc==true&&chedo==0)
            {   
                goto tieptuc;
            }
            // thoat
            else if (luaChonKetThuc==false&&chedo==0)
            {
                return 0;
            }
        }
    }
    SDL_Quit();
    return 0;
}