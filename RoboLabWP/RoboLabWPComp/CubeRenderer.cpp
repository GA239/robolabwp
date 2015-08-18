
#include "pch.h"

#include "CubeRenderer.h"

#include "..\shader.h"
#include "..\fshader.h"
//#include "esUtil.h"
#include "tga_utils.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

struct VertexPositionColor
{
	XMFLOAT3 pos;
	XMFLOAT3 color;
};

CubeRenderer::CubeRenderer(): m_loadingComplete(false)
{
}

void CubeRenderer::CreateDeviceResources()
{
	AngleBase::CreateDeviceResources();
}

CubeRenderer::~CubeRenderer()
{
	
	glDeleteProgram(m_colorProgram);
	glDeleteProgram(mProgram);
	glDeleteTextures(1, &mBaseMapTexID);
	glDeleteTextures(1, &mLightMapTexID);
}

void CubeRenderer::CreateGLResources()
{
    m_colorProgram = glCreateProgram();
	glProgramBinaryOES(m_colorProgram, GL_PROGRAM_BINARY_ANGLE, gProgram, sizeof(gProgram));
    a_positionColor = glGetAttribLocation(m_colorProgram, "a_position");
    a_colorColor = glGetAttribLocation(m_colorProgram, "a_color");
    u_mvpColor = glGetUniformLocation(m_colorProgram, "u_mvp");
	
	
	//texture
	mProgram = glCreateProgram();
	glProgramBinaryOES(mProgram, GL_PROGRAM_BINARY_ANGLE, gfProgram, sizeof(gfProgram));
	// Get the attribute locations
	mPositionLoc = glGetAttribLocation(mProgram, "a_position");
	mTexCoordLoc = glGetAttribLocation(mProgram, "a_texCoord");
	
	mBaseMapLoc = glGetUniformLocation(mProgram, "s_baseMap");
	mLightMapLoc = glGetUniformLocation(mProgram, "s_lightMap");
	
	// Load the textures
	mBaseMapTexID = loadtextureMOD("basemap.tga");
	mLightMapTexID = loadtextureMOD("lightmap.tga");
	if (mBaseMapTexID == 0 || mLightMapTexID == 0)
	{
		m_loadingComplete = false;
		return;
	}
	//texture

	//glViewport(0, 0, static_cast<UINT>(m_renderTargetSize.Width), static_cast<UINT>(m_renderTargetSize.Height));
    glEnable(GL_DEPTH_TEST);
    m_loadingComplete = true;
}

GLuint CubeRenderer::loadtextureMOD(const string &path)
{
    TGAImage img;
    if (!LoadTGAImageFromFile(path, &img))
    {
        return 0;
    }

    return LoadTextureFromTGAImage(img);
}

void CubeRenderer::CreateWindowSizeDependentResources()
{
	AngleBase::CreateWindowSizeDependentResources();
}

void CubeRenderer::UpdatePerspectiveMatrix()
{
    float fovAngleY = 70.0f * XM_PI / 180.0f;
    m_projectionMatrix = XMMatrixPerspectiveFovRH(fovAngleY, m_aspectRatio, 0.01f, 100.0f);

    // In Windows Phone 8.0 C++ apps, we need to rotate the projection matrix by the 
    // device's current rotation matrix
    m_projectionMatrix = XMMatrixMultiply(m_orientationMatrix, m_projectionMatrix);
}

void CubeRenderer::OnOrientationChanged(Windows::Graphics::Display::DisplayOrientations orientation)
{
	AngleBase::OnOrientationChanged(orientation);
    UpdatePerspectiveMatrix();
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
	(void) timeDelta;

    XMVECTOR eye = XMVectorSet(0.0f, 0.7f, 1.5f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, -0.1f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
            
	m_viewMatrix = XMMatrixLookAtRH(eye, at, up);
	m_modelMatrix = XMMatrixRotationY(timeTotal * XM_PIDIV4);
}

void CubeRenderer::OnRender()
{
    XMFLOAT4X4 mvp;
    XMStoreFloat4x4(&mvp, (XMMatrixMultiply(XMMatrixMultiply(m_modelMatrix, m_viewMatrix), m_projectionMatrix)));

	
    glClearColor(0.098f, 0.098f, 0.439f, 1.000f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//////////////////////////////////////////////////////////////////
/*    glUseProgram(m_colorProgram);
    glUniformMatrix4fv(u_mvpColor, 1, GL_FALSE, &mvp.m[0][0]);

    VertexPositionColor cubeVertices[] = 
	{
		{XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, 0.0f)},
		{XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT3(0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.5f, -0.5f, -0.5f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{XMFLOAT3( 0.5f, -0.5f,  0.5f), XMFLOAT3(1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.5f,  0.5f, -0.5f), XMFLOAT3(1.0f, 1.0f, 0.0f)},
		{XMFLOAT3( 0.5f,  0.5f,  0.5f), XMFLOAT3(1.0f, 1.0f, 1.0f)},
	};
    unsigned short cubeIndices[] = 
    {

        0,2,1, // -x
        1,2,3,

        4,5,6, // +x
        5,7,6,

        0,1,5, // -y
        0,5,4,

        2,6,7, // +y
        2,7,3,

        0,4,6, // -z
        0,6,2,

        1,3,7, // +z
        1,7,5,
    };
	*/
	//////////////////////////////////////////////////////////////////
	
	//glEnableVertexAttribArray(a_positionColor);
    glEnableVertexAttribArray(a_colorColor);
    //glVertexAttribPointer(a_positionColor, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), cubeVertices);
    //glVertexAttribPointer(a_colorColor, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor), reinterpret_cast<char*>(cubeVertices) + sizeof(XMFLOAT3));
    //glDrawElements(GL_TRIANGLES, ARRAYSIZE(cubeIndices), GL_UNSIGNED_SHORT, cubeIndices);
    //glDisableVertexAttribArray(a_positionColor);
    glDisableVertexAttribArray(a_colorColor);
	

	GLfloat vertices[] =
	{
		-0.5f,  0.5f, 0.0f,  // Position 0
		0.0f,  0.0f,        // TexCoord 0
		-0.5f, -0.5f, 0.0f,  // Position 1
		0.0f,  1.0f,        // TexCoord 1
		0.5f, -0.5f, 0.0f,  // Position 2
		1.0f,  1.0f,        // TexCoord 2
		0.5f,  0.5f, 0.0f,  // Position 3
		1.0f,  0.0f         // TexCoord 3
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the program object
	glUseProgram(mProgram);

	// Load the vertex position
	glVertexAttribPointer(mPositionLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vertices);
	// Load the texture coordinate
	glVertexAttribPointer(mTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vertices + 3);
	
	glEnableVertexAttribArray(mPositionLoc);
	glEnableVertexAttribArray(mTexCoordLoc);

	// Bind the base map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mBaseMapTexID);

	// Set the base map sampler to texture unit to 0
	glUniform1i(mBaseMapLoc, 0);

	// Bind the light map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mLightMapTexID);

	// Set the light map sampler to texture unit 1
	glUniform1i(mLightMapLoc, 1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

	glDisableVertexAttribArray(mPositionLoc);
	glDisableVertexAttribArray(mTexCoordLoc);
}

