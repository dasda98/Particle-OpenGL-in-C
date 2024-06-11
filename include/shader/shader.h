#ifndef SHADER_H
#define SHADER_H

typedef struct {
    unsigned int ID;
} Shader;

Shader createShader(const char* vertexPath, const char* fragmentPath);
void useShader(Shader* shader);

char* readFile(const char* filePath);
void checkCompileErrors(unsigned int shader, const char* type);

#endif //SHADER_H
