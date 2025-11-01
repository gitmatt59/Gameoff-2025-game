#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		return -1;
	}

class entity{
  public:
    
    glm::vec3 cord;
    unsigned int VAO;
    entity(float x, float y ,float z ,unsigned int V){
    cord= glm::vec3{x , y, z};
    VAO=V;
    }
    
};


float vertices[] ={

    -1.0f, 1.0f, 0.0f,
     1.0f, 1.0f, 0.0f,
    -1.0f,-1.0f, 0.0f,
     1.0f, -1.0f,0.0f
  };


	unsigned int indices[] ={

		0,1,2,2,3,1

		
	};
	unsigned int EBO;
	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) ,indices ,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER ,VBO);
	glBufferData(GL_ARRAY_BUFFER ,sizeof(vertices) ,vertices ,GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

	
	glEnableVertexAttribArray(0);

	  entity player(0.0,0.0,0.0,VAO);

