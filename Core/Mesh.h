<<<<<<< HEAD
#ifndef MESH_H
#define MESH_H

#include "Object.h"

class Mesh
{
	private:
		Object mesh;

	public:
		Mesh();
		virtual ~Mesh();

		bool Initialize(/*Model* modelRawData*/);

		void Update();
		void Render();
};

=======
#ifndef MESH_H
#define MESH_H

#include "Object.h"

class Mesh
{
	private:
		Object mesh;

	public:
		Mesh();
		virtual ~Mesh();

		bool Initialize(/*Model* modelRawData*/);

		void Update();
		void Render();
};

>>>>>>> 1ed802f4b6ab5e0da54017392c9b581129a6155b
#endif