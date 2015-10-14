#ifndef NLIB_H
#define NLIB_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>

//SDL tool
#include "screen.h"
#include "timer.h"

//图形
#include "shape.h"
using rectangle = SDL_Rect;
using point = SDL_Point;

//运动 碰撞 反射
#include "box.h"

//矩阵（变换）……运算（二阶矩阵=2D变换）
#include "matrix.h"

//____常量定义____
//路径
const std::string root = ""; //当前文件路径
const std::string ttfroot = root + "ttf/"; //当前字体路径
const std::string imageroot = root + "image/"； //当前图片路径
//帧数
const int FPS = 60;
//颜色
const SDL_Color white = { 255, 255, 255, 255 };

#endif