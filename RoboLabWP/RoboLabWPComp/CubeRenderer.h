#pragma once
//#define GL_GLEXT_PROTOTYPES

//#define GL_GLEXT_PROTOTYPES

#include "AngleBase.h"
#include <DirectXMath.h>
#include <stdlib.h>

#include <string>

using namespace std;



// This class renders a simple spinning cube.
ref class CubeRenderer sealed : public AngleBase
{
public:
	CubeRenderer();
	virtual ~CubeRenderer();

	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	void Update(float timeTotal, float timeDelta);
	virtual void OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation) override;
	virtual void OnRender() override;
    virtual void CreateGLResources() override;



private:
    void UpdatePerspectiveMatrix();
	//GLuint loadtexture( char* fileName );
	GLuint loadtextureMOD(const string &path);

    bool m_loadingComplete;
    GLuint m_colorProgram;
    GLint a_positionColor;
    GLint a_colorColor;
    GLint u_mvpColor;
    DirectX::XMMATRIX m_projectionMatrix;
    DirectX::XMMATRIX m_viewMatrix;
    DirectX::XMMATRIX m_modelMatrix;

	// Handle to a program object
	GLuint mProgram;

	// Attribute locations
	GLint mPositionLoc;
	GLint mTexCoordLoc;

	// Sampler locations
	GLint mBaseMapLoc;
	GLint mLightMapLoc;

	// Texture handle
	GLuint mBaseMapTexID;
	GLuint mLightMapTexID;
};
