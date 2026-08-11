/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 ****************************************************************************/
#include "2d/CCCameraBackgroundBrush.h"
#include "base/ccTypes.h"
#include "2d/CCCamera.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "platform/CCGL.h"  // для glClear, glClearColor

NS_CC_BEGIN

CameraBackgroundBrush::CameraBackgroundBrush()
{
}

CameraBackgroundBrush::~CameraBackgroundBrush()
{
}

CameraBackgroundBrush* CameraBackgroundBrush::createNoneBrush()
{
    auto ret = new (std::nothrow) CameraBackgroundBrush();
    ret->init();
    ret->autorelease();
    return ret;
}

// Изменяем возвращаемый тип на CameraBackgroundBrush*
CameraBackgroundBrush* CameraBackgroundBrush::createColorBrush(const Color4F& color, float depth)
{
    return CameraBackgroundColorBrush::create(color, depth);
}

// Изменяем возвращаемый тип на CameraBackgroundBrush*
CameraBackgroundBrush* CameraBackgroundBrush::createDepthBrush(float depth)
{
    return CameraBackgroundDepthBrush::create(depth);
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundDepthBrush::CameraBackgroundDepthBrush()
: _depth(0.f)
, _clearColor(false)
{
}

CameraBackgroundDepthBrush::~CameraBackgroundDepthBrush()
{
}

CameraBackgroundDepthBrush* CameraBackgroundDepthBrush::create(float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundDepthBrush();
    
    if (nullptr != ret && ret->init())
    {
        ret->_depth = depth;
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool CameraBackgroundDepthBrush::init()
{
    return true;
}

void CameraBackgroundDepthBrush::drawBackground(Camera* /*camera*/)
{
    glClearDepth(_depth);
    glClear(GL_DEPTH_BUFFER_BIT);
}

//////////////////////////////////////////////////////////////////////////////////////////

CameraBackgroundColorBrush::CameraBackgroundColorBrush()
: _color(0.f, 0.f, 0.f, 0.f)
{
}

CameraBackgroundColorBrush::~CameraBackgroundColorBrush()
{
}

bool CameraBackgroundColorBrush::init()
{
    return true;
}

void CameraBackgroundColorBrush::drawBackground(Camera* camera)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CameraBackgroundColorBrush::setColor(const Color4F& color)
{
    _color = color;
}

CameraBackgroundColorBrush* CameraBackgroundColorBrush::create(const Color4F& color, float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundColorBrush();

    if (nullptr != ret && ret->init())
    {
        ret->setColor(color);
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

NS_CC_END
