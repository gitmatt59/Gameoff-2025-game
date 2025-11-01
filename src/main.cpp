#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <shaderclass.h>
#include <cameraclass.h>

#include <stb_image.h>
#include <textureclass.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vertex_stuff.h>

class entity{
  public:
    
    glm::vec3 cord;
    unsigned int VAO;
    entity(float x, float y ,float z ,unsigned int V){
    cord= glm::vec3{x , y, z};
    VAO=V;
    }
    
};

glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{



}  
void Input(GLFWwindow *window){
	if(glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)glfwSetWindowShouldClose(window , true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR ,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window =glfwCreateWindow(800,600,"coolest game that you will ever see, trust",NULL,NULL);
	if (window==NULL){
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		return -1;
	}
	glViewport(0,0,800,600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
	//shader
	Shader shader1("../shaders/default.vert" ,"../shaders/default.frag");

	
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






	//transformations
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); 
	//shader1.use();
	//unsigned int transformLoc = glGetUniformLocation(shader1.ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	//textures
  Texture texture1("container.jpg");
  texture1.activate(GL_TEXTURE0);
	

	shader1.use();
	shader1.setInt("texture1",0);
	shader1.setInt("texture2",1);
	
	int modelLoc = glGetUniformLocation(shader1.ID, "model");
	int viewLoc = glGetUniformLocation(shader1.ID, "view");
	int projectionLoc = glGetUniformLocation(shader1.ID, "projection");


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	//camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f); 
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 
	cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
	view =glm::lookAt(cameraPos , cameraPos+cameraFront ,cameraUp);
	float rot=1.0f;
	float cameraSpeed=0.05f;

	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetCursorPosCallback(window, mouse_callback); 

	//go to start of file to see code

	float currentFrame , dt,lastFrame=0;
	glEnable(GL_DEPTH_TEST);  
	while(!glfwWindowShouldClose(window))
	{
		currentFrame = glfwGetTime();
	  dt = currentFrame - lastFrame;					
		lastFrame = currentFrame;

		cameraSpeed=10.0f * dt;
		//input
		Input(window);

		//drawin
		shader1.use();
		glClearColor(0.2f,0.1f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//model = glm::rotate(model,   glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//const float radius = 10.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); 
    model =glm::mat4{1.0f};
		shader1.use();

		glBindVertexArray(player.VAO);
    model = glm::translate(model,player.cord);
		glDrawElements(GL_TRIANGLES ,6,GL_UNSIGNED_INT ,0);
		//glDrawArrays(GL_TRIANGLES,0,3);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glfwSwapBuffers(window);
		glfwPollEvents();		

		if(glfwGetKey(window , GLFW_KEY_D) == GLFW_PRESS)player.cord+=glm::vec3{10.0f*dt,0.0f,0.0f};
    if(glfwGetKey(window , GLFW_KEY_A) == GLFW_PRESS)player.cord+=glm::vec3{-10.0f*dt,0.0f,0.0f};	
    if(glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS)player.cord+=glm::vec3{0.0f,10.0f*dt,0.0f};
		if(glfwGetKey(window , GLFW_KEY_S) == GLFW_PRESS)player.cord+=glm::vec3{0.0f,-10.0f*dt,0.0f};

		
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	}


	glfwTerminate();

	return 0;

}

