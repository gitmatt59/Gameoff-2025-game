class entity{
  public:
    
    glm::vec3 cord;
    unsigned int VAO;
    entity(float x, float y ,float z ,unsigned int V){
    cord= glm::vec3{x , y, z};
    VAO=V;
    }
    
};

