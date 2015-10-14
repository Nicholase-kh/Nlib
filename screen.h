#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

#include <string>
#include <memory>
#include <fstream>

class screen {
public:
	//Init & Quit
	screen(Uint32 Wflag = 0, Uint32 Rflag = (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	~screen();
	//Load image or ttf
	SDL_Texture* LoadImg(const std::string &file);
	SDL_Texture* LoadImg(const std::string &file, Uint8 R, Uint8 G, Uint8 B);
	SDL_Texture* LoadImg(const std::string &file, SDL_Color Key);
	SDL_Texture* LoadText(const std::string &message, const std::string &ttf, SDL_Color color = { 0,0,0,255 }, int F_size = 32);
	//Blit
	void Blit(SDL_Texture* tex);
	void Blit(SDL_Texture* tex, int x, int y, SDL_Rect* clip = nullptr);
	void Blit(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* pos, int x = 0, int y = 0, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);//flip: SDL_FLIP_NONE SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
	//Draw
	void DrawPoint(int x, int y, SDL_Color color = {0, 0, 0, 255});
	void DrawPoint(SDL_Point p, SDL_Color color = {0, 0, 0, 255});
	void DrawPoints(const SDL_Point* points, int n, SDL_Color color = {0, 0, 0, 255});
	void DrawLine(SDL_Point A, SDL_Point B, SDL_Color color = {0, 0, 0, 255});
	void DrawLines(const SDL_Point* points, int n, SDL_Color color = {0, 0, 0, 255});
	void DrawRect(const SDL_Rect* rect, SDL_Color color = {0, 0, 0, 255});
	void DrawRects(const SDL_Rect* rects, int n, SDL_Color color = {0, 0, 0, 255});
	void DrawFillRect(const SDL_Rect* rect, SDL_Color color = {0, 0, 0, 255});
	void DrawFillRects(const SDL_Rect* rects, int n, SDL_Color color = {0, 0, 0, 255});
	//others...
	void Clear(SDL_Color color = {0, 0, 0, 0});
	void Present();
	SDL_Rect Box() const;
	std::ofstream& GetErr(const char* (*GetError)(void) = SDL_GetError);
private:
	std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> _win = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
	std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> _ren = std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);
	SDL_Rect _box;
	std::ofstream flog;
};

#endif