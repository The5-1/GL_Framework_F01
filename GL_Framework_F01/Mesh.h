#pragma once

#include "stl_include.h"
#include "GL_include.h"
#include "assimp_include.h"

#include "Logging.h"

#include "ForwardDeclarations.h"

#include "Shader.h"


namespace The5 {

	struct Vertex {
	public:
		// position
		vec3 position;
		// normal
		vec3 normal;
		// tangent
		vec3 tangent;
		// bitangent
		vec3 bitangent;
		// texCoords
		vec2 uv0;
		// vertex colors
		vec3 color0;

		Vertex(vec3 pos)
		{
			position = pos;
		}

		static vertexList makeVertices(vec3List points)
		{
			vertexList verts;
			for (auto const& pos : points) 
			{
				verts.push_back(Vertex(pos));
			}
			return verts;
		}
	};

	//static std::vector<Mesh> MeshRessources;

	class Mesh {
	public:
		std::string name;

		vertexList vertices;
		indexList indices;
		unsigned int VAO; //stores state of vertex attributes

		Mesh(std::string name, vertexList vertices, indexList indices) : name(name)
		{
			this->vertices = vertices;
			this->indices = indices;
			createBuffers();
		}

		Mesh(std::string name, vec3List positions, indexList indices) : name(name)
		{
			vertexList vertices = Vertex::makeVertices(positions);
			this->vertices = vertices;
			this->indices = indices;
			createBuffers();
		}

		void draw()
		{
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}


	private:
		std::string filepath;
		unsigned int VBO; //sores all per-vertex data
		unsigned int EBO; //stores indices

		void createBuffers()
		{
			//generate unique NAMEs/IDs for the buffers and store the references to them, does not set any state yet
			glGenVertexArrays(1, &VAO); //VAO references all buffers and their format
			glGenBuffers(1, &VBO); //will hold the entire vertex struct with all its attributes
			glGenBuffers(1, &EBO); //will hold the indices

			//VAO stores the state of...
			//- enabled/disabled VertexAttribArrays
			//- bound VertexAttribPointers and their VBOs
			//its kind of a container so we can easily recreate a state later on
			glBindVertexArray(VAO); //(There is only one target to bind VAOs to, so it got a own function.)

			glBindBuffer(GL_ARRAY_BUFFER, VBO);  //Bind the VBO to the GL_ARRAY_BUFFER binding point, only one can be bound to each binding point at once
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //Copy CPU vertex struct into the specified GPU buffer

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER binding point
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); //Copy CPU vertex indices into the specified GPU buffer

			//Set the state for the vertex attributes
			//Since the VAO is bound, we also store this state in the VAO
			glEnableVertexAttribArray(0); //enables the generic vertex attribute array to be used by glDrawArrays or glDrawElements
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); //location, vec3, floats, not normalize, stride = sizeof(Vertex), offset where the data in the buffer begins
			// vertex normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			// vertex tangent
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
			// vertex bitangent
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
			// vertex texture coords
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv0));
			// vertex colors
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color0));

			glBindVertexArray(0); //Disable storing in the VAO, the state above is memorized in the VAO
		}
	};
}
