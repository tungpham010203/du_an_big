// #include"khoitao.h"
#include "runCheDoVatPham.h"
const int SCREEN_WIDTH = 1850;//1850;//rộng
const int SCREEN_HEIGHT = 1000;
const int pxDichChuyen = 15;
const int toaDoYNhanVat=760;
int level=1;
// cua so win
SDL_Window* gWindow = NULL;
SDL_Surface* gALL = NULL;
Mix_Chunk* soundCoi=NULL;
Mix_Chunk* soundNo=NULL;
Mix_Music* musicVatpham=NULL;
int tocDoRoi=3;

//0=quay mặt sang phải
// 1 = quay mặt sang trái
// 2 = chạy sang phải
// 3 = chạy sang trái
// 4 = nhảy
// 5 = ngã
int checkHoatDong=0;

int chieuCaoKhungNhanVat = 150;
int chieuRongKhungNhanVat = 90;
int HP=3;
double timecu,timeXuatHien,timeXuatHienBom=0;
int soLuongCoin=0;//số lượng vật phẩm đang có trên màn hình
int soLuongBom=0;
bool arrCoinTrueFalse[5]{false,false,false,false,false};//vvật phẩm nài còn trên màn hình
bool arrBomTrueFalse[5]{false,false,false,false,false};
long diem=0;
SDL_Rect sizeHP;
SDL_Rect sizeCat;

nhanvat bia[5]{
nhanvat(gALL,"bianho.png",1850,0),
nhanvat(gALL,"bianho.png",1850,0),
nhanvat(gALL,"bianho.png",1850,0),
nhanvat(gALL,"bianho.png",1850,0),
nhanvat(gALL,"bianho.png",1850,0)
};
nhanvat bom[5]{
nhanvat(gALL,"bom.png",1850,0),
nhanvat(gALL,"bom.png",1850,0),
nhanvat(gALL,"bom.png",1850,0),
nhanvat(gALL,"bom.png",1850,0),
nhanvat(gALL,"bom.png",1850,0)
};


nhanvat gBackground(gALL,"anhnenchuan.png",0,0);
nhanvat thanhHP(gALL,"data/3timmau.png", 1607,361);
nhanvat nutChucNang(gALL,"data/nutchucnangTrong.png",1754,0);
nhanvat khungNoi(gALL,"data/khunganhnenchuan.png",0,0);
nhanvat nhanVatgame(gALL,"data/nhanvatgame.png",600,toaDoYNhanVat);
nhanvat troNgaiOng(gALL,"data/ong,png",0,0);
nhanvat endGame(gALL,"data/manEndGame.png",688,200);
nhanvat nutNext(gALL,"data/nutnext.png",841,738);
nhanvat sao[4]{
nhanvat(gALL," ",0,0),
nhanvat(gALL,"data/1sao.png",872,295),
nhanvat(gALL,"data/2sao.png",767,322),
nhanvat(gALL,"data/3sao.png",767,300)
};
Text textDiem(gALL, "data/3Dumb.ttf", 65,  intToString(diem).c_str(),  { 255, 255, 255,255 },  1590, 510);
Text textLevel(gALL, "data/3Dumb.ttf", 65,  ("level "+intToString(level)).c_str(),  { 255, 255, 255,255 },  1580, 810);

