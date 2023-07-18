#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <chrono>
#include <cmath>
#include <math.h>
#include "utils.hpp"

/*

TP1 du cours IMN401 a remettre le 20 fevrier 2023

    Remis par : 
        Ivan Serra Moncadas seri1101
        Mathis MOYSE moym1101
        Robin LEJEUNE lejr0501
*/

namespace IMN401 {

    GLuint programFS;
    GLuint varUniform;
    GLuint timeUniform;

    void printProgramError(GLuint program)
    {
        GLuint isLinked;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            std::cout << "Error : " + std::string(infoLog.begin(), infoLog.end()) + "\n";

            // We don't need the program anymore.
            glDeleteProgram(program);
            return;
        }
        else
            std::cout << "Shader compilation...OK" << std::endl;


    }

    void printPipelineError(GLuint pipeline)
    {
        GLuint isValid;
        glGetProgramPipelineiv(pipeline, GL_VALIDATE_STATUS, (int*)&isValid);
        if (isValid == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramPipelineiv(pipeline, GL_INFO_LOG_LENGTH, &maxLength);
            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramPipelineInfoLog(pipeline, maxLength, &maxLength, &infoLog[0]);

            std::cout << "Error : " + std::string(infoLog.begin(), infoLog.end()) + "\n";
            // We don't need the program anymore.
            glDeleteProgram(pipeline);
            return;
        }
        else
            std::cout << "Pipeline...OK" << std::endl;

    }

    // Fonction de callback qui change la couleur en fonction de la touche pressee
    void callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS && key == GLFW_KEY_E)
        {
            glm::vec3 col(0, 1.0, 0);
            glProgramUniform3f(programFS, varUniform, 0, 1.0, 0);
        }
    }

    int main()
    {
        // Init GLFW
        glfwInit();

        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return EXIT_FAILURE;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const int width = 800;
        const int height = 800;

        GLFWwindow* window = glfwCreateWindow(width, height, "TP - From Scratch", NULL, NULL);
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, NULL);

        glfwSetKeyCallback(window, callback); // voir fonction callback une fonction qui a un comortement en fonction de la touche pressee

        // Load all OpenGL functions using the glfw loader function
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize OpenGL context" << std::endl;
            glfwTerminate();
            return EXIT_FAILURE;
        }


        // shaders
        std::string strVS = readFile("shaders/triangle-vs.glsl"); // VertexShader
        const GLchar* vsCode = strVS.c_str();
        std::string strFS = readFile("shaders/triangle-fs.glsl"); // FragmentShader
        const GLchar* fsCode = strFS.c_str();



        // Initialization
        // ===============================
        // TODO: init buffers, shaders, etc.
        // cf. https://www.khronos.org/files/opengl46-quick-reference-card.pdf

        glClearColor(1, 1, 1, 1.0);

        GLint const nombreSommets = 111; 
        const float radius = 0.5f; // rayon du cercle

        int const size = nombreSommets + 1; // On fait +1 car il y a le centre en plus
        int i = 1;

        glm::vec3 vec[size];
        vec[0] = glm::vec3(0.0f, 0.0f, 0.0f); // le centre du cercle si on veut deplacer le cercle il faut penser à changer les valeurs c et s en faisant x + c et y + s
        // boucle qui recupere toutes les valeurs trigonometriques autour du centre
        for (i; i <= nombreSommets; i++)
        {
            GLfloat c = radius * cos(i * 2.0f * M_PI/ nombreSommets);
            GLfloat s = radius * sin(i * 2.0f * M_PI / nombreSommets);
            vec[i] = glm::vec3(c, s, 0.0f);
        }

        int const IndexSize = 3 * size;
        GLuint index[IndexSize];
        GLuint j = 0;
        for (j; j < nombreSommets; j++)
        {
            GLuint temp = j;
            index[j * 3] = 0;
            index[j * 3 + 1] = temp + 1;
            index[j * 3 + 2] = temp + 2;
        }
        index[(j-1) * 3 + 2] = 1; // la derniere valeur est à 1 pour faire fermer le cercle

        
        // Creation du VBO
        GLuint buffer; 
        glCreateBuffers(1, &buffer); // creation de 1 buffer
        glNamedBufferData(buffer, sizeof(glm::vec3) * size, &vec, GL_STATIC_DRAW); // on rempli le buffer le buffer correspond à lidentifiant du buffer et on met la ref du vec pour avoir les vrai valeurs

        // Creation du VBO indices
        GLuint VBO_indice;
        glCreateBuffers(1, &VBO_indice);

        // On va mettre le VBO (vertex buffer object) dans le VAO (vertex array object)
        // Creation du VAO
        GLuint VA;
        glCreateVertexArrays(1, &VA);
        glEnableVertexArrayAttrib(VA, 0); // Voir la convention (position, couleur etc)
        glVertexArrayAttribFormat(VA, 0 /*le cannal*/, 3, GL_FLOAT, GL_FALSE, 0 /*Ici on indique que c'est continu, la distance entre les elmt*/);
        glVertexArrayVertexBuffer(VA, 0, buffer, 0, sizeof(float) * 3 /*Ici on met la taille en bit dans la mémoire*/);
        glVertexArrayAttribBinding(VA, 0, 0);

        // Creation du pipeline
        GLuint pipeline;
        GLuint programVS = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vsCode);
        programFS = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fsCode);

        glCreateProgramPipelines(1, &pipeline); // Initialiser le pipeline

        glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, programVS); // Dire quon utilise ce program avec ce pipeline
        glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, programFS); // Dire qu'on utilise ce program avec ce pipeline
        
        glValidateProgramPipeline(pipeline); // Verifier que tout ce passe bien

        glBindProgramPipeline(pipeline);
        glBindVertexArray(VA); // On rajoute le VA dans le pipeline

        // Variable uniforme de la couleur FS
        varUniform = glGetUniformLocation(programFS, "couleur");
        glProgramUniform3f(programFS, varUniform, 1.0, 0, 0);

        // Variable uniforme du temps pour le VS
        timeUniform = glGetUniformLocation(programVS, "time");
        auto timeStart = std::chrono::high_resolution_clock::now();
        float time = 0.0f;
        glProgramUniform1f(programVS, timeUniform, time);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indice);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

        printProgramError(programVS);
        printProgramError(programFS);
        printPipelineError(pipeline);

        if (glGetError() != GL_NO_ERROR) {
            std::cerr << "OpenGL error" << std::endl;
            return EXIT_FAILURE;
        }

        /*
        *   Faire une animation
        *    uniform t;
        *    cos(t) -> entre (-1, ... , 1)
        *    pos += alpha * cos(t) * v (le vecteur qui pointe vers le centre)
        *    
        * 
        *      ATTENTION a la concordance des type
        *       C'est à nous d'etre reponsable de preciser la taille des données et les types
        */

        // ===============================

        

        // Rendering loop
        while (!glfwWindowShouldClose(window))
        {
            auto timeNow = std::chrono::high_resolution_clock::now();
            float duration = std::chrono::duration<float, std::milli>(timeNow - timeStart).count();
            time = duration;
            glProgramUniform1f(programVS, timeUniform, time);

            // Handle events
            glfwPollEvents();

         
            // ===============================
            // TODO: render here !

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Toujours mettre cette fonction dans la boucle de rendu
            glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_INT, 0); // Pour afficher avec le mode indexe 
            // ===============================

            glfwSwapBuffers(window);
        }

        // Clean up
        glfwTerminate();

        return EXIT_SUCCESS;
    }
}

int main()
{
    return IMN401::main();
}