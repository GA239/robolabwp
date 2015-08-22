#include "pch.h"
#include "MZFlowGraphicObject.h"

#include "Model/Game/MZGame.h"
#include "Model/Basic Types/MZMacro.h"
#include "Model\Game\Game objects\MZFlow.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"
#include "View/Graphics/Vertex system/MZVertexSystem.h"


MZFlowGraphicObject::MZFlowGraphicObject(void)
{
    _particlesCount = 0;
    _particlePositionData = NULL;
    _particlePropertiesData = NULL;
}


MZFlowGraphicObject::~MZFlowGraphicObject(void)
{
    if(_particlePositionData != NULL)
    {
        free(_particlePositionData);
        _particlePositionData = NULL;
    }
    if(_particlePropertiesData != NULL)
    {
        free(_particlePropertiesData);
        _particlePropertiesData = NULL;
    }
}

void MZFlowGraphicObject::render()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	MZMatrixSystem* MatrixSystem = MZMatrixSystem::getInstance();
	MZTextureSystem* TextureSystem = MZTextureSystem::getInstance();
	//////////////////////////////////////////////////////////////////////
	ShaderSystem->useProgramWithName("particle");
    TextureSystem->useColorWithKey("flow");
    MatrixSystem->prepare();
    glDrawArrays(GL_POINTS, 0, _particlesCount);
    
	//////////////////////////////////////////////////////////////////////
	ShaderSystem->FreeInst();
	MatrixSystem->FreeInst();
	TextureSystem->FreeInst();
}
void MZFlowGraphicObject::newGame()
{
	MZVertexSystem* VertexSystem = MZVertexSystem::getInstance();
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////
	_particlesCount = 0;
	vector<MZGameObject*> objectList = Game->_maze->objectList();
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] != NULL)
		{
			if (objectList[i]->info() == FLOW)
			{
				MZFlow *flow = (MZFlow*)objectList[i];
				_particlesCount += flow->length() * 20;
			}
		}
    }
    
    if(_particlePositionData != NULL)
    {
        free(_particlePositionData);
        _particlePositionData = NULL;
    }
    if(_particlePropertiesData != NULL)
    {
        free(_particlePropertiesData);
        _particlePropertiesData = NULL;
    }

   if(_particlesCount != 0)
    {
        int shift = 0;
        _particlePropertiesData = (float *)malloc(sizeof(float) * 4 * _particlesCount);
        _particlePositionData = (float *) malloc(sizeof(float) * 3 * _particlesCount);
		for (unsigned int j = 0; j < objectList.size(); j++)
		{
			if (objectList[j] != NULL)
			{
				if (objectList[j]->info() == FLOW)
				{
					MZFlow *flow = (MZFlow*)objectList[j];
					int i;
					for(i = 0; i < flow->length() * 20; i++)
					{
						switch (flow->direction())
						{
							case RIGHT:
								_particlePositionData[(shift + i) * 3] = (float)flow->position()->x();
								_particlePositionData[(shift + i) * 3 + 1] = flow->position()->y() + (double)(rand()%100)/100.0;
								_particlePropertiesData[(shift + i) * 4] = flow->speed() - 0.05 + (double)(rand()%10)/100.0;
								_particlePropertiesData[(shift + i) * 4 + 1] = 0;
								break;
							case LEFT:
								_particlePositionData[(shift + i) * 3] = flow->position()->x() + 1;
								_particlePositionData[(shift + i) * 3 + 1] = flow->position()->y() + (double)(rand()%100)/100.0;
								_particlePropertiesData[(shift + i) * 4] = - flow->speed() + 0.05 - (double)(rand()%10)/100.0;
								_particlePropertiesData[(shift + i) * 4 + 1] = 0;
								break;
							case UP:
								_particlePositionData[(shift + i) * 3] = flow->position()->x() + (double)(rand()%100)/100.0;
								_particlePositionData[(shift + i) * 3 + 1] = flow->position()->y();
								_particlePropertiesData[(shift + i) * 4] = 0;
								_particlePropertiesData[(shift + i) * 4 + 1] = flow->speed() - 0.05 + (double)(rand()%10)/100.0;
								break;
							case DOWN:
								_particlePositionData[(shift + i) * 3] = flow->position()->x() + (double)(rand()%100)/100.0;
								_particlePositionData[(shift + i) * 3 + 1] = flow->position()->y() + 1;
								_particlePropertiesData[(shift + i) * 4] = 0;
								_particlePropertiesData[(shift + i) * 4 + 1] = - flow->speed() + 0.05 - (double)(rand()%10)/100.0;
								break;
						}
						_particlePositionData[(shift + i) * 3 + 2] = flow->length();
						_particlePropertiesData[(shift + i) * 4 + 2] = 0.5 + (double)(rand() % 50) / 50.0; //alpha value
						_particlePropertiesData[(shift + i) * 4 + 3] = (double)(rand() % 100) * flow->length(); // starting position in flow
					}
					shift += i;
				}
			}
		}
        
        MZVertexBuffer *particlePropertiesBuffer = new MZVertexBuffer(PARTICLE_PROPERTIES_BUFFER,_particlePropertiesData, sizeof(float) * 4 * _particlesCount, "properties");
        MZVertexBuffer *particlePositionBuffer = new MZVertexBuffer(PARTICLE_STARTING_POSITION_BUFFER, _particlePositionData, sizeof(float) * 3 * _particlesCount, "startingPosition");
        
        MZGeometry *particleGeometry = new MZGeometry();
        particleGeometry->addVertexBuffer(particlePositionBuffer);
        particleGeometry->addVertexBuffer(particlePropertiesBuffer);
        particleGeometry->bindInProgram("particle");
        VertexSystem->setGeometry(particleGeometry, "particles");
        VertexSystem->useGeometryWithName("particles");
    }
	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
	VertexSystem->FreeInst();
}