const Uint8 * keyState;
// int main( int argc, char* args[] ){
//     runCheDoVatPham("ssss");
//     return 0;
// }
void troNgaiong(){
    if (nhanVatgame.returnToaDoX()>troNgaiOng.returnToaDoX())
    {
        troNgaiOng.updateToaDoX(troNgaiOng.returnToaDoX()+2);
        troNgaiOng.updateToaDoY(troNgaiOng.returnToaDoY+3);
    }
    else
    {
        
        troNgaiOng.updateToaDoX(troNgaiOng.returnToaDoX()-2);
        troNgaiOng.updateToaDoY(troNgaiOng.returnToaDoY+3);
    }
}
void hamEndGame(){
    bool quit=false;
    SDL_Event e;
    int x, y;
    while (quit==false)
    {
        keyState = SDL_GetKeyboardState(NULL);
        while (SDL_PollEvent(&e)){
            endGame.updateBeMat(gALL);
            // std::cout<<x<<" "<<y<<"\n";
            SDL_GetMouseState(&x, &y);
            if (x>841&&x<841+177&&y>738&&y<63+738)
            {
                nutNext.updateBeMat(gALL);
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    Mix_PlayChannel(-1, soundCoi, 0);
                    quit=true;              
                }
                else if (keyState[SDL_SCANCODE_KP_ENTER])
                {
                    Mix_PlayChannel(-1, soundCoi, 0);
                    quit=true;  
                }
                
            }
            
        }
        if (HP==3)
        {
            sao[3].updateBeMat(gALL);
        }
        else if (HP==2)
        {
            sao[2].updateBeMat(gALL);   
        }
        else if (HP==1)
        {
            sao[1].updateBeMat(gALL);
        }
        SDL_UpdateWindowSurface(gWindow);
    }
}
long runCheDoVatPham(std::string name)
{
    sizeCat.x = 0;
    sizeCat.y = 0;
    sizeCat.w = chieuRongKhungNhanVat;
    sizeCat.h = chieuCaoKhungNhanVat;
    
    
    if (!init())
    {
        std::cout<<"khong the khoi tao.";   
        return 1;
    }
    Text textName(gALL, "data/3Dumb.ttf", 35,  name.c_str(),  { 255, 255, 255,255 },  1550, 230);
    SDL_Event e;
    bool quit = false;
    // Xóa bộ đệm hiển thị
    // SDL_FillRect(ga, NULL, SDL_MapRGB(textSurface->format, 0x00, 0x00, 0x00));


    
    while (quit == false)
    {
        // Xóa màn hình
        // SDL_FillRect(gALL, NULL, SDL_MapRGB(gALL->format, 0xFF, 0xFF, 0xFF));
        // if (checkHoatDong==2)checkHoatDong=0;
        // else checkHoatDong=1;
        if (clock()-timeXuatHien>900 && soLuongCoin<5&&arrCoinTrueFalse[soLuongCoin]==false)
        {
            timeXuatHien=clock();
            bia[soLuongCoin].updateToaDoX(ranDom());
            arrCoinTrueFalse[soLuongCoin]=true;
            // bia[soLuongCoin].updateToaDoX(ranDom());
            soLuongCoin++;
        }
        if (clock()-timeXuatHienBom>500 && soLuongBom<5&&arrBomTrueFalse[soLuongBom]==false)
        {
            timeXuatHienBom=clock();
            bom[soLuongBom].updateToaDoX(ranDom());
            arrBomTrueFalse[soLuongBom]=true;
            soLuongBom++;
        }
        if (soLuongCoin==5)
        {
            soLuongCoin=0;
        }
        if (soLuongBom==5)
        {
            soLuongBom=0;
        }
        
        keyState = SDL_GetKeyboardState(NULL);
        //Background
        gBackground.updateBeMat(gALL);
        while (SDL_PollEvent(&e))
        // if (SDL_PollEvent(&e))
        {
            
            if (e.type == SDL_QUIT)quit = true;
            
            // else if(e.key.keysym.sym== SDLK_LEFT){
            //     if (checkHoatDong==){
            //         checkHoatDong=true;
            //         nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()-60);
            //     }
            //     else{
            //     nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()-pxDichChuyen);
            //     }
            // }
            // else if(e.key.keysym.sym==SDLK_RIGHT){
            //     if (checkHoatDong==true){
            //         checkHoatDong=false;
            //         nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()+60);
            //     }
            //     else{
            //         nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()+pxDichChuyen);
            //         // SDL_BlitSurface(nhanvatll, NULL, gALL, &{100,100});
            //     }
            // }
            //phai



        //     int x, y;
        // SDL_GetMouseState(&x, &y);
        //     if (e.type == SDL_MOUSEBUTTONDOWN) {
        //         // Mix_PlayChannel(-1, soundCoi, 0);
        //         std::cout<<x<<" "<<y<<"\n";                  
        //     }
        }
        
            if(keyState[SDL_SCANCODE_A]||keyState[SDL_SCANCODE_LEFT]){
                if (checkHoatDong==1){
                    checkHoatDong=3;
                    nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()-60);
                    if (clock()-timecu>30)
                    {
                        sizeCat.x += 90;
                        if (sizeCat.x >= 430)sizeCat.x = 0;
                        timecu=clock();
                    }
                }
                else{
                    checkHoatDong=3;
                nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()-pxDichChuyen);
                if (clock()-timecu>30)
                    {
                        sizeCat.x += 90;
                        if (sizeCat.x >= 430)sizeCat.x = 0;
                        timecu=clock();
                    }
                }
            }
            
            
            //trai
            else if(keyState[SDL_SCANCODE_D]||keyState[SDL_SCANCODE_RIGHT]){
                if (checkHoatDong==0){
                    checkHoatDong=2;
                    nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()+60);
                    if (clock()-timecu>1)
                    {
                        sizeCat.x += 90;
                        if (sizeCat.x >= 430)sizeCat.x = 0;
                        timecu=clock();
                    }
                }
                else{
                    checkHoatDong=2;
                    nhanVatgame.updateToaDoX(nhanVatgame.returnToaDoX()+pxDichChuyen);
                    if (clock()-timecu>1)
                    {
                        sizeCat.x += 90;
                        if (sizeCat.x >= 430)sizeCat.x = 0;
                        timecu=clock();
                    }
                    // SDL_BlitSurface(nhanvatll, NULL, gALL, &{100,100});
                }
            }
        trangThaiNhanVat();
        vaTram();

        for (int i = 0; i < 5; i++)
        {
            if (arrCoinTrueFalse[i]==true)
            {
                bia[i].updateToaDoY(bia[i].returnToaDoY()+tocDoRoi);
            }
            if (arrBomTrueFalse[i]==true)
            {
                bom[i].updateToaDoY(bom[i].returnToaDoY()+tocDoRoi+1);
                
            }
            
        }
        ////////////////////////////////////////////////////////////////////////////
        //update
        
        //Tiền + bom
        for (int i = 0; i < 5; i++)
        {   
            bia[i].updateBeMat(gALL);
            bom[i].updateBeMat(gALL);
        }
        //nhân vật
        nhanVatgame.updateBeMat(gALL,sizeCat);
        //khung
        khungNoi.updateBeMat(gALL);

        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x>1754&&x<1850&&y>0&&y<100)
        {
            nutChucNang.updateBeMat(gALL);
            
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                Mix_PlayChannel(-1, soundCoi, 0);    
                           
            }
    
        }
        
        //thanh HP
        updateHP();
        //điểm
        textDiem.updateBeMatText(gALL, intToString(diem).c_str(),{ 255, 255, 255 });
        textLevel.updateBeMatText(gALL,("level "+intToString(level)).c_str(),{ 0, 0, 0 });
        //usersName
        textName.updateBeMatText(gALL);

        //////////////////////////////////////////////////////////////////////////////
        // Cập nhật
        SDL_UpdateWindowSurface(gWindow);
        
        if (HP==0)
        {
            quit=true;
        }
        
        SDL_FillRect(gALL, NULL, SDL_MapRGB(gALL->format, 0x00, 0x00, 0x00));
        SDL_Delay(10);
        
    }
	// close();100/3
	return diem;
}

