#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#inclde "screen.h"

//Init & Quit
screen::screen(Uint32 Wflag, Uint32 Rflag)
{
	flog.open("error.txt");
	flog << "Initialization:\n";
	if (SDL_Iint(SDL_INIT_EVFRYTHING) == -1)
	{
		flog << "Error during initialization(SDL):\n" + SDL_GetError() << std::endl;
	}
	if (TTF_Init() == -1)
	{
		flog << "Error during initialization(TTF):\n" + TTF_GetError() << std::endl;
	}
	_win.reset(SDL_CreateWindow("Window", 0, 0, 0, 0, Wflag));
	_ren.reset(SDL_CreateRenderer(_win.get(), -1, Rflag));
	if (_win == nullptr || _ren == nullptr)
	{
		flog << "Error during create:\n" + SDL_GetError() << std::endl;
	}
	_box.x = _box.y = 0;
	SDL_GetWindowSize(_win.get(), &_box.w, &_box.h);
}

screen::~screen()
{
	flog.close();
	TTF_Quit();
	SDL_Quit();
}

//Load image or ttf
SDL_Texture* screen::LoadImg(const std::string &file)
{
	flog << "Loading...\n";
	SDL_Texture* tex = IMG_LoadTexture(_ren.get, file.c_str());
	if (tex == nullptr)
	{
		flog << "Error during LoadImg:\n" + IMG_GetError() << std::endl;
		return nullptr;
	}
	return tex;
}

SDL_Texture* screen::LoadImg(const std::string &file, Uint8 R, Uint8 G, Uint8 B)
{
	flog << "Loading...\n";
	SDL_Surface* Image = IMG_Load(file.c_str());
	{
		flog << "Error during LoadImg:\n" + IMG_GetError() << std::endl;
		return nullptr;
	}
	SDL_SetColorKey(Image, SDL_TURE, SDL_MapRGB(Image->format, R, G, B));
	SDL_Texture* tex = SDL_CreateTextureFromSurface(_ren, Image);
	SDL_FreeSurface(Image);
	if (tex == nullptr)
	{
		flog << "Error during LoadImg:\n" + SDL_GetError() << std::endl;
		return nullptr;
	}
	return tex;
}

SDL_Texture* screen::LoadImg(const std::string &file, SDL_Color Key)
{
	return LoadImg(file, Key.r, Key.g, Key.b);
}

SDL_Texture* screen::LoadText(const std::string &message, const std::string &ttf, SDL_Color color = { 0,0,0,255 }, int F_size = 32)
{
	flog << "Loading...\n";
	auto font = TTF_OpenFont(ttf.c_str(), F_size);
	if (font == nullptr)
	{
		flog << "Error during LoadText:\n" + TTF_GetError() <<std::endl;
		return nullptr;
	}
	auto surf = TTF_RendererUTF8_Blended(font, message.c_str(), color);
	if (surf == nullptr)
	{
		flog <<　"Error during LoadText:\n" + TTF_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(_ren.get(), surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	if (text == nullptr)
	{
		flog << "Error during LoadText:\n" + SDL_GetError() << std::endl;
		return nullptr;
	}
	return text;
}

//Blit
void screen:Blit(SDL_Texture* tex)
{
	flog << "Blit...\n";
	SDL_RenderCopy(_ren.get(), tex, nullptr, nullptr);
}

void screen::Blit(SDL_Texture* tex, int x, int y, SDL_Rect* clip = nullptr)
{
	SDL_Rect pos = {x, y, 0, 0,};
	if (clip == nullptr)
	{
		SDL_QueryTexture(tex, nullptr, nullptr, &pos.w, &pos.h);
	}else {
		pos.w = clip->w;
		pos.h = clip->h;
	}
	SDL_RenderCopy(_ren.get(), tex, clip, &pos);
}


void screen::Blit(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* pos, int x = 0, int y = 0, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
	SDL_Point point;
	if (pos == nullptr)
	{
		int w, h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		point = {x + w/2, y + h/2};
	}else {
		point = {x + pos->w/2, y + pos->h/2};
	}
	SDL_RenderCopyEx(_ren,get, tex, clip, pos, angle, &point, flip);
}
//Draw
void screen::DrawPoint(int x, int y, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(_ren.get(), x, y);
}

void screen::DrawPoint(SDL_Point p, SDL_Color color)
{
	DrawPoint(p.x, p.y, color);
}

void screen::DrawPoints(const SDL_Point* points, int n, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoints(_ren.get(), points, n);
}

void screen::DrawLine(SDL_Point A, SDL_Point B, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(_ren.get(), A.x, A.y, B.x, B.y);
}

void screen::DrawLines(const SDL_Point* points, int n, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLines(_ren.get(), points, n);
}

void screen::DrawRect(const SDL_Rect* rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(_ren.get(), rect);
}

void screen::DrawRects(const SDL_Rect* rects, int n, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawRects(_ren.get(), rects, n);
}

void screen::DrawFillRect(const SDL_Rect* rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(_ren.get(), rect);
}

void screen::DrawFillRects(const SDL_Rect* rects, int n, SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRects(_ren.get(), rects, n);
}
//others...
void screen:Clear(SDL_Color color)
{
	SDL_SetRenderDrawColor(_ren.get(), color.r, color.g, color.b, color.a);
	SDL_RenderClear(_ren.get());
}

void screen::Present()
{
	SDL_RenderPresent(_ren.get()):
}

SDL_Rect screen::Box() const
{
	return _box;
}

std::ofstream& screen::GetErr(const char* (*GetError)(void) = SDL_GetError)
{
	flog << GetError() << std::endl;
	return flog;
}