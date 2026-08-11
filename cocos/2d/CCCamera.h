/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#ifndef __CCCAMERA_H__
#define __CCCAMERA_H__

#include "2d/CCNode.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class Renderer;

/** Camera flag. */
enum class CameraFlag
{
    DEFAULT = 1,
    USER1 = 1 << 1,
    USER2 = 1 << 2,
    USER3 = 1 << 3,
    USER4 = 1 << 4,
    USER5 = 1 << 5,
    USER6 = 1 << 6,
    USER7 = 1 << 7,
    USER8 = 1 << 8,
};

/** 
 @brief Camera is a base class for all cameras, used to determine what and how to render to the screen.
 
 A Camera has projection matrix, view matrix and additional transform.
 */
class CC_DLL Camera : public Node
{
public:
    /** Creates a default camera.
     @return An autoreleased Camera object.
     */
    static Camera* create();
    
    /** Initializes camera with default values */
    virtual bool init() override;
    
    /** Initializes camera with perspective projection.
     @param fieldOfView The field of view for perspective projection.
     @param aspectRatio The aspect ratio of camera.
     @param nearPlane The near clipping plane distance.
     @param farPlane The far clipping plane distance.
     @return true if successful, otherwise false.
     */
    bool initWithPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    
    /** Initializes camera with orthographic projection.
     @param zoomX The zoom factor for X axis.
     @param zoomY The zoom factor for Y axis.
     @param nearPlane The near clipping plane distance.
     @param farPlane The far clipping plane distance.
     @return true if successful, otherwise false.
     */
    bool initWithOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    
    /** Initialize default camera */
    void initDefault();
    
    /** Apply the camera */
    void apply();
    
    /** Clear background with max depth */
    void clearBackground();
    
    /** Gets the view matrix of camera.
     @return The view matrix.
     */
    const Mat4& getViewMatrix() const { return _viewMatrix; }
    
    /** Gets the projection matrix of camera.
     @return The projection matrix.
     */
    const Mat4& getProjectionMatrix() const { return _projectionMatrix; }
    
    /** Gets the view projection matrix of camera.
     @return The view projection matrix.
     */
    const Mat4& getViewProjectionMatrix() const;
    
    /** Gets the projection type of camera.
     @return The projection type.
     */
    int getProjectionType() const { return _projectionType; }
    
    /** Gets the camera flag.
     @return The camera flag.
     */
    CameraFlag getCameraFlag() const { return _cameraFlag; }
    
    /** Sets the camera flag.
     @param flag The camera flag.
     */
    void setCameraFlag(CameraFlag flag) { _cameraFlag = flag; }
    
    /** Gets the render order.
     @return The render order.
     */
    int getRenderOrder() const { return _renderOrder; }
    
    /** Sets the render order.
     @param order The render order.
     */
    void setRenderOrder(int order) { _renderOrder = order; }
    
    /** Gets the depth of the camera.
     @return The camera depth.
     */
    float getDepth() const { return _depth; }
    
    /** Sets the depth of the camera.
     @param depth The camera depth.
     */
    void setDepth(float depth) { _depth = depth; }
    
    /** Check if the camera is visible.
     @return true if visible, false if not.
     */
    bool isVisible() const { return _visible; }
    
    /** Set the visibility.
     @param visible true if visible, false if not.
     */
    void setVisible(bool visible) { _visible = visible; }
    
    /** Set the additional projection matrix.
     @param mat The additional projection matrix.
     */
    void setAdditionalProjection(const Mat4& mat) { _additionalProjection = mat; }
    
    /** Gets the additional projection matrix.
     @return The additional projection matrix.
     */
    const Mat4& getAdditionalProjection() const { return _additionalProjection; }
    
    /** Set the additional transform matrix.
     @param mat The additional transform matrix.
     */
    void setAdditionalTransform(const Mat4& mat) { _additionalTransform = mat; }
    
    /** Gets the additional transform matrix.
     @return The additional transform matrix.
     */
    const Mat4& getAdditionalTransform() const { return _additionalTransform; }
    
    /** Check if the camera has depth test.
     @return true if depth test is enabled, false if not.
     */
    bool getDepthTest() const { return _depthTest; }
    
    /** Set the depth test.
     @param depthTest true to enable depth test, false to disable.
     */
    void setDepthTest(bool depthTest) { _depthTest = depthTest; }
    
    /** Check if the camera has clear color.
     @return true if clear color is enabled, false if not.
     */
    bool getClearColor() const { return _clearColor; }
    
    /** Set the clear color.
     @param clearColor true to enable clear color, false to disable.
     */
    void setClearColor(bool clearColor) { _clearColor = clearColor; }
    
    /** Gets the clear color.
     @return The clear color.
     */
    const Color4F& getClearColorValue() const { return _clearColorValue; }
    
    /** Sets the clear color.
     @param clearColor The clear color.
     */
    void setClearColorValue(const Color4F& clearColor) { _clearColorValue = clearColor; }
    
    /** Check if the camera has clear depth.
     @return true if clear depth is enabled, false if not.
     */
    bool getClearDepth() const { return _clearDepth; }
    
    /** Set the clear depth.
     @param clearDepth true to enable clear depth, false to disable.
     */
    void setClearDepth(bool clearDepth) { _clearDepth = clearDepth; }
    
    /** Gets the clear depth.
     @return The clear depth.
     */
    float getClearDepthValue() const { return _clearDepthValue; }
    
    /** Sets the clear depth.
     @param clearDepth The clear depth.
     */
    void setClearDepthValue(float clearDepth) { _clearDepthValue = clearDepth; }
    
    /** Check if the camera has clear stencil.
     @return true if clear stencil is enabled, false if not.
     */
    bool getClearStencil() const { return _clearStencil; }
    
    /** Set the clear stencil.
     @param clearStencil true to enable clear stencil, false to disable.
     */
    void setClearStencil(bool clearStencil) { _clearStencil = clearStencil; }
    
    /** Gets the clear stencil.
     @return The clear stencil.
     */
    int getClearStencilValue() const { return _clearStencilValue; }
    
    /** Sets the clear stencil.
     @param clearStencil The clear stencil.
     */
    void setClearStencilValue(int clearStencil) { _clearStencilValue = clearStencil; }
    
    /** Gets the camera type.
     @return The camera type.
     */
    int getCameraType() const { return _cameraType; }
    
public:
    static Camera* _visitingCamera;
    
CC_CONSTRUCTOR_ACCESS:
    Camera();
    virtual ~Camera();
    
protected:
    enum
    {
        CAMERA_TYPE_DEFAULT = 0,
        CAMERA_TYPE_PERSPECTIVE = 1,
        CAMERA_TYPE_ORTHOGRAPHIC = 2,
    };
    
    void updateMatrix();
    
    Mat4 _viewMatrix;                // The view matrix.
    Mat4 _projectionMatrix;          // The projection matrix.
    Mat4 _viewProjectionMatrix;      // The view projection matrix.
    Mat4 _additionalProjection;      // Additional projection matrix.
    Mat4 _additionalTransform;       // Additional transform.
    int _projectionType;
    
    int _renderOrder;
    float _depth;
    CameraFlag _cameraFlag;
    bool _visible;
    bool _depthTest;
    bool _clearColor;
    bool _clearDepth;
    bool _clearStencil;
    Color4F _clearColorValue;
    float _clearDepthValue;
    int _clearStencilValue;
    int _cameraType;
    bool _dirty;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Camera);
};

NS_CC_END

#endif // __CCCAMERA_H__
