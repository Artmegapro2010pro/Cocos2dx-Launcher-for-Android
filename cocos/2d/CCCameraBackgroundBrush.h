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

#ifndef __CCCAMERABACKGROUNDBRUSH_H__
#define __CCCAMERABACKGROUNDBRUSH_H__

#include "base/ccTypes.h"
#include "base/CCRef.h"
#include "renderer/CCQuadCommand.h"
#include "renderer/CCCustomCommand.h"
#include "renderer/CCGroupCommand.h"
#include "renderer/backend/Types.h"

NS_CC_BEGIN

class Camera;

// ============================================================
// 1. Сначала объявляем дочерние классы (чтобы они были видны)
// ============================================================

class CC_DLL CameraBackgroundDepthBrush : public Ref
{
public:
    static CameraBackgroundDepthBrush* create(float depth = 1.f);
    void drawBackground(Camera* camera);
    void setDepth(float depth) { _depth = depth; }

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundDepthBrush();
    virtual ~CameraBackgroundDepthBrush();
    bool init();

protected:
    float _depth = 1.0f;
    bool _clearColor = false;
};

class CC_DLL CameraBackgroundColorBrush : public Ref
{
public:
    static CameraBackgroundColorBrush* create(const Color4F& color, float depth = 1.f);
    void drawBackground(Camera* camera);
    void setColor(const Color4F& color);

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundColorBrush();
    virtual ~CameraBackgroundColorBrush();
    bool init();

protected:
    Color4F _color;
};

// ============================================================
// 2. Теперь объявляем базовый класс (он использует дочерние)
// ============================================================

class CC_DLL CameraBackgroundBrush : public Ref
{
public:
    enum class BrushType
    {
        NONE,   // none brush
        DEPTH,  // depth brush
        COLOR,  // color brush
    };
    
    virtual BrushType getBrushType() const { return BrushType::NONE; }
    
    static CameraBackgroundBrush* createNoneBrush();
    static CameraBackgroundBrush* createDepthBrush(float depth = 1.f);
    static CameraBackgroundBrush* createColorBrush(const Color4F& color, float depth = 1.f);
    
    virtual void drawBackground(Camera* camera) {}
    virtual bool isValid() { return true; }

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundBrush();
    virtual ~CameraBackgroundBrush();
    virtual bool init() { return true; }
};

NS_CC_END

#endif // __CCCAMERABACKGROUNDBRUSH_H__