int hamLevel(){
    if ((diem>=500&&level==1))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=1000&&level==2))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=1500&&level==3))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=2000&&level==4))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=2500&&level==5))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=3000&&level==6))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=3500&&level==7))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=4000&&level==8))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
    else if ((diem>=4500&&level==9))
    {
        hamEndGame();
        HP++;
        level++;
        tocDoRoi++;
    }
}

bool init(){
    gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN );
	if( gWindow == NULL ){
        std::cout<<( "Window could not be created! SDL_Error:\n", SDL_GetError() );
        return false;
    }
    gALL = SDL_GetWindowSurface( gWindow );
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    musicVatpham = Mix_LoadMUS("nhacnendotoc.mp3");
    Mix_PlayMusic(musicVatpham, -1);
    soundCoi = Mix_LoadWAV("data/coin.wav");
    soundNo = Mix_LoadWAV("data/bomNo.wav");
    return true;
}
void vaTram(){
    for (int i = 0; i < 5; i++)
    {
    if ((nhanVatgame.returnToaDoX()+30<=bia[i].returnToaDoX()&&(nhanVatgame.returnToaDoX()+60>=bia[i].returnToaDoX())) && ((bia[i].returnToaDoY()<850)&&(bia[i].returnToaDoY()>750)))
    //||(nhanVatgame.returnToaDoX()+30<=bia[i].returnToaDoX()&&(nhanVatgame.returnToaDoX()+120>=bia[i].returnToaDoX())) && ((bia[i].returnToaDoY()<toaDoYNhanVat+50)&&(bia[i].returnToaDoY()>toaDoYNhanVat)))
    {
        // bia[i].updateToaDoX(ranDom());
        // bia[i].updateToaDoY(1);
        Mix_PlayChannel(-1, soundCoi, 0);
        arrCoinTrueFalse[i]=false;
        diem+=100;
        bia[i].updateToaDoX(1900);
        bia[i].updateToaDoY(1);
        hamLevel();
    }
    if ((nhanVatgame.returnToaDoX()+30<=bom[i].returnToaDoX()&&(nhanVatgame.returnToaDoX()+60>=bom[i].returnToaDoX())) && ((bom[i].returnToaDoY()<850)&&(bom[i].returnToaDoY()>750)))
    {
        // bom[i].updateToaDoX(ranDom());
        // bom[i].updateToaDoY(1);
        Mix_PlayChannel(-1, soundNo, 0);
        arrBomTrueFalse[i]=false;
        diem-=200;
        HP--;
        bom[i].updateToaDoX(1900);
        bom[i].updateToaDoY(1);
    }
    
    if (bia[i].returnToaDoY()>1000)
    {
        int x=ranDom();
        arrCoinTrueFalse[i]=false;
        bia[i].updateToaDoX(1900);
        bia[i].updateToaDoY(1);
    }
    if (bom[i].returnToaDoY()>1000)
    {
        int x=ranDom();
        arrBomTrueFalse[i]=false;
        bom[i].updateToaDoX(1900);
        bom[i].updateToaDoY(1);
    }
    }
    if (nhanVatgame.returnToaDoX()>1450)
    {
        nhanVatgame.updateToaDoX(1450);
    }
        
}
void trangThaiNhanVat(){
    // 0 = quay mặt sang phải
    // 1 = quay mặt sang trái
    // 2 = chạy sang phải
    // 3 = chạy sang trái
    // 4 = nhảy
    // 5 = ngã
    if (checkHoatDong==0)
    {
        sizeCat.y = 0;
    }
    else if (checkHoatDong==1)
    {
        sizeCat.y= chieuCaoKhungNhanVat*1;
    }
    else if (checkHoatDong==2)
    {
        sizeCat.y = chieuCaoKhungNhanVat*2;
    }
    else if (checkHoatDong==3)
    {
        sizeCat.y = chieuCaoKhungNhanVat*3;
    }
    else if (checkHoatDong==4)
    {
        sizeCat.y = chieuCaoKhungNhanVat*4;
    }
    else if (checkHoatDong==5)
    {
        sizeCat.y = chieuCaoKhungNhanVat*5;
    }
    if (clock()-timecu>100)
    {
        sizeCat.x += 90;
        timecu=clock();
        if (sizeCat.x >= 449)sizeCat.x = 0;
    }
}
void updateHP(){
    if (HP==3)
        {
            
            thanhHP.updateBeMat(gALL);
            
        }else if(HP==2)
        {
            
            sizeHP.w = 53*2;
            sizeHP.h = 49;
            thanhHP.updateBeMat(gALL,sizeHP);
        }
        else if (HP==1)
        {
            sizeHP.w = 53;
            sizeHP.h = 49;
            thanhHP.updateBeMat(gALL,sizeHP);
        }
        else if (HP==0)
        {
            sizeHP.w = 0;
            sizeHP.h = 0;
            thanhHP.updateBeMat(gALL,sizeHP);
        }
}

// void close()
// {
// 	//Deallocate surface
// 	SDL_FreeSurface( gBackground );
// 	gBackground = NULL;
    
//     //
//     SDL_FreeSurface(nhanVatgame);
//     nhanVatgame = NULL;

//     SDL_FreeSurface(nhanVatgame);
//     nhanVatgame = NULL;
// 	//Destroy window
// 	SDL_DestroyWindow( gWindow );
// 	gWindow = NULL;

// 	//Quit SDL subsystems
// 	SDL_Quit();
// }
