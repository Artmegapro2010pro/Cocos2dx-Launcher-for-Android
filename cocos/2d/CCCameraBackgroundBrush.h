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

/**
 * Defines a brush to clear the background of camera.
 */
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
    static CameraBackgroundDepthBrush* createDepthBrush(float depth = 1.f);
    static CameraBackgroundColorBrush* createColorBrush(const Color4F& color, float depth);
    
    virtual void drawBackground(Camera* camera) {}
    virtual bool isValid() { return true; }

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundBrush();
    virtual ~CameraBackgroundBrush();
    virtual bool init() { return true; }
    
protected:
    backend::ProgramState* _programState = nullptr;
};

/**
 * Depth brush clear depth buffer with given depth
 */
class CC_DLL CameraBackgroundDepthBrush : public CameraBackgroundBrush
{
public:
    static CameraBackgroundDepthBrush* create(float depth);
    virtual BrushType getBrushType() const override { return BrushType::DEPTH; }
    virtual void drawBackground(Camera* camera) override;
    void setDepth(float depth) { _depth = depth; }

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundDepthBrush();
    virtual ~CameraBackgroundDepthBrush();
    virtual bool init() override;

private:
    void onBeforeDraw();
    void onAfterDraw();

protected:
    float _depth;
    backend::UniformLocation _locDepth;
    CustomCommand _customCommand;
    GroupCommand _groupCommand;

    bool _clearColor = false;
    std::vector<V3F_C4B_T2F> _vertices;
    struct {
        uint32_t stencilWriteMask = 0;
        bool depthTest = true;
        backend::CompareFunction compareFunc = backend::CompareFunction::ALWAYS;
    } _stateBlock;
};

/**
 * Color brush clear buffer with given depth and color
 */
class CC_DLL CameraBackgroundColorBrush : public CameraBackgroundDepthBrush
{
public:
    virtual BrushType getBrushType() const override { return BrushType::COLOR; }
    static CameraBackgroundColorBrush* create(const Color4F& color, float depth);
    virtual void drawBackground(Camera* camera) override;
    void setColor(const Color4F& color);

CC_CONSTRUCTOR_ACCESS:
    CameraBackgroundColorBrush();
    virtual ~CameraBackgroundColorBrush();
    virtual bool init() override;
    
protected:
    Color4F _color;
};

NS_CC_END

#endif // __CCCAMERABACKGROUNDBRUSH_H__
