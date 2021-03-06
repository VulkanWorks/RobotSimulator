//--------------------------------------------------
// Robot Simulator
// scene.h
// Date: 16/07/2020
// By Breno Cunha Queiroz
//--------------------------------------------------
#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <memory>
#include "defines.h"
#include "physics/physicsEngine.h"
#include "vulkan/model.h"
#include "vulkan/texture.h"
#include "vulkan/buffer.h"
#include "vulkan/commandPool.h"
#include "vulkan/material.h"
#include "object.h"

class Scene
{
	public:
		Scene();
		~Scene();

		void loadObject(std::string fileName);
		void addObject(Object* object);
		void addComplexObject(Object* object);
		void createBuffers(CommandPool* commandPool);

		void linkObjects();
		void updatePhysics(float dt);

		//--------- Getters ----------//
		PhysicsEngine* getPhysicsEngine() const { return _physicsEngine; }
		//----- Simulation specific ------//
		std::vector<Object*> getObjects() const { return _objects; };
		std::vector<Model*> getModels() const { return _models; };
		std::vector<Texture*> getTextures() const { return _textures; };

		Buffer* getVertexBuffer() const { return _vertexBuffer; }
		Buffer* getIndexBuffer() const { return _indexBuffer; }
		Buffer* getMaterialBuffer() const { return _materialBuffer; }
		Buffer* getOffsetBuffer() const { return _offsetBuffer; }
		Buffer* getAabbBuffer() const { return _aabbBuffer; }
		Buffer* getProceduralBuffer() const { return _proceduralBuffer; }
		bool hasProcedurals() const { return static_cast<bool>(_proceduralBuffer); }

		//----- Line debugger -----//
		void addLine(glm::vec3 p0, glm::vec3 p1, glm::vec3 color);
		void cleanLines();
		void drawCollisionShapes();
		void updateLineBuffer();

		//----- Simulator specific -----//
		Buffer* getLineVertexBuffer() const { return _lineVertexBuffer; }
		Buffer* getLineIndexBuffer() const { return _lineIndexBuffer; }
		uint32_t getLineIndexCount() const {return _lineIndexCount; }

		//---- Physics helpers ----//
		Object* getObjectFromPhysicsBody(btRigidBody* body);

	private:
		template <class T>
		void createSceneBuffer(Buffer*& buffer,
			const VkBufferUsageFlags usage, 
			const std::vector<T>& content,
			const uint32_t maxElements=0);

		template <class T>
		void copyFromStagingBuffer(Buffer* dstBuffer, const std::vector<T>& content);

		void genGridLines();

		// Objects in the scene
		std::vector<Object*> _objects;
		// Models and textures loaded to the memory
		std::vector<Model*> _models;
		std::vector<Texture*> _textures;

		Device* _device;
		CommandPool* _commandPool;
		Buffer* _vertexBuffer;
		Buffer* _indexBuffer;
		Buffer* _materialBuffer;
		Buffer* _offsetBuffer;
		Buffer* _aabbBuffer;
		Buffer* _proceduralBuffer;

		// Simulator specific
		uint32_t _maxLineCount;// Maximum number of lines that can be store in memory
		uint32_t _lineIndexCount;// Current index count (line count*2)
		uint32_t _indexGridCount;// Number of lines in the grid
		Buffer* _lineVertexBuffer;
		Buffer* _lineIndexBuffer;
		std::vector<Vertex> _hostLineVertex;
		std::vector<uint32_t> _hostLineIndex;

		//---------- Physics ----------//
		PhysicsEngine* _physicsEngine;
};

#endif// SCENE_H
