#pragma once

#include "Model\Basic Types\MZMotion.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"
#include "View/Graphics/Vertex system/MZVertexSystem.h"

#include "View\Graphics\Graphic objects\MZGraphicObject.h"

class MZRenderingCore
{
public:
	MZRenderingCore(void);
	virtual ~MZRenderingCore(void);

	void update(int frame);
	void updateStepMadeWithMotion(MZMotion * motion);
	void updateNewGame();
	void render();
	void pinchFired();

private:
	MZShaderSystem *_shaderSystem;
    MZMatrixSystem *_matrixSystem;
    MZTextureSystem *_textureSystem;
    MZAnimationSystem *_animationSystem;
    MZVertexSystem *_vertexSystem;
    
    MZVertexBuffer *_particlePositionBuffer;
    MZVertexBuffer *_particlePropertiesBuffer;
    MZVertexArrayObject *_vertexArrayObject;
    double _zoom;
    
    vector<MZGraphicObject*> _graphicObjects;
    //NSMutableDictionary *_graphicObjects;
    int _frame;
};

